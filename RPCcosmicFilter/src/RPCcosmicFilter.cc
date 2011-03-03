// -*- C++ -*-
//
// Package:    RPCcosmicFilter
// Class:      RPCcosmicFilter
// 
/**\class RPCcosmicFilter RPCcosmicFilter.cc RPCHSCPFilter/RPCcosmicFilter/src/RPCcosmicFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Thu Jun 10 11:34:48 CEST 2010
// $Id: RPCcosmicFilter.cc,v 1.2 2011/03/03 15:24:37 carrillo Exp $
//
//


// system include files
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "RecoMuon/MeasurementDet/interface/MuonDetLayerMeasurements.h"
#include "TrackingTools/PatternTools/interface/TrajMeasLessEstim.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/Navigation/interface/DirectMuonNavigation.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "TrackingTools/MeasurementDet/interface/TrajectoryMeasurementGroup.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/RPCGeometry/interface/RPCRoll.h> 
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCParticle.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TH2F.h"
#include <TStyle.h>

//
// class declaration
//

class RPCcosmicFilter : public edm::EDFilter {
   public:
  explicit RPCcosmicFilter(const edm::ParameterSet& );
      ~RPCcosmicFilter();
      edm::ESHandle<RPCGeometry> rpcGeo;
      std::vector<unsigned int> blacklist;
      bool firstbook;
      
      TFile * theFileOut;

      TH1F * statistics;
      TH1F * phidistro;
      TH1F * etadistro;
      TH1F * etadistroupleg;
      TH1F * etadistrodownleg;
      TH1F * bxupleg;
      TH1F * bxdownleg;
      TH1F * hitshisto;      
      TH1F * hitsupleghisto;
      TH1F * hitsdownleghisto;
      TH1F * hitsupleghistoeta;
      TH1F * hitsdownleghistoeta;
      TH2F * phiscatter;
      TH2F * etascatter;
      TH2F * bxscatter;
      TH1F * muondistro;
      TH1F * bxdiff;

      std::string  m_trackTag;
      std::string rootFileNameCal;
      int MinRPCRecHits;
      double synchth;
      double minIntegral;
      double minMean;
  private:
      edm::InputTag rpcRecHitsLabel;
      virtual void beginJob();
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endRun() ;
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
RPCcosmicFilter::RPCcosmicFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  MinRPCRecHits = iConfig.getUntrackedParameter<int>("MinRPCRecHits");
  rootFileNameCal =iConfig.getUntrackedParameter<std::string>("rootFileNameCal");
  synchth = iConfig.getUntrackedParameter<double>("synchth");
  minIntegral = iConfig.getUntrackedParameter<double>("minIntegral");
  minMean = iConfig.getUntrackedParameter<double>("minMean");

  bxupleg = new TH1F("bxupleg","bxupleg",7,-3.5,3.5);
  bxdownleg = new TH1F("bxdownleg","bxdownleg",7,-3.5,3.5);
  hitshisto = new TH1F("hits","hits",21,-0.5,20.5);
  hitsupleghisto = new TH1F("hitsupleg","hitsupleg",21,-0.5,20.5);
  hitsdownleghisto = new TH1F("hitsdownleg","hitsdownleg",21,-0.5,20.5);
  hitsupleghistoeta = new TH1F("hitsuplegeta","hitsuplegeta",21,-0.5,20.5);
  hitsdownleghistoeta = new TH1F("hitsdownlegeta","hitsdownlegeta",21,-0.5,20.5);
  phidistro = new TH1F("phidistro","phidistro",100,-3.141592,3.141592);
  etadistro = new TH1F("etadistro","etadistro",100,-2.5,2.5);
  etadistroupleg = new TH1F("etadistroupleg","etadistroupleg",100,-2.5,2.5);
  etadistrodownleg = new TH1F("etadistrodownleg","etadistrodownleg",100,-2.5,2.5);
  statistics = new TH1F("statistics","statistics",8,-0.5,7.5);
  phiscatter = new TH2F("phiscatter","phiscatter",1000,-3.141592,3.141592,1000,-3.141592,3.141592);
  etascatter = new TH2F("etascatter","etascatter",100,-2.5,2.5,1000,-2.5,2.5);
  bxscatter = new TH2F("bxscatter","bxscatter",70,-3.5,3.5,70,-3.5,3.5);
  muondistro = new TH1F("muondistro","muondistro",10,-0.5,9.5);
  bxdiff = new TH1F("bxdiff","bxdiff up - down",100,-6,6);
}


RPCcosmicFilter::~RPCcosmicFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------

bool IsBadRoll(uint32_t rawId,std::vector<uint32_t> thelist){
  bool isBadRoll = false;
  if(!(find(thelist.begin(),thelist.end(),rawId)==thelist.end())){
    isBadRoll=true;
  }
  return isBadRoll;
}


float nullifbacktoback(float phi1,float phi2){
  float diffphi = fabs(phi1 - phi2);
  if(diffphi>3.14159265358979) return 2*3.14159265358979-diffphi-3.14159265358979;
  else if(diffphi < -3.14159265358979) return 2*3.1415926535+diffphi-3.14159265358979;
  else return diffphi-3.14159265358979;
}

bool
RPCcosmicFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackTag,trackCollectionHandle);

  std::cout <<"\t Getting the RPC RecHits"<<std::endl;
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);
  
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  
  std::cout<<"\t Loop on all the reconstructed muons"<<std::endl;
  std::cout<<"\t There are "<<trackCollectionHandle->size()<<" muon tracks in this event"<<std::endl;
  
  statistics->Fill(0); //number of analyzed events
  
  muondistro->Fill(trackCollectionHandle->size());
  
  if(trackCollectionHandle->size()==2){
    statistics->Fill(1); //number of analyzed events with two muons
    reco::TrackCollection::const_iterator leg1 = trackCollectionHandle->begin();
    reco::TrackCollection::const_iterator leg2 = leg1+1; 
    reco::TrackCollection::const_iterator upleg; 
    reco::TrackCollection::const_iterator downleg; 
    
    phidistro->Fill(leg1->phi());
    phidistro->Fill(leg2->phi());

    etadistro->Fill(leg1->eta());
    etadistro->Fill(leg2->eta());
    
    if(leg1->phi()>0 && leg2->phi()<0){
      upleg = leg1;
      downleg = leg2;
    }else{
      upleg = leg2;
      downleg = leg1;
    }
    
    phiscatter->Fill(upleg->phi(),downleg->phi());
    etascatter->Fill(upleg->eta(),downleg->eta());
    etadistrodownleg->Fill(downleg->eta());
    etadistroupleg->Fill(downleg->eta());

    //upleg
    float aveupleg = 0;
    float hitsupleg = 0;
    std::cout<<"\t going with leg 1"<<std::endl;
    for(trackingRecHit_iterator recHit = upleg->recHitsBegin(); recHit != upleg->recHitsEnd(); ++recHit){
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue; //Is a hit in the Muon System?
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue; //Is an RPC Hit?
      std::cout<<"\t \t 1/6 Is a hit in the Muon System? "<<std::endl;
      std::cout<<"\t \t 2/6 Is an RPCHit? "<<std::endl;
      std::cout<<"\t \t 3/6 Is a valid hit? "<<std::endl;
      if (!(*recHit)->isValid()) continue; //Is Valid
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  rpcHits->get(rollId);
      RPCRecHitCollection::const_iterator recHitC;
      int size = 0;
      int clusterS=0;
      std::cout<<"\t \t \t Looping on the rechits of the same roll"<<std::endl;
      for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) {
	clusterS=(*recHitC).clusterSize(); 
	RPCDetId rollId = (RPCDetId)(*recHitC).geographicalId();
	std::cout<<"\t \t \t \t"<<rollId<<" bx "<<(*recHitC).BunchX()<<std::endl;
	size++;
      }
      std::cout<<"\t \t 5/6 Is the only RecHit in this roll.? size = "<<size<<std::endl;
      if(size>1) continue; //Is the only RecHit in this roll.?
      int bx = ((RPCRecHit*)(&(**recHit)))->BunchX();
      bxupleg->Fill(bx);
      aveupleg=aveupleg+bx;
      hitsupleg++;
    }
    //now downleg
    float avedownleg = 0;
    float hitsdownleg = 0;
    std::cout<<"\t going with leg 1"<<std::endl;
    for(trackingRecHit_iterator recHit = downleg->recHitsBegin(); recHit != downleg->recHitsEnd(); ++recHit){
      if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue; //Is a hit in the Muon System?
      if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue; //Is an RPC Hit?
      std::cout<<"\t \t 1/6 Is a hit in the Muon System? "<<std::endl;
      std::cout<<"\t \t 2/6 Is an RPCHit? "<<std::endl;
      std::cout<<"\t \t 3/6 Is a valid hit? "<<std::endl;
      if (!(*recHit)->isValid()) continue; //Is Valid
      RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  rpcHits->get(rollId);
      RPCRecHitCollection::const_iterator recHitC;
      int size = 0;
      int clusterS=0;
      std::cout<<"\t \t \t Looping on the rechits of the same roll"<<std::endl;
      for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) {
	clusterS=(*recHitC).clusterSize(); 
	RPCDetId rollId = (RPCDetId)(*recHitC).geographicalId();
	std::cout<<"\t \t \t \t"<<rollId<<" bx "<<(*recHitC).BunchX()<<std::endl;
	size++;
      }
      std::cout<<"\t \t 5/6 Is the only RecHit in this roll.? size = "<<size<<std::endl;
      if(size>1) continue; //Is the only RecHit in this roll.?
      int bx = ((RPCRecHit*)(&(**recHit)))->BunchX();
      bxdownleg->Fill(bx);
      avedownleg=avedownleg+bx;
      hitsdownleg++;
    }
  
    hitsupleghisto->Fill(hitsupleg);
    hitsdownleghisto->Fill(hitsdownleg);
    
    if(fabs(upleg->eta())>=1.6) hitsupleghistoeta->Fill(hitsupleg);
    if(fabs(downleg->eta())>=1.6)  hitsdownleghistoeta->Fill(hitsdownleg);

    hitshisto->Fill(hitsupleg+hitsdownleg);

    if(hitsupleg!=0) statistics->Fill(2); //number of analyzed events with two muons and hits in the upper leg
    if(hitsdownleg!=0) statistics->Fill(3); //number of analyzed events with two muons and hits in the down leg
    
    if(hitsupleg != 0 && hitsdownleg!=0){
      statistics->Fill(4); //number of analyzed events with two muons and hits in both legs
      aveupleg = aveupleg/hitsupleg;
      std::cout<<"the averupleg = "<<aveupleg<<" "<<hitsupleg<<std::endl;
      avedownleg = avedownleg/hitsdownleg;
      std::cout<<"the averdownleg = "<<avedownleg<<std::endl;
      std::cout<<"Filling the Histogram"<<std::endl;
      bxscatter->Fill(aveupleg,avedownleg);
      bxdiff->Fill(aveupleg-avedownleg);
      if(aveupleg <= -0.5 && avedownleg>=-0.5){
	statistics->Fill(5);
	statistics->Fill(7);
	return true;
      }
    }else if(hitsupleg==0 && fabs(upleg->eta())>=1.6){
      statistics->Fill(6);
      statistics->Fill(7);
      return true;
    }
  }
  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCcosmicFilter::beginJob(){
  std::cout<<"Begin Job"<<std::endl;
  firstbook = true;
  theFileOut = new TFile("cosmics.root", "RECREATE");
}

void
 RPCcosmicFilter::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::cout<<"Begin Run"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------

void 
RPCcosmicFilter::endRun(){
}

void 
RPCcosmicFilter::endJob(){
  std::cout<<"end Job"<<std::endl;
  std::cout<<"saving File"<<std::endl;

  statistics->GetXaxis()->SetBinLabel(1,"Ev. Analyzed");
  statistics->GetXaxis()->SetBinLabel(2,"2 mu Ev"); 
  statistics->GetXaxis()->SetBinLabel(3,"RPChits up-leg");
  statistics->GetXaxis()->SetBinLabel(4,"RPChits down-leg");
  statistics->GetXaxis()->SetBinLabel(5,"RPChits both-legs");
  statistics->GetXaxis()->SetBinLabel(6,"Cosmic BX");
  statistics->GetXaxis()->SetBinLabel(7,"Cosmic No hits up leg");
  statistics->GetXaxis()->SetBinLabel(8,"Cosmic OR Both");
  statistics->GetXaxis()->SetLabelSize(0.03);
  
  bxupleg->GetXaxis()->SetTitle("bx");
  bxdownleg->GetXaxis()->SetTitle("bx");
  hitsdownleghisto->GetXaxis()->SetTitle("RPC hits down leg");
  hitsupleghisto->GetXaxis()->SetTitle("RPC hits up leg");
  hitshisto->GetXaxis()->SetTitle("RPC hits both");
  phidistro->GetXaxis()->SetTitle("phi");
  etadistro->GetXaxis()->SetTitle("eta");
  etadistroupleg->GetXaxis()->SetTitle("eta up leg");
  etadistrodownleg->GetXaxis()->SetTitle("eta down leg");

  phiscatter->GetXaxis()->SetTitle("phi up leg");
  phiscatter->GetYaxis()->SetTitle("phi down leg");

  etascatter->GetXaxis()->SetTitle("eta up leg");
  etascatter->GetYaxis()->SetTitle("eta down leg");

  bxscatter->GetXaxis()->SetTitle("Average bx up leg");
  bxscatter->GetYaxis()->SetTitle("Average bx down leg");

  muondistro->GetXaxis()->SetTitle("Number of muons");
  bxdiff->GetXaxis()->SetTitle("<bx up> - <bx down>");

  TCanvas * Ca0;

  gStyle->SetPalette(1);

  Ca0 = new TCanvas("Ca5a","Scatter Angle Plots",800,600);
  Ca0->Clear();
  hitshisto->Draw();
  Ca0->SaveAs("hitshisto.png");Ca0->Clear();
  hitsupleghisto->Draw();
  hitsupleghistoeta->SetFillColor(2);
  hitsupleghistoeta->Draw("same");
  Ca0->SaveAs("hitsupleghisto.png");Ca0->Clear();
  hitsdownleghisto->Draw();
  hitsdownleghistoeta->SetFillColor(2);
  hitsdownleghistoeta->Draw("same");
  Ca0->SaveAs("hitsdownleghisto.png");Ca0->Clear();
  phidistro->Draw();
  Ca0->SaveAs("phidistro.png");Ca0->Clear();
  etadistro->Draw();
  Ca0->SaveAs("etadistro.png");Ca0->Clear();
  etadistroupleg->Draw();
  Ca0->SaveAs("etadistroupleg.png");Ca0->Clear();
  etadistrodownleg->Draw();
  Ca0->SaveAs("etadistrodownleg.png");Ca0->Clear();
  bxdiff->Draw();
  Ca0->SaveAs("bxdiff.png");Ca0->Clear();
  bxscatter->Draw();
  bxscatter->SetDrawOption("COLZ");
  Ca0->SaveAs("bxscatter.png");Ca0->Clear();
  phiscatter->Draw();
  phiscatter->SetDrawOption("COLZ");
  Ca0->SaveAs("phiscatter.png");Ca0->Clear();
  etascatter->Draw();
  etascatter->SetDrawOption("COLZ");
  Ca0->SaveAs("etascatter.png");Ca0->Clear();
  Ca0->SetLogy();
  bxupleg->Draw();
  Ca0->SaveAs("bxupleg.png");Ca0->Clear();
  Ca0->SetLogy();
  bxdownleg->Draw();
  Ca0->SaveAs("bxdownleg.png");Ca0->Clear();
  Ca0->SetLogy();
  muondistro->Draw();
  Ca0->SaveAs("muondistro.png");Ca0->Clear();
  Ca0->SetLogy();
  statistics->Draw();
  Ca0->SaveAs("statistics.png");Ca0->Clear();

  theFileOut->cd();
  bxupleg->Write();
  bxdownleg->Write();
  hitshisto->Write();
  hitsupleghisto->Write();
  hitsdownleghisto->Write();
  hitsupleghistoeta->Write();
  hitsdownleghistoeta->Write();
  phidistro->Write();
  etadistro->Write();
  etadistrodownleg->Write();
  etadistroupleg->Write();
  phiscatter->Write();
  etascatter->Write();
  statistics->Write();
  bxscatter->Write();
  muondistro->Write();
  theFileOut->Write();
  theFileOut->Close();

}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCcosmicFilter);
