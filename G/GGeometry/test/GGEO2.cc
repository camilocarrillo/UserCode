// -*- C++ -*-
//
// Package:    GGEO2
// Class:      GGEO2
// 
/**\class GGEO2 GGEO2.cc rpcgeo/GGEO2/src/GGEO2.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/91
//         Created:  Wed Sep 26 17:08:29 CEST 2007
// $Id: GGEO2.cc,v 1.2 2011/11/30 15:20:52 mmaggi Exp $
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
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

#include <DataFormats/GDigi/interface/GDigi.h>
#include <DataFormats/GDigi/interface/GDigiCollection.h>

#include <DataFormats/MuonDetId/interface/GDetId.h>
#include <Geometry/GGeometry/interface/GGeometry.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>

#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include <Geometry/GGeometry/interface/GGeomServ.h>

//
// class decleration
//

class GGEO2 : public edm::EDAnalyzer {
   public:
      explicit GGEO2(const edm::ParameterSet&);
      ~GGEO2();


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
GGEO2::GGEO2(const edm::ParameterSet& /*iConfig*/){
   //now do what ever initialization is needed
}


GGEO2::~GGEO2()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GGEO2::analyze(const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::cout <<" Getting the G Geometry"<<std::endl;
   edm::ESHandle<GGeometry> rpcGeo;
   iSetup.get<MuonGeometryRecord>().get(rpcGeo);

   for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
     if( dynamic_cast< GChamber* >( *it ) != 0 ){
       GChamber* ch = dynamic_cast< GChamber* >( *it ); 
       std::vector< const GRoll*> roles = (ch->rolls());
       
       //std::cout<<"G Chamber"<<ch->id()<<std::endl;
       
       for(std::vector<const GRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	 GDetId rpcId = (*r)->id();
	 //int stripsinthisroll=(*r)->nstrips();
	 GGeomServ rpcsrv(rpcId);
	 if (rpcId.region()==0){ 
	   //	   const RectangularStripTopology* top_= dynamic_cast<const RectangularStripTopology*> (&((*r)->topology()));
	   //	   float stripl = top_->stripLength();
	   //	   float stripw = top_->pitch();
	   const BoundPlane & GSurface = (*r)->surface();
	   GlobalPoint CenterPointRollGlobal = GSurface.toGlobal(LocalPoint(0,0,0));
	   std::cout<<rpcsrv.name()<<" "<<CenterPointRollGlobal.x()<<" "<<CenterPointRollGlobal.y()<<" "<<CenterPointRollGlobal.z()<<std::endl;
	   GlobalPoint i = GSurface.toGlobal(LocalPoint(1,0,0));
	   GlobalPoint j = GSurface.toGlobal(LocalPoint(0,1,0));
	   std::cout<<" i "<<i.x()<<" "<<i.y()<<" "<<i.z()<<std::endl;
	   std::cout<<" j "<<j.x()<<" "<<j.y()<<" "<<j.z()<<std::endl;

	   

	 }else{
	   //	   const TrapezoidalStripTopology* top_= dynamic_cast<const TrapezoidalStripTopology*> (&((*r)->topology()));
	   //	   float stripl = top_->stripLength();
	   //float stripw = top_->pitch();
	   const BoundPlane & GSurface = (*r)->surface();
	   GlobalPoint CenterPointRollGlobal = GSurface.toGlobal(LocalPoint(0,0,0));
	   std::cout<<rpcsrv.name()<<" "<<CenterPointRollGlobal.x()<<" "<<CenterPointRollGlobal.y()<<" "<<CenterPointRollGlobal.z()<<std::endl;
	 }
       }
     }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
GGEO2::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GGEO2::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GGEO2);
