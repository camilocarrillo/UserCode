#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void HLT(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data; 
  float value;

  string name = "HLT"; //name withtout .txt
  data.open((name+".txt").c_str());

  ofstream HLTEffErr; 
  HLTEffErr.open("HLTEffErr.txt");

  string label;
  float eff;
  float err;
  float exp;
  float obs;

  const int N = 227;  

  TH1F * histo = new TH1F("histo",name.c_str(),N,-0.5,N+0.5);

  int bin = 1;

  data >>label>>exp>>obs;

  while(!data.eof()){
    histo->GetXaxis()->SetBinLabel(bin,label.c_str());
    cout<<label<<" "<<exp<<" "<<obs<<endl;

    if(exp!=0){
	eff = obs/exp;
	err = sqrt(eff*(1-eff)/exp);
        histo->SetBinContent(bin,eff);
        histo->SetBinError(bin,err); 
    }
    HLTEffErr<<label<<" "<<eff<<" "<<err<<endl;
    data >>label>>exp>>obs;
    bin++;
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.45);
  histo->Draw();
  histo->SetMaximum(1.1);
  histo->SetMinimum(0.);
  histo->GetXaxis()->LabelsOption("v");
  histo->SetLabelSize(0.01);
  Ca0->SaveAs((name+".png").c_str());
  
}
