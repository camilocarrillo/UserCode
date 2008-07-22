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
#include <DQMOffline/Muon/interface/RPCBookFolderStructure.h>

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
#include <TStyle.h>
#include "TText.h"
#include "TPaveText.h"
//
// class decleration
//

class TFile;

class LASTEFF : public edm::EDAnalyzer {
public:
  explicit LASTEFF(const edm::ParameterSet&);
  ~LASTEFF();
  
  TFile * theFile;
  TFile * theFileOut;

  TH1F * histoRPC;
  TH1F * histoDT;
  TH1F * histoeffIdRPC_DT;
  TH1F * BXDistribution;
  TH1F * histoRealRPC;

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

  TH1F * AverageEffWm2;
  TH1F * AverageEffWm1;
  TH1F * AverageEffW0;
  TH1F * AverageEffW1;
  TH1F * AverageEffW2;

  TH1F * AverageEffWm2far;
  TH1F * AverageEffWm1far;
  TH1F * AverageEffW0far;
  TH1F * AverageEffW1far;
  TH1F * AverageEffW2far;
  
  TH1F * NoPredictionWm2;
  TH1F * NoPredictionWm1;
  TH1F * NoPredictionW0;
  TH1F * NoPredictionW1;
  TH1F * NoPredictionW2;

  TH1F * NoPredictionWm2far;
  TH1F * NoPredictionWm1far;
  TH1F * NoPredictionW0far;
  TH1F * NoPredictionW1far;
  TH1F * NoPredictionW2far;

  TGaxis * bxAxis;

  TPaveText * pave;

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string file;
      std::string fileout;
      std::ofstream rpcInfo;
      std::ofstream rpcNames;
      std::ofstream rollsWithData;
      std::ofstream rollsWithOutData;
      std::ofstream rollsBarrel;
      std::ofstream rollsEndCap;
      std::ofstream rollsPointedForASegment;
      std::ofstream rollsNotPointedForASegment;
      std::ofstream bxMeanList;
      bool offline;
};


LASTEFF::LASTEFF(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  file=iConfig.getUntrackedParameter<std::string>("fileName");
  fileout=iConfig.getUntrackedParameter<std::string>("fileOut");  
  offline=iConfig.getUntrackedParameter<bool>("offline");
}


LASTEFF::~LASTEFF()
{}

void 
LASTEFF::beginJob(const edm::EventSetup&)
{
  theFile = new TFile(file.c_str());
  theFileOut = new TFile(fileout.c_str(), "RECREATE");
  rpcInfo.open("RPCInfo.txt");
  rpcNames.open("RPCNames.txt");
  rollsWithOutData.open("rollsWithOutData.txt");
  rollsWithData.open("rollsWithData.txt");
  rollsBarrel.open("rollsBarrel.txt");
  rollsEndCap.open("rollsEndCap.txt");
  rollsPointedForASegment.open("rollsPointedForASegment.txt");
  rollsNotPointedForASegment.open("rollsNotPointedForASegment.txt");
  bxMeanList.open("bxMeanList.txt");
}

void LASTEFF::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  //  bool first=false;
  std::cout <<"\t Getting the RPC Geometry"<<std::endl;
  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  int CanvaSizeX = 800;
  int CanvaSizeY = 600;

  TCanvas * Ca1;
  TCanvas * Ca2;
  
  Ca1 = new TCanvas("Ca1","Efficiency",CanvaSizeX,CanvaSizeY);
  Ca2 = new TCanvas("Ca2","Global Efficiency",1200,CanvaSizeY);

  EffGlobWm2= new TH1F ("GlobEfficiencyWheel_-2near","Efficiency Near Side Wheel -2",101,0.5,101.5);
  EffGlobWm2far= new TH1F ("GlobEfficiencyWheel_-2far","Efficiency Far Side Wheel -2",105,0.5,105.5);
  BXGlobWm2=  new TH1F ("GlobBXWheel_-2near","BX Near Side Wheel -2",101,0.5,101.5);
  BXGlobWm2far=  new TH1F ("GlobBXWheel_-2far","BX Far Side Wheel -2",105,0.5,105.5);
  MaskedGlobWm2=  new TH1F ("GlobMaskedWheel_-2near","Masked Near Side Wheel -2",101,0.5,101.5);
  MaskedGlobWm2far=  new TH1F ("GlobMaskedWheel_-2far","Masked Far Side Wheel -2",105,0.5,105.5);
  AverageEffWm2= new TH1F ("AverageEfficiencyWheel_-2near","Average Efficiency Near Side Wheel -2 ",101,0.5,101.5);
  AverageEffWm2far = new TH1F ("AverageEfficiencyWheel_-2far","Average Efficiency Far Side Wheel -2 ",105,0.5,105.5);
  NoPredictionWm2= new TH1F ("NoPredictionWheel_-2near","No Predictions Near Side Wheel -2 ",101,0.5,101.5);
  NoPredictionWm2far= new TH1F ("NoPredictionWheel_-2far","No Predictions Efficiency Far Side Wheel -2 ",105,0.5,105.5);
  
  EffGlobWm1=  new TH1F ("GlobEfficiencyWheel_-1near","Efficiency Near Side Wheel -1",101,0.5,101.5);
  EffGlobWm1far= new TH1F ("GlobEfficiencyWheel_-1far","Efficiency Far Side Wheel -1",105,0.5,105.5);
  BXGlobWm1=  new TH1F ("GlobBXWheel_-1near","BX Near Side Wheel -1",101,0.5,101.5);
  BXGlobWm1far=  new TH1F ("GlobBXWheel_-1far","BX Far Side Wheel -1",105,0.5,105.5);
  MaskedGlobWm1=  new TH1F ("GlobMaskedWheel_-1near","Masked Near Side Wheel -1",101,0.5,101.5);
  MaskedGlobWm1far=  new TH1F ("GlobMaskedWheel_-1far","Masked Far Side Wheel -1",105,0.5,105.5);
  AverageEffWm1= new TH1F ("AverageEfficiencyWheel_-1near","Average Efficiency Near Side Wheel -1 ",101,0.5,101.5);
  AverageEffWm1far= new TH1F ("AverageEfficiencyWheel_-1far","Average Efficiency Far Side Wheel -1 ",105,0.5,105.5);
  NoPredictionWm1= new TH1F ("NoPredictionWheel_-1near","No Predictions Near Side Wheel -1 ",101,0.5,101.5);
  NoPredictionWm1far= new TH1F ("NoPredictionWheel_-1far","No Predictions Efficiency Far Side Wheel -1 ",105,0.5,105.5);

  EffGlobW0 =  new TH1F ("GlobEfficiencyWheel_0near","Efficiency Near Side Wheel 0",101,0.5,101.5);
  EffGlobW0far = new TH1F ("GlobEfficiencyWheel_0far","Efficiency Far Side Wheel 0",105,0.5,105.5);
  BXGlobW0 =  new TH1F ("GlobBXWheel_0near","BX Near Side Wheel 0",101,0.5,101.5);
  BXGlobW0far =  new TH1F ("GlobBXWheel_0far","BX Far Side Wheel 0",105,0.5,105.5);
  MaskedGlobW0 =  new TH1F ("GlobMaskedWheel_0near","Masked Near Side Wheel 0",101,0.5,101.5);
  MaskedGlobW0far =  new TH1F ("GlobMaskedWheel_0far","Masked Far Side Wheel 0",105,0.5,105.5);
  AverageEffW0= new TH1F ("AverageEfficiencyWheel_0near","Average Efficiency Near Side Wheel 0 ",101,0.5,101.5);
  AverageEffW0far= new TH1F ("AverageEfficiencyWheel_0far","Average Efficiency Far Side Wheel 0 ",105,0.5,105.5);
  NoPredictionW0= new TH1F ("NoPredictionWheel_0near","No Predictions Near Side Wheel 0 ",101,0.5,101.5);
  NoPredictionW0far= new TH1F ("NoPredictionWheel_0far","No Predictions Efficiency Far Side Wheel 0 ",105,0.5,105.5);

  EffGlobW1 =  new TH1F ("GlobEfficiencyWheel_1near","Efficiency Near Side Wheel 1",101,0.5,101.5);
  EffGlobW1far = new TH1F ("GlobEfficiencyWheel_1far","Efficiency Far Side Wheel 1",105,0.5,105.5);  
  BXGlobW1 =  new TH1F ("GlobBXWheel_1near","BX Near Side Wheel 1",101,0.5,101.5);
  BXGlobW1far =  new TH1F ("GlobBXWheel_1far","BX Far Side Wheel 1",105,0.5,105.5);
  MaskedGlobW1 =  new TH1F ("GlobMaskedWheel_1near","Masked Near Side Wheel 1",101,0.5,101.5);
  MaskedGlobW1far =  new TH1F ("GlobMaskedWheel_1far","Masked Far Side Wheel 1",105,0.5,105.5);
  AverageEffW1= new TH1F ("AverageEfficiencyWheel_1near","Average Efficiency Near Side Wheel 1 ",101,0.5,101.5);
  AverageEffW1far= new TH1F ("AverageEfficiencyWheel_1far","Average Efficiency Far Side Wheel 1 ",105,0.5,105.5);
  NoPredictionW1= new TH1F ("NoPredictionWheel_1near","No Predictions Near Side Wheel 1 ",101,0.5,101.5);
  NoPredictionW1far= new TH1F ("NoPredictionWheel_1far","No Predictions Efficiency Far Side Wheel 1 ",105,0.5,105.5);

  EffGlobW2 =  new TH1F ("GlobEfficiencyWheel_2near","Efficiency Near Side Wheel 2",101,0.5,101.5);
  EffGlobW2far = new TH1F ("GlobEfficiencyWheel_2far","Efficiency Far Side Wheel 2",105,0.5,105.5);
  BXGlobW2 =  new TH1F ("GlobBXWheel_2near","BX Near Side Wheel 2",101,0.5,101.5);
  BXGlobW2far =  new TH1F ("GlobBXWheel_2far","BX Far Side Wheel 2",105,0.5,105.5);
  MaskedGlobW2 =  new TH1F ("GlobMaskedWheel_2near","Masked Near Side Wheel 2",101,0.5,101.5);
  MaskedGlobW2far =  new TH1F ("GlobMaskedWheel_2far","Masked Far Side Wheel 2",105,0.5,105.5);
  AverageEffW2= new TH1F ("AverageEfficiencyWheel_2near","Average Efficiency Near Side Wheel 2 ",101,0.5,101.5);
  AverageEffW2far= new TH1F ("AverageEfficiencyWheel_2far","Average Efficiency Far Side Wheel 2 ",105,0.5,105.5);
  NoPredictionW2= new TH1F ("NoPredictionWheel_2near","No Predictions Near Side Wheel 2 ",101,0.5,101.5);
  NoPredictionW2far= new TH1F ("NoPredictionWheel_2far","No Predictions Efficiency Far Side Wheel 2 ",105,0.5,105.5);
  
  int indexWheel[5];
  for(int j=0;j<5;j++){
    indexWheel[j]=0;
  }
  
  int indexWheelf[5];
  for(int j=0;j<5;j++){
    indexWheelf[j]=0;
  }
  
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if( dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);
		
	int sector = rpcId.sector();
  	
	if(rpcId.region()==0){
	  std::string detUnitLabel, meIdRPC,meIdDT, bxDistroId, meIdRealRPC  ;
	 
	  RPCBookFolderStructure *  folderStr = new RPCBookFolderStructure(); //Anna
	  std::string folder = "DQMData/RPC/MuonSegEff/" +  folderStr->folderStructure(rpcId);
		
	  meIdRPC = folder +"/RPCDataOccupancyFromDT_"+ rpcsrv.name();	
	  meIdDT =folder+"/ExpectedOccupancyFromDT_"+ rpcsrv.name();
	  bxDistroId =folder+"/BXDistribution_"+ rpcsrv.name();
	  meIdRealRPC =folder+"/RealDetectedOccupancyFromDT_"+ rpcsrv.name();  
	  
	  /*histoRPC= dbe->get(meIdRPC);
	  histoDT= dbe->get(meIdDT);
	  BXDistribution = dbe->get(bxDistroId);
	  histoRealRPC = dbe->get(meIdRealRPC);*/

	  histoRPC= (TH1F*)theFile->Get(meIdRPC.c_str());
          histoDT= (TH1F*)theFile->Get(meIdDT.c_str());
          BXDistribution = (TH1F*)theFile->Get(bxDistroId.c_str());
          histoRealRPC = (TH1F*)theFile->Get(meIdRealRPC.c_str());


	  std::cout <<rpcsrv.name()<<std::endl;

	  int NumberMasked=0;
	  int NumberWithOutPrediction=0;
	  double p = 0;
	  double o = 0;
	  float mybxhisto = 0;
	  float mybxerror = 0;
	  float ef =0;
	  float er =0;
	  float buffef = 0;
	  float buffer = 0;
	  float sumbuffef = 0;
	  float sumbuffer = 0;
	  float averageeff = 0;
	  float averageerr = 0;

	  int NumberStripsPointed = 0;
	  
	  if(histoRPC && histoDT && BXDistribution && histoRealRPC){
	    for(int i=1;i<=int((*r)->nstrips());++i){
	      if(histoRealRPC->GetBinContent(i)==0) NumberMasked++;
	      
	      if(histoDT->GetBinContent(i)!=0){
		buffef = float(histoRPC->GetBinContent(i))/float(histoDT->GetBinContent(i));
		buffer = sqrt(buffef*(1.-buffef)/float(histoDT->GetBinContent(i)));
		sumbuffef = sumbuffef + buffef;
		sumbuffer = sumbuffer + buffer*buffer;
		NumberStripsPointed++;
	      }else{
		NumberWithOutPrediction++;
	      }
	    }
	    p=histoDT->Integral();
	    o=histoRPC->Integral();

	    if(NumberStripsPointed!=0){
	      averageeff = (sumbuffef/float(NumberStripsPointed))*100.;
	      averageerr = sqrt(sumbuffer/float(NumberStripsPointed))*100.;
	    }

	    mybxhisto = 50.+BXDistribution->GetMean()*10;
	    mybxerror = BXDistribution->GetRMS()*10;
	  }
	  
	  int Ring = rpcId.ring();
	  
	  if(p!=0){
	    ef = float(o)/float(p); 
	    er = sqrt(ef*(1.-ef)/float(p));
	  }
	  
	  ef=ef*100;
	  er=er*100;
	    
	  std::string camera = rpcsrv.name().c_str();
	  
	  float stripsratio = (float(NumberMasked)/float((*r)->nstrips()))*100.;
	  float nopredictionsratio = (float(NumberWithOutPrediction)/float((*r)->nstrips()))*100.;
	  

	  //Near Side

	  if((sector==1||sector==2||sector==3||sector==10||sector==11||sector==12)){
	    if(Ring==-2){
	      indexWheel[0]++;  
	      EffGlobWm2->SetBinContent(indexWheel[0],ef);  
	      EffGlobWm2->SetBinError(indexWheel[0],er);  
	      EffGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());

	      BXGlobWm2->SetBinContent(indexWheel[0],mybxhisto);  
	      BXGlobWm2->SetBinError(indexWheel[0],mybxerror);  
	      BXGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());
	      
	      MaskedGlobWm2->SetBinContent(indexWheel[0],stripsratio);  
	      MaskedGlobWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());

	      AverageEffWm2->SetBinContent(indexWheel[0],averageeff);
	      AverageEffWm2->SetBinError(indexWheel[0],averageerr);  
	      AverageEffWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());
	      
	      NoPredictionWm2->SetBinContent(indexWheel[0],nopredictionsratio);
              NoPredictionWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());
	    }else if(Ring==-1){
	      indexWheel[1]++;  
	      EffGlobWm1->SetBinContent(indexWheel[1],ef);  
	      EffGlobWm1->SetBinError(indexWheel[1],er);  
	      EffGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera.c_str());  
	      
	      BXGlobWm1->SetBinContent(indexWheel[1],mybxhisto);  
	      BXGlobWm1->SetBinError(indexWheel[1],mybxerror);  
	      BXGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera.c_str());
	      
	      MaskedGlobWm1->SetBinContent(indexWheel[1],stripsratio);  
	      MaskedGlobWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera.c_str());

	      AverageEffWm1->SetBinContent(indexWheel[1],averageeff);
	      AverageEffWm1->SetBinError(indexWheel[1],averageerr);  
	      AverageEffWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera.c_str());
	      
	      NoPredictionWm1->SetBinContent(indexWheel[1],nopredictionsratio);
              NoPredictionWm1->GetXaxis()->SetBinLabel(indexWheel[1],camera.c_str());

	    }else if(Ring==0){
	      indexWheel[2]++;  
	      EffGlobW0->SetBinContent(indexWheel[2],ef);  
	      EffGlobW0->SetBinError(indexWheel[2],er);  
	      EffGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera.c_str());  
	      
	      BXGlobW0->SetBinContent(indexWheel[2],mybxhisto);  
	      BXGlobW0->SetBinError(indexWheel[2],mybxerror);  
	      BXGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera.c_str());

	      MaskedGlobW0->SetBinContent(indexWheel[2],stripsratio);  
	      MaskedGlobW0->GetXaxis()->SetBinLabel(indexWheel[2],camera.c_str());
	      
	      AverageEffW0->SetBinContent(indexWheel[2],averageeff);
	      AverageEffW0->SetBinError(indexWheel[2],averageerr);  
	      AverageEffW0->GetXaxis()->SetBinLabel(indexWheel[2],camera.c_str());
	      
	      NoPredictionW0->SetBinContent(indexWheel[2],nopredictionsratio);
              NoPredictionW0->GetXaxis()->SetBinLabel(indexWheel[2],camera.c_str());	      
	    }else if(Ring==1){
	      indexWheel[3]++;  
	      EffGlobW1->SetBinContent(indexWheel[3],ef);  
	      EffGlobW1->SetBinError(indexWheel[3],er);  
	      EffGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera.c_str());  
	      
	      BXGlobW1->SetBinContent(indexWheel[3],mybxhisto);  
	      BXGlobW1->SetBinError(indexWheel[3],mybxerror);  
	      BXGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera.c_str());

	      MaskedGlobW1->SetBinContent(indexWheel[3],stripsratio);  
	      MaskedGlobW1->GetXaxis()->SetBinLabel(indexWheel[3],camera.c_str());

	      AverageEffW1->SetBinContent(indexWheel[3],averageeff);
	      AverageEffW1->SetBinError(indexWheel[3],averageerr);  
	      AverageEffW1->GetXaxis()->SetBinLabel(indexWheel[3],camera.c_str());
	      
	      NoPredictionW1->SetBinContent(indexWheel[3],nopredictionsratio);
              NoPredictionW1->GetXaxis()->SetBinLabel(indexWheel[3],camera.c_str());	      
	    }else if(Ring==2){
	      indexWheel[4]++;
	      EffGlobW2->SetBinContent(indexWheel[4],ef);
	      EffGlobW2->SetBinError(indexWheel[4],er);
	      EffGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera.c_str());

	      BXGlobW2->SetBinContent(indexWheel[4],mybxhisto);  
	      BXGlobW2->SetBinError(indexWheel[4],mybxerror);  
	      BXGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera.c_str());
	      
	      MaskedGlobW2->SetBinContent(indexWheel[4],stripsratio);  
	      MaskedGlobW2->GetXaxis()->SetBinLabel(indexWheel[4],camera.c_str());

	      AverageEffW2->SetBinContent(indexWheel[4],averageeff);
	      AverageEffW2->SetBinError(indexWheel[4],averageerr);  
	      AverageEffW2->GetXaxis()->SetBinLabel(indexWheel[4],camera.c_str());
	      
	      NoPredictionW2->SetBinContent(indexWheel[4],nopredictionsratio);
              NoPredictionW2->GetXaxis()->SetBinLabel(indexWheel[4],camera.c_str());	      
	    }
	  }else{//Far Side 
	    if(Ring==-2){
	      indexWheelf[0]++;  
	      EffGlobWm2far->SetBinContent(indexWheelf[0],ef);  
	      EffGlobWm2far->SetBinError(indexWheelf[0],er);  
	      EffGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera.c_str());

	      BXGlobWm2far->SetBinContent(indexWheelf[0],mybxhisto);  
	      BXGlobWm2far->SetBinError(indexWheelf[0],mybxerror);  
	      BXGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera.c_str());
	      
	      MaskedGlobWm2far->SetBinContent(indexWheelf[0],stripsratio);
	      MaskedGlobWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera.c_str());
	      
	      AverageEffWm2far->SetBinContent(indexWheelf[0],averageeff);
              AverageEffWm2far->SetBinError(indexWheelf[0],averageerr);
              AverageEffWm2far->GetXaxis()->SetBinLabel(indexWheelf[0],camera.c_str());

              NoPredictionWm2->SetBinContent(indexWheel[0],nopredictionsratio);
              NoPredictionWm2->GetXaxis()->SetBinLabel(indexWheel[0],camera.c_str());


	    }else if(Ring==-1){
	      indexWheelf[1]++;  
	      EffGlobWm1far->SetBinContent(indexWheelf[1],ef);  
	      EffGlobWm1far->SetBinError(indexWheelf[1],er);  
	      EffGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera.c_str());  
	      
	      BXGlobWm1far->SetBinContent(indexWheelf[1],mybxhisto);  
	      BXGlobWm1far->SetBinError(indexWheelf[1],mybxerror);  
	      BXGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera.c_str());
	      
	      MaskedGlobWm1far->SetBinContent(indexWheelf[1],stripsratio);
	      MaskedGlobWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera.c_str());

	      AverageEffWm1far->SetBinContent(indexWheelf[1],averageeff);
              AverageEffWm1far->SetBinError(indexWheelf[1],averageerr);
              AverageEffWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera.c_str());

              NoPredictionWm1far->SetBinContent(indexWheelf[1],nopredictionsratio);
              NoPredictionWm1far->GetXaxis()->SetBinLabel(indexWheelf[1],camera.c_str());

	    }else  if(Ring==0){
	      indexWheelf[2]++;  
	      EffGlobW0far->SetBinContent(indexWheelf[2],ef);  
	      EffGlobW0far->SetBinError(indexWheelf[2],er);  
	      EffGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera.c_str());  
	      
	      BXGlobW0far->SetBinContent(indexWheelf[2],mybxhisto);  
	      BXGlobW0far->SetBinError(indexWheelf[2],mybxerror);  
	      BXGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera.c_str());

	      MaskedGlobW0far->SetBinContent(indexWheelf[2],stripsratio);
	      MaskedGlobW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera.c_str());

	      AverageEffW0far->SetBinContent(indexWheelf[2],averageeff);
              AverageEffW0far->SetBinError(indexWheelf[2],averageerr);
              AverageEffW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera.c_str());

              NoPredictionW0far->SetBinContent(indexWheelf[2],nopredictionsratio);
              NoPredictionW0far->GetXaxis()->SetBinLabel(indexWheelf[2],camera.c_str());
	    }else if(Ring==1){
	      indexWheelf[3]++;  
	      EffGlobW1far->SetBinContent(indexWheelf[3],ef);  
	      EffGlobW1far->SetBinError(indexWheelf[3],er);  
	      EffGlobW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera.c_str());  
	      
	      BXGlobW1far->SetBinContent(indexWheelf[3],mybxhisto);  
	      BXGlobW1far->SetBinError(indexWheelf[3],mybxerror);  
	      BXGlobW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera.c_str());

	      MaskedGlobW1far->SetBinContent(indexWheelf[3],stripsratio);
	      MaskedGlobW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera.c_str());
	      
	      AverageEffW1far->SetBinContent(indexWheelf[3],averageeff);
              AverageEffW1far->SetBinError(indexWheelf[3],averageerr);
              AverageEffW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera.c_str());

              NoPredictionW1far->SetBinContent(indexWheelf[3],nopredictionsratio);
              NoPredictionW1far->GetXaxis()->SetBinLabel(indexWheelf[3],camera.c_str());

	    }else if(Ring==2){
	      indexWheelf[4]++;
	      EffGlobW2far->SetBinContent(indexWheelf[4],ef);
	      EffGlobW2far->SetBinError(indexWheelf[4],er);
	      EffGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera.c_str());

	      BXGlobW2far->SetBinContent(indexWheelf[4],mybxhisto);  
	      BXGlobW2far->SetBinError(indexWheelf[4],mybxerror);  
	      BXGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera.c_str());
	      
	      MaskedGlobW2far->SetBinContent(indexWheelf[4],stripsratio);
	      MaskedGlobW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera.c_str());

	      AverageEffW2far->SetBinContent(indexWheelf[4],averageeff);
              AverageEffW2far->SetBinError(indexWheelf[4],averageerr);
              AverageEffW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera.c_str());

              NoPredictionW2far->SetBinContent(indexWheelf[4],nopredictionsratio);
              NoPredictionW2far->GetXaxis()->SetBinLabel(indexWheelf[4],camera.c_str());
	    }
	  }
	}
      }
    }
  }
  

//Producing Images

EffGlobWm2->GetXaxis()->LabelsOption("v");
EffGlobWm1->GetXaxis()->LabelsOption("v");
EffGlobW0->GetXaxis()->LabelsOption("v");
EffGlobW1->GetXaxis()->LabelsOption("v");
EffGlobW2->GetXaxis()->LabelsOption("v");

EffGlobWm2->GetXaxis()->SetLabelSize(0.03);
EffGlobWm1->GetXaxis()->SetLabelSize(0.03);
EffGlobW0->GetXaxis()->SetLabelSize(0.03);
EffGlobW1->GetXaxis()->SetLabelSize(0.03);
EffGlobW2->GetXaxis()->SetLabelSize(0.03);

EffGlobWm2->GetYaxis()->SetRangeUser(0.,100.);
EffGlobWm1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW0->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW2->GetYaxis()->SetRangeUser(0.,100.);
  
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

EffGlobWm2far->GetXaxis()->SetLabelSize(0.03);
EffGlobWm1far->GetXaxis()->SetLabelSize(0.03);
EffGlobW0far->GetXaxis()->SetLabelSize(0.03);
EffGlobW1far->GetXaxis()->SetLabelSize(0.03);
EffGlobW2far->GetXaxis()->SetLabelSize(0.03);

EffGlobWm2far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobWm1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW0far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW2far->GetYaxis()->SetRangeUser(0.,100.);
  
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

AverageEffWm2->GetXaxis()->LabelsOption("v");
AverageEffWm1->GetXaxis()->LabelsOption("v");
AverageEffW0->GetXaxis()->LabelsOption("v");
AverageEffW1->GetXaxis()->LabelsOption("v");
AverageEffW2->GetXaxis()->LabelsOption("v");

AverageEffWm2far->GetXaxis()->LabelsOption("v");
AverageEffWm1far->GetXaxis()->LabelsOption("v");
AverageEffW0far->GetXaxis()->LabelsOption("v");
AverageEffW1far->GetXaxis()->LabelsOption("v");
AverageEffW2far->GetXaxis()->LabelsOption("v");

NoPredictionWm2->GetXaxis()->LabelsOption("v");
NoPredictionWm1->GetXaxis()->LabelsOption("v");
NoPredictionW0->GetXaxis()->LabelsOption("v");
NoPredictionW1->GetXaxis()->LabelsOption("v");
NoPredictionW2->GetXaxis()->LabelsOption("v");

NoPredictionWm2far->GetXaxis()->LabelsOption("v");
NoPredictionWm1far->GetXaxis()->LabelsOption("v");
NoPredictionW0far->GetXaxis()->LabelsOption("v");
NoPredictionW1far->GetXaxis()->LabelsOption("v");
NoPredictionW2far->GetXaxis()->LabelsOption("v");

std::cout<<"Efficiency Images"<<std::endl;


pave = new TPaveText(35,119,60,102);
TText *t1=pave->AddText("BX Distribution (Right Axis ->)");
t1->SetTextColor(9);
TText *t2=pave->AddText("Average Efficiency (%)");
t2->SetTextColor(8);
TText *t3=pave->AddText("Integral Efficiency (%)");
//black
TText *t4=pave->AddText("Strips without Data (ratio)"); 
t4->SetTextColor(2);
TText *t5=pave->AddText("Strips Never Pointed for a Segment (ratio)");
t5->SetTextColor(5);

pave->SetFillColor(18);

t1->SetTextSize(0.019);
t2->SetTextSize(0.019);
t3->SetTextSize(0.019);
t4->SetTextSize(0.019);
t5->SetTextSize(0.019);


Ca2->SetBottomMargin(0.4);
  
TGaxis * bxAxis = new TGaxis(104.,0.,104.,100.,-5,5,11,"+L");
TGaxis * bxAxisFar = new TGaxis(108.,0.,108.,100.,-5,5,11,"+L");

bxAxis->SetLabelColor(9);
bxAxis->SetName("bxAxis");
bxAxis->SetTitle("Mean BX (bx Units)");
bxAxis->SetTitleColor(9);
bxAxis->CenterTitle();

bxAxisFar->SetLabelColor(9);
bxAxisFar->SetName("bxAxis");
bxAxisFar->SetTitle("Mean BX (bx Units)");
bxAxisFar->SetTitleColor(9);
bxAxisFar->CenterTitle();
gStyle->SetOptStat(0);

EffGlobWm2->Draw();
EffGlobWm2->GetYaxis()->SetTitle("%");
  
BXGlobWm2->SetMarkerColor(9);
BXGlobWm2->SetLineColor(9);
BXGlobWm2->Draw("same");

MaskedGlobWm2->SetMarkerColor(2);
MaskedGlobWm2->SetLineColor(2);
MaskedGlobWm2->Draw("same");

AverageEffWm2->SetMarkerColor(8);
AverageEffWm2->SetLineColor(8);
AverageEffWm2->Draw("same");

NoPredictionWm2->SetMarkerColor(5);
NoPredictionWm2->SetLineColor(5);
NoPredictionWm2->Draw("same");

pave->Draw();
 
bxAxis->Draw("same");
  
Ca2->SaveAs("BxDeadStripEffFromLocalWm2near.png");
Ca2->SaveAs("BxDeadStripEffFromLocalWm2near.root");
Ca2->Clear();

EffGlobWm2far->Draw();
EffGlobWm2far->GetYaxis()->SetTitle("%");
  
BXGlobWm2far->SetMarkerColor(9);
BXGlobWm2far->SetLineColor(9);
BXGlobWm2far->Draw("same");

MaskedGlobWm2far->SetMarkerColor(2);
MaskedGlobWm2far->SetLineColor(2);
MaskedGlobWm2far->Draw("same");

AverageEffWm2far->SetMarkerColor(8);
AverageEffWm2far->SetLineColor(8);
AverageEffWm2far->Draw("same");

NoPredictionWm2far->SetMarkerColor(5);
NoPredictionWm2far->SetLineColor(5);
NoPredictionWm2far->Draw("same");

pave->Draw();

bxAxisFar->Draw("same");
  
Ca2->SaveAs("BxDeadStripEffFromLocalWm2far.png");
Ca2->SaveAs("BxDeadStripEffFromLocalWm2far.root");
Ca2->Clear();

EffGlobWm1->Draw();
EffGlobWm1->GetYaxis()->SetTitle("%");
  
BXGlobWm1->SetMarkerColor(9);
BXGlobWm1->SetLineColor(9);
BXGlobWm1->Draw("same");

MaskedGlobWm1->SetMarkerColor(2);
MaskedGlobWm1->SetLineColor(2);
MaskedGlobWm1->Draw("same");

AverageEffWm1->SetMarkerColor(8);
AverageEffWm1->SetLineColor(8);
AverageEffWm1->Draw("same");

NoPredictionWm1->SetMarkerColor(5);
NoPredictionWm1->SetLineColor(5);
NoPredictionWm1->Draw("same");
 
pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalWm1near.png");
Ca2->SaveAs("BxDeadStripEffFromLocalWm1near.root");
Ca2->Clear();

EffGlobWm1far->Draw();
EffGlobWm1far->GetYaxis()->SetTitle("%");
  
BXGlobWm1far->SetMarkerColor(9);
BXGlobWm1far->SetLineColor(9);
BXGlobWm1far->Draw("same");

MaskedGlobWm1far->SetMarkerColor(2);
MaskedGlobWm1far->SetLineColor(2);
MaskedGlobWm1far->Draw("same");

AverageEffWm1far->SetMarkerColor(8);
AverageEffWm1far->SetLineColor(8);
AverageEffWm1far->Draw("same");

NoPredictionWm1far->SetMarkerColor(5);
NoPredictionWm1far->SetLineColor(5);
NoPredictionWm1far->Draw("same");
 
pave->Draw();

bxAxisFar->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalWm1far.png");
Ca2->SaveAs("BxDeadStripEffFromLocalWm1far.root");
Ca2->Clear();

EffGlobW0->Draw();
EffGlobW0->GetYaxis()->SetTitle("%");
  
BXGlobW0->SetMarkerColor(9);
BXGlobW0->SetLineColor(9);
BXGlobW0->Draw("same");

MaskedGlobW0->SetMarkerColor(2);
MaskedGlobW0->SetLineColor(2);
MaskedGlobW0->Draw("same");

AverageEffW0->SetMarkerColor(8);
AverageEffW0->SetLineColor(8);
AverageEffW0->Draw("same");

NoPredictionW0->SetMarkerColor(5);
NoPredictionW0->SetLineColor(5);
NoPredictionW0->Draw("same");
 
pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalW0near.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW0near.root");
Ca2->Clear();

EffGlobW0far->Draw();
EffGlobW0far->GetYaxis()->SetTitle("%");
  
BXGlobW0far->SetMarkerColor(9);
BXGlobW0far->SetLineColor(9);
BXGlobW0far->Draw("same");

MaskedGlobW0far->SetMarkerColor(2);
MaskedGlobW0far->SetLineColor(2);
MaskedGlobW0far->Draw("same");

AverageEffW0far->SetMarkerColor(8);
AverageEffW0far->SetLineColor(8);
AverageEffW0far->Draw("same");

  NoPredictionW0far->SetMarkerColor(5);
NoPredictionW0far->SetLineColor(5);
NoPredictionW0far->Draw("same");
 
pave->Draw();

bxAxisFar->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalW0far.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW0far.root");
Ca2->Clear();

EffGlobW1->Draw();
EffGlobW1->GetYaxis()->SetTitle("%");
  
BXGlobW1->SetMarkerColor(9);
BXGlobW1->SetLineColor(9);
BXGlobW1->Draw("same");

MaskedGlobW1->SetMarkerColor(2);
MaskedGlobW1->SetLineColor(2);
MaskedGlobW1->Draw("same");

AverageEffW1->SetMarkerColor(8);
AverageEffW1->SetLineColor(8);
AverageEffW1->Draw("same");

NoPredictionW1->SetMarkerColor(5);
NoPredictionW1->SetLineColor(5);
NoPredictionW1->Draw("same");

pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalW1near.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW1near.root");
Ca2->Clear();

EffGlobW1far->Draw();
EffGlobW1far->GetYaxis()->SetTitle("%");
  
BXGlobW1far->SetMarkerColor(9);
BXGlobW1far->SetLineColor(9);
BXGlobW1far->Draw("same");

MaskedGlobW1far->SetMarkerColor(2);
MaskedGlobW1far->SetLineColor(2);
MaskedGlobW1far->Draw("same");

AverageEffW1far->SetMarkerColor(8);
AverageEffW1far->SetLineColor(8);
AverageEffW1far->Draw("same");

NoPredictionW1far->SetMarkerColor(5);
NoPredictionW1far->SetLineColor(5);
NoPredictionW1far->Draw("same");

pave->Draw();

bxAxisFar->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalW1far.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW1far.root");
Ca2->Clear();

EffGlobW2->Draw();
EffGlobW2->GetYaxis()->SetTitle("%");
  
BXGlobW2->SetMarkerColor(9);
BXGlobW2->SetLineColor(9);
BXGlobW2->Draw("same");

MaskedGlobW2->SetMarkerColor(2);
MaskedGlobW2->SetLineColor(2);
MaskedGlobW2->Draw("same");

AverageEffW2->SetMarkerColor(8);
AverageEffW2->SetLineColor(8);
AverageEffW2->Draw("same");

NoPredictionW2->SetMarkerColor(5);
NoPredictionW2->SetLineColor(5);
NoPredictionW2->Draw("same");

pave->Draw();
  
bxAxis->Draw("same");

Ca2->SaveAs("BxDeadStripEffFromLocalW2near.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW2near.root");
Ca2->Clear();
  
EffGlobW2far->Draw();
EffGlobW2far->GetYaxis()->SetTitle("%");
  
BXGlobW2far->SetMarkerColor(9);
BXGlobW2far->SetLineColor(9);
BXGlobW2far->Draw("same");

MaskedGlobW2far->SetMarkerColor(2);
MaskedGlobW2far->SetLineColor(2);
MaskedGlobW2far->Draw("same");

AverageEffW2far->SetMarkerColor(8);
AverageEffW2far->SetLineColor(8);
AverageEffW2far->Draw("same");

NoPredictionW2far->SetMarkerColor(5);
NoPredictionW2far->SetLineColor(5);
NoPredictionW2far->Draw("same");

pave->Draw();

bxAxisFar->Draw("same");
  
Ca2->SaveAs("BxDeadStripEffFromLocalW2far.png");
Ca2->SaveAs("BxDeadStripEffFromLocalW2far.root");
Ca2->Clear();

theFileOut->cd();

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

AverageEffWm2->Write();
AverageEffWm1->Write();
AverageEffW0->Write();
AverageEffW1->Write();
AverageEffW2->Write();

AverageEffWm2far->Write();
AverageEffWm1far->Write();
AverageEffW0far->Write();
AverageEffW1far->Write();
AverageEffW2far->Write();

NoPredictionWm2->Write();
NoPredictionWm1->Write();
NoPredictionW0->Write();
NoPredictionW1->Write();
NoPredictionW2->Write();

NoPredictionWm2far->Write();
NoPredictionWm1far->Write();
NoPredictionW0far->Write();
NoPredictionW1far->Write();
NoPredictionW2far->Write();

Ca2->Close();
  
Ca1->Close();
theFileOut->Close();
theFile->Close();

} 

// ------------ method called once each job just after ending the event loop  ------------
void 
LASTEFF::endJob(){
    
}

DEFINE_FWK_MODULE(LASTEFF);


