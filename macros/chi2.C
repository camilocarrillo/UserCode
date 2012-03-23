#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void chi2(){
  TFile * theFile[20];
  
  theFile[0] = new TFile("histos0.root");
  theFile[1] = new TFile("histos1.root");
  theFile[2] = new TFile("histos2.root");
  theFile[3] = new TFile("histos3.root");
  theFile[4] = new TFile("histos4.root");
  theFile[5] = new TFile("histos5.root");
  theFile[6] = new TFile("histos6.root");
  theFile[7] = new TFile("histos7.root");
  theFile[8] = new TFile("histos8.root");
  theFile[9] = new TFile("histos9.root");
  theFile[10] = new TFile("histos10.root");
  theFile[11] = new TFile("histos11.root");
  theFile[12] = new TFile("histos12.root");
  theFile[13] = new TFile("histos13.root");
  theFile[14] = new TFile("histos14.root");
  theFile[15] = new TFile("histos15.root");
  theFile[16] = new TFile("histos16.root");
  theFile[17] = new TFile("histos17.root");
  theFile[18] = new TFile("histos18.root");
  theFile[19] = new TFile("histos19.root");

  float shift=0;
  float shifts[20];
  float chi2b[20];
  float chi2e[20];

  	
	
  for(int i=0;i<20;i++){
    TH1F * chi2 = (TH1F*) (theFile[i]->Get("Barrel-CHI2"));
    cout<<shift<<" "<<chi2->GetMean()<<endl;
    shifts[i]=shift;
    chi2b[i]=chi2->GetMean();
    shift = shift+0.01;
  }

  TGraphErrors * scan1 = new TGraph(20,shifts,chi2b);
	
  shift =0;
  for(int i=0;i<20;i++){
    TH1F * chi2 = (TH1F*) (theFile[i]->Get("Endcap-CHI2"));
    cout<<shift<<" "<<chi2->GetMean()<<endl;
    shifts[i]=shift;
    chi2e[i]=chi2->GetMean();
    shift = shift+0.01;
  }

  TGraphErrors * scan2 = new TGraph(20,shifts,chi2e);

  scan2->SetMarkerStyle(22);
  scan2->SetMarkerSize(1.0);
  
  scan1->SetMarkerStyle(20);
  scan1->SetMarkerSize(1.0);

  scan1->SetMarkerColor(22);

  TCanvas *c1 = new TCanvas("c1","gerrors2",200,10,700,500);
  //c1->SetFillColor(42);
  c1->SetGrid();

  // draw a frame to define the range
  TH1F *hr = c1->DrawFrame(0,0,0.2,10);
  hr->SetXTitle("shift");
  hr->SetYTitle("chi2");
  //c1->GetFrame()->SetFillColor(21);
  //c1->GetFrame()->SetBorderSize(12);

  scan2->Draw("P");
  scan1->Draw("P");
  
  TLegend *leg = new TLegend(0.6,0.45,0.9,0.3);
  leg->AddEntry(scan2,"endcap","p");
  leg->AddEntry(scan1,"barrel","p");
 
  leg->Draw("same");

  c1->SaveAs("chi2.png");




}
