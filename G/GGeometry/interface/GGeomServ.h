#ifndef GGeometry_GGeomServ_h
#define GGeometry_GGeomServ_h

#include <string>
#include <vector>

class GDetId;
class GGeomServ{
 public:
  GGeomServ(const GDetId& id);
  virtual ~GGeomServ();
  virtual std::string shortname();
  virtual std::string name();
  virtual std::string chambername();
  virtual int eta_partition(); 
  virtual int chambernr();
  virtual int segment();
  virtual bool inverted();
  virtual bool zpositive();
  virtual bool aclockwise();
  std::vector<int> channelInChip();
 
protected:
  GGeomServ();
  
 protected:
  const GDetId* _id;
  std::string _n;
  std::string _sn;
  std::string _cn;
  int _t;
  int _cnr;
  bool _z;
  bool _a;

};
#endif
