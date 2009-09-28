// -*- C++ -*-
//
// Package:    RPCPointProducer
// Class:      RPCPointProducer
// 
/**\class RPCPointProducer RPCPointProducer.cc Analysis/RPCPointProducer/src/RPCPointProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Wed Sep 16 14:56:18 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Analysis/RPCPointProducer/interface/DTSegtoRPC.h>


//
// class decleration
//

class RPCPointProducer : public edm::EDProducer {
   public:
      explicit RPCPointProducer(const edm::ParameterSet&);
      ~RPCPointProducer();
      std::string dt4DSegments;
   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
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
RPCPointProducer::RPCPointProducer(const edm::ParameterSet& iConfig)
{
  std::cout<<"In the constructor"<<std::endl;
  dt4DSegments=iConfig.getUntrackedParameter<std::string>("dt4DSegments","dt4DSegments");
  //register your products
  /* Examples
     produces<ExampleData2>();
     
     //if do put with a label
     produces<ExampleData2>("label");
  */
  //now do what ever other initialization is needed
}


RPCPointProducer::~RPCPointProducer()
{
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RPCPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::cout<<"Getting the DT Segments"<<std::endl;
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(dt4DSegments, all4DSegments);
  
  std::cout<<"calling the class that extrapolates"<<std::endl;
  DTSegtoRPC test(all4DSegments,iSetup,iEvent);
  std::cout<<"number of segments = "<<test.numberofsegments()<<std::endl;
  
  std::vector<RPCPoint> ThePoints = test.GetThePoints();

  std::cout<<"Number of extrapolations = "<<ThePoints.size()<<std::endl;
  
  if(ThePoints.size()!=0){

    std::vector<RPCPoint>::iterator itVectorData;

    for(itVectorData = ThePoints.begin(); itVectorData != ThePoints.end(); itVectorData++){
      RPCPoint Point = *(itVectorData);
      std::cout<<Point.rawId()<<" "<<Point.x()<<" "<<Point.y()<<std::endl;
    }

    //iEvent.put(ThePoints); ????????????????????
    
  }
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCPointProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCPointProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCPointProducer);
