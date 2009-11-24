// -*- C++ -*-
//
// Package:    RPCSelectEventsForIlumination
// Class:      RPCSelectEventsForIlumination
// 
/**\class RPCSelectEventsForIlumination RPCSelectEventsForIlumination.cc Analysis/RPCSelectEventsForIlumination/src/RPCSelectEventsForIlumination.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Nov 19 12:01:17 CET 2009
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
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"


//
// class declaration
//

class RPCSelectEventsForIlumination : public edm::EDFilter {
   public:
      explicit RPCSelectEventsForIlumination(const edm::ParameterSet&);
      ~RPCSelectEventsForIlumination();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag rpcDTPointsLabel;
      edm::InputTag rpcCSCPointsLabel;

      // ----------member data ---------------------------
};

RPCSelectEventsForIlumination::RPCSelectEventsForIlumination(const edm::ParameterSet& iConfig)
{
  rpcDTPointsLabel = iConfig.getParameter<edm::InputTag>("rpcDTPoints");
  rpcCSCPointsLabel = iConfig.getParameter<edm::InputTag>("rpcCSCPoints");
}


RPCSelectEventsForIlumination::~RPCSelectEventsForIlumination()
{
  
}

bool
RPCSelectEventsForIlumination::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){
  edm::Handle<RPCRecHitCollection> rpcDTPoints;
  iEvent.getByLabel(rpcDTPointsLabel,rpcDTPoints);

  edm::Handle<RPCRecHitCollection> rpcCSCPoints;
  iEvent.getByLabel(rpcCSCPointsLabel,rpcCSCPoints);

  RPCRecHitCollection::const_iterator rpcPoint;

  //DTPart

  //  for(rpcPoint = rpcDTPoints->begin(); rpcPoint != rpcDTPoints->end(); rpcPoint++){
  for(rpcPoint = rpcCSCPoints->begin(); rpcPoint != rpcCSCPoints->end(); rpcPoint++){
    LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
    RPCDetId  rpcId = rpcPoint->rpcId(); 
    
    if(rpcId.region()!=0 && rpcId.station()==1 && rpcId.ring()==2){//selection of events pointing to RE1/2 
      //if(rpcId.rawId() == 637567373 && PointExtrapolatedRPCFrame.y() >=60.0){ //Raw ID:637567373 NameW-2_RB1in_S04_Backward
      std::cout<<"Event Passed "<<iEvent.id().event()<<std::endl;
      return true;
    }
  }
  
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCSelectEventsForIlumination::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCSelectEventsForIlumination::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCSelectEventsForIlumination);
