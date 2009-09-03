// -*- C++ -*-
//
// Package:    VALIDATOR
// Class:      VALIDATOR
// 
/**\class VALIDATOR VALIDATOR.cc beta/VALIDATOR/src/VALIDATOR.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Aug 31 15:34:26 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "DataFormats/DetId/interface/DetId.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "beta/BETA/interface/BETA.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "FastSimulation/Tracking/test/FastTrackAnalyzer.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "RecoMuon/TrackingTools/interface/MuonPatternRecoDumper.h"

#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class decleration
//

//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"

#include "TFile.h"
#include "TTree.h"
#include "TKey.h"

//Track
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

class VALIDATOR : public edm::EDAnalyzer {
   public:
      explicit VALIDATOR(const edm::ParameterSet&);
      ~VALIDATOR();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string partLabel;

      std::string muonRPCDigis;
      std::string rootFileName;

      int partid;
      TFile* theFile;

      TH1F * statistics;

      TH1F * expectedeta;
      TH1F * expectedphi;
      TH1F * expectedbeta;
      TH1F * expectedp;
      TH1F * expectedpt;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

float betapm(float p,float m){//beta from mass and 3 momentum
  float beta = 1./sqrt(1+((m*m)/(p*p)));
  if(beta<=1 && beta>=0){
    return beta;
  }else{
    std::cout<<"p and m are not relativistic variables=p"<<p<<" m="<<m<<std::endl;
    return 0;
  }
}

//
// static data member definitions
//

//
// constructors and destructor
//
VALIDATOR::VALIDATOR(const edm::ParameterSet& iConfig)

{
 partLabel = iConfig.getUntrackedParameter<std::string>("partLabel");
 partid = iConfig.getUntrackedParameter<int>("partid"); 
 muonRPCDigis=iConfig.getUntrackedParameter<std::string>("muonRPCDigis","muonRPCDigis");
 rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");

   //now do what ever initialization is needed

}


VALIDATOR::~VALIDATOR()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
VALIDATOR::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(partLabel,genParticles );

  statistics->Fill(1);

  bool firstParticle = true;

  reco::GenParticleCollection::const_iterator partIt;
  for(partIt=genParticles->begin();partIt!=genParticles->end();++partIt) {
    
    float etamc=0;
    float phimc=0;
    float betamc=0;
    float pmc=0;
    float mmc=0;
    
    if(partIt->pdgId()!=partid) continue;
    
    std::cout<<"This event contains one HSCP"<<std::endl;
    if(firstParticle){
      statistics->Fill(2); 
      firstParticle=false;
    }
    
    float e=partIt->energy();
    float ptmc = partIt->pt();
    pmc=partIt->p();
    
    betamc=pmc/e;
    
    int event = iEvent.id().event();
    etamc = partIt->eta();
    phimc = partIt->phi();
    
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
    expectedpt->Fill(ptmc);
    
    std::cout<<"ev="<<event<<" phimc="<<partIt->phi()<<" etamc="<<etamc<<" betamc="<<betamc<<" pmc="<<pmc<<"GeV ptmc="<<ptmc<<"GeV mmc="<<mmc<<"GeV"<<std::endl;
    
  }
  
  std::cout << " Getting the SimHits " <<std::endl;
  std::vector<edm::Handle<edm::PSimHitContainer> > theSimHitContainers;
  iEvent.getManyByType(theSimHitContainers);
  std::cout << " The Number of sim Hits is  " << theSimHitContainers.size() <<std::endl;
  
   //SimTrack Stuff
  
  std::vector<PSimHit> theSimHits;
  
  for (int i = 0; i < int(theSimHitContainers.size()); i++){
    theSimHits.insert(theSimHits.end(),theSimHitContainers.at(i)->begin(),theSimHitContainers.at(i)->end());
  } 
  
  bool firstSimHitFromHSCP = true;
  
  for (std::vector<PSimHit>::const_iterator iHit = theSimHits.begin(); iHit != theSimHits.end(); iHit++){  
    if((*iHit).particleType()== partid){//Only HSCPs
      DetId theDetUnitId((*iHit).detUnitId());
      DetId simdetid= DetId((*iHit).detUnitId());
      if(simdetid.det()==DetId::Muon &&  simdetid.subdetId()== MuonSubdetId::RPC){//Only RPCs
	if(firstSimHitFromHSCP){
	  firstSimHitFromHSCP = false;
	  statistics->Fill(3);
	}
      }
    }
  }
  

  edm::Handle<RPCDigiCollection> rpcDigis;
  iEvent.getByLabel(muonRPCDigis, rpcDigis);
  //iEvent.getByType(rpcDigis);

  bool firstDigi = true;
  
  RPCDigiCollection::DigiRangeIterator rpcDigiCI;
  for(rpcDigiCI = rpcDigis->begin();rpcDigiCI!=rpcDigis->end();rpcDigiCI++){
    const RPCDigiCollection::Range& range = (*rpcDigiCI).second;    
    for (RPCDigiCollection::const_iterator digiIt = range.first;digiIt!=range.second;++digiIt){
      if(firstDigi){
	firstDigi = false;
	statistics->Fill(4);
      }
    }
  }

  
  edm::Handle<RPCRecHitCollection> rpcRecHits; 
  iEvent.getByLabel("rpcRecHits","",rpcRecHits);

  bool firstRecHit = true;
  RPCRecHitCollection::const_iterator recHit;
  for(recHit = rpcRecHits->begin(); recHit != rpcRecHits->end(); recHit++) {
    if(firstRecHit){
      firstRecHit=false;
      statistics->Fill(5);
    }
  }
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
VALIDATOR::beginJob(const edm::EventSetup&)
{
  theFile = new TFile(rootFileName.c_str(),"RECREATE");
  
  statistics = new TH1F("statistics","Global information about events",5,0.5,5.5);          
  expectedeta = new TH1F("EtaExpected","Eta Expected",100,-2.5,2.5);           
  expectedphi = new TH1F("PhiExpected","Phi Expected",100,-3.1415926,3.1415926); 
  expectedbeta = new TH1F("BetaExpected","Beta Expected",100,0,1);                
  expectedp = new TH1F("PExpected","P Expected",100,0,1500);
  expectedpt = new TH1F("PtExpected","Pt Expected",100,0,1500);
    
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VALIDATOR::endJob() {

  theFile->cd();
  statistics->GetXaxis()->SetBinLabel(1,"Events");
  statistics->GetXaxis()->SetBinLabel(2,"with HSCP");
  statistics->GetXaxis()->SetBinLabel(3,"with SimHits from HSCP");
  statistics->GetXaxis()->SetBinLabel(4,"with RPC Digis");
  statistics->GetXaxis()->SetBinLabel(5,"with RPC RecHits");
  statistics->GetXaxis()->LabelsOption("h");
  statistics->GetXaxis()->SetLabelSize(0.033);
  statistics->SetFillColor(2);
  statistics->Write();

  expectedeta->GetXaxis()->SetTitle("eta"); 
  expectedeta->Write();
  expectedphi->GetXaxis()->SetTitle("phi(radians)"); 
  expectedphi->Write();
  expectedbeta->GetXaxis()->SetTitle("beta(c)"); 
  expectedbeta->Write();  
  expectedp->GetXaxis()->SetTitle("momentum(GeV)"); 
  expectedp->Write();
  expectedpt->GetXaxis()->SetTitle("Transverse momentum(GeV)"); 
  expectedpt->Write();
 
  theFile->Close();
  
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(VALIDATOR);
