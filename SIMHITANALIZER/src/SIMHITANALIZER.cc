// -*- C++ -*-
//
// Package:    SIMHITANALIZER
// Class:      SIMHITANALIZER
// 
/**\class SIMHITANALIZER SIMHITANALIZER.cc beta/SIMHITANALIZER/src/SIMHITANALIZER.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Feb 23 15:41:52 CET 2009
// $Id: SIMHITANALIZER.cc,v 1.3 2010/06/17 09:16:42 carrillo Exp $
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

#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include <Geometry/RPCGeometry/interface/RPCRoll.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>



#include <cmath>

//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"

//Track
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

//
// class decleration
//

class SIMHITANALIZER : public edm::EDAnalyzer {
public:
  explicit SIMHITANALIZER(const edm::ParameterSet&);
  ~SIMHITANALIZER();
  edm::ESHandle <RPCGeometry> rpcGeo;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  
private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginJob();
  virtual void endJob() ;
  // ----------member data ---------------------------
  TFile * theFile;
  TH1F * St1R1;
  TH1F * St2R1;
  TH1F * St3R1;
  TH1F * St4R1;
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
SIMHITANALIZER::SIMHITANALIZER(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
}


SIMHITANALIZER::~SIMHITANALIZER()
{

}

void
SIMHITANALIZER::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   std::cout << " Getting the SimHits " <<std::endl;
   std::vector<edm::Handle<edm::PSimHitContainer> > theSimHitContainers;
   iEvent.getManyByType(theSimHitContainers);
   std::cout << " The Number of sim Hits is  " << theSimHitContainers.size() <<std::endl;
   
   //SimTrack Stuff

   std::vector<PSimHit> theSimHits;
   
   for (int i = 0; i < int(theSimHitContainers.size()); i++){
     theSimHits.insert(theSimHits.end(),theSimHitContainers.at(i)->begin(),theSimHitContainers.at(i)->end());
   } 

   for (std::vector<PSimHit>::const_iterator iHit = theSimHits.begin(); iHit != theSimHits.end(); iHit++){
     
     if(abs((*iHit).particleType())== 13){//Only Muons
      
       DetId theDetUnitId((*iHit).detUnitId());
       
       DetId simdetid= DetId((*iHit).detUnitId());

       if(simdetid.det()==DetId::Muon &&  simdetid.subdetId()== MuonSubdetId::RPC){//Only RPCs
 
	 RPCDetId rollId(theDetUnitId);
	 RPCGeomServ rpcsrv(rollId);
	 
	 //std::cout << " Reading the Roll"<<std::endl;
	 const RPCRoll* rollasociated = rpcGeo->roll(rollId);
	 
	 //std::cout << " Getting the Surface"<<std::endl;
	 const BoundPlane & RPCSurface = rollasociated->surface(); 
	 
	 GlobalPoint SimHitInGlobal = RPCSurface.toGlobal((*iHit).localPosition());

	 if(rollId.region()==0) continue; //skip barrel
	 if(abs(rollId.ring())!=1) continue; //skip other rings
	 
	 if(rollId.station()==1){ St1R1->Fill((*iHit).timeOfFlight()); std::cout<<"Hit in Ring 1 Station 1"<<std::endl;}
	 if(rollId.station()==2){ St2R1->Fill((*iHit).timeOfFlight()); std::cout<<"Hit in Ring 1 Station 2"<<std::endl;}
	 if(rollId.station()==3){ St3R1->Fill((*iHit).timeOfFlight()); std::cout<<"Hit in Ring 1 Station 3"<<std::endl;}
	 if(rollId.station()==4){ St4R1->Fill((*iHit).timeOfFlight()); std::cout<<"Hit in Ring 1 Station 4"<<std::endl;}
	 
	 std::cout<<"\t\t We have an RPC Sim Hit! in t="<<(*iHit).timeOfFlight()<<"ns "<<rpcsrv.name()<<" Global postition="<<SimHitInGlobal<<std::endl;

	 std::cout<<"\t\t r="<<SimHitInGlobal.mag()<<" phi="<<SimHitInGlobal.phi()<<" eta="<<SimHitInGlobal.eta()<<std::endl;
       }
     }
   }
}



// ------------ method called once each job just before starting event loop  ------------
void 
SIMHITANALIZER::beginRun(const edm::Run& run, const edm::EventSetup& iSetup)
{
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
SIMHITANALIZER::beginJob() {
  theFile = new TFile("GDetector_ToF.root","RECREATE");
  St1R1 = new TH1F("St1R1","St1R1",500,15,40); 
  St2R1 = new TH1F("St2R1","St2R1",500,15,40); 
  St3R1 = new TH1F("St3R1","St3R1",500,15,40); 
  St4R1 = new TH1F("St4R1","St4R1",500,15,40); 
}

void 
SIMHITANALIZER::endJob() {
  theFile->cd();
  std::cout<<"saving root files"<<std::endl;
  St1R1->Write();
  St2R1->Write();
  St3R1->Write();
  St4R1->Write();
  theFile->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(SIMHITANALIZER);
