void FitFlat(){
  TFile *f1 = new TFile("9300WithEff.root");
  TH1F *tmpef;
  f1->GetObject("AverageEfficiencyWheel_1near",tmpef);
  TCanvas *c1 = new TCanvas("c1","c1",800,1000);
  tmpef->Draw();
  TF1 *func = new TF1("func","[0]",100,1);
  func->SetParLimits(0,0,100);
  tmpef->Fit("func","W");
}

Double_t fitf(Double_t x,Double_t par)
{
  return par;
}
