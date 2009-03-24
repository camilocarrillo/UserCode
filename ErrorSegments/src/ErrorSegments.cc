// -*- C++ -*-
//
// Package:    ErrorSegments
// Class:      ErrorSegments
// 
/**\class ErrorSegments ErrorSegments.cc Analysis/ErrorSegments/src/ErrorSegments.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Feb 26 14:49:55 CET 2009
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

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include "FWCore/Framework/interface/ESHandle.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"


//
// class decleration
//

class ErrorSegments : public edm::EDAnalyzer {
   public:
      explicit ErrorSegments(const edm::ParameterSet&);
      ~ErrorSegments();
      TFile * theFile;
      TH1F * chi2histoZ;      
      TH1F * chi2histoRP;
      TH1F * nhitsZ;
      TH1F * nhitsRP;
      TH1F * directionZ;
      TH1F * directionRP;
      TH2F * scaterChi2AngleZ;
      TH2F * scaterChi2AngleRP;
  

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

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
ErrorSegments::ErrorSegments(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  
  theFile = new TFile("segmentshitos.root", "RECREATE");
  chi2histoZ = new TH1F ("chi2histoZ","chi2histoZ",100,0.,100.);
  chi2histoRP= new TH1F ("chi2histoRP","chi2histoRP",100,0.,100.);
  nhitsZ= new TH1F ("nhitsZ","nhitsZ",21,-0.5,20.5);
  nhitsRP= new TH1F ("nhitsRP","nhitsRP",21,-0.5,20.5);
  directionZ= new TH1F ("directionZ","directionZ",100,-0.5*3.1415,0.5*3.1415);
  directionRP = new TH1F ("directionRP","directionRP",100,-0.5*3.1415,0.5*3.1415);
  scaterChi2AngleRP = new TH2F ("scaterChi2AngleRP","scaterChi2AngleRP",100,0.,100.,100,-0.5*3.1415,0.5*3.1415);
  scaterChi2AngleZ = new TH2F ("scaterChi2AngleZ","scaterChi2AngleZ",100,0.,100.,100,-0.5*3.1415,0.5*3.1415);
 
}


ErrorSegments::~ErrorSegments()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ErrorSegments::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::cout<<"Getting the DT Segments"<<std::endl;
   edm::Handle<DTRecSegment4DCollection> all4DSegments;
   iEvent.getByLabel("dt4DSegments", all4DSegments);

   if(all4DSegments->size()>0){
     std::cout<<"We have DT Segments"<<std::endl;
     DTRecSegment4DCollection::const_iterator segment;  
     
     for (segment = all4DSegments->begin();segment!=all4DSegments->end(); ++segment){if(segment->dimension()==4){
       DTChamberId DTId = segment->chamberId();
       std::cout<<"\t"<<DTId<<"\n Position="<<segment->localPosition()<<"+/-"<<segment->localPositionError()
		<<"\n Direction="<<segment->localDirection()<<"+/-"<<segment->localDirectionError()
		<<"\n chi2="<<segment->chi2()<<" dof="<<segment->degreesOfFreedom()<<" chi2/dof="<<segment->chi2()/float( segment->degreesOfFreedom())
		<<" fidof="<<segment->phiSegment()->degreesOfFreedom()
		<<" z dof="<<segment->zSegment()->degreesOfFreedom()
		<<" dimension phi="<<segment->phiSegment()->dimension()
		<<" dimension z="<<segment->zSegment()->dimension()<<std::endl;
       
       float dx = segment->localDirection().x();
       float dy = segment->localDirection().y();
       float dz = segment->localDirection().z();
       
       if(DTId.sector()==4 && DTId.station() == 1 && DTId.wheel()==2 /*&& segment->zSegment()->degreesOfFreedom()==2*/){
	 std::cout<<"Filling Histo with "<<std::endl;
	 int ndofz = segment->zSegment()->degreesOfFreedom();
	 int ndofrp = segment->phiSegment()->degreesOfFreedom();
	 chi2histoZ->Fill(segment->zSegment()->chi2()/ndofz);
	 chi2histoRP->Fill(segment->phiSegment()->chi2()/ndofrp);

	 //nhitsZ->Fill(ndofz+segment->zSegment()->specificRecHits().size());
	 nhitsRP->Fill(ndofrp);
	 nhitsZ->Fill(ndofz);

	 float anglerp = asin(dx/sqrt(dz*dz+dx*dx));
	 float anglez = asin(dy/sqrt(dz*dz+dy*dy));

	 directionRP->Fill(anglerp);
	 directionZ->Fill(anglez);
	 
	 scaterChi2AngleZ->Fill(segment->zSegment()->chi2()/ndofz,anglez);
	 scaterChi2AngleRP->Fill(segment->phiSegment()->chi2()/ndofrp,anglerp);
	 	 
       }
     }}
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
ErrorSegments::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ErrorSegments::endJob() {
  chi2histoZ->Write();

  chi2histoRP->Write();
  nhitsZ->Write();
  nhitsRP->Write();
  directionRP->Write();
  directionZ->Write();
  scaterChi2AngleZ->Write();
  scaterChi2AngleRP->Write();

  theFile->Save();
  theFile->Close();
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(ErrorSegments);
