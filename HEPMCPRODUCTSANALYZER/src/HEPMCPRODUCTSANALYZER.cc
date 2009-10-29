// -*- C++ -*-
//
// Package:    HEPMCPRODUCTSANALYZER
// Class:      HEPMCPRODUCTSANALYZER
// 
/**\class HEPMCPRODUCTSANALYZER HEPMCPRODUCTSANALYZER.cc beta/HEPMCPRODUCTSANALYZER/src/HEPMCPRODUCTSANALYZER.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Wed Oct 28 15:52:36 CET 2009
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

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Particle.h"

//
// class decleration
//

class HEPMCPRODUCTSANALYZER : public edm::EDAnalyzer {
   public:
      explicit HEPMCPRODUCTSANALYZER(const edm::ParameterSet&);
      ~HEPMCPRODUCTSANALYZER();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag hepMCProduct_label_;
      double   genLeadTrackPt_,genEta_;
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
HEPMCPRODUCTSANALYZER::HEPMCPRODUCTSANALYZER(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  hepMCProduct_label_   = iConfig.getParameter<edm::InputTag>("HepMCProduct");
  genLeadTrackPt_       = iConfig.getParameter<double>("GenLeadTrackPt");
  genEta_               = iConfig.getParameter<double>("GenEta");
}


HEPMCPRODUCTSANALYZER::~HEPMCPRODUCTSANALYZER()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
HEPMCPRODUCTSANALYZER::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   ESHandle<HepPDT::ParticleDataTable> pdt;
   iSetup.getData(pdt);
   
   Handle<HepMCProduct> genEvent;
   iEvent.getByLabel(hepMCProduct_label_, genEvent);
   if (genEvent.isValid())
   {
     float genLeadTrackPt=-100;
     for (HepMC::GenEvent::particle_const_iterator iter=(*(genEvent->GetEvent())).particles_begin();
          iter!=(*(genEvent->GetEvent())).particles_end(); 
          ++iter)
     {
       HepMC::GenParticle* theParticle=*iter;
       double pt=pow(pow(theParticle->momentum().px(),2)+pow(theParticle->momentum().py(),2), 0.5);
       double charge=pdt->particle(theParticle->pdg_id())->charge();
       std::cout<<" pdgId="<<theParticle->pdg_id()<<" pt="<<pt<<" status="<<theParticle->status()<<std::endl;
     }
   }
   else 
   {
     std::cout<<"genEvent in not valid!"<<std::endl;
   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
HEPMCPRODUCTSANALYZER::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HEPMCPRODUCTSANALYZER::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HEPMCPRODUCTSANALYZER);