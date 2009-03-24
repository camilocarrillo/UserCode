#include "READINGCANDIDATES.C"

void CALLINGLOOP(){
  
  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HSCP_RPC_CANDIDATE.root");
  if (!f) {
    f = new TFile("HSCP_RPC_CANDIDATE.root");
  }
  tree = (TTree*)gDirectory->Get("HSCP_RPC_CANDIDATE");
  
  READINGCANDIDATES hscpCand(tree);
  hscpCand.Loop();
  
  TFile *f2 = (TFile*)gROOT->GetListOfFiles()->FindObject("HSCP_fromMC.root");
  if (!f2) {
    f2 = new TFile("HSCP_fromMC.root");
  }
  treeMC = (TTree*)gDirectory->Get("HSCP_fromMC");
  
  READINGCANDIDATES hscpMC (treeMC);
  hscpMC.Loop();
  
}
