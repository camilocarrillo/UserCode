#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringExpObs(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data; 
  float value;

  string name = "HLTEff_Eta24_KKtau"; //name withtout .txt
  data.open((name+".txt").c_str());

  string label;
  float eff;
  float err;
  float exp;
  float obs;

  const int N = 101;  

  TH1F * histo = new TH1F("histo",name.c_str(),101,0.5,101+0.5);
  int bin = 0;

  while(!data.eof() && bin<101){
    bin++;
    data >>label>>obs>>exp;
    histo->GetXaxis()->SetBinLabel(bin,label.c_str());
    cout<<label<<" "<<obs<<" "<<exp<<endl;

    if(exp!=0){
	eff = obs/exp;
	err = sqrt(eff*(1-eff)/exp);
        histo->SetBinContent(bin,eff);
        histo->SetBinError(bin,err); 
    }
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.45);
  histo->Draw();
  histo->SetMaximum(1.1);
  histo->SetMinimum(0.);
  histo->GetXaxis()->LabelsOption("v");
  histo->SetLabelSize(0.03);
  Ca0->SaveAs((name+".png").c_str());
  
}
