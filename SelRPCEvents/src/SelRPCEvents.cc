// -*- C++ -*-
//
// Package:    SelRPCEvents
// Class:      SelRPCEvents
// 
/**\class SelRPCEvents SelRPCEvents.cc Analysis/SelRPCEvents/src/SelRPCEvents.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/

#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

class SelRPCEvents : public edm::EDFilter {
public:
  explicit SelRPCEvents(const edm::ParameterSet&);
  ~SelRPCEvents();
  
private:
  virtual void beginRun(const edm::Run&,const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endRun() ;
  std::string eventsfile;  
  std::map<int, std::set<int> > evts;

      
};

SelRPCEvents::SelRPCEvents(const edm::ParameterSet& iConfig)
{
  eventsfile = iConfig.getUntrackedParameter<std::string>("eventsfile","selection.txt");
  std::cout<<"eventsfile "<<eventsfile<<std::endl;
  std::string fname(eventsfile.c_str());
  std::ifstream ifin(fname.c_str());
  std::cout<<"file name "<<fname.c_str()<<std::endl;
  int run;
  int eve;
  while (ifin.good()){
    run =0;
    ifin >>run >>eve;
    if (run > 0){
      std::set<int> elis;
      if(evts.find(run) != evts.end()){
	elis=evts[run];
      }
      elis.insert(eve);
      evts[run]=elis;
      std::cout<<"loading map run="<<run<<" event="<<eve<<std::endl;
    }
  }
}



SelRPCEvents::~SelRPCEvents()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called on each new Event  ------------
bool SelRPCEvents::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){
  int evt = iEvent.id().event();
  int run = iEvent.id().run();
  std::cout <<"Filtering .... Event "<<run<<"   "<<evt<<std::endl;
  if(evts.find(run)!=evts.end()){
    std::set<int> elis=evts[run];
    if (elis.find(evt)!=elis.end()){
      std::cout <<" ==> Bad Event: RUN="<<run<<" EVT="<<evt<<std::endl;
      std::cout <<"Passed "<<run<<"   "<<evt<<std::endl;
      return true;
    }
  }
  std::cout <<"Event skipped "<<run<<"   "<<evt<<std::endl;
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
SelRPCEvents::beginRun(const edm::Run&,const edm::EventSetup&)
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
SelRPCEvents::endRun() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelRPCEvents);
