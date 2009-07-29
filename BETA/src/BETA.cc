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

  betaHisto = new TH1F("BetaMC","Beta Distribution",100,0,1);
  betaMyHisto = new TH1F("BetaMy","Beta Identified Distribution",100,0,1);
  effInBetaHisto = new TH1F("BetaEff","Beta Efficiency",100,0,1);

  betaTHisto= new TH1F("BetaT","BetaT Distribution",100,0,1);
  NumRecHits = new TH1F("BX","Number of RecHits With the same BX",15,0,15);
  nr = new TH1F("nr","Number of SimHits",10,0,10);
  etaHisto = new TH1F("EtaRecHits","Number of RPCSimHits in a given Eta",100,-3,3);

  soloEtaHisto = new TH1F("EtaMC","Number of Particles for a given Eta",100,-10,10);
  soloEtaMyHisto = new TH1F("EtaMy","Number of Particles Identified for a given Eta",100,-10,10);
  effInEtaHisto = new TH1F("EtaEff","Eta Efficiency",100,-10,10);

  diffsimhitrechitphi = new TH1F("DeltaPhi","Delta Phi",100,-0.05,0.05);
  diffsimhitrechiteta = new TH1F("DeltaEta","Delta Eta",100,-0.5,0.5);

  residualRecSimHisto = new TH1F("RecSim","Residual dx Rec Sim for HSCP",100,-20,20);

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
  etaout=0;
  
  bxLayerFile.open(fileNameBXLayer.c_str());

  fileMatrix.open("fileMatrixJUSTHSCP.txt");

  matrixHisto = new TH1F("LayersandBX","Histogram 2D Layers and BX",30,-0.5,29.5);
  
  totalHSCP=0;
  
  eventsWithRPCSimHits=0;
}

void BETA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel("rpcRecHits",rpcHits);

  edm::ESHandle<RPCGeometry> rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  edm::Handle<reco::CandidateCollection> genParticles;
  iEvent.getByLabel(partLabel,genParticles );

  std::vector<edm::Handle<edm::PSimHitContainer> > theSimHitContainers;
  iEvent.getManyByType(theSimHitContainers);

  std::cout << " Number of Particles in this event: " << genParticles->size() << std::endl;

  hscp = false;
   
  //Matrix Stuff Cloning RECHIT.cc

  int const layitLimit=7;
  int const bxsitLimit=4;
  int matrixbit[bxsitLimit][layitLimit];
  for(int lay=0;lay<layitLimit;lay++){//looping layers
    for(int bxs=0;bxs<bxsitLimit;bxs++){//looping bx
      matrixbit[bxs][lay]=0;
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

  bool isthereRPCSimHits=false;

  int countHitsInRPC=0;       
  for (std::vector<PSimHit>::const_iterator iHit = theSimHits.begin();
       iHit != theSimHits.end(); iHit++){

    if((*iHit).particleType()== 2000015){//Only HSCPs
      
      std::cout<<"\t\t SimHit.ParticleType "<<(*iHit).particleType()<<std::endl;
      
      DetId theDetUnitId((*iHit).detUnitId());
      
      std::cout<<"\t\t\t HSCP SimHit, now is an RPC Hit?"<<std::endl;
      
      DetId simdetid= DetId((*iHit).detUnitId());
      if(simdetid.det()==DetId::Muon &&  simdetid.subdetId()== MuonSubdetId::RPC){
	
	isthereRPCSimHits=true;
	RPCDetId RPCId(theDetUnitId);
	
	std::cout<<"\t\t\t\t subdetId "<<simdetid.subdetId()<<std::endl;
	std::cout<<"\t\t\t\t We have a HSPC touching RPC "<<std::endl;
	countHitsInRPC++;
	std::cout<<"\t\t\t\t countingHits now is "<<countHitsInRPC<<std::endl;
	
	simHitHSCP++;
	
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

	  for (recIt = recHitCollection.first;recIt != recHitCollection.second ; recIt++){
	    float dx=(*recIt).localPosition().x()-(*iHit).localPosition().x();
	    float dy=(*recIt).localPosition().y()-(*iHit).localPosition().y();
	    float dist=sqrt(dx*dx+dy*dy);
	     
	    std::cout<<"\t\t\t\t dist="<<dist<<" dx="<<dx<<" dy="<<dy<<std::endl;
	     
	    if(fabs(dx)<fabs(dxmin)){
	      dxmin=dx;
	      //In the minimum is for sure the RecHit Associated to our RPCSimHit for a HSCP if it was reconstructed!!!
	      rpcRecHitMin=(*recIt); 
	      foundmin=true;
	    }
	     
	    countRecHit++;
	  }
	  
	  if(dxmin==9999.){
	    std::cout<<"\t\t\t\t No single RecHit Associeated"<<std::endl;
	    norHitHSCP++;
	  }
	  else if(dxmin<=6.){
	    std::cout<<"\t\t\t Yes... The minimum was dx="<<dxmin
		     <<" with  BX="<<rpcRecHitMin.BunchX()<<std::endl;
	    
	    const RPCRoll* rollasociated = rpcGeo->roll(RPCId);
	    const BoundPlane & RPCSurface = rollasociated->surface();
	    
	    GlobalPoint RecHitGlobal = RPCSurface.toGlobal(rpcRecHitMin.localPosition());
	    GlobalPoint SimHitGlobal = RPCSurface.toGlobal((*iHit).localPosition());
	    
	    double dphi=RecHitGlobal.phi()-SimHitGlobal.phi(); 
	    double deta=RecHitGlobal.eta()-SimHitGlobal.eta();
	    
	    diffsimhitrechitphi->Fill(dphi);
	    diffsimhitrechiteta->Fill(deta);
	    
	    std::cout<<" d phi="<<dphi
		     <<" d eta="<<deta;
	    
	    recHitHSCP++;
	    residualRecSimHisto->Fill(dxmin);
	    std::cout<<"\t\t\t Filling the bx histogram with="<<rpcRecHitMin.BunchX()<<std::endl;
	    bx->Fill(rpcRecHitMin.BunchX());

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
	       
	      bxLayerFile<<"  "<<layer<<"-"<<BX<<"bx "<<(*iHit).timeOfFlight()<<"ns" ; 
	      //works fine simple print

	      fileMatrix<<"\n "<<layer<<"-"<<BX<<" "<<(*iHit).timeOfFlight()<<"ns"
			<<" posRec="<<rpcRecHitMin.localPosition()
			<<" posSim="<<(*iHit).localPosition();
	      
	      matrixbit[BX][layer]++;
	       
	    }else{
	      int mySt = RPCId.station();
	      int layer=0;
	      if(mySt==1){layerE1Histo->Fill(rpcRecHitMin.BunchX());layer =1;}
	      if(mySt==2){layerE2Histo->Fill(rpcRecHitMin.BunchX());layer =2;}
	      if(mySt==3){layerE3Histo->Fill(rpcRecHitMin.BunchX());layer =3;}
	      bxLayerFile<<"  E"<<layer<<"-"<<BX<<"bx "<<(*iHit).timeOfFlight()<<"ns" ; //works fine simple print

	      
	      fileMatrix<<"\n E "<<layer<<"-"<<BX<<" "<<(*iHit).timeOfFlight()<<"ns"
			<<" posRec="<<rpcRecHitMin.localPosition()
			<<" posSim="<<(*iHit).localPosition(); //works fine simple print
	      
	      //matrixbit[BX][layer]++;
	    }
	  }
	  std::cout<<"\t\t\t Number of recHits in the same roll="<<countRecHit<<" roll "<<RPCId<<std::endl;
	}
      }
    }
  }
     
  //if(countHitsInRPC!=0)


  nr->Fill(countHitsInRPC);
  
  ////////////////////////////////////////////// Cloning the RPCHITANA.cc for HSCP+ RecHits BEGIN

  int count=0;// does the fingerprint has something?

  for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
    for(int lay=1;lay<layitLimit;lay++){//looping layers
      count=count+matrixbit[bxs][lay];
    }
  }
  
  if(count!=0){
    fileMatrix<<"\n";
  
    std::cout<<"Printing matrix Event "<<iEvent.id().event()<<std::endl;
    fileMatrix<<"Printing matrix Event "<<iEvent.id().event()<<std::endl;
  
    for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
      for(int lay=1;lay<layitLimit;lay++){//looping layers
	fileMatrix<<matrixbit[bxs][lay];
      }
      fileMatrix<<"\n";
    }

    //When we count endcaps this should work
    //assert(counter==rpcHits->size());
  

    int layersHited = 0;
    int Maxbx[7];
    std::cout<<"Cleaning array Maxbx"<<std::endl;
    for(int i=0;i<7;i++)Maxbx[i]=0;
    std::cout<<"Cleaned"<<std::endl;

    for(int lay=1;lay<7;lay++){//looping layers
      bool anyhit = false;
      int maxbx = 0;
      for(int bxs=bxsitLimit-1;bxs>=0;bxs--){//looping bx
	if(matrixbit[bxs][lay]!=0.){
	  //fileMatrix<<"Increasing "<<bxs<<" "<<lay<<" "<<matrixbit[bxs][lay]<<std::endl;
	  matrixHisto->Fill(bxs+(lay-1)*5,matrixbit[bxs][lay]);
	  if(matrixbit[bxs][lay]!=0){
	    anyhit=true;
	    if(maxbx<bxs)maxbx=bxs;
	  }
	}
      }	
      if(anyhit){
	layersHited++;
	Maxbx[lay]=maxbx;
      }
      std::cout<<"Writing the Max array"<<" lay = "<<lay<<" maxbx = "<<maxbx<<std::endl;
	    
    }

    fileMatrix<<"Number Of layers "<<layersHited<<std::endl;
    std::cout<<"Number Of layers "<<layersHited<<std::endl;
  
    for(int i=1;i<7;i++)fileMatrix<<" L"<<i<<" "<<Maxbx[i];
    fileMatrix<<"\n";

    fileMatrix<<"dys ";
  
    int pendpos=0;
    int dy=0;
    for(int i=1;i<6;i++){
      dy=Maxbx[i+1]-Maxbx[i];
      fileMatrix<<" "<<dy;
      if(Maxbx[i+1]!=0)pendpos=pendpos+dy;
    }

    float average=0;
    for(int i=1;i<7;i++)if(Maxbx[i]!=0)average=average+(float)(Maxbx[i]);
    average=average/(float)(layersHited);
  

    
    if(layersHited>=2&&(pendpos>0||average>=1))hscp=true; //important if
    
    std::cout<<" pendpos= "<<pendpos<<" average= "<<average<<" boolean hscp= "<<hscp<<std::endl;
    fileMatrix<<" pendpos= "<<pendpos<<" average= "<<average<<" boolean hscp= "<<hscp<<std::endl;
    
    if(hscp) totalHSCP++;
    
  }else{
    std::cout<<" Empty fingerprint"<<std::endl;
    fileMatrix<<" Empty fingerprint"<<std::endl;
  }

  /////////////////////////////////////////// Cloning the RPCHITANA.cc for HSCP RecHits END
  // 
  //

  std::cout<<"loop on the particles"<<std::endl;

  reco::CandidateCollection::const_iterator partIt;
  for(partIt=genParticles->begin();partIt!=genParticles->end();++partIt) {
    if(partIt->pdgId()==2000015){
      //ABOUT ETA
      std::cout<<"\t\t Filling the histogram Eta="<<partIt->eta()<<" HitsRPC "<<countHitsInRPC<<std::endl;
      etaHisto->Fill(partIt->eta(),countHitsInRPC);
      soloEtaHisto->Fill(partIt->eta());
      if(hscp)soloEtaMyHisto->Fill(partIt->eta());
      //ABOUT BETA
      float p=partIt->p();
      float e=partIt->energy();
      float beta=p/e;
      betaHisto->Fill(beta);
      if(hscp)betaMyHisto->Fill(beta);
      float pt = partIt->pt();
      //float et = partIt->et();
      float betaT=pt/e;
      betaTHisto->Fill(betaT);
      if(count!=0)bxLayerFile<<"\t"<<" eta="<<partIt->eta()<<" beta="<<beta<<"c";
      if(count!=0)fileMatrix<<" eta="<<partIt->eta()<<" beta="<<beta<<"c Event "<<iEvent.id().event()<<"\n";
      if(fabs(partIt->eta()>1.14))etaout++;
      std::cout<<" p="<<p<<" pt="<<pt<<" m="<<sqrt(e*e-p*p)<<std::endl;
    }
  }
     
  
  //Filling Histograms With all recHitInformation
 
  int vectorbx[11];
  for(int i=0;i<11;i++)vectorbx[i]=0;
  int i =0;

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


  //New Algo

  RPCRecHitCollection::const_iterator recIt1;
  RPCRecHitCollection::const_iterator recIt2;
  RPCRecHitCollection::const_iterator recIt3;
  
  for(recIt1=rpcHits->begin();recIt1!=rpcHits->end();++recIt1){
    const RPCRoll* rollasociated1 = rpcGeo->roll((*recIt1).rpcId());
    const BoundPlane & RPCSurface1 = rollasociated1->surface();
    GlobalPoint RecHitGlobal1 = RPCSurface1.toGlobal((*recIt1).localPosition());
    for(recIt2=rpcHits->begin();recIt2!=rpcHits->end();++recIt2){
      const RPCRoll* rollasociated2 = rpcGeo->roll((*recIt2).rpcId());
      const BoundPlane & RPCSurface2 = rollasociated2->surface();
      GlobalPoint RecHitGlobal2 = RPCSurface2.toGlobal((*recIt2).localPosition());
      for(recIt3=rpcHits->begin();recIt3!=rpcHits->end();++recIt3){
	const RPCRoll* rollasociated3 = rpcGeo->roll((*recIt3).rpcId());
	const BoundPlane & RPCSurface3 = rollasociated3->surface();
	GlobalPoint RecHitGlobal3 = RPCSurface3.toGlobal((*recIt3).localPosition());
	if(recIt1 != recIt2 && recIt2 != recIt3 && recIt1 != recIt3){
	  if(fabs(RecHitGlobal3.eta()-RecHitGlobal2.eta())<=0.15 &&
	     fabs(RecHitGlobal2.eta()-RecHitGlobal1.eta())<=0.15 &&
	     fabs(RecHitGlobal1.eta()-RecHitGlobal3.eta())<=0.15 &&
	     fabs(RecHitGlobal3.phi()-RecHitGlobal2.phi())<=0.02 &&
	     fabs(RecHitGlobal2.phi()-RecHitGlobal1.phi())<=0.02 &&
	     fabs(RecHitGlobal1.phi()-RecHitGlobal3.phi())<=0.02){
	  
	    std::cout<<"Candidate!!!"<<std::endl;
	    std::cout<<"\t RecHit 1"<<RecHitGlobal1<<" "<<RecHitGlobal1.eta()<<" "<<RecHitGlobal1.phi()<<std::endl;
	    std::cout<<"\t RecHit 2"<<RecHitGlobal2<<" "<<RecHitGlobal2.eta()<<" "<<RecHitGlobal2.phi()<<std::endl;
	    std::cout<<"\t RecHit 3"<<RecHitGlobal3<<" "<<RecHitGlobal3.eta()<<" "<<RecHitGlobal3.phi()<<std::endl;
	  }
	}
      }
    }
  }
  
  


}



 void  BETA::endJob() {

  if(simHitHSCP!=recHitHSCP+norHitHSCP)
    std::cout<<simHitHSCP<<"!="<<recHitHSCP+norHitHSCP<<std::endl;
  
  assert(simHitHSCP==recHitHSCP+norHitHSCP);



    //Building Efficiencies
  
  for(int i=1;i<=100;i++){
    std::cout<<betaHisto->GetBinContent(i)<<"\t";
    std::cout<<betaMyHisto->GetBinContent(i)<<"\t \t";

    std::cout<<soloEtaHisto->GetBinContent(i)<<"\t";
    std::cout<<soloEtaMyHisto->GetBinContent(i)<<std::endl;

    if(betaHisto->GetBinContent(i)!=0){
      float eff= (float)(betaMyHisto->GetBinContent(i))/(float)(betaHisto->GetBinContent(i));
      effInBetaHisto->SetBinContent(i,eff*100.);
      float err=sqrt(eff*(1-eff)/(float)(betaHisto->GetBinContent(i)));
      effInBetaHisto->SetBinError(i,err*100.);
      
    }
  
    if(soloEtaHisto->GetBinContent(i)!=0){
      float eff= (float)(soloEtaMyHisto->GetBinContent(i))/(float)(soloEtaHisto->GetBinContent(i));
      effInEtaHisto->SetBinContent(i,eff*100.);
      float err=sqrt(eff*(1-eff)/(float)(soloEtaHisto->GetBinContent(i)));
      effInEtaHisto->SetBinError(i,err*100.);
    }
  }










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
  betaHisto->GetXaxis()->SetTitle("#beta");
  Ca1->SaveAs(beta.c_str());
   
  Ca1->Clear();
 
  std::cout<<"Creating betaTHisto"<<std::endl;
  betaTHisto->Draw();
  betaTHisto->GetXaxis()->SetTitle("#beta_t");
  Ca1->SaveAs(betaT.c_str());

  Ca1->Clear();
 
  std::cout<<"Creating betaMyHisto"<<std::endl;
  betaMyHisto->Draw();
  betaMyHisto->GetXaxis()->SetTitle("#beta_my");
  Ca1->SaveAs("MyBeta.png");

  
  Ca1->Clear();
 
  std::cout<<"Creating soloEtaMyHisto"<<std::endl;
  soloEtaMyHisto->Draw();
  soloEtaMyHisto->GetXaxis()->SetTitle("#eta_my");
  Ca1->SaveAs("soloEtaMy.png");

  Ca1->Clear();
 
  std::cout<<"Creating effInBeta"<<std::endl;
  effInBetaHisto->Draw();
  effInBetaHisto->GetXaxis()->SetTitle("#beta");
  Ca1->SaveAs("EffBeta.png");

  Ca1->Clear();
 
  std::cout<<"Creating effInEta"<<std::endl;
  effInEtaHisto->Draw();
  effInEtaHisto->GetXaxis()->SetTitle("#beta");
  Ca1->SaveAs("EffEta.png");

  Ca1->Clear();
 
  std::cout<<"Creating matrixHisto"<<std::endl;
  matrixHisto->Draw();
  matrixHisto->GetXaxis()->SetTitle("#BX and Layer");
  Ca1->SaveAs("MatrixHisto.png");

  Ca1->Clear();
 
  std::cout<<"Creating diffsimhitrechiteta"<<std::endl;
  diffsimhitrechiteta->Draw();
  diffsimhitrechiteta->GetXaxis()->SetTitle("D-eta");
  Ca1->SaveAs("diffsimhitrechiteta.png");

  Ca1->Clear();
 
  std::cout<<"Creating diffsimhitrechitphi"<<std::endl;
  diffsimhitrechitphi->Draw();
  diffsimhitrechitphi->GetXaxis()->SetTitle("D-phi");
  Ca1->SaveAs("diffsimhitrechitphi.png");


  std::cout<<"cd the file"<<std::endl;

  theFile->cd();

  std::cout<<"Writing the histos"<<std::endl;
  bx->Write();
  
  betaHisto->Write();
  betaMyHisto->Write();
  effInBetaHisto->Write();
  
  betaTHisto->Write();
  NumRecHits->Write();
  nr->Write();
  etaHisto->Write();
  
  soloEtaHisto->Write();
  soloEtaMyHisto->Write();
  effInEtaHisto->Write();
  
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

  diffsimhitrechiteta->Write();
  diffsimhitrechitphi->Write();

  theFile->Close();

  std::cout<<"\n TOTAL bool HSPCs = "<<totalHSCP<<std::endl;
  fileMatrix<<"\n TOTAL bool HSPCs = "<<totalHSCP<<std::endl;

  std::cout<<"\n HSCP with Eta > 1.14 = "<<etaout<<std::endl;
  fileMatrix<<"\n HSCP with Eta > 1.14 = "<<etaout<<std::endl;


  std::cout<<"\n Events with RPCSimHits HSPCs = "<<eventsWithRPCSimHits<<std::endl;
  fileMatrix<<"\n Events with RPCSimHits HSPCs = "<<eventsWithRPCSimHits<<std::endl;

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
