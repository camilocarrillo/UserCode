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
// $Id: RPCPointProducer.cc,v 1.1 2009/09/28 10:23:40 carrillo Exp $
//
//


// system include files
#include <memory>
#include <ctime>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
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
  dt4DSegments=iConfig.getUntrackedParameter<std::string>("dt4DSegments","dt4DSegments");
  produces<RPCRecHitCollection>("rpcPoints");
}


RPCPointProducer::~RPCPointProducer(){

}

void
RPCPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  /*
  struct timespec start_time, stop_time;
  time_t fs;
  time_t fn;
  time_t ls;
  time_t ln;
  clock_gettime(CLOCK_REALTIME, &start_time);  
  */

  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(dt4DSegments, all4DSegments);
  
  /*
  clock_gettime(CLOCK_REALTIME, &stop_time);
  fs=start_time.tv_sec;
  fn=start_time.tv_nsec;
  ls=stop_time.tv_sec;
  ln=stop_time.tv_nsec;
  std::cout <<" =============++| "<<ls-fs<<" sec "<<ln-fn<<" us"<<std::endl;
  clock_gettime(CLOCK_REALTIME, &start_time);
  */
  
  DTSegtoRPC test(all4DSegments,iSetup,iEvent);
  
  /*
  clock_gettime(CLOCK_REALTIME, &stop_time);
  fs=start_time.tv_sec;
  fn=start_time.tv_nsec;
  ls=stop_time.tv_sec;
  ln=stop_time.tv_nsec;
  std::cout <<" =============++|| "<<ls-fs<<" sec "<<ln-fn<<" us"<<std::endl;
  clock_gettime(CLOCK_REALTIME, &start_time);
  */
  
  std::auto_ptr<RPCRecHitCollection> ThePoints(test.thePoints());  
  
  iEvent.put(ThePoints,"rpcPoints"); 
  
  /*
  clock_gettime(CLOCK_REALTIME, &stop_time);
  fs=start_time.tv_sec;
  fn=start_time.tv_nsec;
  ls=stop_time.tv_sec;
  ln=stop_time.tv_nsec;
  std::cout <<" =============++||| "<<ls-fs<<" sec "<<ln-fn<<" us"<<std::endl;
  */

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
