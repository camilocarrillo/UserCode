#ifndef Geometry_GSimAlgo_GRoll_H
#define Geometry_GSimAlgo_GRoll_H

#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "DataFormats/MuonDetId/interface/GDetId.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

class StripTopology;
class GRollSpecs;
class GChamber;
class GRoll : public GeomDetUnit{

 public:
  
  GRoll(GDetId id, BoundPlane::BoundPlanePointer bp, GRollSpecs* rrs);
  ~GRoll();
  const GRollSpecs* specs() const;
  GDetId id() const;
  const Topology& topology() const;
  const StripTopology& specificTopology() const;
  const GeomDetType& type() const; 
 
  /// Return the chamber this roll belongs to 
  const GChamber* chamber() const;
  
  int nstrips() const;

  LocalPoint  centreOfStrip(int strip) const;
  LocalPoint  centreOfStrip(float strip) const;
  LocalError  localError(float strip) const;

  float strip(const LocalPoint& lp) const;
  float pitch() const;
  float localPitch(const LocalPoint& lp) const; 
  bool isBarrel() const; 
  bool isForward() const;
  
 private:
  void setChamber(const GChamber* ch);

 private:
  GDetId _id;
  GRollSpecs* _rrs;
  const GChamber* theCh; // NOT owned
};

#endif
