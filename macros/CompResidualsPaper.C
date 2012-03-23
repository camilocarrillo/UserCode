#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void CompResiduals(){
gROOT->Reset();
gStyle->SetOptStat(0);

TFile * theFile1 = new TFile("efficiency_raw/secefficiency_raw.root");
TFile * theFile2 = new TFile("efficiency_raw_ali/secefficiency_raw_ali.root");

std::cout<<"Reading files"<<std::endl;
//TH1F * thehisto2 = (TH1F*) (theFile1->Get("residualStation1Ring2_C"));
//TH1F * thehisto1 = (TH1F*) (theFile2->Get("residualStation1Ring2_C"));

TH1F * thehisto2 = (TH1F*) (theFile1->Get("residualRB2in"));
TH1F * thehisto1 = (TH1F*) (theFile2->Get("residualRB2in"));

//thehisto1->SetMaximum(1);
//thehisto2->SetMaximum(1);

std::cout<<"Creating Canvas"<<std::endl;
TCanvas *Ca1 = new TCanvas("Ca1","RB2in",800,600);
std::cout<<"Drawing first"<<std::endl;
thehisto1->Draw("");

std::cout<<"Drawing second"<<std::endl;
thehisto2->SetMarkerColor(9);
thehisto2->SetLineColor(9);
thehisto2->Draw("same");

 thehisto1->SetXTitle("residuals (cm)");
 thehisto2->SetXTitle("residuals (cm)");

 std::stringstream sta1;
 std::stringstream sta2;

 TLegend *leg = new TLegend(0.6,0.8,0.9,0.7);
 sta1<<"RMS="<<thehisto1->GetRMS()<<"cm";
 sta2<<"RMS="<<thehisto2->GetRMS()<<"cm";
 leg->AddEntry(thehisto1,"Without_Ali","l");
 leg->AddEntry(thehisto1,(sta1.str()).c_str(),"l");
 leg->AddEntry(thehisto2,"With_Ali","l");
 leg->AddEntry(thehisto2,(sta2.str()).c_str(),"l");
 leg->Draw("same");


Ca1->SaveAs("ComparisonResiduals.png");

}
