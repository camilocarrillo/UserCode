// -*- C++ -*-
//
// Package:    DIGIANALIZER
// Class:      DIGIANALIZER
// 
/**\class DIGIANALIZER DIGIANALIZER.cc beta/DIGIANALIZER/src/DIGIANALIZER.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Mon Mar 16 23:08:11 CET 2009
// $Id: DIGIANALIZER.cc,v 1.1 2009/03/22 21:29:54 carrillo Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

//
// class decleration
//

class DIGIANALIZER : public edm::EDAnalyzer {
   public:
      explicit DIGIANALIZER(const edm::ParameterSet&);
      ~DIGIANALIZER();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DIGIANALIZER::DIGIANALIZER(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


DIGIANALIZER::~DIGIANALIZER()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DIGIANALIZER::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<RPCDigiCollection> rpcDigis;
   iEvent.getByLabel("simMuonRPCDigis", rpcDigis);
   //iEvent.getByType(rpcDigis);
   
   RPCDigiCollection::DigiRangeIterator rpcDigiCI;

   int digisBarrel=0;
   int digisForward=0;
   int digisBackward=0;
   
   for(rpcDigiCI = rpcDigis->begin();rpcDigiCI!=rpcDigis->end();rpcDigiCI++){
     //std::cout<<(*rpcDigiCI).first<<endl;;
     const RPCDigiCollection::Range& range = (*rpcDigiCI).second;
     int region = (*rpcDigiCI).first.region();
     for (RPCDigiCollection::const_iterator digiIt = range.first;digiIt!=range.second;++digiIt){
       
       std::cout<<*digiIt<<std::endl;
       std::cout<<"Strip number: "<<digiIt->strip()<<std::endl;
       if(region==0) digisBarrel++;
       else if(region==1) digisForward++;
       else if(region==-1) digisBackward++;
     }
   }
   
   std::cout<<digisBarrel<<" "<<digisForward<<" "<<digisBackward<<std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
DIGIANALIZER::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DIGIANALIZER::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DIGIANALIZER);
