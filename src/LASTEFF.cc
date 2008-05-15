// -*- C++ -*-
//
// Package:    LASTEFF
// Class:      LASTEFF
// 
/**\class LASTEFF LASTEFF.cc LASTEFF/LASTEFF/src/LASTEFF.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/45
//         Created:  Tue May 13 12:23:34 CEST 2008
// $Id$
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
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "FWCore/Framework/interface/ESHandle.h"

//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TTree.h"

//
// class decleration
//

class TFile;

class LASTEFF : public edm::EDAnalyzer {
   public:
      explicit LASTEFF(const edm::ParameterSet&);
      ~LASTEFF();
  
      TFile * theFile;
      TFile * theFileout;

  TH1F * histoRPC;
  TH1F * histoDT;
  TH1F * histoRPC_2D;
  TH1F * histoDT_2D;
  TH1F * histoeffIdRPC_DT_2D;
  TH1F * histoeffIdRPC_DT;
  


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string file;

  
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
LASTEFF::LASTEFF(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed


  file=iConfig.getUntrackedParameter<std::string>("fileName");


}


LASTEFF::~LASTEFF()
{}


void 
LASTEFF::beginJob(const edm::EventSetup&)
{
  theFile = new TFile(file.c_str());
  theFileout = new TFile("output.root", "RECREATE");
}


void
LASTEFF::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  
  //   Read Tree named "T" in memory. Tree pointer is assigned the same name

  bool first=false;
  std::cout <<"\t Getting the RPC Geometry"<<std::endl;
  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if( dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	RPCGeomServ rpcsrv(rpcId);

	if(rpcId.region()==0&&rpcId.ring()==0&&rpcId.sector()==1){
	
	  char detUnitLabel[128];

	  char meIdRPC [128];
	  char meIdDT [128];
	  
	  char meIdRPC_2D [128];
	  char meIdDT_2D [128];
	
	  char effIdRPC_DT [128];
	  char effIdRPC_DT_2D [128];
	

	  std::string regionName;
	  std::string ringType;
	  char  folder[120];

	  if(rpcId.region()==0) {
	    regionName="Barrel";
	    ringType="Wheel";
	  }
	  else{
	    ringType="Disk";
	    if(rpcId.region() == -1) regionName="Endcap-";
	    if(rpcId.region() ==  1) regionName="Endcap+";
	  }
	
	  sprintf(folder,"DQMData/RPC/MuonSegEff/%s/%s_%d/station_%d/sector_%d",
		  regionName.c_str(),ringType.c_str(),rpcId.ring(),rpcId.station(),rpcId.sector());
	  sprintf(detUnitLabel ,"%s",rpcsrv.name().c_str());
	
	  sprintf(meIdRPC,"%s/RPCDataOccupancyFromDT_%s",folder,detUnitLabel);
	  sprintf(meIdRPC_2D,"%s/RPCDataOccupancy2DFromDT_%s",folder,detUnitLabel);
	
	  sprintf(meIdDT,"%s/ExpectedOccupancyFromDT_%s",folder,detUnitLabel);
	  sprintf(meIdDT_2D,"%s/ExpectedOccupancy2DFromDT_%s",folder,detUnitLabel);

	  sprintf(effIdRPC_DT,"%s/EfficienyFromDTExtrapolation_%s",folder,detUnitLabel);
	  sprintf(effIdRPC_DT_2D,"%s/EfficienyFromDT2DExtrapolation_%s",folder,detUnitLabel);


	  std::cout<<"Before If..."<<std::endl;
	  if(histoRPC!=0  &&  histoDT!=0 && histoRPC_2D!=0 && histoDT_2D!=0 && histoeffIdRPC_DT_2D!=0 && histoeffIdRPC_DT!=0){
	  //if(!theFile->cd(folder)){
	    std::cout<<"No empty Histogram"<<std::endl;
	    std::cout<<folder<<std::endl;
	    
	    histoRPC= (TH1F*)theFile->Get(meIdRPC);
	    histoDT= (TH1F*)theFile->Get(meIdDT);
	    histoRPC_2D= (TH1F*)theFile->Get(meIdRPC_2D);
	    histoDT_2D= (TH1F*)theFile->Get(meIdDT_2D);
	    histoeffIdRPC_DT_2D= (TH1F*)theFile->Get(effIdRPC_DT_2D);
	    histoeffIdRPC_DT = (TH1F*)theFile->Get(effIdRPC_DT);
	    
	  
	  
	    for(unsigned int i=1;i<=100;++i){
	      if(histoDT->GetBinContent(i) != 0){
		float eff = histoRPC->GetBinContent(i)/histoDT->GetBinContent(i);
		float erreff = sqrt(eff*(1-eff)/histoDT->GetBinContent(i));
		histoeffIdRPC_DT->SetBinContent(i,eff*100.);
		histoeffIdRPC_DT->SetBinError(i,erreff*100.);
		std::cout<<"Bin Content"<<histoDT->GetBinContent(i)<<std::endl;
	      }
	    }
	
	    for(unsigned int i=1;i<=100;++i){
	      for(unsigned int j=1;j<=200;++j){
		if(histoDT_2D->GetBinContent(i,j) != 0){
		  float eff = histoRPC_2D->GetBinContent(i,j)/histoDT_2D->GetBinContent(i,j);
		  float erreff = sqrt(eff*(1-eff)/histoDT_2D->GetBinContent(i,j));
		  histoeffIdRPC_DT_2D->SetBinContent(i,j,eff*100.);
		  histoeffIdRPC_DT_2D->SetBinError(i,j,erreff*100.);
		}
	      }
	    }

	    std::cout<<"cd outputfile folder"<<std::endl;
	    if(first){
	      theFileout->cd();
	      first=false;
	    }
	    histoRPC->Write();
	    histoDT->Write();
	    histoRPC_2D->Write();
	    histoDT_2D->Write();
	    histoeffIdRPC_DT_2D->Write();
	    histoeffIdRPC_DT->Write();
	  }
	}
      }
    }
  }
  theFileout->Close();
  theFile->Close();
}


// ------------ method called once each job just after ending the event loop  ------------
void 
LASTEFF::endJob(){
    
}

//define this as a plug-in
DEFINE_FWK_MODULE(LASTEFF);
