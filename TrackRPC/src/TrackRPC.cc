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

//Root

#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include <fstream>

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

      std::string partLabel;

      std::string rootFileName;
      
      TFile* theFile;

      TH1F * statistics;
  
      TH1F * efficiencyeta;
      TH1F * efficiencyphi;
      TH1F * efficiencybeta;

      TH1F * expectedeta;
      TH1F * expectedphi;
      TH1F * expectedbeta;

      TH1F * observedeta;
      TH1F * observedphi;
      TH1F * observedbeta;

      TH1F * residualeta;
      TH1F * residualphi;
      TH1F * residualbeta;

       
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
  partLabel = iConfig.getUntrackedParameter<std::string>("partLabel");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");


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
  statistics->Fill(1);
  
  std::cout<<"Reading the particles container"<<std::endl;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(partLabel,genParticles );
  
  std::cout << " Number of Particles in this event: " << genParticles->size() << std::endl;

  
  // information from the muon system: TOF
  // information from the tracker: dE/dx
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;
  
  std::cout<<"We found "<<trackCollectionHandle->size()<<" tracks"<<std::endl;

  reco::GenParticleCollection::const_iterator partIt;
  for(partIt=genParticles->begin();partIt!=genParticles->end();++partIt) {
    std::cout<<" Particle Id="<<partIt->pdgId()<<std::endl;
    float etamc=0;
    float phimc=0;
    float betamc=0;
    int partid = -2000015;
    if(partIt->pdgId()==partid){
      statistics->Fill(2);
      float p=partIt->p();
      float e=partIt->energy();
      float pt = partIt->pt();
      //float betaT=pt/e;
      
      betamc=p/e;

      int event = iEvent.id().event();
      etamc = partIt->eta();
      phimc = partIt->phi();
      
      std::cout<<"\t EVENT="<<event<<"    phi="<<partIt->phi()<<" etamc="<<etamc<<" betamc="<<betamc<<" p="<<p<<"GeV pt="<<pt<<"GeV m="<<sqrt(e*e-p*p)<<"GeV"<<std::endl;
      
    }else{
      std::cout<<"This is not a "<<partid<<" particle"<<std::endl;
      continue;
    }
    
    float eta=0;
    float phi=0;
    float beta = 1;
    
    std::cout<<"Loop on all the reconstructed muons"<<std::endl;

    for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
      eta=muon->eta();
      phi=muon->phi();
      
      std::cout<<" phi="<<phi
	       <<" eta="<<eta
	       <<" pt="<<muon->pt()<<std::endl;

      int rechitcounter = 0;
      for(trackingRecHit_iterator recHit2 = muon->recHitsBegin(); recHit2 != muon->recHitsEnd(); ++recHit2) {
	rechitcounter++;
      }

      if(rechitcounter==0){
	std::cout<<"No RPC Rec recHits in this track"<<std::endl; 
	continue;
      }
    
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
      bool outOfTime = false;
      bool increasing = true;
      bool anydifferentzero = true;
      bool anydifferentone = true;

      if(HSCPRPCRecHits.size()==0){
	continue;
	std::cout<<"no RPC RecHits in this muon"<<std::endl;
      }
      
      for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
	outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0
	increasing &= (point->bx>=lastbx); //condition 2: BX must be increase when going inside-out.
	anydifferentzero &= (!point->bx==0); //to check one knee withoutzeros
	anydifferentone &= (!point->bx==1); //to check one knee withoutones
	lastbx = point->bx;
	float r=point->gp.mag();
	std::cout<<" r="<<r<<" bx="<<point->bx<<" outOfTime"<<outOfTime<<" increasing"<<increasing<<" anydifferentzero"<<anydifferentzero<<std::endl;
      }
      std::cout<<"pattern "<<std::endl;
    
      for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
	std::cout<<point->bx;
      }
      std::cout<<std::endl;

      bool Candidate = (outOfTime&&increasing);

      if(Candidate){
	statistics->Fill(3);
	std::cout<<"We found an HSCPs let's try to stimate beta"<<std::endl;
	// here we should get some pattern-based estimate

	//Counting knees
	int lastbx=-7;
	int knees=0;
	float maginknee = 0;
	float maginfirstknee = 0;
	for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
	  if(lastbx==-7){
	    maginfirstknee = point->gp.mag();
	  }else if((lastbx!=point->bx)){
	    std::cout<<"one knee between"<<lastbx<<point->bx<<std::endl;
	    maginknee=point->gp.mag();
	    knees++;
	  }
	  lastbx=point->bx;
	}
      
	if(knees==0){
	  std::cout<<"knees="<<knees<<std::endl;
	  beta=maginfirstknee/(25+maginfirstknee/30.)/30.;
	}else if(knees==1){
	  float beta1=0;
	  float beta2=0;
	  std::cout<<"knees="<<knees<<std::endl;
	  std::cout<<" anydifferentzero="<<anydifferentzero<<" anydifferentone="<<anydifferentone<<std::endl;
	  if(!anydifferentzero){
	    beta=maginknee/(25+maginknee/30.)/30.;
	  }else if(!anydifferentone){//i.e non zeros and no ones
	    beta=maginknee/(50+maginknee/30.)/30.;
	  }else{
	    beta1=maginknee/(25+maginknee/30.)/30.;
	    float dr =(maginknee-maginfirstknee);
	    beta2 = dr/(25.+dr/30.);
	    std::cout<<"beta1="<<beta1<<" beta2="<<beta2<<std::endl;
	    beta = (beta1 + beta2)*0.5;
	  }
	}else if(knees==2){
	  std::cout<<"knees="<<knees<<std::endl;
	  knees=0;
	  float beta1=0;
	  float beta2=0;
	  lastbx=-7;
	  for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
	    if(lastbx==-7){
	      maginfirstknee = point->gp.mag();
	    }else if((lastbx!=point->bx)){
	      std::cout<<"one knee between"<<lastbx<<point->bx<<std::endl;
	      knees++;
	      if(knees==2){
		float maginsecondknee=point->gp.mag();
		beta1=maginknee/(25+maginknee/30.)/30.;
		float dr =(maginknee-maginsecondknee);
		beta2 = dr/(25.+dr/30.);
		std::cout<<"beta1="<<beta1<<" beta2="<<beta2<<std::endl;
	      }
	    }
	    lastbx=point->bx;
	  }
	  beta = (beta1 + beta2)*0.5;
	}
      
	std::cout<<"beta="<<beta<<std::endl;
      }else{
	std::cout<<"We didn't found an HSCPs"<<std::endl;
      }
    
      std::cout<<"etamc="<<etamc<<" phimc="<<phimc<<" betamc="<<betamc<<std::endl;
      expectedeta->Fill(etamc);
      expectedphi->Fill(phimc);
      expectedbeta->Fill(betamc);
      
      if(Candidate){
	std::cout<<"eta  ="<<eta<<" phi  ="<<phi<<" beta  ="<<beta<<std::endl;
      	float diffeta = etamc - eta;
	float diffphi = phimc - phi;
	float diffbeta = betamc - beta;
	
	if(fabs(diffeta)<=0.3 && fabs(diffphi)<=0.03){
	  std::cout<<"Coincidence!!"<<std::endl;
	  observedeta->Fill(eta);
	  observedphi->Fill(phi);
	  observedbeta->Fill(beta);
	  residualphi->Fill(diffphi);
	  residualeta->Fill(diffeta);
	  residualbeta->Fill(diffbeta);
	}else{
	  std::cout<<" Identified but in different direction"<<std::endl;
	}
      }else{
	std::cout<<" Muon Not mateched with an HSCP"<<std::endl;
      }
    }
  }
}
// ------------ method called once each job just before starting event loop  ------------
void 
TrackRPC::beginJob(const edm::EventSetup& iSetup)
  {
    iSetup.get<MuonGeometryRecord>().get(rpcGeo);


    theFile = new TFile(rootFileName.c_str(),"RECREATE");

    statistics = new TH1F("statistics","Some Information",10,0.5,10.5);		 
    
    efficiencyeta = new TH1F("EtaEff","Eta Efficiency",100,-2.5,2.5);		 
    efficiencyphi = new TH1F("PhiEff","Phi Efficiency",100,-3.1415926,3.1415926); 
    efficiencybeta = new TH1F("BetaEff","Beta Efficiency",100,0,1);                
    
    expectedeta = new TH1F("EtaExpected","Eta Expected",100,-2.5,2.5);		 
    expectedphi = new TH1F("PhiExpected","Phi Expected",100,-3.1415926,3.1415926); 
    expectedbeta = new TH1F("BetaExpected","Beta Expected",100,0,1);                
    
    observedeta = new TH1F("EtaObserved","Eta Observed",100,-2.5,2.5);		 
    observedphi = new TH1F("PhiObserved","Phi Observed",100,-3.1415926,3.1415926); 
    observedbeta = new TH1F("BetaObserved","Beta Observed",100,0,1);                
    
    residualeta = new TH1F("Residual Eta","Eta Residuals",100,-0.2,0.2);
    residualphi = new TH1F("Residual Phi","Phi Residuals",100,-0.05,0.05);
    residualbeta = new TH1F("Residual Beta","Beta Residuals",100,-0.5,0.5);

  }

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackRPC::endJob() {

  statistics->GetXaxis()->SetBinLabel(1,"Events");
  statistics->GetXaxis()->SetBinLabel(2,"Events with HSCP");
  statistics->GetXaxis()->SetBinLabel(3,"Events with HSCPs in Mu/RPC");
    
  for(int k=1;k<=100;k++){
    float effeta = 0;
    float erreta = 0;
    if(expectedeta->GetBinContent(k)!=0){
      effeta = observedeta->GetBinContent(k)/expectedeta->GetBinContent(k);
      erreta = sqrt(effeta*(1-effeta)/expectedeta->GetBinContent(k));
    }
    efficiencyeta->SetBinContent(k,effeta);
    efficiencyeta->SetBinError(k,erreta);
    
    float effphi = 0;
    float errphi = 0;
    if(expectedphi->GetBinContent(k)!=0){
      effphi = observedphi->GetBinContent(k)/expectedphi->GetBinContent(k);
      errphi = sqrt(effphi*(1-effphi)/expectedphi->GetBinContent(k));
    }
    efficiencyphi->SetBinContent(k,effphi);
    efficiencyphi->SetBinError(k,errphi);

    float effbeta = 0;
    float errbeta = 0;
    if(expectedbeta->GetBinContent(k)!=0){
      effbeta = observedbeta->GetBinContent(k)/expectedbeta->GetBinContent(k);
      errbeta = sqrt(effbeta*(1-effbeta)/expectedbeta->GetBinContent(k));
    }
    efficiencybeta->SetBinContent(k,effbeta);
    efficiencybeta->SetBinError(k,errbeta);
    

  }
  
  theFile->cd();

  statistics->Write();
  
  efficiencyeta->Write();
  efficiencyphi->Write();
  efficiencybeta->Write();

  expectedeta->Write();
  expectedphi->Write();
  expectedbeta->Write();

  observedeta->Write();
  observedphi->Write();
  observedbeta->Write();

  residualeta->Write();
  residualphi->Write();
  residualbeta->Write();

  theFile->Close();


}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackRPC);
