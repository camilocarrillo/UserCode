// -*- C++ -*-
//
// Package:    GCSC
// Class:      GCSC
// 
/**\class GCSC GCSC.cc TESTCSCG/GCSC/src/GCSC.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
 */
//
// Original Author:  Haiyun Teng
//         Created:  Wed Feb 25 18:09:15 CET 2009
// $Id: GCSC.cc,v 1.7 2011/10/18 13:23:18 yana Exp $
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

#include <memory>
#include "FWCore/Framework/interface/MakerMacros.h"
#include <DataFormats/MuonDetId/interface/GDetId.h>
#include <Geometry/GGeometry/interface/GGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>
#include <Geometry/GGeometry/interface/GGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCChamber.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>

//
// class decleration
//
class CSCStationIndex{
    public:
        CSCStationIndex():_region(0),_station(0),_ring(0),_chamber(0){}
        CSCStationIndex(int region, int station, int ring, int chamber):
            _region(region),
            _station(station),
            _ring(ring),
            _chamber(chamber){}
        ~CSCStationIndex(){}
        int region() const {return _region;}
        int station() const {return _station;}
        int ring() const {return _ring;}
        int chamber() const {return _chamber;}
        bool operator<(const CSCStationIndex& cscind) const{
            if(cscind.region()!=this->region())
                return cscind.region()<this->region();
            else if(cscind.station()!=this->station())
                return cscind.station()<this->station();
            else if(cscind.ring()!=this->ring())
                return cscind.ring()<this->ring();
            else if(cscind.chamber()!=this->chamber())
                return cscind.chamber()<this->chamber();
            return false;
        }

    private:
        int _region;
        int _station;
        int _ring;  
        int _chamber;
};

class GCSC : public edm::EDAnalyzer {
    public:
        explicit GCSC(const edm::ParameterSet&);
        ~GCSC();


    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

        // ----------member data ---------------------------
        std::map<CSCStationIndex,std::set<GDetId> > rollstoreCSC;
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





GCSC::GCSC(const edm::ParameterSet& /*iConfig*/)

{
    //now do what ever initialization is needed

}


GCSC::~GCSC()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}



// ------------ method called to for each event  ------------
void GCSC::beginJob() {
}


// ------------ method called once each job just before starting event loop  ------------
void 
GCSC::analyze(const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup)
{
  using namespace std;
  edm::ESHandle<GGeometry> pGGeom;
  iSetup.get<MuonGeometryRecord>().get(pGGeom);
  const GGeometry* rpcGeometry = (const GGeometry*)&*pGGeom;
  edm::ESHandle<CSCGeometry> pCSCGeom;
  iSetup.get<MuonGeometryRecord>().get(pCSCGeom);
  const CSCGeometry* cscGeometry = (const CSCGeometry*)&*pCSCGeom;

  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeometry->dets().begin();it<rpcGeometry->dets().end();it++){
    if(dynamic_cast< GChamber* >( *it ) != 0 ){
      GChamber* ch = dynamic_cast< GChamber* >( *it ); 
      std::vector< const GRoll*> roles = (ch->rolls());
      for(std::vector<const GRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	GDetId rpcId = (*r)->id();
	int region=rpcId.region();
	//booking all histograms
	GGeomServ rpcsrv(rpcId);
	std::string nameRoll = rpcsrv.name();
	//std::cout<<"Booking for "<<nameRoll<<std::endl;
	
	if(region!=0){
// 	  const TrapezoidalStripTopology* topE_=dynamic_cast<const TrapezoidalStripTopology*>(&((*r)->topology()));
// 	  float stripl = topE_->stripLength();
// 	  float stripw = topE_->pitch();
	  int region=rpcId.region();
          int station=rpcId.station();
          int ring=rpcId.ring();
          int cscring=ring;
          int cscstation=station;
	  GGeomServ rpcsrv(rpcId);
	  int rpcsegment = rpcsrv.segment(); //This replace rpcsrv.segment();
	  //std::cout<<"My segment="<<mySegment(rpcId)<<" GeomServ="<<rpcsrv.segment()<<std::endl;
	  int cscchamber = rpcsegment;//FIX THIS ACCORDING TO GGeomServ::segment()Definition
          if((station==2||station==3)&&ring==3){//Adding Ring 3 of G to the CSC Ring 2
            cscring = 2;
          }
	  
	  CSCStationIndex ind(region,cscstation,cscring,cscchamber);
          std::set<GDetId> myrolls;
	  if (rollstoreCSC.find(ind)!=rollstoreCSC.end()){
            myrolls=rollstoreCSC[ind];
          }
          myrolls.insert(rpcId);
          rollstoreCSC[ind]=myrolls;

	}
      }
    }
  }
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeometry->dets().begin();it<rpcGeometry->dets().end();it++){
    if( dynamic_cast< GChamber* >( *it ) != 0 ){
      GChamber* ch = dynamic_cast< GChamber* >( *it );                                                                         std::vector< const GRoll*> roles = (ch->rolls());                                                                          for(std::vector<const GRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){                              
	GDetId rpcId = (*r)->id();
	int region = rpcId.region();                                        
	if(region!=0 && (rpcId.ring()==2 || rpcId.ring()==3)){                                                    
       	  int region=rpcId.region();                                                                                         
          int station=rpcId.station();                                                                                       
          int ring=rpcId.ring();                                                                                             
	  int cscring = ring;
	  
	  if((station==2||station==3)&&ring==3) cscring = 2; //CSC Ring 2 covers rpc ring 2 & 3                              


          int cscstation=station;                                                                                            
          GGeomServ rpcsrv(rpcId);                                                                                         
          int rpcsegment = rpcsrv.segment();                                                                                 
                                                                                                                             
                                                                                                                                       
          int cscchamber = rpcsegment+1;                                                                                     
          if(cscchamber==37)cscchamber=1;                                                                                    
          CSCStationIndex ind(region,cscstation,cscring,cscchamber);                                                         
	  std::set<GDetId> myrolls;                                                                                        
          if (rollstoreCSC.find(ind)!=rollstoreCSC.end())myrolls=rollstoreCSC[ind];                                          
          myrolls.insert(rpcId);                                                                                             
          rollstoreCSC[ind]=myrolls;                                                                                         
                                                                                                                             
          cscchamber = rpcsegment-1;                                                                                         
          if(cscchamber==0)cscchamber=36;                                                                                    
          CSCStationIndex indDos(region,cscstation,cscring,cscchamber);                                                      
	  std::set<GDetId> myrollsDos;                                                                                     
          if (rollstoreCSC.find(indDos)!=rollstoreCSC.end()) myrollsDos=rollstoreCSC[indDos];                                 
          myrollsDos.insert(rpcId);                                                                                          
          rollstoreCSC[indDos]=myrollsDos;                                                                                      
                                                                                                                             
        }            
      }
    }
  }


  //adding more rpcs 



  // Now check binding
  const std::vector<CSCChamber*> cscChambers = cscGeometry->chambers();
  for(std::vector<CSCChamber*>::const_iterator CSCChamberIter = cscChambers.begin(); CSCChamberIter != cscChambers.end(); CSCChamberIter++){   
    
    CSCDetId CSCId = (*CSCChamberIter)->id();

    int cscEndCap = CSCId.endcap();
    int cscStation = CSCId.station();
    int cscRing = CSCId.ring();
//     int cscChamber = CSCId.chamber();
    int rpcRegion = 1; if(cscEndCap==2) rpcRegion= -1;//Relacion entre las endcaps
    int rpcRing = cscRing;
    if(cscRing==4)rpcRing =1;
    int rpcStation = cscStation;
    int rpcSegment = CSCId.chamber();


    //std::cout<<"CSC \t \t Getting chamber from Geometry"<<std::endl;
    const CSCChamber* TheChamber=cscGeometry->chamber(CSCId); 
    //std::cout<<"CSC \t \t Getting ID from Chamber"<<std::endl;

    std::set<GDetId> rollsForThisCSC = rollstoreCSC[CSCStationIndex(rpcRegion,rpcStation,rpcRing,rpcSegment)];
    if(CSCId.ring()!=1) std::cout<<"CSC for"<<CSCId<<" "<<rollsForThisCSC.size()<<" rolls."<<std::endl;

    for (std::set<GDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++){
      const GRoll* rollasociated = rpcGeometry->roll(*iteraRoll);
      GDetId rpcId = rollasociated->id();
      GGeomServ rpcsrv(rpcId);

      const BoundPlane & GSurface = rollasociated->surface(); 
      
      GlobalPoint CenterPointRollGlobal = GSurface.toGlobal(LocalPoint(0,0,0));
      GlobalPoint CenterPointCSCGlobal = TheChamber->toGlobal(LocalPoint(0,0,0));
      
      //LocalPoint CenterRollinCSCFrame = TheChamber->toLocal(CenterPointRollGlobal);

      float rpcphi=0;
      float cscphi=0;
      
      (CenterPointRollGlobal.barePhi()<0)? 
	rpcphi = 2*3.141592+CenterPointRollGlobal.barePhi():rpcphi=CenterPointRollGlobal.barePhi();
      
      (CenterPointCSCGlobal.barePhi()<0)? 
	cscphi = 2*3.1415926536+CenterPointCSCGlobal.barePhi():cscphi=CenterPointCSCGlobal.barePhi();
      
      float df=fabs(cscphi-rpcphi); 
      float dr=fabs(CenterPointRollGlobal.perp()-CenterPointCSCGlobal.perp());
      float diffz=CenterPointRollGlobal.z()-CenterPointCSCGlobal.z();
      float dfg=df*180./3.14159265;
      
      std::cout<<"CSC \t "<<rpcsrv.segment()<<rpcsrv.name()<<" dr="<<dr<<" dz="<<diffz<<" dfg="<<dfg<<std::endl;

      bool print = false;

      if((dr>200.||fabs(diffz)>55.||dfg>1.) && print){ 
	std::cout<<"\t \t problem CSC Station= "<<CSCId.station()
	  <<" Ring= "<<CSCId.ring()
	  <<" Chamber= "<<CSCId.chamber()
	  <<" cscphi="<<cscphi*180/3.14159265
	  <<"\t G Station= "<<rpcId.station()
	  <<" ring= "<<rpcId.ring()
          <<" segment =-> "<<rpcsrv.segment()
	  <<" rollphi="<<rpcphi*180/3.14159265
	  <<"\t dfg="<<dfg
	  <<" dz="<<diffz
	  <<" dr="<<dr
	  <<std::endl;
		    
      }
    }
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GCSC::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GCSC);
