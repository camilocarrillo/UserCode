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
// $Id: TrackRPC.cc,v 1.8 2010/04/15 14:35:09 carrillo Exp $
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

#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>


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

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

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

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

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

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "SUSYBSMAnalysis/HSCP/src/BetaFromRPC.cc"

//Root

#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include <fstream>
#include "TGraphErrors.h"

//
// class decleration
//

class TrackRPC : public edm::EDAnalyzer {
   public:
      explicit TrackRPC(const edm::ParameterSet&);
      ~TrackRPC();
  
      edm::ESHandle<RPCGeometry> rpcGeo;

   private:
  virtual void beginRun(const edm::Run&,const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      std::string  m_trackTag;
      edm::InputTag m_muonsTag;
      edm::InputTag m_muonsTOFTag;
      std::string TjInput;
      std::string thePropagatorName;
      float minTkP, minDtP, maxTkBeta, minDR, maxInvPtDiff, maxChi2;

      edm::InputTag partLabel;

      std::string rootFileName;

      int partid;


      
      TFile* theFile;

      TH1F * statistics;

      TH1F * mass;
  
      TH1F * expectedeta;
      TH1F * expectedphi;
      TH1F * expectedbeta;
      TH1F * expectedp;

      TH1F * observedeta;
      TH1F * observedphi;
      TH1F * observedbeta;
      TH1F * observedp;

      TH1F * trackobservedeta;
      TH1F * trackobservedphi;
      TH1F * trackobservedbeta;
      TH1F * trackobservedp;

      TH1F * residualeta;
      TH1F * residualphi;
      TH1F * residualbeta;
      TH1F * residualp;

      TH1F * trackresidualeta;
      TH1F * trackresidualphi;
      TH1F * trackresidualp;
  
      TH2F * residualbetaVsEta;
      TH2F * residualbetaVsKnees;
      TH2F * residualbetaVsbeta;
  
              
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
  partLabel = iConfig.getParameter<edm::InputTag>("partLabel");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
  partid = iConfig.getUntrackedParameter<int>("partid"); 

}


TrackRPC::~TrackRPC()
{
  
}

//
// member functions
//

float gamma(float b){//gamma from beta
  if(b<1 && b>0){
    return 1./sqrt(1-b*b);
  }else{
    std::cout<<"error in the estimation of b="<<b<<std::endl;
    return 0;
  }
}

float betapm(float p,float m){//beta from mass and 3 momentum
  float beta = 1./sqrt(1+((m*m)/(p*p)));
  if(beta<=1 && beta>=0){
    return beta;
  }else{
    std::cout<<"p and m are not relativistic variables=p"<<p<<" m="<<m<<std::endl;
    return 0;
  }
}

// ------------ method called to for each event  ------------
void
TrackRPC::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  statistics->Fill(1);
  
  std::cout<<"Reading the particles container"<<std::endl;

  edm::Handle<edm::HepMCProduct> genParticles;
  iEvent.getByLabel(partLabel, genParticles);

  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(genParticles->GetEvent()));

  
  // std::cout<<"Number of Particles in this event: " << genParticles->size() << std::endl;

  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;
  
  for(HepMC::GenEvent::particle_iterator partIt = myGenEvent->particles_begin();
      partIt != myGenEvent->particles_end(); ++partIt ){
    //std::cout<<"Particle Id="<<partIt->pdgId()<<std::endl;
    float etamc=0;
    float phimc=0;
    float betamc=0;
    float pmc=0;
    float mmc=0;
    
    if((*partIt)->pdg_id()==partid){
      std::cout<<"This event contains one HSCP"<<std::endl;
      statistics->Fill(2);

      float e=sqrt ( (*partIt)->momentum().mag()*(*partIt)->momentum().mag() + (*partIt)->generated_mass()* (*partIt)->generated_mass() );

      float pt = (*partIt)->momentum().perp();
      //float betaT=pt/e;
      pmc=(*partIt)->momentum().mag();

      betamc=pmc/e;

      int event = iEvent.id().event();
      etamc = (*partIt)->momentum().eta();
      phimc = (*partIt)->momentum().phi();

      mmc=sqrt(e*e-pmc*pmc);

      if(abs(partid) == 2000015){
	betamc = betapm(pmc,303.27); //bug in random gun for kktaus
	mmc = 303.27;
	std::cout<<"warning correcting theoretical beta and mass for kktaus due to the error on the mass for the sample"<<std::endl;
      }
      
      std::cout<<"Filling expected"<<std::endl;

      expectedeta->Fill(etamc);
      expectedphi->Fill(phimc);
      expectedbeta->Fill(betamc);
      expectedp->Fill(pmc);
      
      std::cout<<"ev="<<event<<" phimc="<<(*partIt)->momentum().phi()<<" etamc="<<etamc<<" betamc="<<betamc<<" pmc="<<pmc<<"GeV pt="<<pt<<"GeV mmc="<<mmc<<"GeV"<<std::endl;
      
    }else{
      continue;
    }
    
    float tracketa=0;
    float trackphi=0;
    float trackp=0;
    float mindR=999999;
    float mindiffeta=9999999;
    float mindiffphi=9999999;
    float mindiffp=9999999;
    
    std::cout<<"\t Loop on all the reconstructed muons"<<std::endl;
    std::cout<<"\t We found "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;

    //loop just to check the reconstructed track
    
    reco::TrackCollection::const_iterator matchedTrack;

    for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
      tracketa=muon->eta();
      trackphi=muon->phi();
      trackp=muon->p();

      float diffeta = etamc - tracketa;
      float diffphi = phimc - trackphi;
      float diffp = pmc - trackp;
      
      float dR = sqrt(diffeta*diffeta+diffphi*diffphi);

      if(dR<mindR){
	mindR = dR;
	mindiffphi = diffphi;
	mindiffeta = diffeta;
	mindiffp = diffp;
	matchedTrack = muon;
      }
    }
    
    if(fabs(mindiffeta)<=0.3 && fabs(mindiffphi)<=0.03){ //assertion in the same cone?
      std::cout<<"\t \t \t Coincidence TRACK WITH MC candidate"<<std::endl;
      trackobservedeta->Fill(etamc);
      trackobservedphi->Fill(phimc);
      trackobservedbeta->Fill(betamc);
      trackobservedp->Fill(pmc);
      trackresidualphi->Fill(mindiffphi);
      trackresidualeta->Fill(mindiffeta);
      trackresidualp->Fill(mindiffp);
    }
    
    float eta=0;
    float phi=0;
    float p=0;
    float beta = 1;
    float knees = 1;
    
    //loop just to check the RPC Candidate
  
    for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
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

      std::cout<<"\t \t phimc="<<phimc<<" etamc="<<etamc<<std::endl;
      std::cout<<"\t \t phi  ="<<phi<<" eta  ="<<eta<<std::endl;
      std::cout<<"\t \t Loop on the rechits"<<std::endl;
      HSCPRPCRecHits.clear();
      for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit){
	//std::cout<<"\t \t Is an RPCRecHit?"<<(*recHit)->geographicalId().subdetId()<<std::endl;
	if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue;
	//std::cout<<"\t \t Is a valid rechit"<<std::endl;
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
      bool outOfTime = false;
      bool increasing = true;
      bool anydifferentzero = true;
      bool anydifferentone = true;

      if(HSCPRPCRecHits.size()==0){
	continue;
	std::cout<<"\t NO RPC RecHits in this muon!!!"<<std::endl;
      }      
     
      std::cout<<"\t \t loop on the RPCHit4D!!!"<<std::endl;
      for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
	float r=point->gp.mag();
	outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0
	increasing &= (point->bx>=lastbx); //condition 2: BX must be increase when going inside-out.
	anydifferentzero &= (!point->bx==0); //to check one knee withoutzeros
	anydifferentone &= (!point->bx==1); //to check one knee withoutones
	lastbx = point->bx;
	std::cout<<"\t \t  r="<<r<<" phi="<<point->gp.phi()<<" eta="<<point->gp.eta()<<" bx="<<point->bx<<" outOfTime"<<outOfTime<<" increasing"<<increasing<<" anydifferentzero"<<anydifferentzero<<std::endl;
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

      
      bool Candidate = (outOfTime&&increasing);

      std::cout<<"\t \t Is an HSCP?"<<std::endl;

      if(Candidate){
	statistics->Fill(3);
	std::cout<<"\t \t \t yes! We found an HSCPs let's try to estimate beta"<<std::endl;
	// here we should get some pattern-based estimate

	BetaFromRPC BetaClass(HSCPRPCRecHits);
	beta = BetaClass.beta();
	knees = BetaClass.knees();

	std::cout<<"\t \t \t beta = "<<beta<<" "<<"knees = "<<knees<<std::endl;
      }else{
	std::cout<<"\t \t \t No we didn't find an HSCPs"<<std::endl;
      }
    
      if(Candidate){
	std::cout<<"\t \t \t Now filling residuals and efficiency histograms if muon matches with an HSCP"<<std::endl;
	
	std::cout<<"\t \t \t etamc="<<etamc<<" phimc="<<phimc<<" betamc="<<betamc<<" pmc="<<pmc<<std::endl;
	std::cout<<"\t \t \t eta  ="<<eta<<" phi  ="<<phi<<" beta  ="<<beta<<" p  ="<<p<<std::endl;
	
      	float diffeta = etamc - eta;
	float diffphi = phimc - phi;
	float diffbeta = betamc - beta;
	float diffp = pmc - p;
	
	if(fabs(diffeta)<=0.3 && fabs(diffphi)<=0.03){ //assertion in the same cone?
	  std::cout<<"\t \t \t Coincidence candidate with MC"<<std::endl;
	  observedeta->Fill(etamc);
	  observedphi->Fill(phimc);
	  observedbeta->Fill(betamc);
	  observedp->Fill(pmc);
	  residualphi->Fill(diffphi);
	  residualeta->Fill(diffeta);
	  residualbeta->Fill(diffbeta);
	  residualp->Fill(diffp);
	  residualbetaVsEta->Fill(etamc,diffbeta);
	  residualbetaVsKnees->Fill(knees,diffbeta);
	  residualbetaVsbeta->Fill(betamc,diffbeta);
	  
	  //Estimation of the mass
	  std::cout<<"\t \t \t Estimating the mass"<<std::endl;
	  float m=p/(gamma(beta)*beta);
	  std::cout<<"\t \t \t mmc="<<mmc<<std::endl;
	  std::cout<<"\t \t \t m  ="<<m<<std::endl;
	  mass->Fill(m);
	}else{
	  std::cout<<"\t \t \t Identified but in different direction this is noise!"<<std::endl;
	}
      }else{
	std::cout<<"\t \t \t Muon Not matched with an HSCP in MC"<<std::endl;
      }
    }
  }
}
// ------------ method called once each job just before starting event loop  ------------
void 
TrackRPC::beginRun(const edm::Run&,const edm::EventSetup& iSetup)
  {
    iSetup.get<MuonGeometryRecord>().get(rpcGeo);
    
    theFile = new TFile(rootFileName.c_str(),"RECREATE");

    statistics = new TH1F("statistics","Some Information",10,0.5,10.5);		 
    mass = new TH1F("mass","Mass estimation",75,0,1500);		 
    
    expectedeta = new TH1F("EtaExpected","Eta Expected",100,-2.5,2.5);		 
    expectedphi = new TH1F("PhiExpected","Phi Expected",100,-3.1415926,3.1415926); 
    expectedbeta = new TH1F("BetaExpected","Beta Expected",100,0,1);                
    expectedp = new TH1F("PExpected","P Expected",100,0,1500);
    
    observedeta = new TH1F("EtaObserved","Eta Observed",100,-2.5,2.5);		 
    observedphi = new TH1F("PhiObserved","Phi Observed",100,-3.1415926,3.1415926); 
    observedbeta = new TH1F("BetaObserved","Beta Observed",100,0,1);                
    observedp = new TH1F("PObserved","P Observed",100,0,1500);    

    residualeta = new TH1F("ResidualEta","Eta Residuals",25,-0.2,0.2);
    residualphi = new TH1F("ResidualPhi","Phi Residuals",100,-0.05,0.05);
    residualbeta = new TH1F("ResidualBeta","Beta Residuals",25,-0.5,0.5);
    residualp = new TH1F("ResidualP","P Residuals",100,-750,750);

    trackobservedeta = new TH1F("trackEtaObserved","Eta Observed",100,-2.5,2.5);		 
    trackobservedphi = new TH1F("trackPhiObserved","Phi Observed",100,-3.1415926,3.1415926); 
    trackobservedbeta = new TH1F("trackBetaObserved","Beta Observed",100,0,1);                
    trackobservedp = new TH1F("trackPObserved","P Observed",100,0,1500);    

    trackresidualeta = new TH1F("trackResidualEta","Eta Residuals",25,-0.2,0.2);
    trackresidualphi = new TH1F("trackResidualPhi","Phi Residuals",100,-0.05,0.05);
    trackresidualp = new TH1F("trackResidualP","P Residuals",100,-750,750);
    
    residualbetaVsEta = new TH2F ("ResidualBetaVsEta","ResidualBetaVsEta",50,-2.5,2.5,25,-0.5,0.5);
    residualbetaVsKnees = new TH2F ("residualbetaVsKnees","residualbetaVsKnees",3,-0.5,3.5,25,-0.5,0.5);
    residualbetaVsbeta = new TH2F ("residualbetaVsbeta","residualbetaVsbeta",10,0.,1.,25,-0.5,0.5);
  }

void 
TrackRPC::endJob() {
  std::cout<<"Starging the endjob"<<std::endl;

  theFile->cd();

  std::cout<<"saving root files"<<std::endl;
  
  statistics->Write();
  mass->Write();
  
  expectedeta->Write();
  expectedphi->Write();
  expectedbeta->Write();  
  expectedp->Write();

  observedeta->Write();
  observedphi->Write();
  observedbeta->Write();
  observedp->Write();

  residualeta->Write();
  residualphi->Write();
  residualbeta->Write();
  residualp->Write();

  trackobservedeta->Write();
  trackobservedphi->Write();
  trackobservedbeta->Write();
  trackobservedp->Write();

  trackresidualeta->Write();
  trackresidualphi->Write();
  trackresidualp->Write();

  residualbetaVsEta->Write();
  residualbetaVsKnees->Write();
  residualbetaVsbeta->Write();
  
  theFile->Close();

}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackRPC);
