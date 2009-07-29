{
//Files
gROOT->Reset();
TFile * theFile = new TFile("/tmp/carrillo/RPCEfficiency.root");
TFile * theFileOut = new TFile("RPCEfficiencyAll.root","RECREATE");

theFileOut->cd();

float fontsize = 0.018;
float bottonMarging = 0.18;
int CanvaSizeX = 1200;
int CanvaSizeY = 600;

//Begin to Get the files

//Disk -3 near
TH1F * NoPredictionDm3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/NoPredictionDisk_m3near");
TH1F * AverageEffDm3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/AverageEfficiencyDisk_m3near");
TH1F * EffGlobDm3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobEfficiencyDisk_m3near");
TH1F * BXGlobDm3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobBXDisk_m3near");
TH1F * MaskedGlobDm3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobMaskedDisk_m3near");

//Disk -3 far
TH1F * NoPredictionDm3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/NoPredictionDisk_m3far");
TH1F * AverageEffDm3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/AverageEfficiencyDisk_m3far");
TH1F * EffGlobDm3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobEfficiencyDisk_m3far");
TH1F * BXGlobDm3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobBXDisk_m3far");
TH1F * MaskedGlobDm3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-3/GlobMaskedDisk_m3far");

//Disk -2 near
TH1F * NoPredictionDm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/NoPredictionDisk_m2near");
TH1F * AverageEffDm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/AverageEfficiencyDisk_m2near");
TH1F * EffGlobDm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobEfficiencyDisk_m2near");
TH1F * BXGlobDm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobBXDisk_m2near");
TH1F * MaskedGlobDm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobMaskedDisk_m2near");

//Disk -2 far
TH1F * NoPredictionDm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/NoPredictionDisk_m2far");
TH1F * AverageEffDm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/AverageEfficiencyDisk_m2far");
TH1F * EffGlobDm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobEfficiencyDisk_m2far");
TH1F * BXGlobDm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobBXDisk_m2far");
TH1F * MaskedGlobDm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-2/GlobMaskedDisk_m2far");

//Disk -1 near
TH1F * NoPredictionDm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/NoPredictionDisk_m1near");
TH1F * AverageEffDm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/AverageEfficiencyDisk_m1near");
TH1F * EffGlobDm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobEfficiencyDisk_m1near");
TH1F * BXGlobDm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobBXDisk_m1near");
TH1F * MaskedGlobDm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobMaskedDisk_m1near");

//Disk -1 far
TH1F * NoPredictionDm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/NoPredictionDisk_m1far");
TH1F * AverageEffDm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/AverageEfficiencyDisk_m1far");
TH1F * EffGlobDm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobEfficiencyDisk_m1far");
TH1F * BXGlobDm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobBXDisk_m1far");
TH1F * MaskedGlobDm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_-1/GlobMaskedDisk_m1far");


//Wheel -2 near
TH1F * NoPredictionWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/NoPredictionWheel_-2near");
TH1F * AverageEffWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/AverageEfficiencyWheel_-2near");
TH1F * EffGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobEfficiencyWheel_-2near");
TH1F * BXGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobBXWheel_-2near");
TH1F * MaskedGlobWm2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobMaskedWheel_-2near");

//Wheel -2 far
TH1F * NoPredictionWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/NoPredictionWheel_-2far");
TH1F * AverageEffWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/AverageEfficiencyWheel_-2far");
TH1F * EffGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobEfficiencyWheel_-2far");
TH1F * BXGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobBXWheel_-2far");
TH1F * MaskedGlobWm2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-2/GlobMaskedWheel_-2far");

//Wheel -1 near
TH1F * NoPredictionWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/NoPredictionWheel_-1near");
TH1F * AverageEffWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/AverageEfficiencyWheel_-1near");
TH1F * EffGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobEfficiencyWheel_-1near");
TH1F * BXGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobBXWheel_-1near");
TH1F * MaskedGlobWm1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobMaskedWheel_-1near");

//Wheel -1 far
TH1F * NoPredictionWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/NoPredictionWheel_-1far");
TH1F * AverageEffWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/AverageEfficiencyWheel_-1far");
TH1F * EffGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobEfficiencyWheel_-1far");
TH1F * BXGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobBXWheel_-1far");
TH1F * MaskedGlobWm1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_-1/GlobMaskedWheel_-1far");

//Wheel 0 near
TH1F * NoPredictionW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/NoPredictionWheel_0near");
TH1F * AverageEffW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/AverageEfficiencyWheel_0near");
TH1F * EffGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobEfficiencyWheel_0near");
TH1F * BXGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobBXWheel_0near");
TH1F * MaskedGlobW0 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobMaskedWheel_0near");

//Wheel 0 far
TH1F * NoPredictionW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/NoPredictionWheel_0far");
TH1F * AverageEffW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/AverageEfficiencyWheel_0far");
TH1F * EffGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobEfficiencyWheel_0far");
TH1F * BXGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobBXWheel_0far");
TH1F * MaskedGlobW0far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_0/GlobMaskedWheel_0far");

//Wheel 1 near

TH1F * NoPredictionW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/NoPredictionWheel_1near");
TH1F * AverageEffW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/AverageEfficiencyWheel_1near");
TH1F * EffGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobEfficiencyWheel_1near");
TH1F * BXGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobBXWheel_1near");
TH1F * MaskedGlobW1 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobMaskedWheel_1near");

//Wheel 1 far
TH1F * NoPredictionW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/NoPredictionWheel_1far");
TH1F * AverageEffW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/AverageEfficiencyWheel_1far");
TH1F * EffGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobEfficiencyWheel_1far");
TH1F * BXGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobBXWheel_1far");
TH1F * MaskedGlobW1far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_1/GlobMaskedWheel_1far");

//Wheel 2 near
TH1F * NoPredictionW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/NoPredictionWheel_2near");
TH1F * AverageEffW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/AverageEfficiencyWheel_2near");
TH1F * EffGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobEfficiencyWheel_2near");
TH1F * BXGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobBXWheel_2near");
TH1F * MaskedGlobW2 = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobMaskedWheel_2near");

//Wheel 2 far
TH1F * NoPredictionW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/NoPredictionWheel_2far");
TH1F * AverageEffW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/AverageEfficiencyWheel_2far");
TH1F * EffGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobEfficiencyWheel_2far");
TH1F * BXGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobBXWheel_2far");
TH1F * MaskedGlobW2far = theFile->Get("DQMData/Muons/RPCEfficiency/Wheel_2/GlobMaskedWheel_2far");


//Disk +1 near
TH1F * NoPredictionD1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/NoPredictionDisk_1near");
TH1F * AverageEffD1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/AverageEfficiencyDisk_1near");
TH1F * EffGlobD1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobEfficiencyDisk_1near");
TH1F * BXGlobD1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobBXDisk_1near");
TH1F * MaskedGlobD1 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobMaskedDisk_1near");

//Disk +1 far
TH1F * NoPredictionD1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/NoPredictionDisk_1far");
TH1F * AverageEffD1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/AverageEfficiencyDisk_1far");
TH1F * EffGlobD1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobEfficiencyDisk_1far");
TH1F * BXGlobD1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobBXDisk_1far");
TH1F * MaskedGlobD1far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_1/GlobMaskedDisk_1far");


//Disk +2 near
TH1F * NoPredictionD2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/NoPredictionDisk_2near");
TH1F * AverageEffD2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/AverageEfficiencyDisk_2near");
TH1F * EffGlobD2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobEfficiencyDisk_2near");
TH1F * BXGlobD2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobBXDisk_2near");
TH1F * MaskedGlobD2 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobMaskedDisk_2near");

//Disk +2 far
TH1F * NoPredictionD2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/NoPredictionDisk_2far");
TH1F * AverageEffD2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/AverageEfficiencyDisk_2far");
TH1F * EffGlobD2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobEfficiencyDisk_2far");
TH1F * BXGlobD2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobBXDisk_2far");
TH1F * MaskedGlobD2far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_2/GlobMaskedDisk_2far");

//Disk +3 near
TH1F * NoPredictionD3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/NoPredictionDisk_3near");
TH1F * AverageEffD3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/AverageEfficiencyDisk_3near");
TH1F * EffGlobD3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobEfficiencyDisk_3near");
TH1F * BXGlobD3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobBXDisk_3near");
TH1F * MaskedGlobD3 = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobMaskedDisk_3near");

//Disk +3 far
TH1F * NoPredictionD3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/NoPredictionDisk_3far");
TH1F * AverageEffD3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/AverageEfficiencyDisk_3far");
TH1F * EffGlobD3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobEfficiencyDisk_3far");
TH1F * BXGlobD3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobBXDisk_3far");
TH1F * MaskedGlobD3far = theFile->Get("DQMData/Muons/RPCEfficiency/Disk_3/GlobMaskedDisk_3far");


//end to get the files

Ca1 = new TCanvas("Ca1","Efficiency",CanvaSizeX,CanvaSizeY);
Ca2 = new TCanvas("Ca2","Global Efficiency",1200,CanvaSizeY);

//Barrel

EffGlobWm2->GetXaxis()->LabelsOption("v");
EffGlobWm1->GetXaxis()->LabelsOption("v");
EffGlobW0->GetXaxis()->LabelsOption("v");
EffGlobW1->GetXaxis()->LabelsOption("v");
EffGlobW2->GetXaxis()->LabelsOption("v");

EffGlobWm2->GetXaxis()->SetLabelSize(0.03);
EffGlobWm1->GetXaxis()->SetLabelSize(0.03);
EffGlobW0->GetXaxis()->SetLabelSize(0.03);
EffGlobW1->GetXaxis()->SetLabelSize(0.03);
EffGlobW2->GetXaxis()->SetLabelSize(0.03);

EffGlobWm2->GetYaxis()->SetRangeUser(0.,100.);
EffGlobWm1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW0->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW2->GetYaxis()->SetRangeUser(0.,100.);
  
BXGlobWm2->GetXaxis()->LabelsOption("v");
BXGlobWm1->GetXaxis()->LabelsOption("v");
BXGlobW0->GetXaxis()->LabelsOption("v");
BXGlobW1->GetXaxis()->LabelsOption("v");
BXGlobW2->GetXaxis()->LabelsOption("v");

MaskedGlobWm2->GetXaxis()->LabelsOption("v");
MaskedGlobWm1->GetXaxis()->LabelsOption("v");
MaskedGlobW0->GetXaxis()->LabelsOption("v");
MaskedGlobW1->GetXaxis()->LabelsOption("v");
MaskedGlobW2->GetXaxis()->LabelsOption("v");

EffGlobWm2far->GetXaxis()->LabelsOption("v");
EffGlobWm1far->GetXaxis()->LabelsOption("v");
EffGlobW0far->GetXaxis()->LabelsOption("v");
EffGlobW1far->GetXaxis()->LabelsOption("v");
EffGlobW2far->GetXaxis()->LabelsOption("v");

EffGlobWm2far->GetXaxis()->SetLabelSize(0.03);
EffGlobWm1far->GetXaxis()->SetLabelSize(0.03);
EffGlobW0far->GetXaxis()->SetLabelSize(0.03);
EffGlobW1far->GetXaxis()->SetLabelSize(0.03);
EffGlobW2far->GetXaxis()->SetLabelSize(0.03);

EffGlobWm2far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobWm1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW0far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobW2far->GetYaxis()->SetRangeUser(0.,100.);
  
BXGlobWm2far->GetXaxis()->LabelsOption("v");
BXGlobWm1far->GetXaxis()->LabelsOption("v");
BXGlobW0far->GetXaxis()->LabelsOption("v");
BXGlobW1far->GetXaxis()->LabelsOption("v");
BXGlobW2far->GetXaxis()->LabelsOption("v");

MaskedGlobWm2far->GetXaxis()->LabelsOption("v");
MaskedGlobWm1far->GetXaxis()->LabelsOption("v");
MaskedGlobW0far->GetXaxis()->LabelsOption("v");
MaskedGlobW1far->GetXaxis()->LabelsOption("v");
MaskedGlobW2far->GetXaxis()->LabelsOption("v");

AverageEffWm2->GetXaxis()->LabelsOption("v");
AverageEffWm1->GetXaxis()->LabelsOption("v");
AverageEffW0->GetXaxis()->LabelsOption("v");
AverageEffW1->GetXaxis()->LabelsOption("v");
AverageEffW2->GetXaxis()->LabelsOption("v");

AverageEffWm2far->GetXaxis()->LabelsOption("v");
AverageEffWm1far->GetXaxis()->LabelsOption("v");
AverageEffW0far->GetXaxis()->LabelsOption("v");
AverageEffW1far->GetXaxis()->LabelsOption("v");
AverageEffW2far->GetXaxis()->LabelsOption("v");

NoPredictionWm2->GetXaxis()->LabelsOption("v");
NoPredictionWm1->GetXaxis()->LabelsOption("v");
NoPredictionW0->GetXaxis()->LabelsOption("v");
NoPredictionW1->GetXaxis()->LabelsOption("v");
NoPredictionW2->GetXaxis()->LabelsOption("v");

NoPredictionWm2far->GetXaxis()->LabelsOption("v");
NoPredictionWm1far->GetXaxis()->LabelsOption("v");
NoPredictionW0far->GetXaxis()->LabelsOption("v");
NoPredictionW1far->GetXaxis()->LabelsOption("v");
NoPredictionW2far->GetXaxis()->LabelsOption("v");


NoPredictionDm3->GetXaxis()->LabelsOption("v");
AverageEffDm3->GetXaxis()->LabelsOption("v");
EffGlobDm3->GetXaxis()->LabelsOption("v");
BXGlobDm3->GetXaxis()->LabelsOption("v");
MaskedGlobDm3->GetXaxis()->LabelsOption("v");
NoPredictionDm3far->GetXaxis()->LabelsOption("v");
AverageEffDm3far->GetXaxis()->LabelsOption("v");
EffGlobDm3far->GetXaxis()->LabelsOption("v");
BXGlobDm3far->GetXaxis()->LabelsOption("v");
MaskedGlobDm3far->GetXaxis()->LabelsOption("v");
NoPredictionDm2->GetXaxis()->LabelsOption("v");
AverageEffDm2->GetXaxis()->LabelsOption("v");
EffGlobDm2->GetXaxis()->LabelsOption("v");
BXGlobDm2->GetXaxis()->LabelsOption("v");
MaskedGlobDm2->GetXaxis()->LabelsOption("v");
NoPredictionDm2far->GetXaxis()->LabelsOption("v");
AverageEffDm2far->GetXaxis()->LabelsOption("v");
EffGlobDm2far->GetXaxis()->LabelsOption("v");
BXGlobDm2far->GetXaxis()->LabelsOption("v");
MaskedGlobDm2far->GetXaxis()->LabelsOption("v");
NoPredictionDm1->GetXaxis()->LabelsOption("v");
AverageEffDm1->GetXaxis()->LabelsOption("v");
EffGlobDm1->GetXaxis()->LabelsOption("v");
BXGlobDm1->GetXaxis()->LabelsOption("v");
MaskedGlobDm1->GetXaxis()->LabelsOption("v");
NoPredictionDm1far->GetXaxis()->LabelsOption("v");
AverageEffDm1far->GetXaxis()->LabelsOption("v");
EffGlobDm1far->GetXaxis()->LabelsOption("v");
BXGlobDm1far->GetXaxis()->LabelsOption("v");
MaskedGlobDm1far->GetXaxis()->LabelsOption("v");
NoPredictionD1->GetXaxis()->LabelsOption("v");
AverageEffD1->GetXaxis()->LabelsOption("v");
EffGlobD1->GetXaxis()->LabelsOption("v");
BXGlobD1->GetXaxis()->LabelsOption("v");
MaskedGlobD1->GetXaxis()->LabelsOption("v");
NoPredictionD1far->GetXaxis()->LabelsOption("v");
AverageEffD1far->GetXaxis()->LabelsOption("v");
EffGlobD1far->GetXaxis()->LabelsOption("v");
BXGlobD1far->GetXaxis()->LabelsOption("v");
MaskedGlobD1far->GetXaxis()->LabelsOption("v");
NoPredictionD2->GetXaxis()->LabelsOption("v");
AverageEffD2->GetXaxis()->LabelsOption("v");
EffGlobD2->GetXaxis()->LabelsOption("v");
BXGlobD2->GetXaxis()->LabelsOption("v");
MaskedGlobD2->GetXaxis()->LabelsOption("v");
NoPredictionD2far->GetXaxis()->LabelsOption("v");
AverageEffD2far->GetXaxis()->LabelsOption("v");
EffGlobD2far->GetXaxis()->LabelsOption("v");
BXGlobD2far->GetXaxis()->LabelsOption("v");
MaskedGlobD2far->GetXaxis()->LabelsOption("v");
NoPredictionD3->GetXaxis()->LabelsOption("v");
AverageEffD3->GetXaxis()->LabelsOption("v");
EffGlobD3->GetXaxis()->LabelsOption("v");
BXGlobD3->GetXaxis()->LabelsOption("v");
MaskedGlobD3->GetXaxis()->LabelsOption("v");
NoPredictionD3far->GetXaxis()->LabelsOption("v");
AverageEffD3far->GetXaxis()->LabelsOption("v");
EffGlobD3far->GetXaxis()->LabelsOption("v");
BXGlobD3far->GetXaxis()->LabelsOption("v");
MaskedGlobD3far->GetXaxis()->LabelsOption("v");

NoPredictionDm3->GetXaxis()->SetLabelSize(0.03);
AverageEffDm3->GetXaxis()->SetLabelSize(0.03);
EffGlobDm3->GetXaxis()->SetLabelSize(0.03);
BXGlobDm3->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm3->GetXaxis()->SetLabelSize(0.03);
NoPredictionDm3far->GetXaxis()->SetLabelSize(0.03);
AverageEffDm3far->GetXaxis()->SetLabelSize(0.03);
EffGlobDm3far->GetXaxis()->SetLabelSize(0.03);
BXGlobDm3far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm3far->GetXaxis()->SetLabelSize(0.03);
NoPredictionDm2->GetXaxis()->SetLabelSize(0.03);
AverageEffDm2->GetXaxis()->SetLabelSize(0.03);
EffGlobDm2->GetXaxis()->SetLabelSize(0.03);
BXGlobDm2->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm2->GetXaxis()->SetLabelSize(0.03);
NoPredictionDm2far->GetXaxis()->SetLabelSize(0.03);
AverageEffDm2far->GetXaxis()->SetLabelSize(0.03);
EffGlobDm2far->GetXaxis()->SetLabelSize(0.03);
BXGlobDm2far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm2far->GetXaxis()->SetLabelSize(0.03);
NoPredictionDm1->GetXaxis()->SetLabelSize(0.03);
AverageEffDm1->GetXaxis()->SetLabelSize(0.03);
EffGlobDm1->GetXaxis()->SetLabelSize(0.03);
BXGlobDm1->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm1->GetXaxis()->SetLabelSize(0.03);
NoPredictionDm1far->GetXaxis()->SetLabelSize(0.03);
AverageEffDm1far->GetXaxis()->SetLabelSize(0.03);
EffGlobDm1far->GetXaxis()->SetLabelSize(0.03);
BXGlobDm1far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobDm1far->GetXaxis()->SetLabelSize(0.03);
NoPredictionD1->GetXaxis()->SetLabelSize(0.03);
AverageEffD1->GetXaxis()->SetLabelSize(0.03);
EffGlobD1->GetXaxis()->SetLabelSize(0.03);
BXGlobD1->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD1->GetXaxis()->SetLabelSize(0.03);
NoPredictionD1far->GetXaxis()->SetLabelSize(0.03);
AverageEffD1far->GetXaxis()->SetLabelSize(0.03);
EffGlobD1far->GetXaxis()->SetLabelSize(0.03);
BXGlobD1far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD1far->GetXaxis()->SetLabelSize(0.03);
NoPredictionD2->GetXaxis()->SetLabelSize(0.03);
AverageEffD2->GetXaxis()->SetLabelSize(0.03);
EffGlobD2->GetXaxis()->SetLabelSize(0.03);
BXGlobD2->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD2->GetXaxis()->SetLabelSize(0.03);
NoPredictionD2far->GetXaxis()->SetLabelSize(0.03);
AverageEffD2far->GetXaxis()->SetLabelSize(0.03);
EffGlobD2far->GetXaxis()->SetLabelSize(0.03);
BXGlobD2far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD2far->GetXaxis()->SetLabelSize(0.03);
NoPredictionD3->GetXaxis()->SetLabelSize(0.03);
AverageEffD3->GetXaxis()->SetLabelSize(0.03);
EffGlobD3->GetXaxis()->SetLabelSize(0.03);
BXGlobD3->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD3->GetXaxis()->SetLabelSize(0.03);
NoPredictionD3far->GetXaxis()->SetLabelSize(0.03);
AverageEffD3far->GetXaxis()->SetLabelSize(0.03);
EffGlobD3far->GetXaxis()->SetLabelSize(0.03);
BXGlobD3far->GetXaxis()->SetLabelSize(0.03);
MaskedGlobD3far->GetXaxis()->SetLabelSize(0.03);

NoPredictionDm3->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm3->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm3->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm3->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionDm3far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm3far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm3far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm3far->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionDm2->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm2->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm2->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm2->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionDm2far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm2far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm2far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm2far->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionDm1->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm1->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm1->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionDm1far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffDm1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobDm1far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobDm1far->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD1->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD1->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD1->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD1->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD1far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD1far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD1far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD1far->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD2->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD2->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD2->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD2->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD2far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD2far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD2far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD2far->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD3->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD3->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD3->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD3->GetYaxis()->SetRangeUser(0.,100.);
NoPredictionD3far->GetYaxis()->SetRangeUser(0.,100.);
AverageEffD3far->GetYaxis()->SetRangeUser(0.,100.);
EffGlobD3far->GetYaxis()->SetRangeUser(0.,100.);
MaskedGlobD3far->GetYaxis()->SetRangeUser(0.,100.);

std::cout<<"Efficiency Images"<<std::endl;

pave = new TPaveText(35,119,60,102);
TText *t1=pave->AddText("BX Distribution (Right Axis ->)");
t1->SetTextColor(9);
TText *t2=pave->AddText("Average Efficiency (%)");
t2->SetTextColor(8);
TText *t3=pave->AddText("Integral Efficiency (%)");
//black
TText *t4=pave->AddText("Strips without Data (ratio)"); 
t4->SetTextColor(2);
TText *t5=pave->AddText("Strips Never Pointed for a Segment (ratio)");
t5->SetTextColor(5);

pave->SetFillColor(18);

t1->SetTextSize(0.019);
t2->SetTextSize(0.019);
t3->SetTextSize(0.019);
t4->SetTextSize(0.019);
t5->SetTextSize(0.019);

Ca2->SetBottomMargin(0.4);
  
TGaxis * bxAxis = new TGaxis(104.,0.,104.,100.,-5,5,11,"+L");
TGaxis * bxAxisFar = new TGaxis(108.,0.,108.,100.,-5,5,11,"+L");
TGaxis * bxAxisEndCap = new TGaxis(112.,0.,112.,100.,-5,5,11,"+L");

bxAxis->SetLabelColor(9);
bxAxis->SetName("bxAxis");
bxAxis->SetTitle("Mean BX (bx Units)");
bxAxis->SetTitleColor(9);
bxAxis->CenterTitle();

bxAxisFar->SetLabelColor(9);
bxAxisFar->SetName("bxAxis");
bxAxisFar->SetTitle("Mean BX (bx Units)");
bxAxisFar->SetTitleColor(9);
bxAxisFar->CenterTitle();

bxAxisEndCap->SetLabelColor(9);
bxAxisEndCap->SetName("bxAxis");
bxAxisEndCap->SetTitle("Mean BX (bx Units)");
bxAxisEndCap->SetTitleColor(9);
bxAxisEndCap->CenterTitle();

gStyle->SetOptStat(0);

EffGlobDm3->Draw();
EffGlobDm3->GetYaxis()->SetTitle("%");
  
BXGlobDm3->SetMarkerColor(9);
BXGlobDm3->SetLineColor(9);
BXGlobDm3->Draw("same");

MaskedGlobDm3->SetMarkerColor(2);
MaskedGlobDm3->SetLineColor(2);
MaskedGlobDm3->Draw("same");

AverageEffDm3->SetMarkerColor(8);
AverageEffDm3->SetLineColor(8);
AverageEffDm3->Draw("same");

NoPredictionDm3->SetMarkerColor(5);
NoPredictionDm3->SetLineColor(5);
NoPredictionDm3->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_Dm3near.png");
Ca2->SaveAs("SegEff_Dm3near.root");
Ca2->Clear();


EffGlobDm2->Draw();
EffGlobDm2->GetYaxis()->SetTitle("%");
  
BXGlobDm2->SetMarkerColor(9);
BXGlobDm2->SetLineColor(9);
BXGlobDm2->Draw("same");

MaskedGlobDm2->SetMarkerColor(2);
MaskedGlobDm2->SetLineColor(2);
MaskedGlobDm2->Draw("same");

AverageEffDm2->SetMarkerColor(8);
AverageEffDm2->SetLineColor(8);
AverageEffDm2->Draw("same");

NoPredictionDm2->SetMarkerColor(5);
NoPredictionDm2->SetLineColor(5);
NoPredictionDm2->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_Dm2near.png");
Ca2->SaveAs("SegEff_Dm2near.root");
Ca2->Clear();


EffGlobDm1->Draw();
EffGlobDm1->GetYaxis()->SetTitle("%");
  
BXGlobDm1->SetMarkerColor(9);
BXGlobDm1->SetLineColor(9);
BXGlobDm1->Draw("same");

MaskedGlobDm1->SetMarkerColor(2);
MaskedGlobDm1->SetLineColor(2);
MaskedGlobDm1->Draw("same");

AverageEffDm1->SetMarkerColor(8);
AverageEffDm1->SetLineColor(8);
AverageEffDm1->Draw("same");

NoPredictionDm1->SetMarkerColor(5);
NoPredictionDm1->SetLineColor(5);
NoPredictionDm1->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_Dm1near.png");
Ca2->SaveAs("SegEff_Dm1near.root");
Ca2->Clear();




EffGlobWm2->Draw();
EffGlobWm2->GetYaxis()->SetTitle("%");
  
BXGlobWm2->SetMarkerColor(9);
BXGlobWm2->SetLineColor(9);
BXGlobWm2->Draw("same");

MaskedGlobWm2->SetMarkerColor(2);
MaskedGlobWm2->SetLineColor(2);
MaskedGlobWm2->Draw("same");

AverageEffWm2->SetMarkerColor(8);
AverageEffWm2->SetLineColor(8);
AverageEffWm2->Draw("same");

NoPredictionWm2->SetMarkerColor(5);
NoPredictionWm2->SetLineColor(5);
NoPredictionWm2->Draw("same");

pave->Draw();

bxAxis->Draw("same");
  
Ca2->SaveAs("SegEff_Wm2near.png");
Ca2->SaveAs("SegEff_Wm2near.root");
Ca2->Clear();

EffGlobWm2far->Draw();
EffGlobWm2far->GetYaxis()->SetTitle("%");
  
BXGlobWm2far->SetMarkerColor(9);
BXGlobWm2far->SetLineColor(9);
BXGlobWm2far->Draw("same");

MaskedGlobWm2far->SetMarkerColor(2);
MaskedGlobWm2far->SetLineColor(2);
MaskedGlobWm2far->Draw("same");

AverageEffWm2far->SetMarkerColor(8);
AverageEffWm2far->SetLineColor(8);
AverageEffWm2far->Draw("same");

NoPredictionWm2far->SetMarkerColor(5);
NoPredictionWm2far->SetLineColor(5);
NoPredictionWm2far->Draw("same");
 
  
bxAxisFar->Draw("same");
  
Ca2->SaveAs("SegEff_Wm2far.png");
Ca2->SaveAs("SegEff_Wm2far.root");
Ca2->Clear();

EffGlobWm1->Draw();
EffGlobWm1->GetYaxis()->SetTitle("%");
  
BXGlobWm1->SetMarkerColor(9);
BXGlobWm1->SetLineColor(9);
BXGlobWm1->Draw("same");

MaskedGlobWm1->SetMarkerColor(2);
MaskedGlobWm1->SetLineColor(2);
MaskedGlobWm1->Draw("same");

AverageEffWm1->SetMarkerColor(8);
AverageEffWm1->SetLineColor(8);
AverageEffWm1->Draw("same");

NoPredictionWm1->SetMarkerColor(5);
NoPredictionWm1->SetLineColor(5);
NoPredictionWm1->Draw("same");
 
pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("SegEff_Wm1near.png");
Ca2->SaveAs("SegEff_Wm1near.root");
Ca2->Clear();

EffGlobWm1far->Draw();
EffGlobWm1far->GetYaxis()->SetTitle("%");
  
BXGlobWm1far->SetMarkerColor(9);
BXGlobWm1far->SetLineColor(9);
BXGlobWm1far->Draw("same");

MaskedGlobWm1far->SetMarkerColor(2);
MaskedGlobWm1far->SetLineColor(2);
MaskedGlobWm1far->Draw("same");

AverageEffWm1far->SetMarkerColor(8);
AverageEffWm1far->SetLineColor(8);
AverageEffWm1far->Draw("same");

NoPredictionWm1far->SetMarkerColor(5);
NoPredictionWm1far->SetLineColor(5);
NoPredictionWm1far->Draw("same");

pave->Draw(); 

bxAxisFar->Draw("same");

Ca2->SaveAs("SegEff_Wm1far.png");
Ca2->SaveAs("SegEff_Wm1far.root");
Ca2->Clear();

EffGlobW0->Draw();
EffGlobW0->GetYaxis()->SetTitle("%");
  
BXGlobW0->SetMarkerColor(9);
BXGlobW0->SetLineColor(9);
BXGlobW0->Draw("same");

MaskedGlobW0->SetMarkerColor(2);
MaskedGlobW0->SetLineColor(2);
MaskedGlobW0->Draw("same");

AverageEffW0->SetMarkerColor(8);
AverageEffW0->SetLineColor(8);
AverageEffW0->Draw("same");

NoPredictionW0->SetMarkerColor(5);
NoPredictionW0->SetLineColor(5);
NoPredictionW0->Draw("same");
 
pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("SegEff_W0near.png");
Ca2->SaveAs("SegEff_W0near.root");
Ca2->Clear();

EffGlobW0far->Draw();
EffGlobW0far->GetYaxis()->SetTitle("%");
  
BXGlobW0far->SetMarkerColor(9);
BXGlobW0far->SetLineColor(9);
BXGlobW0far->Draw("same");

MaskedGlobW0far->SetMarkerColor(2);
MaskedGlobW0far->SetLineColor(2);
MaskedGlobW0far->Draw("same");

AverageEffW0far->SetMarkerColor(8);
AverageEffW0far->SetLineColor(8);
AverageEffW0far->Draw("same");

NoPredictionW0far->SetMarkerColor(5);
NoPredictionW0far->SetLineColor(5);
NoPredictionW0far->Draw("same");
 
pave->Draw();

bxAxisFar->Draw("same");

Ca2->SaveAs("SegEff_W0far.png");
Ca2->SaveAs("SegEff_W0far.root");
Ca2->Clear();

EffGlobW1->Draw();
EffGlobW1->GetYaxis()->SetTitle("%");
  
BXGlobW1->SetMarkerColor(9);
BXGlobW1->SetLineColor(9);
BXGlobW1->Draw("same");

MaskedGlobW1->SetMarkerColor(2);
MaskedGlobW1->SetLineColor(2);
MaskedGlobW1->Draw("same");

AverageEffW1->SetMarkerColor(8);
AverageEffW1->SetLineColor(8);
AverageEffW1->Draw("same");

NoPredictionW1->SetMarkerColor(5);
NoPredictionW1->SetLineColor(5);
NoPredictionW1->Draw("same");

pave->Draw();

bxAxis->Draw("same");

Ca2->SaveAs("SegEff_W1near.png");
Ca2->SaveAs("SegEff_W1near.root");
Ca2->Clear();

EffGlobW1far->Draw();
EffGlobW1far->GetYaxis()->SetTitle("%");
  
BXGlobW1far->SetMarkerColor(9);
BXGlobW1far->SetLineColor(9);
BXGlobW1far->Draw("same");

MaskedGlobW1far->SetMarkerColor(2);
MaskedGlobW1far->SetLineColor(2);
MaskedGlobW1far->Draw("same");

AverageEffW1far->SetMarkerColor(8);
AverageEffW1far->SetLineColor(8);
AverageEffW1far->Draw("same");

NoPredictionW1far->SetMarkerColor(5);
NoPredictionW1far->SetLineColor(5);
NoPredictionW1far->Draw("same");

pave->Draw();

bxAxisFar->Draw("same");

Ca2->SaveAs("SegEff_W1far.png");
Ca2->SaveAs("SegEff_W1far.root");
Ca2->Clear();

EffGlobW2->Draw();
EffGlobW2->GetYaxis()->SetTitle("%");
  
BXGlobW2->SetMarkerColor(9);
BXGlobW2->SetLineColor(9);
BXGlobW2->Draw("same");

MaskedGlobW2->SetMarkerColor(2);
MaskedGlobW2->SetLineColor(2);
MaskedGlobW2->Draw("same");

AverageEffW2->SetMarkerColor(8);
AverageEffW2->SetLineColor(8);
AverageEffW2->Draw("same");

NoPredictionW2->SetMarkerColor(5);
NoPredictionW2->SetLineColor(5);
NoPredictionW2->Draw("same");

pave->Draw();
  
bxAxis->Draw("same");

Ca2->SaveAs("SegEff_W2near.png");
Ca2->SaveAs("SegEff_W2near.root");
Ca2->Clear();
  
EffGlobW2far->Draw();
EffGlobW2far->GetYaxis()->SetTitle("%");
  
BXGlobW2far->SetMarkerColor(9);
BXGlobW2far->SetLineColor(9);
BXGlobW2far->Draw("same");

MaskedGlobW2far->SetMarkerColor(2);
MaskedGlobW2far->SetLineColor(2);
MaskedGlobW2far->Draw("same");

AverageEffW2far->SetMarkerColor(8);
AverageEffW2far->SetLineColor(8);
AverageEffW2far->Draw("same");

NoPredictionW2far->SetMarkerColor(5);
NoPredictionW2far->SetLineColor(5);
NoPredictionW2far->Draw("same");

pave->Draw();
  
bxAxisFar->Draw("same");
  
Ca2->SaveAs("SegEff_W2far.png");
Ca2->SaveAs("SegEff_W2far.root");
Ca2->Clear();


EffGlobD1->Draw();
EffGlobD1->GetYaxis()->SetTitle("%");
  
BXGlobD1->SetMarkerColor(9);
BXGlobD1->SetLineColor(9);
BXGlobD1->Draw("same");

MaskedGlobD1->SetMarkerColor(2);
MaskedGlobD1->SetLineColor(2);
MaskedGlobD1->Draw("same");

AverageEffD1->SetMarkerColor(8);
AverageEffD1->SetLineColor(8);
AverageEffD1->Draw("same");

NoPredictionD1->SetMarkerColor(5);
NoPredictionD1->SetLineColor(5);
NoPredictionD1->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_D1near.png");
Ca2->SaveAs("SegEff_D1near.root");
Ca2->Clear();


EffGlobD2->Draw();
EffGlobD2->GetYaxis()->SetTitle("%");
  
BXGlobD2->SetMarkerColor(9);
BXGlobD2->SetLineColor(9);
BXGlobD2->Draw("same");

MaskedGlobD2->SetMarkerColor(2);
MaskedGlobD2->SetLineColor(2);
MaskedGlobD2->Draw("same");

AverageEffD2->SetMarkerColor(8);
AverageEffD2->SetLineColor(8);
AverageEffD2->Draw("same");

NoPredictionD2->SetMarkerColor(5);
NoPredictionD2->SetLineColor(5);
NoPredictionD2->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_D2near.png");
Ca2->SaveAs("SegEff_D2near.root");
Ca2->Clear();


EffGlobD3->Draw();
EffGlobD3->GetYaxis()->SetTitle("%");
  
BXGlobD3->SetMarkerColor(9);
BXGlobD3->SetLineColor(9);
BXGlobD3->Draw("same");

MaskedGlobD3->SetMarkerColor(2);
MaskedGlobD3->SetLineColor(2);
MaskedGlobD3->Draw("same");

AverageEffD3->SetMarkerColor(8);
AverageEffD3->SetLineColor(8);
AverageEffD3->Draw("same");

NoPredictionD3->SetMarkerColor(5);
NoPredictionD3->SetLineColor(5);
NoPredictionD3->Draw("same");

pave->Draw();

bxAxisEndCap->Draw("same");
  
Ca2->SaveAs("SegEff_D3near.png");
Ca2->SaveAs("SegEff_D3near.root");
Ca2->Clear();


theFileOut->cd();

EffGlobWm2->Write();
EffGlobWm1->Write();
EffGlobW0->Write();
EffGlobW1->Write();
EffGlobW2->Write();

EffGlobWm2far->Write();
EffGlobWm1far->Write();
EffGlobW0far->Write();
EffGlobW1far->Write();
EffGlobW2far->Write();

BXGlobWm2->Write();
BXGlobWm1->Write();
BXGlobW0->Write();
BXGlobW1->Write();
BXGlobW2->Write();

BXGlobWm2far->Write();
BXGlobWm1far->Write();
BXGlobW0far->Write();
BXGlobW1far->Write();
BXGlobW2far->Write();

MaskedGlobWm2->Write();
MaskedGlobWm1->Write();
MaskedGlobW0->Write();
MaskedGlobW1->Write();
MaskedGlobW2->Write();

MaskedGlobWm2far->Write();
MaskedGlobWm1far->Write();
MaskedGlobW0far->Write();
MaskedGlobW1far->Write();
MaskedGlobW2far->Write();

AverageEffWm2->Write();
AverageEffWm1->Write();
AverageEffW0->Write();
AverageEffW1->Write();
AverageEffW2->Write();

AverageEffWm2far->Write();
AverageEffWm1far->Write();
AverageEffW0far->Write();
AverageEffW1far->Write();
AverageEffW2far->Write();

NoPredictionWm2->Write();
NoPredictionWm1->Write();
NoPredictionW0->Write();
NoPredictionW1->Write();
NoPredictionW2->Write();

NoPredictionWm2far->Write();
NoPredictionWm1far->Write();
NoPredictionW0far->Write();
NoPredictionW1far->Write();
NoPredictionW2far->Write();

NoPredictionDm3->Write();
AverageEffDm3->Write();
EffGlobDm3->Write();
BXGlobDm3->Write();
MaskedGlobDm3->Write();
NoPredictionDm3far->Write();
AverageEffDm3far->Write();
EffGlobDm3far->Write();
BXGlobDm3far->Write();
MaskedGlobDm3far->Write();
NoPredictionDm2->Write();
AverageEffDm2->Write();
EffGlobDm2->Write();
BXGlobDm2->Write();
MaskedGlobDm2->Write();
NoPredictionDm2far->Write();
AverageEffDm2far->Write();
EffGlobDm2far->Write();
BXGlobDm2far->Write();
MaskedGlobDm2far->Write();
NoPredictionDm1->Write();
AverageEffDm1->Write();
EffGlobDm1->Write();
BXGlobDm1->Write();
MaskedGlobDm1->Write();
NoPredictionDm1far->Write();
AverageEffDm1far->Write();
EffGlobDm1far->Write();
BXGlobDm1far->Write();
MaskedGlobDm1far->Write();
NoPredictionD1->Write();
AverageEffD1->Write();
EffGlobD1->Write();
BXGlobD1->Write();
MaskedGlobD1->Write();
NoPredictionD1far->Write();
AverageEffD1far->Write();
EffGlobD1far->Write();
BXGlobD1far->Write();
MaskedGlobD1far->Write();
NoPredictionD2->Write();
AverageEffD2->Write();
EffGlobD2->Write();
BXGlobD2->Write();
MaskedGlobD2->Write();
NoPredictionD2far->Write();
AverageEffD2far->Write();
EffGlobD2far->Write();
BXGlobD2far->Write();
MaskedGlobD2far->Write();
NoPredictionD3->Write();
AverageEffD3->Write();
EffGlobD3->Write();
BXGlobD3->Write();
MaskedGlobD3->Write();
NoPredictionD3far->Write();
AverageEffD3far->Write();
EffGlobD3far->Write();
BXGlobD3far->Write();
MaskedGlobD3far->Write();

Ca2->Close();
  
Ca1->Close();
theFileOut->Close();
theFile->Close();

}

