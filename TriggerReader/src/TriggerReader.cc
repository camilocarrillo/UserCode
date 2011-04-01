// -*- C++ -*-
//
// Package:    TriggerReader
// Class:      TriggerReader
// 
/**\class TriggerReader TriggerReader.cc TriggerReader/TriggerReader/src/TriggerReader.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Fri Apr  1 11:36:36 CEST 2011
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

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"


//
// class declaration
//

class TriggerReader : public edm::EDAnalyzer {
   public:
      explicit TriggerReader(const edm::ParameterSet&);
      ~TriggerReader();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
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
TriggerReader::TriggerReader(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


TriggerReader::~TriggerReader()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TriggerReader::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<L1MuGMTReadoutCollection> gmtrc_handle;
  iEvent.getByLabel("hltGtDigis",gmtrc_handle);
  std::vector<L1MuGMTExtendedCand> gmt_candidates = (*gmtrc_handle).getRecord().getGMTCands();
  std::vector<L1MuGMTExtendedCand>::const_iterator candidate;
  std::cout<<"The number of GMT Candidates in this event is "<<gmt_candidates.size()<<std::endl;
  for(candidate=gmt_candidates.begin(); candidate!=gmt_candidates.end(); candidate++) {
    int quality=candidate->quality();
    if(quality==0)continue; 
    float eta=candidate->etaValue();
    float phi=candidate->phiValue();      
    phi*=180/3.141592653;
    std::cout<<"GMT coord phi="<<phi<<" eta="<<eta<<" quality="<<quality<<std::endl;    
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerReader::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerReader::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerReader);
