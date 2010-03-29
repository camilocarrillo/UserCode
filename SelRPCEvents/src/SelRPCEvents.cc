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
//
// Original Author:  Marcello Maggi
//         Created:  Mon Nov 17 14:01:33 CET 2008
// $Id: SelRPCEvents.cc,v 1.3 2010/03/19 14:19:59 carrillo Exp $
//
//

// system include files
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <set>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
// class declaration
//

class SelRPCEvents : public edm::EDFilter {
public:
  explicit SelRPCEvents(const edm::ParameterSet&);
  ~SelRPCEvents();
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
      // ----------member data ---------------------------
private:
  std::map<int, std::set<int> > evts;

      
};

SelRPCEvents::SelRPCEvents(const edm::ParameterSet& iConfig)
{
 
 std::string fname("selection.txt");
  std::ifstream ifin(fname.c_str());
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
  bool selected=false;
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
SelRPCEvents::beginJob(const edm::EventSetup&)
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
SelRPCEvents::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelRPCEvents);
