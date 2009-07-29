{
gROOT->Reset();

#include "Riostream.h"
#include<fstream>



//Parametros de entrada-------------------------------------------

 TFile * theFile2 = new TFile("108624/eff108624.root");
 TFile * theFile2sec = new TFile("108624/sec108624.root");

 TFile * theFile1 = new TFile("108671/eff108671.root"); 
 TFile * theFile1sec = new TFile("108671/sec108671.root"); 

 std::string string2 = "210mV_Run_108624"; //should be short!!!
 std::string string1 = "220mV_Run_108671";

//Parametros de entrada------------------------------------------

 std::string folder = string1+"Vs"+string2+"/";
 system(("mkdir "+folder).c_str());
 system(("mkdir "+folder+"Sides").c_str());
 system(("mkdir "+folder+"Distro").c_str());

 std::stringstream sta1; 
 std::stringstream sta2; 

 std::cout<<"Creating Canvas"<<std::endl;
 TCanvas *Ca1 = new TCanvas("Ca1","Plots",800,600);
 gStyle->SetOptStat(0);

//// Clu 1

 std::cout<<"Reading DistBorderClu1La1"<<std::endl;
 TH1F * DistBorderClu1La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La1"));
 TH1F * DistBorderClu1La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La1"<<std::endl;
 DistBorderClu1La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La1"<<std::endl;
 DistBorderClu1La11->SetMarkerColor(9);
 DistBorderClu1La11->SetLineColor(9);
 DistBorderClu1La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu1La1Comp.png").c_str());

 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu1La2"<<std::endl;
 TH1F * DistBorderClu1La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La2"));
 TH1F * DistBorderClu1La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La2"<<std::endl;
 DistBorderClu1La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La2"<<std::endl;
 DistBorderClu1La21->SetMarkerColor(9);
 DistBorderClu1La21->SetLineColor(9);
 DistBorderClu1La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La21->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La22->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu1La2Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu1La6"<<std::endl;
 TH1F * DistBorderClu1La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La6"));
 TH1F * DistBorderClu1La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La6"<<std::endl;
 DistBorderClu1La62->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La6"<<std::endl;
 DistBorderClu1La61->SetMarkerColor(9);
 DistBorderClu1La61->SetLineColor(9);
 DistBorderClu1La61->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La61->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La62->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu1La6Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

///// Clu 2

 std::cout<<"Reading DistBorderClu2La1"<<std::endl;
 TH1F * DistBorderClu2La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La1"));
 TH1F * DistBorderClu2La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La1"<<std::endl;
 DistBorderClu2La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La1"<<std::endl;
 DistBorderClu2La11->SetMarkerColor(9);
 DistBorderClu2La11->SetLineColor(9);
 DistBorderClu2La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu2La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu2La1Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu2La2"<<std::endl;
 TH1F * DistBorderClu2La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La2"));
 TH1F * DistBorderClu2La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La2"<<std::endl;
 DistBorderClu2La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La2"<<std::endl;
 DistBorderClu2La21->SetMarkerColor(9);
 DistBorderClu2La21->SetLineColor(9);
 DistBorderClu2La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La21->GetMean()<<" RMS="<<DistBorderClu1La21->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La22->GetMean()<<" RMS="<<DistBorderClu1La22->GetRMS();
 leg->AddEntry(DistBorderClu2La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu2La2Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu2La6"<<std::endl;
 TH1F * DistBorderClu2La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La6"));
 TH1F * DistBorderClu2La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La6"<<std::endl;
 std::cout<<"DrawNormalizeding second DistBorderClu2La6"<<std::endl;
 DistBorderClu2La61->SetMarkerColor(9);
 DistBorderClu2La61->SetLineColor(9);
 DistBorderClu2La61->DrawNormalized("");
 DistBorderClu2La62->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La61->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La62->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(DistBorderClu2La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu2La6Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

/////

///// Clu 3

 std::cout<<"Reading DistBorderClu3La1"<<std::endl;
 TH1F * DistBorderClu3La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La1"));
 TH1F * DistBorderClu3La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La1"<<std::endl;
 DistBorderClu3La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La1"<<std::endl;
 DistBorderClu3La11->SetMarkerColor(9);
 DistBorderClu3La11->SetLineColor(9);
 DistBorderClu3La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu3La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu3La1Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu3La2"<<std::endl;
 TH1F * DistBorderClu3La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La2"));
 TH1F * DistBorderClu3La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La2"<<std::endl;
 DistBorderClu3La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La2"<<std::endl;
 DistBorderClu3La21->SetMarkerColor(9);
 DistBorderClu3La21->SetLineColor(9);
 DistBorderClu3La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La21->GetMean()<<" RMS="<<DistBorderClu1La21->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La22->GetMean()<<" RMS="<<DistBorderClu1La22->GetRMS();
 leg->AddEntry(DistBorderClu3La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu3La2Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu3La6"<<std::endl;
 TH1F * DistBorderClu3La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La6"));
 TH1F * DistBorderClu3La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La6"<<std::endl;
 std::cout<<"DrawNormalizeding second DistBorderClu3La6"<<std::endl;
 DistBorderClu3La61->SetMarkerColor(9);
 DistBorderClu3La61->SetLineColor(9);
 DistBorderClu3La61->DrawNormalized("");
 DistBorderClu3La62->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La61->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La62->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(DistBorderClu3La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"DistBorderClu3La6Comp.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

/////


// Global Residuals Layer 1

 std::cout<<"Reading GlobalResiduals"<<std::endl;
 TH1F * GlobalResidualsClu1La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La1"));
 TH1F * GlobalResidualsClu2La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La1"));
 TH1F * GlobalResidualsClu3La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La1"));

 TH1F * GlobalResidualsLa11 = GlobalResidualsClu1La11->Clone();
 GlobalResidualsLa11->Add(GlobalResidualsClu2La11);
 GlobalResidualsLa11->Add(GlobalResidualsClu3La11);

 TH1F * GlobalResidualsClu1La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La1"));
 TH1F * GlobalResidualsClu2La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La1"));
 TH1F * GlobalResidualsClu3La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La1"));
 TH1F * GlobalResidualsLa12 = GlobalResidualsClu1La12->Clone();
 GlobalResidualsLa12->Add(GlobalResidualsClu2La12);
 GlobalResidualsLa12->Add(GlobalResidualsClu3La12);

 std::cout<<"Global Residuals  first AllLa11"<<std::endl;
 GlobalResidualsLa12->DrawNormalized("");
 std::cout<<"Global Residuals second AllLa12"<<std::endl;
 GlobalResidualsLa11->SetMarkerColor(9);
 GlobalResidualsLa11->SetLineColor(9);
 GlobalResidualsLa11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.8,0.9,0.6);
 leg->AddEntry(GlobalResidualsLa11,string1.c_str(),"l");  
 leg->AddEntry(GlobalResidualsLa12,string2.c_str(),"l");
 leg->Draw("same");
 Ca1->SaveAs((folder+"GlobalResidualsLa1Comp.png").c_str());
 Ca1->Clear();

//// Global Residuals Layer 6

 std::cout<<"Reading GlobalResiduals"<<std::endl;
 TH1F * GlobalResidualsClu1La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La6"));
 TH1F * GlobalResidualsClu2La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La6"));
 TH1F * GlobalResidualsClu3La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La6"));

 TH1F * GlobalResidualsLa61 = GlobalResidualsClu1La61->Clone();
 GlobalResidualsLa61->Add(GlobalResidualsClu2La61);
 GlobalResidualsLa61->Add(GlobalResidualsClu3La61);

 TH1F * GlobalResidualsClu1La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La6"));
 TH1F * GlobalResidualsClu2La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La6"));
 TH1F * GlobalResidualsClu3La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La6"));
 TH1F * GlobalResidualsLa62 = GlobalResidualsClu1La62->Clone();
 GlobalResidualsLa62->Add(GlobalResidualsClu2La62);
 GlobalResidualsLa62->Add(GlobalResidualsClu3La62);

 std::cout<<"Global Residuals  first AllLa61"<<std::endl;
 GlobalResidualsLa62->DrawNormalized("");
 std::cout<<"Global Residuals second AllLa62"<<std::endl;
 GlobalResidualsLa61->SetMarkerColor(9);
 GlobalResidualsLa61->SetLineColor(9);
 GlobalResidualsLa61->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.8,0.9,0.6);
 leg->AddEntry(GlobalResidualsLa61,string1.c_str(),"l");  
 leg->AddEntry(GlobalResidualsLa62,string2.c_str(),"l");
 leg->Draw("same");
 Ca1->SaveAs((folder+"GlobalResidualsLa6Comp.png").c_str());
 Ca1->Clear();


///// EffBarrel and others

 std::cout<<"Reading PinoBarrel"<<std::endl;
 TH1F * PinoBarrel1 = (TH1F*) (theFile1sec->Get("PinoBarrel"));
 TH1F * PinoBarrel2 = (TH1F*) (theFile2sec->Get("PinoBarrel"));
 std::cout<<"Drawing first PinoBarrel"<<std::endl;
 PinoBarrel2->Draw("");
 std::cout<<"Drawing second PinoBarrel"<<std::endl;
 PinoBarrel1->SetMarkerColor(9);
 PinoBarrel1->SetLineColor(9);
 PinoBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<PinoBarrel1->GetMean()<<" RMS="<<PinoBarrel1->GetRMS();
 sta2<<"Mean="<<PinoBarrel2->GetMean()<<" RMS="<<PinoBarrel2->GetRMS();
 leg->AddEntry(PinoBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(PinoBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(PinoBarrel2,string2.c_str(),"l");
 leg->AddEntry(PinoBarrel2,(sta1.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/PinoBarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading PinoEndCap"<<std::endl;
 TH1F * PinoEndCap1 = (TH1F*) (theFile1sec->Get("PinoEndCap"));
 TH1F * PinoEndCap2 = (TH1F*) (theFile2sec->Get("PinoEndCap"));
 std::cout<<"Drawing first PinoEndCap"<<std::endl;
 PinoEndCap2->Draw("");
 std::cout<<"Drawing second PinoEndCap"<<std::endl;
 PinoEndCap1->SetMarkerColor(9);
 PinoEndCap1->SetLineColor(9);
 PinoEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<PinoEndCap1->GetMean()<<" RMS="<<PinoEndCap1->GetRMS();
 sta2<<"Mean="<<PinoEndCap2->GetMean()<<" RMS="<<PinoEndCap2->GetRMS();
 leg->AddEntry(PinoEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(PinoEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(PinoEndCap2,string2.c_str(),"l");
 leg->AddEntry(PinoEndCap2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/PinoEndCap.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading EffBarrel"<<std::endl;
 TH1F * EffBarrel1 = (TH1F*) (theFile1sec->Get("EffBarrel"));
 TH1F * EffBarrel2 = (TH1F*) (theFile2sec->Get("EffBarrel"));
 std::cout<<"Drawing first EffBarrel"<<std::endl;
 EffBarrel2->Draw("");
 std::cout<<"Drawing second EffBarrel"<<std::endl;
 EffBarrel1->SetMarkerColor(9);
 EffBarrel1->SetLineColor(9);
 EffBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<EffBarrel1->GetMean()<<" RMS="<<EffBarrel1->GetRMS();
 sta2<<"Mean="<<EffBarrel2->GetMean()<<" RMS="<<EffBarrel2->GetRMS();
 leg->AddEntry(EffBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(EffBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(EffBarrel2,string2.c_str(),"l");
 leg->AddEntry(EffBarrel2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/EffDistroBarrel.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Pino EndCap"<<std::endl;
 TH1F * EffEndCap1 = (TH1F*) (theFile1sec->Get("EffDistroEndCap"));
 TH1F * EffEndCap2 = (TH1F*) (theFile2sec->Get("EffDistroEndCap"));
 std::cout<<"Drawing first EffEndCap"<<std::endl;
 EffEndCap2->Draw("");
 std::cout<<"Drawing second EffEndCap"<<std::endl;
 EffEndCap1->SetMarkerColor(9);
 EffEndCap1->SetLineColor(9);
 EffEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<EffEndCap1->GetMean()<<" RMS="<<EffEndCap1->GetRMS();
 sta2<<"Mean="<<EffEndCap2->GetMean()<<" RMS="<<EffEndCap2->GetRMS();
 leg->AddEntry(EffEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(EffEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(EffEndCap2,string2.c_str(),"l");
 leg->AddEntry(EffEndCap2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/EffDistroEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DoubleGapBarrel"<<std::endl;
 TH1F * DoubleGapBarrel1 = (TH1F*) (theFile1sec->Get("DoubleGapBarrel"));
 TH1F * DoubleGapBarrel2 = (TH1F*) (theFile2sec->Get("DoubleGapBarrel"));
 std::cout<<"Drawing first DoubleGapBarrel"<<std::endl;
 DoubleGapBarrel2->Draw("");
 std::cout<<"Drawing second DoubleGapBarrel"<<std::endl;
 DoubleGapBarrel1->SetMarkerColor(9);
 DoubleGapBarrel1->SetLineColor(9);
 DoubleGapBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<DoubleGapBarrel1->GetMean()<<" RMS="<<DoubleGapBarrel1->GetRMS();
 sta2<<"Mean="<<DoubleGapBarrel2->GetMean()<<" RMS="<<DoubleGapBarrel2->GetRMS();
 leg->AddEntry(DoubleGapBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(DoubleGapBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DoubleGapBarrel2,string2.c_str(),"l");
 leg->AddEntry(DoubleGapBarrel2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/DoubleGapBarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DoubleGapEndCap"<<std::endl;
 TH1F * DoubleGapEndCap1 = (TH1F*) (theFile1sec->Get("DoubleGapEndCap"));
 TH1F * DoubleGapEndCap2 = (TH1F*) (theFile2sec->Get("DoubleGapEndCap"));
 std::cout<<"Drawing first DoubleGapEndCap"<<std::endl;
 DoubleGapEndCap2->Draw("");
 std::cout<<"Drawing second DoubleGapEndCap"<<std::endl;
 DoubleGapEndCap1->SetMarkerColor(9);
 DoubleGapEndCap1->SetLineColor(9);
 DoubleGapEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<DoubleGapEndCap1->GetMean()<<" RMS="<<DoubleGapEndCap1->GetRMS();
 sta2<<"Mean="<<DoubleGapEndCap2->GetMean()<<" RMS="<<DoubleGapEndCap2->GetRMS();
 leg->AddEntry(DoubleGapEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(DoubleGapEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DoubleGapEndCap2,string2.c_str(),"l");
 leg->AddEntry(DoubleGapEndCap2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/DoubleGapEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading BXBarrel"<<std::endl;
 TH2F * BXBarrel1 = (TH2F*) (theFile1sec->Get("BXBarrel"));
 TH2F * BXBarrel2 = (TH2F*) (theFile2sec->Get("BXBarrel"));
 std::cout<<"Drawing first BXBarrel"<<std::endl;
 BXBarrel2->Draw("");
 std::cout<<"Drawing second BXBarrel"<<std::endl;
 BXBarrel1->SetMarkerColor(9);
 BXBarrel1->SetLineColor(9);
 BXBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<BXBarrel1->GetMean()<<" RMS="<<BXBarrel1->GetRMS();
 sta2<<"Mean="<<BXBarrel2->GetMean()<<" RMS="<<BXBarrel2->GetRMS();
 leg->AddEntry(BXBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(BXBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXBarrel2,string2.c_str(),"l");
 leg->AddEntry(BXBarrel2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"bxbarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading BXEndCap"<<std::endl;
 TH2F * BXEndCap1 = (TH2F*) (theFile1sec->Get("BXEndCap"));
 TH2F * BXEndCap2 = (TH2F*) (theFile2sec->Get("BXEndCap"));
 std::cout<<"Drawing first BXEndCap"<<std::endl;
 BXEndCap2->Draw("");
 std::cout<<"Drawing second BXEndCap"<<std::endl;
 BXEndCap1->SetMarkerColor(9);
 BXEndCap1->SetLineColor(9);
 BXEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.8,0.5,0.6);
 sta1<<"Mean="<<BXEndCap1->GetMean()<<" RMS="<<BXEndCap1->GetRMS();
 sta2<<"Mean="<<BXEndCap2->GetMean()<<" RMS="<<BXEndCap2->GetRMS();
 leg->AddEntry(BXEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(BXEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXEndCap2,string2.c_str(),"l");
 leg->AddEntry(BXEndCap2,(sta1.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"bxendcap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 TCanvas *Ca2 = new TCanvas("Ca2","Global Efficiency",1200,600);

 Ca2->SetBottomMargin(0.4);

 //-------------------------------------------------all far sides -----------------------------------------------------------------------------------------------------------

 std::cout<<"Reading AverageEfficiencyWheel_-2far"<<std::endl;
 TH1F * AverageEfficiencyWheel_m2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-2far"));
 TH1F * AverageEfficiencyWheel_m2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-2far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-2far"<<std::endl;
 AverageEfficiencyWheel_m2far2->Draw("");
 AverageEfficiencyWheel_m2far2->GetYaxis()->SetTitle("%");
 std::cout<<"Drawing second AverageEfficiencyWheel_-2far"<<std::endl;
 AverageEfficiencyWheel_m2far1->SetMarkerColor(9);
 AverageEfficiencyWheel_m2far1->SetLineColor(9);
 AverageEfficiencyWheel_m2far1->Draw("same");
 
 AverageEfficiencyWheel_m2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m2far2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm2far.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyWheel_-1far"<<std::endl;
 TH1F * AverageEfficiencyWheel_m1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-1far"));
 TH1F * AverageEfficiencyWheel_m1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-1far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-1far"<<std::endl;
 AverageEfficiencyWheel_m1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_-1far"<<std::endl;
 AverageEfficiencyWheel_m1far1->SetMarkerColor(9);
 AverageEfficiencyWheel_m1far1->SetLineColor(9);
 AverageEfficiencyWheel_m1far1->Draw("same");

 AverageEfficiencyWheel_m1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m1far2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm1far.png").c_str());
 sta1.str("");
 sta2.str("");


 
 std::cout<<"Reading AverageEfficiencyWheel_0far"<<std::endl;
 TH1F * AverageEfficiencyWheel_0far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_0far"));
 TH1F * AverageEfficiencyWheel_0far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_0far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_0far"<<std::endl;
 AverageEfficiencyWheel_0far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_0far"<<std::endl;
 AverageEfficiencyWheel_0far1->SetMarkerColor(9);
 AverageEfficiencyWheel_0far1->SetLineColor(9);
 AverageEfficiencyWheel_0far1->Draw("same");

 AverageEfficiencyWheel_0far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_0far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_0far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_0far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_0far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_0far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_0far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_0far2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W0far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_1far"<<std::endl;
 TH1F * AverageEfficiencyWheel_1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_1far"));
 TH1F * AverageEfficiencyWheel_1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_1far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_1far"<<std::endl;
 AverageEfficiencyWheel_1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_1far"<<std::endl;
 AverageEfficiencyWheel_1far1->SetMarkerColor(9);
 AverageEfficiencyWheel_1far1->SetLineColor(9);
 AverageEfficiencyWheel_1far1->Draw("same");

 AverageEfficiencyWheel_1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_1far2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W1far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_2far"<<std::endl;
 TH1F * AverageEfficiencyWheel_2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_2far"));
 TH1F * AverageEfficiencyWheel_2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_2far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_2far"<<std::endl;
 AverageEfficiencyWheel_2far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_2far"<<std::endl;
 AverageEfficiencyWheel_2far1->SetMarkerColor(9);
 AverageEfficiencyWheel_2far1->SetLineColor(9);
 AverageEfficiencyWheel_2far1->Draw("same");

 AverageEfficiencyWheel_2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_2far2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W2far.png").c_str());
 sta1.str("");
 sta2.str("");



////

 //all near sides

 std::cout<<"Reading AverageEfficiencyWheel_-2near"<<std::endl;
 TH1F * AverageEfficiencyWheel_m2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-2near"));
 TH1F * AverageEfficiencyWheel_m2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-2near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-2near"<<std::endl;
 AverageEfficiencyWheel_m2near2->Draw("");
 AverageEfficiencyWheel_m2near2->GetYaxis()->SetTitle("%");
 std::cout<<"Drawing second AverageEfficiencyWheel_-2near"<<std::endl;
 AverageEfficiencyWheel_m2near1->SetMarkerColor(9);
 AverageEfficiencyWheel_m2near1->SetLineColor(9);
 AverageEfficiencyWheel_m2near1->Draw("same");
 
 AverageEfficiencyWheel_m2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m2near2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm2near.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyWheel_-1near"<<std::endl;
 TH1F * AverageEfficiencyWheel_m1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-1near"));
 TH1F * AverageEfficiencyWheel_m1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-1near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-1near"<<std::endl;
 AverageEfficiencyWheel_m1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_-1near"<<std::endl;
 AverageEfficiencyWheel_m1near1->SetMarkerColor(9);
 AverageEfficiencyWheel_m1near1->SetLineColor(9);
 AverageEfficiencyWheel_m1near1->Draw("same");

 AverageEfficiencyWheel_m1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m1near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m1near2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm1near.png").c_str());
 sta1.str("");
 sta2.str("");

 
 std::cout<<"Reading AverageEfficiencyWheel_0near"<<std::endl;
 TH1F * AverageEfficiencyWheel_0near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_0near"));
 TH1F * AverageEfficiencyWheel_0near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_0near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_0near"<<std::endl;
 AverageEfficiencyWheel_0near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_0near"<<std::endl;
 AverageEfficiencyWheel_0near1->SetMarkerColor(9);
 AverageEfficiencyWheel_0near1->SetLineColor(9);
 AverageEfficiencyWheel_0near1->Draw("same");

 AverageEfficiencyWheel_0near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_0near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_0near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_0near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_0near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_0near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_0near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_0near2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W0near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_1near"<<std::endl;
 TH1F * AverageEfficiencyWheel_1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_1near"));
 TH1F * AverageEfficiencyWheel_1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_1near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_1near"<<std::endl;
 AverageEfficiencyWheel_1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_1near"<<std::endl;
 AverageEfficiencyWheel_1near1->SetMarkerColor(9);
 AverageEfficiencyWheel_1near1->SetLineColor(9);
 AverageEfficiencyWheel_1near1->Draw("same");

 AverageEfficiencyWheel_1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_1near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_1near2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W1near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_2near"<<std::endl;
 TH1F * AverageEfficiencyWheel_2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_2near"));
 TH1F * AverageEfficiencyWheel_2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_2near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_2near"<<std::endl;
 AverageEfficiencyWheel_2near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_2near"<<std::endl;
 AverageEfficiencyWheel_2near1->SetMarkerColor(9);
 AverageEfficiencyWheel_2near1->SetLineColor(9);
 AverageEfficiencyWheel_2near1->Draw("same");

 AverageEfficiencyWheel_2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_2near2,(sta1.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W2near.png").c_str());
 sta1.str("");
 sta2.str("");

////

 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/MainIndex.html >"+folder+"/MainIndex.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/index.html >"+folder+"/index.html").c_str());

// Ca1->Clear();
// Ca1->Close();

}

//Open root y dentro del promt de root simplemente 
//root [0] .x macroProdPlotsXYeY.C

