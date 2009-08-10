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
  float x[4], ex[4], mask[4];
  
  string line, namesave;
  ofstream hvscaninfo;

  TFile *_file0 = TFile::Open("8800/sec109815.root");
  TFile *_file1 = TFile::Open("9000/sec109815.root");
  TFile *_file2 = TFile::Open("9100/sec109718.root");
  TFile *_file3 = TFile::Open("9200/sec109468.root");
  TFile *_file4 = TFile::Open("9300/sec109578.root");


  string name;
  string roll[4];
  float eff;
  float err;

  ifstream filein;
  ifstream efftxt8800;
  ifstream efftxt9000;
  ifstream efftxt9100;
  ifstream efftxt9200;
  ifstream efftxt9300;

  filein.open("rolls-side-.txt");
  efftxt8800.open("8800/eff-side-.txt");
  efftxt9000.open("9000/eff-side-.txt");
  efftxt9100.open("9100/eff-side-.txt");
  efftxt9200.open("9200/eff-side-.txt");
  efftxt9300.open("9300/eff-side-.txt");
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
    float avEFF[5];
    float avERR[5];
    getline(filein,line);
    //cout <<"In line"<< line << endl;
      
    string Roll = line;
    string name = "Profile_For_" + Roll;
      
    TH1F *HV8800 = (TH1F*)_file0->Get(name.c_str());
    TH1F *HV9000 = (TH1F*)_file1->Get(name.c_str());
    TH1F *HV9100 = (TH1F*)_file2->Get(name.c_str());
    TH1F *HV9200 = (TH1F*)_file3->Get(name.c_str());
    TH1F *HV9300 = (TH1F*)_file4->Get(name.c_str());
      
    if(HV8000&&HV9000&&HV9100&&HV9200&&HV9300){

      efftxt8800 >> roll[0] >> avEFF[0] >> avERR[0] >> mask[0];
      efftxt9000 >> roll[1] >> avEFF[1] >> avERR[1] >> mask[1];
      efftxt9100 >> roll[2] >> avEFF[2] >> avERR[2] >> mask[2];
      efftxt9200 >> roll[3] >> avEFF[3] >> avERR[3] >> mask[3];
      efftxt9300 >> roll[4] >> avEFF[4] >> avERR[4] >> mask[4];
      
      if(! (roll[0].compare(roll[1]) && roll[1].compare(roll[2]) && roll[2].compare(roll[3]) && roll[3].compare(roll[4]) && roll[4].compare(roll[0]))){
	cout<<"All strings Match!!"<<endl;
      }else{
	cout<<"!!!!!!!!!!!!!!! STOP bad matching files !!!!!!!!!!!!"<<endl;
	for(int i=0;i<6;i++) cout<<roll[i]<<" "; cout <<Roll<<endl;
	cout<<roll[0].compare(roll[1]) << roll[1].compare(roll[2]) << roll[2].compare(roll[0])<<endl;
	break;
      }
      
      x[0] = 8.9; //correction for pressure and temperature here
      x[1] = 9.0; //correction for pressure and temperature here
      x[2] = 9.1; //correction for pressure and temperature here
      x[3] = 9.2; //correction for pressure and temperature here
      x[4] = 9.3; //correction for pressure and temperature here

      ex[0] = 0.0001;
      ex[1] = 0.0001;
      ex[2] = 0.0001;
      ex[3] = 0.0001;
      ex[4] = 0.0001;
      
      bool good=true;
      
      for(i=0;i<4;i++){
	//if(avEFF[i]-avEFF[i+1]>5.)good = false;
	if(avEFF[i]==0. || avEFF[i+1]==0.) good = false;
      }
      
      string titlename = "Efficiency vs HV " + Roll; 
      namesave = "GlobalEff.png";
      string foldername = Roll;
      string fullname = foldername + string("/") + namesave;
    
      grp = new TGraphErrors(5, x, avEFF, ex, avERR);
    
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

      TH1F * masked = new TH1F("Masked","Masked",4,8.95,9.35);
      masked->SetBinContent(1,mask[0]);
      masked->SetBinContent(2,mask[1]);
      masked->SetBinContent(3,mask[2]);
      masked->SetBinContent(4,mask[3]);
      masked->SetBinContent(5,mask[4]);
      masked->SetLineColor(kRed);
      masked->Draw();

      masked->GetYaxis()->SetRangeUser(0.,100.);
	      
      fullname = foldername + "/masked.png";
      C1->SaveAs(fullname.c_str());
      C1->Clear();

    
      HV8800->SetLineColor(1);
      HV9000->SetLineColor(2);
      HV9100->SetLineColor(3);
      HV9200->SetLineColor(4);
      HV9300->SetLineColor(5);
    
      HV8800->SetMaximum(1);
      HV9000->SetMaximum(1);
      HV9100->SetMaximum(1);
      HV9200->SetMaximum(1);
      HV9300->SetMaximum(1);
    
      HV8800->Draw();
      HV9000->Draw("same");
      HV9100->Draw("same");
      HV9200->Draw("same");
      HV9300->Draw("same");
    
      string titlename = "Profile " + Roll;
    
      HV8800->SetTitle(titlename.c_str());
      HV8800->GetYaxis()->SetTitle("Efficiency(%)");
    
      namesave = "Profile.png";
      string foldername = Roll;
      string fullname = foldername + string("/") + namesave;
    
      C1->SaveAs(fullname.c_str());
      C1->Clear();

      delete grp;  
      delete f1;
      delete masked;
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
  
  efftxt8800.close();
  efftxt9000.close();
  efftxt9100.close();
  efftxt9200.close();
  efftxt9300.close();

  exit(0);

}
