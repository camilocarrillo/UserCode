#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringFloat(){
  gROOT->Reset();
  gStyle->SetOptStat(1111111);

  ifstream data;
  
  float value;

 // string name = "L1Eff"; //name withtout .txt
  string name = "JustRPCMon7TeV";
	
  data.open((name+".txt").c_str());
  string label;
  float eff;
  
  TH1F * histo = new TH1F("histo",name.c_str(),66,0.5,66.5);
  int bin = 0;

  while(!data.eof() && bin<66){
    bin++;
    data >>label>>eff;
    cout<<label<<" "<<eff<<endl;
    histo->GetXaxis()->SetBinLabel(bin,label.c_str());
    histo->SetBinContent(bin,eff);
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
//  Ca0->SetBottomMargin(0.4);
  histo->Draw();
//  histo->SetMaximum(100000.);
// histo->SetMinimum(0.);
  histo->GetXaxis()->LabelsOption("v");
  histo->GetYaxis()->SetTitle("Events/run");
  
  histo->SetLabelSize(0.03);
  Ca0->SetLogy();
  Ca0->SaveAs((name+".png").c_str());
  
}
