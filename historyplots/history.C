#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void setHisto(TH1F * histo){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.03);
  histo->SetMarkerStyle(21);
  histo->Draw("P");         
}

void setHistonormalized(TH1F * histo,int sty){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.03);
  histo->SetMarkerStyle(sty);
  histo->DrawNormalized("P");         
}

void setHistosame(TH1F * histo, int sty){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.03);
  histo->SetMarkerStyle(sty);
  histo->DrawNormalized("Psame");         
}

float masked(TFile * file){

  std::cout<<"Calling masked"<<std::endl;
  
  float total=0;
  TH1F * allmasked[10];
  
  allmasked[0]= (TH1F*) (file->Get("GlobMaskedWheel_-2near"));
  allmasked[1]= (TH1F*) (file->Get("GlobMaskedWheel_-1near"));
  allmasked[2]= (TH1F*) (file->Get("GlobMaskedWheel_0near"));
  allmasked[3]= (TH1F*) (file->Get("GlobMaskedWheel_1near"));
  allmasked[4]= (TH1F*) (file->Get("GlobMaskedWheel_2near"));
  allmasked[5]= (TH1F*) (file->Get("GlobMaskedWheel_2far"));
  allmasked[6]= (TH1F*) (file->Get("GlobMaskedWheel_-2far"));
  allmasked[7]= (TH1F*) (file->Get("GlobMaskedWheel_-1far"));
  allmasked[8]= (TH1F*) (file->Get("GlobMaskedWheel_0far"));
  allmasked[9]= (TH1F*) (file->Get("GlobMaskedWheel_1far"));

  for(int i=0;i<10;i++) total = total + allmasked[i]->Integral();

  total = (total/1020);

  std::cout<<total<<std::endl;
  
  delete allmasked[0];

  return total;
}

float maskedendcap(TFile * file){

  std::cout<<"Calling masked endcap"<<std::endl;
  
  float total=0;
  TH1F * allmasked[12];
  
  allmasked[0]= (TH1F*) (file->Get("GlobMaskedDisk_3near"));  
  allmasked[1]= (TH1F*) (file->Get("GlobMaskedDisk_2near"));  
  allmasked[2]= (TH1F*) (file->Get("GlobMaskedDisk_1near"));  
  allmasked[3]= (TH1F*) (file->Get("GlobMaskedDisk_m3near")); 
  allmasked[4]= (TH1F*) (file->Get("GlobMaskedDisk_m2near")); 
  allmasked[5]= (TH1F*) (file->Get("GlobMaskedDisk_m1near")); 
  allmasked[6]= (TH1F*) (file->Get("GlobMaskedDisk_3far"));  
  allmasked[7]= (TH1F*) (file->Get("GlobMaskedDisk_2far"));  
  allmasked[8]= (TH1F*) (file->Get("GlobMaskedDisk_1far"));  
  allmasked[9]= (TH1F*) (file->Get("GlobMaskedDisk_m3far")); 
  allmasked[10]=(TH1F*) (file->Get("GlobMaskedDisk_m2far")); 
  allmasked[11]=(TH1F*) (file->Get("GlobMaskedDisk_m1far")); 

  for(int i=0;i<12;i++) total = total + allmasked[i]->Integral();

  total = (total/1296);

  std::cout<<total<<std::endl;
  
  delete allmasked[0];

  return total;
}

void history(){
  //gROOT->Reset();
  gStyle->SetOptStat(0);
  
  ifstream fileruns;

  //--hvth info
  
  map<string,float> hvinfo;
  map<string,int> thinfo;

  ifstream hvth;

  fileruns.open("runslist.txt");
  hvth.open("/afs/cern.ch/user/c/carrillo/historyplots/hvth.txt");
  
  string Run;
  float hv=0;
  int th=0;
  
  while(!hvth.eof()){
    hvth >>Run >>hv >>th;
    if(Run.size()==0) continue;
    std::cout<<Run<<" "<<hv<<" "<<th<<std::endl;  
    hvinfo[Run]=hv;
    thinfo[Run]=th;
  }
  
  //----------

  //--cutp info
  
  map<string,float> cubarrelinfo;
  map<string,float> errorcubarrelinfo;
  map<string,float> tpbarrelinfo;
  map<string,float> errortpbarrelinfo;

  map<string,float> cuendcapinfo;
  map<string,float> errorcuendcapinfo;
  map<string,float> tpendcapinfo;
  map<string,float> errortpendcapinfo;

  ifstream cutp;

  cutp.open("/afs/cern.ch/user/c/carrillo/historyplots/cutp.txt");
  
  string Run;
  float cu=0;
  float tp=0;
  
  while(!cutp.eof()){
    cutp >>Run >>cubarrelinfo[Run] >>errorcubarrelinfo[Run] >>tpbarrelinfo[Run] >>errortpbarrelinfo[Run] 
	 >>cuendcapinfo[Run] >>errorcuendcapinfo[Run] >>tpendcapinfo[Run] >>errortpendcapinfo[Run];
    std::cout<<Run<<" "<<cubarrelinfo[Run]<<" "<<errorcubarrelinfo[Run]<<" "<<tpbarrelinfo[Run]<<" "<<errortpbarrelinfo[Run]<<std::endl;
    if(Run.size()==0) continue;
  }
  
  //----------


  string run;
 
  std::cout<<"Before the while "<<std::endl;

  const int N=74;

  TH1F * EventsH = new TH1F("EventsH","Number of events History",N,0,N);
  TH1F * DoubleGapBarrelH = new TH1F("DoubleGapBarrelH","Double Gap Mean Efficiency Barrel",N,0,N);
  TH1F * DoubleGapEndCapH = new TH1F("DoubleGapEndCapH","Double Gap Mean Efficiency EndCap",N,0,N);
  TH1F * bxbarrelH = new TH1F("bxbarrelH","Mean Bunch Crossing Barrel (error bars Mean RMS)",N,0,N);
  TH1F * bxendcapH = new TH1F("bxendcapH","Mean Bunch Crossing EndCap (error bars Mean RMS)",N,0,N);
  TH1F * CLSH = new TH1F("CLSH","Cluster Size for the Barrel (error bars Mean RMS)",N,0,N);
  TH1F * hvH = new TH1F("hvH","High Voltage for the whole system",N,0,N);
  TH1F * thH = new TH1F("thH","Threshold for the whole system",N,0,N);
  TH1F * maskedH = new TH1F("maskedH","Average Percentage of strips without data per roll in the Barrel",N,0,N);
  TH1F * maskedendcapH = new TH1F("maskedendcapH","Average Percentage of strips without data per roll in the End Cap",N,0,N);
  TH1F * tpbarrelH = new TH1F("tpbarrelH","Average temperature for the barrel",N,0,N);
  TH1F * tpendcapH = new TH1F("tpendcapH","Average temperature for the endcap",N,0,N);
  TH1F * cubarrelH = new TH1F("cubarrelH","Average current for the barrel",N,0,N);
  TH1F * cuendcapH = new TH1F("cuendcapH","Average current for the endcap",N,0,N);
  
  int index=1;

  std::cout<<"Before the while "<<std::endl;

  while(!fileruns.eof()){
    getline(fileruns,run);
    std::cout<<run<<std::endl;
    if(run.size()==0) continue;
    TFile * theFile = new TFile(("eff"+run+".root").c_str());
    TFile * secFile = new TFile(("sec"+run+".root").c_str());

    if(!theFile) continue;
    if(!secFile) continue;
    
    //Set Run Axis
    EventsH->GetXaxis()->SetBinLabel(index,run.c_str());
    DoubleGapBarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
    DoubleGapEndCapH->GetXaxis()->SetBinLabel(index,run.c_str());
    bxbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
    bxendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
    CLSH->GetXaxis()->SetBinLabel(index,run.c_str());
    thH->GetXaxis()->SetBinLabel(index,run.c_str());
    hvH->GetXaxis()->SetBinLabel(index,run.c_str());
    maskedH->GetXaxis()->SetBinLabel(index,run.c_str());
    maskedendcapH->GetXaxis()->SetBinLabel(index,run.c_str());

    tpbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
    tpendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
    	       
    cubarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
    cuendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
    
  
    TH1F * Statistics = (TH1F*) (theFile->Get("DQMData/Muons/MuonSegEff/Statistics"));
    EventsH->SetBinContent(index,Statistics->GetBinContent(1));
    
    TH1F * DoubleGapBarrel = (TH1F*) (secFile->Get("DoubleGapBarrel"));
    DoubleGapBarrelH->SetBinContent(index,DoubleGapBarrel->GetMean());

    TH1F * DoubleGapEndCap = (TH1F*) (secFile->Get("DoubleGapEndCap"));
    DoubleGapEndCapH->SetBinContent(index,DoubleGapEndCap->GetMean());

    TH2F * bxbarrel = (TH2F*) (secFile->Get("BXBarrel"));
    bxbarrelH->SetBinContent(index,bxbarrel->ProjectionX("_px")->GetMean());
    bxbarrelH->SetBinError(index,bxbarrel->ProjectionY("_py")->GetMean());
    
    TH2F * bxendcap = (TH2F*) (secFile->Get("BXEndCap"));
    bxendcapH->SetBinContent(index,bxendcap->ProjectionX("_px")->GetMean());
    bxendcapH->SetBinError(index,bxendcap->ProjectionY("_py")->GetMean());
    
    TH1F * CLS = (TH1F*) (secFile->Get("CLS"));
    CLSH->SetBinContent(index,CLS->GetMean());
    CLSH->SetBinError(index,CLS->GetRMS());
    
    hvH->SetBinContent(index,hvinfo[run]);
    thH->SetBinContent(index,thinfo[run]);
    
    maskedH->SetBinContent(index,masked(secFile));
    maskedendcapH->SetBinContent(index,maskedendcap(secFile));
    
    if(tpbarrelinfo[run]!=0){
      tpbarrelH->SetBinContent(index,tpbarrelinfo[run]);
      tpbarrelH->SetBinError(index,errortpbarrelinfo[run]);
    }
    
    if(tpendcapinfo[run]!=0){
      tpendcapH->SetBinContent(index,tpendcapinfo[run]);
      tpendcapH->SetBinError(index,errortpendcapinfo[run]);
    }
    	       
    if(cubarrelinfo[run]!=0){
      cubarrelH->SetBinContent(index,cubarrelinfo[run]);
      cubarrelH->SetBinError(index,errorcubarrelinfo[run]);
    }

    if(cuendcapinfo[run]!=0){
      cuendcapH->SetBinContent(index,cuendcapinfo[run]);
      cuendcapH->SetBinError(index,errorcuendcapinfo[run]);
    }
    
    delete theFile;
    index++;
  }

  TCanvas * Ca0 = new TCanvas("Ca0","History",1200,800);

  setHisto(EventsH);
  Ca0->SaveAs("EventsH.png");
  Ca0->Clear();

  setHisto(DoubleGapBarrelH);
  Ca0->SaveAs("DoubleGapBarrelH.png");
  Ca0->Clear();
  
  setHisto(DoubleGapEndCapH);
  Ca0->SaveAs("DoubleGapEndCapH.png");
  Ca0->Clear();

  setHisto(bxendcapH);
  Ca0->SaveAs("bxendcapH.png");
  Ca0->Clear();

  setHisto(bxbarrelH);
  Ca0->SaveAs("bxbarrelH.png");
  Ca0->Clear();

  setHisto(CLSH);
  Ca0->SaveAs("CLSH.png");
  Ca0->Clear();

  setHisto(hvH);
  Ca0->SaveAs("hvH.png");
  Ca0->Clear();

  setHisto(thH);
  Ca0->SaveAs("thH.png");
  Ca0->Clear();

  setHisto(maskedH);
  Ca0->SaveAs("maskedH.png");
  Ca0->Clear();

  setHisto(maskedendcapH);
  Ca0->SaveAs("maskedendcapH.png");
  Ca0->Clear();
  
  setHisto(tpbarrelH);
  Ca0->SaveAs("tpbarrelH.png");
  Ca0->Clear();

  setHisto(tpendcapH);
  Ca0->SaveAs("tpendcapH.png");
  Ca0->Clear();
	       
  setHisto(cubarrelH);
  Ca0->SaveAs("cubarrelH.png");
  Ca0->Clear();

  setHisto(cuendcapH);
  Ca0->SaveAs("cuendcapH.png");
  Ca0->Clear();
  
  setHistonormalized(CLSH,21);
  setHistosame(DoubleGapBarrelH,22);
  setHistosame(hvH,23);
  setHistosame(thH,24);

  TLegend *leg = new TLegend(0.1295987,0.1437824,0.4297659,0.2448187,NULL,"brNDC");
  leg->AddEntry(DoubleGapBarrelH,"Efficiency","plc");
  leg->AddEntry(CLSH,"Cluster Size","plc");
  leg->AddEntry(hvH,"High Voltage","plc");
  leg->AddEntry(thH,"Threshold","plc");
  leg->Draw("same");

  Ca0->SaveAs("all.png");

  TFile *  theFileOut = new TFile("summaryCRAFT09.root", "RECREATE");
  theFileOut->cd();
  CLSH->Write();
  hvH->Write();
  thH->Write();
  DoubleGapBarrelH->Write();
  theFileOut->Write();


}
