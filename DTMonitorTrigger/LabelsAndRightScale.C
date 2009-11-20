#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void LabelsAndRightScale(){
  //gROOT->Reset();
  gStyle->SetOptStat(0);
  TFile *f =new TFile("/tmp/carrillo/GMTOccupancyBit6.root");
  TH1F *expGMT_etaphi  = (TH1F*) (f->Get("DQMData/TriggerMonitoringPlots/expGMT_etaphi"));
  
  const double gmt_etascale[63] = {-2.40, -2.35, -2.30, -2.25, -2.20, -2.15, -2.10,  
			    -2.05, -2.00, -1.95, -1.90, -1.85, -1.80, -1.75,  
			    -1.70, -1.60, -1.50, -1.40, -1.30, -1.20, -1.10,  
			    -1.00, -0.90, -0.80, -0.70, -0.60, -0.50, -0.40,  
			    -0.30, -0.20, -0.10,  0.00,  0.10,  0.20,  0.30,  
			    0.40,  0.50,  0.60,  0.70,  0.80,  0.90,  1.00,  
			    1.10,  1.20,  1.30,  1.40,  1.50,  1.60,  1.70,  
			    1.75,  1.80,  1.85,  1.90,  1.95,  2.00,  2.05,  
			    2.10,  2.15,  2.20,  2.25,  2.30,  2.35,  2.40};
  
   TH2F *NewexpGMT_etaphi = new TH2F("NewexpGMT_etaphi","NewGMTTriggerEtaPhi",62,gmt_etascale,144,0.,360.);

   for(int etabin = 1;etabin<=63;etabin++){
     for(int phibin = 1;phibin<=144;phibin++){
       float occupancy = expGMT_etaphi->GetBinContent(etabin,phibin);
       if(occupancy!=0) std::cout<<occupancy<<std::endl;
       NewexpGMT_etaphi->SetBinContent(etabin,phibin,occupancy);
     }
   }

   TCanvas * Ca0 = new TCanvas("Ca0","NewexpGMT_Etaphi",1200,800);
   NewexpGMT_etaphi->Draw();
   NewexpGMT_etaphi->GetXaxis()->SetTitle("eta");
   NewexpGMT_etaphi->GetYaxis()->SetTitle("phi");
   Ca0->SaveAs("GMTOccupancyGoodEta.png");
//   Ca0->Clear();
   
/*   expGMT_etaphi->Draw();
   expGMT_etaphi->GetXaxis()->SetTitle("discrete eta");
   expGMT_etaphi->GetYaxis()->SetTitle("phi");
//   Ca0->SaveAs("GMTOccupancy.png");
//   Ca0->Clear();

//   exit(0);
*/
}
