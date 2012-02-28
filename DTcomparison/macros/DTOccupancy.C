#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void setHisto(TH2F * histo){
  //  histo->GetXaxis()->LabelsOption("v");
  //  histo->GetXaxis()->SetLabelSize(0.03);
  //histo->Draw("CONT4COLZ ");         
}

void DTOccupancy(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  cout<<"getting the file"<<endl;

  //  TFile * theFile = new TFile("../histograms.root");  
  //TFile * theFile = new TFile("../histograms180250.root");  
  //  TFile * theFile = new TFile("../histograms180250_STASegments.root");  
  TFile * theFile = new TFile("../histograms163286STA.root");  

	
  cout<<"getting the histo"<<endl;

  TH2F * OccupancyWheelm2 = (TH2F*) (theFile->Get("OccupancyWheelm2"));
  TH2F * OccupancyWheelm1 = (TH2F*) (theFile->Get("OccupancyWheelm1"));
  TH2F * OccupancyWheel0 = (TH2F*) (theFile->Get("OccupancyWheel0"));
  TH2F * OccupancyWheel1 = (TH2F*) (theFile->Get("OccupancyWheel1"));
  TH2F * OccupancyWheel2 = (TH2F*) (theFile->Get("OccupancyWheel2"));
  
  //  if(!occupancy) cout<<"histo not found"<<endl;

  cout<<"creating canvas"<<endl;
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);

  OccupancyWheelm2->GetXaxis()->SetLabelSize(0.12);
  OccupancyWheelm1->GetXaxis()->SetLabelSize(0.12);
  OccupancyWheel0->GetXaxis()->SetLabelSize(0.12);
  OccupancyWheel1->GetXaxis()->SetLabelSize(0.12);
  OccupancyWheel2->GetXaxis()->SetLabelSize(0.12);

  OccupancyWheelm2->GetYaxis()->SetLabelSize(0.17);
  OccupancyWheelm1->GetYaxis()->SetLabelSize(0.17);
  OccupancyWheel0->GetYaxis()->SetLabelSize(0.17);
  OccupancyWheel1->GetYaxis()->SetLabelSize(0.17);
  OccupancyWheel2->GetYaxis()->SetLabelSize(0.17);

  OccupancyWheelm2->GetXaxis()->SetTitleSize(0.25);
  OccupancyWheelm1->GetXaxis()->SetTitleSize(0.25);
  OccupancyWheel0->GetXaxis()->SetTitleSize(0.25);
  OccupancyWheel1->GetXaxis()->SetTitleSize(0.25);
  OccupancyWheel2->GetXaxis()->SetTitleSize(0.25);

  OccupancyWheelm2->GetYaxis()->SetTitleSize(0.25);
  OccupancyWheelm1->GetYaxis()->SetTitleSize(0.25);
  OccupancyWheel0->GetYaxis()->SetTitleSize(0.25);
  OccupancyWheel1->GetYaxis()->SetTitleSize(0.25);
  OccupancyWheel2->GetYaxis()->SetTitleSize(0.25);

  Ca0->Divide(1,5); 
  Ca0_1->cd();
  OccupancyWheelm2->Draw("COLZ"); OccupancyWheelm2->GetXaxis()->SetTitle("Sector"); OccupancyWheelm2->GetYaxis()->SetTitle("Station Wheel -2"); OccupancyWheelm2->SetTitle("Occupancy Wheel -2");
  Ca0_2->cd();
  OccupancyWheelm1->Draw("COLZ"); OccupancyWheelm1->GetXaxis()->SetTitle("Sector"); OccupancyWheelm1->GetYaxis()->SetTitle("Station Wheel -1"); OccupancyWheelm1->SetTitle("Occupancy Wheel -1");
  Ca0_3->cd();
  OccupancyWheel0->Draw("COLZ"); OccupancyWheel0->GetXaxis()->SetTitle("Sector"); OccupancyWheel0->GetYaxis()->SetTitle("Station Wheel 0"); OccupancyWheel0->SetTitle("Occupancy Wheel 0"); 
  Ca0_4->cd();
  OccupancyWheel1->Draw("COLZ"); OccupancyWheel1->GetXaxis()->SetTitle("Sector"); OccupancyWheel1->GetYaxis()->SetTitle("Station Wheel 1"); OccupancyWheel1->SetTitle("Occupancy Wheel 1");
  Ca0_5->cd();
  OccupancyWheel2->Draw("COLZ"); OccupancyWheel2->GetXaxis()->SetTitle("Sector"); OccupancyWheel2->GetYaxis()->SetTitle("Station Wheel 2"); OccupancyWheel2->SetTitle("Occupancy Wheel 2");
  cout<<"saving plot"<<endl;
  Ca0->SaveAs("occupancy_163286STA.png");

  exit(0);
  
}
