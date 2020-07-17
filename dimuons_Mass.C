#define dimuon_cxx
#include "dimuon2.h"

void dimuons_Mass() {

  TChain * chain = new TChain("AnalysisTree","");
  chain->Add("data_histoall.root");

  //chain->Show();
  //chain->Scan("*");

  dimuon a(chain);
  a._nev = 100000;
  
  a.GetSpectrum();

  a.SelectPeak();

  a.FitPeak();

}

// Esta e a funcao mais importante no processo
void dimuon::GetSpectrum() {

  // Checando a tree
  if (fChain == 0) return;

  // Criando um simples histograma da massa
  TH1F *hDimuonMass_normal = new TH1F("hDimuonMass","hDimuonMass",10000,7,14);
  FillHisto(hDimuonMass);
  SaveHisto(hDimuonMass);

  // Escalas logaritimicas
  SaveHisto(hDimuonMass,kTRUE);

  // define outro histograma (especial): com larguras variáveis de bin (!)
  
  double xbins[100000];
  xbins[0] = .1; 
  int nbins = 0;
  double binWidth=0.005; 
  for (int i=1; xbins[i-1]<500; i++) {
    xbins[i] = xbins[i-1]*(1+binWidth);
    nbins++;
  }

  TH1F *hDimuonMass = new TH1F("hDimuonMass1","hDimuonMass1",nbins,xbins);
  FillHisto(hDimuonMass1);
  SaveHisto(hDimuonMass1,kTRUE);


  for (int i=1; i<=hDimuonMass1->GetNbinsX(); i++) {
    hDimuonMass->SetBinContent(i, hDimuonMass1->GetBinContent(i)/hDimuonMass1->GetBinWidth(i));
  }
  SaveHisto(hDimuonMass1,kTRUE);

}

void dimuon::SaveHisto(TH1F* hist, Int_t log) {

  //Definindo o estilo
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  //Definindo os eixos x e y
  hist->GetXaxis()->SetTitle("#mu^{+}#mu^{-} invariant mass [GeV]");
  hist->GetYaxis()->SetTitle("Events / GeV");

  //Criando o canvas 
  TCanvas *canvas = new TCanvas("canvas","canvas",800,600);

  if(log) {
    canvas->SetLogx();
    canvas->SetLogy();
  }

  hist->Draw("HIST");

  TString hn ("");
  hn += "plots/";
  hn += hist->GetName();
  if(log) hn += "_log";
  hn += ".png";
  canvas->SaveAs(hn);
  delete canvas;

  //TH1F* h2 = (TH1F*)hist->Clone();
  //h2->SetName(hn);
  _outFile->cd();
  hist->Draw("HIST");
  hist->Write();
  _outFile->Write();

}

void dimuon::FillHisto(TH1F* hist) {
  
  // loop sobre a tree e preenchendo os histogromas
  Long64_t nentries = fChain->GetEntriesFast();
  nentries = _nev>0 ? _nev : nentries;
  //cout << "nentries: " << nentries << endl;
  
  // duvida
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if ( Cut(ientry) < 0) continue;
    
     double mass = leadingMuon_Mass->M();
    
    hist->Fill(mass);  
  }

}

void dimuon::SelectPeak() {
  

  //Definindo o intervalo do pico 
  Double_t mmin(9), mmax(9.5);
  _mmin = mmin;  _mmax = mmax;  

  //Criando um histograma proximo ao pico
  TH1F *hDimuonMass_peak = new TH1F("hDimuonMass_peak","hDimuonMass_peak",100,mmin,mmax);
  FillHisto(hDimuonMass_peak);
  SaveHisto(hDimuonMass_peak);

}

void dimuon::FitPeak() {
 
  if(!_outFile) {cout << "Check input file." << endl; return;}

  // Recuperando o histograma referente ao pico
  TH1F* hpeak= 0;
  TString hname("hDimuonMass_mypeak");
  _outFile->GetObject(hname,hpeak);
  if (!hpeak) {
    cout << "Check input histogram:" << hname <<  endl;
    return;
  }

  //Definindo a funcao de ajuste e preenchendo o histograma
  const Int_t nfitpar(5);
  TF1* f = new TF1("f",fitfun,_mmin,_mmax,nfitpar);
  f->SetParameters(100,3.09,0.1,0,0);
  hpeak->Fit("f");

  //Escreva o resultado do ajuste em um array
  Double_t par[nfitpar];
  f->GetParameters(par);

  printf("\nFitResults:\n\tResonance mass: %5.3f +/- %5.3f GeV/c^2.\n",
	 par[1],f->GetParErrors()[1]);


  //O que se segue é estética, principalmente ...

  gROOT->LoadMacro("tdrstyle.C");

  TCanvas *canvas0 = new TCanvas("peak","peak",800,600);
 

  hpeak->GetXaxis()->SetTitle("#mu^{+}#mu^{-} invariant mass [GeV/c^{2}]");
  hpeak->GetYaxis()->SetTitle(Form("Events / %3.1f MeV/c^{2}",hpeak->GetBinWidth(1)*1000));
  hpeak->SetStats(0);
  hpeak->SetTitle("");
  hpeak->SetMarkerStyle(21);
  hpeak->SetMarkerSize(0.8);

  hpeak->Fit("f","V+","ep");

  //Definindo funções individuais para cada representação
  
  TF1 *signalFcn = new TF1("signalFcn",signal,_mmin,_mmax,3);
  signalFcn->SetLineColor(kBlue);
  signalFcn->SetNpx(500);
  TF1 *backFcn = new TF1("backFcn",backgr,_mmin,_mmax,2);
  backFcn->SetLineColor(kGray);
  backFcn->SetLineStyle(2);

  signalFcn->SetParameters(par);
  signalFcn->Draw("same");
  
  backFcn->SetParameters(&par[3]);
  backFcn->Draw("same");
    
  // Escrevendo as legendas
  
  TLegend *legend=new TLegend(0.7,0.65,0.88,0.85);
  legend->SetBorderSize(0);
  legend->SetTextFont(40);
  legend->SetTextSize(0.03);
  legend->AddEntry(hpeak,"Data","lpe");
  legend->AddEntry(backFcn,"Background fit","l");
  legend->AddEntry(signalFcn,"Signal fit","l");
  legend->AddEntry(f,"Global Fit","l");
  legend->Draw("same");

  // Resultados do ajuste
  
  TLatex L;
  L.SetNDC();
  L.SetTextSize(0.04);
  L.DrawLatex(0.15,0.8,"Dimuon Spectrum");
  L.SetTextSize(0.03);
  L.DrawLatex(0.15,0.75,"resonance: Upsilon Meson");
  L.DrawLatex(0.15,0.70,Form("mass: %5.3f #pm %5.3f GeV/c^{2}",
			     par[1], f->GetParErrors()[1]));
  L.DrawLatex(0.15,0.65,Form("with: %5.3f #pm %5.3f MeV/c^{2}", 
			     par[2]*1000, f->GetParErrors()[2]*1000));

  // Salva o histograma com a função de ajuste
  canvas0->SaveAs("plots/mypeak.png");

}


Double_t signal(Double_t *x, Double_t *par) {
  
  // Uma simples gaussiana
  return par[0]*exp(-0.5*TMath::Power(((x[0]-par[1])/(par[2])),2)); 
}

Double_t backgr(Double_t *x, Double_t *par) {
  
  // Uma simples polinominal
  return par[0]+par[2]*x[0];
}

Double_t fitfun(Double_t *x, Double_t *par) {
  
  return signal(x,par) + backgr(x,&par[3]); 
}
