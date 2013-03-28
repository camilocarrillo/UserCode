#include "Geometry/GGeometry/interface/GRoll.h"
#include "Geometry/GGeometry/interface/GRollSpecs.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"


GRoll::GRoll(GDetId id, BoundPlane::BoundPlanePointer bp, GRollSpecs* rrs) :
  GeomDetUnit(bp), _id(id),_rrs(rrs)
{
  setDetId(id);
}

GRoll::~GRoll()
{
  delete _rrs; //Assume the roll owns it specs (specs are not shared)
}

const  GRollSpecs*
GRoll::specs() const
{
  return _rrs;
}

GDetId
GRoll::id() const
{
  return _id;
}

const Topology&
GRoll::topology() const
{
  return _rrs->topology();
}

const GeomDetType& 
GRoll::type() const
{
  return (*_rrs);
}

const GChamber* GRoll::chamber() const {
  return theCh;
}

int 
GRoll::nstrips() const
{
  return this->specificTopology().nstrips();
}

LocalPoint
GRoll::centreOfStrip(int strip) const
{
  float s = static_cast<float>(strip)-0.5;
  return this->specificTopology().localPosition(s);
}

LocalPoint
GRoll::centreOfStrip(float strip) const
{
  return this->specificTopology().localPosition(strip);
}

LocalError
GRoll::localError(float strip) const
{
  return this->specificTopology().localError(strip,1./sqrt(12.));
}

float
GRoll::strip(const LocalPoint& lp) const
{ 
  return this->specificTopology().strip(lp);

}

float
GRoll::localPitch(const LocalPoint& lp) const
{ 
  return this->specificTopology().localPitch(lp);

}

float
GRoll::pitch() const
{ 
  return this->specificTopology().pitch();

}

bool
GRoll::isBarrel() const
{
  return ((this->id()).region()==0);
}  

bool 
GRoll::isForward() const

{
  return (!this->isBarrel());
} 



const StripTopology&
GRoll::specificTopology() const
{
  return _rrs->specificTopology();
}




void
GRoll::setChamber(const GChamber* ch)
{
  theCh = ch; 
}
