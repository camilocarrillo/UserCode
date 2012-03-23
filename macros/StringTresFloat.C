#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void StringTresFloat(){
  gROOT->Reset();
  gStyle->SetOptStat(0);

  ifstream data;
  
  float value;

 // string name = "L1Eff"; //name withtout .txt
  string name = "time";
	
  data.open((name+".txt").c_str());
  int event;
  float uno;
  float dos;
  float tres;

  const int to = 1269945066;
  const int tf = 1269947903;

  TH1F * histoUno = new TH1F("histo",name.c_str(),tf-to,to,tf);
  TH1F * histoDos = new TH1F("histo",name.c_str(),tf-to,to,tf);
  TH1F * histoTres = new TH1F("histo",name.c_str(),tf-to,to,tf);

  int Tmax =0;  
  int Tmin =9967372379;
  int bin = 0;

  while(!data.eof() && bin<1165){
    bin++;
    data >>event>>uno>>dos>>tres;
    cout<<event<<" "<<uno<<" "<<dos<<" "<<tres<<endl;
    histoUno->Fill(event,uno);
    histoDos->Fill(event,dos);
    histoTres->Fill(event,tres);
    if(event > Tmax) Tmax = event;
    if(event < Tmin) Tmin = event;
  }
  
  cout<<"timeinfo"<<Tmin<<" "<<Tmax<<endl;

  histoUno->SetLineColor(2);
  histoDos->SetLineColor(4);
  histoTres->SetLineColor(6);

  histoUno->SetLineWidth(3);
  histoDos->SetLineWidth(3);
  histoTres->SetLineWidth(3);

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  Ca0->SetBottomMargin(0.4);
  histoTres->SetLabelSize(0.03);
  histoTres->GetYaxis()->SetTitle("RPC Clusters x ClusterSize /1sec");
  histoTres->GetXaxis()->SetTitle("Time (sec)");
//  histoTres->SetMaximum(3000);
  histoTres->Draw("");
  histoTres->GetXaxis()->LabelsOption("v");

  histoUno->SetLabelSize(0.03);
  histoUno->Draw("same");
  histoUno->GetXaxis()->LabelsOption("v");
 
  histoDos->SetLabelSize(0.03);
  histoDos->Draw("same");
  histoDos->GetXaxis()->LabelsOption("v");

  TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
  leg->AddEntry(histoUno,"RB","l");
  leg->AddEntry(histoDos,"RE+","l");
  leg->AddEntry(histoTres,"RE-","l");
  leg->Draw("same");


  
  Ca0->SaveAs((name+".png").c_str());
 
}
