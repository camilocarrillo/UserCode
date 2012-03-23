{

#include "Riostream.h"
  
  gROOT->Reset();


  // gluino
//  TFile * theFile1 = new TFile("_HSCPgluino_M-200_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile2 = new TFile("_HSCPgluino_M-300_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile3 = new TFile("_HSCPgluino_M-400_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile4 = new TFile("_HSCPgluino_M-500_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile5 = new TFile("_HSCPgluino_M-600_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile6 = new TFile("_HSCPgluino_M-900_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");

// stop pythia and madgraph just replacing madgraph for pythia
//  TFile * theFile1 = new TFile("_HSCPstop_M-130_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile2 = new TFile("_HSCPstop_M-200_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile3 = new TFile("_HSCPstop_M-300_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile4 = new TFile("_HSCPstop_M-500_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//  TFile * theFile5 = new TFile("_HSCPstop_M-800_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
// // TFile * theFile6 = new TFile("/hscpVal.root");


//stau
TFile * theFile1 = new TFile("_HSCPstau_M-100_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
TFile * theFile2 = new TFile("_HSCPstau_M-126_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
TFile * theFile3 = new TFile("_HSCPstau_M-156_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
TFile * theFile4 = new TFile("_HSCPstau_M-200_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
TFile * theFile5 = new TFile("_HSCPstau_M-247_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
TFile * theFile6 = new TFile("_HSCPstau_M-308_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");

//comparison stop

//TFile * theFile1 = new TFile("_HSCPstop_M-800_7TeV-madgraph_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");
//TFile * theFile2 = new TFile("_HSCPstop_M-800_7TeV-pythia6_Spring10-START3X_V26-v1_GEN-SIM-RECO/hscpVal.root");

 std::cout<<"Reading histos"<<std::endl;

 const int N = 6;	

 TH1F * particleEta[N+1];
 int mass[N+1];
 int color[N+1];

particleEta[1] = (TH1F*) (theFile1->Get("hscpValidator/particleEta"));mass[1]=800;  color[1]=1; 
particleEta[2] = (TH1F*) (theFile2->Get("hscpValidator/particleEta"));mass[2]=800;  color[2]=9; 
particleEta[3] = (TH1F*) (theFile3->Get("hscpValidator/particleEta"));mass[3]=400;  color[3]=2; 
particleEta[4] = (TH1F*) (theFile4->Get("hscpValidator/particleEta"));mass[4]=500;  color[4]=4; 
particleEta[5] = (TH1F*) (theFile5->Get("hscpValidator/particleEta"));mass[5]=600; color[5]=6;
particleEta[6] = (TH1F*) (theFile6->Get("hscpValidator/particleEta"));mass[6]=900; color[6]=5;


//stop replacing mass after commeting particleEta[6]

//  mass[1]=130;
//  mass[2]=200;
//  mass[3]=300;
//  mass[4]=500;
//  mass[5]=900;


 //stau replacing masses

mass[1]=100;
mass[2]=126;
mass[3]=156;
mass[4]=200;
mass[5]=247;
mass[6]=308;
 
 std::cout<<"Creating Canvas"<<std::endl;
 TCanvas *Ca1 = new TCanvas("Ca1","Eta",1200,800);

 float max = -1;
 
 for(int i = 1;i<N+1;i++){
   if(i==1){
     std::cout<<"Drawing "<<i<<"th"<<std::endl;
     particleEta[i]->SetMarkerColor(color[i]);
     particleEta[i]->SetLineColor(color[i]);  
     particleEta[i]->SetLineWidth(2);  
     particleEta[i]->Draw("E");
     float thismax = particleEta[i]->GetBinContent(particleEta[i]->GetMaximumBin());
     if(thismax>max) max = thismax;
   }
   else{
     std::cout<<"Drawing "<<i<<"th"<<std::endl;
     particleEta[i]->SetMarkerColor(color[i]);
     particleEta[i]->SetLineColor(color[i]);  
     particleEta[i]->SetLineWidth(2);  
     particleEta[i]->Draw("sameE");
     float thismax = particleEta[i]->GetBinContent(particleEta[i]->GetMaximumBin());
     if(thismax>max) max = thismax;
   }
 }
   
 std::stringstream sta[N+1];
 
 TLegend *leg = new TLegend(0.4974874,0.8304196,0.9974874,0.9965035,NULL,"brNDC");
 leg->SetTextFont(62);
 leg->SetLineColor(1);
 leg->SetLineStyle(1);
 leg->SetLineWidth(1);
 leg->SetFillColor(19);
 leg->SetFillStyle(1001);

 float x[N+1], y[N+1], ey[N+1];
 
 for(int i = 1;i<N+1;i++){
   sta[i]<<"Mass "<<mass[i]<<"GeV Mean "<<endl<<particleEta[i]->GetMean()<<endl<<" RMS "<<particleEta[i]->GetRMS();
   x[i]=mass[i];
   y[i]=particleEta[i]->GetMean();
   ey[i]=particleEta[i]->GetRMS();
   particleEta[i]->SetMaximum(1.2*max);
 }
 
 for(int i = 1;i<N+1;i++){
   leg->AddEntry(particleEta[i],(sta[i].str()).c_str(),"l");
 }
 
 leg->Draw("same");

 Ca1->SaveAs("EtaComparison.png");

 TGraphErrors * grp = new TGraphErrors(N+1,x,y,0,ey);
 
 TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);    
 
 grp->SetTitle("Eta for different mass points");
 grp->SetLineColor(kRed);
 grp->SetMarkerStyle(20);
 grp->SetMarkerSize(1.0);
 grp->GetXaxis()->SetTitle("gluino mass(GeV)");
 grp->GetYaxis()->SetTitle("Mean Eta error bars RMS");
 grp->Draw("AP");

 Ca0->SaveAs("EtaVsMass.png");
 exit(0) ;
}









