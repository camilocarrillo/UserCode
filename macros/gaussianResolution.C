#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TLegend"

void setHisto(TH2F * histo){
  //  histo->GetXaxis()->LabelsOption("v");
  //  histo->GetXaxis()->SetLabelSize(0.03);
  //histo->Draw("CONT4COLZ ");         
  histo->Draw("COLZ ");         
  //histo->Draw("");         
  histo->GetXaxis()->SetTitle("cm");
  histo->GetYaxis()->SetTitle("cm");
  histo->SetTitle("2D Efficiency for W+2_RB2in_S04_Forward");
}

void gaussianResolution(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  //gStyle->SetOptStat(S);
  gStyle->SetOptFit(0);

  cout<<"getting the file"<<endl;

  TFile * theFile = new TFile("secefficiency-WZ.root");  
	
  cout<<"getting the histo"<<endl;

  string title = "residualStation1Ring2_C";

  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str()));
			      
  residuals->GetXaxis()->SetTitle((title+" (cm)").c_str());
  residuals->GetXaxis()->SetRangeUser(-6,6);
  residuals->SetLineWidth(3);
  residuals->Fit("gaus","Q" ,"C" ,-2,2);
  float sigma = residuals->GetFunction("gaus")->GetParameter(2);

  cout<<sigma<<endl;
  
  stringstream legend;
    
  TLegend *leg = new TLegend(0.75,0.9,0.9,0.8);
  legend.str("");
  legend<<"sigma =  "<<sigma<<"cm";
  residuals->GetFunction("gaus")->SetLineWidth(3);
  leg->AddEntry(residuals->GetFunction("gaus"),legend.str().c_str(),"l");
  
  if(!residuals) cout<<"histo not found"<<endl;
  
  cout<<"creating canvas"<<endl;
  TCanvas * Ca0 = new TCanvas("Ca0","Residuals",1200,800);
  residuals->Draw();
  leg->Draw("same");
  cout<<"saving plot"<<endl;
  Ca0->SaveAs((title+".png").c_str());

  //  exit(0);
  
}
