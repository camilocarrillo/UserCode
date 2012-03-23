#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringExpObsExpObs(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data;
  
  float value;

  //  string name = "2011Map_testGrid";
  string name = "original_grid";

  data.open((name+".txt").c_str());

  string event;
  float expuno=0.;
  float expdos=0.;
  float obsuno=0.;
  float obsdos=0.;

  const int N = 72;  

  TH1F * histoUno = new TH1F("Uno","Uno",N,0.5,N+0.5);
  TH1F * histoDos = new TH1F("Dos","Dos",N,0.5,N+0.5);

  int bin = 1;
  float sumdiff=0.;
	
  data >>event>>expuno>>obsuno>>expdos>>obsdos;

  float effuno;
  float erruno;
  float effdos;
  float errdos;

  while(!data.eof()){
    cout<<"input \t "<<event<<" "<<expuno<<" "<<obsuno<<" "<<expdos<<" "<<obsdos<<endl;
    
    histoUno->GetXaxis()->SetBinLabel(bin,event.c_str());

    effuno = 0.;
    erruno = 0.;

    if(expuno!=0){
      effuno = obsuno/expuno;
      erruno = sqrt(effuno*(1-effuno)/expuno);
    }
    
    if(obsuno==0 && expuno!=0){
      effuno = 0.000001;
      erruno = 0.000001;
    }
    
   //cout<<event<<" "<<effuno<<" "<<erruno<<endl;

    effdos = 0.;
    errdos = 0.;
    
    if(expdos!=0){
      effdos = obsdos/expdos;
      errdos = sqrt(effdos*(1-effdos)/expdos);
    }

    if(obsdos==0 && expdos!=0){
      effdos = 0.000001;
      errdos = 0.000001;
    }


    //    cout<<event<<" "<<effdos<<" "<<errdos<<endl;
    
    cout<<"output \t "<<event<<" "<<effuno<<" "<<erruno<<" "<<effdos<<" "<<errdos<<" "<<effuno-effdos<<" "<<erruno+errdos<<endl;
    sumdiff = sumdiff+(effuno-effdos);

    histoUno->SetBinContent(bin,effuno);
    histoUno->SetBinError(bin,erruno);
    histoDos->GetXaxis()->SetBinLabel(bin,event.c_str());
    histoDos->SetBinContent(bin,effdos);
    histoDos->SetBinError(bin,errdos);
    bin++;
    
    data >>event>>expuno>>obsuno>>expdos>>obsdos;

  }
  
  cout<<"average drop"<<sumdiff/((float) N)<<endl;
  
  histoUno->SetLineColor(2);
  histoDos->SetLineColor(4);

  histoUno->SetMarkerColor(2);
  histoDos->SetMarkerColor(4);

  histoUno->SetMarkerSize(1.2);
  histoDos->SetMarkerSize(1.2);

  histoUno->SetLineWidth(3);
  histoDos->SetLineWidth(3);

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",900,600);
  Ca0->SetBottomMargin(0.4);
  histoUno->SetLabelSize(0.03);
  histoUno->GetYaxis()->SetTitle("Efficiency(%)");
  histoUno->SetMinimum(-0.01);
  histoUno->Draw("");
  histoUno->GetXaxis()->LabelsOption("v");

  histoDos->SetLabelSize(0.03);
  histoDos->SetMinimum(-0.01);
  histoDos->Draw("same");
  histoDos->GetXaxis()->LabelsOption("v");
 
  TLegend *leg = new TLegend(0.4,0.8,0.7,0.7);
  leg->AddEntry(histoUno,"original","l");
  leg->AddEntry(histoDos,"grid","l");
  leg->Draw("same");
  
  Ca0->SaveAs((name+".png").c_str());
 
}
