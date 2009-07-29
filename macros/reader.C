void reader(){
  TFile *f1 = new TFile("testsingle.root");
  TTree *Events = (TTree*) f1->Get("Events");
  Events->ls();
}
