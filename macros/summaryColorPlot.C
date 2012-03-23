#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <TStyle.h>

void setHisto(TH2F * histo){
  //  histo->GetXaxis()->LabelsOption("v");
  //  histo->GetXaxis()->SetLabelSize(0.03);
  //histo->Draw("CONT4COLZ ");         
}

void summaryColorPlot(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  cout<<"getting the file"<<endl;

  //TFile * theFile = new TFile("/var/www/html/tmp/eff69912_300pre10_Straighter/seceff69912_300pre10_Straighter.root");  
  //TFile * theFile = new TFile("/var/www/html/efficiency/_Cosmics_Commissioning08_CRAFT_ALL_V4_ReReco-v1_RECO/69912/sec69912.root");
  //TFile * theFile = new TFile("/var/www/html/efficiency/_Eff_My_HLT_Skim/alineamiento70195/seceffalineamiento70195.root");
  //TFile * theFile = new TFile("eff110900.root");  
  TFile * theFile = new TFile("secFactorization.root");  
  //TFile * theFile = new TFile("sec220_9400.root");
  //TFile * theFile = new TFile("secondmuon.root");

  cout<<"getting the histo"<<endl;

  TH2F * summary = (TH2F*) (theFile->Get("Efficiency_Roll_vs_Sector_Disk_-1"));

  summary->SetMinimum(0);
  summary->SetMaximum(100);

  if(summary) cout<<"histo not found"<<endl;

  cout<<"creating canvas"<<endl;
  TCanvas * Ca0 = new TCanvas("Ca0","Muography",1200,800);

  int colorPalette3[20];

  colorPalette3[0]= 632; // 0 red 
  colorPalette3[1]= 632; // 5 red
  colorPalette3[2]= 632; // 10 
  colorPalette3[3]= 632; // 15 
  colorPalette3[4]= 632; // 20 
  colorPalette3[5]= 632; // 25 
  colorPalette3[6]= 632; // 30 
  colorPalette3[7]= 632; // 35
  colorPalette3[8]= 632; // 40
  colorPalette3[9]= 632; // 45
  colorPalette3[10]= 632; // 50
  colorPalette3[11]= 632; // 55
  colorPalette3[12]= 632; // 60
  colorPalette3[13]= 632; // 65
  colorPalette3[14]= 807; // 70
  colorPalette3[15]= 807; // 75
  colorPalette3[16]= 400; // 80
  colorPalette3[17]= 400; // 85
  colorPalette3[18]= 400; // 90 
  colorPalette3[19]= 416; // 95 % green 
  
  gStyle->SetPalette(20,colorPalette3);

  summary->Draw("");         
  summary->Draw("COLZ");         

  cout<<"saving plot"<<endl;
  Ca0->SaveAs("summary.png");

  //  exit(0);
  
}
