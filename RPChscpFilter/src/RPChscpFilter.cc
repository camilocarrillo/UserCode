// -*- C++ -*-
//
// Package:    RPChscpFilter
// Class:      RPChscpFilter
// 
/**\class RPChscpFilter RPChscpFilter.cc RPCHSCPFilter/RPChscpFilter/src/RPChscpFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Thu Jun 10 11:34:48 CEST 2010
// $Id: RPChscpFilter.cc,v 1.3 2010/06/14 16:28:46 carrillo Exp $
//
//


// system include files
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include "FWCore/ParameterSet/interface/InputTag.h"
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "RecoMuon/MeasurementDet/interface/MuonDetLayerMeasurements.h"
#include "TrackingTools/PatternTools/interface/TrajMeasLessEstim.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/Navigation/interface/DirectMuonNavigation.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "TrackingTools/MeasurementDet/interface/TrajectoryMeasurementGroup.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/RPCGeometry/interface/RPCRoll.h> 
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCParticle.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "TFile.h"
#include "TH1F.h"
//
// class declaration
//

class RPChscpFilter : public edm::EDFilter {
   public:
  explicit RPChscpFilter(const edm::ParameterSet& );
      ~RPChscpFilter();
      edm::ESHandle<RPCGeometry> rpcGeo;
      std::vector<unsigned int> blacklist;
      bool firstbook;
      TFile * theFileCal;
      TH1F * theHisto;
      std::string  m_trackTag;
      std::string rootFileNameCal;
      int MinRPCRecHits;
      double synchth;
      double minIntegral;
      double minMean;
  private:
      virtual void beginJob();
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endRun() ;
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
RPChscpFilter::RPChscpFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  MinRPCRecHits = iConfig.getUntrackedParameter<int>("MinRPCRecHits");
  rootFileNameCal =iConfig.getUntrackedParameter<std::string>("rootFileNameCal");
  synchth = iConfig.getUntrackedParameter<double>("synchth");
  minIntegral = iConfig.getUntrackedParameter<double>("minIntegral");
  minMean = iConfig.getUntrackedParameter<double>("minMean");

}


RPChscpFilter::~RPChscpFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------

bool IsBadRoll(uint32_t rawId,std::vector<uint32_t> thelist){
  bool isBadRoll = false;
  if(!(find(thelist.begin(),thelist.end(),rawId)==thelist.end())){
    isBadRoll=true;
  }
  return isBadRoll;
}

bool
RPChscpFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 
  if(firstbook){
  firstbook = false;

  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  theFileCal = new TFile(rootFileNameCal.c_str());
  
  if(!theFileCal) std::cout<<"The File Doesn't exist"<<std::endl;

  blacklist.clear();
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it );
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
        RPCDetId rpcId = (*r)->id();
        RPCGeomServ rpcsrv(rpcId);
	std::string nameRoll = rpcsrv.name();
	std::string meIdRES,folder;
        folder = "DQMData/BXMuon_";
        meIdRES = folder + nameRoll;
        theHisto = (TH1F*)theFileCal->Get(meIdRES.c_str());
	float ratio = 0;
	int noGoodHits = theHisto->Integral()-theHisto->GetBinContent(6);
	if(theHisto->GetBinContent(6)!=0) ratio = float(noGoodHits)/float(theHisto->GetBinContent(6));
        if(theHisto->Integral()<minIntegral) std::cout<<"NotEnoughMuonHits_for "<<nameRoll<<std::endl;
        if(ratio>synchth) std::cout<<"S "<<nameRoll<<" ratio="<<ratio<<std::endl;
        if(ratio>synchth  && theHisto->Integral() >= minIntegral) std::cout<<"SI "<<nameRoll<<" ratio"<<ratio<<" integral="<<theHisto->Integral()<<std::endl;
        if(ratio>synchth  && theHisto->Integral() >= minIntegral && fabs(theHisto->GetMean()) >= minMean){
	  std::cout<<"SIM "<<nameRoll<<" ratio="<<ratio<<" integral="<<theHisto->Integral()<<" mean="<<theHisto->GetMean()<<std::endl;
	  blacklist.push_back(rpcId.rawId());
	}
      }
    }
  }
  std::cout<<"Number of rolls in black list = "<<blacklist.size()<<std::endl;
  }

  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;

  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
	
  int counter = 0;
  float eta=0;
  float phi=0;
  float p=0;
    

  std::cout<<"\t Loop on all the reconstructed muons"<<std::endl;
  std::cout<<"\t We found "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;
  for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
    counter++;
    std::cout<<"counter = "<<counter<<std::endl;
    
    std::cout<<"going"<<std::endl;
    
    eta=muon->eta();
    phi=muon->phi();
    p=muon->p();

    int rechitcounter = 0;
    for(trackingRecHit_iterator recHit2 = muon->recHitsBegin(); recHit2 != muon->recHitsEnd(); ++recHit2) {
      rechitcounter++;
    }

    if(rechitcounter==0){
      std::cout<<"!!!!!!!!!!!!No recHits in this track"<<std::endl;
    }
    std::cout<<"\t \t Rechitcounter in this muon = "<<rechitcounter<<std::endl;
    std::cout<<"\t \t phi  ="<<phi<<" eta  ="<<eta<<std::endl;
    std::cout<<"\t \t Loop on the rechits"<<std::endl;
    
    HSCPRPCRecHits.clear();
    for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit){
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue;
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue;
      if (!(*recHit)->isValid()) continue;
      if(IsBadRoll((RPCDetId)(*recHit)->geographicalId().rawId(),blacklist)) continue;
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      LocalPoint recHitPos=(*recHit)->localPosition();
      const RPCRoll* rollasociated = rpcGeo->roll(rollId); 
      const BoundPlane & RPCSurface = rollasociated->surface();
      susybsm::RPCHit4D ThisHit;
      ThisHit.bx = ((RPCRecHit*)(&(**recHit)))->BunchX();
      ThisHit.gp = RPCSurface.toGlobal(recHitPos);
      ThisHit.id = (RPCDetId)(*recHit)->geographicalId().rawId();
      HSCPRPCRecHits.push_back(ThisHit);
    }
    
    // here we go on with  the RPC procedure                                                                                                                          
    std::sort(HSCPRPCRecHits.begin(), HSCPRPCRecHits.end());
    int lastbx=-7;
    bool outOfTime = false;
    bool increasing = true;
    bool anydifferentzero = true;
    bool anydifferentone = true;
    
    if(HSCPRPCRecHits.size()<MinRPCRecHits){
      std::cout<<"\t Less than"<<MinRPCRecHits<<"RecHits in this muon!!! = "<<HSCPRPCRecHits.size()<<std::endl;
      continue;
    }

    std::cout<<"Number of RPC Hits for this Muon Track"<<HSCPRPCRecHits.size()<<std::endl;
    
    std::cout<<"\t \t loop on the RPCHit4D!!!"<<std::endl;
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      float r=point->gp.mag();
      outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0                                                                           
      increasing &= (point->bx>=lastbx); //condition 2: BX must be increase when going inside-out.                                                                   
      anydifferentzero &= (!point->bx==0); //to check one knee withoutzeros                                                                                          
      anydifferentone &= (!point->bx==1); //to check one knee withoutones                                                                                            
      lastbx = point->bx;
      std::cout<<"\t \t  r="<<r<<" phi="<<point->gp.phi()<<" eta="<<point->gp.eta()<<" bx="<<point->bx<<" outOfTime"<<outOfTime<<" increasing"<<increasing<<" anyddfferentzero"<<anydifferentzero<<point->id<<std::endl;
    }
    std::cout<<"\t \t";

    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      std::cout<<point->bx;
    }
    std::cout<<std::endl;
    
    bool pp = true;

    float delay = 0;
    if(pp){
      delay=12.5; //half bunch crossing delay for pp collisions                                                                                                          }
    }
    
    bool Candidate = (outOfTime&&increasing);

    std::cout<<"\t \t Is an HSCP?"<<std::endl;

    if(Candidate){
      std::cout<<"\t \t \t yes! We found an HSCPs let's try to estimate beta"<<std::endl;
      return true;
      // here we should get some pattern-based estimate  
    }
  }
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPChscpFilter::beginJob(){
  std::cout<<"Begin Job"<<std::endl;
  firstbook = true;
}

void
RPChscpFilter::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::cout<<"Begin Run"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------

void 
RPChscpFilter::endRun(){
  std::cout<<"end Run"<<std::endl;
}

void 
RPChscpFilter::endJob(){
  std::cout<<"end Job"<<std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPChscpFilter);
