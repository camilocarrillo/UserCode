{
gROOT->Reset();
#include "Riostream.h"

   ifstream in;
   in.open("alleff.txt");

   Float_t x,y,ey;
   Int_t nlines = 0;
   TFile * theFile = new TFile("merge43434.root");
   TFile * theFileOut = new TFile("merge43434witheff.root","RECREATE");

   TH1F * GlobOcupancyWheel_0 = theFile->Get("GlobOcupancyWheel_0");
   TH1F * GlobExpectedWheel_0 = theFile->Get("GlobExpectedWheel_0");
   TH1F * GlobEfficiencyWheel_0 = theFile->Get("GlobEfficiencyWheel_0");

   TH1F * GlobOcupancyWheel_1 = theFile->Get("GlobOcupancyWheel_1");
   TH1F * GlobExpectedWheel_1 = theFile->Get("GlobExpectedWheel_1");
   TH1F * GlobEfficiencyWheel_1 = theFile->Get("GlobEfficiencyWheel_1");

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

theFileOut->cd();
GlobEfficiencyWheel_0->Write();
GlobEfficiencyWheel_1->Write();

theFile->Close();
theFileOut->Close();

std::cout<<"Merged in Wheel 0= "<<merged0<<std::endl;
std::cout<<"Merged in Wheel 1= "<<merged1<<std::endl;
  
}

//Open root y dentro del promt de root simplemente 
//root [0] .x macroProdPlotsXYeY.C
