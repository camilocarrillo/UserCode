// -*- C++ -*-
//
// Package:    GGEO_POSTLS1
// Class:      GGEO_POSTLS1
// 
/**\class GGEO_POSTLS1 GGEO_POSTLS1.cc rpcgeo/GGEO_POSTLS1/src/GGEO_POSTLS1.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/91
//         Created:  Wed Sep 26 17:08:29 CEST 2007
// $Id: GGEO_POSTLS1.cc,v 1.1 2013/03/25 17:13:45 carrillo Exp $
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

class GGEO_POSTLS1 : public edm::EDAnalyzer {
   public:
      explicit GGEO_POSTLS1(const edm::ParameterSet&);
      ~GGEO_POSTLS1();


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
GGEO_POSTLS1::GGEO_POSTLS1(const edm::ParameterSet& /*iConfig*/){
   //now do what ever initialization is needed
}


GGEO_POSTLS1::~GGEO_POSTLS1()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GGEO_POSTLS1::analyze(const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::cout <<" Getting the G Geometry"<<std::endl;
   edm::ESHandle<GGeometry> rpcGeo;
   iSetup.get<MuonGeometryRecord>().get(rpcGeo);

   float areaendcap=0;
   int sumstripwendcap=0;

   for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
     if( dynamic_cast< GChamber* >( *it ) != 0 ){
       GChamber* ch = dynamic_cast< GChamber* >( *it ); 
       std::vector< const GRoll*> roles = (ch->rolls());
       for(std::vector<const GRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	 GDetId rpcId = (*r)->id();
	 int stripsinthisroll=(*r)->nstrips();
	 GGeomServ rpcsrv(rpcId);
	 
	 if(rpcId.region()!=0 && rpcId.station()==4){
	   std::cout<<rpcId<<rpcsrv.name()<<" strips="<<stripsinthisroll<<std::endl;
	   
	   const TrapezoidalStripTopology* top_= dynamic_cast<const TrapezoidalStripTopology*> (&((*r)->topology()));
	   float s1 = static_cast<float>(1)-0.5;
	   float sLast = static_cast<float>(stripsinthisroll)-0.5;
	   float stripl = top_->stripLength();
	   float stripw = top_->pitch();
	   areaendcap = areaendcap + stripw*stripl*stripsinthisroll;
	   sumstripwendcap=sumstripwendcap+stripw*stripsinthisroll;
	   
	   std::cout<<" AllInfo"<<rpcsrv.name()<<" stripl="<<stripl<<" stripw="<<stripw<<" stripsinthisroll="<<stripsinthisroll<<" area roll="<<stripl*stripw<<" area total endcap="<<areaendcap<<std::endl;
	   const BoundPlane & GSurface = (*r)->surface();
	   GlobalPoint FirstStripCenterPointInGlobal = GSurface.toGlobal(top_->localPosition(s1));
	   GlobalPoint LastStripCenterPointInGlobal = GSurface.toGlobal(top_->localPosition(sLast));
	   
	   double rpcphiFirst = FirstStripCenterPointInGlobal.barePhi();//*180./3.141592;
	   double rpcphiLast  = LastStripCenterPointInGlobal.barePhi();//*180./3.141592;

	   //double rpcYFirst = FirstStripCenterPointInGlobal.y();
	   //double rpcYLast  = LastStripCenterPointInGlobal.y();

	   double diff=rpcphiLast-rpcphiFirst;
	   
	   double rollphi = (rpcphiFirst+rpcphiLast)*0.5*180./3.141592;
	     
	   double orientation=diff/fabs(diff);

	   int seg=rpcsrv.segment();

	   std::cout<<rpcsrv.name()<<" midlephi="<<rollphi<<" "<<orientation<<" seg="<<seg
		    <<" First.phi="<<rpcphiFirst<<" First.Y="<<FirstStripCenterPointInGlobal.y()
		    <<"  Last.phi="<<rpcphiLast<<" Last.Y="<<LastStripCenterPointInGlobal.y()
		    <<" Last.X="<<LastStripCenterPointInGlobal.x()
		    <<" Last.Z="<<LastStripCenterPointInGlobal.z();	   
	 }
       }
     }
   }

  
}


// ------------ method called once each job just before starting event loop  ------------
void 
GGEO_POSTLS1::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GGEO_POSTLS1::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GGEO_POSTLS1);
