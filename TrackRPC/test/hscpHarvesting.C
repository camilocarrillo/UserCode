#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void hscpHarvesting(){
  gStyle->SetOptStat(0);
  
  TFile * theFile1 = new TFile("totalmerge.root");
//  TFile * theFile1 = new TFile("/tmp/carrillo/hscpkktau300.root");
//  TFile * theFile1 = new TFile("/tmp/carrillo/hscpstaus247.root");

  TFile * theFileOut = new TFile("hscpkktau300Harvesting.root","RECREATE");

  TH1F * statistics = (TH1F*) (theFile1->Get("statistics"));

  TH1F * mass = (TH1F*) (theFile1->Get("mass"));

  TH1F * expectedbeta = (TH1F*) (theFile1->Get("BetaExpected"));
  TH1F * observedbeta = (TH1F*) (theFile1->Get("BetaObserved"));
  
  TH1F * expectedeta = (TH1F*) (theFile1->Get("EtaExpected"));
  TH1F * observedeta = (TH1F*) (theFile1->Get("EtaObserved"));

  TH1F * expectedphi = (TH1F*) (theFile1->Get("PhiExpected"));
  TH1F * observedphi = (TH1F*) (theFile1->Get("PhiObserved"));

  TH1F * expectedp = (TH1F*) (theFile1->Get("PExpected"));
  TH1F * observedp = (TH1F*) (theFile1->Get("PObserved"));

  TH1F * efficiencyeta = new TH1F("EtaEff","Eta Efficiency",100,-2.5,2.5);		 
  TH1F * efficiencyphi = new TH1F("PhiEff","Phi Efficiency",100,-3.1415926,3.1415926); 
  TH1F * efficiencybeta = new TH1F("BetaEff","Beta Efficiency",100,0,1);                
  TH1F * efficiencyp = new TH1F("PEfficiency","P Efficiency",100,0,1500);

  TH2F * residualbetaVsEta = (TH2F*) (theFile1->Get("ResidualBetaVsEta"));
  
  statistics->GetXaxis()->SetBinLabel(1,"Events");
  statistics->GetXaxis()->SetBinLabel(2,"Events with HSCP in MC");
  statistics->GetXaxis()->SetBinLabel(3,"Events with HSCP in Mu/RPC");
    
  for(int k=1;k<=100;k++){
    float effeta = 0;
    float erreta = 0;
    if(expectedeta->GetBinContent(k)!=0){
      effeta = observedeta->GetBinContent(k)/expectedeta->GetBinContent(k);
      erreta = sqrt(effeta*(1-effeta)/expectedeta->GetBinContent(k));
    }
    efficiencyeta->SetBinContent(k,effeta);
    efficiencyeta->SetBinError(k,erreta);
    
    float effphi = 0;
    float errphi = 0;
    if(expectedphi->GetBinContent(k)!=0){
      effphi = observedphi->GetBinContent(k)/expectedphi->GetBinContent(k);
      errphi = sqrt(effphi*(1-effphi)/expectedphi->GetBinContent(k));
    }
    efficiencyphi->SetBinContent(k,effphi);
    efficiencyphi->SetBinError(k,errphi);

    float effbeta = 0;
    float errbeta = 0;
    if(expectedbeta->GetBinContent(k)!=0){
      effbeta = observedbeta->GetBinContent(k)/expectedbeta->GetBinContent(k);
      errbeta = sqrt(effbeta*(1-effbeta)/expectedbeta->GetBinContent(k));
    }
    efficiencybeta->SetBinContent(k,effbeta);
    efficiencybeta->SetBinError(k,errbeta);

    float effp = 0;
    float errp = 0;
    if(expectedp->GetBinContent(k)!=0){
      effp = observedp->GetBinContent(k)/expectedp->GetBinContent(k);
      errp = sqrt(effp*(1-effp)/expectedp->GetBinContent(k));
    }
    efficiencyp->SetBinContent(k,effp);
    efficiencyp->SetBinError(k,errp);
    
  }
  
  const int n = 50;
  
  float x[n];
  float y[n];
  float ex[n];
  float ey[n];
  
  float step = 5./float(n);

  for(int i=0;i<50;i++){
    float mean = residualbetaVsEta->ProjectionY("_py",i,i+1)->GetMean();
    float error  = residualbetaVsEta->ProjectionY("_py",i,i+1)->GetRMS();
    std::cout<<"mean="<<mean<<" rms="<<error<<std::endl;
    
    x[i]=(i+1)*step-2.5;
    ex[i]=step*0.5;
    y[i]=mean;
    ey[i]=error;
  }
  
  TCanvas * Ca5;

  Ca5 = new TCanvas("Ca5","etaVsresolution",800,600);

  TGraphErrors * plot1 = new TGraphErrors(n,x,y,ex,ey);
  TGraph * plot2 = new TGraphErrors(n,x,ey);

  plot1->SetMarkerColor(1);
  plot1->SetMarkerStyle(20);
  plot1->SetMarkerSize(0.5);
  plot1->GetXaxis()->SetTitle("Eta");
  plot1->GetYaxis()->SetTitle("Mean Beta Distribution (Error Bars RMS)");
  plot1->Draw("AP");
  std::string labeltoSave = "etaVsresolution.png";
  Ca5->SaveAs(labeltoSave.c_str());
  Ca5->Clear();
  
  plot2->SetMarkerColor(1);
  plot2->SetMarkerStyle(20);
  plot2->SetMarkerSize(0.5);
  plot2->GetXaxis()->SetTitle("Eta");
  plot2->GetYaxis()->SetTitle("RMS in beta");
  plot2->Draw("AP");
  std::string labeltoSave = "etaVsrms.png";
  Ca5->SaveAs(labeltoSave.c_str());
  Ca5->Clear();
  
  statistics->Write();
  mass->Write();
  
  efficiencyeta->Write();
  efficiencyphi->Write();
  efficiencybeta->Write();
  efficiencyp->Write();

  expectedeta->Write();
  expectedphi->Write();
  expectedbeta->Write();  
  expectedp->Write();

  observedeta->Write();
  observedphi->Write();
  observedbeta->Write();
  observedp->Write();

  TH1F * residualeta = (TH1F*) (theFile1->Get("ResidualEta"));
  TH1F * residualphi = (TH1F*) (theFile1->Get("ResidualPhi"));
  TH1F * residualbeta = (TH1F*) (theFile1->Get("ResidualBeta"));
  TH1F * residualp = (TH1F*) (theFile1->Get("ResidualP"));

  residualeta->Write();
  residualphi->Write();
  residualbeta->Write();
  residualp->Write();

  residualbetaVsEta->Write();

  theFileOut->Write();
  theFileOut->Close();
    
}
