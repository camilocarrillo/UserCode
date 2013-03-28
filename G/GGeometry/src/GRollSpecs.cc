#include "Geometry/GGeometry/interface/GRollSpecs.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"


using namespace GeomDetEnumerators;


GRollSpecs::GRollSpecs( SubDetector rss, const std::string& name, const GSpecs& pars)
  :  GeomDetType(name,rss),_p(pars),_n(name)
{
  if (rss == GBarrel ){
    int nstrip =static_cast<int>( _p[2]);
    float pitch = _p[0]*2/_p[2];
    float striplength = _p[1]*2;
    _top = new RectangularStripTopology(nstrip,pitch,striplength);
  }else if (rss == GEndcap ){
    float b = _p[0];
    float B = _p[1];
    float h = _p[2];
    float r0 = h*(B+b)/(B-b);
    float striplength = h*2;
    float strips = _p[3];
    float pitch = (b+B)/strips;
    int nstrip =static_cast<int>(strips);
  
    _top = new TrapezoidalStripTopology(nstrip,pitch,striplength,r0);
  } else {
    _top = 0;
  }
}


GRollSpecs::~GRollSpecs()
{
  if (_top)
    delete _top;
  _top=0;
}


const Topology& 
GRollSpecs::topology() const
{
  return *(_top);
}

const StripTopology& 
GRollSpecs::specificTopology() const
{
  return *(_top);
}


const std::string&
GRollSpecs::detName() const
{
  return _n;
}
