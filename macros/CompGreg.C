#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void CompGreg(){
gROOT->Reset();

TFile * theFile1 = new TFile("re12.root");
TFile * theFile2 = new TFile("/tmp/carrillo/prodimages/119090/sec119090.root");

std::cout<<"Reading files"<<std::endl;
TH1F * thehisto1 = (TH1F*) (theFile1->Get("h_eff"));
TH1F * thehisto2 = (TH1F*) (theFile2->Get("GregDistroD1R2"));

thehisto1->SetMaximum(1);
thehisto2->SetMaximum(1);


std::cout<<"Creating Canvas"<<std::endl;
TCanvas *Ca1 = new TCanvas("Ca1","RE1_2",800,600);
std::cout<<"Drawing first"<<std::endl;
thehisto1->Draw("");

std::cout<<"Drawing second"<<std::endl;
thehisto2->SetMarkerColor(9);
thehisto2->SetLineColor(9);
thehisto2->Draw("same");

Ca1->SaveAs("ComparisonRE12.png");

}
