//Create and draw a polar graph
//Author: Olivier Couet
   
void graphpolar()
{
   // Illustrates how to use TGraphPolar

  TCanvas * CPol = new TCanvas("CPol","TGraphPolar Examples",600,600);

  float pi = 3.14159265;
    
  Double_t xmin=0.;
  Double_t xmax=pi;
  
  TFile *_file0 = TFile::Open("eff70195_70402_70674.root");

  TH1F * AngClu1La1 =  (TH1F*)_file0->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/AngClu1La1");
  
  TH1F * AngClu2La1 =  (TH1F*)_file0->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/AngClu2La1");
  
  const int n = 50;


  Double_t x[n];
  Double_t y[n];
  Double_t x1[n];
  Double_t y1[n];
  
  TF1 * fplot = new TF1("fplot","cos(x)",xmin,xmax);
  
  for (Int_t ipt = 0; ipt < n; ipt++){
    x[ipt] = ipt*(xmax-xmin)/n+xmin;
    y[ipt] = AngClu1La1->GetBinContent(ipt)/AngClu1La1->GetEntries();
  }
  
  TGraphPolar * grP = new TGraphPolar(n,x,y);
  grP->SetLineColor(2);
  grP->SetLineWidth(0.2);
  grP->Draw("");
  
  for (Int_t ipt = 0; ipt < n; ipt++){
    x1[ipt] = ipt*(xmax-xmin)/n+xmin;
    y1[ipt] = AngClu2La1->GetBinContent(ipt)/AngClu2La1->GetEntries();
  }
  
  TGraphPolar * grP1 = new TGraphPolar(n,x1,y1);
  grP1->SetLineColor(4);
  grP1->SetLineWidth(0.2);
  grP1->Draw("same");
  
  // Update, otherwise GetPolargram returns 0
  CPol->Update();

  //grP1->GetPolargram()->SetTextColor(8);
  //grP1->GetPolargram()->SetRangePolar(-TMath::Pi(),TMath::Pi());
  //grP1->GetPolargram()->SetNdivPolar(703);
  //grP1->GetPolargram()->SetToRadian();
}
