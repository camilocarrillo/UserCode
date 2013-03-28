#ifndef Geometry_GSimAlgo_GRollSpecs_H
#define Geometry_GSimAlgo_GRollSpecs_H

/** \class GRollSpecs
 *  Storage of the parameters of the G Chamber
 *  using standard topologies
 *
 * \author M. Maggi - INFN Bari
 *
 */
#include <vector>
#include <string>

class StripTopology;

#include "Geometry/CommonDetUnit/interface/GeomDetType.h"


class GRollSpecs : public GeomDetType {

 public:
  typedef std::vector<float> GSpecs;

  GRollSpecs( SubDetector rss, const std::string& name, const GSpecs& pars);

  ~GRollSpecs();

  const Topology& topology() const;

  const StripTopology& specificTopology() const;

  const std::string& detName() const;

 private:
  StripTopology* _top;
  std::vector<float> _p;
  std::string _n;

};
#endif
