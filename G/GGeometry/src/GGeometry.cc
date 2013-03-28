/** Implementation of the Model for G Geometry
 *
 *  \author M. Maggi - INFN Bari
 */

#include <Geometry/GGeometry/interface/GGeometry.h>
#include <Geometry/CommonDetUnit/interface/GeomDetUnit.h>

GGeometry::GGeometry(){}


GGeometry::~GGeometry()
{
  // delete all the chamber associated to the geometry
  //for (std::vector<GChamber*>::const_iterator ich = allChambers.begin();
  //      ich != allChambers.end(); ++ich){
  //  delete (*ich);
  //}
}  

 
const GGeometry::DetTypeContainer&  GGeometry::detTypes() const{
  return theRollTypes;
}


const GGeometry::DetUnitContainer& GGeometry::detUnits() const{
  return theRolls;
}


const GGeometry::DetContainer& GGeometry::dets() const{
  return theDets;
}

  
const GGeometry::DetIdContainer& GGeometry::detUnitIds() const{
  return theRollIds;
}


const GGeometry::DetIdContainer& GGeometry::detIds() const{
  return theDetIds;
}


const GeomDetUnit* GGeometry::idToDetUnit(DetId id) const{
  return dynamic_cast<const GeomDetUnit*>(idToDet(id));
}


const GeomDet* GGeometry::idToDet(DetId id) const{
  mapIdToDet::const_iterator i = theMap.find(id);
  return (i != theMap.end()) ?
    i->second : 0 ;
}

const std::vector<GChamber*>& GGeometry::chambers() const {
  return allChambers;
}

const std::vector<GRoll*>& GGeometry::rolls() const{
  return allRolls;
}

const GChamber* GGeometry::chamber(GDetId id) const{
  return dynamic_cast<const GChamber*>(idToDet(id.chamberId()));
}

const GRoll* GGeometry::roll(GDetId id) const{
  return dynamic_cast<const GRoll*>(idToDetUnit(id));
}


void
GGeometry::add(GRoll* roll){
  theDets.push_back(roll);
  allRolls.push_back(roll);
  theRolls.push_back(roll);
  theRollIds.push_back(roll->geographicalId());
  theDetIds.push_back(roll->geographicalId());
  GeomDetType* _t = const_cast<GeomDetType*>(&roll->type());
  theRollTypes.push_back(_t);
  theMap.insert(std::pair<DetId,GeomDetUnit*>
		(roll->geographicalId(),roll));
}

void
GGeometry::add(GChamber* chamber){
  allChambers.push_back(chamber);
  theDets.push_back(chamber);
  theDetIds.push_back(chamber->geographicalId());
  theMap.insert(std::pair<DetId,GeomDet*>
		(chamber->geographicalId(),chamber));
}
