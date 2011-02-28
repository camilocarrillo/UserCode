// -*- C++ -*-
//
// Package:    RPCcosmicFilter
// Class:      RPCcosmicFilter
// 
/**\class RPCcosmicFilter RPCcosmicFilter.cc RPCHSCPFilter/RPCcosmicFilter/src/RPCcosmicFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Thu Jun 10 11:34:48 CEST 2010
// $Id: RPCcosmicFilter.cc,v 1.5 2010/10/31 13:30:27 carrillo Exp $
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
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"
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
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
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

class RPCcosmicFilter : public edm::EDFilter {
   public:
  explicit RPCcosmicFilter(const edm::ParameterSet& );
      ~RPCcosmicFilter();
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
      edm::InputTag rpcRecHitsLabel;
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
RPCcosmicFilter::RPCcosmicFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  MinRPCRecHits = iConfig.getUntrackedParameter<int>("MinRPCRecHits");
  rootFileNameCal =iConfig.getUntrackedParameter<std::string>("rootFileNameCal");
  synchth = iConfig.getUntrackedParameter<double>("synchth");
  minIntegral = iConfig.getUntrackedParameter<double>("minIntegral");
  minMean = iConfig.getUntrackedParameter<double>("minMean");
}


RPCcosmicFilter::~RPCcosmicFilter()
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


float nullifbacktoback(float phi1,float phi2){
  float diffphi = fabs(phi1 - phi2);
  if(diffphi>3.14159265358979) return 2*3.14159265358979-diffphi-3.14159265358979;
  else if(diffphi < -3.14159265358979) return 2*3.1415926535+diffphi-3.14159265358979;
  else return diffphi-3.14159265358979;
}

bool
RPCcosmicFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
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
        if(theHisto->Integral()<minIntegral) //std::cout<<"NotEnoughMuonHits_for "<<nameRoll<<std::endl;
        if(ratio>synchth) //std::cout<<"S "<<nameRoll<<" ratio="<<ratio<<std::endl;
        if(ratio>synchth  && theHisto->Integral() >= minIntegral) //std::cout<<"SI "<<nameRoll<<" ratio"<<ratio<<" integral="<<theHisto->Integral()<<std::endl;
        if(ratio>synchth  && theHisto->Integral() >= minIntegral && fabs(theHisto->GetMean()) >= minMean){
	  //std::cout<<"SIM "<<nameRoll<<" ratio="<<ratio<<" integral="<<theHisto->Integral()<<" mean="<<theHisto->GetMean()<<std::endl;
	  blacklist.push_back(rpcId.rawId());
	}
      }
    }
  }
  std::cout<<"Number of rolls in black list = "<<blacklist.size()<<std::endl;
  }

  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);

  std::cout <<"\t Getting the RPC RecHits"<<std::endl;
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);
  
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;

  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
	
  int counter = 0;
  float eta=0;
  float phi=0;
  float p=0;
    

  std::cout<<"\t Loop on all the reconstructed muons"<<std::endl;
  std::cout<<"\t There are "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;

  bool cosmic = false;

  if(trackCollectionHandle->size()>=2)
    for (reco::TrackCollection::const_iterator leg1 = trackCollectionHandle->begin(); leg1!=trackCollectionHandle->end(); leg1++){
      for (reco::TrackCollection::const_iterator leg2 = leg1+1; leg2!=trackCollectionHandle->end(); leg2++){
	float deltaphi = fabs(nullifbacktoback(leg1->phi(),leg2->phi()));
	std::cout<<" deltaphi = "<<deltaphi<<std::endl;
	if(deltaphi<=0.02 && deltaphi>0){
	  std::cout<<"Probably we got a cosmic in this envet"<<std::endl;
	  cosmic = true;
 	}
      }
    }
  
  for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
    counter++;
    
    eta=muon->eta();
    phi=muon->phi();
    p=muon->p();

    std::cout<<"Muon muon->chi2() = "<<muon->chi2()<<std::endl;
    std::cout<<"Muon muon->chi2()/ndof = "<<muon->chi2()/muon->ndof() <<std::endl;

    if(muon->chi2()/muon->ndof()>40){
      std::cout<<"Event skiped because of muon->chi2/ndof = "<<muon->chi2()/muon->ndof()<<std::endl;
      continue; //Is the Muon chi2/ndof smaller than 20.      
    }
    
    std::cout<<" muon->pt = "<<muon->pt()<<" GeV dxy = "<<muon->dxy()<<std::endl;

    if(muon->pt()<30.){ 
      std::cout<<"Event skiped because of muon->pt = "<<muon->pt()<<std::endl;
      continue; //Is the Muon pt smaller than 30GeV.
    }
    if(fabs(muon->dxy()) > 0.25){
      std::cout<<"Event skiped because of muon->dxy = "<<muon->dxy()<<std::endl;
      continue;  //Is the transverse impact parameter bigger than 0.25cm?.
    }

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
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue; //Is a hit in the Muon System?
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue; //Is an RPC Hit?
      if (!(*recHit)->isValid()) continue; //Is Valid
      if(IsBadRoll((RPCDetId)(*recHit)->geographicalId().rawId(),blacklist)) continue; //The Hit belongs to a good roll.?
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      std::cout<<"Getting RecHits in Roll Asociated"<<std::endl;
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  rpcHits->get(rollId);
      RPCRecHitCollection::const_iterator recHitC;
      int size = 0;
      int clusterS=0;
      for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) {
	clusterS=(*recHitC).clusterSize(); 
	size++;
      }
      if(size>1) continue; //Is the only RecHit in this roll.?
      if(clusterS>4) continue; //Is the Cluster Size 5 or bigger? 
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
    bool allnegative = true;
    bool allpositive = true;
    
    if((int) HSCPRPCRecHits.size()<MinRPCRecHits){
      std::cout<<"\t Less than"<<MinRPCRecHits<<"RecHits in this muon!!! = "<<HSCPRPCRecHits.size()<<std::endl;
      continue;
    }

    std::cout<<"Number of RPC Hits for this Muon Track = "<<HSCPRPCRecHits.size()<<std::endl;
    
    std::cout<<"\t \t loop on the RPCHit4D!!!"<<std::endl;
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      float r=point->gp.mag();
      outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0                                                                           
      increasing &= (point->bx==lastbx || point->bx==lastbx+1 || lastbx ==-7); //condition 2: BX must be increase when going inside-out.                                                                   

      allpositive &= (point->bx>=0); //condition 3: None of them can be negative

      allnegative &= (point->bx<0); //condition 4: Not all the BX can be negative

      lastbx = point->bx;
      std::cout<<"\t \t  r="<<r<<" phi="<<point->gp.phi()<<" eta="<<point->gp.eta()
	       <<" bx="<<point->bx<<" lastbx="<<lastbx<<" outOfTime"<<outOfTime
	       <<" increasing"<<increasing<<" "<<point->id
	       <<" allnegative "<<allnegative<<" allpositive "<<allpositive<<std::endl;
    }
    
    std::cout<<"\t \t";

    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      std::cout<<point->bx;
    }
    std::cout<<std::endl;
    
    bool pp = true;
    float delay = 0;
    if(pp){
      delay=12.5; //half bunch crossing delay for pp collisions
    }
    
    bool Candidate = (outOfTime&&increasing&&!cosmic&&!allnegative&&allpositive);

    std::cout<<"\t \t Is an HSCP?"<<std::endl;

    if(Candidate){
      std::cout<<"\t \t \t yes! We found an HSCPs let's try to estimate beta"<<std::endl;
      return true;
      // here we should get some pattern-based estimate  
    }else{
      std::cout<<"\t \t \t NO! any of these is false outOfTime&&increasing&&!cosmic&&!allnegative "<<std::endl;
    }
  }
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCcosmicFilter::beginJob(){
  std::cout<<"Begin Job"<<std::endl;
  firstbook = true;
}

void
RPCcosmicFilter::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::cout<<"Begin Run"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------

void 
RPCcosmicFilter::endRun(){
  std::cout<<"end Run"<<std::endl;
}

void 
RPCcosmicFilter::endJob(){
  std::cout<<"end Job"<<std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCcosmicFilter);
