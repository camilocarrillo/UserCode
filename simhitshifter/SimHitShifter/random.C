#include "TRandom.h"

void random(){

  TRandom *numberGenerator = new TRandom();
  
  float meanRPC = 0.25;
  float sigmaRPC = 5.2;

  float meanDT = 0.;
  float sigmaDT = 2.;

  float meanCSC = 5.;
  float sigmaCSC = 3.;

  std::ofstream RPCtext;
  std::ofstream DTtext;
  std::ofstream CSCtext;

  RPCtext.open("RPC.dat");
  DTtext.open("DT.dat");
  CSCtext.open("CSC.dat");

  TH1F * histoRPC = new TH1F("histoRPC","RPC dToF",101,meanRPC-3*sigmaRPC,meanRPC+3*sigmaRPC);
  TH1F * histoDT = new TH1F("histoDT","DT dToF",101,meanDT-3*sigmaDT,meanDT+3*sigmaDT);
  TH1F * histoCSC = new TH1F("histoCSC","CSC dToF",101,meanCSC-3*sigmaCSC,meanCSC+3*sigmaCSC);

  for(int i=1;i<=2316;i++){
    double valueRPC = numberGenerator->Gaus(meanRPC,sigmaRPC);
    histoRPC->Fill(valueRPC);
    RPCtext<<valueRPC<<endl;
    cout<<valueRPC<<endl;
  }

  for(int i=1;i<=250;i++){
    double valueDT = numberGenerator->Gaus(meanDT,sigmaDT);
    histoDT->Fill(valueDT);
    DTtext<<valueDT<<endl;
    cout<<valueDT<<endl;
  }

  for(int i=1;i<=4284;i++){
    double valueCSC = numberGenerator->Gaus(meanCSC,sigmaCSC);
    histoCSC->Fill(valueCSC);
    CSCtext<<valueCSC<<endl;
    cout<<valueCSC<<endl;
  }

  RPCtext.close();
  DTtext.close();
  CSCtext.close();
  
  TCanvas * Ca0 = new TCanvas("Ca0","Canvas",800,600);
  histoRPC->Draw();
  histoRPC->GetXaxis()->SetTitle("RPC");
  Ca0->SaveAs("RPC.png");
  Ca0->Clear();

  histoDT->Draw();
  histoDT->GetXaxis()->SetTitle("DT");
  Ca0->SaveAs("DT.png");

  Ca0->Clear();

  histoCSC->Draw();
  histoCSC->GetXaxis()->SetTitle("CSC");
  Ca0->SaveAs("CSC.png");

  gSystem->Exec("source toSourceToMergeAllMuon");  

}
