#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void hscpHarvesting(){
  gStyle->SetOptStat(0);
  
  TFile * theFile1 = new TFile("hscpftheory12345.root");
  TFile * theFileOut = new TFile("sechscpftheory12345.root","RECREATE");

//  TFile * theFile1 = new TFile("/tmp/carrillo/PlotsStau156.root");
//  TFile * theFileOut = new TFile("hscpStau156harvesting.root","RECREATE");

  TH1F * statistics = (TH1F*) (theFile1->Get("statistics"));

  TH1F * mass = (TH1F*) (theFile1->Get("mass"));


  TH1F * expectedbeta = (TH1F*) (theFile1->Get("BetaExpected"));
  TH1F * observedbeta = (TH1F*) (theFile1->Get("BetaObserved"));
  TH1F * trackobservedbeta = (TH1F*) (theFile1->Get("trackBetaObserved"));
  
  TH1F * expectedeta = (TH1F*) (theFile1->Get("EtaExpected"));
  TH1F * observedeta = (TH1F*) (theFile1->Get("EtaObserved"));
  TH1F * trackobservedeta = (TH1F*) (theFile1->Get("trackEtaObserved"));

  TH1F * expectedphi = (TH1F*) (theFile1->Get("PhiExpected"));
  TH1F * observedphi = (TH1F*) (theFile1->Get("PhiObserved"));
  TH1F * trackobservedphi = (TH1F*) (theFile1->Get("trackPhiObserved"));

  TH1F * expectedp = (TH1F*) (theFile1->Get("PExpected"));
  TH1F * observedp = (TH1F*) (theFile1->Get("PObserved"));
  TH1F * trackobservedp = (TH1F*) (theFile1->Get("trackPObserved"));

  TH1F * efficiencyeta = new TH1F("EtaEff","Eta Efficiency HSCP",100,-2.5,2.5);		 
  TH1F * efficiencyphi = new TH1F("PhiEff","Phi Efficiency HSCP",100,-3.1415926,3.1415926); 
  TH1F * efficiencybeta = new TH1F("BetaEff","Beta Efficiency HSCP",100,0,1);                
  TH1F * efficiencyp = new TH1F("PEfficiency","P Efficiency HSCP",100,0,1500);

  TH1F * trackefficiencyeta = new TH1F("trackEtaEff","Eta Efficiency Tracks",100,-2.5,2.5);		 
  TH1F * trackefficiencyphi = new TH1F("trackPhiEff","Phi Efficiency Tracks",100,-3.1415926,3.1415926); 
  TH1F * trackefficiencybeta = new TH1F("trackBetaEff","Beta Efficiency Tracks",100,0,1);                
  TH1F * trackefficiencyp = new TH1F("trackPEfficiency","P Efficiency Tracks",100,0,1500);

  TH2F * residualbetaVsEta = (TH2F*) (theFile1->Get("ResidualBetaVsEta"));
  
  statistics->GetXaxis()->SetBinLabel(1,"Events");
  statistics->GetXaxis()->SetBinLabel(2,"Events with HSCP in MC");
  statistics->GetXaxis()->SetBinLabel(3,"Events with HSCP in Mu/RPC");
    
  for(int k=1;k<=100;k++){
    //hscp part
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
    
    //track part
    float trackeffeta = 0;
    float erreta = 0;
    if(expectedeta->GetBinContent(k)!=0){
      trackeffeta = trackobservedeta->GetBinContent(k)/expectedeta->GetBinContent(k);
      erreta = sqrt(trackeffeta*(1-trackeffeta)/expectedeta->GetBinContent(k));
    }
    trackefficiencyeta->SetBinContent(k,trackeffeta);
    trackefficiencyeta->SetBinError(k,erreta);
    
    float trackeffphi = 0;
    float errphi = 0;
    if(expectedphi->GetBinContent(k)!=0){
      trackeffphi = trackobservedphi->GetBinContent(k)/expectedphi->GetBinContent(k);
      errphi = sqrt(trackeffphi*(1-trackeffphi)/expectedphi->GetBinContent(k));
    }
    trackefficiencyphi->SetBinContent(k,trackeffphi);
    trackefficiencyphi->SetBinError(k,errphi);

    float trackeffbeta = 0;
    float errbeta = 0;
    if(expectedbeta->GetBinContent(k)!=0){
      trackeffbeta = trackobservedbeta->GetBinContent(k)/expectedbeta->GetBinContent(k);
      errbeta = sqrt(trackeffbeta*(1-trackeffbeta)/expectedbeta->GetBinContent(k));
    }
    trackefficiencybeta->SetBinContent(k,trackeffbeta);
    trackefficiencybeta->SetBinError(k,errbeta);

    float trackeffp = 0;
    float errp = 0;
    if(expectedp->GetBinContent(k)!=0){
      trackeffp = trackobservedp->GetBinContent(k)/expectedp->GetBinContent(k);
      errp = sqrt(trackeffp*(1-trackeffp)/expectedp->GetBinContent(k));
    }
    trackefficiencyp->SetBinContent(k,trackeffp);
    trackefficiencyp->SetBinError(k,errp);
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

  std::string command = "mkdir reco";
  system(command.c_str());
  
  mass->GetXaxis()->SetTitle("mass(GeV)");
  mass->Draw();
  mass->Write();
  Ca5->SaveAs("reco/mass.png");
  Ca5->Clear();


  //eta stuff
  expectedeta->SetFillColor(1);
  expectedeta->SetXTitle("#eta");
  expectedeta->SetTitle("Distribution in eta");
  expectedeta->Draw("");
  trackobservedeta->SetFillColor(5);
  trackobservedeta->Draw("same");
  observedeta->SetFillColor(4);
  observedeta->Draw("same");
  TLegend *leg = new TLegend(0.6,1.0,1.0,0.7);
  std::stringstream legend;
  legend<<"Gen Particle 100%";
  leg->AddEntry(expectedeta,(legend.str()).c_str(),"f");
  legend.str("");
  legend<<"Match Muon "<<(trackobservedeta->Integral()/expectedeta->Integral())*100<<"%";
  leg->AddEntry(trackobservedeta,(legend.str()).c_str(),"f");
  legend.str("");
  legend<<"HSCP "<<(observedeta->Integral()/expectedeta->Integral())*100<<"%"<<" Muon "<<(observedeta->Integral()/trackobservedeta->Integral())*100<<"%";
  leg->AddEntry(observedeta,(legend.str()).c_str(),"f");
  leg->Draw("same");
  leg->SetTextFont(62);
  Ca5->SaveAs("reco/eta.png");
  Ca5->Clear();
  expectedeta->Write();
  observedeta->Write();
  trackobservedeta->Write();
  efficiencyeta->Draw("");
  efficiencyeta->SetXTitle("#eta");
  Ca5->SaveAs("reco/effeta.png");
  Ca5->Clear();
  trackefficiencyeta->Draw("");
  trackefficiencyeta->SetXTitle("#eta");
  Ca5->SaveAs("reco/trackeffeta.png");
  Ca5->Clear();
  
    
  //phi stuff
  expectedphi->SetFillColor(1);
  expectedphi->SetXTitle("#phi");
  expectedphi->SetTitle("Distribution in phi");
  expectedphi->SetMinimum(0);
  expectedphi->Draw("");
  trackobservedphi->SetFillColor(5);
  trackobservedphi->Draw("same");
  observedphi->SetFillColor(4);
  observedphi->Draw("same");
  leg->Draw("same");
  Ca5->SaveAs("reco/phi.png");
  Ca5->Clear();
  expectedphi->Write();
  observedphi->Write();
  trackobservedphi->Write();
  efficiencyphi->Draw("");
  efficiencyphi->SetXTitle("#phi");
  Ca5->SaveAs("reco/effphi.png");
  Ca5->Clear();
  trackefficiencyphi->Draw("");
  trackefficiencyphi->SetXTitle("#phi");
  Ca5->SaveAs("reco/trackeffphi.png");
  Ca5->Clear();
  
  //beta stuff
  expectedbeta->SetFillColor(1);
  expectedbeta->SetXTitle("#beta(c)");
  expectedbeta->SetTitle("Distribution in beta");
  expectedbeta->SetMinimum(0);
  expectedbeta->Draw("");
  trackobservedbeta->SetFillColor(5);
  trackobservedbeta->Draw("same");
  observedbeta->SetFillColor(4);
  observedbeta->Draw("same");
  TLegend *leg2 = new TLegend(0.2,0.85,0.6,0.65);
  std::stringstream legend;
  legend<<"Gen Particle 100%";
  leg2->AddEntry(expectedeta,(legend.str()).c_str(),"f");
  legend.str("");
  legend<<"Match Muon "<<(trackobservedeta->Integral()/expectedeta->Integral())*100<<"%";
  leg2->AddEntry(trackobservedeta,(legend.str()).c_str(),"f");
  legend.str("");
  legend<<"HSCP "<<(observedeta->Integral()/expectedeta->Integral())*100<<"%"<<" Muon "<<(observedeta->Integral()/trackobservedeta->Integral())*100<<"%";
  leg2->AddEntry(observedeta,(legend.str()).c_str(),"f");
  leg2->Draw("same");
  Ca5->SaveAs("reco/beta.png");
  Ca5->Clear();
  expectedbeta->Write();
  observedbeta->Write();
  trackobservedbeta->Write();
  efficiencybeta->Draw("");
  efficiencybeta->SetXTitle("#beta(c)");
  Ca5->SaveAs("reco/effbeta.png");
  Ca5->Clear();
  trackefficiencybeta->Draw("");
  trackefficiencybeta->SetXTitle("#beta(c)");
  Ca5->SaveAs("reco/trackeffbeta.png");
  Ca5->Clear();


  //P stuff
  expectedp->SetFillColor(1);
  expectedp->SetXTitle("p(GeV/c)");
  expectedp->SetTitle("Distribution in p");
  expectedp->SetMinimum(0);
  expectedp->Draw("");
  trackobservedp->SetFillColor(5);
  trackobservedp->Draw("same");
  observedp->SetFillColor(4);
  observedp->Draw("same");
  leg->Draw("same");
  Ca5->SaveAs("reco/p.png");
  Ca5->Clear();
  expectedp->Write();
  observedp->Write();
  trackobservedp->Write();
  efficiencyp->Draw("");
  efficiencyp->SetXTitle("p(GeV/c)");
  Ca5->SaveAs("reco/effp.png");
  Ca5->Clear();
  trackefficiencyp->Draw("");
  trackefficiencyp->SetXTitle("p(GeV/c)");
  Ca5->SaveAs("reco/trackeffp.png");
  Ca5->Clear();
  
  //Saving efficiencies
  efficiencyeta->Write();
  efficiencyphi->Write();
  efficiencybeta->Write();
  efficiencyp->Write();

  trackefficiencyeta->Write();
  trackefficiencyphi->Write();
  trackefficiencybeta->Write();
  trackefficiencyp->Write();

  TH1F * residualeta = (TH1F*) (theFile1->Get("ResidualEta"));
  TH1F * residualphi = (TH1F*) (theFile1->Get("ResidualPhi"));
  TH1F * residualbeta = (TH1F*) (theFile1->Get("ResidualBeta"));
  TH1F * residualp = (TH1F*) (theFile1->Get("ResidualP"));

  TH1F * trackresidualeta = (TH1F*) (theFile1->Get("trackResidualEta"));
  TH1F * trackresidualphi = (TH1F*) (theFile1->Get("trackResidualPhi"));
  TH1F * trackresidualbeta = (TH1F*) (theFile1->Get("trackResidualBeta"));
  TH1F * trackresidualp = (TH1F*) (theFile1->Get("trackResidualP"));


  residualeta->Draw();
  residualeta->SetXTitle("#Delta #eta");
  Ca5->SaveAs("reco/residualeta.png");
  Ca5->Clear(); 
  residualeta->Write();

  residualphi->Draw();
  residualphi->SetXTitle("#Delta #phi");
  Ca5->SaveAs("reco/residualphi.png");
  Ca5->Clear();
  residualphi->Write();

  residualbeta->Draw();
  residualbeta->SetXTitle("#Delta #beta (c)");
  Ca5->SaveAs("reco/residualbeta.png");
  Ca5->Clear();
  residualbeta->Write();

  residualp->Draw();
  residualp->SetXTitle("#Delta p (GeV/c)");
  Ca5->SaveAs("reco/residualp.png");
  Ca5->Clear();
  residualp->Write();

  residualbetaVsEta->Write();
  residualbetaVsEta->Draw();
  Ca5->SaveAs("reco/residualbetaVsEta.png");
  Ca5->Clear();

  trackresidualeta->Draw();
  trackresidualeta->SetXTitle("#Delta #eta");
  Ca5->SaveAs("reco/trackresidualeta.png");
  Ca5->Clear(); 
  trackresidualeta->Write();

  trackresidualphi->Draw();
  trackresidualphi->SetXTitle("#Delta #phi");
  Ca5->SaveAs("reco/trackresidualphi.png");
  Ca5->Clear();
  trackresidualphi->Write();

  trackresidualp->Draw();
  trackresidualp->SetXTitle("#Delta p (GeV/c)");
  Ca5->SaveAs("reco/trackresidualp.png");
  Ca5->Clear();
  trackresidualp->Write();

  statistics->GetXaxis()->LabelsOption("v");
  statistics->GetXaxis()->SetLabelSize(0.035);
  statistics->Draw();
  Ca5->SetBottomMargin(0.35);
  statistics->Write();
  Ca5->SaveAs("reco/statistics.png");
  Ca5->Clear();
  
  theFileOut->Write();
  theFileOut->Close();

  exit(0);
}
