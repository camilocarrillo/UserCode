#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void slopesx2(){
  gROOT->Reset();
  gStyle->SetOptStat(1);

  ifstream data;
  
  float value, value2;

  string name = "slopesx2";

  data.open((name+".txt").c_str());
  
  TH1F * histo = new TH1F("histo",name.c_str(),100,-5,5);
  TH1F * histo2 = new TH1F("histo2",name.c_str(),100,-5,5);
  data >>value>>value2;

  while(!data.eof()){
    cout<<value<<" "<<value2<<endl;
    histo->Fill(value*10);
    histo2->Fill(value2*10);
    data >>value>>value2;
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  histo2->Draw();
  histo2->SetFillColor(kBlue);
  histo->Draw("same");
  //  histo->SetLinceColor(kRed);
  histo->GetXaxis()->SetTitle("%/10mbar");
  Ca0->SaveAs((name+".png").c_str());
  
}
