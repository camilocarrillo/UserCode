// -*- C++ -*-
//
// Package:    TrackRPC
// Class:      TrackRPC
// 
/**\class TrackRPC TrackRPC.cc track/TrackRPC/src/TrackRPC.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon May 18 16:59:36 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"


#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "RecoMuon/MeasurementDet/interface/MuonDetLayerMeasurements.h"
#include "TrackingTools/KalmanUpdators/interface/Chi2MeasurementEstimator.h"
#include "TrackingTools/PatternTools/interface/TrajMeasLessEstim.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "TrackingTools/MeasurementDet/interface/TrajectoryMeasurementGroup.h"

#include "RecoMuon/Navigation/interface/DirectMuonNavigation.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h" 
#include "TrackingTools/KalmanUpdators/interface/Chi2MeasurementEstimator.h" 
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"

#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "TrackingTools/MeasurementDet/interface/TrajectoryMeasurementGroup.h"

#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h> 
#include <Geometry/RPCGeometry/interface/RPCRoll.h> 
#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCParticle.h"

#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>

//
// class decleration
//

class TrackRPC : public edm::EDAnalyzer {
   public:
      explicit TrackRPC(const edm::ParameterSet&);
      ~TrackRPC();

      edm::ESHandle<RPCGeometry> rpcGeo;

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      std::string  m_trackTag;
      edm::InputTag m_muonsTag;
      edm::InputTag m_muonsTOFTag;
      std::string TjInput;
      std::string thePropagatorName;
      float minTkP, minDtP, maxTkBeta, minDR, maxInvPtDiff, maxChi2;

     
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
TrackRPC::TrackRPC(const edm::ParameterSet& iConfig)
{
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  //  m_muonsTag = iConfig.getParameter<edm::InputTag>("muons");
  //  m_muonsTOFTag = iConfig.getParameter<edm::InputTag>("muonsTOF");

  //  maxChi2=iConfig.getParameter<double>("maxTkChi2"); //5
}


TrackRPC::~TrackRPC()
{
  
}

//
// member functions
//

// ------------ method called to for each event  ------------
void
TrackRPC::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // information from the muon system: TOF
  // information from the tracker: dE/dx
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;

  std::cout<<"We found "<<trackCollectionHandle->size()<<" tracks"<<std::endl;
  
  for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
    
    std::cout<<" phi="<<muon->phi()
	     <<" eta="<<muon->eta()
	     <<" pt="<<muon->pt()<<std::endl;

    int rechitcounter = 0;
    for(trackingRecHit_iterator recHit2 = muon->recHitsBegin(); recHit2 != muon->recHitsEnd(); ++recHit2) {
      rechitcounter++;
    }

    if(rechitcounter==0){ std::cout<<"No Rec recHits in this track"<<std::endl; continue;}
    
    std::cout<<"\t Rechitcounter = "<<rechitcounter<<std::endl;

    for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit) {
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue;
      if (!(*recHit)->isValid()) continue;
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      RPCGeomServ rpcsrv(rollId);
      LocalPoint recHitPos=(*recHit)->localPosition();

      const RPCRoll* rollasociated = rpcGeo->roll(rollId);
      const BoundPlane & RPCSurface = rollasociated->surface();
     
      susybsm::RPCHit4D ThisHit;
      ThisHit.bx = ((RPCRecHit*)(&(**recHit)))->BunchX();
      ThisHit.gp = RPCSurface.toGlobal(recHitPos);
      ThisHit.id = (RPCDetId)(*recHit)->geographicalId().rawId();
      HSCPRPCRecHits.push_back(ThisHit);
    }
    
    // here we go on with the RPC procedure 
    std::sort(HSCPRPCRecHits.begin(), HSCPRPCRecHits.end());
    int lastbx=-7;
    bool decreasing = true;
    bool outOfTime = false;
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0
      decreasing &= (point->bx>=lastbx); //condition 2: BX must be increase when going inside-out.
      lastbx = point->bx;
      float r=sqrt((point->gp.x())*(point->gp.x())+(point->gp.y())*(point->gp.y())+(point->gp.z())*(point->gp.z()));
      std::cout<<" r="<<r<<"-bx="<<point->bx<<" outOfTime"<<outOfTime<<" decreasing"<<decreasing<<std::endl;
    }
    std::cout<<"pattern "<<std::endl;
    
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      std::cout<<point->bx;
    }
    std::cout<<std::endl;

    bool Candidate = (outOfTime&&decreasing);
    float beta = 1; // here we should get some pattern-based estimate
    
    if(Candidate){
      std::cout<<"We found an HSCPs"<<std::endl;
    }
  }
}
// ------------ method called once each job just before starting event loop  ------------
void 
TrackRPC::beginJob(const edm::EventSetup& iSetup)
  {
    iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  }

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackRPC::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackRPC);
