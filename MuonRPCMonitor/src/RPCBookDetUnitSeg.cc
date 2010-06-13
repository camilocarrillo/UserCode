#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <MuonRPCMonitor/MuonRPCMonitor/interface/MuonRPCMonitor.h>
#include "DQMServices/Core/interface/MonitorElement.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
std::map<std::string, MonitorElement*> MuonRPCMonitor::bookDetUnitSeg(RPCDetId & detId) {
  
  std::map<std::string, MonitorElement*> meMap;
   
  //  dbe->setCurrentFolder("BX/");

  RPCGeomServ RPCname(detId);
  std::string nameRoll = RPCname.name();

  char detUnitLabel[128];
  char layerLabel[128];

  sprintf(detUnitLabel ,"%s",nameRoll.c_str());
  sprintf(layerLabel ,"%s",nameRoll.c_str());

  char meId [128];
  char meTitle [128];

  sprintf(meId,"BXMuon_%s",detUnitLabel);
  sprintf(meTitle,"BXMuon_%s",layerLabel);
  std::cout<<"Booking "<<nameRoll<<std::endl;
  meMap[meId] = dbe->book1D(meId, meTitle, 11,-5.5, 5.5);

  return meMap;
}



