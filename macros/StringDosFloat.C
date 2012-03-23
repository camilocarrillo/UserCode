#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringDosFloat(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data;
  
  float value;

  string name = "HLT2";
	
  data.open((name+".txt").c_str());
  string event;
  float uno;
  float dos;
  float erruno;
  float errdos;

  const int N = 73;  

 TH1F * histoUno = new TH1F("Uno","Uno",N,0.5,N+0.5);
 TH1F * histoDos = new TH1F("Dos","Dos",N,0.5,N+0.5);

 int bin = 0;

  while(!data.eof() && bin<N){
    bin++;
    data >>event>>uno>>erruno>>dos>>errdos;
    cout<<event<<" "<<uno<<" "<<erruno<<" "<<dos<<" "<<errdos<<endl;
    histoUno->GetXaxis()->SetBinLabel(bin,event.c_str());
    histoUno->SetBinContent(bin,uno);
    histoUno->SetBinError(bin,erruno);
    histoDos->GetXaxis()->SetBinLabel(bin,event.c_str());
    histoDos->SetBinContent(bin,dos);
    histoDos->SetBinError(bin,errdos);
  }
  
  histoUno->SetLineColor(2);
  histoDos->SetLineColor(4);

  histoUno->SetLineWidth(3);
  histoDos->SetLineWidth(3);

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.4);
  histoUno->SetLabelSize(0.03);
  histoUno->GetYaxis()->SetTitle("Efficiency(%)");
  histoUno->Draw("");
  histoUno->GetXaxis()->LabelsOption("v");

  histoDos->SetLabelSize(0.03);
  histoDos->Draw("same");
  histoDos->GetXaxis()->LabelsOption("v");
 
  TLegend *leg = new TLegend(0.4,0.8,0.7,0.7);
  leg->AddEntry(histoUno,"Madgraph","l");
  leg->AddEntry(histoDos,"Pythia","l");
  leg->Draw("same");
  
  Ca0->SaveAs((name+".png").c_str());
 
}
