#include "TFile.h"

void PlotSummaryCRAFT09(){
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
 
  TFile *f =new TFile("summaryCRAFT09.root");
  if (f->IsZombie()){
    cout <<"File Not Found"<<endl;
  }
  TH1* h1=0;
  TH1* h2=0;
  TH1* h3=0;
  TH1* h4=0;
  
  c1 = new TCanvas("c1","Test",200,10,800,600);
  c1->Range(0,0,1,1);

  TPad *p1 = new TPad("p1","p1",0.01,0.78,0.99,0.99);
  p1->Draw();
  p1->cd();
  p1->SetBorderMode(0);
  p1->SetTopMargin(0.);
  p1->SetBottomMargin(0.);
  f->GetObject("thH",h1);
  h1->GetYaxis()->SetTitle("Thr (mV)");
  h1->GetYaxis()->CenterTitle(true);
  h1->GetYaxis()->SetLabelSize(0.1);
  h1->GetYaxis()->SetTitleOffset(0.2);
  h1->GetYaxis()->SetTitleSize(0.15);
  h1->Draw("");
  p1->Modified();
  c1->cd();

 
  TPad *p2 = new TPad("p2","p2",0.01,0.56,0.99,0.78);
  p2->Draw();
  p2->cd();
  p2->SetBorderMode(0);
  p2->SetTopMargin(0.);
  p2->SetBottomMargin(0.);
  f->GetObject("hvH",h2);
  h2->GetYaxis()->SetTitle("HV (kV)");
  h2->GetYaxis()->CenterTitle(true);
  h2->GetYaxis()->SetLabelSize(0.1);
  h2->GetYaxis()->SetTitleOffset(0.2);
  h2->GetYaxis()->SetTitleSize(0.15);

  h2->Draw("");
  p2->Modified();
  c1->cd();

  TPad *p3 = new TPad("p3","p3",0.01,0.34,0.99,0.56);
  p3->Draw();
  p3->cd();
  p3->SetBorderMode(0);
  p3->SetTopMargin(0.);
  p3->SetBottomMargin(0.);
  f->GetObject("CLSH",h3);
  //  h3->SetMaximum(5.);
  h3->GetYaxis()->SetTitle("Cluster Size");
  h3->GetYaxis()->CenterTitle(true);
  h3->GetYaxis()->SetLabelSize(0.1);
  h3->GetYaxis()->SetTitleOffset(0.2);
  h3->GetYaxis()->SetTitleSize(0.15);
  h3->SetMaximum(3.4);
  h3->SetMinimum(0.1);
  h3->Draw("p");
  p3->Modified();
  c1->cd();


  TPad *p4 = new TPad("p4","p4",0.01,0.01,0.99,0.34);
  p4->Draw();
  p4->cd();
  p4->SetBorderMode(0);
  p4->SetTopMargin(0.);
  p4->SetBottomMargin(0.3);
  f->GetObject("DoubleGapBarrelH",h4);
  h4->GetXaxis()->SetTitle("Run Number");
  h4->GetXaxis()->CenterTitle(true);
  h4->GetYaxis()->SetTitle("Efficiency");
  h4->GetYaxis()->CenterTitle(true);
  h4->GetXaxis()->SetLabelSize(0.08);
  h4->GetYaxis()->SetLabelSize(0.06);
  h4->GetYaxis()->SetTitleOffset(0.3);
  h4->GetYaxis()->SetTitleSize(0.1);
  h4->GetXaxis()->SetTitleOffset(1.5);
  h4->GetXaxis()->SetTitleSize(0.1);
  h4->SetMaximum(110);
  h4->Draw("P");
  p4->Modified();
  c1->cd();
  //c1->SetFillColor(42);

  //  h1->SetMaximum();

  /*
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);
  h1->SetLineStyle(1);
  h2->SetLineStyle(2);
  h3->SetLineStyle(4);
  h1->SetLineWidth(3);
  h2->SetLineWidth(3);
  h3->SetLineWidth(3);
  p1->cd();
  h1->Draw();
  p1->Modified();
  c1->cd();
  p2->cd();
  h2->Draw();
  p2->Modified();
  p3->cd();
  h3->Draw();
  p3->Modified();
  p4->cd();
  h4->Draw();
  p4->Modified();
  c1->cd();
  */
  /*
  float lyu1=0.90*massimo;
  float lyd1=0.85*massimo;
  float lyu2=0.80*massimo;
  float lyd2=0.75*massimo;
  float lyu3=0.70*massimo;
  float lyd3=0.65*massimo;


  TLine *lho1 = new TLine(0.6,lyu1,0.7,lyu1);
  TLine *lvl1 = new TLine(0.6,lyu1,0.6,lyd1);
  TLine *lvr1 = new TLine(0.7,lyu1,0.7,lyd1);
  lho1->SetLineColor(1);
  lho1->SetLineStyle(1);
  lho1->SetLineWidth(3);
  lho1->Draw();
  lvl1->SetLineColor(1);
  lvl1->SetLineStyle(1);
  lvl1->SetLineWidth(3);
  lvl1->Draw();
  lvr1->SetLineColor(1);
  lvr1->SetLineStyle(1);
  lvr1->SetLineWidth(3);
  lvr1->Draw();

  TLine *lho2 = new TLine(0.6,lyu2,0.7,lyu2);
  TLine *lvl2 = new TLine(0.6,lyu2,0.6,lyd2);
  TLine *lvr2 = new TLine(0.7,lyu2,0.7,lyd2);
  lho2->SetLineColor(2);
  lho2->SetLineStyle(2);
  lho2->SetLineWidth(3);
  lho2->Draw();
  lvl2->SetLineColor(2);
  lvl2->SetLineStyle(2);
  lvl2->SetLineWidth(3);
  lvl2->Draw();
  lvr2->SetLineColor(2);
  lvr2->SetLineStyle(2);
  lvr2->SetLineWidth(3);
  lvr2->Draw();


  TLine *lho3 = new TLine(0.6,lyu3,0.7,lyu3);
  TLine *lvl3 = new TLine(0.6,lyu3,0.6,lyd3);
  TLine *lvr3 = new TLine(0.7,lyu3,0.7,lyd3);
  lho3->SetLineColor(4);
  lho3->SetLineStyle(4);
  lho3->SetLineWidth(2);
  lho3->Draw();
  lvl3->SetLineColor(4);
  lvl3->SetLineStyle(4);
  lvl3->SetLineWidth(2);
  lvl3->Draw();
  lvr3->SetLineColor(4);
  lvr3->SetLineStyle(4);
  lvr3->SetLineWidth(2);
  lvr3->Draw();

  float tiy=massimo*1.02;
  TText *ti = new TText (0.5,tiy,"RB-2 near side HV=9.2kV");
  ti->SetTextFont(132);
  ti->SetTextAlign(21);
  ti->SetTextSize(0.06);
  ti->Draw();  
  
  float kty1 = (lyu1-lyd1)/2.+lyd1;  
  float kty2 = (lyu2-lyd2)/2.+lyd2; 
  float kty3 = (lyu3-lyd3)/2.+lyd3;
  TText *t1 = new TText (0.72,kty1,"Thr = 220 mV");
  TText *t2 = new TText (0.72,kty2,"Thr = 230 mV");
  TText *t3 = new TText (0.72,kty3,"Thr = 240 mV");
  t1->SetTextFont(132);
  //  t1->SetTextAttributes(12);
  t2->SetTextFont(132);
  t3->SetTextFont(132);
  t1->SetTextAlign(12);
  t2->SetTextAlign(12);
  t3->SetTextAlign(12);
  t1->SetTextSize(0.045);
  t2->SetTextSize(0.045);
  t3->SetTextSize(0.045);
  t1->Draw();
  t2->Draw();
  t3->Draw();
  */
}
