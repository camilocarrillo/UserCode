#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

void overlapRolls(){
  ifstream rolls;
  /*  rolls.open("2011/rollsBarrel.txt");
  string roll[2172];
  for (int n=0;n<1020;n++){
  //for (int n=0;n<2;n++){
    rolls>>roll[n];
    cout<<"In roll"<<roll[n]<<endl;
    overlapRoll(roll[n]+".txt",true);
  }
  rolls.close();
  */

  rolls.open("2011/rollsEndCap.txt");
  string roll[1152];
  for (int n=0;n<1152;n++){
  //for (int n=0;n<2;n++){
    rolls>>roll[n];
    cout<<"In roll"<<roll[n]<<endl;
    overlapRoll(roll[n]+".txt",false);
  }
  rolls.close();


}

void overlapRoll(string roll, bool barrel){
  const int Nscan1 = 21;
  const int Nscan2 = 8;

  const string pathScan1 = "2010";
  const string pathScan2 = "2011";
  
  float scan1xBarrel[Nscan1], scan1y[Nscan1];
  float scan1xEndCap[Nscan1];

  float scan2xBarrel[Nscan2], scan2y[Nscan2];
  float scan2xEndCap[Nscan2];

  string pointscan1fromLuigi[Nscan1];
  string pointscan2fromLuigi[Nscan2];

  string pointscan1fromEff[Nscan1];
  string pointscan2fromEff[Nscan2];

  ifstream luigi1;
  ifstream luigi2;

  luigi1.open((pathScan1+"/luigi.txt").c_str());
  for (int n=0;n<Nscan1;n++){
    luigi1>>pointscan1fromLuigi[n]>>scan1xBarrel[n]>>scan1xEndCap[n];
  }
  luigi1.close();

  luigi2.open((pathScan2+"/luigi.txt").c_str());
  for (int n=0;n<Nscan2;n++){
    luigi2>>pointscan2fromLuigi[n]>>scan2xBarrel[n]>>scan2xEndCap[n];
  }
  luigi2.close();

  ifstream effscan1;
  ifstream effscan2;
  
  effscan1.open((pathScan1+"/"+roll).c_str());
  for (int n=0;n<Nscan1;n++){
    effscan1>>pointscan1fromEff[n]>>scan1y[n];
  }
  effscan1.close();

  effscan2.open((pathScan2+"/"+roll).c_str());
  for (int n=0;n<Nscan2;n++){
    effscan2>>pointscan2fromEff[n]>>scan2y[n];
  }
  effscan2.close();

  string name = "HV_Scan";

  int k = 0;

  cout<<"scan1"<<endl;
  for(k=0;k<Nscan1;k++){
    cout<<scan1xBarrel[k]<<" "<<scan1y[k]<<endl;
  }

  cout<<"scan2"<<endl;
  for(k=0;k<Nscan2;k++){
    cout<<scan2xBarrel[k]<<" "<<scan2y[k]<<endl;
  }
  
  //TGraphErrors * scan1 = new TGraph(Nscan1,scan1xBarrel,scan1y);
  //TGraphErrors * scan2 = new TGraph(Nscan2,scan2xBarrel,scan2y);

  TGraphErrors * scan1 = new TGraph(Nscan1,scan1xEndCap,scan1y);
  TGraphErrors * scan2 = new TGraph(Nscan2,scan2xEndCap,scan2y);
  
  
  scan1->SetTitle(name.c_str());
  
  scan2->SetMarkerStyle(22);
  scan2->SetMarkerSize(1.0);
  
  scan1->SetMarkerStyle(20);
  scan1->SetMarkerSize(1.0);

  scan1->SetMarkerColor(21);
  scan1->SetMarkerColor(22);
  
  scan1->SetMinimum(0);
  scan1->SetMaximum(100);
  scan2->SetMinimum(0);
  scan2->SetMaximum(100);
  
  // Ca0->DrawFrame(8.8,10,0,100);
 //scan1->Draw("PC");
 //scan2->Draw("APC");

 TCanvas *c1 = new TCanvas("c1","gerrors2",200,10,700,500);
 //c1->SetFillColor(42);
 c1->SetGrid();

 // draw a frame to define the range
 TH1F *hr = c1->DrawFrame(8.5,0,9.8,100);
 hr->SetXTitle("HV(kV)");
 hr->SetYTitle("Efficiency(%)");
 //c1->GetFrame()->SetFillColor(21);
 //c1->GetFrame()->SetBorderSize(12);

 scan2->Draw("P");
 scan1->Draw("P");
  
 scan2->GetXaxis()->SetTitle("HV(kV)");
 scan2->GetYaxis()->SetTitle("Efficiency (%)");

 scan1->GetXaxis()->SetTitle("HV(kV)");
 scan1->GetYaxis()->SetTitle("Efficiency (%)");

 TLegend *leg = new TLegend(0.6,0.45,0.9,0.3);
 leg->AddEntry(scan2,pathScan2.c_str(),"p");
 leg->AddEntry(scan1,pathScan1.c_str(),"p");
 
 leg->Draw("same");

 c1->SaveAs((roll+".png").c_str());

 c1->Clear();

}


