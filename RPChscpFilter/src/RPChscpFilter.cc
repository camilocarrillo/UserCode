// -*- C++ -*-
//
// Package:    RPChscpFilter
// Class:      RPChscpFilter
// 
/**\class RPChscpFilter RPChscpFilter.cc RPCHSCPFilter/RPChscpFilter/src/RPChscpFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Thu Jun 10 11:34:48 CEST 2010
// $Id: RPChscpFilter.cc,v 1.5 2010/10/31 13:30:27 carrillo Exp $
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
#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCParticle.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

//
// class declaration
//

class RPChscpFilter : public edm::EDFilter {
   public:
  explicit RPChscpFilter(const edm::ParameterSet& );
     ~RPChscpFilter();
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
  
      std::string rootFileName;
      
      TFile* theFile;
      
      TH1F * statistics;
   
      TH1F * muonMultiplicity;
  
      TH1F * recHitMultiplicity;
      TH1F * rpcrecHitMultiplicity;
      TH1F * chi2;
      TH1F * dxy;
  
      TH1F * mass;

      TH1F * twomuonangle; 
      
      TH1F * observedeta;
      TH1F * observedphi;
      TH1F * observedbeta;
      TH1F * observedp;
      TH1F * observedpt;
  
      TH1F * trackobservedeta;
      TH1F * trackobservedphi;
      TH1F * trackobservedbeta;
      TH1F * trackobservedp;
      TH1F * trackobservedpt;
      
      TH2F * betaVsp;
  
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
RPChscpFilter::RPChscpFilter(const edm::ParameterSet& iConfig)
{
  std::cout<<"In The Constructor"<<std::endl;
  //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  MinRPCRecHits = iConfig.getUntrackedParameter<int>("MinRPCRecHits");
  rootFileNameCal =iConfig.getUntrackedParameter<std::string>("rootFileNameCal");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
  synchth = iConfig.getUntrackedParameter<double>("synchth");
  minIntegral = iConfig.getUntrackedParameter<double>("minIntegral");
  minMean = iConfig.getUntrackedParameter<double>("minMean");
}


RPChscpFilter::~RPChscpFilter()
{
  std::cout<<"In The Destructor"<<std::endl;

}


//
// member functions
//

// ------------ method called on each new Event  ------------

float BetaCalculatorRPC(std::vector<susybsm::RPCHit4D> HSCPRPCRecHits){

  std::cout<<"Inside BetaCalculatorRPC "<<std::endl;

  int lastbx=-7;
  bool outOfTime = false;
  bool increasing = true;
  bool anydifferentzero = true;
  bool anydifferentone = true;

  float betavalue = 1;

  std::cout<<"Inside BetaCalculatorRPC Preliminar loop on the RPCHit4D!!!"<<std::endl;

  std::sort(HSCPRPCRecHits.begin(), HSCPRPCRecHits.end()); //Organizing them

  for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
    outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0
    increasing &= (point->bx>=lastbx); //condition 2: BX must be increase when going inside-out.
    anydifferentzero &= (!point->bx==0); //to check one knee withoutzeros
    anydifferentone &= (!point->bx==1); //to check one knee withoutones
    lastbx = point->bx;
    float r=point->gp.mag();
    std::cout<<"Inside BetaCalculatorRPC \t  r="<<r<<" phi="<<point->gp.phi()<<" eta="<<point->gp.eta()<<" bx="<<point->bx<<" outOfTime"<<outOfTime<<" increasing"<<increasing<<" anydifferentzero"<<anydifferentzero<<std::endl;
  }
  
  bool Candidate = (outOfTime&&increasing);

  // here we should get some pattern-based estimate

  //Counting knees

  std::cout<<"Inside BetaCalculatorRPC Counting knees"<<std::endl;

  float delay=12.5;
  lastbx=-7; //already declared for the preliminar loop
  int knees=0;
  float maginknee = 0;
  float maginfirstknee = 0;
  for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
    if(lastbx==-7){
      maginfirstknee = point->gp.mag();
    }else if((lastbx!=point->bx)){
      std::cout<<"Inside BetaCalculatorRPC \t one knee between"<<lastbx<<point->bx<<std::endl;
      maginknee=point->gp.mag();
      knees++;
    }
    lastbx=point->bx;
  }

  std::cout<<"Inside BetaCalculatorRPC knees = "<<knees<<std::endl;
      
  if(knees==0){
    std::cout<<"Inside BetaCalculatorRPC  \t \t knees="<<knees<<std::endl;
    betavalue=maginfirstknee/(25.-delay+maginfirstknee/30.)/30.;
  }else if(knees==1){
    float betavalue1=0;
    float betavalue2=0;
    std::cout<<"Inside BetaCalculatorRPC  \t \t knees="<<knees<<std::endl;
    std::cout<<"Inside BetaCalculatorRPC  \t \t anydifferentzero="<<anydifferentzero<<" anydifferentone="<<anydifferentone<<std::endl;
    if(!anydifferentzero){
      betavalue=maginknee/(25-delay+maginknee/30.)/30.;
    }else if(!anydifferentone){//i.e non zeros and no ones
      betavalue=maginknee/(50-delay+maginknee/30.)/30.;
    }else{
      betavalue1=maginknee/(25-delay+maginknee/30.)/30.;
      float dr =(maginknee-maginfirstknee);
      betavalue2 = dr/(25.-delay+dr/30.);
      std::cout<<"Inside BetaCalculatorRPC  \t \t \t not zero neither ones betavalue1="<<betavalue1<<" betavalue2="<<betavalue2<<std::endl;
      betavalue = (betavalue1 + betavalue2)*0.5;
    }
  }else if(knees==2){
    std::cout<<"Inside BetaCalculatorRPC  \t \t knees="<<knees<<std::endl;
    knees=0;
    float betavalue1=0;
    float betavalue2=0;
    lastbx=-7;
    std::cout<<"Inside BetaCalculatorRPC  \t \t looping again on the RPCRecHits4D="<<knees<<std::endl;
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHits.begin(); point < HSCPRPCRecHits.end(); ++point) {
      if(lastbx==-7){
	maginfirstknee = point->gp.mag();
      }else if((lastbx!=point->bx)){
	std::cout<<"Inside BetaCalculatorRPC  \t \t \t one knee between"<<lastbx<<point->bx<<std::endl;
	knees++;
	if(knees==2){
	  float maginsecondknee=point->gp.mag();
	  betavalue1=maginknee/(25-delay+maginknee/30.)/30.;
	  float dr =(maginknee-maginsecondknee);
	  betavalue2 = dr/(25.+dr/30.);
	  std::cout<<"Inside BetaCalculatorRPC  \t \t \t betavalue1="<<betavalue1<<" betavalue2="<<betavalue2<<std::endl;
	}
      }
      lastbx=point->bx;
    }
    betavalue = (betavalue1 + betavalue2)*0.5;
  }
  
  if(Candidate){
    std::cout<<"Inside BetaCalculatorRPC \t \t \t yes! We found an HSCPs let's try to estimate beta"<<std::endl;
  }else{
    std::cout<<"Inside BetaCalculatorRPC \t \t \t seems that there is no RPC HSCP Candidate in the set of RPC4DHit"<<std::endl;
    betavalue = 1.;
  }
  
  if(HSCPRPCRecHits.size()==0){
    std::cout<<"Inside BetaCalculatorRPC \t WARINNG EMPTY RPC4DRecHits CONTAINER!!!"<<std::endl;
    betavalue = 1.;
  }

  return betavalue;
}


bool IsBadRoll(uint32_t rawId,std::vector<uint32_t> thelist){
  bool isBadRoll = false;
  if(!(find(thelist.begin(),thelist.end(),rawId)==thelist.end())){
    isBadRoll=true;
  }
  return isBadRoll;
}

float gamma(float b){//gamma from beta                                                                                        
  if(b<1 && b>0){
    return 1./sqrt(1-b*b);
  }else{
    std::cout<<"error in the estimation of b="<<b<<std::endl;
    return 0;
  }
}

float nullifbacktoback(float phi1,float phi2){
  float diffphi = fabs(phi1 - phi2);
  if(diffphi>3.14159265358979) return 2*3.14159265358979-diffphi-3.14159265358979;
  else if(diffphi < -3.14159265358979) return 2*3.1415926535+diffphi-3.14159265358979;
  else return diffphi-3.14159265358979;
}


bool RPChscpFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  if(firstbook){
  firstbook = false;

  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  theFileCal = new TFile(rootFileNameCal.c_str());
  
  if(!theFileCal){
    std::cout<<"The File Doesn't exist"<<std::endl;
  }else{
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
  }

  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);

  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);
  
  std::vector<susybsm::RPCHit4D> HSCPRPCRecHitsR;

  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
	
  int counter = 0;
  float eta=0;
  float phi=0;
  float p=0;
  float pt=0;
    
  std::cout<<"Filling Statistics"<<std::endl;

  statistics->Fill(1);

  std::cout<<"Loop on all the reconstructed muons"<<std::endl;
  
  std::cout<<"There are "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;

  muonMultiplicity->Fill(trackCollectionHandle->size());

  bool cosmic = false;

  std::cout<<"Checking if it is cosmic?"<<std::endl;


  if(trackCollectionHandle->size()>=2)
    for (reco::TrackCollection::const_iterator leg1 = trackCollectionHandle->begin(); leg1!=trackCollectionHandle->end(); leg1++){
      for (reco::TrackCollection::const_iterator leg2 = leg1+1; leg2!=trackCollectionHandle->end(); leg2++){
	float deltaphi = fabs(nullifbacktoback(leg1->phi(),leg2->phi()));
	std::cout<<" deltaphi = "<<deltaphi<<std::endl;
	twomuonangle->Fill(deltaphi);
	if(deltaphi<=0.02 && deltaphi>0){
	  std::cout<<"\t Probably we got a cosmic in this envet"<<std::endl;
	  cosmic = true;
 	}
      }
    }

  if(cosmic){    
    std::cout<<"\t Yes it is a cosmic"<<std::endl;
    statistics->Fill(2);
  }


  std::cout<<"Looping on all the reconstructed muons"<<std::endl;

  for (reco::TrackCollection::const_iterator muon = trackCollectionHandle->begin(); muon!=trackCollectionHandle->end(); muon++) {
    counter++;
    
    eta=muon->eta();
    phi=muon->phi();
    p=muon->p();
    pt=muon->pt();
    float beta=1;

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
    
    if(muon->chi2()/muon->ndof()>40){
      std::cout<<"\t Event skiped because of muon->chi2/ndof = "<<muon->chi2()/muon->ndof()<<std::endl;
      continue; //Is the Muon chi2/ndof smaller than 20.      
    }
    
    std::cout<<"\t Cheking pt muon->pt = "<<pt<<" GeV dxy = "<<muon->dxy()<<std::endl;
    
    if(muon->pt()<30.){ 
      std::cout<<"\t Event skiped because of muon->pt = "<<muon->pt()<<std::endl;
      continue; //Is the Muon pt smaller than 30GeV.
    }

    std::cout<<"\t Cheking dxy "<<std::endl;

    if(fabs(muon->dxy()) > 0.25){
      std::cout<<"\t Event skiped because of muon->dxy = "<<muon->dxy()<<std::endl;
      continue;  //Is the transverse impact parameter bigger than 0.25cm?.
    }

    int rechitcounter = 0;
    int rpcrechitcounter = 0;
    for(trackingRecHit_iterator recHit2 = muon->recHitsBegin(); recHit2 != muon->recHitsEnd(); ++recHit2) {
      rechitcounter++;
      if(((*recHit2)->geographicalId().det()==DetId::Muon)&&((*recHit2)->geographicalId().subdetId() == MuonSubdetId::RPC)){
	rpcrechitcounter++;
      }
    }

    std::cout<<"\t Cheking Number of rechits associated to the muon "<<rechitcounter<<std::endl;
    if(rechitcounter==0){
      std::cout<<"\t !!!!!!!!!!!!No recHits in this track"<<std::endl;
      continue;
    }

    std::cout<<"\t Cheking Number of RPCrechits associated to the muon "<<rpcrechitcounter<<std::endl;
    if(rpcrechitcounter==0){
      std::cout<<"\t !!!!!!!!!!!!No RPCrecHits in this track"<<std::endl;
      continue;
    }
    
    std::cout<<"\t Rechitcounter in this muon = "<<rechitcounter<<std::endl;
    std::cout<<"\t RPCrechitcounter in this muon = "<<rpcrechitcounter<<std::endl;
    
    recHitMultiplicity->Fill(rechitcounter);
    rpcrecHitMultiplicity->Fill(rpcrechitcounter);

    std::cout<<"\t phi  ="<<phi<<" eta  ="<<eta<<std::endl;
    std::cout<<"\t The muon passes all the requirements now loop on its rechits"<<std::endl;
    
    HSCPRPCRecHitsR.clear();
    for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit){
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue; //Is a hit in the Muon System?
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue; //Is an RPC Hit?
      std::cout<<"\t \t 1/6 Is a hit in the Muon System? "<<std::endl;
      std::cout<<"\t \t 2/6 Is an RPCHit? "<<std::endl;
      std::cout<<"\t \t 3/6 Is a valid hit? "<<std::endl;
      if (!(*recHit)->isValid()) continue; //Is Valid
      std::cout<<"\t \t 4/6 The Hit belongs to a good roll.?"<<std::endl;
      if(IsBadRoll((RPCDetId)(*recHit)->geographicalId().rawId(),blacklist)) continue; //The Hit belongs to a good roll.?
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();

      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  rpcHits->get(rollId);
      RPCRecHitCollection::const_iterator recHitC;
      int size = 0;
      int clusterS=0;
      std::cout<<"\t \t \t Looping on the rechits of the same roll"<<std::endl;
      for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) {
	clusterS=(*recHitC).clusterSize(); 
	RPCDetId rollId = (RPCDetId)(*recHitC).geographicalId();
	std::cout<<"\t \t \t \t"<<rollId<<" bx "<<(*recHitC).BunchX()<<std::endl;
	size++;
      }
      std::cout<<"\t \t 5/6 Is the only RecHit in this roll.? size = "<<size<<std::endl;
      if(size>1) continue; //Is the only RecHit in this roll.?
      std::cout<<"\t \t 6/6 Is the Cluster Size bigger than 4.?"<<std::endl;
      if(clusterS>4) continue; //Is the Cluster Size 5 or bigger? 
      LocalPoint recHitPos=(*recHit)->localPosition();
      const RPCRoll* rollasociated = rpcGeo->roll(rollId); 
      const BoundPlane & RPCSurface = rollasociated->surface();
      susybsm::RPCHit4D ThisHit;
      ThisHit.bx = ((RPCRecHit*)(&(**recHit)))->BunchX();
      ThisHit.gp = RPCSurface.toGlobal(recHitPos);
      ThisHit.id = (RPCDetId)(*recHit)->geographicalId().rawId();
      HSCPRPCRecHitsR.push_back(ThisHit);
      std::cout<<"\t \t All answers were yes"<<std::endl;
    }
    
    // here we go on with  the RPC procedure                                                                                                                          
    std::sort(HSCPRPCRecHitsR.begin(), HSCPRPCRecHitsR.end());
    int lastbx=-7;
    bool outOfTime = false;
    bool increasing = true;
    bool allnegative = true;
    bool allpositive = true;
    
    std::cout<<"\t \t \t The number of RPCRecHits that passed the previos cuts is bigger than "<<MinRPCRecHits<<" ?"<<std::endl;
    if((int) HSCPRPCRecHitsR.size()<MinRPCRecHits){
      std::cout<<"\t \t \t \t No Less than"<<MinRPCRecHits<<"RecHits in this muon!!! = "<<HSCPRPCRecHitsR.size()<<std::endl; //The number of RPCRecHits that passed the previos cuts is bigger than MinRPCRecHits 
      continue;
    }

    std::cout<<"\t \t \t \t Yes the number of RPC Hits for this Muon Track = "<<HSCPRPCRecHitsR.size()<<std::endl;
    std::cout<<"\t \t \t \t Loop on the RPCHit4D!!!"<<std::endl;
    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHitsR.begin(); point < HSCPRPCRecHitsR.end(); ++point) {
      float r=point->gp.mag();
      outOfTime |= (point->bx!=0); //condition 1: at least one measurement must have BX!=0                                                                           
      increasing &= (point->bx==lastbx || point->bx==lastbx+1 || lastbx ==-7); //condition 2: BX must be increase when going inside-out.                                                                   
      allpositive &= (point->bx>=0); //condition 3: None of them can be negative

      allnegative &= (point->bx<0); //condition 4: Not all the BX can be negative

      lastbx = point->bx;
      std::cout<<"\t \t \t \t r="<<r<<" phi="<<point->gp.phi()<<" eta="<<point->gp.eta()
	       <<" bx="<<point->bx<<" lastbx="<<lastbx<<" outOfTime"<<outOfTime
	       <<" increasing"<<increasing<<" "<<point->id
	       <<" allnegative "<<allnegative<<" allpositive "<<allpositive<<std::endl;
    }
    
    std::cout<<"\t \t \t \t The RPC pattern ";

    for(std::vector<susybsm::RPCHit4D>::iterator point = HSCPRPCRecHitsR.begin(); point < HSCPRPCRecHitsR.end(); ++point) {
      std::cout<<point->bx;
    }
    std::cout<<std::endl;
    
    bool pp = true;
    float delay = 0;
    if(pp){
      delay=12.5; //half bunch crossing delay for pp collisions
    }
    
    bool Candidate = (outOfTime&&increasing&&!cosmic&&!allnegative&&allpositive);

    std::cout<<"\t \t \t \t Is an HSCP?"<<std::endl;

    if(Candidate){

      statistics->Fill(3);

      std::cout<<"\t \t \t \t \t yes! We found an HSCPs let's try to estimate beta"<<std::endl;
      beta = BetaCalculatorRPC(HSCPRPCRecHitsR);
      std::cout<<"\t \t \t \t \t Estimating the mass"<<std::endl;
      float m=p/(gamma(beta)*beta);
      std::cout<<"\t \t \t \t \t m  = "<<m<<std::endl;
      std::cout<<"\t \t \t \t \t p  = "<<p<<std::endl;
      std::cout<<"\t \t \t \t \t b  = "<<beta<<std::endl;
      
      observedeta->Fill(eta);
      observedphi->Fill(phi);
      observedbeta->Fill(beta);
      observedp->Fill(p);
      observedpt->Fill(pt);
      mass->Fill(m);
      
      trackobservedbeta->Fill(beta);
      betaVsp->Fill(beta,p);
      
      return true;
    }else{
      std::cout<<"\t \t \t \t \t NO! any of these is false outOfTime&&increasing&&!cosmic&&!allnegative&&allpositive "
	       <<outOfTime<<increasing<<!cosmic<<!allnegative<<allpositive<<std::endl;
    }
    trackobservedbeta->Fill(beta);
    betaVsp->Fill(beta,p);
  }
  
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPChscpFilter::beginJob(){
  std::cout<<"Begin Job"<<std::endl;
  firstbook = true;
  
  theFile = new TFile(rootFileName.c_str(),"RECREATE");

  statistics = new TH1F("statistics","Some Information",10,0.5,10.5); 
  muonMultiplicity = new TH1F("Muon_Multiplicity","Muon_Multiplicity",11,-0.5,10.5); 
  recHitMultiplicity = new TH1F("recHitMultiplicity","recHitMultiplicity",101,-0.5,100.5);
  rpcrecHitMultiplicity = new TH1F("RPCrecHitMultiplicity","RPCrecHitMultiplicity",21,-0.5,20.5);

  chi2 = new TH1F("chi2_normalized","chi2_normalized",101,-0.5,100.5);
  dxy = new TH1F("dxy","dxy",200,-10,10);

  twomuonangle = new TH1F("Two_Muons_Angle","Two_Muons_Angle",100,-3.1411592,3.141592); 
  
  mass = new TH1F("mass","Mass estimation",75,0,1500); 
    
  observedeta = new TH1F("EtaObserved","Eta Observed HSCP",100,-2.5,2.5); 
  observedphi = new TH1F("PhiObserved","Phi Observed HSCP",100,-3.1415926,3.1415926); 
  observedbeta = new TH1F("BetaObserved","Beta Observed HSCP",101,0,1.1);                
  observedp = new TH1F("PObserved","P Observed HSCP",100,0,1500);    
  observedpt = new TH1F("PtObserved","Pt Observed HSCP",100,0,1500);    

  trackobservedeta = new TH1F("trackEtaObserved","Eta Observed Track",100,-2.5,2.5); 
  trackobservedphi = new TH1F("trackPhiObserved","Phi Observed Track",100,-3.1415926,3.1415926); 
  trackobservedbeta = new TH1F("trackBetaObserved","Beta Observed Track",101,0,1.1);                
  trackobservedp = new TH1F("trackPObserved","P Observed Track",100,0,1500);    
  trackobservedpt = new TH1F("trackPtObserved","Pt Observed Track",100,0,1500);    

  betaVsp = new TH2F ("beta_Vs_p","beta_Vs_p",101,0,1.1,100,0,1000);


  std::cout<<"Finishing Begin Job"<<std::endl;
}

void
RPChscpFilter::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::cout<<"Begin Run"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------

void 
RPChscpFilter::endRun(){
  std::cout<<"end Run"<<std::endl;
}

void 
RPChscpFilter::endJob(){
  std::cout<<"end Job"<<std::endl;

  std::cout<<"Starging the endjob"<<std::endl;

  theFile->cd();

  std::cout<<"saving root files"<<std::endl;
  
  statistics->Write();
  twomuonangle->Write();
  muonMultiplicity->Write();

  recHitMultiplicity->Write();
  rpcrecHitMultiplicity->Write();
  chi2->Write();
  dxy->Write();
  
  mass->Write();
  
  observedeta->Write();
  observedphi->Write();
  observedbeta->Write();
  observedp->Write();
  observedpt->Write();

  trackobservedeta->Write();
  trackobservedphi->Write();
  trackobservedbeta->Write();
  trackobservedp->Write();
  trackobservedpt->Write();

  betaVsp->Write();

  theFile->Close();



}

//define this as a plug-in

DEFINE_FWK_MODULE(RPChscpFilter);


