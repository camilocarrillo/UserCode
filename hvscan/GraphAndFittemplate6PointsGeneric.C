#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

Double_t fitfunc( Double_t* _x, Double_t* _par )
{
  Double_t effmax = _par[0];
  Double_t S = _par[1];
  Double_t HV50 = _par[2];

  return effmax / (1.0 + TMath::Exp( S *( _x[0] - HV50 ) ) );
}

Double_t amano(double hv,double S,double emax,double hv50 )
{
  return emax / (1.0 + TMath::Exp( S *( hv - hv50 ) ) );
}


void GraphAndFit(){
  int i, j;
  int NumOfBins_0 = 0, NumOfBins_1 = 0, NumOfBins_2 = 0, NumOfBins_3 = 0;
  float x[5], ex[5], mask[5];
  
  string line, namesave;
  ofstream hvscaninfo;

  std::cout<<"Getting the root files"<<std::endl;

  TFile *_file0 = TFile::Open("-HV1-/sec-RUN1-.root");
  TFile *_file1 = TFile::Open("-HV2-/sec-RUN2-.root");
  TFile *_file2 = TFile::Open("-HV3-/sec-RUN3-.root");
  TFile *_file3 = TFile::Open("-HV4-/sec-RUN4-.root");
  TFile *_file4 = TFile::Open("-HV5-/sec-RUN5-.root");
  TFile *_file5 = TFile::Open("-HV6-/sec-RUN6-.root");


  string name;
  string roll[6];
  float eff;
  float err;

  ifstream filein;
  ifstream efftxt-HV1-;
  ifstream efftxt-HV2-;
  ifstream efftxt-HV3-;
  ifstream efftxt-HV4-;
  ifstream efftxt-HV5-;
  ifstream efftxt-HV6-;

  std::cout<<"Getting the txt files"<<std::endl;

  filein.open("rolls-side-.txt");
  efftxt-HV1-.open("-HV1-/eff-side-.txt");
  efftxt-HV2-.open("-HV2-/eff-side-.txt");
  efftxt-HV3-.open("-HV3-/eff-side-.txt");
  efftxt-HV4-.open("-HV4-/eff-side-.txt");
  efftxt-HV5-.open("-HV5-/eff-side-.txt");
  efftxt-HV6-.open("-HV6-/eff-side-.txt");
  hvscaninfo.open("output-side-.txt");

  TGraphErrors * grp;
  
  TCanvas *C1 = new TCanvas("C1","Global Efficiency",200,10,800,600);
  C1->SetFillColor(10);
  C1->Draw();
  C1->cd();

  TF1 * f1;
  int k=1;


  TH1F * EffBarrel = new TH1F ("EffBarrel","Efficiency Distribution For -side-",40,0.5,100.5);

  TH1F * WPBarrel = new TH1F ("WPBarrel","HV Distribution for -side-",40,8.5,9.5);

  TH1F * EffGlob = new TH1F ("GlobEfficiencyWheel_-side-","Efficiency -side-",-N-,0.5,-N-.5); //101 near
  //TH1F EffGlob = new TH1F ("GlobEfficiencyWheel_-side-","Efficiency -side-",-N-,0.5,-N-.5);  //105 far

  int index = 0;

  std::cout<<"Before the while "<<std::endl;

  while ( !filein.eof()){

    //Masked Strips

    index++;

    f1 = new TF1("f1",fitfunc,8.5,9.5, 3 ); //antes era 3 pero esta bien por que es el numero de parametros del fit

    f1->SetParameter(0, 95.0);
    f1->SetParameter(1, -0.36);
    f1->SetParameter(2, 8.7);

    float EFF_0 = 0, EFF_1 = 0, EFF_2 =0;
    float ERR_0 = 0, ERR_1 = 0, ERR_2 =0;
    float EFFSUM_0 = 0, EFFSUM_1 = 0, EFFSUM_2 = 0;
    float ERRSUM_0 = 0, ERRSUM_1 = 0,  ERRSUM_2 = 0;  
    float sqrtERR_0, sqrtERR_1, sqrtERR_2;
    float avEFF[6];
    float avERR[6];
    getline(filein,line);
    //cout <<"In line"<< line << endl;
      
    string Roll = line;
    string name = "Profile_For_" + Roll;

    std::cout<<"In this roll "<<Roll<<std::endl;
      
    TH1F *HV-HV1- = (TH1F*)_file0->Get(name.c_str());
    TH1F *HV-HV2- = (TH1F*)_file1->Get(name.c_str());
    TH1F *HV-HV3- = (TH1F*)_file2->Get(name.c_str());
    TH1F *HV-HV4- = (TH1F*)_file3->Get(name.c_str());
    TH1F *HV-HV5- = (TH1F*)_file4->Get(name.c_str());
    TH1F *HV-HV6- = (TH1F*)_file5->Get(name.c_str());
    
      
    if(HV-HV1-&&HV-HV2-&&HV-HV3-&&HV-HV4-&&HV-HV5-&&HV-HV6-){

      efftxt-HV1- >> roll[0] >> avEFF[0] >> avERR[0] >> mask[0];
      efftxt-HV2- >> roll[1] >> avEFF[1] >> avERR[1] >> mask[1];
      efftxt-HV3- >> roll[2] >> avEFF[2] >> avERR[2] >> mask[2];
      efftxt-HV4- >> roll[3] >> avEFF[3] >> avERR[3] >> mask[3];
      efftxt-HV5- >> roll[4] >> avEFF[4] >> avERR[4] >> mask[4];
      efftxt-HV6- >> roll[5] >> avEFF[5] >> avERR[5] >> mask[5];

      
      std::cout<<"Comparing strings "<<std::endl;
      if(!(roll[0].compare(roll[1]) && roll[1].compare(roll[2]) && roll[2].compare(roll[3]) && roll[3].compare(roll[4]) && roll[4].compare(roll[5])&& roll[5].compare(roll[0])  )){
	cout<<"All strings Match!!"<<endl;
      }else{
	cout<<"!!!!!!!!!!!!!!! STOP bad matching files !!!!!!!!!!!!"<<endl;
	for(int i=0;i<7;i++) cout<<roll[i]<<" "; cout <<Roll<<endl;
	cout<<roll[0].compare(roll[1]) << roll[1].compare(roll[2]) << roll[2].compare(roll[0])<<endl;
	break;
	exit(0);
      }
      
      x[0] = 8.8; //correction for pressure and temperature here
      x[1] = 9.0; //correction for pressure and temperature here
      x[2] = 9.1; //correction for pressure and temperature here
      x[3] = 9.2; //correction for pressure and temperature here
      x[4] = 9.3; //correction for pressure and temperature here
      x[5] = 9.4; //correction for pressure and temperature here

      ex[0] = 0.0001;
      ex[1] = 0.0001;
      ex[2] = 0.0001;
      ex[3] = 0.0001;
      ex[4] = 0.0001;
      ex[5] = 0.0001;
      
      bool good=true;
      
      for(i=0;i<4;i++){
	if(avEFF[i]==0. || avEFF[i+1]==0.) good = false;
      }
      
      string titlename = "Efficiency vs HV " + Roll; 
      namesave = "GlobalEff.png";
      string foldername = Roll;
      string fullname = foldername + string("/") + namesave;
    
      grp = new TGraphErrors(6, x, avEFF, ex, avERR);
    
      grp->SetTitle(titlename.c_str());
      grp->SetLineColor(kRed);
      grp->SetMarkerStyle(20);
      grp->SetMarkerSize(1.0);
      grp->SetMinimum(-0.01);
      grp->SetMaximum(100);
      grp->GetXaxis()->SetTitle("HV(kV)");
      grp->GetYaxis()->SetTitle("Efficiency(%)");
      grp->Fit(f1);
      
      grp->Draw("AP");
      
      double emax=f1->GetParameter(0);
      
      double parameters[3];
      parameters[0]=emax;
      parameters[1]=f1->GetParameter(1);
      parameters[2]=f1->GetParameter(2);
      
      for(i=0;i<3;i++){
	cout<<"i="<<parameters[i]<<" "<<endl;
      }
    
      double hv[1]={0};
      double wp=0;
      bool found=false;

      //0.05 means 5% belows maximum efficiency
      //0.02 means 2% belows maximum efficiency


      for(hv[0]=8.5;hv[0]<=10.0;hv[0]=hv[0]+0.01){
	if(emax-amano(hv[0],f1->GetParameter(1),f1->GetParameter(0),f1->GetParameter(2))<=0.02*emax && found==false){
	  cout<<hv[0]<< " " <<amano(hv[0],f1->GetParameter(1),f1->GetParameter(0),f1->GetParameter(2))<<" "<<emax<<endl;
	  wp=hv[0];
	  found=true;
	}
      }


      //if(roll[0].compare("W+0_RB2out_S03_Forward") || W+0_RB3+_S10_Forward)
      
      
      //if(emax > 100) good = false; //far from the knee
      //if(emax < 60) good = false;
      
      
      EffGlob->SetBinContent(index,emax);
      EffGlob->GetXaxis()->SetBinLabel(index,roll[0].c_str());
      
      string cond = "bad";
      if(good){
	cond  = "good";
	EffBarrel->Fill(emax);
	WPBarrel->Fill(wp);
      }

      hvscaninfo<<Roll<<" "<<wp<<" "<<emax<<" "<<cond<<" roll scan"<<endl;
	    
      gSystem->mkdir(foldername.c_str());
      C1->SaveAs(fullname.c_str());
      C1->Clear();

      TH1F * masked = new TH1F("Masked","Masked",6,8.75,9.45); //cambiar 
      masked->SetBinContent(1,mask[0]);
      masked->SetBinContent(2,mask[1]);
      masked->SetBinContent(3,mask[2]);
      masked->SetBinContent(4,mask[3]);
      masked->SetBinContent(5,mask[4]);
      masked->SetBinContent(6,mask[5]);
      masked->SetLineColor(kRed);
      masked->Draw();

      masked->GetYaxis()->SetRangeUser(0.,100.);
	      
      fullname = foldername + "/masked.png";
      C1->SaveAs(fullname.c_str());
      C1->Clear();

      
      HV-HV1-->SetLineColor(1);
      HV-HV2-->SetLineColor(2);
      HV-HV3-->SetLineColor(3);
      HV-HV4-->SetLineColor(4);
      HV-HV5-->SetLineColor(5);
      HV-HV6-->SetLineColor(6);
    
      HV-HV1-->SetMaximum(1);
      HV-HV2-->SetMaximum(1);
      HV-HV3-->SetMaximum(1);
      HV-HV4-->SetMaximum(1);
      HV-HV5-->SetMaximum(1);
      HV-HV6-->SetMaximum(1);
    
      HV-HV1-->Draw();
      HV-HV2-->Draw("same");
      HV-HV3-->Draw("same");
      HV-HV4-->Draw("same");
      HV-HV5-->Draw("same");
      HV-HV6-->Draw("same");
    
      string titlename = "Profile " + Roll;
    
      HV-HV1-->SetTitle(titlename.c_str());
      HV-HV1-->GetYaxis()->SetTitle("Efficiency(%)");
    
      namesave = "Profile.png";
      string foldername = Roll;
      string fullname = foldername + string("/") + namesave;
    
      C1->SaveAs(fullname.c_str());
      C1->Clear();

      delete grp;  
      delete f1;
      delete masked;
    }else{
      std::cout<<"ONE OF THE HISTOGRAMS DOESNT EXIST"<<std::endl;
      continue ;
    }
	   
  }

  C1->Clear();
  EffBarrel->SaveAs("effDistro-side-.root");
  EffBarrel->GetXaxis()->SetTitle("%"); EffBarrel->Draw(); C1->SaveAs("effDistro-side-.png");

  C1->Clear();
  WPBarrel->SaveAs("wp-side-.root");
  WPBarrel->GetXaxis()->SetTitle("knee(V)"); WPBarrel->Draw(); C1->SaveAs("wp-side-.png");

  C1->Clear();
  EffGlob->Draw();
  EffGlob->GetXaxis()->LabelsOption("v");
  EffGlob->GetXaxis()->SetLabelSize(0.03);
  EffGlob->GetYaxis()->SetRangeUser(0.,100.);
  EffGlob->GetYaxis()->SetTitle("%");
  EffGlob->SaveAs("effGlob-side-.root");

  C1->SaveAs("effGlobCa-side-.root");
  C1->SaveAs("effGlob-side-.png");
      
  hvscaninfo.close();
  
  efftxt-HV1-.close();
  efftxt-HV2-.close();
  efftxt-HV3-.close();
  efftxt-HV4-.close();
  efftxt-HV5-.close();
  efftxt-HV6-.close();

  exit(0);

}
