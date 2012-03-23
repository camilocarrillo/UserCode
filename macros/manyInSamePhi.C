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

 TH1F * particlePhi[N+1];
 int mass[N+1];
 int color[N+1];

particlePhi[1] = (TH1F*) (theFile1->Get("hscpValidator/particlePhi"));mass[1]=800;  color[1]=1; 
particlePhi[2] = (TH1F*) (theFile2->Get("hscpValidator/particlePhi"));mass[2]=800;  color[2]=9; 
particlePhi[3] = (TH1F*) (theFile3->Get("hscpValidator/particlePhi"));mass[3]=400;  color[3]=2; 
particlePhi[4] = (TH1F*) (theFile4->Get("hscpValidator/particlePhi"));mass[4]=500;  color[4]=4; 
particlePhi[5] = (TH1F*) (theFile5->Get("hscpValidator/particlePhi"));mass[5]=600; color[5]=6;
particlePhi[6] = (TH1F*) (theFile6->Get("hscpValidator/particlePhi"));mass[6]=900; color[6]=5;


//stop replacing mass after commeting particlePhi[6]

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
 TCanvas *Ca1 = new TCanvas("Ca1","Phi",1200,800);

 float max = -1;
 
 for(int i = 1;i<N+1;i++){
   if(i==1){
     std::cout<<"Drawing "<<i<<"th"<<std::endl;
     particlePhi[i]->SetMarkerColor(color[i]);
     particlePhi[i]->SetLineColor(color[i]);  
     particlePhi[i]->SetLineWidth(2);  
     particlePhi[i]->Draw("E");
     float thismax = particlePhi[i]->GetBinContent(particlePhi[i]->GetMaximumBin());
     if(thismax>max) max = thismax;
   }
   else{
     std::cout<<"Drawing "<<i<<"th"<<std::endl;
     particlePhi[i]->SetMarkerColor(color[i]);
     particlePhi[i]->SetLineColor(color[i]);  
     particlePhi[i]->SetLineWidth(2);  
     particlePhi[i]->Draw("sameE");
     float thismax = particlePhi[i]->GetBinContent(particlePhi[i]->GetMaximumBin());
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
   sta[i]<<"Mass "<<mass[i]<<"GeV Mean "<<endl<<particlePhi[i]->GetMean()<<endl<<" RMS "<<particlePhi[i]->GetRMS();
   x[i]=mass[i];
   y[i]=particlePhi[i]->GetMean();
   ey[i]=particlePhi[i]->GetRMS();
   particlePhi[i]->SetMaximum(1.2*max);
 }
 
 for(int i = 1;i<N+1;i++){
   leg->AddEntry(particlePhi[i],(sta[i].str()).c_str(),"l");
 }
 
 leg->Draw("same");

 Ca1->SaveAs("PhiComparison.png");

 TGraphErrors * grp = new TGraphErrors(N+1,x,y,0,ey);
 
 TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);    
 
 grp->SetTitle("Phi for different mass points");
 grp->SetLineColor(kRed);
 grp->SetMarkerStyle(20);
 grp->SetMarkerSize(1.0);
 grp->GetXaxis()->SetTitle("gluino mass(GeV)");
 grp->GetYaxis()->SetTitle("Mean Phi error bars RMS");
 grp->Draw("AP");

 Ca0->SaveAs("PhiVsMass.png");
 exit(0) ;
}









