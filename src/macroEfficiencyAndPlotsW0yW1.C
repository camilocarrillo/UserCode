{
TFile * theFile = new TFile("Global.root");
TFile * theFileOut = new TFile("GlobalWithEff.root","RECREATE");

//Efficiency Images

theFileOut->cd();

float fontsize = 0.018;
float bottonMarging = 0.18;
int CanvaSizeX = 1200;
int CanvaSizeY = 600;

//Wheel 0
TH1F * GlobOcupancyWheel_0 = theFile->Get("GlobOcupancyWheel_0");
TH1F * GlobExpectedWheel_0 = theFile->Get("GlobExpectedWheel_0");
TH1F * GlobEfficiencyWheel_0 = theFile->Get("GlobEfficiencyWheel_0");
TH1F * GlobExpectedWheel_0 = (TH1F*)(theFile->Get("GlobExpectedWheel_0"));
TH1F * GlobOcupancyWheel_0 = (TH1F*)(theFile->Get("GlobOcupancyWheel_0"));

GlobExpectedWheel_0->Sumw2();
GlobOcupancyWheel_0->Sumw2();
GlobExpectedWheel_0->Divide(GlobOcupancyWheel_0,GlobExpectedWheel_0,1.0,1.0,"B");
GlobExpectedWheel_0->SetLineColor(1);
GlobExpectedWheel_0->GetYaxis()->SetTitle("Efficiency (%)");
GlobExpectedWheel_0->GetXaxis()->SetLabelSize(fontsize);

Ca1 = new TCanvas("Ca1","EfficiencyW0",CanvaSizeX,CanvaSizeY);
Ca1->SetBottomMargin(bottonMarging);
GlobExpectedWheel_0->LabelsDeflate();
GlobExpectedWheel_0->Write();
GlobExpectedWheel_0->Draw();
Ca1->SaveAs("results/Efficiency/EfficiencyWheel0.png");

Ca1->Close();


//Wheel 1
TH1F * GlobOcupancyWheel_1 = theFile->Get("GlobOcupancyWheel_1");
TH1F * GlobExpectedWheel_1 = theFile->Get("GlobExpectedWheel_1");
TH1F * GlobEfficiencyWheel_1 = theFile->Get("GlobEfficiencyWheel_1");
TH1F * GlobExpectedWheel_1 = (TH1F*)(theFile->Get("GlobExpectedWheel_1"));
TH1F * GlobOcupancyWheel_1 = (TH1F*)(theFile->Get("GlobOcupancyWheel_1"));
GlobExpectedWheel_1->Sumw2();
GlobOcupancyWheel_1->Sumw2();
GlobExpectedWheel_1->Divide(GlobOcupancyWheel_1,GlobExpectedWheel_1,1.0,1.0,"B");
GlobExpectedWheel_1->SetLineColor(1);
GlobExpectedWheel_1->GetYaxis()->SetTitle("Efficiency (%)");
GlobExpectedWheel_1->GetXaxis()->SetLabelSize(fontsize);

Ca3 = new TCanvas("Ca3","EfficiencyW1",CanvaSizeX,CanvaSizeY);
Ca3->SetBottomMargin(bottonMarging);
GlobExpectedWheel_1->LabelsDeflate();
GlobExpectedWheel_1->Write();
GlobExpectedWheel_1->Draw();
Ca3->SaveAs("results/Efficiency/EfficiencyWheel1.png");
Ca3->Close();

//Printing Efficiency Images!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11111111

Ca2 = new TCanvas("Ca2","Residuals",800,600);

//The Other Images



TH1F * BXDistribution = theFile->Get("BXDistribution");
std::cout<<"Creating BX Distribution Image"<<std::endl;
if(BXDistribution){
  BXDistribution->Draw();
  BXDistribution->GetXaxis()->SetTitle("BX Distribution");
  Ca2->SaveAs("results/mydqm/BXDistribution.png");
  Ca2->Clear();
  BXDistribution->Write();
}


TH1F * DigisDistribution = theFile->Get("DigisDistribution");
std::cout<<"Creating Residuals for Different Layers"<<std::endl;
if(DigisDistribution){
  DigisDistribution->Draw();
  DigisDistribution->GetXaxis()->SetTitle("Digis Distribution (digis/event)");
  Ca2->SaveAs("results/mydqm/DigisDistribution.png");
  Ca2->Clear();
  BXDistribution->Write();
}


TH1F * hGlobalResLa1 = theFile->Get("GlobalResidualsLa1");
std::cout<<"Creating Residuals for Different Layers"<<std::endl;
hGlobalResLa1->Draw();
hGlobalResLa1->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer1.png");
Ca2->Clear();
hGlobalResLa1->Write();

TH1F * hGlobalResLa2 = theFile->Get("GlobalResidualsLa2");
hGlobalResLa2->Draw();
hGlobalResLa2->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer2.png");
Ca2->Clear();
hGlobalResLa2->Write();

TH1F * hGlobalResLa3 = theFile->Get("GlobalResidualsLa3");
hGlobalResLa3->Draw();
hGlobalResLa3->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer3.png");
Ca2->Clear();
hGlobalResLa3->Write();

TH1F * hGlobalResLa4 = theFile->Get("GlobalResidualsLa4");
hGlobalResLa4->Draw();
hGlobalResLa4->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer4.png");
Ca2->Clear();
hGlobalResLa4->Write();
  
TH1F * hGlobalResLa5 = theFile->Get("GlobalResidualsLa5");
hGlobalResLa5->Draw();
hGlobalResLa5->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer5.png");
Ca2->Clear();
hGlobalResLa5->Write();

TH1F * hGlobalResLa6 = theFile->Get("GlobalResidualsLa6");
hGlobalResLa6->Draw();
hGlobalResLa6->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsLayer6.png");
Ca2->Clear();
hGlobalResLa6->Write();
  

//Clu1 all Layers

TH1F * hGlobalResClu1La1 = theFile->Get("GlobalResidualsClu1La1");
hGlobalResClu1La1->Draw();
hGlobalResClu1La1->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La1.png");
Ca2->Clear();
hGlobalResClu1La1->Write();

TH1F * hGlobalResClu1La2 = theFile->Get("GlobalResidualsClu1La2");
hGlobalResClu1La2->Draw();
hGlobalResClu1La2->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La2.png");
Ca2->Clear();
hGlobalResClu1La2->Write();

TH1F * hGlobalResClu1La3 = theFile->Get("GlobalResidualsClu1La3");
hGlobalResClu1La3->Draw();
hGlobalResClu1La3->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La3.png");
Ca2->Clear();
hGlobalResClu1La3->Write();
  
TH1F * hGlobalResClu1La4 = theFile->Get("GlobalResidualsClu1La4");
hGlobalResClu1La4->Draw();
hGlobalResClu1La4->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La4.png");
Ca2->Clear();
hGlobalResClu1La4->Write();

TH1F * hGlobalResClu1La5 = theFile->Get("GlobalResidualsClu1La5");
hGlobalResClu1La5->Draw();
hGlobalResClu1La5->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La5.png");
Ca2->Clear();
hGlobalResClu1La5->Write();

TH1F * hGlobalResClu1La6 = theFile->Get("GlobalResidualsClu1La6");
hGlobalResClu1La6->Draw();
hGlobalResClu1La6->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu1La6.png");
Ca2->Clear();
hGlobalResClu1La6->Write();

//Clu2 all Layers

TH1F * hGlobalResClu2La1 = theFile->Get("GlobalResidualsClu2La1");
hGlobalResClu2La1->Draw();
hGlobalResClu2La1->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La1.png");
Ca2->Clear();
hGlobalResClu2La1->Write();

TH1F * hGlobalResClu2La2 = theFile->Get("GlobalResidualsClu2La2");
hGlobalResClu2La2->Draw();
hGlobalResClu2La2->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La2.png");
Ca2->Clear();
hGlobalResClu2La2->Write();

TH1F * hGlobalResClu2La3 = theFile->Get("GlobalResidualsClu2La3");
hGlobalResClu2La3->Draw();
hGlobalResClu2La3->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La3.png");
Ca2->Clear();
hGlobalResClu2La3->Write();
  
TH1F * hGlobalResClu2La4 = theFile->Get("GlobalResidualsClu2La4");
hGlobalResClu2La4->Draw();
hGlobalResClu2La4->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La4.png");
Ca2->Clear();
hGlobalResClu2La4->Write();

TH1F * hGlobalResClu2La5 = theFile->Get("GlobalResidualsClu2La5");
hGlobalResClu2La5->Draw();
hGlobalResClu2La5->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La5.png");
Ca2->Clear();
hGlobalResClu2La5->Write();

TH1F * hGlobalResClu2La6 = theFile->Get("GlobalResidualsClu2La6");
hGlobalResClu2La6->Draw();
hGlobalResClu2La6->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu2La6.png");
Ca2->Clear();
hGlobalResClu2La6->Write();


//Residuals
  
TH1F * hGlobalResClu3La1= theFile->Get("GlobalResidualsClu3La1");
hGlobalResClu3La1->Draw();
hGlobalResClu3La1->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La1.png");
Ca2->Clear();
hGlobalResClu3La1->Write();

TH1F * hGlobalResClu3La2= theFile->Get("GlobalResidualsClu3La2");
hGlobalResClu3La2->Draw();
hGlobalResClu3La2->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La2.png");
Ca2->Clear();
hGlobalResClu3La2->Write();

TH1F * hGlobalResClu3La3= theFile->Get("GlobalResidualsClu3La3");
hGlobalResClu3La3->Draw();
hGlobalResClu3La3->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La3.png");
Ca2->Clear();
hGlobalResClu3La3->Write();
  
TH1F * hGlobalResClu3La4= theFile->Get("GlobalResidualsClu3La4");
hGlobalResClu3La4->Draw();
hGlobalResClu3La4->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La4.png");
Ca2->Clear();
hGlobalResClu3La4->Write();

TH1F * hGlobalResClu3La5= theFile->Get("GlobalResidualsClu3La5");
hGlobalResClu3La5->Draw();
hGlobalResClu3La5->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La5.png");
Ca2->Clear();
hGlobalResClu3La5->Write();

TH1F * hGlobalResClu3La6= theFile->Get("GlobalResidualsClu3La6");
hGlobalResClu3La6->Draw();
hGlobalResClu3La6->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/ResidualsClu3La6.png");
Ca2->Clear();
hGlobalResClu3La6->Write();


//Global Residuals in Y

TH1F * GlobalResidualsY= theFile->Get("GlobalResidualsY");
GlobalResidualsY->Draw();
GlobalResidualsY->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalResidualsY.png");
Ca2->Clear();
GlobalResidualsY->Write();


TH1F * hGlobalYResLa1 = theFile->Get("GlobalYResidualsLa1");
std::cout<<"Creating Residuals for Different Layers"<<std::endl;
hGlobalYResLa1->Draw();
hGlobalYResLa1->GetXaxis()->SetTitle("Residuals Y (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa1.png");
Ca2->Clear();
hGlobalYResLa1->Write();


TH1F * hGlobalYResLa2 = theFile->Get("GlobalYResidualsLa2");
hGlobalYResLa2->Draw();
hGlobalYResLa2->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa2.png");
Ca2->Clear();
hGlobalYResLa2->Write();

TH1F * hGlobalYResLa3 = theFile->Get("GlobalYResidualsLa3");
hGlobalYResLa3->Draw();
hGlobalYResLa3->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa3.png");
Ca2->Clear();
hGlobalYResLa3->Write();

TH1F * hGlobalYResLa4 = theFile->Get("GlobalYResidualsLa4");
hGlobalYResLa4->Draw();
hGlobalYResLa4->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa4.png");
Ca2->Clear();
hGlobalYResLa4->Write();
  
TH1F * hGlobalYResLa5 = theFile->Get("GlobalYResidualsLa5");
hGlobalYResLa5->Draw();
hGlobalYResLa5->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa5.png");
Ca2->Clear();
hGlobalYResLa5->Write();

TH1F * hGlobalYResLa6 = theFile->Get("GlobalYResidualsLa6");
hGlobalYResLa6->Draw();
hGlobalYResLa6->GetXaxis()->SetTitle("Residuals (cm)");
Ca2->SaveAs("results/residuals/GlobalYResidualsLa6.png");
Ca2->Clear();
hGlobalYResLa6->Write();  

TH1F * Statistics = theFile->Get("Statistics");
Statistics->Draw();
Ca2->SetBottomMargin(0.4);
Ca2->SaveAs("results/mydqm/Statistics.png");
Ca2->Clear();
hGlobalYResLa6->Write();  

Ca2->Close();


theFileOut->Close();
theFile->Close();

}


//TCanvas *c1 = new TCanvas("c1","c1",800,600);
//c1->Range(0,0,1,1);
//c1->SetFillColor(0);
//c1->SetBorderSize(2);

