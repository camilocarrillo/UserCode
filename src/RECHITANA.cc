// -*- C++ -*-
//
// Package:    RECHITANA
// Class:      RECHITANA
// 
/**\class RECHITANA RECHITANA.cc rechitana/RECHITANA/src/RECHITANA.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/28
//         Created:  Tue Apr 22 14:47:26 CEST 2008
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
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "DataFormats/DetId/interface/DetId.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include <fstream>

class RECHITANA : public edm::EDAnalyzer {
public:
  explicit RECHITANA(const edm::ParameterSet&);
  ~RECHITANA();
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  std::ofstream fileMatrix;
  //int matrixbitTOTAL[4][7];
  TFile* theFile;
  TH1F * matrixHisto;
  int Maxbx[7];
  int totalHSCP;

};


RECHITANA::RECHITANA(const edm::ParameterSet& iConfig)
{
  
}


RECHITANA::~RECHITANA()
{
}

void RECHITANA::beginJob(const edm::EventSetup&)
{
  fileMatrix.open("fileMatrix.txt");
  theFile = new TFile("rechitana.root", "RECREATE");
  //matrixHisto = new TH1F("LayersandBX","Histogram 2D Layers and BX",6,0.5,6.5,4,-0.5,3.5);
  matrixHisto = new TH1F("LayersandBX","Histogram 2D Layers and BX",30,-0.5,29.5);
  totalHSCP=0;
  
  //for(int lay=0;lay<4;lay++){//looping layers
  //  for(int bxs=0;bxs<7;bxs++){//looping bx
  //    matrixbitTOTAL[bxs][lay]=0;
  //  }
  //}
}

void RECHITANA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel("rpcRecHits",rpcHits);
  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  RPCRecHitCollection::const_iterator recIt;
  
  //Identifing in the RecHits-HSPC
   
  int const layitLimit=7;
  int const bxsitLimit=4;
  int matrixbit[bxsitLimit][layitLimit];
  for(int lay=0;lay<layitLimit;lay++){//looping layers
    for(int bxs=0;bxs<bxsitLimit;bxs++){//looping bx
      matrixbit[bxs][lay]=0;
    }
  }
  
  for(recIt=rpcHits->begin();recIt!=rpcHits->end();++recIt){
    RPCDetId RPCId((*recIt).rpcId());
    std::cout<<"RPCId"<<RPCId<<std::endl;
    
    int BX = (*recIt).BunchX();
    int layer=0;
    int mySt = RPCId.station();
    
    if(RPCId.region()==0){
      int myLa = RPCId.layer();
      if(mySt==1&&myLa==1){layer=1;}
      if(mySt==1&&myLa==2){layer=2;}
      if(mySt==2&&myLa==1){layer=3;}
      if(mySt==2&&myLa==2){layer=4;}
      if(mySt==3){layer=5;}
      if(mySt==4){layer=6;}
      matrixbit[BX][layer]++;
    }else{
      if(mySt==1){layer=1;}
      if(mySt==2){layer=2;}
      if(mySt==3){layer=3;}
    }
  }
  
  fileMatrix<<"\n";

  for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
    for(int lay=1;lay<layitLimit;lay++){//looping layers
      fileMatrix<<matrixbit[bxs][lay];
    }
    fileMatrix<<"\n";
  }

  //When we count endcaps this should work
  //assert(counter==rpcHits->size());
  
  std::cout<<"Printing matrix Event "<<iEvent.id().event()<<std::endl;
  fileMatrix<<"Printing matrix Event "<<iEvent.id().event()<<std::endl;

  bool hscp = false;
  int layersHited = 0;
  std::cout<<"Cleaning array Maxbx"<<std::endl;
  for(int i=0;i<7;i++)Maxbx[i]=0;
  std::cout<<"Cleaned"<<std::endl;

  for(int lay=1;lay<7;lay++){//looping layers
    bool anyhit = false;
    int maxbx = 0;
    for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
      if(matrixbit[bxs][lay]!=0.){
	//fileMatrix<<"Increasing "<<bxs<<" "<<lay<<" "<<matrixbit[bxs][lay]<<std::endl;
	matrixHisto->Fill(bxs+(lay-1)*5,matrixbit[bxs][lay]);
	if(matrixbit[bxs][lay]!=0){
	  anyhit=true;
	  if(maxbx<bxs)maxbx=bxs;
	}
      }
    }	
    if(anyhit)layersHited++;
    std::cout<<"Writing the array"<<" lay = "<<lay<<" maxbx = "<<maxbx<<std::endl;
    Maxbx[lay]=maxbx;
  }

  fileMatrix<<"Number Of layers "<<layersHited<<std::endl;
  for(int i=1;i<7;i++)fileMatrix<<" L"<<i<<" "<<Maxbx[i];
  fileMatrix<<"\n";

  fileMatrix<<"pendpos ";
  
  int pendpos=0;
  for(int i=1;i<6;i++){
    if(Maxbx[i]<Maxbx[i+1]){
      pendpos++;
    }
    if(Maxbx[i]>Maxbx[i+1]){
      pendpos--;
    }
    fileMatrix<<" "<<pendpos;
    
  }
  
  
  std::cout<<"Number Of layers "<<layersHited<<std::endl;
  
  if(layersHited>=3&&pendpos>0)hscp=true;
  
  std::cout<<" pendpos= "<<pendpos<<" boolean hscp= "<<hscp<<std::endl;
  fileMatrix<<" pendpos= "<<pendpos<<" boolean hscp= "<<hscp<<std::endl;
  
  if(hscp) totalHSCP++;
  
  
  //updating total counter

  //for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
  //  for(int lay=1;lay<layitLimit;lay++){//looping layers
  //    matrixbitTOTAL[bxs][lay]=matrixbitTOTAL[bxs][lay]+matrixbit[bxs][lay];
  //  }	
  //}
}

void RECHITANA::endJob() {
  
  /*
  for(int bxs=7-1;bxs>=0;bxs--){//looping bx
    for(int lay=1;lay<4;lay++){//looping layers
      fileMatrix<<matrixbitTOTAL[bxs][lay]<<"\t";
    }
    fileMatrix<<"\n";
  }
  fileMatrix<<"\n";
  
  */
  std::cout<<"\n TOTAL HSPCs = "<<totalHSCP<<std::endl;
  fileMatrix<<"\n TOTAL HSPCs = "<<totalHSCP<<std::endl;

  theFile->cd();
  matrixHisto->Write();
  theFile->Close();
  fileMatrix.close();

}

//define this as a plug-in
DEFINE_FWK_MODULE(RECHITANA);
