// -*- C++ -*-
//
// Package:    RECHITANALIZER
// Class:      RECHITANALIZER
// 
/**\class RECHITANALIZER RECHITANALIZER.cc beta/RECHITANALIZER/src/RECHITANALIZER.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Mar 16 22:50:16 CET 2009
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
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/RPCDigi/interface/RPCDigiCollection.h>
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
 
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include <Geometry/RPCGeometry/interface/RPCRoll.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>


//
// class decleration
//

class RECHITANALIZER : public edm::EDAnalyzer {
   public:
      explicit RECHITANALIZER(const edm::ParameterSet&);
      ~RECHITANALIZER();
      edm::ESHandle <RPCGeometry> rpcGeo;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      
   private:
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
RECHITANALIZER::RECHITANALIZER(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed

}


RECHITANALIZER::~RECHITANALIZER()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
RECHITANALIZER::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // ================
   // RPC recHits
   // ================
   Handle<RPCRecHitCollection> rpcRecHits; 
   iEvent.getByLabel("rpcRecHits","",rpcRecHits);
   //   iEvent.getByType(rpcRecHits);

   // count the number of RPC rechits
   int nRPC = 0;
   RPCRecHitCollection::const_iterator recHit;
   for (recHit = rpcRecHits->begin(); recHit != rpcRecHits->end(); recHit++) {
     //    RPCDetId id = (RPCDetId)(*recHit).rpcId();
     //    LocalPoint rhitlocal = (*recHit).localPosition();
     nRPC++;
   }
   

   std::cout<<"The Number of Rec Hits is "<<nRPC<<std::endl;

   for (recHit = rpcRecHits->begin(); recHit != rpcRecHits->end(); recHit++) {
     RPCDetId rollId = (RPCDetId)(*recHit).rpcId();
     RPCGeomServ rpcsrv(rollId);
     LocalPoint recHitPos=recHit->localPosition();

     const RPCRoll* rollasociated = rpcGeo->roll(rollId);

     const BoundPlane & RPCSurface = rollasociated->surface(); 

     GlobalPoint RecHitInGlobal = RPCSurface.toGlobal(recHitPos);
     
     std::cout<<"\t \t We have an RPC Rec Hit! bx="<<recHit->BunchX()<<" Roll="<<rpcsrv.name()<<" Global Position="<<RecHitInGlobal<<std::endl;

   }
}


// ------------ method called once each job just before starting event loop  ------------

void RECHITANALIZER::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
RECHITANALIZER::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RECHITANALIZER);
