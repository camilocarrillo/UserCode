#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <efficiencyFunctions.C>

void higgs_hlt(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  const int n = 17;

  float etascale_base[n] = {-2.4, -2.1, -1.6, -1.2, -0.9, -0.6, -0.3,-0.2,0,0.2,0.3,0.6,0.9,1.2,1.6,2.1,2.4};

  float etascale[n-1];

  for(k=0;k<n-1;k++){
    etascale[k]=(etascale_base[k]+etascale_base[k+1])*0.5;
  }

  TCanvas * Ca0 = new TCanvas("Ca0","2D efficiency",1200,800);

  string name = "Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATA";

  TH2F * histoDATA = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoDATA->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoDATA->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoDATA->SetBinContent(i,j,Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATA(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATA(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoDATA->Draw(); histoDATA->GetXaxis()->SetTitle("#eta 1"); histoDATA->GetYaxis()->SetTitle("#eta 2"); histoDATA->GetXaxis()->LabelsOption("h"); histoDATA->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_MC";

  TH2F * histoMC = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoMC->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoMC->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoMC->SetBinContent(i,j,Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_MC(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_MC(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoMC->Draw(); histoMC->GetXaxis()->SetTitle("#eta 1"); histoMC->GetYaxis()->SetTitle("#eta 2"); histoMC->GetXaxis()->LabelsOption("h"); histoMC->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC";

  TH2F * histoDATAoverMC = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoDATAoverMC->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoDATAoverMC->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoDATAoverMC->SetBinContent(i,j,Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoDATAoverMC->Draw(); histoDATAoverMC->GetXaxis()->SetTitle("#eta 1"); histoDATAoverMC->GetYaxis()->SetTitle("#eta 2"); histoDATAoverMC->GetXaxis()->LabelsOption("h"); histoDATAoverMC->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC_manual";

  TH2F * myratio = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    myratio->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    myratio->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      myratio->SetBinContent(i,j,histoDATA->GetBinContent(i,j)/histoMC->GetBinContent(i,j));
    }
  }
  myratio->Draw(); myratio->GetXaxis()->SetTitle("#eta 1"); myratio->GetYaxis()->SetTitle("#eta 2"); myratio->GetXaxis()->LabelsOption("h"); myratio->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //-----------------------------------------------------------------------------------------------------------

  string name = "Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATA";

  TH2F * histoDATA = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoDATA->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoDATA->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoDATA->SetBinContent(i,j,Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATA(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATA(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoDATA->Draw(); histoDATA->GetXaxis()->SetTitle("#eta 1"); histoDATA->GetYaxis()->SetTitle("#eta 2"); histoDATA->GetXaxis()->LabelsOption("h"); histoDATA->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_MC";

  TH2F * histoMC = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoMC->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoMC->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoMC->SetBinContent(i,j,Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_MC(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_MC(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoMC->Draw(); histoMC->GetXaxis()->SetTitle("#eta 1"); histoMC->GetYaxis()->SetTitle("#eta 2"); histoMC->GetXaxis()->LabelsOption("h"); histoMC->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC";

  TH2F * histoDATAoverMC = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    histoDATAoverMC->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    histoDATAoverMC->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      histoDATAoverMC->SetBinContent(i,j,Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(etascale[i-1],etascale[j-1]));
      cout<<i<<","<<j<<","<<Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(etascale[i-1],etascale[j-1])<<endl;
    }
  }
  histoDATAoverMC->Draw(); histoDATAoverMC->GetXaxis()->SetTitle("#eta 1"); histoDATAoverMC->GetYaxis()->SetTitle("#eta 2"); histoDATAoverMC->GetXaxis()->LabelsOption("h"); histoDATAoverMC->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

  //--

  string name = "Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC_manual";

  TH2F * myratio = new TH2F(name.c_str(),name.c_str(),n-1,0.5,n-.5,n-1,0.5,n-.5);
  std::stringstream buffer_string;
  for(k=0;k<n-1;k++){
    buffer_string.str("");
    buffer_string<<etascale[k];
    myratio->GetXaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
    myratio->GetYaxis()->SetBinLabel(k+1,buffer_string.str().c_str());
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      myratio->SetBinContent(i,j,histoDATA->GetBinContent(i,j)/histoMC->GetBinContent(i,j));
    }
  }
  myratio->Draw(); myratio->GetXaxis()->SetTitle("#eta 1"); myratio->GetYaxis()->SetTitle("#eta 2"); myratio->GetXaxis()->LabelsOption("h"); myratio->SetDrawOption("COLZ");
  Ca0->SaveAs((name+".png").c_str()); Ca0->Clear();

}

