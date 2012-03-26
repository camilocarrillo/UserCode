// -*- C++ -*-
//
// Package:    CSCSegmentAnalyzer
// Class:      CSCSegmentAnalyzer
// 
/**\class CSCSegmentAnalyzer CSCSegmentAnalyzer.cc Analysis/CSCSegmentAnalyzer/src/CSCSegmentAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Feb  5 11:30:12 CET 2009
// $Id: CSCSegmentAnalyzer.cc,v 1.7 2012/03/23 10:27:30 carrillo Exp $
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
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>


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

class CSCSegmentAnalyzer : public edm::EDFilter {
public:
  explicit CSCSegmentAnalyzer(const edm::ParameterSet&);
  ~CSCSegmentAnalyzer();
  TFile * theFile;
  TH2F * OccupancyDiskm3;
  TH2F * OccupancyDiskm2;
  TH2F * OccupancyDiskm1;
  TH2F * OccupancyDisk1;
  TH2F * OccupancyDisk2;
  TH2F * OccupancyDisk3; 

  TH1F * nHits;
  TH1F * Hdof;
  TH1F * chi2;
  TH1F * dimen;
  TH1F * HnumberOfSegmentsPerEvent;
  TH1F * HnumberOfSegmentsPerEventDim4;

  
  edm::InputTag cscSegments;
private:
  std::string filename;
  virtual void beginJob(const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  int Wheel;
  int Station;
  int Sector;
};

CSCSegmentAnalyzer::CSCSegmentAnalyzer(const edm::ParameterSet& iConfig)
{
  cscSegments=iConfig.getParameter<edm::InputTag>("cscSegments");
  
  filename=iConfig.getUntrackedParameter<std::string>("fileName");
  
  std::cout<<"the file name is "<<filename<<std::endl;
  theFile = new TFile(filename.c_str(),"RECREATE");
  
  OccupancyDiskm3 = new TH2F ("OccupancyDiskm3","Segment Occupancy Disk -3",36,0.5,36.5,3,0.5,3.5);
  OccupancyDiskm2 = new TH2F ("OccupancyDiskm2","Segment Occupancy Disk -2",36,0.5,36.5,3,0.5,3.5);
  OccupancyDiskm1=  new TH2F ("OccupancyDiskm1","Segment Occupancy Disk -1",36,0.5,36.5,3,0.5,3.5);
  OccupancyDisk1 =  new TH2F ("OccupancyDisk1","Segment Occupancy Disk 1",  36,0.5,36.5,3,0.5,3.5);
  OccupancyDisk2 =  new TH2F ("OccupancyDisk2","Segment Occupancy Disk 2",  36,0.5,36.5,3,0.5,3.5);
  OccupancyDisk3 =  new TH2F ("OccupancyDisk3","Segment Occupancy Disk 3",  36,0.5,36.5,3,0.5,3.5);

  nHits= new TH1F ("NumberOfHits","NumberOfHits",20,-0.5,19.5);
  Hdof= new TH1F ("DegreesOfFreedom","DegreesOfFreedom",20,-0.5,19.5);
  
  chi2= new TH1F ("chi2","chi2",100,0,20);
  dimen= new TH1F ("dimen","dimen",10,-0.5,9.5);
    
  HnumberOfSegmentsPerEvent = new TH1F ("HnumberOfSegmentsPerEvent","Number Of Segments Per Event",16,-0.5,15.5);
  HnumberOfSegmentsPerEventDim4 = new TH1F ("HnumberOfSegmentsPerEventDim4","Number Of Segments Per Event Dimension 4",16,-0.5,15.5);
}


CSCSegmentAnalyzer::~CSCSegmentAnalyzer()
{
 
}

bool
CSCSegmentAnalyzer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  std::cout<<"the input tag is"<<cscSegments<<std::endl;
  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByLabel(cscSegments, allCSCSegments);

  bool interestingEvent = false;

  int numberOfSegmentsPerEvent=0;
  int numberOfSegmentsPerEventDim4=0;
    
  if(allCSCSegments.isValid()) if(allCSCSegments->size()>0){
    std::cout<<"We have CSC Segments"<<std::endl;
    CSCSegmentCollection::const_iterator segment;  
    
    for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment){
      if(segment->dimension()!=4) continue;
      CSCDetId CSCId = segment->cscDetId();
      
      numberOfSegmentsPerEvent++;
      numberOfSegmentsPerEventDim4++;
      
      int Hits=0;
      int dof=0;

      Hits=(segment->recHits()).size();
      dof=segment->degreesOfFreedom();
      Hdof->Fill(dof);
      
      std::cout<<"allinfo "<<segment->dimension()<<" | "<<dof<<" "<<Hits<<" | ";
      
      std::cout<<std::endl;
      
      chi2->Fill(segment->chi2());
      dimen->Fill(segment->dimension());
      nHits->Fill(Hits);
      
      int thisStation = CSCId.station();
      int thisChamber = CSCId.chamber();
      int thisRing = CSCId.ring();
      
      std::cout<<"\t 1st "<<CSCId<<std::endl;

      if(CSCId.endcap()==1){
	if(thisStation==1){ OccupancyDisk1->Fill(thisChamber,thisRing);}
	if(thisStation==2){ OccupancyDisk2->Fill(thisChamber,thisRing);}
	if(thisStation==3){ OccupancyDisk3->Fill(thisChamber,thisRing);}
      } 
      if(CSCId.endcap()==2){
	if(thisStation==1){ OccupancyDiskm1->Fill(thisChamber,thisRing);}
	if(thisStation==2){ OccupancyDiskm2->Fill(thisChamber,thisRing);}
	if(thisStation==3){ OccupancyDiskm3->Fill(thisChamber,thisRing);}
      }
      
      
      interestingEvent = false;
    }  
  }

  HnumberOfSegmentsPerEventDim4->Fill(numberOfSegmentsPerEventDim4);
  HnumberOfSegmentsPerEvent->Fill(numberOfSegmentsPerEvent);
  
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
CSCSegmentAnalyzer::beginJob(const edm::EventSetup&)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CSCSegmentAnalyzer::endJob() {
  std::cout<<"end Job begining "<<std::endl;
  theFile->cd();
  std::cout<<"file cd "<<std::endl;

  OccupancyDiskm3->Write();	   
  OccupancyDiskm2->Write();	   
  OccupancyDiskm1->Write();	   
  OccupancyDisk1->Write();	    
  OccupancyDisk2->Write();	    
  OccupancyDisk3->Write();
  
  nHits->Write();	   
  chi2->Write();	   
  dimen->Write();	   
  
  HnumberOfSegmentsPerEvent->Write();
  HnumberOfSegmentsPerEventDim4->Write();
  
  Hdof->Write();
  
  std::cout<<"files wrote "<<std::endl;
  theFile->Write();
  theFile->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(CSCSegmentAnalyzer);
