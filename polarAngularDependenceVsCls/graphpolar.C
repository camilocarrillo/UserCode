//Create and draw a polar graph
//Author: Olivier Couet

#include <iostream.h>
   
void graphpolar()
{
   // Illustrates how to use TGraphPolar

  TCanvas * CPol = new TCanvas("CPol","Cluster Size Distribution for different Angles",600,600);

  float pi = 3.14159265;
    
  Double_t xmin=0.;
  Double_t xmax=pi;
  
  TFile *_file0 = TFile::Open("eff70195_70402_70674.root");

  TPaveText * pave;
  pave = new TPaveText(2,0.07,3,0.09);
  TText *t1=pave->AddText("Cluster Size 1");
  t1->SetTextColor(9);
  TText *t2=pave->AddText("Cluster Size 2");
  t2->SetTextColor(2);
  TText *t3=pave->AddText("Cluster Size 3");
  t3->SetTextColor(8);

  
  pave->SetFillColor(0);
  
  t1->SetTextSize(0.03);
  t2->SetTextSize(0.03);
  t3->SetTextSize(0.03);

    
  //TFile *_file0 = TFile::Open("eff70036.root");

  TH1F * AngClu1La1 =  (TH1F*)_file0->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/AngClu1La1");
  TH1F * AngClu2La1 =  (TH1F*)_file0->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/AngClu2La1");
  TH1F * AngClu3La1 =  (TH1F*)_file0->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/AngClu3La1");

  const int n = 50;

  Double_t x[n];
  Double_t y[n];
  Double_t x1[n];
  Double_t y1[n];
  Double_t x3[n];
  Double_t y3[n];

  for (Int_t ipt = 0; ipt < n; ipt++){
    x[ipt] = ipt*(xmax-xmin)/n;
    y[ipt] = AngClu1La1->GetBinContent(ipt)/AngClu1La1->Integral();
    cout<<x[ipt]<<" "<<y[ipt]<<endl;
  }
  
  TGraphPolar * grP = new TGraphPolar(n,x,y);
  grP->SetTitle("Angle of incidence");
  grP->SetLineColor(9);
  grP->SetLineWidth(0.3);
  grP->Draw("");
  
  for (Int_t ipt = 0; ipt < n; ipt++){
    x3[ipt] = ipt*(xmax-xmin)/n;
    y3[ipt] = AngClu3La1->GetBinContent(ipt)/AngClu3La1->Integral();
    cout<<x1[ipt]<<" "<<y1[ipt]<<endl;
  }
  
  TGraphPolar * grP3 = new TGraphPolar(n,x3,y3);
  grP3->SetLineColor(8);
  grP3->SetLineWidth(0.3);
  grP3->Draw("same");


  for (Int_t ipt = 0; ipt < n; ipt++){
    x1[ipt] = ipt*(xmax-xmin)/n;
    y1[ipt] = AngClu2La1->GetBinContent(ipt)/AngClu2La1->Integral();
    cout<<x1[ipt]<<" "<<y1[ipt]<<endl;
  }
  
  TGraphPolar * grP1 = new TGraphPolar(n,x1,y1);
  grP1->SetLineColor(2);
  grP1->SetLineWidth(0.3);
  grP1->Draw("same");
  
  // Update, otherwise GetPolargram returns 0
  CPol->Update();

  grP1->GetPolargram()->SetTextSize(0.03);
  grP1->GetPolargram()->SetTwoPi();
  grP1->GetPolargram()->SetToDegree();

  CPol->SaveAs("3Polar.png");
  
  TCanvas * Ca1 = new TCanvas("CartesianPlots","Cluster size distribution for different Angles",600,600);

  float pi = 3.14159265;
  TH1F * AngClu1La1Norm = new TH1F("AngClu1La1Norm","Normalized distribution angle of incidence for different cluster sizes",50,0.,pi);
  TH1F * AngClu2La1Norm = new TH1F("AngClu2La1Norm","Angle of incident Muon Cluster Size 2",50,0.,pi);
  TH1F * AngClu3La1Norm = new TH1F("AngClu3La1Norm","Angle of incident Muon Cluster Size 3",50,0.,pi);
  
  AngClu1La1Norm->GetXaxis()->SetTitle("radians");


  for (Int_t ipt = 0; ipt < n; ipt++){
    AngClu1La1Norm->SetBinContent(ipt,AngClu1La1->GetBinContent(ipt)/AngClu1La1->Integral());
    AngClu2La1Norm->SetBinContent(ipt,AngClu2La1->GetBinContent(ipt)/AngClu2La1->Integral());
    AngClu3La1Norm->SetBinContent(ipt,AngClu3La1->GetBinContent(ipt)/AngClu3La1->Integral());
  }

  gStyle->SetOptStat(0);


  Ca1->Clear();
  
  AngClu1La1Norm->SetFillColor(0);
  AngClu2La1Norm->SetFillColor(0);
  AngClu3La1Norm->SetFillColor(0);
  

  AngClu1La1Norm->SetMarkerColor(9);
  AngClu1La1Norm->SetLineColor(9);
  AngClu1La1Norm->Draw("");
  AngClu2La1Norm->SetMarkerColor(2);
  AngClu2La1Norm->SetLineColor(2);
  AngClu2La1Norm->Draw("same");
  AngClu3La1Norm->SetMarkerColor(8);
  AngClu3La1Norm->SetLineColor(8);
  AngClu3La1Norm->Draw("same");


  cout<<AngClu3La1Norm->Integral()<<" "<<AngClu2La1Norm->Integral()<<" "<<AngClu3La1Norm->Integral()<<endl;
  pave->Draw();
  
  Ca1->SaveAs("3Cartesian.png");

}
