{
gROOT->Reset();
#include "Riostream.h"

   ifstream in;
   in.open("alleff.txt");

   Float_t x,y,ey;
   Int_t nlines = 0;
   TFile *f = new TFile("Plots.root","RECREATE");
   TH1F *h1 = new TH1F("Eff","MC and Segment Extrapolation",100,0.5,100.5);
   TH1F *h2 = new TH1F("Diff","Diference MC - Method",100,0.5,100.5);
   TH1F *h3 = new TH1F("Disc","Discrepancy between MC and Segment Extrapolation",100,0.5,100.5);

   while (1) {
     in >>x >>y >>ey;
     if (!in.good()) break;
     if (nlines < 5) printf("x=%3f, y=%3f ey=%3f \n",x,y,ey);

     h1->SetBinContent(x,y);
     h1->SetBinError(x,ey);
     h1->GetXaxis()->SetTitle("Efficiency Produced with MC (%)");
     h1->GetYaxis()->SetTitle("Efficiency with Segment Extrapolation(%)");

     h2->SetBinContent(x,y-x);
     h2->SetBinError(x,ey);
     h2->GetXaxis()->SetTitle("Efficiency MC (%)");
     h2->GetYaxis()->SetTitle("Eff MC - Eff Segments (%)");


     if(x!=0) h3->SetBinContent(x,fabs(x-y)/x);
     h3->SetBinError(x,ey);
     h3->GetXaxis()->SetTitle("Efficiency MC (%)");
     h3->GetYaxis()->SetTitle("Eff MC - Eff Segments/ Eff MC");
     
     nlines++;
   }
   printf(" found %d pointsn",nlines);
   in.close();
   
   TCanvas *Ca1 = new TCanvas("Ca1","Temp Canvas",1200,1200);

   h1->Draw();
   Ca1->SaveAs("Eff.png");
   Ca1->Clear();

   h2->Draw();
   Ca1->SaveAs("Diff.png");
   Ca1->Clear();

   h3->Draw();
   Ca1->SaveAs("Disc.png");

   f->Write();
}

//Open root y dentro del promt de root simplemente 
//root [0] .x macroProdPlotsXYeY.C
