// -*- C++ -*-
//
// Package:    HSCPHUNT
// Class:      HSCPHUNT
// 
/**\class HSCPHUNT HSCPHUNT.cc beta/HSCPHUNT/src/HSCPHUNT.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Mar 16 22:50:16 CET 2009
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
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/RPCDigi/interface/RPCDigiCollection.h>
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
 
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include <Geometry/RPCGeometry/interface/RPCRoll.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <DataFormats/TrackingRecHit/interface/TrackingRecHit.h>
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"

#include "TFile.h"
#include "TTree.h"
#include "TKey.h"

//
// class decleration
//

class HSCPHUNT : public edm::EDAnalyzer {
public:
  explicit HSCPHUNT(const edm::ParameterSet&);
  ~HSCPHUNT();
  edm::ESHandle <RPCGeometry> rpcGeo;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  
  int event;
  float phi;
  float beta;
  float eta;

  
  typedef struct {
    Int_t event;
    Float_t eta,phi,beta;
  } HSCP_RPC_CANDIDATE;
  
  HSCP_RPC_CANDIDATE myCandidate;
  TTree *ttreeOutput;
  TFile *f;
  
private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  float etarange(float eta1,float eta2,float eta3);
  float dist(float phi1,float phi2);
  float dist3(float phi1,float phi2,float phi3);
};


HSCPHUNT::HSCPHUNT(const edm::ParameterSet& iConfig){
  f = new TFile("HSCP_RPC_CANDIDATE.root", "RECREATE");
  ttreeOutput = new TTree("HSCP_RPC_CANDIDATE", "HSCP_RPC_CANDIDATE");
  ttreeOutput->Branch("event", &event, "event/I");
  ttreeOutput->Branch("eta", &eta ,"eta/F");
  ttreeOutput->Branch("phi", &phi, "phi/F");
  ttreeOutput->Branch("beta", &beta, "beta/F");
}


HSCPHUNT::~HSCPHUNT()
{
  f->Write();
  f->Close();
}

//
// member functions
//

typedef struct {
  int id;
  int bx;
  GlobalPoint gp;
} RPC4DHit;


bool bigmag(const RPC4DHit &Point1,const RPC4DHit &Point2){
  if((Point2).gp.mag() > (Point1).gp.mag()) return true;
  else return false;
}

float HSCPHUNT::etarange(float eta1,float eta2,float eta3){
  float etamax = eta1; 
  if(eta2>etamax) etamax = eta2;
  if(eta3>etamax) etamax = eta3;
  
  float etamin = eta1;
  if(eta2<etamin) etamin = eta2;
  if(eta3<etamin) etamin = eta3;
  
  return fabs(etamax-etamin);
} 

float HSCPHUNT::dist(float phi1,float phi2){
  if(fabs(phi1-phi2)>3.14159265) return 2*3.1415926535-fabs(phi1-phi2);
  else return fabs(phi1-phi2);
}

float HSCPHUNT::dist3(float phi1,float phi2,float phi3){
  return dist(phi1,phi2)+dist(phi2,phi3)+dist(phi3,phi1);
}

// ------------ method called to for each event  ------------
void
HSCPHUNT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   event = iEvent.id().event();

   Handle<RPCRecHitCollection> rpcRecHits; 
   iEvent.getByLabel("rpcRecHits","",rpcRecHits);

   int nRPC = 0;


   RPCRecHitCollection::const_iterator recHit;
      
   for (recHit = rpcRecHits->begin(); recHit != rpcRecHits->end(); recHit++) {
     //    RPCDetId id = (RPCDetId)(*recHit).rpcId();
     //    LocalPoint rhitlocal = (*recHit).localPosition();
     nRPC++;
   }


   std::cout<<"The Number of Rec Hits is "<<nRPC<<std::endl;

   std::vector<RPC4DHit> BestAngularMatch;
   std::vector<RPC4DHit> GlobalRPC4DHits;
   std::vector<RPC4DHit> GlobalRPC4DHitsNoBx0;

   int k=0;
   
   for (recHit = rpcRecHits->begin(); recHit != rpcRecHits->end(); recHit++) {
     RPCDetId rollId = (RPCDetId)(*recHit).rpcId();
     RPCGeomServ rpcsrv(rollId);
     LocalPoint recHitPos=recHit->localPosition();    
     const RPCRoll* rollasociated = rpcGeo->roll(rollId);
     const BoundPlane & RPCSurface = rollasociated->surface(); 
     GlobalPoint RecHitInGlobal = RPCSurface.toGlobal(recHitPos);
     
     int BX = recHit->BunchX();
     std::cout<<"\t \t We have an RPC Rec Hit! bx="<<BX<<" Roll="<<rpcsrv.name()<<" Global Position="<<RecHitInGlobal<<std::endl;
     
     RPC4DHit ThisHit;
     ThisHit.bx =  BX;
     ThisHit.gp = RecHitInGlobal;
     ThisHit.id = k;
     GlobalRPC4DHits.push_back(ThisHit);
     if(BX!=0)GlobalRPC4DHitsNoBx0.push_back(ThisHit);
     k++;
   }
   
   assert(nRPC==int(GlobalRPC4DHits.size()));

   if(GlobalRPC4DHitsNoBx0.size()==0){
     std::cout<<"No Chances for HSCPs"<<std::endl;
   }   
   
   float minangularspread = 100.;
   float minetaspread = 100.;
   
   for(std::vector<RPC4DHit>::iterator Point = GlobalRPC4DHitsNoBx0.begin(); Point!=GlobalRPC4DHitsNoBx0.end(); ++Point){ 
     for(std::vector<RPC4DHit>::iterator Point2 = GlobalRPC4DHits.begin(); Point2!=GlobalRPC4DHits.end(); ++Point2){if(Point2->id!=Point->id){
       for(std::vector<RPC4DHit>::iterator Point3 = Point2; Point3!=GlobalRPC4DHits.end(); ++Point3){if(Point3->id!=Point2->id && Point3->id!=Point->id){
	 float angularspread = dist3(Point->gp.phi().value(),Point2->gp.phi().value(),Point3->gp.phi().value()); 
	 if(angularspread<minangularspread){
	   minangularspread = angularspread;
	   std::cout<<"For phi"<< Point->gp.phi()<<" "<<Point2->gp.phi()<<" "<<Point3->gp.phi()<<std::endl;
	   phi=(Point->gp.phi().value()+Point2->gp.phi().value()+Point3->gp.phi().value())/3.; //implementar average
	   
	   float etaspread = etarange(float(Point->gp.eta()),float(Point2->gp.eta()),float(Point3->gp.eta()));
	   if(etaspread<0.2){
	     minetaspread = etaspread;
	     std::cout<<"For eta"<<Point->gp.eta()<<" "<<Point2->gp.eta()<<" "<<Point3->gp.eta()<<std::endl;
	     eta = (float(Point->gp.eta())+float(Point2->gp.eta())+float(Point3->gp.eta()))/3.;
	     BestAngularMatch.clear();
	     BestAngularMatch.push_back(*Point);
	     BestAngularMatch.push_back(*Point2);
	     BestAngularMatch.push_back(*Point3);
	   }
	 }
       }}
     }}
   }

   bool hscp = false;
   bool increasingbx = false;
 
   if(minetaspread!=100.){
     std::cout<<" candidate phi="<<phi<<" angularspread"<<minangularspread<<std::endl;
     std::cout<<" candidate eta="<<eta<<" etaspread"<<minetaspread<<std::endl;
     
     std::sort(BestAngularMatch.begin(), BestAngularMatch.end(), bigmag);
     
     int lastbx=-7; 
     
     hscp = true;
     
     for(std::vector<RPC4DHit>::iterator Point = BestAngularMatch.begin(); Point!=BestAngularMatch.end(); ++Point){
       bool thisbx = false;           
       if(lastbx<=Point->bx){
	 thisbx = true;
	 if(lastbx!= -7 && lastbx<Point->bx){
	   increasingbx=true;
	 }
	 std::cout<<Point->gp.mag()<<" "<<Point->bx<<" comparing "<<lastbx<<" with "<<Point->bx<<" Increasing bool="<<increasingbx<<std::endl;
       }
       hscp = hscp*thisbx;
       lastbx = Point->bx; 
     }
     std::cout<<std::endl;
   }
   
   std::cout<<" bool Increasing BX "<<increasingbx<<std::endl;
   
   hscp = hscp*increasingbx;
   
   if(hscp){ 
     std::cout<<" Candidate phi="<<phi<<" eta="<<eta<<std::endl;
     beta =0;
     ttreeOutput->Fill();
   }
   else std::cout<<"No Candidate HSCP"<<std::endl;
   
}
// ------------ method called once each job just before starting event loop  ------------

void HSCPHUNT::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HSCPHUNT::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HSCPHUNT);
