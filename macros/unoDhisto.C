#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void unoDhisto(){
  gROOT->Reset();
  gStyle->SetOptStat(1);

  ifstream data;
  
  float value;

  string name = "chi2bad";
  data.open((name+".txt").c_str());
  
  TH1F * histo = new TH1F("histo",name.c_str(),101,-0.5,10.5);
  data >>value;
  while(!data.eof()){
    cout<<value<<endl;
    histo->Fill(value);
    data >>value;
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  histo->Draw();
  histo->GetXaxis()->SetTitle(name.c_str());
  Ca0->SaveAs((name+".png").c_str());
  
}
