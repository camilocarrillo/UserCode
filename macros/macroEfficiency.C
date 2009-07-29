{
TFile * theFile = new TFile("merge43434.root");
TFile * theFileOut = new TFile("merge43434witheff.root","RECREATE");


TCanvas *c1 = new TCanvas("c1","c1",800,600);
c1->Range(0,0,1,1);
c1->SetFillColor(0);
c1->SetBorderSize(2);

TH1F * GlobOcupancyWheel_0 = theFile->Get("GlobOcupancyWheel_0");
TH1F * GlobExpectedWheel_0 = theFile->Get("GlobExpectedWheel_0");
TH1F * GlobEfficiencyWheel_0 = theFile->Get("GlobEfficiencyWheel_0");

TH1F *GlobExpectedWheel_0 = (TH1F*)(theFile->Get("GlobExpectedWheel_0"));
TH1F *GlobOcupancyWheel_0 = (TH1F*)(theFile->Get("GlobOcupancyWheel_0"));

GlobExpectedWheel_0->Sumw2();
GlobOcupancyWheel_0->Sumw2();
GlobExpectedWheel_0->Divide(GlobOcupancyWheel_0,GlobExpectedWheel_0,1.0,1.0,"B");
GlobExpectedWheel_0->SetLineColor(1);
//GlobExpectedWheel_0->GetXaxis()->SetTitle("Roll Name");
GlobExpectedWheel_0->GetYaxis()->SetTitle("Efficiency (%)");

theFileOut->cd();
GlobExpectedWheel_0->Write();
theFileOut->Close();

theFile->Close();

}
