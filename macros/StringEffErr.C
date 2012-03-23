#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringEffErr(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data;
  
  float value;

 // string name = "L1Eff"; //name withtout .txt
  string name = "effWheel";
	
  data.open((name+".txt").c_str());
  string label;
  float eff;
  float err;
  
  const int N = 5;
  TH1F * histo = new TH1F("histo",name.c_str(),N,-0.5,N-0.5);
  int bin = 1;

  data >>label>>eff>>err;

  while(!data.eof() && bin<N){
    bin++;
    cout<<label<<" "<<eff<<" "<<err<<endl;
    histo->GetXaxis()->SetBinLabel(bin,label.c_str());
    histo->SetBinContent(bin,eff);
    histo->SetBinError(bin,err);
    data >>label>>eff>>err;
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.4);
  histo->Draw();
  histo->SetMaximum(1.);
  histo->SetMinimum(0.9);
  histo->GetXaxis()->LabelsOption("v");
  histo->SetLabelSize(0.03);
  Ca0->SaveAs((name+".png").c_str());
  
}
