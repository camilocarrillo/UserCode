#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TLegend"

void setHisto(TH1F * tof, string title,string name,bool barrel){
  tof->GetXaxis()->SetTitle(name.c_str());
  if(barrel){
    tof->GetXaxis()->SetLabelSize(0.05);
    tof->GetXaxis()->SetTitleSize(0.05);
  }else{
    tof->GetXaxis()->SetLabelSize(0.065);
    tof->GetXaxis()->SetTitleSize(0.065);
  }
  tof->SetLineWidth(3);
  tof->Fit("gaus","Q" ,"C" ,15,40);

  float sigma = tof->GetFunction("gaus")->GetParameter(2);
  stringstream legend;
  TLegend *leg = new TLegend(0.65,0.93,0.89,0.7);
  legend.str("");
  if(sigma<1) legend<<"#sigma="<<setprecision(2)<<sigma<<"ns";
  else        legend<<"#sigma="<<setprecision(3)<<sigma<<"ns";

  tof->GetFunction("gaus")->SetLineWidth(3);
  leg->AddEntry(tof->GetFunction("gaus"),legend.str().c_str(),"l");  
  if(barrel)  leg->SetTextSize(0.05);
  else leg->SetTextSize(0.08);
 
  float mu = tof->GetFunction("gaus")->GetParameter(1);
  legend.str("");
  if(mu<1) legend<<"#mu="<<setprecision(2)<<mu<<"ns";
  else        legend<<"#mu="<<setprecision(3)<<mu<<"ns";
  leg->AddEntry(tof->GetFunction("gaus"),legend.str().c_str(),"l");  
  if(barrel)  leg->SetTextSize(0.05);
  else leg->SetTextSize(0.08);
  
  tof->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);
}

void allStations(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  cout<<"getting the file"<<endl;

  TFile * theFile = new TFile("GDetector_ToF.root");  

  //All Tof
  cout<<"getting the histo"<<endl;

  TCanvas * Ca0 = new TCanvas("Ca0","ToF",1200,800);  Ca0->Divide(2,2);
  
  string name,title;
  name = "GDetector ToF Station 1 Ring 1(ns)"; title = "St1R1";  TH1F * St1R1 = (TH1F*) (theFile->Get(title.c_str())); Ca0_1->cd(); setHisto(St1R1,title,name,true); 
  name = "GDetector ToF Station 2 Ring 1(ns)"; title = "St2R1";  TH1F * St2R1 = (TH1F*) (theFile->Get(title.c_str())); Ca0_2->cd(); setHisto(St2R1,title,name,true); 
  name = "GDetector ToF Station 3 Ring 1(ns)"; title = "St3R1";  TH1F * St3R1 = (TH1F*) (theFile->Get(title.c_str())); Ca0_3->cd(); setHisto(St3R1,title,name,true); 
  name = "GDetector ToF Station 4 Ring 1(ns)"; title = "St4R1";  TH1F * St4R1 = (TH1F*) (theFile->Get(title.c_str())); Ca0_4->cd(); setHisto(St4R1,title,name,true); 
 
  Ca0->SaveAs("ToF.png"); 
  //  exit(0);
  
}
