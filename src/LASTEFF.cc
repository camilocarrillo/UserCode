// -*- C++ -*-
//
// Package:    LASTEFF
// Class:      LASTEFF
// 
/**\class LASTEFF LASTEFF.cc LASTEFF/LASTEFF/src/LASTEFF.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/45
//         Created:  Tue May 13 12:23:34 CEST 2008
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include<string>
#include<fstream>

//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TTree.h"

//
// class decleration
//

class TFile;

class LASTEFF : public edm::EDAnalyzer {
   public:
      explicit LASTEFF(const edm::ParameterSet&);
      ~LASTEFF();
  
      TFile * theFile;
      TFile * theFileout;

  TH1F * histoRPC;
  TH1F * histoDT;
  TH1F * histoRPC_2D;
  TH1F * histoDT_2D;
  TH1F * histoeffIdRPC_DT_2D;
  TH1F * histoeffIdRPC_DT;
  


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string file;
      std::string fileOut;
      std::ofstream rpcInfo;
      std::ofstream rpcNames;
      std::ofstream rollsWithData;
      std::ofstream rollsWithOutData;
      std::ofstream rollsBarrel;
      std::ofstream rollsEndCap;
      std::ofstream rollsPointedForASegment;
      std::ofstream rollsNotPointedForASegment;
  
      
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
LASTEFF::LASTEFF(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  file=iConfig.getUntrackedParameter<std::string>("fileName");
  fileOut=iConfig.getUntrackedParameter<std::string>("fileOut");
  

}


LASTEFF::~LASTEFF()
{}


void 
LASTEFF::beginJob(const edm::EventSetup&)
{
  theFile = new TFile(file.c_str());
  theFileout = new TFile(fileOut.c_str(), "RECREATE");
  rpcInfo.open("RPCInfo.txt");
  rpcNames.open("RPCNames.txt");
  rollsWithOutData.open("rollsWithOutData.txt");
  rollsWithData.open("rollsWithData.txt");
  rollsBarrel.open("rollsBarrel.txt");
  rollsEndCap.open("rollsEndCap.txt");
  rollsPointedForASegment.open("rollsPointedForASegment.txt");
  rollsNotPointedForASegment.open("rollsNotPointedForASegment.txt");
}


void
LASTEFF::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  bool first=false;
  std::cout <<"\t Getting the RPC Geometry"<<std::endl;
  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  int CanvaSizeX = 800;
  int CanvaSizeY = 600;

  TCanvas * Ca1;
  
  Ca1 = new TCanvas("Ca1","EfficiencyW0",CanvaSizeX,CanvaSizeY);

  
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if( dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);
	
	
	rpcInfo<<rpcId<<"\t"<<rpcsrv.name()<<"\t No Strips="<<(*r)->nstrips()<<std::endl;
	rpcNames<<rpcsrv.name()<<std::endl;

	if(rpcId.region()==0){

	  rollsBarrel<<rpcsrv.name()<<std::endl;
	  
	  char detUnitLabel[128];

	  char meIdRPC [128];
	  char meIdDT [128];
	  
	  char meIdRPC_2D [128];
	  char meIdDT_2D [128];
	
	  char effIdRPC_DT [128];
	  char effIdRPC_DT_2D [128];

	  char namefile1D [128];
	  char namefile2D [128];

	  std::string regionName;
	  std::string ringType;
	  char  folder[120];

	  if(rpcId.region()==0) {
	    regionName="Barrel";
	    ringType="Wheel";
	  }
	  else{
	    ringType="Disk";
	    if(rpcId.region() == -1) regionName="Endcap-";
	    if(rpcId.region() ==  1) regionName="Endcap+";
	  }
	
	  sprintf(folder,"DQMData/RPC/MuonSegEff/%s/%s_%d/station_%d/sector_%d",
		  regionName.c_str(),ringType.c_str(),rpcId.ring(),rpcId.station(),rpcId.sector());
	  sprintf(detUnitLabel ,"%s",rpcsrv.name().c_str());
	
	  sprintf(meIdRPC,"%s/RPCDataOccupancyFromDT_%s",folder,detUnitLabel);
	  sprintf(meIdRPC_2D,"%s/RPCDataOccupancy2DFromDT_%s",folder,detUnitLabel);
	
	  sprintf(meIdDT,"%s/ExpectedOccupancyFromDT_%s",folder,detUnitLabel);
	  sprintf(meIdDT_2D,"%s/ExpectedOccupancy2DFromDT_%s",folder,detUnitLabel);

	  sprintf(effIdRPC_DT,"%s/EfficienyFromDTExtrapolation_%s",folder,detUnitLabel);
	  sprintf(effIdRPC_DT_2D,"%s/EfficienyFromDT2DExtrapolation_%s",folder,detUnitLabel);

	  std::cout<<folder<<std::endl;
	  
	  histoRPC= (TH1F*)theFile->Get(meIdRPC);
	  histoDT= (TH1F*)theFile->Get(meIdDT);
	  histoRPC_2D= (TH1F*)theFile->Get(meIdRPC_2D);
	  histoDT_2D= (TH1F*)theFile->Get(meIdDT_2D);
	  histoeffIdRPC_DT_2D= (TH1F*)theFile->Get(effIdRPC_DT_2D);
	  histoeffIdRPC_DT = (TH1F*)theFile->Get(effIdRPC_DT);

	  std::cout<<"Before If..."<<std::endl;

	  if(histoRPC && histoDT && histoRPC_2D && histoDT_2D && histoeffIdRPC_DT_2D && histoeffIdRPC_DT){
	    
	    std::cout<<"No empty Histogram"<<std::endl;
	    
	    bool somenthing1D = false;
	    
  	    for(unsigned int i=1;i<=100;++i){
	      if(histoDT->GetBinContent(i) != 0){
		float eff = histoRPC->GetBinContent(i)/histoDT->GetBinContent(i);
		float erreff = sqrt(eff*(1-eff)/histoDT->GetBinContent(i));
		histoeffIdRPC_DT->SetBinContent(i,eff*100.);
		histoeffIdRPC_DT->SetBinError(i,erreff*100.);
		somenthing1D = true;
		std::cout<<"Bin Content"<<histoDT->GetBinContent(i)<<std::endl;
	      }
	    }
	    
	    bool somenthing2D = false;

	    for(unsigned int i=1;i<=100;++i){
	      for(unsigned int j=1;j<=200;++j){
		if(histoDT_2D->GetBinContent(i,j) != 0){
		  float eff = histoRPC_2D->GetBinContent(i,j)/histoDT_2D->GetBinContent(i,j);
		  float erreff = sqrt(eff*(1-eff)/histoDT_2D->GetBinContent(i,j));
		  histoeffIdRPC_DT_2D->SetBinContent(i,j,eff*100.);
		  histoeffIdRPC_DT_2D->SetBinError(i,j,erreff*100.);
		  somenthing2D = true;
		}
	      }
	    }
	    
	    if(first){
	      std::cout<<"cd outputfile folder just first time"<<std::endl;
	      theFileout->cd();
	      first=false;
	    }
	    
	    if(somenthing1D){
	      histoRPC->Write();
	      histoDT->Write();
	      histoeffIdRPC_DT->Write();
	      histoeffIdRPC_DT->LabelsDeflate();
	      rollsPointedForASegment<<rpcsrv.name()<<std::endl;
	      if(histoeffIdRPC_DT->GetRMS()!=0){
		histoeffIdRPC_DT->Draw();
		sprintf(namefile1D,"results/Efficiency/profile.%s.png",detUnitLabel);
		Ca1->SaveAs(namefile1D);
		rollsWithData<<rpcsrv.name()<<std::endl;
	      }else{
	      rollsWithOutData<<rpcsrv.name()<<std::endl;
	      }
	      Ca1->Clear();
	    }else{
	      rollsNotPointedForASegment<<rpcsrv.name()<<std::endl;
	    }
	    
	    if(somenthing2D){
	      histoRPC_2D->Write();
	      histoDT_2D->Write();
	      histoeffIdRPC_DT_2D->Write();
	      if(histoeffIdRPC_DT_2D->GetRMS()!=0){
		histoeffIdRPC_DT_2D->Draw();
		sprintf(namefile2D,"results/Efficiency/profile2D.%s.png",detUnitLabel);
		Ca1->SaveAs(namefile2D);
	      }
	      Ca1->Clear();
	    }
	  }
	}else{
	  rollsEndCap<<rpcsrv.name()<<std::endl;
	}
      }
    }
  }
  
  Ca1->Close();
  theFileout->Close();
  theFile->Close();
  rollsWithOutData.close();
  rollsWithData.close();
  rollsBarrel.close();
  rollsEndCap.close();
  rpcInfo.close();
  
}


// ------------ method called once each job just after ending the event loop  ------------
void 
LASTEFF::endJob(){
    
}

//define this as a plug-in
DEFINE_FWK_MODULE(LASTEFF);
