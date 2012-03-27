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

void CSCOccupancy(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  cout<<"getting the file"<<endl;

  string name = "HighLumi_AllSegments" ;
  
  TFile * theFile = new TFile(("../"+name+".root").c_str());  
  
  cout<<"getting the histo"<<endl;

  TH2F * OccupancyDiskm3 = (TH2F*) (theFile->Get("OccupancyDiskm3"));
  TH2F * OccupancyDiskm2 = (TH2F*) (theFile->Get("OccupancyDiskm2"));
  TH2F * OccupancyDiskm1= (TH2F*) (theFile->Get("OccupancyDiskm1"));
  TH2F * OccupancyDisk1 = (TH2F*) (theFile->Get("OccupancyDisk1"));
  TH2F * OccupancyDisk2 = (TH2F*) (theFile->Get("OccupancyDisk2"));
  TH2F * OccupancyDisk3 = (TH2F*) (theFile->Get("OccupancyDisk3"));; 


  TH1F * nHits= (TH1F*) (theFile->Get("NumberOfHits"));
  TH1F * Hdof= (TH1F*) (theFile->Get("DegreesOfFreedom"));
  TH1F * chi2= (TH1F*) (theFile->Get("chi2"));
  TH1F * dimen= (TH1F*) (theFile->Get("dimen"));
  TH1F * HnumberOfSegmentsPerEvent = (TH1F*) (theFile->Get("HnumberOfSegmentsPerEvent"));
  TH1F * HnumberOfSegmentsPerEventDim4 = (TH1F*) (theFile->Get("HnumberOfSegmentsPerEventDim4"));

  //  if(!occupancy) cout<<"histo not found"<<endl;

  cout<<"creating canvas"<<endl;
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);

  OccupancyDiskm3->GetXaxis()->SetLabelSize(0.12);
  OccupancyDiskm2->GetXaxis()->SetLabelSize(0.12);
  OccupancyDiskm1->GetXaxis()->SetLabelSize(0.12);
  OccupancyDisk1->GetXaxis()->SetLabelSize(0.12);
  OccupancyDisk2->GetXaxis()->SetLabelSize(0.12);
  OccupancyDisk3->GetXaxis()->SetLabelSize(0.12);

  OccupancyDiskm3->GetXaxis()->SetTitleSize(0.25);
  OccupancyDiskm2->GetXaxis()->SetTitleSize(0.25);
  OccupancyDiskm1->GetXaxis()->SetTitleSize(0.25);
  OccupancyDisk1->GetXaxis()->SetTitleSize(0.25);
  OccupancyDisk2->GetXaxis()->SetTitleSize(0.25);
  OccupancyDisk3->GetXaxis()->SetTitleSize(0.25);


  Ca0->Divide(1,6); 
  
  Ca0_1->cd();
  OccupancyDiskm3->Draw("COLZ"); OccupancyDiskm3->GetXaxis()->SetTitle("Sector"); OccupancyDiskm3->GetYaxis()->SetTitle("Station Wheel -2"); OccupancyDiskm3->SetTitle("Occupancy Wheel -2");
  Ca0_2->cd();
  OccupancyDiskm2->Draw("COLZ"); OccupancyDiskm2->GetXaxis()->SetTitle("Sector"); OccupancyDiskm2->GetYaxis()->SetTitle("Station Wheel -1"); OccupancyDiskm2->SetTitle("Occupancy Wheel -1");
  Ca0_3->cd();
  OccupancyDiskm1->Draw("COLZ"); OccupancyDiskm1->GetXaxis()->SetTitle("Sector"); OccupancyDiskm1->GetYaxis()->SetTitle("Station Wheel 0"); OccupancyDiskm1->SetTitle("Occupancy Wheel 0"); 
  Ca0_4->cd();
  OccupancyDisk3->Draw("COLZ"); OccupancyDisk3->GetXaxis()->SetTitle("Sector"); OccupancyDisk3->GetYaxis()->SetTitle("Station Wheel -2"); OccupancyDisk3->SetTitle("Occupancy Wheel -2");
  Ca0_5->cd();
  OccupancyDisk2->Draw("COLZ"); OccupancyDisk2->GetXaxis()->SetTitle("Sector"); OccupancyDisk2->GetYaxis()->SetTitle("Station Wheel -1"); OccupancyDisk2->SetTitle("Occupancy Wheel -1");
  Ca0_6->cd();
  OccupancyDisk1->Draw("COLZ"); OccupancyDisk1->GetXaxis()->SetTitle("Sector"); OccupancyDisk1->GetYaxis()->SetTitle("Station Wheel 0"); OccupancyDisk1->SetTitle("Occupancy Wheel 0"); 
  
 
  Ca0->SaveAs(("Occupancy_"+name+".png").c_str());

  TCanvas * Ca1= new TCanvas("Ca1","Canvas",1200,700);  

  Ca1->Divide(3,2); 
  Ca1_1->cd();
  nHits->Draw(); nHits->GetXaxis()->SetTitle("Number of Hits 4D Segment");  nHits->GetXaxis()->SetTitleSize(0.06);nHits->GetXaxis()->SetLabelSize(0.04);
  Ca1_2->cd();
  Hdof->Draw(); Hdof->GetXaxis()->SetTitle("Number of Degrees of Freedom 4D Segment");Hdof->GetXaxis()->SetTitleSize(0.06);Hdof->GetXaxis()->SetLabelSize(0.04);
  Ca1_3->cd();
  chi2->Draw(); chi2->GetXaxis()->SetTitle("#chi^2/ndof");chi2->GetXaxis()->SetTitleSize(0.06);chi2->GetXaxis()->SetLabelSize(0.04);
  Ca1_4->cd();
  dimen->Draw(); dimen->GetXaxis()->SetTitle("Segment Dimension");dimen->GetXaxis()->SetTitleSize(0.06);dimen->GetXaxis()->SetLabelSize(0.04);
  Ca1_5->cd();
  HnumberOfSegmentsPerEvent->Draw(); HnumberOfSegmentsPerEvent->GetXaxis()->SetTitle("Number of Segments Per Event");HnumberOfSegmentsPerEvent->GetXaxis()->SetTitleSize(0.06);HnumberOfSegmentsPerEvent->GetXaxis()->SetLabelSize(0.04);
  HnumberOfSegmentsPerEventDim4->Draw("same"); HnumberOfSegmentsPerEventDim4->GetXaxis()->SetTitle("Number of Segments Per Event");HnumberOfSegmentsPerEventDim4->GetXaxis()->SetTitleSize(0.06);HnumberOfSegmentsPerEventDim4->GetXaxis()->SetLabelSize(0.04);
  HnumberOfSegmentsPerEventDim4->SetFillColor(4);

  cout<<"saving plot"<<endl;
  Ca1->SaveAs(("Distributions_"+name+".png").c_str());

  exit(0);
  
}
