/* This Class Header */
#include "Geometry/GGeometry/interface/GChamber.h"

/* Collaborating Class Header */
#include "Geometry/GGeometry/interface/GRoll.h"


/* C++ Headers */
#include <iostream>

/* ====================================================================== */

/* Constructor */ 
GChamber::GChamber(GDetId id, 
		       const ReferenceCountingPointer<BoundPlane> & plane) :
  GeomDet(plane), theId(id)
{
  setDetId(id);
}

/* Destructor */ 
GChamber::~GChamber() {
}


GDetId
GChamber::id() const
{
  return theId;
}

/* Operations */ 

bool 
GChamber::operator==(const GChamber& ch) const {
  return this->id()==ch.id();
}



void 
GChamber::add(GRoll* rl) {
  theRolls.push_back(rl);
}



std::vector<const GeomDet*> 
GChamber::components() const {
  return  std::vector<const GeomDet*>(theRolls.begin(), theRolls.end());
}



const GeomDet* 
GChamber::component(DetId id) const {
  return roll(GDetId(id.rawId()));
}


const std::vector<const GRoll*>& 
GChamber::rolls() const 
{
  return theRolls;
}

int
GChamber::nrolls() const
{
  return theRolls.size();
}

const GRoll* 
GChamber::roll(GDetId id) const
{
  if (id.chamberId()!=theId) return 0; // not in this Roll!
  return roll(id.roll());
}


const GRoll* 
GChamber::roll(int isl) const 
{
  for (std::vector<const GRoll*>::const_iterator i = theRolls.begin();
       i!= theRolls.end(); ++i) {
    if ((*i)->id().roll()==isl) 
      return (*i);
  }
  return 0;
}

