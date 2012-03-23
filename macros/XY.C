#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void XY(){
  int i, j;
  const int n = 8;	
  float x[n], y[n];

  ifstream data;

  string name = "gluinoXsection";
  data.open((name+".txt").c_str());

  int k = 0;

  TH2F * histo = new TH2F("","",20,8.0,10.0,100,0,100);

  while(!data.eof() && k<n){
    data>>x[k]>>y[k];
    cout<<x[k]<<" "<<y[k]<<endl;
    hist->Fill(x[k],y[k]);
    k++;
  }
  
 Wheel0Summary->SetMinimum(0); 
  Wheel0Summary->SetMaximum(100);
  Wheel0Summary->Draw();
  Wheel0Summary->GetXaxis()->LabelsOption("h");
  Wheel0Summary->SetDrawOption("COLZ");
  Wheel0Summary->GetXaxis()->SetLabelSize(0.035);

  
}
