// -*- C++ -*-
//
// Package:    CLSPT
// Class:      CLSPT
// 
/**\class CLSPT CLSPT.cc CLSPT/CLSPT/src/CLSPT.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,42 R-021,+41227671624,
//         Created:  Thu May 17 01:32:34 CEST 2012
// $Id: CLSPT.cc,v 1.5 2012/05/17 22:39:30 carrillo Exp $
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
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"


#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/getRef.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"


#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"

// ROOT stuff
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>


//using namespace std;

//
// class declaration
//

class CLSPT : public edm::EDAnalyzer {
   public:
      explicit CLSPT(const edm::ParameterSet&);
      ~CLSPT();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  TFile * theFileCal;
  TH1F * theHisto;
  std::string  m_trackTag;
  edm::InputTag rpcRecHitsLabel;

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

  std::string rootFileName;
      
  TFile* theFile;
      
  TH1F * muonMultiplicity;
  
  TH1F * recHitMultiplicity;
  TH1F * rpcrecHitMultiplicity;
  TH1F * chi2;
  TH1F * dxy;
  
  TH1F * trackobservedeta;
  TH1F * trackobservedphi;
  TH1F * trackobservedp;
  TH1F * trackobservedpt;

  TH2F * clspt;
  TH1F * ptAllcls;  

  TH2F * RB1in; 
  TH2F * RB1out;
  TH2F * RB2in;
  TH2F * RB2out;
  TH2F * RB3;
  TH2F * RB4;


  TGraphErrors * meanclspt;    

  TGraphErrors * meanRB1in;
  TGraphErrors * meanRB1out;
  TGraphErrors * meanRB2in;
  TGraphErrors * meanRB2out;
  TGraphErrors * meanRB3;
  TGraphErrors * meanRB4;
 


  TFile * MuFile;
  TTree * MuTree;
  //double Mu_pt=0;
  //int nRCP=0;
  //int clusterS[40];


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
CLSPT::CLSPT(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  m_trackTag = iConfig.getUntrackedParameter<std::string>("tracks");
  rpcRecHitsLabel = iConfig.getParameter<edm::InputTag>("rpcRecHits");
  rootFileName = iConfig.getUntrackedParameter<std::string>("rootFileName");
  //  Mu_Tree(0); Mu_pt(0);
  // Mu_pt(0);
}


CLSPT::~CLSPT()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CLSPT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  iSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);

  edm::Handle<reco::TrackCollection> alltracks;
  iEvent.getByLabel(m_trackTag,alltracks);

  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsLabel,rpcHits);

   int counter = 0;
   float eta=0;
   float phi=0;
   float p=0;
   float pt=0;

   

  // std::cout<<"There are "<<alltracks->size()<<" muon tracks in this event"<<std::endl;
   muonMultiplicity->Fill(alltracks->size());
  // std::cout<<"Looping on all the reconstructed muons"<<std::endl;

   reco::TrackCollection::const_iterator muon;

   for(muon=alltracks->begin(); muon!=alltracks->end();muon++) {
     counter++;
     
     eta=muon->eta();
     phi=muon->phi();
     p=muon->p();
     pt=muon->pt();

    // Mu_pt=pt;	    
 
     trackobservedeta->Fill(eta);
     trackobservedphi->Fill(phi);
     trackobservedp->Fill(p);
     trackobservedpt->Fill(pt);
     dxy->Fill(muon->dxy());
     chi2->Fill(muon->chi2()/muon->ndof());
     
     //std::cout<<"\t phi  ="<<phi<<" eta  ="<<eta<<" p = "<<p<<" pt = "<<pt<<std::endl;
     //std::cout<<"\t Muon muon->chi2() = "<<muon->chi2()<<std::endl;
     //std::cout<<"\t Muon muon->chi2()/ndof = "<<muon->chi2()/muon->ndof() <<std::endl;
     //std::cout<<"\t Cheking chi2/ndof"<<std::endl;

     int counterhits=0;
     int counterhitsRPC=0;
     int nRPC=0;     

     for(trackingRecHit_iterator recHit = muon->recHitsBegin(); recHit != muon->recHitsEnd(); ++recHit)
     {
       counterhits++;
       if ( (*recHit)->geographicalId().det() != DetId::Muon  ) continue; //Is a hit in the Muon System?
       if ( (*recHit)->geographicalId().subdetId() != MuonSubdetId::RPC ) continue; //Is an RPC Hit?
       if (!(*recHit)->isValid()) continue; //Is Valid
       counterhitsRPC++;

       RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();

       typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
       rangeRecHits recHitCollection =  rpcHits->get(rollId);

       RPCRecHitCollection::const_iterator recHitC;
       int size = 0;
       int clusterS=0;
       // std::cout<<"\t \t Looping on the rechits of the same roll"<<std::endl;
       for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) 
        {
	 clusterS=(*recHitC).clusterSize(); 
	 size++;
        }

       if(size!=1)
         {
	  continue;
	  std::cout<<"\t \t \t more than one rechit in this roll discarted for filling histograms"<<std::endl;
         }
      
       //std::cout<<" phi "<<phi<<" eta "<<eta<<" p "<<p<<" pt "<<pt<<" chi2 "<<muon->chi2()<<" chi2ndof "<<muon->chi2()/muon->ndof() <<" clusterS "<<clusterS<<" located "<<rollId<<std::endl;

       ///////////////begin loop selection
     
       int layer= 0;
	  	    
	  if(rollId.station()==1&&rollId.layer()==1) layer = 1;
	  else if(rollId.station()==1&&rollId.layer()==2) layer = 2;
	  else if(rollId.station()==2&&rollId.layer()==1) layer = 3;
	  else if(rollId.station()==2&&rollId.layer()==2)  layer = 4;
	  else if(rollId.station()==3) layer = 5;
	  else if(rollId.station()==4) layer = 6;

	    
          if(layer==1) RB1in->Fill(pt,clusterS);
	  if(layer==2) RB1out->Fill(pt,clusterS);
          if(layer==3) RB2in->Fill(pt,clusterS);
	  if(layer==4) RB2out->Fill(pt,clusterS); 
          if(layer==5) RB3->Fill(pt,clusterS);
          if(layer==6) RB4->Fill(pt,clusterS);

          clspt->Fill(pt,clusterS);
          ptAllcls->Fill(pt);
       //std::cout<<"\t Cheking chi2/ndof"<<std::endl;
 
        //std::cout<<"\t \t \t The cluster Size for this hit is : "<<clusterS<<" and it is located in "<<rollId<<std::endl;
        //std::cout<<"\t \t size "<<size<<std::endl;
        nRPC++;
      }

    // std::cout<<"\t \t nRPC "<<nRPC<<std::endl;
    // std::cout<<"\t \t number of hits in this muon "<<counterhits<<std::endl;
    // std::cout<<"\t \t number of hits in this muon at RPC "<<counterhitsRPC<<std::endl;

     recHitMultiplicity->Fill(counterhits);
     rpcrecHitMultiplicity->Fill(counterhitsRPC);
     
   
   }
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
CLSPT::beginJob()
{

  //std::cout<<"Begin Job"<<std::endl;
  
    theFile = new TFile(rootFileName.c_str(),"RECREATE");

    muonMultiplicity = new TH1F("Muon_Multiplicity","Muon_Multiplicity",11,-0.5,10.5); 
    recHitMultiplicity = new TH1F("recHitMultiplicity","recHitMultiplicity",101,-0.5,100.5);
    rpcrecHitMultiplicity = new TH1F("RPCrecHitMultiplicity","RPCrecHitMultiplicity",21,-0.5,20.5);

    chi2 = new TH1F("chi2_normalized","chi2_normalized",101,-0.5,100.5);
    dxy = new TH1F("dxy","dxy",200,-10,10);

    trackobservedeta = new TH1F("EtaObserved","Eta",100,-2.5,2.5); 
    trackobservedphi = new TH1F("PhiObserved","Phi",100,-3.1415926,3.1415926); 
    trackobservedp = new TH1F("PObserved","P ",100,0,1500);    
    trackobservedpt = new TH1F("PtObserved","Pt",100,0,100);    
    
    clspt =  new TH2F("Cluster size Vs pt","clspt",100,0.,100.,10,0.,10.0);  
    
    RB1in = new TH2F("RB1in","RB1in",100,0.,100.,10,0.,10.0);
    RB1out = new TH2F("RB1out","RB1out",100,0.,100.,10,0.,10.0);
    RB2in = new TH2F("RB2in","RB2in",100,0.,100.,10,0.,10.0);
    RB2out = new TH2F("RB2out","RB2out",100,0.,100.,10,0.,10.0);
    RB3 = new TH2F("RB3","RB3",100,0.,100.,10,0.,10.0);
    RB4 = new TH2F("RB3","RB3",100,0.,100.,10,0.,10.0);

    ptAllcls =  new TH1F("ptAllcls","ptAllcls",100,0.,100.);   
    
   //std::cout<<"Finishing Begin Job"<<std::endl;

    //MuFile = new TFile("Muon_file","RECREATE");
    //MuTree = new TTree("Tree","Muons");
    //MuTree->SetDirectory(MuFile);
    //MuTree->Branch("Mu_pt",&Mu_pt,"Mu_pt/D");

}

// ---------- method called once each job just after ending the event loop  ------------
void 
CLSPT::endJob() 
{
  theFile->cd();
  
  muonMultiplicity->Write();

  recHitMultiplicity->Write();
  rpcrecHitMultiplicity->Write();
  chi2->Write();
  dxy->Write();
  
  trackobservedeta->Write();
  trackobservedphi->Write();
  trackobservedp->Write();
  trackobservedpt->Write();

  clspt->Write();  
  ptAllcls->Write();

  RB1in->Write();
  RB1out->Write();
  RB2in->Write();
  RB2out->Write();
  RB3->Write();
  RB4->Write();

  
  Double_t step=1; 
  int n=100;
  Double_t x[100],y[100],ex[100],ey[100];   
  Double_t xRB1in[100],yRB1in[100],exRB1in[100],eyRB1in[100];
  Double_t xRB1out[100],yRB1out[100],exRB1out[100],eyRB1out[100];
  Double_t xRB2in[100],yRB2in[100],exRB2in[100],eyRB2in[100];
  Double_t xRB2out[100],yRB2out[100],exRB2out[100],eyRB2out[100];
  Double_t xRB3[100],yRB3[100],exRB3[100],eyRB3[100];
  Double_t xRB4[100],yRB4[100],exRB4[100],eyRB4[100];



  for(int i=0;i<n;i++)
       {
       float mean = clspt->ProjectionY("_py",i,i+1)->GetMean();
       float entries = clspt->ProjectionY("_py",i,i+1)->GetEntries();
       float error = clspt->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entries); 
       x[i]=(i+0.5)*step;
       y[i]=mean;
       ey[i]=error;
       ex[i]=step*0.5;

       //
       float meanRB1in = RB1in->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB1in = RB1in->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB1in = RB1in->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB1in);
       xRB1in[i]=(i+0.5)*step;
       yRB1in[i]=meanRB1in;
       eyRB1in[i]=errorRB1in;
       exRB1in[i]=step*0.5;
       //
       float meanRB1out = RB1out->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB1out = RB1out->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB1out = RB1out->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB1out);
       xRB1out[i]=(i+0.5)*step;
       yRB1out[i]=meanRB1out;
       eyRB1out[i]=errorRB1out;
       exRB1out[i]=step*0.5;
       //
       float meanRB2in = RB2in->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB2in = RB2in->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB2in = RB2in->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB2in);
       xRB2in[i]=(i+0.5)*step;
       yRB2in[i]=meanRB2in;
       eyRB2in[i]=errorRB2in;
       exRB2in[i]=step*0.5;  
       //
       float meanRB2out = RB2out->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB2out = RB2out->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB2out = RB2out->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB2out);
       xRB2out[i]=(i+0.5)*step;
       yRB2out[i]=meanRB2out;
       eyRB2out[i]=errorRB2out;
       exRB2out[i]=step*0.5;
       //
       float meanRB3 = RB3->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB3 = RB3->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB3 = RB3->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB3);
       xRB3[i]=(i+0.5)*step;
       yRB3[i]=meanRB3;
       eyRB3[i]=errorRB3;
       exRB3[i]=step*0.5;
       //	/
       float meanRB4 = RB4->ProjectionY("_py",i,i+1)->GetMean();
       float entriesRB4 = RB4->ProjectionY("_py",i,i+1)->GetEntries();
       float errorRB4 = RB4->ProjectionY("_py",i,i+1)->GetRMS()/sqrt(entriesRB4);
       xRB4[i]=(i+0.5)*step;
       yRB4[i]=meanRB4;
       eyRB4[i]=errorRB4;
       exRB4[i]=step*0.5;
	
       
       //std::cout<<"flag "<<i<<" x= "<<x[i]<<" y= "<<y[i]<<std::endl;   		
       }


   meanclspt = new TGraphErrors(n,x,y,ex,ey);
   meanclspt->SetTitle("meanclspt");     
   meanclspt->Write();


   meanRB1in = new TGraphErrors(n,xRB1in,yRB1in,exRB1in,eyRB1in);
   meanRB1in->SetTitle("meanRB1in");  
   meanRB1in->Write();
   meanRB1out= new TGraphErrors(n,xRB1out,yRB1out,exRB1out,eyRB1out);
   meanRB1out->SetTitle("meanRB1out");      
   meanRB1out->Write();
   meanRB2in = new TGraphErrors(n,xRB2in,yRB2in,exRB2in,eyRB2in);
   meanRB2in->SetTitle("meanRB2in");      
   meanRB2in->Write();
   meanRB2out = new TGraphErrors(n,xRB2out,yRB2out,exRB2out,eyRB2out);
   meanRB2out->SetTitle("meanRB2out");      
   meanRB2out->Write();
   meanRB3 = new TGraphErrors(n,xRB3,yRB3,exRB3,eyRB3);
   meanRB3->SetTitle("meanRB3");      
   meanRB3->Write();
   meanRB4 = new TGraphErrors(n,xRB4,yRB4,exRB4,eyRB4);
   meanRB4->SetTitle("meanRB4");     
   meanRB4->Write();



   theFile->Close();

 

}

// ------------ method called when starting to processes a run  ------------
void 
CLSPT::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CLSPT::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CLSPT::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CLSPT::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CLSPT::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CLSPT);
