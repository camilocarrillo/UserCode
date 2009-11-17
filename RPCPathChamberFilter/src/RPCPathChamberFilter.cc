// -*- C++ -*-
//
// Package:    RPCPathPathChambFilter
// Class:      RPCPathChambFilter
// 
/**\class RPCPathChambFilter RPCPathChambFilter.cc Analysis/RPCPathChambFilter/src/RPCPathChambFilter.cc

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

class RPCPathChambFilter : public edm::EDFilter {
   public:
      explicit RPCPathChambFilter(const edm::ParameterSet&);
      ~RPCPathChambFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      double rangestrips;
      edm::InputTag rpcRecHitsLabel;
      edm::InputTag rpcDTPointsLabel;
      edm::InputTag rpcCSCPointsLabel;

      
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
RPCPathChambFilter::RPCPathChambFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

  rangestrips = iConfig.getUntrackedParameter<double>("rangestrips",1.);
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  rpcDTPointsLabel  = iConfig.getParameter<edm::InputTag>("rpcDTPoints");
  rpcCSCPointsLabel  = iConfig.getParameter<edm::InputTag>("rpcCSCPoints");

}


RPCPathChambFilter::~RPCPathChambFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool RPCPathChambFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);

  edm::Handle<RPCRecHitCollection> rpcDTPoints;
  iEvent.getByLabel(rpcDTPointsLabel,rpcDTPoints);

  edm::Handle<RPCRecHitCollection> rpcCSCPoints;
  iEvent.getByLabel(rpcCSCPointsLabel,rpcCSCPoints);

  float cluSize = 0;
  
  RPCRecHitCollection::const_iterator rpcPoint;

  //DTPart

  for(rpcPoint = rpcDTPoints->begin(); rpcPoint != rpcDTPoints->end(); rpcPoint++){
    LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
    RPCDetId  rpcId = rpcPoint->rpcId();
    typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
    rangeRecHits recHitCollection =  rpcHits->get(rpcId);
    if(recHitCollection.first==recHitCollection.second){
      std::cout<<"DT passed, no rechits for this RPCId =  "<<rpcId<<std::endl;
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
      std::cout<<"DT passed, RecHits but far away "<<rpcId<<std::endl;
      return true;
    }
  }

  //CSCPart

  for(rpcPoint = rpcCSCPoints->begin(); rpcPoint != rpcCSCPoints->end(); rpcPoint++){
    LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
    RPCDetId  rpcId = rpcPoint->rpcId();
    typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
    rangeRecHits recHitCollection =  rpcHits->get(rpcId);
    if(recHitCollection.first==recHitCollection.second){
      std::cout<<"CSC passed, no rechits for this RPCId =  "<<rpcId<<std::endl;
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
      std::cout<<"CSC passed, RecHits but far away "<<rpcId<<std::endl;
      return true;
    }
  }

  std::cout<<" skiped"<<std::endl;
  return false;
}




// ------------ method called once each job just before starting event loop  ------------
void 
RPCPathChambFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCPathChambFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCPathChambFilter);
