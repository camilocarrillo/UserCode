{
gROOT->Reset();
#include "Riostream.h"

ifstream in;
in.open("alleff.txt");

Float_t x,y,ey;
Int_t nlines = 0;
TFile * theFile = new TFile("merge43553.root");
TFile * theFileOut = new TFile("merge43553witheff.root","RECREATE");

TH1F * GlobOcupancyWheel_m2 = theFile->Get("GlobOcupancyWheel_-2");
TH1F * GlobExpectedWheel_m2 = theFile->Get("GlobExpectedWheel_-2");
TH1F * GlobEfficiencyWheel_m2 = theFile->Get("GlobEfficiencyWheel_-2");

int mergedm2=0;

for(int i=0;i<=240;i++){
  float o = GlobOcupancyWheel_m2->GetBinContent(i);
  float p = GlobExpectedWheel_m2->GetBinContent(i);
  
  if(p!=0/*&&( GlobOcupancyWheel_0->GetBinLabel(i) == GlobExpectedWheel_0->GetBinLabel(i))*/){
    
    float ef = float(o)/float(p); 
    float er = sqrt(ef*(1.-ef)/float(p));
    
    GlobEfficiencyWheel_m2->SetBinContent(i,ef*100.);
    GlobEfficiencyWheel_m2->SetBinError(i,er*100.);
    
    std::cout<<o<<" "<<p<<std::endl;
    mergedm2++;
  }
}

TH1F * GlobOcupancyWheel_m1 = theFile->Get("GlobOcupancyWheel_-1");
TH1F * GlobExpectedWheel_m1 = theFile->Get("GlobExpectedWheel_-1");
TH1F * GlobEfficiencyWheel_m1 = theFile->Get("GlobEfficiencyWheel_-1");

int mergedm1=0;

for(int i=0;i<=240;i++){
  float o = GlobOcupancyWheel_m1->GetBinContent(i);
  float p = GlobExpectedWheel_m1->GetBinContent(i);
  
  if(p!=0/*&&( GlobOcupancyWheel_0->GetBinLabel(i) == GlobExpectedWheel_0->GetBinLabel(i))*/){
    
    float ef = float(o)/float(p); 
    float er = sqrt(ef*(1.-ef)/float(p));
    
    GlobEfficiencyWheel_m1->SetBinContent(i,ef*100.);
    GlobEfficiencyWheel_m1->SetBinError(i,er*100.);
    
    std::cout<<o<<" "<<p<<std::endl;
    mergedm1++;
  }
}

TH1F * GlobOcupancyWheel_0 = theFile->Get("GlobOcupancyWheel_0");
TH1F * GlobExpectedWheel_0 = theFile->Get("GlobExpectedWheel_0");
TH1F * GlobEfficiencyWheel_0 = theFile->Get("GlobEfficiencyWheel_0");

int merged0=0;

for(int i=0;i<=240;i++){
  float o = GlobOcupancyWheel_0->GetBinContent(i);
  float p = GlobExpectedWheel_0->GetBinContent(i);
  
  if(p!=0/*&&( GlobOcupancyWheel_0->GetBinLabel(i) == GlobExpectedWheel_0->GetBinLabel(i))*/){
    
    float ef = float(o)/float(p); 
    float er = sqrt(ef*(1.-ef)/float(p));
    
    GlobEfficiencyWheel_0->SetBinContent(i,ef*100.);
    GlobEfficiencyWheel_0->SetBinError(i,er*100.);
    
    std::cout<<o<<" "<<p<<std::endl;
      merged0++;
  }
}

TH1F * GlobOcupancyWheel_1 = theFile->Get("GlobOcupancyWheel_1");
TH1F * GlobExpectedWheel_1 = theFile->Get("GlobExpectedWheel_1");
TH1F * GlobEfficiencyWheel_1 = theFile->Get("GlobEfficiencyWheel_1");

int merged1=0;

for(int i=0;i<=240;i++){
  float o = GlobOcupancyWheel_1->GetBinContent(i);
  float p = GlobExpectedWheel_1->GetBinContent(i);
  
  if(p!=0/*&&(GlobOcupancyWheel_1->GetBinLabel(i) == GlobExpectedWheel_1->GetBinLabel(i))*/){
    
    float ef = float(o)/float(p); 
    float er = sqrt(ef*(1.-ef)/float(p));
    
    GlobEfficiencyWheel_1->SetBinContent(i,ef*100.);
    GlobEfficiencyWheel_1->SetBinError(i,er*100.);
    
    std::cout<<o<<" "<<p<<std::endl;
    merged1++;
  }
  
  
}

TH1F * GlobOcupancyWheel_2 = theFile->Get("GlobOcupancyWheel_2");
TH1F * GlobExpectedWheel_2 = theFile->Get("GlobExpectedWheel_2");
TH1F * GlobEfficiencyWheel_2 = theFile->Get("GlobEfficiencyWheel_2");

int merged2=0;

for(int i=0;i<=240;i++){
  float o = GlobOcupancyWheel_2->GetBinContent(i);
  float p = GlobExpectedWheel_2->GetBinContent(i);
  
  if(p!=0/*&&(GlobOcupancyWheel_1->GetBinLabel(i) == GlobExpectedWheel_1->GetBinLabel(i))*/){
    
    float ef = float(o)/float(p); 
    float er = sqrt(ef*(1.-ef)/float(p));
    
    GlobEfficiencyWheel_2->SetBinContent(i,ef*100.);
    GlobEfficiencyWheel_2->SetBinError(i,er*100.);
    
    std::cout<<o<<" "<<p<<std::endl;
    merged2++;
  }
}

theFileOut->cd();
GlobEfficiencyWheel_m2->Write();
GlobEfficiencyWheel_m1->Write();
GlobEfficiencyWheel_0->Write();
GlobEfficiencyWheel_1->Write();
GlobEfficiencyWheel_2->Write();
theFileOut->Close();
theFile->Close();


std::cout<<"Merged in Wheel -2= "<<mergedm2<<std::endl;
std::cout<<"Merged in Wheel -1= "<<mergedm1<<std::endl;
std::cout<<"Merged in Wheel 0= "<<merged0<<std::endl;
std::cout<<"Merged in Wheel 1= "<<merged1<<std::endl;
std::cout<<"Merged in Wheel 2= "<<merged2<<std::endl;
  
}

//Open root y dentro del promt de root simplemente 
//root [0] .x macroProdPlotsXYeY.C
