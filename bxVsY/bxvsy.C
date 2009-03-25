void bxvsy(){	
  TFile * file = TFile::Open("bottom.root");
  TH2F * histo = (TH2F*)file->Get("DQMData/Muons/MuonSegEff/bxVsy");
  
  const int n = 126;
  float x[n];
  float y[n];
  for(int i=0;i<n;i++){
    float mean = histo->ProjectionX("_px",i,i+1)->GetMean();
    cout<<i+1<<" "<<mean<<endl;
    x[i]=i+1;
    y[i]=mean;
  }
  
  TGraph * plot = new TGraph(n,x,y);	
  plot->SetMarkerColor(6);
  plot->SetMarkerStyle(20);
  plot->SetMarkerSize(0.5);
  plot->GetXaxis()->SetRangeUser(0.,float(n));
  plot->GetXaxis()->SetTitle("Distance to the BOTTOM of the Chamber (cm)");
  plot->GetYaxis()->SetTitle("Mean BX (bx Units)");	
  plot->Draw("AP");
  
  //	exit();	
}
