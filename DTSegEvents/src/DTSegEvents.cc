// -*- C++ -*-
//
// Package:    DTSegEvents
// Class:      DTSegEvents
// 
/**\class DTSegEvents DTSegEvents.cc Analysis/DTSegEvents/src/DTSegEvents.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Feb  5 11:30:12 CET 2009
// $Id$
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


//
// class declaration
//

class DTSegEvents : public edm::EDFilter {
   public:
      explicit DTSegEvents(const edm::ParameterSet&);
      ~DTSegEvents();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string dt4DSegments;
      int Wheel;
      int Station;
      int Sector;
  
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
DTSegEvents::DTSegEvents(const edm::ParameterSet& iConfig)
{
  dt4DSegments=iConfig.getUntrackedParameter<std::string>("dt4DSegments","dt4DSegments");
  Wheel = iConfig.getUntrackedParameter<int>("Wheel",0); 
  Station = iConfig.getUntrackedParameter<int>("Station",0); 
  Sector = iConfig.getUntrackedParameter<int>("Sector",0); 
}


DTSegEvents::~DTSegEvents()
{
 
}

bool
DTSegEvents::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::cout<<"Getting the DT Segments"<<std::endl;
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(dt4DSegments, all4DSegments);

  bool interestingEvent = false;

  if(all4DSegments->size()>0){
    std::cout<<"We have DT Segments"<<std::endl;
    DTRecSegment4DCollection::const_iterator segment;  
    
    for (segment = all4DSegments->begin();segment!=all4DSegments->end(); ++segment){
       DTChamberId DTId = segment->chamberId();
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
DTSegEvents::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DTSegEvents::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTSegEvents);
