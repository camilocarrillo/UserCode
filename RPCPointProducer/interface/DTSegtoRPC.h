#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>

class RPCPoint{
 public:
  float x(){return _x;}
  float y(){return _y;}
  uint32_t rawId(){return _rawId;}
 
  RPCPoint(uint32_t rawId,float x, float y){
    _rawId=rawId;
    _x=x;
    _y=y;
  }
 private:
  uint32_t _rawId;
  float _x;
  float _y;
};

class DTSegtoRPC {
public:
  explicit DTSegtoRPC(edm::Handle<DTRecSegment4DCollection> all4DSegments,const edm::EventSetup& iSetup, const edm::Event& iEvent);
  ~DTSegtoRPC();
  int numberofsegments() {return _numberofsegments;}
  std::vector<RPCPoint> GetThePoints(){return _ThePoints;}
   
private:
  int _numberofsegments;
  std::vector<RPCPoint> _ThePoints; 
};

class DTStationIndex{
public: 
  DTStationIndex():_region(0),_wheel(0),_sector(0),_station(0){}
  DTStationIndex(int region, int wheel, int sector, int station) : 
    _region(region),
    _wheel(wheel),
    _sector(sector),
    _station(station){}
  ~DTStationIndex(){}
  int region() const {return _region;}
  int wheel() const {return _wheel;}
  int sector() const {return _sector;}
  int station() const {return _station;}
  bool operator<(const DTStationIndex& dtind) const{
    if(dtind.region()!=this->region())
      return dtind.region()<this->region();
    else if(dtind.wheel()!=this->wheel())
      return dtind.wheel()<this->wheel();
    else if(dtind.sector()!=this->sector())
      return dtind.sector()<this->sector();
    else if(dtind.station()!=this->station())
      return dtind.station()<this->station();
    return false;
  }

private:
  int _region;
  int _wheel;
  int _sector;
  int _station; 
};

class ObjectMap{
public:
  static ObjectMap* GetInstance(const edm::EventSetup& iSetup);
  std::set<RPCDetId> GetRolls(DTStationIndex dtstationindex){return mapInstance->rollstoreDT[dtstationindex];}
//protected:
  std::map<DTStationIndex,std::set<RPCDetId> > rollstoreDT;
  ObjectMap(const edm::EventSetup& iSetup);
private:
  static ObjectMap* mapInstance;
}; 

