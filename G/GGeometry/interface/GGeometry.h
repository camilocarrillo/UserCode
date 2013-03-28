#ifndef GGeometry_GGeometry_h
#define GGeometry_GGeometry_h

/** \class GGeometry
 *
 *  The model of the geometry of G.
 *
 *  \author M. Maggi - INFN Bari
 */

#include "DataFormats/DetId/interface/DetId.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/GGeometry/interface/GRoll.h"
#include "Geometry/GGeometry/interface/GChamber.h"
#include <vector>
#include <map>


class GeomDetType;
class GeomDetUnit;

class GGeometry : public TrackingGeometry {

 public:
  /// Default constructor
  GGeometry();

  /// Destructor
  virtual ~GGeometry();

  // Return a vector of all det types
  virtual const DetTypeContainer&  detTypes() const;

  // Return a vector of all GeomDetUnit
  virtual const DetUnitContainer& detUnits() const;

  // Return a vector of all GeomDet
  virtual const DetContainer& dets() const;
  
  // Return a vector of all GeomDetUnit DetIds
  virtual const DetIdContainer& detUnitIds() const;

  // Return a vector of all GeomDet DetIds
  virtual const DetIdContainer& detIds() const;

  // Return the pointer to the GeomDetUnit corresponding to a given DetId
  virtual const GeomDetUnit* idToDetUnit(DetId) const;

  // Return the pointer to the GeomDet corresponding to a given DetId
  virtual const GeomDet* idToDet(DetId) const;


  //---- Extension of the interface

  /// Return a vector of all G chambers
  const std::vector<GChamber*>& chambers() const;

  /// Return a vector of all G rolls
  const std::vector<GRoll*>& rolls() const;

  // Return a GChamber given its id
  const GChamber* chamber(GDetId id) const;

  /// Return a roll given its id
  const GRoll* roll(GDetId id) const;

  /// Add a G roll to the Geometry
  void add(GRoll* roll);

  /// Add a G roll to the Geometry
  void add(GChamber* ch);

 private:
  DetUnitContainer theRolls;
  DetContainer theDets;
  DetTypeContainer theRollTypes;
  DetIdContainer theRollIds;
  DetIdContainer theDetIds;
  
  // Map for efficient lookup by DetId 
  mapIdToDet theMap;

  std::vector<GRoll*> allRolls; // Are not owned by this class; are owned by their chamber.
  std::vector<GChamber*> allChambers; // Are owned by this class.

};

#endif
