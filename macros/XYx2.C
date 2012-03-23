#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void XY(){
  const int n = 6;	
  float x[n], y[n];

  ifstream data;

  string name = "stopXsection";
  data.open((name+".txt").c_str());

  int k = 0;

  while(!data.eof() && k<n){
    data>>x[k]>>y[k];
    cout<<x[k]<<" "<<y[k]<<endl;
    k++;
  }
  
    TGraphErrors * grp = new TGraph(n,x,y);
    
    TCanvas * Ca0 = new TCanvas("Ca0","Canvas",1200,800);    

    grp->SetTitle(name.c_str());
    grp->SetLineColor(kRed);
    grp->SetMarkerStyle(20);
    grp->SetMarkerSize(1.0);
    grp->SetMinimum(1.0e-05);
    grp->SetMaximum(400);
    grp->GetXaxis()->SetTitle("stop mass(GeV)");
    grp->GetYaxis()->SetTitle("Cross Section (pb)");
    grp->Draw("AP");
            
}
