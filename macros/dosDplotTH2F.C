#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void dosDplotTH2F(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);


  ifstream data;

  float valuex;
  float valuey;

  string name = "xy";
  data.open((name+".txt").c_str());

  TH2F * histo = new TH2F("histo",name.c_str(),100,8.500,10.000,100,0,100);

  while(!data.eof()){
    data >>valuex>>valuey;
    cout<<valuex<<" "<<valuey<<endl;
    histo->Fill(valuex,valuey);
  }

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  histo->Draw();
  histo->GetXaxis()->SetTitle(name.c_str());
  histo->GetXaxis()->LabelsOption("h");
  histo->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str());

}



