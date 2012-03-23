#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void scatterPloteta(){
  gROOT->Reset();
  gStyle->SetOptStat(1);

  ifstream data;
  
  float valueX;
  float valueY;

  string name = "eta";
  data.open((name+".txt").c_str());
  
  TH2F * histo = new TH2F("histo",name.c_str(),1000,-2.4,2.4,100,-2.4,2.4); //eta
  TH1F * histo1D = new TH1F("histo1D",name.c_str(),1000,-2.4,2.4); //eta

//  float pi = 3.14159265;
//  TH2F * histo = new TH2F("histo",name.c_str(),1000,-1*pi,pi,1000,-1*pi,pi); //phi
//  TH1F * histo1D = new TH1F("histo1D",name.c_str(),1000,-1*pi,pi); //phi

  while(!data.eof()){
    data >>valueX>>valueY;
    cout<<valueX<<" "<<valueY<<endl;
    histo->Fill(valueX,valueY);
    histo1D->Fill(valueX-valueY);
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  histo->SetLineWidth(3);

  TFile * theFile = new TFile("eta.root","RECREATE");
  theFile->cd();

  histo->Draw();
  histo1D->DrawNormalized("same");
  histo->GetXaxis()->SetTitle(("RPC"+name).c_str());
  histo->GetYaxis()->SetTitle(("CSC"+name).c_str());
  Ca0->SaveAs((name+".png").c_str());

  histo1D->Write();
  histo->Write();

  theFile->Save();
  theFile->Close();

  
}
