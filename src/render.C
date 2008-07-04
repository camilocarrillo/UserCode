{
//Files

TFile * theFile = new TFile("RPCEfficiency.root");
TFile * theFileOut = new TFile("RESULT.root","RECREATE");

theFileOut->cd();

float fontsize = 0.018;
float bottonMarging = 0.18;
int CanvaSizeX = 1200;
int CanvaSizeY = 600;

//Begin to Get the files

//Wheel -2 near
TH1F * EffGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobEfficiencyWheel_-2near");
TH1F * BXGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobBXWheel_-2near");
TH1F * MaskedGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobMaskedWheel_-2near");

//Wheel -2 far
TH1F * EffGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobEfficiencyWheel_-2far");
TH1F * BXGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobBXWheel_-2far");
TH1F * MaskedGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobMaskedWheel_-2far");

//Wheel -1 near
TH1F * EffGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobEfficiencyWheel_-1near");
TH1F * BXGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobBXWheel_-1near");
TH1F * MaskedGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobMaskedWheel_-1near");

//Wheel -1 far
TH1F * EffGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobEfficiencyWheel_-1far");
TH1F * BXGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobBXWheel_-1far");
TH1F * MaskedGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobMaskedWheel_-1far");

//Wheel 0 near
TH1F * EffGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobEfficiencyWheel_0near");
TH1F * BXGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobBXWheel_0near");
TH1F * MaskedGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobMaskedWheel_0near");

//Wheel 0 far
TH1F * EffGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobEfficiencyWheel_0far");
TH1F * BXGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobBXWheel_0far");
TH1F * MaskedGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobMaskedWheel_0far");

//Wheel 1 near
TH1F * EffGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobEfficiencyWheel_1near");
TH1F * BXGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobBXWheel_1near");
TH1F * MaskedGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobMaskedWheel_1near");

//Wheel 1 far
TH1F * EffGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobEfficiencyWheel_1far");
TH1F * BXGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobBXWheel_1far");
TH1F * MaskedGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobMaskedWheel_1far");

//Wheel 2 near
TH1F * EffGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobEfficiencyWheel_2near");
TH1F * BXGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobBXWheel_2near");
TH1F * MaskedGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobMaskedWheel_2near");

//Wheel 2 far
TH1F * EffGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobEfficiencyWheel_2far");
TH1F * BXGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobBXWheel_2far");
TH1F * MaskedGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobMaskedWheel_2far");

//end to get the files

  Ca1 = new TCanvas("Ca1","Efficiency",CanvaSizeX,CanvaSizeY);
  Ca2 = new TCanvas("Ca2","Global Efficiency",1200,CanvaSizeY);

  EffGlobWm2->GetXaxis()->LabelsOption("v");
  EffGlobWm1->GetXaxis()->LabelsOption("v");
  EffGlobW0->GetXaxis()->LabelsOption("v");
  EffGlobW1->GetXaxis()->LabelsOption("v");
  EffGlobW2->GetXaxis()->LabelsOption("v");

  EffGlobWm2->GetXaxis()->SetLabelSize(0.03);
  EffGlobWm1->GetXaxis()->SetLabelSize(0.03);
  EffGlobW0->GetXaxis()->SetLabelSize(0.03);
  EffGlobW1->GetXaxis()->SetLabelSize(0.03);
  EffGlobW2->GetXaxis()->SetLabelSize(0.03);

  EffGlobWm2->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobWm1->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW0->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW1->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW2->GetYaxis()->SetRangeUser(0.,100.);
  
  BXGlobWm2->GetXaxis()->LabelsOption("v");
  BXGlobWm1->GetXaxis()->LabelsOption("v");
  BXGlobW0->GetXaxis()->LabelsOption("v");
  BXGlobW1->GetXaxis()->LabelsOption("v");
  BXGlobW2->GetXaxis()->LabelsOption("v");

  MaskedGlobWm2->GetXaxis()->LabelsOption("v");
  MaskedGlobWm1->GetXaxis()->LabelsOption("v");
  MaskedGlobW0->GetXaxis()->LabelsOption("v");
  MaskedGlobW1->GetXaxis()->LabelsOption("v");
  MaskedGlobW2->GetXaxis()->LabelsOption("v");


  EffGlobWm2far->GetXaxis()->LabelsOption("v");
  EffGlobWm1far->GetXaxis()->LabelsOption("v");
  EffGlobW0far->GetXaxis()->LabelsOption("v");
  EffGlobW1far->GetXaxis()->LabelsOption("v");
  EffGlobW2far->GetXaxis()->LabelsOption("v");

  EffGlobWm2far->GetXaxis()->SetLabelSize(0.03);
  EffGlobWm1far->GetXaxis()->SetLabelSize(0.03);
  EffGlobW0far->GetXaxis()->SetLabelSize(0.03);
  EffGlobW1far->GetXaxis()->SetLabelSize(0.03);
  EffGlobW2far->GetXaxis()->SetLabelSize(0.03);

  EffGlobWm2far->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobWm1far->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW0far->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW1far->GetYaxis()->SetRangeUser(0.,100.);
  EffGlobW2far->GetYaxis()->SetRangeUser(0.,100.);
  
  BXGlobWm2far->GetXaxis()->LabelsOption("v");
  BXGlobWm1far->GetXaxis()->LabelsOption("v");
  BXGlobW0far->GetXaxis()->LabelsOption("v");
  BXGlobW1far->GetXaxis()->LabelsOption("v");
  BXGlobW2far->GetXaxis()->LabelsOption("v");

  MaskedGlobWm2far->GetXaxis()->LabelsOption("v");
  MaskedGlobWm1far->GetXaxis()->LabelsOption("v");
  MaskedGlobW0far->GetXaxis()->LabelsOption("v");
  MaskedGlobW1far->GetXaxis()->LabelsOption("v");
  MaskedGlobW2far->GetXaxis()->LabelsOption("v");

  std::cout<<"Efficiency Images"<<std::endl;

  Ca2->SetBottomMargin(0.4);
  
  TGaxis * bxAxis = new TGaxis(102.,0.,102.,100.,-5,5,11,"+L");
  TGaxis * bxAxisFar = new TGaxis(105.,0.,105.,100.,-5,5,11,"+L");

  bxAxis->SetLabelColor(9);
  bxAxis->SetName("bxAxis");
  bxAxis->SetTitle("Mean BX");
  bxAxis->SetTitleColor(9);
  bxAxis->CenterTitle();

  bxAxisFar->SetLabelColor(9);
  bxAxisFar->SetName("bxAxis");
  bxAxisFar->SetTitle("Mean BX");
  bxAxisFar->SetTitleColor(9);
  bxAxisFar->CenterTitle();
  gStyle->SetOptStat(0);

  EffGlobWm2->LabelsDeflate();
  EffGlobWm2->Draw();
  EffGlobWm2->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobWm2->LabelsDeflate();
  BXGlobWm2->SetMarkerColor(9);
  BXGlobWm2->SetLineColor(9);
  BXGlobWm2->Draw("same");

  MaskedGlobWm2->LabelsDeflate();
  MaskedGlobWm2->SetMarkerColor(2);
  MaskedGlobWm2->SetLineColor(2);
  MaskedGlobWm2->Draw("same");

  bxAxis->Draw("same");
  
  Ca2->SaveAs("BxDeadStripEffFromLocalWm2near.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalWm2near.root");
  Ca2->Clear();

  EffGlobWm2far->LabelsDeflate();
  EffGlobWm2far->Draw();
  EffGlobWm2far->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobWm2far->LabelsDeflate();
  BXGlobWm2far->SetMarkerColor(9);
  BXGlobWm2far->SetLineColor(9);
  BXGlobWm2far->Draw("same");

  MaskedGlobWm2far->LabelsDeflate();
  MaskedGlobWm2far->SetMarkerColor(2);
  MaskedGlobWm2far->SetLineColor(2);
  MaskedGlobWm2far->Draw("same");
  
  bxAxisFar->Draw("same");
  
  Ca2->SaveAs("BxDeadStripEffFromLocalWm2far.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalWm2far.root");
  Ca2->Clear();

  EffGlobWm1->LabelsDeflate();
  EffGlobWm1->Draw();
  EffGlobWm1->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobWm1->LabelsDeflate();
  BXGlobWm1->SetMarkerColor(9);
  BXGlobWm1->SetLineColor(9);
  BXGlobWm1->Draw("same");

  MaskedGlobWm1->LabelsDeflate();
  MaskedGlobWm1->SetMarkerColor(2);
  MaskedGlobWm1->SetLineColor(2);
  MaskedGlobWm1->Draw("same");

  bxAxis->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalWm1near.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalWm1near.root");
  Ca2->Clear();

  EffGlobWm1far->LabelsDeflate();
  EffGlobWm1far->Draw();
  EffGlobWm1far->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobWm1far->LabelsDeflate();
  BXGlobWm1far->SetMarkerColor(9);
  BXGlobWm1far->SetLineColor(9);
  BXGlobWm1far->Draw("same");

  MaskedGlobWm1far->LabelsDeflate();
  MaskedGlobWm1far->SetMarkerColor(2);
  MaskedGlobWm1far->SetLineColor(2);
  MaskedGlobWm1far->Draw("same");

  bxAxisFar->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalWm1far.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalWm1far.root");
  Ca2->Clear();

  EffGlobW0->LabelsDeflate();
  EffGlobW0->Draw();
  EffGlobW0->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW0->LabelsDeflate();
  BXGlobW0->SetMarkerColor(9);
  BXGlobW0->SetLineColor(9);
  BXGlobW0->Draw("same");

  MaskedGlobW0->LabelsDeflate();
  MaskedGlobW0->SetMarkerColor(2);
  MaskedGlobW0->SetLineColor(2);
  MaskedGlobW0->Draw("same");

  bxAxis->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalW0near.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW0near.root");
  Ca2->Clear();

  EffGlobW0far->LabelsDeflate();
  EffGlobW0far->Draw();
  EffGlobW0far->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW0far->LabelsDeflate();
  BXGlobW0far->SetMarkerColor(9);
  BXGlobW0far->SetLineColor(9);
  BXGlobW0far->Draw("same");

  MaskedGlobW0far->LabelsDeflate();
  MaskedGlobW0far->SetMarkerColor(2);
  MaskedGlobW0far->SetLineColor(2);
  MaskedGlobW0far->Draw("same");

  bxAxisFar->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalW0far.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW0far.root");
  Ca2->Clear();

  EffGlobW1->LabelsDeflate();
  EffGlobW1->Draw();
  EffGlobW1->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW1->LabelsDeflate();
  BXGlobW1->SetMarkerColor(9);
  BXGlobW1->SetLineColor(9);
  BXGlobW1->Draw("same");

  MaskedGlobW1->LabelsDeflate();
  MaskedGlobW1->SetMarkerColor(2);
  MaskedGlobW1->SetLineColor(2);
  MaskedGlobW1->Draw("same");

  bxAxis->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalW1near.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW1near.root");
  Ca2->Clear();

  EffGlobW1far->LabelsDeflate();
  EffGlobW1far->Draw();
  EffGlobW1far->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW1far->LabelsDeflate();
  BXGlobW1far->SetMarkerColor(9);
  BXGlobW1far->SetLineColor(9);
  BXGlobW1far->Draw("same");

  MaskedGlobW1far->LabelsDeflate();
  MaskedGlobW1far->SetMarkerColor(2);
  MaskedGlobW1far->SetLineColor(2);
  MaskedGlobW1far->Draw("same");

  bxAxisFar->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalW1far.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW1far.root");
  Ca2->Clear();

  EffGlobW2->LabelsDeflate();
  EffGlobW2->Draw();
  EffGlobW2->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW2->LabelsDeflate();
  BXGlobW2->SetMarkerColor(9);
  BXGlobW2->SetLineColor(9);
  BXGlobW2->Draw("same");

  MaskedGlobW2->LabelsDeflate();
  MaskedGlobW2->SetMarkerColor(2);
  MaskedGlobW2->SetLineColor(2);
  MaskedGlobW2->Draw("same");
  
  bxAxis->Draw("same");

  Ca2->SaveAs("BxDeadStripEffFromLocalW2near.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW2near.root");
  Ca2->Clear();
  
  EffGlobW2far->LabelsDeflate();
  EffGlobW2far->Draw();
  EffGlobW2far->GetYaxis()->SetTitle("Efficiency (%)/Dead Strips (%)");
  
  BXGlobW2far->LabelsDeflate();
  BXGlobW2far->SetMarkerColor(9);
  BXGlobW2far->SetLineColor(9);
  BXGlobW2far->Draw("same");

  MaskedGlobW2far->LabelsDeflate();
  MaskedGlobW2far->SetMarkerColor(2);
  MaskedGlobW2far->SetLineColor(2);
  MaskedGlobW2far->Draw("same");
  
  bxAxisFar->Draw("same");
  
  Ca2->SaveAs("BxDeadStripEffFromLocalW2far.png");
  Ca2->SaveAs("BxDeadStripEffFromLocalW2far.root");
  Ca2->Clear();

  theFileOut->cd();

  EffGlobWm2->Write();
  EffGlobWm1->Write();
  EffGlobW0->Write();
  EffGlobW1->Write();
  EffGlobW2->Write();

  EffGlobWm2far->Write();
  EffGlobWm1far->Write();
  EffGlobW0far->Write();
  EffGlobW1far->Write();
  EffGlobW2far->Write();

  BXGlobWm2->Write();
  BXGlobWm1->Write();
  BXGlobW0->Write();
  BXGlobW1->Write();
  BXGlobW2->Write();

  BXGlobWm2far->Write();
  BXGlobWm1far->Write();
  BXGlobW0far->Write();
  BXGlobW1far->Write();
  BXGlobW2far->Write();

  MaskedGlobWm2->Write();
  MaskedGlobWm1->Write();
  MaskedGlobW0->Write();
  MaskedGlobW1->Write();
  MaskedGlobW2->Write();

  MaskedGlobWm2far->Write();
  MaskedGlobWm1far->Write();
  MaskedGlobW0far->Write();
  MaskedGlobW1far->Write();
  MaskedGlobW2far->Write();

  Ca2->Close();
  
  Ca1->Close();
  theFileOut->Close();
  theFile->Close();

}

