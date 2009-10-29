// -*- C++ -*-
//
// Package:    RPCPathoChambFilter
// Class:      RPCPathoChambFilter
// 
/**\class RPCPathoChambFilter RPCPathoChambFilter.cc Analysis/RPCPathoChambFilter/src/RPCPathoChambFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Thu Oct 29 11:04:22 CET 2009
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

class RPCPathoChambFilter : public edm::EDFilter {
   public:
      explicit RPCPathoChambFilter(const edm::ParameterSet&);
      ~RPCPathoChambFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      double rangestrips;
      edm::InputTag rpcRecHitsLabel;
      edm::InputTag rpcPointsLabel;

      
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
RPCPathoChambFilter::RPCPathoChambFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

  rangestrips = iConfig.getUntrackedParameter<double>("rangestrips",1.);
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  rpcPointsLabel  = iConfig.getParameter<edm::InputTag>("rpcPoints");

}


RPCPathoChambFilter::~RPCPathoChambFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RPCPathoChambFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool anyunmatched = false;
  float cluSize = 0;

  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);

  edm::Handle<RPCRecHitCollection> rpcPoints;
  iEvent.getByLabel(rpcPointsLabel,rpcPoints);
  
  RPCRecHitCollection::const_iterator rpcPoint;
  
  for(rpcPoint = rpcPoints->begin(); rpcPoint != rpcPoints->end(); rpcPoint++){
    LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
    RPCDetId  rpcId = rpcPoint->rpcId();
    typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
    rangeRecHits recHitCollection =  rpcHits->get(rpcId);
    if(recHitCollection.first==recHitCollection.second){
      std::cout<<" passed, no eff"<<std::endl;
      return true;
    }
    float minres = 3000.;
    RPCRecHitCollection::const_iterator recHit;
    for(recHit = recHitCollection.first; recHit != recHitCollection.second ; recHit++) {
      LocalPoint recHitPos=recHit->localPosition();
      float res=PointExtrapolatedRPCFrame.x()- recHitPos.x();
      if(fabs(res)<fabs(minres)){
	minres=res;
	cluSize = recHit->clusterSize();
      }
    }
    if(fabs(minres)>=(rangestrips+cluSize*0.5)*3){ //3 is a typyical strip with for RPCs
      std::cout<<" passed, no eff"<<std::endl;
      return true;
    }
  }
  std::cout<<" skiped"<<std::endl;
  return anyunmatched;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCPathoChambFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCPathoChambFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCPathoChambFilter);
