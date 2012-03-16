// -*- C++ -*-
//
// Package:    DTcomparison
// Class:      DTcomparison
// 
/**\class DTcomparison DTcomparison.cc Analysis/DTcomparison/src/DTcomparison.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Feb  5 11:30:12 CET 2009
// $Id: DTcomparison.cc,v 1.3 2012/02/28 13:20:25 carrillo Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include <cmath>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"


//
// class declaration
//

class TFile;

class DTcomparison : public edm::EDFilter {
public:
  explicit DTcomparison(const edm::ParameterSet&);
  ~DTcomparison();
  TFile * theFile;
  TH2F * OccupancyWheelm2;
  TH2F * OccupancyWheelm1;
  TH2F * OccupancyWheel0;
  TH2F * OccupancyWheel1;
  TH2F * OccupancyWheel2;
  TH1F * nHits;
  TH1F * nHitsZ;
  TH1F * nHitsPhi;
  TH1F * chi2;
  TH1F * dimen;
  TH1F * proy;     
  
  edm::InputTag dt4DSegments;
private:
  std::string filename;
  virtual void beginJob(const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  int Wheel;
  int Station;
  int Sector;
};

DTcomparison::DTcomparison(const edm::ParameterSet& iConfig)
{
  dt4DSegments=iConfig.getParameter<edm::InputTag>("dt4DSegments");
  
  filename=iConfig.getUntrackedParameter<std::string>("fileName");

  std::cout<<"the file name is "<<filename<<std::endl;
  theFile = new TFile(filename.c_str(),"RECREATE");

  Wheel = iConfig.getUntrackedParameter<int>("Wheel",0); 
  Station = iConfig.getUntrackedParameter<int>("Station",0); 
  Sector = iConfig.getUntrackedParameter<int>("Sector",0); 

  OccupancyWheelm2 = new TH2F ("OccupancyWheelm2","Segment Occupancy Wheel -2",12,0.5,12.5,4,0.5,4.5);
  OccupancyWheelm1 = new TH2F ("OccupancyWheelm1","Segment Occupancy Wheel -1",12,0.5,12.5,4,0.5,4.5);
  OccupancyWheel0 =  new TH2F ("OccupancyWheel0","Segment Occupancy Wheel 0",  12,0.5,12.5,4,0.5,4.5);
  OccupancyWheel1 =  new TH2F ("OccupancyWheel1","Segment Occupancy Wheel 1",  12,0.5,12.5,4,0.5,4.5);
  OccupancyWheel2 =  new TH2F ("OccupancyWheel2","Segment Occupancy Wheel 2",  12,0.5,12.5,4,0.5,4.5);

  nHits= new TH1F ("NumberOfHits","NumberOfHits",20,0,20);
  nHitsPhi= new TH1F ("NumberOfHitsPhi","NumberOfHitsPhi",10,0,10);
  nHitsZ= new TH1F ("NumberOfHitsZ","NumberOfHitsZ",10,0,10);
  
  chi2= new TH1F ("chi2","chi2",100,0,20);
  dimen= new TH1F ("dimen","dimen",10,-0.5,9.5);
  proy= new TH1F ("proy","proy",2,-0.5,1.5);
}


DTcomparison::~DTcomparison()
{
 
}

bool
DTcomparison::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  std::cout<<"the input tag is"<<dt4DSegments<<std::endl;
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(dt4DSegments, all4DSegments);
  
  bool interestingEvent = false;


  if(all4DSegments.isValid()) if(all4DSegments->size()>0){
    std::cout<<"We have DT Segments"<<std::endl;
    DTRecSegment4DCollection::const_iterator segment;  
    
    for (segment = all4DSegments->begin();segment!=all4DSegments->end(); ++segment){
      DTChamberId DTId = segment->chamberId();
      
      if(segment->hasPhi()) 
	proy->Fill(0); 
      if(segment->hasZed()) 
	proy->Fill(1);
      
      //int HitsZ = ((((*segment).zSegment())->specificRecHits()).size());
      //int HitsPhi = (((*segment).phiSegment())->specificRecHits()).size();
      //nHitsPhi->Fill(HitsPhi);
      //nHitsZ->Fill(HitsZ);
      //nHits->Fill(HitsZ+HitsPhi);
      chi2->Fill(segment->chi2());
      dimen->Fill(segment->dimension());
      
      int thisWheel = DTId.wheel();
      int thisStation = DTId.station();
      int thisSector = DTId.sector();

      std::cout<<"\t 1st "<<DTId<<std::endl;
      
      if(thisWheel==-2){ OccupancyWheelm2->Fill(thisSector,thisStation);}
      if(thisWheel==-1){ OccupancyWheelm1->Fill(thisSector,thisStation);}
      if(thisWheel==0){  OccupancyWheel0->Fill(thisSector,thisStation);}
      if(thisWheel==1){  OccupancyWheel1->Fill(thisSector,thisStation);}
      if(thisWheel==2){  OccupancyWheel2->Fill(thisSector,thisStation);}

      std::cout<<"\t"<<DTId<<std::endl;
      if(DTId.wheel()==Wheel && DTId.station()==Station && DTId.sector()==Sector){
	std::cout<<"\t \t Right"<<DTId<<std::endl;
	interestingEvent = true;
      }
    }  
  }
  if(interestingEvent){
    std::cout<<"\t \t Saving Event"<<std::endl;
    return true;
  }else{
    std::cout<<"\t \t Skiping Event"<<std::endl;
    return false;
  }
}

// ------------ method called once each job just before starting event loop  ------------
void 
DTcomparison::beginJob(const edm::EventSetup&)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DTcomparison::endJob() {
  std::cout<<"end Job begining "<<std::endl;
  theFile->cd();
  std::cout<<"file cd "<<std::endl;
  OccupancyWheelm2->Write();
  OccupancyWheelm1->Write();
  OccupancyWheel0 ->Write();
  OccupancyWheel1 ->Write();
  OccupancyWheel2 ->Write();
  
  nHits->Write();	   
  nHitsZ->Write();   
  nHitsPhi->Write(); 
  chi2->Write();	   
  dimen->Write();	   
  proy->Write();     

  std::cout<<"files wrote "<<std::endl;
  theFile->Write();
  theFile->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTcomparison);
