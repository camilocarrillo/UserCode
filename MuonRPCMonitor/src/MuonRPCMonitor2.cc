// -*- C++ -*-
//
// Package:    MuonRPCMonitor2
// Class:      MuonRPCMonitor2
// 
/**\class MuonRPCMonitor2 MuonRPCMonitor2.cc MuonRPCMonitor2/MuonRPCMonitor2/src/MuonRPCMonitor2.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Sun Jun 13 13:55:21 CEST 2010
// $Id$
//
//
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MuonRPCMonitor/MuonRPCMonitor/interface/MuonRPCMonitor2.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

MuonRPCMonitor2::MuonRPCMonitor2(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
  rootFileNameOut =iConfig.getUntrackedParameter<std::string>("rootFileNameOut");   
  synchth = iConfig.getUntrackedParameter<double>("synchth");
  minIntegral = iConfig.getUntrackedParameter<double>("minIntegral");
  minMean = iConfig.getUntrackedParameter<double>("minMean");
}


MuonRPCMonitor2::~MuonRPCMonitor2()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MuonRPCMonitor2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  
}


// ------------ method called once each job just before starting event loop  ------------
void MuonRPCMonitor2::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){

  std::cout<<"Begin Job"<<std::endl;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  theFile = new TFile(rootFileName.c_str());
  if(!theFile) std::cout<<"The File Doesn't exist"<<std::endl;
  theFileOut = new TFile(rootFileNameOut.c_str(), "RECREATE");

  ratioHistoBarrel = new TH1F("ratiosychBarrel","ratio synch Barrel",100,0,1); 
  ratioHistoEndCapP = new TH1F("ratiosychEndCapP","ratio synch EndCap +",100,0,1); 
  ratioHistoEndCapN = new TH1F("ratiosychEndCapN","ratio synch EndCap -",100,0,1); 
  BXRMSBarrel = new TH2F("BXVsRMSBarrel","BX Vs RMS Barrel",51,-5.0,5.0,51,0.,4.);  
  BXRMSEndCapP = new TH2F("BXVsRMSEndCapP","BX Vs RMS EndCap+ ",51,-5.0,5.0,51,0.,4.);    
  BXRMSEndCapN = new TH2F("BXVsRMSEndCapN","BX Vs RMS EndCap- ",51,-5.0,5.0,51,0.,4.);    
  Integrals = new TH1F("Integrals","Integrals",1001,-0.5,1000.5); 
  Means = new TH1F("Means","Means",101,-1,1); 
  RealMeans = new TH1F("RealMeans","RealMeans",101,-1,1); 
  RMSs = new TH1F("RMSs","RMSs",100,0,2); 

  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);
	std::string nameRoll = rpcsrv.name();
	std::string meIdRES,folder;
	folder = "DQMData/BXMuon_";
	meIdRES = folder + nameRoll;
	theHisto = (TH1F*)theFile->Get(meIdRES.c_str());
	int noGoodHits = theHisto->Integral()-theHisto->GetBinContent(6);
	float ratio = 0;
	Integrals->Fill(theHisto->Integral());
	Means->Fill(theHisto->GetMean());
	if(theHisto->Integral()>minIntegral)RealMeans->Fill(theHisto->GetMean());
	RMSs->Fill(theHisto->GetRMS());
	if(theHisto->GetBinContent(6)!=0) ratio = float(noGoodHits)/float(theHisto->GetBinContent(6));
	std::cout<<nameRoll<<" mean="<<theHisto->GetMean()<<" rms="<<theHisto->GetRMS()<<" integral="<<theHisto->Integral()<<" noGoodHits="<<noGoodHits<<std::endl;
	if(rpcId.region()==0) {BXRMSBarrel->Fill(theHisto->GetMean(),theHisto->GetRMS()); ratioHistoBarrel->Fill(ratio);}
	else if(rpcId.region()==-1){BXRMSEndCapN->Fill(theHisto->GetMean(),theHisto->GetRMS()); ratioHistoEndCapN->Fill(ratio);}
	else if(rpcId.region()==1){BXRMSEndCapP->Fill(theHisto->GetMean(),theHisto->GetRMS());ratioHistoEndCapP->Fill(ratio);}
	if(theHisto->Integral()<minIntegral) std::cout<<"NotEnoughMuonHits_for "<<nameRoll<<std::endl;
	if(ratio>synchth) std::cout<<"S "<<nameRoll<<" ratio="<<ratio<<std::endl;
	if(ratio>synchth  && theHisto->Integral() >= minIntegral) std::cout<<"SI "<<nameRoll<<" ratio"<<ratio<<" integral="<<theHisto->Integral()<<std::endl;
	if(ratio>synchth  && theHisto->Integral() >= minIntegral && fabs(theHisto->GetMean()) >= minMean)  std::cout<<"SIM "<<nameRoll<<" ratio="<<ratio<<" integral="<<theHisto->Integral()<<" mean="<<theHisto->GetMean()<<std::endl;
      }
    }
  }
}

void MuonRPCMonitor2::endRun(const edm::Run& r, const edm::EventSetup& iSetup){
  theFileOut->cd();
  BXRMSBarrel->SetFillColor(1);
  BXRMSEndCapP->SetFillColor(1);
  BXRMSEndCapN->SetFillColor(1);
  ratioHistoBarrel->SetFillColor(1);   
  ratioHistoEndCapP->SetFillColor(1);
  ratioHistoEndCapN->SetFillColor(1);
  Integrals->SetFillColor(1);

  BXRMSBarrel->Write();
  BXRMSEndCapP->Write();
  BXRMSEndCapN->Write();
  ratioHistoBarrel->Write();   
  ratioHistoEndCapP->Write();
  ratioHistoEndCapN->Write();
  Integrals->Write();
  Means->Write();
  RealMeans->Write();
  RMSs->Write();  
  TCanvas * Ca1;
  Ca1 = new TCanvas("Ca1","Synch",800,600);
  
  Means->SetFillColor(1);
  Means->Draw();
  RealMeans->SetFillColor(5);
  RealMeans->Draw("same");
  Ca1->SetLogy();
  Ca1->SaveAs("Means.png");
  Ca1->Write();
  theFileOut->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonRPCMonitor2);
