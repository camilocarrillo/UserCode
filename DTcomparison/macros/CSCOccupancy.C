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

  string name = "LowLumi_AllSegments" ;
  
  TFile * theFile = new TFile(("../"+name+".root").c_str());  
  
  cout<<"getting the histo"<<endl;

  TH2F * OccupancyDiskm3 = (TH2F*) (theFile->Get("OccupancyWheelm2"));
  TH2F * OccupancyDiskm2 = (TH2F*) (theFile->Get("OccupancyWheelm1"));
  TH2F * OccupancyDiskm1= (TH2F*) (theFile->Get("OccupancyWheel0"));
  TH2F * OccupancyDisk1 = (TH2F*) (theFile->Get("OccupancyWheel1"));
  TH2F * OccupancyDisk2 = (TH2F*) (theFile->Get("OccupancyWheel2"));
  TH2F * OccupancyDisk3 = (TH2F*) (theFile->Get("OccupancyWheel2"));; 


  TH1F * nHits= (TH1F*) (theFile->Get("NumberOfHits"));
  TH1F * nHitsPhi= (TH1F*) (theFile->Get("NumberOfHitsPhi"));
  TH1F * nHitsZ= (TH1F*) (theFile->Get("NumberOfHitsZ"));
	 					   
  TH1F * Hdof= (TH1F*) (theFile->Get("DegreesOfFreedom"));
  TH1F * HdofPhi= (TH1F*) (theFile->Get("DegreesOfFreedomPhi"));
  TH1F * HdofZ= (TH1F*) (theFile->Get("DegreesOfFreedomZ"));
  
  TH1F * chi2= (TH1F*) (theFile->Get("chi2"));
  TH1F * dimen= (TH1F*) (theFile->Get("dimen"));
  TH1F * proy= (TH1F*) (theFile->Get("proy"));

  TH1F * HnumberOfSegmentsPerEvent = (TH1F*) (theFile->Get("HnumberOfSegmentsPerEvent"));
  TH1F * HnumberOfSegmentsPerEventDim4 = (TH1F*) (theFile->Get("HnumberOfSegmentsPerEventDim4"));

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
  Ca0->SaveAs(("Occupancy_"+name+".png").c_str());

  TCanvas * Ca1= new TCanvas("Ca1","Canvas",1200,800);  

  Ca1->Divide(3,3); 
  Ca1_1->cd();
  nHits->Draw(); nHits->GetXaxis()->SetTitle("Number of Hits 4D Segment");  nHits->GetXaxis()->SetTitleSize(0.06);nHits->GetXaxis()->SetLabelSize(0.04);
  Ca1_2->cd();
  nHitsPhi->Draw(); nHitsPhi->GetXaxis()->SetTitle("Number of Hits #phi Segment"); nHitsPhi->GetXaxis()->SetTitleSize(0.06);nHitsPhi->GetXaxis()->SetLabelSize(0.04);
  Ca1_3->cd();
  nHitsZ->Draw(); nHitsZ->GetXaxis()->SetTitle("Number of Hits Z Segment");nHitsZ->GetXaxis()->SetTitleSize(0.06);nHitsZ->GetXaxis()->SetLabelSize(0.04);
  Ca1_4->cd();
  Hdof->Draw(); Hdof->GetXaxis()->SetTitle("Number of Degrees of Freedom 4D Segment");Hdof->GetXaxis()->SetTitleSize(0.06);Hdof->GetXaxis()->SetLabelSize(0.04);
  Ca1_5->cd();
  HdofPhi->Draw(); HdofPhi->GetXaxis()->SetTitle("Number of Degrees of Freedom #phi segment");HdofPhi->GetXaxis()->SetTitleSize(0.06);HdofPhi->GetXaxis()->SetLabelSize(0.04);
  Ca1_6->cd();
  HdofZ->Draw(); HdofZ->GetXaxis()->SetTitle("Number of Degrees of Freedom Z segment");HdofZ->GetXaxis()->SetTitleSize(0.06);HdofZ->GetXaxis()->SetLabelSize(0.04);
  Ca1_7->cd();
  chi2->Draw(); chi2->GetXaxis()->SetTitle("#chi^2/ndof");chi2->GetXaxis()->SetTitleSize(0.06);chi2->GetXaxis()->SetLabelSize(0.04);
  Ca1_8->cd();
  dimen->Draw(); dimen->GetXaxis()->SetTitle("Segment Dimension");dimen->GetXaxis()->SetTitleSize(0.06);dimen->GetXaxis()->SetLabelSize(0.04);
  Ca1_9->cd();
  HnumberOfSegmentsPerEvent->Draw(); HnumberOfSegmentsPerEvent->GetXaxis()->SetTitle("Number of Segments Per Event");HnumberOfSegmentsPerEvent->GetXaxis()->SetTitleSize(0.06);HnumberOfSegmentsPerEvent->GetXaxis()->SetLabelSize(0.04);
  HnumberOfSegmentsPerEventDim4->Draw("same"); HnumberOfSegmentsPerEventDim4->GetXaxis()->SetTitle("Number of Segments Per Event");HnumberOfSegmentsPerEventDim4->GetXaxis()->SetTitleSize(0.06);HnumberOfSegmentsPerEventDim4->GetXaxis()->SetLabelSize(0.04);
  HnumberOfSegmentsPerEventDim4->SetFillColor(4);

  cout<<"saving plot"<<endl;
  Ca1->SaveAs(("Distributions_"+name+".png").c_str());

  exit(0);
  
}
