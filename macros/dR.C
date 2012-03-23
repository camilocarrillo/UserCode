#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void dR(){
  gROOT->Reset();
  gStyle->SetOptStat(1);

  ifstream dataphi;
  ifstream dataeta;
  
  float etaRPC;
  float etaCSC;

  float phiRPC;
  float phiCSC;

  dataphi.open("phi.txt");
  dataeta.open("eta.txt");

  std::string name = "dR";

  float pi = 3.14159265;
  float dphi = 0;
  float deta = 0;

  TH1F * histo = new TH1F("histo",name.c_str(),1000,0,0.5);
  TH2F * histo2D = new TH2F("histo2D",name.c_str(),400,-0.2,0.2,400,-0.2,0.2);

  while(!dataphi.eof()){
    dataphi >>phiRPC>>phiCSC;
    dataeta >>etaRPC>>etaCSC;
    dphi = phiRPC-phiCSC;
    deta = etaRPC-etaCSC;
    histo->Fill(sqrt(dphi*dphi+deta*deta));
    histo2D->Fill(dphi,deta);
  }

  TFile * theFile = new TFile("dR.root","RECREATE");
  theFile->cd();

  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
 /* histo->SetLineWidth(3);
  histo->Draw();
  histo->SetMaximum(histo->GetMaximumStored());
  histo->GetXaxis()->SetTitle(name.c_str());*/

  gStyle->SetPalette(1);

  histo2D->GetXaxis()->SetTitle("dPhi");
  histo2D->GetYaxis()->SetTitle("dEta");
  histo2D->Draw();
  histo2D->SetDrawOption("color");
  histo2D->Write();
  Ca0->SaveAs((name+".png").c_str());
  theFile->Save();
  theFile->Close();
 
}
