#include "TROOT.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFitResult.h"
#include "TLegend.h"
#include "TLatex.h"
#include "FitFunctions.h" 

using namespace std;


//Funcao de ajuste gaussiana para os 3 estados do upsilon
Double_t Signal(Double_t *x, Double_t *par) {
  return Gaus(x,par) + Gaus(x, &par[3]) + Gaus(x, &par[6]);
}

// Codigo para criar o histograma da massa invariante presente no arquivo Run2011A_MuOnia_Upsilon.root.
void massa_invariante2(){
	


        TFile *file0 = TFile::Open("Run2011A_MuOnia_Upsilon.root");	
	TTree *t = (TTree*)file0->Get("tagandprobe/AnalysisTree");     
	
	//Criando as variaveis
	int PassingProbeTrackingMuon;
        int PassingProbeStandAloneMuon;
        int PassingProbeGlobalMuon;
        int FailingProbeTrackingMuon;
        int FailingProbeStandAloneMuon;
        int FailingProbeGlobalMuon;
        double InvariantMass; 

	int i;	//Variavel de iteracao

	//Acessando as variaveis
	t->SetBranchAddress("InvariantMass",	                 &InvariantMass);
	t->SetBranchAddress("PassingProbeTrackingMuon",	         &PassingProbeTrackingMuon);
	t->SetBranchAddress("PassingProbeStandAloneMuon",	 &PassingProbeStandAloneMuon);
	t->SetBranchAddress("PassingProbeGlobalMuon",		 &PassingProbeGlobalMuon);
        t->SetBranchAddress("FailingProbeStandAloneMuon",	 &FailingProbeStandAloneMuon);
	t->SetBranchAddress("FailingProbeTrackingMuon",	         &FailingProbeTrackingMuon);
        t->SetBranchAddress("FailingProbeGlobalMuon",	         &FailingProbeGlobalMuon);
      
	//Cria os histogramas selecionados
	TH1F *h1 = new TH1F("InvariantMass","Invariant Mass;Mass_{#mu^{+}#mu^{-}} (GeV); Counts ",100 ,9.,11.);

	 Long64_t nentries = t->GetEntries();
         for (int i = 0; i < nentries; i++)
        {
                t-> GetEntry(i);		//Acessando a entrada da TTree

		h1->Fill(InvariantMass);       //Preenchendo o  histogram 
	}

	TCanvas *c1 = new TCanvas("c1","Invariant Mass", 800, 500);	//Criando o canvas para o histograma

        
	   c1->SetTopMargin(0.09);
	   c1->SetRightMargin(0.09);
	   c1->SetBottomMargin(0.15);
	   c1->SetLeftMargin(0.15);

	   h1->SetMarkerStyle(20); 
	   h1->SetMarkerColor(kRed);
	   h1->SetLineColor(kRed);	

          // Canvas p/o histograma  
          h1->SetLineColor(kBlue);
        
        //Criando a função p/ o ajuste
        TF1 *f = new TF1("f",Signal,7.,12.,10);
	
	// Definindo os parametros
        f->SetParName(0,	"Gaus(1S) a (altura)");
	f->SetParName(1,	"Gaus(1S) b (posicao)");
	f->SetParName(2,	"Gaus(1S) c (largura)");
	f->SetParName(3,	"Gaus(2S) a (altura)");
	f->SetParName(4,	"Gaus(2S) b (posicao)");
	f->SetParName(5,	"Gaus(2S) c (largura)");
	f->SetParName(6,	"Gaus(3S) a (altura)");
	f->SetParName(7,	"Gaus(3S) b (posicao)");
	f->SetParName(8,	"Gaus(3S) c (largura)");
        f->SetNpx(1000);	//Resolucao da funcao

     
       //Parametros para o primeiro estado Y(1S)
	f->SetParameter(0, 2.0);
	f->FixParameter(1, 9.4603); //Valor da massa primeiro pico 
	f->SetParameter(2, 1);
	
	//Parametros para o segundo estado Y(2S)
	f->SetParameter(3, 2.0);
	f->FixParameter(4, 10.02326); //Valor da massa segundo pico
	f->SetParameter(5, 70);


	//Paramentros para o terceiro estado Y(3S)
	f->SetParameter(6, 2.0);
	f->FixParameter(7, 10.3552); //Valor da massa terceiro pico
	f->SetParameter(8, 10.331);
	//f->SetParameter(8, 1.0331); 

        f->SetLineColor(kBlue); //Fit Color

	//Função de ajuste
	TFitResultPtr fitr = h1->Fit(f,"RNS","",7.,14.);
 
        //Desenha o histograma em pontos 
	h1->Draw("ep");
	f->Draw("same");

	TLatex *tx = new TLatex();
	tx->SetTextSize(0.04);
	tx->SetTextAlign(12);
	tx->SetTextFont(42);
	tx->SetNDC(kTRUE);

        tx->DrawLatex(0.70,0.60,Form("#chi^{2}/ndf = %g/%d",fitr->Chi2(),fitr->Ndf()));



        TLegend *l = new TLegend(0.72,0.68,0.90,0.90);
	l->SetTextSize(0.04);
	l->AddEntry(h1,"#Upsilon#rightarrow#mu^{+}#mu^{-}","lp");
	l->AddEntry(f,"Ajuste","l");
	l->Draw(); 
	
	c1->SaveAs("InvariantMass.png");	
}





