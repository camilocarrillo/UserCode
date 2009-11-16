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
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include "FWCore/Framework/interface/ESHandle.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include <Analysis/RPCPointProducer/interface/DTSegtoRPC.h>
#include <Analysis/RPCPointProducer/interface/CSCSegtoRPC.h>

//
// class decleration
//

class RPCPointProducer : public edm::EDProducer {
   public:
      explicit RPCPointProducer(const edm::ParameterSet&);
      ~RPCPointProducer();
      std::string dt4DSegments;
      std::string cscSegments;
   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      bool incldt;
      bool inclcsc;
      bool debug;
      double MinCosAng;
      double MaxD;
      double MaxDrb4;
      double MaxDistanceBetweenSegments;
      double ExtrapolatedRegion;
  
      // ----------member data ---------------------------
};

RPCPointProducer::RPCPointProducer(const edm::ParameterSet& iConfig)
{
  dt4DSegments=iConfig.getUntrackedParameter<std::string>("dt4DSegments","dt4DSegments");
  cscSegments=iConfig.getUntrackedParameter<std::string>("cscSegments","cscSegments");

  debug=iConfig.getUntrackedParameter<bool>("debug",false);
  incldt=iConfig.getUntrackedParameter<bool>("incldt",true);
  inclcsc=iConfig.getUntrackedParameter<bool>("inclcsc",true);
  MinCosAng=iConfig.getUntrackedParameter<double>("MinCosAng",0.95);
  MaxD=iConfig.getUntrackedParameter<double>("MaxD",80.);
  MaxDrb4=iConfig.getUntrackedParameter<double>("MaxDrb4",150.);
  MaxDistanceBetweenSegments=iConfig.getUntrackedParameter<double>("",150.);
  ExtrapolatedRegion=iConfig.getUntrackedParameter<double>("ExtrapolatedRegion",0.5);

  produces<RPCRecHitCollection>("RPCDTExtrapolatedPoints");
  produces<RPCRecHitCollection>("RPCCSCExtrapolatedPoints");
  
}


RPCPointProducer::~RPCPointProducer(){

}

void RPCPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  /*
  struct timespec start_time, stop_time;
  time_t fs;
  time_t fn;
  time_t ls;
  time_t ln;
  clock_gettime(CLOCK_REALTIME, &start_time);  
  */

  if(incldt){
    edm::Handle<DTRecSegment4DCollection> all4DSegments;
    iEvent.getByLabel(dt4DSegments, all4DSegments);
    DTSegtoRPC DTClass(all4DSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
    std::auto_ptr<RPCRecHitCollection> TheDTPoints(DTClass.thePoints());  
    
    iEvent.put(TheDTPoints,"RPCDTExtrapolatedPoints"); 
  }

  if(inclcsc){
    edm::Handle<CSCSegmentCollection> allCSCSegments;
    iEvent.getByLabel(cscSegments, allCSCSegments);
    CSCSegtoRPC CSCClass(allCSCSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
    std::auto_ptr<RPCRecHitCollection> TheCSCPoints(CSCClass.thePoints());  
  
    iEvent.put(TheCSCPoints,"RPCCSCExtrapolatedPoints"); 
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
