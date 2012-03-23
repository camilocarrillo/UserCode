#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void XYall(){
  float stopx[5], stopy[5];
  float gluix[6], gluiy[6];
  float staux[6], stauy[6];
  ifstream data;

  string name = "Cross_Section";

  int k = 0;
  staux[0]=100 ; stauy[0]=1.34;
  staux[1]=126 ; stauy[1]=3.35e-1;
  staux[2]=156 ; stauy[2]=9.85e-2;
  staux[3]=200 ; stauy[3]=2.26e-2;
  staux[4]=247 ; stauy[4]=7.75e-3;
  staux[5]=308 ; stauy[5]=2.14e-3;

  gluix[0]=200 ; gluiy[0]=3.27e+2;
  gluix[1]=300 ; gluiy[1]=2.77e+1;
  gluix[2]=600 ; gluiy[2]=1.71e-1;
  gluix[3]=900 ; gluiy[3]=3.94e-3;
  gluix[4]=1200; gluiy[4]=1.69e-4;
  gluix[5]=1500; gluiy[5]=1.11e-5;

  stopx[0]=130 ; stopy[0]=6.55e+1;
  stopx[1]=200 ; stopy[1]=6.83e+0;
  stopx[2]=300 ; stopy[2]=6.48e-1;
  stopx[3]=500 ; stopy[3]=2.29e-2;
  stopx[4]=800 ; stopy[4]=5.42e-4;

 TGraphErrors * stau = new TGraph(6,staux,stauy);
 TGraphErrors * glui = new TGraph(6,gluix,gluiy);
 TGraphErrors * stop = new TGraph(5,stopx,stopy);

 TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);

 Ca0->SetLogy();

 stau->SetTitle(name.c_str());

 glui->SetMarkerStyle(22);
 glui->SetMarkerSize(2.0);

 stop->SetMarkerStyle(23);
 stop->SetMarkerSize(2.0);

 stau->SetMarkerStyle(20);
 stau->SetMarkerSize(2.0);

 stau->SetMinimum(1.0e-06);
 stau->SetMaximum(400);
 glui->SetMinimum(1.0e-06);
 glui->SetMaximum(400);
 stop->SetMinimum(1.0e-06);
 stop->SetMaximum(400);

 //Ca0->DrawFrame(0,1.0e-06,1500,400);

 // glui->Draw("APC");
 // stop->Draw("PC");
 stau->Draw("APC");

 Ca0->Modified();
 Ca0->Update();

 
 glui->GetXaxis()->SetTitle("mass(GeV/c^{2})");
 glui->GetYaxis()->SetTitle("#sigma (pb)");

 stop->GetXaxis()->SetTitle("mass(GeV/c^{2})");
 stop->GetYaxis()->SetTitle("#sigma (pb)");

 stau->GetXaxis()->SetTitle("mass(GeV/c^{2})");
 stau->GetYaxis()->SetTitle("#sigma (pb)");

 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 //leg->AddEntry(glui,"gluino split-SUSY","lp");
 //leg->AddEntry(stop,"stop MSSM","lp");
 leg->AddEntry(stau,"stau mGMSB","lp");
 
 leg->Draw("same");

 Ca0->SaveAs("StauXSection.png");

}


