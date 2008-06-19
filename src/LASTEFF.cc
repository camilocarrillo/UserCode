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
#include "TGaxis.h"

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
  TH1F * BXDistribution;

  TH1F * EffGlobWm2;
  TH1F * EffGlobWm1;
  TH1F * EffGlobW0;
  TH1F * EffGlobW1;
  TH1F * EffGlobW2;

  TH1F * EffGlobWm2far;
  TH1F * EffGlobWm1far;
  TH1F * EffGlobW0far;
  TH1F * EffGlobW1far;
  TH1F * EffGlobW2far;

  TH1F * BXGlobWm2;
  TH1F * BXGlobWm1;
  TH1F * BXGlobW0;
  TH1F * BXGlobW1;
  TH1F * BXGlobW2;
  
  TH1F * BXGlobWm2far;
  TH1F * BXGlobWm1far;
  TH1F * BXGlobW0far;
  TH1F * BXGlobW1far;
  TH1F * BXGlobW2far;

  TH1F * MaskedGlobWm2;
  TH1F * MaskedGlobWm1;
  TH1F * MaskedGlobW0;
  TH1F * MaskedGlobW1;
  TH1F * MaskedGlobW2;
  
  TH1F * MaskedGlobWm2far;
  TH1F * MaskedGlobWm1far;
  TH1F * MaskedGlobW0far;
  TH1F * MaskedGlobW1far;
  TH1F * MaskedGlobW2far;

  TGaxis * bxAxis;

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
};


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
  TCanvas * Ca2;
  
  Ca1 = new TCanvas("Ca1","Efficiency",CanvaSizeX,CanvaSizeY);
  Ca2 = new TCanvas("Ca2","Global Efficiency",1200,CanvaSizeY);
  
  EffGlobWm2= new TH1F("GlobEfficiencyWheel_-2near"," Efficiency Near Wheel -2 ",205,0.5,205.5);
  EffGlobWm1= new TH1F("GlobEfficiencyWheel_-1near"," Efficiency Near Wheel -1",205,0.5,205.5);
  EffGlobW0 = new TH1F("GlobEfficiencyWheel_0near"," Efficiency Near Wheel 0",205,0.5,205.5);
  EffGlobW1 = new TH1F("GlobEfficiencyWheel_1near"," Efficiency Near Wheel 1",205,0.5,205.5);
  EffGlobW2 = new TH1F("GlobEfficiencyWheel_2near"," Efficiency Near Wheel 2",205,0.5,205.5);

  EffGlobWm2far=new TH1F("GlobEfficiencyWheel_-2far"," Efficiency Far Wheel -2",205,0.5,205.5);
  EffGlobWm1far=new TH1F("GlobEfficiencyWheel_-1far"," Efficiency Far Wheel -1",205,0.5,205.5);
  EffGlobW0far =new TH1F("GlobEfficiencyWheel_0far"," Efficiency Far Wheel 0",205,0.5,205.5);
  EffGlobW1far =new TH1F("GlobEfficiencyWheel_1far"," Efficiency Far Wheel 1",205,0.5,205.5);
  EffGlobW2far =new TH1F("GlobEfficiencyWheel_2far"," Efficiency Far Wheel 2",205,0.5,205.5);

  BXGlobWm2= new TH1F("GlobBXWheel_-2near"," BX Near Wheel -2",205,0.5,205.5);
  BXGlobWm1= new TH1F("GlobBXWheel_-1near"," BX Near Wheel -1",205,0.5,205.5);
  BXGlobW0 = new TH1F("GlobBXWheel_0near"," BX Near Wheel 0",205,0.5,205.5);
  BXGlobW1 = new TH1F("GlobBXWheel_1near"," BX Near Wheel 1",205,0.5,205.5);
  BXGlobW2 = new TH1F("GlobBXWheel_2near"," BX Near Wheel 2",205,0.5,205.5);

  BXGlobWm2far= new TH1F("GlobBXWheel_-2far"," BX Far Wheel -2",205,0.5,205.5);
  BXGlobWm1far= new TH1F("GlobBXWheel_-1far"," BX Far Wheel -1",205,0.5,205.5);
  BXGlobW0far = new TH1F("GlobBXWheel_0far"," BX Far Wheel 0",205,0.5,205.5);
  BXGlobW1far = new TH1F("GlobBXWheel_1far"," BX Far Wheel 1",205,0.5,205.5);
  BXGlobW2far = new TH1F("GlobBXWheel_2far"," BX Far Wheel 2",205,0.5,205.5);

  MaskedGlobWm2= new TH1F("GlobMaskedWheel_-2near"," Masked Near Wheel -2",205,0.5,205.5);
  MaskedGlobWm1= new TH1F("GlobMaskedWheel_-1near"," Masked Near Wheel -1",205,0.5,205.5);
  MaskedGlobW0 = new TH1F("GlobMaskedWheel_0near"," Masked Near Wheel 0",205,0.5,205.5);
  MaskedGlobW1 = new TH1F("GlobMaskedWheel_1near"," Masked Near Wheel 1",205,0.5,205.5);
  MaskedGlobW2 = new TH1F("GlobMaskedWheel_2near"," Masked Near Wheel 2",205,0.5,205.5);

  MaskedGlobWm2far= new TH1F("GlobMaskedWheel_-2far"," Masked Far Wheel -2",205,0.5,205.5);
  MaskedGlobWm1far= new TH1F("GlobMaskedWheel_-1far"," Masked Far Wheel -1",205,0.5,205.5);
  MaskedGlobW0far = new TH1F("GlobMaskedWheel_0far"," Masked Far Wheel 0",205,0.5,205.5);
  MaskedGlobW1far = new TH1F("GlobMaskedWheel_1far"," Masked Far Wheel 1",205,0.5,205.5);
  MaskedGlobW2far = new TH1F("GlobMaskedWheel_2far"," Masked Far Wheel 2",205,0.5,205.5);

  int indexWheel[5];
  for(int j=0;j<5;j++){
    indexWheel[j]=1;
  }
  
  int indexWheelf[5];
  for(int j=0;j<5;j++){
    indexWheelf[j]=1;
  }

  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if( dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);
		
	rpcInfo<<rpcId<<"\t"<<rpcsrv.name()<<"\t No Strips="<<(*r)->nstrips()<<std::endl;
	rpcNames<<rpcsrv.name()<<std::endl;

	int NumberMasked=0;
	
	int sector = rpcId.sector();
	
  	
	if(rpcId.region()==0){
	  
	  rollsBarrel<<rpcsrv.name()<<std::endl;
	  
	  char detUnitLabel[128];

	  char meIdRPC [128];
	  char meIdDT [128];
	  
	  char meIdRPC_2D [128];
	  char meIdDT_2D [128];
	
	  char effIdRPC_DT [128];
	  char effIdRPC_DT_2D [128];
	  
	  char bxDistroId [128];
	  char bxFileName [128];

	  char namefile1D [128];
	  char namefile2D [128];
	  
	  std::string regionName;
	  std::string ringType;
	  char  folder[120];
	  
	  
	  if(rpcId.region()==0){
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
	  
	  sprintf(bxDistroId,"%s/BXDistribution_%s",folder,detUnitLabel);
	  
	  std::cout<<folder<<std::endl;
	  
	  histoRPC= (TH1F*)theFile->Get(meIdRPC);
	  histoDT= (TH1F*)theFile->Get(meIdDT);
	  histoRPC_2D= (TH1F*)theFile->Get(meIdRPC_2D);
	  histoDT_2D= (TH1F*)theFile->Get(meIdDT_2D);
	  histoeffIdRPC_DT_2D= (TH1F*)theFile->Get(effIdRPC_DT_2D);
	  histoeffIdRPC_DT = (TH1F*)theFile->Get(effIdRPC_DT);
	  BXDistribution = (TH1F*)theFile->Get(bxDistroId);
	  
	  std::cout<<"Before If..."<<std::endl;
	  
	  if(histoRPC && histoDT && histoRPC_2D && histoDT_2D && histoeffIdRPC_DT_2D && histoeffIdRPC_DT && BXDistribution){
	    
	    std::cout<<"No empty Histogram"<<std::endl;
	    
	    bool somenthing1D = false;
	    
  	    for(unsigned int i=1;i<=int((*r)->nstrips());++i){
	      if(histoDT->GetBinContent(i) != 0){
		float eff = histoRPC->GetBinContent(i)/histoDT->GetBinContent(i);
		float erreff = sqrt(eff*(1-eff)/histoDT->GetBinContent(i));
		histoeffIdRPC_DT->SetBinContent(i,eff*100.);
		histoeffIdRPC_DT->SetBinError(i,erreff*100.);
		somenthing1D = true;
		std::cout<<"Bin Content"<<histoDT->GetBinContent(i)<<std::endl;
	      }
	      if(histoRPC->GetBinContent(i)==0) NumberMasked++;
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
	    
	    if(BXDistribution->Integral()!=0){
	      sprintf(bxFileName,"results/mydqm/bxDistribution.%s.png",detUnitLabel);
	      BXDistribution->Draw("");
	      Ca1->SaveAs(bxFileName);
	      Ca1->Clear();
	    }
	    
	    
	    //Global Efficiency per Wheel
	    
	    int Ring = rpcId.ring();
	    
	    float ef =0;
	    float er =0;
	  
	    double p=histoDT->Integral();
	    double o=histoRPC->Integral();
	    
	    if(p!=0){
	      ef = float(o)/float(p); 
	      er = sqrt(ef*(1.-ef)/float(p));
	    }
	    
	    ef=ef*100;
	    er=er*100;
	    
	    char cam[128];	
	    sprintf(cam,"%s",rpcsrv.name().c_str());
	    TString camera = (TString)cam;
	    
	    std::cout<<"Integrals for "<<camera<<" is RPC="<<o<<" DT="<<p<<std::endl;

	    float stripsratio = (float(NumberMasked)/float((*r)->nstrips()))*100.;
	    
	    std::cout<<"Strips Ratio for"<<camera<<" is "<<stripsratio<<std::endl;

	    if(sector==1||sector==2||sector==3||sector==10||sector==11||sector==12){
	      if(Ring==-2){
		indexWheel[0]++;  
		EffGlobWm2->SetBinContent(indexWheel[0],ef);  
		EffGlobWm2->SetBinError(indexWheel[0],er);  
		EffGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera);

		BXGlobWm2->SetBinContent(indexWheel[0],50.+BXDistribution->GetMean()*10);  
		BXGlobWm2->SetBinError(indexWheel[0],BXDistribution->GetRMS()*10);  
		//BXGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera);
	      
		MaskedGlobWm2->SetBinContent(indexWheel[0],stripsratio);  
		//MaskedGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera);
	      }
	    
	      if(Ring==-1){
		indexWheel[1]++;  
		EffGlobWm1->SetBinContent(indexWheel[1],ef);  
		EffGlobWm1->SetBinError(indexWheel[1],er);  
		EffGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera);  
	      
		BXGlobWm1->SetBinContent(indexWheel[1],50.+BXDistribution->GetMean()*10);  
		BXGlobWm1->SetBinError(indexWheel[1],BXDistribution->GetRMS()*10);  
		//BXGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera);
	      
		MaskedGlobWm1->SetBinContent(indexWheel[1],stripsratio);  
		//MaskedGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera);
	      }
	    
	      if(Ring==0){
		indexWheel[2]++;  
		EffGlobW0->SetBinContent(indexWheel[2],ef);  
		EffGlobW0->SetBinError(indexWheel[2],er);  
		EffGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera);  
	      
		BXGlobW0->SetBinContent(indexWheel[2],50.+BXDistribution->GetMean()*10);  
		BXGlobW0->SetBinError(indexWheel[2],BXDistribution->GetRMS()*10);  
		//BXGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera);

		MaskedGlobW0->SetBinContent(indexWheel[2],stripsratio);  
		//MaskedGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera);
	      }
	
	      if(Ring==1){
		indexWheel[3]++;  
		EffGlobW1->SetBinContent(indexWheel[3],ef);  
		EffGlobW1->SetBinError(indexWheel[3],er);  
		EffGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera);  
	      
		BXGlobW1->SetBinContent(indexWheel[3],50.+BXDistribution->GetMean()*10);  
		BXGlobW1->SetBinError(indexWheel[3],BXDistribution->GetRMS()*10);  
		//BXGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera);

		MaskedGlobW1->SetBinContent(indexWheel[3],stripsratio);  
		//MaskedGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera);
	      }
	    
	      if(Ring==2){
		indexWheel[4]++;
		EffGlobW2->SetBinContent(indexWheel[4],ef);
		EffGlobW2->SetBinError(indexWheel[4],er);
		EffGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera);

		BXGlobW2->SetBinContent(indexWheel[4],50.+BXDistribution->GetMean()*10);  
		BXGlobW2->SetBinError(indexWheel[4],BXDistribution->GetRMS()*10);  
		//BXGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera);
	      
		MaskedGlobW2->SetBinContent(indexWheel[4],stripsratio);  
		//MaskedGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera);
	      }
	    }else{
	      
	      if(Ring==-2){
		indexWheelf[0]++;  
		EffGlobWm2far->SetBinContent(indexWheelf[0],ef);  
		EffGlobWm2far->SetBinError(indexWheelf[0],er);  
		EffGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera);

		BXGlobWm2far->SetBinContent(indexWheelf[0],50.+BXDistribution->GetMean()*10);  
		BXGlobWm2far->SetBinError(indexWheelf[0],BXDistribution->GetRMS()*10);  
		//BXGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera);
	      
		MaskedGlobWm2far->SetBinContent(indexWheelf[0],stripsratio);
		//MaskedGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera);
	      }
	    
	      if(Ring==-1){
		indexWheelf[1]++;  
		EffGlobWm1far->SetBinContent(indexWheelf[1],ef);  
		EffGlobWm1far->SetBinError(indexWheelf[1],er);  
		EffGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera);  
	      
		BXGlobWm1far->SetBinContent(indexWheelf[1],50.+BXDistribution->GetMean()*10);  
		BXGlobWm1far->SetBinError(indexWheelf[1],BXDistribution->GetRMS()*10);  
		//BXGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera);
	      
		MaskedGlobWm1far->SetBinContent(indexWheelf[1],stripsratio);
		//MaskedGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera);
	      }
	    
	      if(Ring==0){
		indexWheelf[2]++;  
		EffGlobW0far->SetBinContent(indexWheelf[2],ef);  
		EffGlobW0far->SetBinError(indexWheelf[2],er);  
		EffGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera);  
	      
		BXGlobW0far->SetBinContent(indexWheelf[2],50.+BXDistribution->GetMean()*10);  
		BXGlobW0far->SetBinError(indexWheelf[2],BXDistribution->GetRMS()*10);  
		//BXGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera);

		MaskedGlobW0far->SetBinContent(indexWheelf[2],stripsratio);
		//MaskedGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera);
	      }
	
	      if(Ring==1){
		indexWheelf[3]++;  
		EffGlobW1far->SetBinContent(indexWheelf[3],ef);  
		EffGlobW1far->SetBinError(indexWheelf[3],er);  
		EffGlobW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera);  
	      
		BXGlobW1far->SetBinContent(indexWheelf[3],50.+BXDistribution->GetMean()*10);  
		BXGlobW1far->SetBinError(indexWheelf[3],BXDistribution->GetRMS()*10);  
		//BXGlobW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera);

		MaskedGlobW1far->SetBinContent(indexWheelf[3],stripsratio);
		//MaskedGlobW1->GetXaxis()->SetBinLabel(indexWheelf[3],camera);
	      }
	    
	      if(Ring==2){
		indexWheelf[4]++;
		EffGlobW2far->SetBinContent(indexWheelf[4],ef);
		EffGlobW2far->SetBinError(indexWheelf[4],er);
		EffGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera);

		BXGlobW2far->SetBinContent(indexWheelf[4],50.+BXDistribution->GetMean()*10);  
		BXGlobW2far->SetBinError(indexWheelf[4],BXDistribution->GetRMS()*10);  
		//BXGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera);
	      
		MaskedGlobW2far->SetBinContent(indexWheelf[4],stripsratio);
		//MaskedGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera);
	      }
	    }
	  }
	}else{
	  rollsEndCap<<rpcsrv.name()<<std::endl;
	}
      }
    }
  }
 
  EffGlobWm2->GetXaxis()->LabelsOption("v");
  EffGlobWm1->GetXaxis()->LabelsOption("v");
  EffGlobW0->GetXaxis()->LabelsOption("v");
  EffGlobW1->GetXaxis()->LabelsOption("v");
  EffGlobW2->GetXaxis()->LabelsOption("v");
  
  BXGlobWm2->GetXaxis()->LabelsOption("v");
  BXGlobWm1->GetXaxis()->LabelsOption("v");
  BXGlobW0->GetXaxis()->LabelsOption("v");
  BXGlobW1->GetXaxis()->LabelsOption("v");
  BXGlobW2->GetXaxis()->LabelsOption("v");

  MaskedGlobWm2->GetXaxis()->LabelsOption("v");
  MaskedGlobWm1->GetXaxis()->LabelsOption("v");
  MaskedGlobW0->GetXaxis()->LabelsOption("v");
  MaskedGlobW1->GetXaxis()->LabelsOption("v");
  MaskedGlobW2->GetXaxis()->LabelsOption("v");


  EffGlobWm2far->GetXaxis()->LabelsOption("v");
  EffGlobWm1far->GetXaxis()->LabelsOption("v");
  EffGlobW0far->GetXaxis()->LabelsOption("v");
  EffGlobW1far->GetXaxis()->LabelsOption("v");
  EffGlobW2far->GetXaxis()->LabelsOption("v");
  
  BXGlobWm2far->GetXaxis()->LabelsOption("v");
  BXGlobWm1far->GetXaxis()->LabelsOption("v");
  BXGlobW0far->GetXaxis()->LabelsOption("v");
  BXGlobW1far->GetXaxis()->LabelsOption("v");
  BXGlobW2far->GetXaxis()->LabelsOption("v");

  MaskedGlobWm2far->GetXaxis()->LabelsOption("v");
  MaskedGlobWm1far->GetXaxis()->LabelsOption("v");
  MaskedGlobW0far->GetXaxis()->LabelsOption("v");
  MaskedGlobW1far->GetXaxis()->LabelsOption("v");
  MaskedGlobW2far->GetXaxis()->LabelsOption("v");

  Ca2 = new TCanvas("Ca2","Global Efficiency",1200,600);
  
  Ca2->Range(-10,-1,10,1);

  TGaxis * bxAxis = new TGaxis(8,-0.8,8,0.8,-5,5,50510,"+L");
  bxAxis->SetLabelColor(9);
  bxAxis->SetName("bxAxis");
  bxAxis->Draw();

  std::cout<<"Efficiency Images"<<std::endl;

  Ca2->SetBottomMargin(0.4);

  EffGlobWm2->LabelsDeflate();
  EffGlobWm2->Draw();
  EffGlobWm2->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobWm2->LabelsDeflate();
  BXGlobWm2->SetMarkerColor(9);
  BXGlobWm2->SetLineColor(9);
  BXGlobWm2->Draw("same");

  MaskedGlobWm2->LabelsDeflate();
  MaskedGlobWm2->SetMarkerColor(2);
  MaskedGlobWm2->SetLineColor(2);
  MaskedGlobWm2->Draw("same");
  
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm2near.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm2near.root");
  Ca2->Clear();

  EffGlobWm2far->LabelsDeflate();
  EffGlobWm2far->Draw();
  EffGlobWm2far->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobWm2far->LabelsDeflate();
  BXGlobWm2far->SetMarkerColor(9);
  BXGlobWm2far->SetLineColor(9);
  BXGlobWm2far->Draw("same");

  MaskedGlobWm2far->LabelsDeflate();
  MaskedGlobWm2far->SetMarkerColor(2);
  MaskedGlobWm2far->SetLineColor(2);
  MaskedGlobWm2far->Draw("same");
  
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm2far.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm2far.root");
  Ca2->Clear();

  EffGlobWm1->LabelsDeflate();
  EffGlobWm1->Draw();
  EffGlobWm1->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobWm1->LabelsDeflate();
  BXGlobWm1->SetMarkerColor(9);
  BXGlobWm1->SetLineColor(9);
  BXGlobWm1->Draw("same");

  MaskedGlobWm1->LabelsDeflate();
  MaskedGlobWm1->SetMarkerColor(2);
  MaskedGlobWm1->SetLineColor(2);
  MaskedGlobWm1->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalWm1near.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm1near.root");
  Ca2->Clear();

  EffGlobWm1far->LabelsDeflate();
  EffGlobWm1far->Draw();
  EffGlobWm1far->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobWm1far->LabelsDeflate();
  BXGlobWm1far->SetMarkerColor(9);
  BXGlobWm1far->SetLineColor(9);
  BXGlobWm1far->Draw("same");

  MaskedGlobWm1far->LabelsDeflate();
  MaskedGlobWm1far->SetMarkerColor(2);
  MaskedGlobWm1far->SetLineColor(2);
  MaskedGlobWm1far->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalWm1far.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalWm1far.root");
  Ca2->Clear();

  EffGlobW0->LabelsDeflate();
  EffGlobW0->Draw();
  EffGlobW0->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW0->LabelsDeflate();
  BXGlobW0->SetMarkerColor(9);
  BXGlobW0->SetLineColor(9);
  BXGlobW0->Draw("same");

  MaskedGlobW0->LabelsDeflate();
  MaskedGlobW0->SetMarkerColor(2);
  MaskedGlobW0->SetLineColor(2);
  MaskedGlobW0->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalW0near.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW0near.root");
  Ca2->Clear();

  EffGlobW0far->LabelsDeflate();
  EffGlobW0far->Draw();
  EffGlobW0far->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW0far->LabelsDeflate();
  BXGlobW0far->SetMarkerColor(9);
  BXGlobW0far->SetLineColor(9);
  BXGlobW0far->Draw("same");

  MaskedGlobW0far->LabelsDeflate();
  MaskedGlobW0far->SetMarkerColor(2);
  MaskedGlobW0far->SetLineColor(2);
  MaskedGlobW0far->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalW0far.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW0far.root");
  Ca2->Clear();

  EffGlobW1->LabelsDeflate();
  EffGlobW1->Draw();
  EffGlobW1->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW1->LabelsDeflate();
  BXGlobW1->SetMarkerColor(9);
  BXGlobW1->SetLineColor(9);
  BXGlobW1->Draw("same");

  MaskedGlobW1->LabelsDeflate();
  MaskedGlobW1->SetMarkerColor(2);
  MaskedGlobW1->SetLineColor(2);
  MaskedGlobW1->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalW1near.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW1near.root");
  Ca2->Clear();

  EffGlobW1far->LabelsDeflate();
  EffGlobW1far->Draw();
  EffGlobW1far->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW1far->LabelsDeflate();
  BXGlobW1far->SetMarkerColor(9);
  BXGlobW1far->SetLineColor(9);
  BXGlobW1far->Draw("same");

  MaskedGlobW1far->LabelsDeflate();
  MaskedGlobW1far->SetMarkerColor(2);
  MaskedGlobW1far->SetLineColor(2);
  MaskedGlobW1far->Draw("same");

  Ca2->SaveAs("GlobalEfficiencyFromLocalW1far.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW1far.root");
  Ca2->Clear();

  EffGlobW2->LabelsDeflate();
  EffGlobW2->Draw();
  EffGlobW2->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW2->LabelsDeflate();
  BXGlobW2->SetMarkerColor(9);
  BXGlobW2->SetLineColor(9);
  BXGlobW2->Draw("same");

  MaskedGlobW2->LabelsDeflate();
  MaskedGlobW2->SetMarkerColor(2);
  MaskedGlobW2->SetLineColor(2);
  MaskedGlobW2->Draw("same");
  
  Ca2->SaveAs("GlobalEfficiencyFromLocalW2near.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW2near.root");
  Ca2->Clear();
  
  EffGlobW2far->LabelsDeflate();
  EffGlobW2far->Draw();
  EffGlobW2far->GetYaxis()->SetTitle("Efficiency %");
  
  BXGlobW2far->LabelsDeflate();
  BXGlobW2far->SetMarkerColor(9);
  BXGlobW2far->SetLineColor(9);
  BXGlobW2far->Draw("same");

  MaskedGlobW2far->LabelsDeflate();
  MaskedGlobW2far->SetMarkerColor(2);
  MaskedGlobW2far->SetLineColor(2);
  MaskedGlobW2far->Draw("same");
  
  Ca2->SaveAs("GlobalEfficiencyFromLocalW2far.png");
  Ca2->SaveAs("GlobalEfficiencyFromLocalW2far.root");
  Ca2->Clear();

  theFileout->cd();

  EffGlobWm2->Write();
  EffGlobWm1->Write();
  EffGlobW0->Write();
  EffGlobW1->Write();
  EffGlobW2->Write();

  EffGlobWm2far->Write();
  EffGlobWm1far->Write();
  EffGlobW0far->Write();
  EffGlobW1far->Write();
  EffGlobW2far->Write();

  BXGlobWm2->Write();
  BXGlobWm1->Write();
  BXGlobW0->Write();
  BXGlobW1->Write();
  BXGlobW2->Write();

  BXGlobWm2far->Write();
  BXGlobWm1far->Write();
  BXGlobW0far->Write();
  BXGlobW1far->Write();
  BXGlobW2far->Write();

  MaskedGlobWm2->Write();
  MaskedGlobWm1->Write();
  MaskedGlobW0->Write();
  MaskedGlobW1->Write();
  MaskedGlobW2->Write();

  MaskedGlobWm2far->Write();
  MaskedGlobWm1far->Write();
  MaskedGlobW0far->Write();
  MaskedGlobW1far->Write();
  MaskedGlobW2far->Write();

  Ca2->Close();
  
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


/* 
	    float eff = histoeffIdRPC_DT->;
	    float err = ;
	    
	    
	    TLine *lineh = new TLine(-9.8,eff,9.8,eff);
	    lineh->Draw();	    

	    TLine *linev = new TLine(0,eff+err/2,0,eff-err/2);
	    linev->Draw();	    

*/
