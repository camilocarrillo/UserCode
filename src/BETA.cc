// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "DataFormats/DetId/interface/DetId.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "beta/BETA/interface/BETA.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "FastSimulation/Tracking/test/FastTrackAnalyzer.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "RecoMuon/TrackingTools/interface/MuonPatternRecoDumper.h"

#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include <cmath>

//Root
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"

//Track
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h" 
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

class Candidate;


BETA::BETA(const edm::ParameterSet& iConfig){
  file  = iConfig.getUntrackedParameter<std::string>("FileName");
  bxFile = iConfig.getUntrackedParameter<std::string>("bxName");
  NumRecHitsFile = iConfig.getUntrackedParameter<std::string>("numName");
  beta = iConfig.getUntrackedParameter<std::string>("beta");
  betaT = iConfig.getUntrackedParameter<std::string>("betaT");
  partLabel = iConfig.getUntrackedParameter<std::string>("partLabel");
  nrFile = iConfig.getUntrackedParameter<std::string>("nrFile");
  //trackLabel = iConfig.getUntrackedParameter<std::string>("trackLabel");
  eta = iConfig.getUntrackedParameter<std::string>("eta");
  soloeta = iConfig.getUntrackedParameter<std::string>("soloeta");
  residualRecSim = iConfig.getUntrackedParameter<std::string>("residualRecSim");
  layerName = iConfig.getUntrackedParameter<std::string>("layerName");
  layerNameEndCap = iConfig.getUntrackedParameter<std::string>("layerNameEndCap");
  fileNameBXLayer = iConfig.getUntrackedParameter<std::string>("fileNameBXLayer");
  //bitsDistroName = iConfig.getUntrackedParameter<std::string>("bitsDistroName");
}

BETA::~BETA(){
}


void BETA::beginJob(const edm::EventSetup&){
  theFile = new TFile(file.c_str(), "RECREATE");
  theFile->cd();
  bx = new TH1F("Times_BX_RecHit","Distribution of BX for HSCP",11,-5,5);
  betaHisto = new TH1F("Beta","1/Beta Distribution",200,0,2);
  betaTHisto= new TH1F("BetaT","BetaT Distribution",100,0,1);
  NumRecHits = new TH1F("BX","Number of RecHits With the same BX",15,0,15);
  nr = new TH1F("nr","Number of SimHits",10,0,10);
  etaHisto = new TH1F("Eta Vs RecHits","Number of RPCSimHits in a given Eta",100,-3,3);
  soloEtaHisto = new TH1F("Eta Distribution for HSPC-","Number of Particles for a given Eta",100,-10,10);
  residualRecSimHisto = new TH1F("RecSim","Residual dx Rec Sim for HSCP",100,-20,20);
  //bitsDistroHisto = new TH1F("BitsDistro","",64,0,63);

  layerB1Histo = new TH1F("BarrelLa1","BX Distribution for Layer 1 Barrel",11,-5,5);
  layerB2Histo = new TH1F("BarrelLa2","BX Distribution for Layer 2 Barrel",11,-5,5);
  layerB3Histo = new TH1F("BarrelLa3","BX Distribution for Layer 3 Barrel",11,-5,5);
  layerB4Histo = new TH1F("BarrelLa4","BX Distribution for Layer 4 Barrel",11,-5,5);
  layerB5Histo = new TH1F("BarrelLa5","BX Distribution for Layer 5 Barrel",11,-5,5);
  layerB6Histo = new TH1F("BarrelLa6","BX Distribution for Layer 6 Barrel",11,-5,5);

  layerE1Histo = new TH1F("EndCapSt1","BX Distribution for Layer 1 End Cap",11,-5,5);
  layerE2Histo = new TH1F("EndCapSt2","BX Distribution for Layer 2 End Cap",11,-5,5);
  layerE3Histo = new TH1F("EndCapSt3","BX Distribution for Layer 3 End Cap",11,-5,5);
  
  simHitHSCP=0;
  norHitHSCP=0;
  recHitHSCP=0;
  
  bxLayerFile.open(fileNameBXLayer.c_str());

  fileMatrix.open("fileMatrix.txt");

  matrixHisto = new TH2F("LayersandBX","Histogram 2D Layers and BX",6,0.5,6.5,4,-0.5,3.5);

}

void BETA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel("rpcRecHits",rpcHits);

  //edm::Handle<RPCDigiCollection> rpcDigis;
  //iEvent.getByLabel("muonRPCDigis",rpcDigis);
  
  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  edm::Handle<reco::CandidateCollection> genParticles;
  iEvent.getByLabel(partLabel,genParticles );

  //edm::ESHandle<MagneticField> theMGField;
  //iSetup.get<IdealMagneticFieldRecord>().get(theMGField);
   
  //edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  //iSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);

  //edm::Handle<reco::TrackCollection> theTrackCollection;
  //iEvent.getByLabel(trackLabel, theTrackCollection);

  //edm::Handle<std::vector<SimTrack> > theSimTracks;
  //iEvent.getByLabel("famosSimHits",theSimTracks); 

  //edm::Handle<edm::SimTrackContainer> simTracks;
  //iEvent.getByLabel("g4SimHits",simTracks);
  
  std::vector<edm::Handle<edm::PSimHitContainer> > theSimHitContainers;
  iEvent.getManyByType(theSimHitContainers);

  std::cout << " Number of Particles in this event: " << genParticles->size() << std::endl;
  //std::cout << " Number of Tracks in this event: " << theTrackCollection->size() << std::endl;

   
  //Matrix Stuff

  int const layitLimit=7;
  int const bxsitLimit=4;
  int matrixbit[bxsitLimit][layitLimit];
  for(int lay=0;lay<layitLimit;lay++){//looping layers
    for(int bxs=0;bxs<bxsitLimit;bxs++){//looping bx
      matrixbit[bxs][lay]=0.;
    }
  }

  //SimTrack Stuff

  std::vector<PSimHit> theSimHits;

      
  for (int i = 0; i < int(theSimHitContainers.size()); i++){
    theSimHits.insert(theSimHits.end(),theSimHitContainers.at(i)->begin(),theSimHitContainers.at(i)->end());
  }

  std::cout << "\t Loop on the SimHits x "<<theSimHitContainers.size()<<std::endl;

  //bxLayerFile<<"New Event "<<iEvent.id().event()<<std::endl;
  bxLayerFile<<"\n"<<iEvent.id().event()<<"  ";

 
  int countHitsInRPC=0;       
  for (std::vector<PSimHit>::const_iterator iHit = theSimHits.begin();
       iHit != theSimHits.end(); iHit++){
    if((*iHit).particleType()== 2000015){
      std::cout<<"\t\t SimHit.ParticleType "<<(*iHit).particleType()<<std::endl;
       
      DetId theDetUnitId((*iHit).detUnitId());

  
      std::cout<<"\t\t\t HSCP SimHit, now is an RPC Hit?"<<std::endl;
       
      DetId simdetid= DetId((*iHit).detUnitId());
      if(simdetid.det()==DetId::Muon &&  simdetid.subdetId()== MuonSubdetId::RPC){
	 
	RPCDetId RPCId(theDetUnitId);
	      
	std::cout<<"\t\t\t\t subdetId "<<simdetid.subdetId()<<std::endl;
	std::cout<<"\t\t\t\t We have a HSPC touching RPC "<<std::endl;
	countHitsInRPC++;
	simHitHSCP++;
	std::cout<<"\t\t\t\t countingHits now is "<<countHitsInRPC<<std::endl;

	//Loop on the RecHits
	 
	std::cout<<"\t\t\t\t Was This SimHit Reconstructed? Looping on RecHits"<<countHitsInRPC<<std::endl;

	//getting the rechits in the same Roll
	typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
	rangeRecHits recHitCollection =  rpcHits->get(RPCId);

	if(recHitCollection.first==recHitCollection.second){
	  std::cout<<"\t\t\t\t No Rec Hit in the same roll"<<std::endl;
	  norHitHSCP++;
	}else{//loop on the recHits with the same Id
	   
	  RPCRecHitCollection::const_iterator recIt;
	  int countRecHit=0;
	  float dxmin=9999.;
	   
	  RPCRecHit rpcRecHitMin; 
	  bool foundmin=false;
	   
	  for (recIt = recHitCollection.first; 
	       recIt != recHitCollection.second ; recIt++){
	    float dx=(*recIt).localPosition().x()-(*iHit).localPosition().x();
	    float dy=(*recIt).localPosition().y()-(*iHit).localPosition().y();
	    float dist=sqrt(dx*dx+dy*dy);
	     
	    std::cout<<"\t\t\t\t dist="<<dist<<" dx="<<dx<<" dy="<<dy<<std::endl;
	     
	    if(fabs(dx)<fabs(dxmin)){
	      dxmin=dx;
	      //In the minimum is for sure the RecHit Associated to our RPCSimHit for a HSCP
	      rpcRecHitMin=(*recIt); 
	      foundmin=true;
	    }
	     
	    countRecHit++;
	  }
	   
	  if(dxmin==9999){
	    std::cout<<"\t\t\t\t No single RecHit Associeated"<<std::endl;
	    norHitHSCP++;
	  }
	  else{


	    std::cout<<"\t\t\t The minimum was dx="<<dxmin
		     <<" with  BX="<<rpcRecHitMin.BunchX()<<std::endl;
	    recHitHSCP++;
	    residualRecSimHisto->Fill(dxmin);
	    std::cout<<"\t\t\t Filling the bx histogram with="<<rpcRecHitMin.BunchX()<<std::endl;
	    bx->Fill(rpcRecHitMin.BunchX());
	    //print the bx of the RecHit in a file
	    int BX = rpcRecHitMin.BunchX();
	    if(RPCId.region()==0){
	      int mySt = RPCId.station();
	      int myLa = RPCId.layer();
	      int layer = 0;
	      if(mySt==1&&myLa==1){layerB1Histo->Fill(BX);layer=1;}
	      if(mySt==1&&myLa==2){layerB2Histo->Fill(BX);layer=2;}
	      if(mySt==2&&myLa==1){layerB3Histo->Fill(BX);layer=3;}
	      if(mySt==2&&myLa==2){layerB4Histo->Fill(BX);layer=4;}
	      if(mySt==3){layerB5Histo->Fill(BX);layer=5;}
	      if(mySt==4){layerB6Histo->Fill(BX);layer=6;}
	       
	      //bxLayerFile<<"\t BX "<<rpcRecHitMin.BunchX()<<" Layer"<<layer;
	      bxLayerFile<<"  B"<<layer<<"-"<<BX<<"bx "<<(*iHit).timeOfFlight()<<"ns" ; //works fine simple print
	       
	      //bxLayerFile<<rpcRecHitMin.BunchX(); 
	      //Bitsdistrohisto->Fill();
	       
	      matrixbit[BX][layer]++;
	       
	    }else{
	      int mySt = RPCId.station();
	      int layer=0;
	      if(mySt==1){layerE1Histo->Fill(rpcRecHitMin.BunchX());layer =1;}
	      if(mySt==2){layerE2Histo->Fill(rpcRecHitMin.BunchX());layer =2;}
	      if(mySt==3){layerE3Histo->Fill(rpcRecHitMin.BunchX());layer =3;}
	      bxLayerFile<<"  E"<<layer<<"-"<<BX<<"bx "<<(*iHit).timeOfFlight()<<"ns" ; //works fine simple print
	    }
	  }
	  std::cout<<"\t\t\t Number of recHits in the same roll="<<countRecHit<<" roll "<<RPCId<<std::endl;
	}
      }
    }
  }

  fileMatrix<<"Printing matrix Event "<<iEvent.id().event()<<std::endl;
  for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
    for(int lay=1;lay<layitLimit;lay++){//looping layers
      fileMatrix<<matrixbit[bxs][lay];
    }
    fileMatrix<<"\n";
  }
  fileMatrix<<"\n";
  
  for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
    for(int lay=1;lay<layitLimit;lay++){//looping layers
      if(matrixbit[bxs][lay]!=0){
	fileMatrix<<"Increasing "<<static_cast<double>(bxs)
		  <<","<<static_cast<double>(lay)<<" in "<<matrixbit[bxs][lay]<<std::endl;
	matrixHisto->Fill(static_cast<double>(bxs),static_cast<double>(lay),matrixbit[bxs][lay]);
      }
    }
  }
     
  
  
  
  //if(countHitsInRPC!=0)
  nr->Fill(countHitsInRPC);
   

  std::cout<<"loop on the particles"<<std::endl;

  reco::CandidateCollection::const_iterator partIt;
  for(partIt=genParticles->begin();partIt!=genParticles->end();++partIt) {
    if(partIt->pdgId()==2000015){
      //ABOUT ETA
      std::cout<<"\t\t Filling the histogram Eta="<<partIt->eta()<<" HitsRPC "<<countHitsInRPC<<std::endl;
      etaHisto->Fill(partIt->eta(),countHitsInRPC);
      soloEtaHisto->Fill(partIt->eta());
       
      //ABOUT BETA
      float p=partIt->p();
      float e=partIt->energy();
      float beta=p/e;
      betaHisto->Fill(1/beta);
      float pt = partIt->pt();
      //float et = partIt->et();
      float betaT=pt/e;
      betaTHisto->Fill(betaT);
      bxLayerFile<<"\t"<<" eta="<<partIt->eta()<<" beta="<<beta<<"c";
    }
  }
   
  /*
    edm::SimTrackContainer::const_iterator simTrack;
   
    std::cout<<"LOOP ON SIMTRACKS"<<std::endl;
    for (simTrack = simTracks->begin(); simTrack != simTracks->end(); ++simTrack){
    std::cout<<(*simTrack).type()<<std::endl;
    if ((*simTrack).type()==2000015) {
    std::cout << "\t Finaly we got the track of a HSPC"<< std::endl;
    std::cout << "\t Sim track mom = " << simTrack->momentum() 
    << " charge = " <<  simTrack->charge() 
    << "\t Id= "<<(*simTrack).type()<<std::endl;
       
    //filling the SimHits Vector
   
    // loop over the SimHits and fill the histograms
    }
    }
  */

  //iSetup.getData( pdt_ );
   

  //RecHitPart
   
  int vectorbx[11];
  for(int i=0;i<11;i++)vectorbx[i]=0;
  int i =0;
  //bool hscp=false;

  RPCRecHitCollection::const_iterator recIt;
  for(recIt=rpcHits->begin();recIt!=rpcHits->end();++recIt){
    int bxs = (*recIt).BunchX();
    //std::cout<<"This Rec Hit has BX="<<bxs<<std::endl;
    for(int j=0;j<11;j++){
      if(bxs==(j-5))vectorbx[j]++;
    }
    i++;
  }
     
  //std::cout<<"Number of rec Hits "<<i<<"="<<rpcHits->size()<<std::endl;
   
  for(int j=0;j<11;j++){
    if(vectorbx[j]!=0) NumRecHits->Fill(vectorbx[j]);
  }
   
  bool empty=true;
   
  for(int j=0;j<11;j++){
    if(vectorbx[j]!=0) empty=false;
  }
   
  if(!empty){
    std::cout<<"We got in \n"<<
      "  BX-5->"<<vectorbx[0]<<
      "  BX-4->"<<vectorbx[1]<<
      "  BX-3->"<<vectorbx[2]<<
      "  BX-2->"<<vectorbx[3]<<
      "  BX-1->"<<vectorbx[4]<<
      "  BX+0->"<<vectorbx[5]<<
      "  BX+1->"<<vectorbx[6]<<
      "  BX+2->"<<vectorbx[7]<<
      "  BX+3->"<<vectorbx[8]<<
      "  BX+4->"<<vectorbx[9]<<
      "  BX+5->"<<vectorbx[10]<<
      std::endl;
  }

}


 void  BETA::endJob() {

  if(simHitHSCP!=recHitHSCP+norHitHSCP)
    std::cout<<simHitHSCP<<"!="<<recHitHSCP+norHitHSCP<<std::endl;
  
  assert(simHitHSCP==recHitHSCP+norHitHSCP);


  std::cout<<"Creating Canvas"<<std::endl;
  TCanvas *Ca1 = new TCanvas("Ca1","Histogram for SUSY",800,600);
  
  std::cout<<"Creating bx Image"<<std::endl;
  bx->Draw();
  Ca1->SaveAs(bxFile.c_str());
  Ca1->Clear();
   
  NumRecHits->Draw();
  //NumRecHits->GetXaxis()->CenterLabels();
  Ca1->SaveAs(NumRecHitsFile.c_str());

  Ca1->Clear();

  nr->Draw();
  nr->GetXaxis()->SetTitle("Distribution of Sim Hits");
  //nr->GetXaxis()->CenterLabels();
  Ca1->SaveAs(nrFile.c_str());

  Ca1->Clear();
   
  etaHisto->Draw();
  //etaHisto->GetXaxis()->CenterLabels();
  etaHisto->GetXaxis()->SetTitle("#eta");
  Ca1->SaveAs(eta.c_str());

  Ca1->Clear();

  std::cout<<"Creating Solo EtaImage"<<std::endl;
  soloEtaHisto->Draw();
  //soloEtaHisto->GetXaxis()->CenterLabels();
  soloEtaHisto->GetXaxis()->SetTitle("#eta");
  Ca1->SaveAs(soloeta.c_str());
   
  Ca1->Clear();
   
  std::cout<<"Creating Residual Rec Sim"<<std::endl;
  residualRecSimHisto->Draw();
  residualRecSimHisto->GetXaxis()->SetTitle("Residual Rec Sim");
  Ca1->SaveAs(residualRecSim.c_str());

  Ca1->Clear();

  std::cout<<"Creating betaHisto"<<std::endl;
  betaHisto->Draw();
  betaHisto->GetXaxis()->SetTitle("#betainv");
  Ca1->SaveAs(beta.c_str());
   
  Ca1->Clear();
 
  std::cout<<"Creating betaTHisto"<<std::endl;
  betaTHisto->Draw();
  betaTHisto->GetXaxis()->SetTitle("#beta_t");
  Ca1->SaveAs(betaT.c_str());

  Ca1->Clear();
 
  //std::cout<<"Creating bitsHisto"<<std::endl;
  //betaTHisto->Draw();
  //betaTHisto->bitsDistroHisto->SetTitle("binary number");
  //Ca1->SaveAs(bitsDistroName.c_str());

  std::cout<<"cd the file"<<std::endl;

  theFile->cd();

  std::cout<<"Writing the histos"<<std::endl;
  bx->Write();
  betaHisto->Write();
  betaTHisto->Write();
  NumRecHits->Write();
  nr->Write();
  etaHisto->Write();
  soloEtaHisto->Write();
  residualRecSimHisto->Write();

  layerB1Histo->Write();
  layerB2Histo->Write();
  layerB3Histo->Write();
  layerB4Histo->Write();
  layerB5Histo->Write();
  layerB6Histo->Write();

  layerE1Histo->Write();
  layerE2Histo->Write();
  layerE3Histo->Write();

  matrixHisto->Write();

  theFile->Close();

  bxLayerFile.close();
  fileMatrix.close();

  float recHitHSCPf = float(recHitHSCP);
  float simHitHSCPf = float(simHitHSCP);

  if(simHitHSCP!=0){
    std::cout<<"SimHits Founded="<<simHitHSCP
	     <<" SimHits Reconstructed = "<<recHitHSCP
	     <<"\t Ratio = "<<recHitHSCPf*100.0/simHitHSCPf<<"%"<<std::endl;
  }else{
    std::cout<<"No single SimHit in this file"<<std::endl;
  }
   
  std::cout<<"Finito!"<<std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(BETA);
