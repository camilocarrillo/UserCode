#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Analysis/RPCPointProducer/interface/DTSegtoRPC.h>

ObjectMap* ObjectMap::mapInstance = NULL;

ObjectMap* ObjectMap::GetInstance(const edm::EventSetup& iSetup){
  if (mapInstance == NULL){
    mapInstance = new ObjectMap(iSetup);
  }
  return mapInstance;
}

ObjectMap::ObjectMap(const edm::EventSetup& iSetup){
  edm::ESHandle<RPCGeometry> rpcGeo;
  edm::ESHandle<DTGeometry> dtGeo;
  
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  iSetup.get<MuonGeometryRecord>().get(dtGeo);
  
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	int region=rpcId.region();
	if(region==0){
	  int wheel=rpcId.ring();
	  int sector=rpcId.sector();
	  int station=rpcId.station();
	  DTStationIndex ind(region,wheel,sector,station);
	  std::set<RPCDetId> myrolls;
	  if (rollstoreDT.find(ind)!=rollstoreDT.end()) myrolls=rollstoreDT[ind];
	  myrolls.insert(rpcId);
	  rollstoreDT[ind]=myrolls;
	}
      }
    }
  }
}

DTSegtoRPC::DTSegtoRPC(edm::Handle<DTRecSegment4DCollection> all4DSegments, const edm::EventSetup& iSetup,const edm::Event& iEvent ){

  edm::ESHandle<RPCGeometry> rpcGeo;
  edm::ESHandle<DTGeometry> dtGeo;
  
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  iSetup.get<MuonGeometryRecord>().get(dtGeo);

  _numberofsegments = 0;
  bool debug = true;
  
  _numberofsegments=all4DSegments->size();

  if(debug) std::cout<<"\t Number of DT Segments in this event = "<<_numberofsegments<<std::endl;
  
  std::map<DTChamberId,int> DTSegmentCounter;
  DTRecSegment4DCollection::const_iterator segment;  
  
  for (segment = all4DSegments->begin();segment!=all4DSegments->end(); ++segment){
    DTSegmentCounter[segment->chamberId()]++;
  }
  
  for (segment = all4DSegments->begin(); segment != all4DSegments->end(); ++segment){
    
    DTChamberId DTId = segment->chamberId();
    
    if(debug) std::cout<<"DT  \t \t This Segment is in Chamber id: "<<DTId<<std::endl;
    if(debug) std::cout<<"DT  \t \t Number of segments in this DT = "<<DTSegmentCounter[DTId]<<std::endl;
    if(debug) std::cout<<"DT  \t \t Is the only one in this DT? and is not in the 4th Station?"<<std::endl;
    
    if(DTSegmentCounter[DTId]!=1 || DTId.station()==4){
      if(debug) std::cout<<"DT \t \t More than one segment in this chamber, or we are in Station 4"<<std::endl;
      continue;
    }
 
    int dtWheel = DTId.wheel();
    int dtStation = DTId.station();
    int dtSector = DTId.sector();      

    LocalPoint segmentPosition= segment->localPosition();
    LocalVector segmentDirection=segment->localDirection();
    
    const GeomDet* gdet=dtGeo->idToDet(segment->geographicalId());
    const BoundPlane & DTSurface = gdet->surface();
      
    //check if the dimension of the segment is 4 

    if(debug) std::cout<<"DT  \t \t Is the segment 4D?"<<std::endl;
    
    if(segment->dimension()!=4){
      if(debug) std::cout<<"DT  \t \t no"<<std::endl;
      continue; 
    }

    if(debug) std::cout<<"DT  \t \t yes"<<std::endl;
    if(debug) std::cout<<"DT  \t \t DT Segment Dimension "<<segment->dimension()<<std::endl; 
	
    float Xo=segmentPosition.x();
    float Yo=segmentPosition.y();
    float Zo=segmentPosition.z();
    float dx=segmentDirection.x();
    float dy=segmentDirection.y();
    float dz=segmentDirection.z();

    std::cout<<"Calling to Object Map class"<<std::endl;
    ObjectMap* TheObject = ObjectMap::GetInstance(iSetup);
    std::cout<<"Creating the DTIndex"<<std::endl;
    DTStationIndex theindex(0,dtWheel,dtSector,dtStation);
    std::cout<<"Getting the Rolls for the given index"<<std::endl;
    
    std::set<RPCDetId> rollsForThisDT = TheObject->GetInstance(iSetup)->GetRolls(theindex);
    
    if(debug) std::cout<<"DT  \t \t Number of rolls for this DT = "<<rollsForThisDT.size()<<std::endl;
    
    assert(rollsForThisDT.size()>=1);
    
    if(debug) std::cout<<"DT  \t \t Loop over all the rolls asociated to this DT"<<std::endl;
    for (std::set<RPCDetId>::iterator iteraRoll = rollsForThisDT.begin();iteraRoll != rollsForThisDT.end(); iteraRoll++){
      const RPCRoll* rollasociated = rpcGeo->roll(*iteraRoll);
      RPCDetId rpcId = rollasociated->id();
      const BoundPlane & RPCSurface = rollasociated->surface(); 
      
      RPCGeomServ rpcsrv(rpcId);
      std::string nameRoll = rpcsrv.name();
      
      if(debug) std::cout<<"DT  \t \t \t RollName: "<<nameRoll<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t Doing the extrapolation to this roll"<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t DT Segment Direction in DTLocal "<<segmentDirection<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t DT Segment Point in DTLocal "<<segmentPosition<<std::endl;
	  
      GlobalPoint CenterPointRollGlobal = RPCSurface.toGlobal(LocalPoint(0,0,0));
      
      LocalPoint CenterRollinDTFrame = DTSurface.toLocal(CenterPointRollGlobal);
      
      if(debug) std::cout<<"DT  \t \t \t Center (0,0,0) Roll In DTLocal"<<CenterRollinDTFrame<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t Center (0,0,0) of the Roll in Global"<<CenterPointRollGlobal<<std::endl;
      
      float D=CenterRollinDTFrame.z();
      
      float X=Xo+dx*D/dz;
      float Y=Yo+dy*D/dz;
      float Z=D;
      
      const RectangularStripTopology* top_= dynamic_cast<const RectangularStripTopology*> (&(rollasociated->topology()));
      LocalPoint xmin = top_->localPosition(0.);
      if(debug) std::cout<<"DT  \t \t \t xmin of this  Roll "<<xmin<<"cm"<<std::endl;
      LocalPoint xmax = top_->localPosition((float)rollasociated->nstrips());
      if(debug) std::cout<<"DT  \t \t \t xmax of this  Roll "<<xmax<<"cm"<<std::endl;
      float rsize = fabs( xmax.x()-xmin.x() );
      if(debug) std::cout<<"DT  \t \t \t Roll Size "<<rsize<<"cm"<<std::endl;
      float stripl = top_->stripLength();
      float stripw = top_->pitch();
      
      if(debug) std::cout<<"DT  \t \t \t Strip Lenght "<<stripl<<"cm"<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t Strip Width "<<stripw<<"cm"<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t X Predicted in DTLocal= "<<X<<"cm"<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t Y Predicted in DTLocal= "<<Y<<"cm"<<std::endl;
      if(debug) std::cout<<"DT  \t \t \t Z Predicted in DTLocal= "<<Z<<"cm"<<std::endl;
      
      float extrapolatedDistance = sqrt((X-Xo)*(X-Xo)+(Y-Yo)*(Y-Yo)+(Z-Zo)*(Z-Zo));
      
      float MaxD = 150;
      
      if(debug) std::cout<<"DT  \t \t \t Is the distance of extrapolation less than MaxD? ="<<extrapolatedDistance<<"cm"<<"MaxD="<<MaxD<<"cm"<<std::endl;
      
      if(extrapolatedDistance<=MaxD){ 
	if(debug) std::cout<<"DT  \t \t \t yes"<<std::endl;   
	GlobalPoint GlobalPointExtrapolated = DTSurface.toGlobal(LocalPoint(X,Y,Z));
	if(debug) std::cout<<"DT  \t \t \t Point ExtraPolated in Global"<<GlobalPointExtrapolated<< std::endl;
	LocalPoint PointExtrapolatedRPCFrame = RPCSurface.toLocal(GlobalPointExtrapolated);
	
	if(debug) std::cout<<"DT  \t \t \t Point Extrapolated in RPCLocal"<<PointExtrapolatedRPCFrame<< std::endl;
	if(debug) std::cout<<"DT  \t \t \t Corner of the Roll = ("<<rsize*0.5<<","<<stripl*0.5<<")"<<std::endl;
	if(debug) std::cout<<"DT \t \t \t Info About the Point Extrapolated in X Abs ("<<fabs(PointExtrapolatedRPCFrame.x())<<","
			   <<fabs(PointExtrapolatedRPCFrame.y())<<","<<fabs(PointExtrapolatedRPCFrame.z())<<")"<<std::endl;
	if(debug) std::cout<<"DT  \t \t \t Does the extrapolation go inside this roll?"<<std::endl;

	if(fabs(PointExtrapolatedRPCFrame.z()) < 1. && 
	   fabs(PointExtrapolatedRPCFrame.x()) < rsize*0.6 && 
	   fabs(PointExtrapolatedRPCFrame.y()) < stripl*0.6){
	  if(debug) std::cout<<"DT  \t \t \t \t yes"<<std::endl;	
	  RPCDetId  rollId = rollasociated->id();
	  RPCGeomServ rpcsrv(rollId);
	  if(debug) std::cout<<" RawId"<<rollId.rawId()<<std::endl;
	  if(debug) std::cout<<" Name"<<rpcsrv.name()<<std::endl;
	  RPCPoint thisPoint(rollId.rawId(),PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
	  
	  _ThePoints.push_back(thisPoint);
	  
	  if(debug) std::cout<<"DT  \t \t \t \t Fill "<<thisPoint.rawId()<<" "<<thisPoint.x()<<" "<<thisPoint.y()
			     <<std::endl;
	}else {
	  if(debug) std::cout<<"DT \t \t \t \t No the prediction is outside of this roll"<<std::endl;
	}//Condition for the right match
      }else{
	if(debug) std::cout<<"DT \t \t \t No, Exrtrapolation too long!, canceled"<<std::endl;
      }//D so big
    }//loop over all the rolls asociated
  }
}

DTSegtoRPC::~DTSegtoRPC(){
}
