// -*- C++ -*-
//
// Package:    RPCHSPCREADER
// Class:      RPCHSPCREADER
// 
/**\class RPCHSPCREADER RPCHSPCREADER.cc beta/RPCHSPCREADER/src/RPCHSPCREADER.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Feb 23 12:29:19 CET 2009
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


//
// class decleration
//

class RPCHSPCREADER : public edm::EDAnalyzer {
public:
  explicit RPCHSPCREADER(const edm::ParameterSet&);
  ~RPCHSPCREADER();
  
  typedef struct {
    Int_t event;
    Float_t eta,phi,beta;
  } HSCP_RPC_CANDIDATE;

  HSCP_RPC_CANDIDATE myCandidate;
  TTree *ttreeOutput;
  TFile *f;
  
  int event;
  float phi;
  float eta;
  float beta;
  
private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      std::string partLabel;
  

};

RPCHSPCREADER::RPCHSPCREADER(const edm::ParameterSet& iConfig)
{
  partLabel = iConfig.getUntrackedParameter<std::string>("partLabel");
  f = new TFile("HSCP_fromMC.root", "RECREATE");
  ttreeOutput = new TTree("HSCP_fromMC", "HSCP_fromMC");
  ttreeOutput->Branch("event", &event, "event/I");
  ttreeOutput->Branch("eta", &eta ,"eta/F");
  ttreeOutput->Branch("phi", &phi, "phi/F");
  ttreeOutput->Branch("beta", &beta, "beta/F");
}


RPCHSPCREADER::~RPCHSPCREADER()
{
  f->Write();
  f->Close();
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
RPCHSPCREADER::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  std::cout<<"Reading the particles container"<<std::endl;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(partLabel,genParticles );
  
  std::cout << " Number of Particles in this event: " << genParticles->size() << std::endl;

  reco::GenParticleCollection::const_iterator partIt;
  for(partIt=genParticles->begin();partIt!=genParticles->end();++partIt) {
    std::cout<<" Particle Id="<<partIt->pdgId()<<std::endl;
    if(partIt->pdgId()==-2000015){
      //ABOUT ETA
      //std::cout<<"\t\t Filling the histogram Eta="<<partIt->eta()<<std::endl;
      //etaHisto->Fill(partIt->eta(),countHitsInRPC);
      //soloEtaHisto->Fill(partIt->eta());
      //if(hscp)soloEtaMyHisto->Fill(partIt->eta());
      //ABOUT BETA
      float p=partIt->p();
      float e=partIt->energy();
      beta=p/e;
      //betaHisto->Fill(beta);
      //if(hscp)betaMyHisto->Fill(beta);
      float pt = partIt->pt();
      //float et = partIt->et();
      float betaT=pt/e;
      //betaTHisto->Fill(betaT);
      //if(count!=0)bxLayerFile<<"\t"<<" eta="<<partIt->eta()<<" beta="<<beta<<"c";
      //if(count!=0)fileMatrix<<" eta="<<partIt->eta()<<" beta="<<beta<<"c Event "<<iEvent.id().event()<<"\n";
      //if(fabs(partIt->eta()>1.14))etaout++;
      std::cout<<"\t phi="<<partIt->phi()<<" eta="<<partIt->eta()<<"beta="<<beta<<" p="<<p<<"GeV pt="<<pt<<"GeV m="<<sqrt(e*e-p*p)<<"GeV"<<std::endl;
      
      event = iEvent.id().event();
      eta = partIt->eta();
      phi = partIt->phi();
      ttreeOutput->Fill();

    }
  }


}


// ------------ method called once each job just before starting event loop  ------------
void 
RPCHSPCREADER::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCHSPCREADER::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCHSPCREADER);
