void bxvsyErrors(){	
  TFile * file = TFile::Open("eff70195_70674.root");
  TH2F * histo = (TH2F*)file->Get("DQMData/Muons/MuonSegEff/bxVsy");
  
  const int n = 126;
  float x[n];
  float y[n];
  float ex[n];
  float ey[n];

  for(int i=0;i<n;i++){
    float mean = histo->ProjectionX("_px",i,i+1)->GetMean();
    float entries = histo->ProjectionX("_px",i,i+1)->GetEntries();
    float error = histo->ProjectionX("_px",i,i+1)->GetRMS()/ sqrt(entries);
    cout<<i+1<<" "<<mean<<" "<<" entries="<<entries<<" error="<<error<<endl;
    x[i]=i+1;
    ex[i]=0.5;
    y[i]=mean;
    ey[i]=error;
    
  }
  
  TGraphErrors * plot = new TGraphErrors(n,x,y,ex,ey);	
  plot->SetMarkerColor(6);
  plot->SetMarkerStyle(20);
  plot->SetMarkerSize(0.5);
  plot->GetXaxis()->SetRangeUser(0.,float(n));
  plot->GetXaxis()->SetTitle("Distance to the BOTTOM of the Chamber (cm)");
  plot->GetYaxis()->SetTitle("Mean BX (bx Units)");	
  plot->Draw("AP");
  
  //	exit();	
}
