{
gROOT->Reset();
#include "Riostream.h"

TFile * theFile1 = new TFile("merge43553witheff.root");
TFile * theFile2 = new TFile("EffProfile.root");
TFile * theFileOut = new TFile("WheelOne.root","RECREATE");

std::cout<<"Reading files"<<std::endl;
TH1F * thehisto1 = (TH1F*) (theFile1->Get("GlobExpectedWheel_1"));
TH1F * thehisto2 = (TH1F*) (theFile2->Get("ExpW+1"));
TH1F * theOutput1 = new TH1F("TheOutPut1","Wheel 1",120,0.5,120.5);
TH1F * theOutput2 = new TH1F("TheOutPut2","Wheel 1",120,0.5,120.5);

int merged0=0;

for(int i=0;i<=100;i++){
  bool match=false;
  const char * label1 = thehisto1->GetXaxis()->GetBinLabel(i);
  
  for(int j=0;j<=100;j++){
    const char * label2 = thehisto2->GetXaxis()->GetBinLabel(j);
    bool samechar=true;
    for(k=1;k<=17;k++){
      if(label1[k]!=label2[k])samechar=false;
    }

    if(samechar && (thehisto1->GetBinContent(i)!=0 && thehisto2->GetBinContent(j)!= 0)){
      printf("%s \n",label1);
      merged0++;
      
      float temp1 = thehisto1->GetBinContent(i);
      theOutput1->SetBinContent(merged0,temp1);
      theOutput1->SetBinError(merged0,thehisto1->GetBinError(i));
      theOutput1->GetXaxis()->SetBinLabel(merged0,thehisto1->GetXaxis()->GetBinLabel(i));
      theOutput1->GetXaxis()->LabelsOption("v");

      float temp2 = thehisto2->GetBinContent(j);
      theOutput2->SetBinContent(merged0,temp2);
      theOutput2->SetBinError(merged0,thehisto2->GetBinError(j));
      theOutput2->GetXaxis()->SetBinLabel(merged0,thehisto2->GetXaxis()->GetBinLabel(j));
      theOutput2->GetXaxis()->LabelsOption("v");
    }
  }
}

std::cout<<"Creating Canvas"<<std::endl;
TCanvas *Ca1 = new TCanvas("Ca1","Wheel_1",800,600);
std::cout<<"Drawing first"<<std::endl;
theOutput1->Draw("");

std::cout<<"Drawing second"<<std::endl;
theOutput2->SetMarkerColor(9);
theOutput2->SetLineColor(9);
theOutput2->Draw("same");

}

//Open root y dentro del promt de root simplemente 
//root [0] .x macroProdPlotsXYeY.C
