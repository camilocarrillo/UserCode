// -*- C++ -*-
//
// Package:    DTMonitorTrigger
// Class:      DTMonitorTrigger
// 
/**\class DTMonitorTrigger DTMonitorTrigger.cc DTMonitorTrigger/DTMonitorTrigger/src/DTMonitorTrigger.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Sun Aug 23 10:40:37 CEST 2009
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

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "FWCore/ServiceRegistry/interface/Service.h"


#include "TMath.h"

//
// class decleration
//

class DTMonitorTrigger : public edm::EDAnalyzer {
   public:
      explicit DTMonitorTrigger(const edm::ParameterSet&);
      ~DTMonitorTrigger();
      double gmt_etascale;

   private:
      virtual void beginJob( const edm::EventSetup& iSetup) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      void initializeHistograms(); 
      void fillGMTTriggerEtaPhi(float phi, float eta);

      std::string fileName_;

      DQMStore* _dbe;

      MonitorElement* expGMT_etaphi;
      edm::InputTag m_GMTInputTag;

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
DTMonitorTrigger::DTMonitorTrigger(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_GMTInputTag =iConfig.getParameter< edm::InputTag >("GMTInputTag");
  fileName_ = iConfig.getUntrackedParameter< std::string >("OutputName","TriggerMonitoringHistograms.root");
}


DTMonitorTrigger::~DTMonitorTrigger()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DTMonitorTrigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<L1MuGMTReadoutCollection> gmtrc_handle;
  iEvent.getByLabel(m_GMTInputTag,gmtrc_handle);
  
  std::vector<L1MuGMTExtendedCand> gmt_candidates = (*gmtrc_handle).getRecord().getGMTCands();
  
  std::vector<L1MuGMTExtendedCand>::const_iterator candidate;
  std::cout<<"The number of GMT Candidates in this event is "<<gmt_candidates.size()<<std::endl;

  for(candidate=gmt_candidates.begin(); candidate!=gmt_candidates.end(); candidate++) {
    int qual = candidate->quality();
    std::cout<<"quality of this GMT Candidate="<<qual<<std::endl;
    if(qual!=6) continue;
    float eta=candidate->etaValue();
    float phi=(candidate->phiValue());      
    phi*=180/TMath::Pi();
    if(candidate->isRPC()){//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  RPC only
      std::cout<<"Something is wrong with the HTL selection for the skim"<<std::endl;
    }
    fillGMTTriggerEtaPhi(phi,eta);
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
DTMonitorTrigger::beginJob( const edm::EventSetup& iSetup)
{
  _dbe = edm::Service<DQMStore>().operator->();
  initializeHistograms();
}


// ------------ method called once each job just after ending the event loop  ------------
void 
DTMonitorTrigger::endJob() {
  _dbe->save(fileName_);
}

void DTMonitorTrigger::initializeHistograms(){
  _dbe->setCurrentFolder("TriggerMonitoringPlots");
  expGMT_etaphi  = _dbe->book2D("expGMT_etaphi","GMTTriggerEtaPhi",63,-0.5,62.5,144,0.,360.);
}

void DTMonitorTrigger::fillGMTTriggerEtaPhi(float phi, float eta){
  float gmt_etascale[63] = {-2.40, -2.35, -2.30, -2.25, -2.20, -2.15, -2.10,  
			    -2.05, -2.00, -1.95, -1.90, -1.85, -1.80, -1.75,  
			    -1.70, -1.60, -1.50, -1.40, -1.30, -1.20, -1.10,  
			    -1.00, -0.90, -0.80, -0.70, -0.60, -0.50, -0.40,  
			    -0.30, -0.20, -0.10,  0.00,  0.10,  0.20,  0.30,  
			    0.40,  0.50,  0.60,  0.70,  0.80,  0.90,  1.00,  
			    1.10,  1.20,  1.30,  1.40,  1.50,  1.60,  1.70,  
			    1.75,  1.80,  1.85,  1.90,  1.95,  2.00,  2.05,  
			    2.10,  2.15,  2.20,  2.25,  2.30,  2.35,  2.40};
  
  float uniformeta = -20;
  std::cout<<eta<<" "<<phi<<std::endl;
  for(int i=0;i<62;i++){
    if(gmt_etascale[i]<=eta && eta <= gmt_etascale[i+1]){
      uniformeta = i;
    }
  }
  
  if(uniformeta == -20) std::cout<<"Warning eta gmt is not an expected value"<<std::endl;
  else expGMT_etaphi->Fill(uniformeta,phi);
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTMonitorTrigger);

    /*std::vector<L1MuRegionalCand> DTBXVector;
    std::vector<L1MuRegionalCand> BarrelRPCVector;
    
    DTBXVector = candidate->getDTBXCands();
    BarrelRPCVector = candidate->getBrlRPCCands();
  
    for(std::vector<L1MuRegionalCand>::const_iterator it = DTBXVector.begin(); it != DTBXVector.end() ; ++it){
      if(it->empty())continue;
      
      float dteta = it->etaValue();
      float dtphi = it->phiValue();

      dtphi = (dtphi/(2*TMath::Pi()))*360.;
      
      fillGMTTriggerEtaPhi(dtphi,dteta);
    }

    for(std::vector<L1MuRegionalCand>::const_iterator it = BarrelRPCVector.begin(); it != BarrelRPCVector.end() ; ++it){
      if(it->empty())continue;

      float rpceta = it->etaValue();
      float rpcphi = it->phiValue();

      rpcphi = (rpcphi/(2*TMath::Pi()))*360.;

      fillRPCTriggerEtaPhi(rpcphi,rpceta);

    }
    */
