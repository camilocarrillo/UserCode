// -*- C++ -*-
//
// Package:    MuonRPCMonitor
// Class:      MuonRPCMonitor
// 
/**\class MuonRPCMonitor MuonRPCMonitor.cc MuonRPCMonitor/MuonRPCMonitor/src/MuonRPCMonitor.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Sun Jun 13 13:55:21 CEST 2010
// $Id: MuonRPCMonitor.cc,v 1.1 2010/06/13 16:08:22 carrillo Exp $
//
//
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MuonRPCMonitor/MuonRPCMonitor/interface/MuonRPCMonitor.h"

MuonRPCMonitor::MuonRPCMonitor(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
  MinRPCRecHits = iConfig.getUntrackedParameter<int>("MinRPCRecHits");//not usefull in this analysis

}


MuonRPCMonitor::~MuonRPCMonitor()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MuonRPCMonitor::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHits;
  char meIdRPCbx [128];

  int counter = 0;
  float eta=0;
  float phi=0;
  float p=0;
    
  std::cout<<"\t Loop on all the reconstructed muons"<<std::endl;
  std::cout<<"\t We found "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;
  observedTracksPerEvent->Fill(trackCollectionHandle->size());
  
  for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
    counter++;
    std::cout<<"counter = "<<counter<<std::endl;
    
    std::cout<<"going"<<std::endl;
    
    eta=muon->eta(); observedeta->Fill(eta);
    phi=muon->phi(); observedphi->Fill(phi);
    p=muon->p(); observedp->Fill(p);

    int rechitcounter = 0;
    
    for(trackingRecHit_iterator recHit2 = muon->recHitsBegin(); recHit2 != muon->recHitsEnd(); ++recHit2) {
      rechitcounter++;
    }
    
    observedNhits->Fill(rechitcounter);
    
    if(rechitcounter==0){
      std::cout<<"!!!!!!!!!!!!No recHits in this track"<<std::endl;
    }

    std::cout<<"\t \t Rechitcounter in this muon = "<<rechitcounter<<std::endl;

    std::cout<<"\t \t phi  ="<<phi<<" eta  ="<<eta<<std::endl;
    std::cout<<"\t \t Loop on the rechits"<<std::endl;
    
    int rechitcounterRPC=0;

    for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit){
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue;
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue;
      if (!(*recHit)->isValid()) continue;
      rechitcounterRPC++;
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      RPCGeomServ rpcsrv(rollId);
      std::string nameRoll = rpcsrv.name();
      sprintf(meIdRPCbx,"BXMuon_%s",nameRoll.c_str());
      std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
      meMap[meIdRPCbx]->Fill(((RPCRecHit*)(&(**recHit)))->BunchX());
    }
    observedNhitsRPC->Fill(rechitcounterRPC);
  }
  
}


// ------------ method called once each job just before starting event loop  ------------
void MuonRPCMonitor::beginJob(){
  std::cout<<"Begin Job"<<std::endl;
  firstbook = true;
}
void MuonRPCMonitor::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::cout<<"Begin Run"<<std::endl;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  if(firstbook){
  dbe = edm::Service<DQMStore>().operator->();

  observedeta = dbe->book1D("EtaObserved","Eta Observed Tracks",100,-2.5,2.5); 
  observedphi = dbe->book1D("PhiObserved","Phi Observed Tracks",100,-3.1415926,3.1415926); 
  observedp = dbe->book1D("PObserved","P Observed Tracks",100,0,1500); 
  observedNhits = dbe->book1D("NhitsObserved","N hits Observed Tracks",41,-0.5,40.5); 
  observedNhitsRPC = dbe->book1D("NhitsObservedRPC","N hits Observed Tracks",21,-0.5,20.5); 
  observedTracksPerEvent = dbe->book1D("NhitsObserved","N hits Observed Tracks",11,-0.5,10.5); 

  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);
	std::string nameRoll = rpcsrv.name();
	std::cout<<"Begin Booking for "<<nameRoll<<std::endl;
	meCollection[nameRoll] = bookDetUnitSeg(rpcId);
	std::cout<<"Finishing book"<<std::endl;
      }
    }
  }
  firstbook=false;
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void MuonRPCMonitor::endJob(){
  std::cout<<"End Job"<<std::endl;
  std::cout<<"Saving root file under "<<rootFileName<<std::endl;
  dbe->save(rootFileName);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonRPCMonitor);
