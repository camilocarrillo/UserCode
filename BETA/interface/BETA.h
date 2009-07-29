#ifndef BETA_h
#define BETA_h


#include<string>
#include<map>
#include<fstream>
#include <memory>
#include <cmath>
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"

class TFile;
class TH1F;
class TCanvas;
class TH2F;

class BETA : public edm::EDAnalyzer {
   public:
      explicit BETA(const edm::ParameterSet&);
      ~BETA();
   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      TFile* theFile;
      TH1F * bx;
      TH1F * betaHisto;
      TH1F * betaTHisto;
      TH1F * NumRecHits;
      TH1F * nr;
      TH1F * etaHisto;
      TH1F * soloEtaMyHisto;
      TH1F * soloEtaHisto;
      TH1F * betaMyHisto;
      TH1F * residualRecSimHisto;
      //      TH1F * bitsDistroHisto;

      TH1F * layerB1Histo;
      TH1F * layerB2Histo;
      TH1F * layerB3Histo;
      TH1F * layerB4Histo;
      TH1F * layerB5Histo;
      TH1F * layerB6Histo;

      TH1F * layerE1Histo;
      TH1F * layerE2Histo;
      TH1F * layerE3Histo;

      TH1F * effInBetaHisto;
      TH1F * effInEtaHisto;
      TH1F * matrixHisto;

      TH1F * diffsimhitrechiteta;	
      TH1F * diffsimhitrechitphi;

      int simHitHSCP;
      int norHitHSCP;
      int recHitHSCP;
      int totalHSCP;
      int eventsWithRPCSimHits;
      int etaout;
      bool hscp;

      std::string file;
      std::string bxFile;
      std::string NumRecHitsFile;
      std::string beta;
      std::string betaT;
      std::string partLabel;
      std::string nrFile;      
      std::string trackLabel;
      std::string eta;
      std::string soloeta;
      std::string residualRecSim;
      std::string layerName;
      std::string layerNameEndCap;
      std::string fileNameBXLayer;
      //std::string bitsDistroName;
      std::ofstream bxLayerFile;
      std::ofstream fileMatrix;
      
      
       //edm::ESHandle<reco::ParticleDataTable> pdt_;
};

#endif
