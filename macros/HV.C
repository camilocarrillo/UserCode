void HV(){

  TH1F *tmpw1  = new TH1F("tmpw1","HV scan",4,8.95,9.35);

  //Con esto inicializo el contenido del histograma
  for(int i=1; i <= 4; ++i ) tmpw1->SetBinContent(i,0.0);

  tmpw1->SetBinContent(1,46.8890); //<-Esta instruccion es similar a Fill
  tmpw1->SetBinError(1,1.14);
  
  tmpw1->SetBinContent(2,79.7778);
  tmpw1->SetBinError(2,1.13);
  
  tmpw1->SetBinContent(3,89.69);
  tmpw1->SetBinError(3,1,14);
  
  tmpw1->SetBinContent(4,92.25);
  tmpw1->SetBinError(4,1.14);
  

  TCanvas *c1 = new TCanvas("c1","c1",800,1200);
  tmpw1->SetLineColor(kRed);
  
  tmpw1->SetMinimum(30);
  tmpw1->SetMaximum(100);

  tmpw1->Draw("E");  
  tmpw1->DrawClone("CSAME"); 
  //La opcion C (linea suave) solamente aparece dibujando con la opcion H

  //tmpw2->Draw("samec*H");
  //tmpw0->Draw("samec*H");
  tmpw1->Draw("samec*H");
  //tmpwm2->Draw("samec*H");

}


  //  tmpw1->SetBinError(9300,0.100504);
//  tmpw2->Fill(9000,68.9720);
  //  tmpw2->SetBinError(9000,0.1002062);
 // tmpw2->Fill(9100,73.5949);
  //  tmpw2->SetBinError(9100,0.102598);
//  tmpw2->Fill(9200,89.9583);
  //  tmpw2->SetBinError(9200,0.102062);
//  tmpw2->Fill(9300,79.5370);
  //  tmpw2->SetBinError(9300,0.101535);
//  tmpw0->Fill(9000,65.8486);
//  tmpw0->Fill(9200,88.3095);
//  tmpw0->Fill(9100,71.8620);
 // tmpw0->Fill(9300,79.43);
//  tmpwm1->Fill(9000,64.6476);
 // tmpwm1->Fill(9200,88.3934);
 // tmpwm1->Fill(9100,70.2718);
 // tmpwm1->Fill(9300,75.9512);

 // tmpwm2->Fill(9000,62.0798);
 // tmpwm2->Fill(9200,81.6476);
 // tmpwm2->Fill(9100,68.7852);
  // tmpwm2->Fill(9300,73.7130);



