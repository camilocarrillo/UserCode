#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void scatterPlot(){
  gROOT->Reset();
  gStyle->SetOptStat(1);

  ifstream data;
  
  float valueX;
  float valueY;

  string name = "phi";
  data.open((name+".txt").c_str());
  
//  TH2F * histo = new TH2F("histo",name.c_str(),100,-2.4,2.4,100,-2.4,2.4); //eta
  TH2F * histo = new TH2F("histo",name.c_str(),13,-0.5,12.5,100,0,100); 

  while(!data.eof()){
    data >>valueX>>valueY;
    cout<<valueX<<" "<<valueY<<endl;
    histo->Fill(valueX,valueY);
    histo1D->Fill(valueX-valueY);
  }
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);
  histo->SetLineWidth(3);
  histo->Draw();
  histo->GetXaxis()->SetTitle("fiducial cut (cm)");
  histo->GetYaxis()->SetTitle("efficiency(%)");
  Ca0->SaveAs((name+".png").c_str());

  TFile * theFile = new TFile("phi.root","RECREATE");
  theFile->cd();
  histo1D->Write();
  histo->Write();
  theFile->Save();
  theFile->Close();

  
}
