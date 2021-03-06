#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringEffErrEffErr(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data;
  
  float value;

  string name = "NoMap_GoodMapMu";
	
  data.open((name+".txt").c_str());

  string event="hola";
  float expuno=1;
  float expdos=1;
  float obsuno=1;
  float obsdos=1;

  const int N = 35;  

  TH1F * histoUno = new TH1F("Uno","Uno",N,0.5,N+0.5);
  TH1F * histoDos = new TH1F("Dos","Dos",N,0.5,N+0.5);

  int bin = 0;
  float sumdiff=0	;
	
  while(!data.eof() && bin<N){
    bin++;
    data >>event>>obsuno>>expuno>>obsdos>>expdos;
    //cout<<event<<" "<<obsuno<<" "<<expuno<<" "<<obsdos<<" "<<expdos<<endl;
    
    histoUno->GetXaxis()->SetBinLabel(bin,event.c_str());

    float effuno = 0;
    float erruno = 0;

    if(expuno!=0){
      effuno = obsuno/expuno;
      erruno = sqrt(effuno*(1-effuno)/expuno);
    }

    float effdos = 0;
    float errdos = 0;

    if(expdos!=0){
      effdos = obsdos/expdos;
      errdos = sqrt(effdos*(1-effdos)/expdos);
    }

    cout<<event<<" "<<effuno<<" "<<erruno<<" "<<effdos<<" "<<errdos<<" "<<effuno-effdos<<" "<<erruno+errdos<<endl;
    sumdiff = sumdiff+(effuno-effdos);

    histoUno->SetBinContent(bin,effuno);
    histoUno->SetBinError(bin,erruno);
    histoDos->GetXaxis()->SetBinLabel(bin,event.c_str());
    histoDos->SetBinContent(bin,effdos);
    histoDos->SetBinError(bin,errdos);
  }
  
  cout<<"average drop"<<sumdiff/((float) N)<<endl;
  
  histoUno->SetLineColor(2);
  histoDos->SetLineColor(4);

  histoUno->SetLineWidth(3);
  histoDos->SetLineWidth(3);

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.4);
  histoUno->SetLabelSize(0.04);
  histoUno->GetYaxis()->SetTitle("Efficiency(%)");
  histoUno->Draw("");
  histoUno->GetXaxis()->LabelsOption("v");

  histoDos->SetLabelSize(0.04);
  histoDos->Draw("same");
  histoDos->GetXaxis()->LabelsOption("v");
 
  TLegend *leg = new TLegend(0.4,0.8,0.7,0.7);
  leg->AddEntry(histoUno,"No_Map","l");
  leg->AddEntry(histoDos,"Good_Map","l");
  leg->Draw("same");
  
  Ca0->SaveAs((name+".png").c_str());
 
}
