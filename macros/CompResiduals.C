#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void CompResiduals(){
gROOT->Reset();
gStyle->SetOptStat(0);

TFile * theFile1 = new TFile("/afs/cern.ch/user/c/carrillo/scratch0/PointProducer/RE12study/effRE12.root");
TFile * theFile2 = new TFile("/afs/cern.ch/user/c/carrillo/scratch0/PointProducer/RE12study/newGeo/effRE12.root");

std::cout<<"Reading files"<<std::endl;
TH1F * thehisto2 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/EndCap/GlobalResidualsClu1R2A"));
TH1F * thehisto1 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/EndCap/GlobalResidualsClu1R2A"));

//thehisto1->SetMaximum(1);
//thehisto2->SetMaximum(1);

std::cout<<"Creating Canvas"<<std::endl;
TCanvas *Ca1 = new TCanvas("Ca1","RE1_2",800,600);
std::cout<<"Drawing first"<<std::endl;
thehisto1->Draw("");

std::cout<<"Drawing second"<<std::endl;
thehisto2->SetMarkerColor(9);
thehisto2->SetLineColor(9);
thehisto2->Draw("same");

 std::stringstream sta1;
 std::stringstream sta2;

 TLegend *leg = new TLegend(0.6,0.8,0.9,0.7);
 sta1<<"Mean="<<thehisto1->GetMean()<<" Integral="<<thehisto1->Integral();
 sta2<<"Mean="<<thehisto2->GetMean()<<" Integral="<<thehisto2->Integral();
 leg->AddEntry(thehisto1,"New Geometry","l");
 leg->AddEntry(thehisto1,(sta1.str()).c_str(),"l");
 leg->AddEntry(thehisto2,"Old Geometry","l");
 leg->AddEntry(thehisto2,(sta2.str()).c_str(),"l");
 leg->Draw("same");


Ca1->SaveAs("ComparisonResiduals.png");

}
