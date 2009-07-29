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
  
  TFile *_file0 = TFile::Open("9000/67838.root");
  TFile *_file1 = TFile::Open("9100/68288.root");
  TFile *_file2 = TFile::Open("9200/66594.root");
  TFile *_file3 = TFile::Open("9300/67647.root");
  
  string name;
  string file;
  
  for(l=1;l<=10;l++){
    if(l==1){
      name = "GlobMaskedWheel_-2near";
      file = "rollsWm2near.txt";
    }else if(l==2){
      name = "GlobMaskedWheel_-2far";
      file = "rollsWm2far.txt";
    }else if(l==3){
      name = "GlobMaskedWheel_-1near";
      file = "rollsWm1near.txt";
    }else if(l==4){
      name = "GlobMaskedWheel_-1far";
      file = "rollsWm1far.txt";
    }else if(l==5){
      name = "GlobMaskedWheel_0near";
      file = "rollsW0near.txt";
    }else if(l==6){
      name = "GlobMaskedWheel_0far";
      file = "rollsW0far.txt";
    }else if(l==7){
      name = "GlobMaskedWheel_1near";
      file = "rollsW1near.txt";
    }else if(l==8){
      name = "GlobMaskedWheel_1far";
      file = "rollsW1far.txt";
    }else if(l==9){
      name = "GlobMaskedWheel_2near";
      file = "rollsW2near.txt";
    }else if(l==10){
      name = "GlobMaskedWheel_2far";
      file = "rollsW2far.txt";
    }
    
  ifstream filein;
  //filein.open("rollsW2far.txt");
  filein.open(file.c_str());
  string output = "output" + file;
  hvscaninfo.open(output.c_str());

  TH1F * masked0 = (TH1F*) (_file0->Get(name.c_str()));
  TH1F * masked1 = (TH1F*) (_file1->Get(name.c_str()));
  TH1F * masked2 = (TH1F*) (_file2->Get(name.c_str()));
  TH1F * masked3 = (TH1F*) (_file3->Get(name.c_str()));
  
  //cout<<"roll size"<<masked0->TH1F::GetNbinsX()<<endl;
  
  TGraphErrors * grp;
  
  TCanvas *C1 = new TCanvas("C1","Global Efficiency",200,10,800,600);
  C1->SetFillColor(10);
  C1->Draw();
  C1->cd();

  TF1 * f1;
  int k=1;

  while ( !filein.eof()){

    //Masked Strips

    f1 = new TF1("f1",fitfunc,8.5,9.5, 3 );
            
    f1->SetParameter(0, 80.0);
    f1->SetParameter(1, 100);
    f1->SetParameter(2, 8.9);

    float EFF_0 = 0, EFF_1 = 0, EFF_2 =0 , EFF_3 = 0;
    float ERR_0 = 0, ERR_1 = 0, ERR_2 =0 , ERR_3 = 0;
    float EFFSUM_0 = 0, EFFSUM_1 = 0, EFFSUM_2 = 0, EFFSUM_3 = 0;
    float ERRSUM_0 = 0, ERRSUM_1 = 0,  ERRSUM_2 = 0,  ERRSUM_3 = 0;  
    float sqrtERR_0, sqrtERR_1, sqrtERR_2, sqrtERR_3;
    float avEFF[4];
    float avERR[4];
    getline(filein,line);
    //cout <<"In line"<< line << endl;
      
    string Roll = line;
    string name = "Profile_For_" + Roll;
      
    TH1F *HV9000 = (TH1F*)_file0->Get(name.c_str());
    TH1F *HV9100 = (TH1F*)_file1->Get(name.c_str());
    TH1F *HV9200 = (TH1F*)_file2->Get(name.c_str());
    TH1F *HV9300 = (TH1F*)_file3->Get(name.c_str());
      
    NumOfBins_0 = HV9000->TH1F::GetNbinsX();
    NumOfBins_1 = HV9100->TH1F::GetNbinsX();
    NumOfBins_2 = HV9200->TH1F::GetNbinsX();
    NumOfBins_3 = HV9300->TH1F::GetNbinsX();
      
    for(i = 1; i <= NumOfBins_0; ++i){
      EFF_0 = HV9000->GetBinContent(i);
      ERR_0 = HV9000->GetBinError(i);
      EFFSUM_0 += EFF_0;  
      ERRSUM_0 += ERR_0*ERR_0;
    }
    avEFF[0] = 100.*EFFSUM_0/NumOfBins_0;
    sqrtERR_0 = sqrt(ERRSUM_0);
    avERR[0] = 100.*sqrtERR_0/NumOfBins_0;
      
    for(i = 1; i <= NumOfBins_1; ++i){
      EFF_1 = HV9100->GetBinContent(i); 
      ERR_1 = HV9100->GetBinError(i);
      EFFSUM_1 += EFF_1;
      ERRSUM_1 += ERR_1*ERR_1;
    }
    avEFF[1] = 100.*EFFSUM_1/NumOfBins_1;
    sqrtERR_1 = sqrt(ERRSUM_1);
    avERR[1] = 100.*sqrtERR_1/NumOfBins_1;
      
    for(i = 1; i <= NumOfBins_2; ++i){
      EFF_2 = HV9200->GetBinContent(i);
      ERR_2 = HV9200->GetBinError(i);
      EFFSUM_2 += EFF_2;
      ERRSUM_2 += ERR_2*ERR_2;
    }
    avEFF[2] = 100.*EFFSUM_2/NumOfBins_2;
    sqrtERR_2 = sqrt(ERRSUM_2);
    avERR[2] = 100.*sqrtERR_2/NumOfBins_2;
      
    for(i = 1; i <= NumOfBins_3; ++i){
      EFF_3 = HV9300->GetBinContent(i);
      ERR_3 = HV9300->GetBinError(i);
      EFFSUM_3 += EFF_3;
      ERRSUM_3 += ERR_3*ERR_3;
    }
    avEFF[3] = 100.*EFFSUM_3/NumOfBins_3;
    sqrtERR_3 = sqrt(ERRSUM_3);
    avERR[3] = 100.*sqrtERR_3/NumOfBins_3;
      
    x[0] = 9.0;
    x[1] = 9.1;
    x[2] = 9.2;
    x[3] = 9.3;

    ex[0] = 0;
    ex[1] = 0;
    ex[2] = 0;
    ex[3] = 0;
      
    bool good=true;
      
    for(i=0;i<3;i++){
      if(avEFF[i]-avEFF[i+1]>5.)good = false;
      if(avEFF[i]==0. || avEFF[i+1]==0.) good = false;
    }
      
    if(!good){
      //cout<<Roll<<" bad scan"<<endl;
    }else{
      //cout<<Roll<<" good scan"<<endl;
    }

    //cout << x[0] <<" : " << avEFF[0] << "------" << avERR[0] << endl;
    //cout << x[1] <<" : " << avEFF[1] << "------" << avERR[1] << endl;
    //cout << x[2] <<" : " << avEFF[2] << "------" << avERR[2] << endl;
    //cout << x[3] <<" : " << avEFF[3] << "------" << avERR[3] << endl;
      
    string titlename = "Efficiency vs HV " + Roll; 
    namesave = "GlobalEff.png";
    string foldername = Roll;
    string fullname = foldername + string("/") + namesave;
    
    grp = new TGraphErrors(4, x, avEFF, ex, avERR);
    
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

    for(hv[0]=8.5;hv[0]<=9.7;hv[0]=hv[0]+0.01){
      if(emax-amano(hv[0],f1->GetParameter(1),f1->GetParameter(0),f1->GetParameter(2))<=0.05 && found==false){
	cout<<hv[0]<< " " <<amano(hv[0],f1->GetParameter(1),f1->GetParameter(0),f1->GetParameter(2))<<" "<<emax<<endl;
    	wp=hv[0];
	found=true;
      }
    }
    
    string cond = "bad";
    if(good){
      cond  = "good";
    }

    hvscaninfo<<Roll<<" "<<wp<<" "<<emax<<" "<<cond<<" roll scan"<<endl;
	    
    TH1F * masked = new TH1F("Masked","Masked",4,8.95,9.35);
    masked->SetBinContent(1,masked0->GetBinContent(k));
    masked->SetBinContent(2,masked1->GetBinContent(k));
    masked->SetBinContent(3,masked2->GetBinContent(k));
    masked->SetBinContent(4,masked3->GetBinContent(k));
    masked->SetLineColor(kRed);
    masked->Draw("same");
         
    gSystem->mkdir(foldername.c_str());
    C1->SaveAs(fullname.c_str());
    C1->Clear();
    
    HV9000->SetLineColor(1);
    HV9100->SetLineColor(2);
    HV9200->SetLineColor(3);
    HV9300->SetLineColor(9);
    
    HV9000->SetMaximum(1);
    HV9100->SetMaximum(1);
    HV9200->SetMaximum(1);
    HV9300->SetMaximum(1);
    
    HV9000->Draw();
    HV9100->Draw("same");
    HV9200->Draw("same");
    HV9300->Draw("same"); 
    
    string titlename = "Profile " + Roll;
    
    HV9000->SetTitle(titlename.c_str());
    HV9000->GetYaxis()->SetTitle("Efficiency(%)");
    
    namesave = "Profile.png";
    string foldername = Roll;
    string fullname = foldername + string("/") + namesave;
    
    C1->SaveAs(fullname.c_str());
    C1->Clear();

    delete grp;  
    delete f1;
    delete masked;
    k++;
  }
  hvscaninfo.close();
  }
}
