#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void getPng(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  cout<<"getting the file"<<endl;

  TFile * theFile = new TFile("cosmics.root");  

  cout<<"getting the histo"<<endl;
  TH1F * statistics	      = (TH1F*)  (theFile->Get("statistics"));
  TH1F * phidistro	      =	(TH1F*)  (theFile->Get("phidistro"));
  TH1F * etadistro	      =	(TH1F*)  (theFile->Get("etadistro"));
  TH1F * etadistroupleg       =	(TH1F*)  (theFile->Get("etadistroupleg"));
  TH1F * etadistrodownleg     =	(TH1F*)  (theFile->Get("etadistrodownleg"));
  TH1F * bxupleg	      =	(TH1F*)  (theFile->Get("bxupleg"));
  TH1F * bxdownleg	      =	(TH1F*)  (theFile->Get("bxdownleg"));
  TH1F * hitshisto	      =	(TH1F*)  (theFile->Get("hits"));
  TH1F * hitsupleghisto       =	(TH1F*)  (theFile->Get("hitsupleg"));
  TH1F * hitsdownleghisto     =	(TH1F*)  (theFile->Get("hitsdownleg"));
  TH1F * hitsupleghistoeta    =	(TH1F*)  (theFile->Get("hitsuplegeta"));
  TH1F * hitsdownleghistoeta  =	(TH1F*)  (theFile->Get("hitsdownlegeta"));
  TH2F * phiscatter	      =	(TH2F*)  (theFile->Get("phiscatter"));
  TH2F * etascatter	      =	(TH2F*)  (theFile->Get("etascatter"));
  TH2F * bxscatter	      =	(TH2F*)  (theFile->Get("bxscatter"));
  TH1F * muondistro	      =	(TH1F*)  (theFile->Get("muondistro"));
  TH1F * bxdiff               =	(TH1F*)  (theFile->Get("bxdiff"));
				      
  Ca0 = new TCanvas("Ca0","Ca0",800,600);
  Ca0->Clear();
  hitshisto->Draw();
  Ca0->SaveAs("hitshisto.png");Ca0->Clear();
  hitsupleghisto->Draw();
  hitsupleghistoeta->SetFillColor(2);
  hitsupleghistoeta->Draw("same");
  Ca0->SaveAs("hitsupleghisto.png");Ca0->Clear();
  hitsdownleghisto->Draw();
  hitsdownleghistoeta->SetFillColor(2);
  hitsdownleghistoeta->Draw("same");
  Ca0->SaveAs("hitsdownleghisto.png");Ca0->Clear();
  phidistro->Draw();
  Ca0->SaveAs("phidistro.png");Ca0->Clear();
  etadistro->Draw();
  Ca0->SaveAs("etadistro.png");Ca0->Clear();
  etadistroupleg->Draw();
  Ca0->SaveAs("etadistroupleg.png");Ca0->Clear();
  etadistrodownleg->Draw();
  Ca0->SaveAs("etadistrodownleg.png");Ca0->Clear();
  bxscatter->Draw();
  bxscatter->SetDrawOption("COLZ");
  Ca0->SaveAs("bxscatter.png");Ca0->Clear();
  phiscatter->Draw();
  //  phiscatter->SetDrawOption("COLZ");
  Ca0->SaveAs("phiscatter.png");Ca0->Clear();
  etascatter->Draw();
  etascatter->SetDrawOption("COLZ");
  Ca0->SaveAs("etascatter.png");Ca0->Clear();
  Ca0->SetLogy();
  bxupleg->Draw();
  Ca0->SaveAs("bxupleg.png");Ca0->Clear();
  Ca0->SetLogy();
  bxdownleg->Draw();
  Ca0->SaveAs("bxdownleg.png");Ca0->Clear();
  Ca0->SetLogy();
  muondistro->Draw();
  Ca0->SaveAs("muondistro.png");Ca0->Clear();
  Ca0->SetLogy();
  statistics->Draw();
  Ca0->SaveAs("statistics.png");Ca0->Clear();
  Ca0->SetLogy();
  bxdiff->Draw();
  Ca0->SaveAs("bxdiff.png");Ca0->Clear();


  exit(0);
  
}
