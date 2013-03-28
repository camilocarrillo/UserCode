#ifndef GGeometry_GChamber_h
#define GGeometry_GChamber_h

/** \class GChamber
 *
 *  Model of a G chamber.
 *   
 *  A chamber is a GeomDet.
 *  The chamber is composed by 2 or 3 Roll (GeomDetUnit).
 *
 *  $Date: 2011/09/27 09:13:42 $
 *  $Revision: 1.4 $
 *  \author R. Trentadue
 */

#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "DataFormats/MuonDetId/interface/GDetId.h"

class GRoll;

class GChamber : public GeomDet {
public:
  /// Constructor
  GChamber(GDetId id, const ReferenceCountingPointer<BoundPlane>& plane);
  /// Destructor
  virtual ~GChamber();

  /// Return the GChamberId of this chamber
  GDetId id() const;

  // Which subdetector
  virtual SubDetector subDetector() const {return GeomDetEnumerators::GBarrel;}

  /// equal if the id is the same
  bool operator==(const GChamber& ch) const;

  /// Add Roll to the chamber which takes ownership
  void add(GRoll* rl);

  /// Return the rolls in the chamber
  virtual std::vector< const GeomDet*> components() const;

  /// Return the sub-component (roll) with a given id in this chamber
  virtual const GeomDet* component(DetId id) const;

  /// Return the Roll corresponding to the given id 
  const GRoll* roll(GDetId id) const;

  const GRoll* roll(int isl) const;
  
  /// Return the Rolls
  const std::vector<const GRoll*>& rolls() const;

  /// Retunr numbers of rolls
  int nrolls() const;

private:

  GDetId theId;

  // The chamber owns its Rolls
  std::vector<const GRoll*> theRolls;

};
#endif
