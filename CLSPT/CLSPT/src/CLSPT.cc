// -*- C++ -*-
//
// Package:    CLSPT
// Class:      CLSPT
// 
/**\class CLSPT CLSPT.cc CLSPT/CLSPT/src/CLSPT.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,42 R-021,+41227671624,
//         Created:  Thu May 17 01:32:34 CEST 2012
// $Id: CLSPT.cc,v 1.2 2012/05/17 18:50:47 carrillo Exp $
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

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"


#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/getRef.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"



using namespace std;

//
// class declaration
//

class CLSPT : public edm::EDAnalyzer {
   public:
      explicit CLSPT(const edm::ParameterSet&);
      ~CLSPT();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  TFile * theFileCal;
  TH1F * theHisto;
  std::string  m_trackTag;

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

  std::string rootFileName;
      
  TFile* theFile;
      
  TH1F * muonMultiplicity;
  
  TH1F * recHitMultiplicity;
  TH1F * rpcrecHitMultiplicity;
  TH1F * chi2;
  TH1F * dxy;
  
  TH1F * trackobservedeta;
  TH1F * trackobservedphi;
  TH1F * trackobservedp;
  TH1F * trackobservedpt;
      
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
CLSPT::CLSPT(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
}


CLSPT::~CLSPT()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CLSPT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  edm::Handle<reco::TrackCollection> alltracks;
  iEvent.getByLabel(m_trackTag,alltracks);

   int counter = 0;
   float eta=0;
   float phi=0;
   float p=0;
   float pt=0;

   std::cout<<"There are "<<alltracks->size()<<" muon tracks in this event"<<std::endl;
   muonMultiplicity->Fill(alltracks->size());
   std::cout<<"Looping on all the reconstructed muons"<<std::endl;

   reco::TrackCollection::const_iterator muon;

   for(muon=alltracks->begin(); muon!=alltracks->end();muon++) {
     counter++;
     
     eta=muon->eta();
     phi=muon->phi();
     p=muon->p();
     pt=muon->pt();
     
     trackobservedeta->Fill(eta);
     trackobservedphi->Fill(phi);
     trackobservedp->Fill(p);
     trackobservedpt->Fill(pt);
     dxy->Fill(muon->dxy());
     chi2->Fill(muon->chi2()/muon->ndof());
     
     std::cout<<"\t phi  ="<<phi<<" eta  ="<<eta<<" p = "<<p<<std::endl;
     std::cout<<"\t Muon muon->chi2() = "<<muon->chi2()<<std::endl;
     std::cout<<"\t Muon muon->chi2()/ndof = "<<muon->chi2()/muon->ndof() <<std::endl;
     std::cout<<"\t Cheking chi2/ndof"<<std::endl;
   }
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
CLSPT::beginJob()
{

  std::cout<<"Begin Job"<<std::endl;
  
    theFile = new TFile(rootFileName.c_str(),"RECREATE");

    muonMultiplicity = new TH1F("Muon_Multiplicity","Muon_Multiplicity",11,-0.5,10.5); 
    recHitMultiplicity = new TH1F("recHitMultiplicity","recHitMultiplicity",101,-0.5,100.5);
    rpcrecHitMultiplicity = new TH1F("RPCrecHitMultiplicity","RPCrecHitMultiplicity",21,-0.5,20.5);

    chi2 = new TH1F("chi2_normalized","chi2_normalized",101,-0.5,100.5);
    dxy = new TH1F("dxy","dxy",200,-10,10);

    trackobservedeta = new TH1F("EtaObserved","Eta",100,-2.5,2.5); 
    trackobservedphi = new TH1F("PhiObserved","Phi",100,-3.1415926,3.1415926); 
    trackobservedp = new TH1F("PObserved","P ",100,0,1500);    
    trackobservedpt = new TH1F("PtObserved","Pt",100,0,1500);    
    std::cout<<"Finishing Begin Job"<<std::endl;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
CLSPT::endJob() 
{

  muonMultiplicity->Write();

  recHitMultiplicity->Write();
  rpcrecHitMultiplicity->Write();
  chi2->Write();
  dxy->Write();
  
  trackobservedeta->Write();
  trackobservedphi->Write();
  trackobservedp->Write();
  trackobservedpt->Write();

  theFile->Close();
}

// ------------ method called when starting to processes a run  ------------
void 
CLSPT::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CLSPT::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CLSPT::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CLSPT::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CLSPT::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CLSPT);
