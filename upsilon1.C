#include "TROOT.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include  <vector>
#include <iostream>
#include <TLorentzVector>

using namespace std;


void upsilon1(){
	

        TFile *file0 = TFile::Open("Run2011A_MuOnia_Upsilon.root");	//Opens the file
	TTree *t = (TTree*)file0->Get("tagandprobe/AnalysisTree");			//Opens TTree from file
	
	//Creates variables
	int PassingProbeTrackingMuon;
        int PassingProbeStandAloneMuon;
        int PassingProbeGlobalMuon;
        int FailingProbeTrackingMuon;
        int FailingProbeStandAloneMuon;
        int FailingProbeGlobalMuon;
        double InvariantMass; 

	int i;	//Itineration variable

	//Assign variables
	t->SetBranchAddress("InvariantMass",	                 &InvariantMass);
	t->SetBranchAddress("PassingProbeTrackingMuon",	         &PassingProbeTrackingMuon);
	t->SetBranchAddress("PassingProbeStandAloneMuon",	 &PassingProbeStandAloneMuon);
	t->SetBranchAddress("PassingProbeGlobalMuon",		 &PassingProbeGlobalMuon);
        t->SetBranchAddress("FailingProbeStandAloneMuon",	 &FailingProbeStandAloneMuon);
	t->SetBranchAddress("FailingProbeTrackingMuon",	         &FailingProbeTrackingMuon);
        t->SetBranchAddress("FailingProbeGlobalMuon",	         &FailingProbeGlobalMuon);
      
	//Cria os histogramas selecionados
        
        TH1F *I_Mass = new TH1F ("I_Mass" , "InvariantMass", 100,7.5,13);
        TH1F *PTrackingMuon = new TH1F ("PTrackingMuon" , "PassingProbeTrackingMuon", 100,0,1.5);
        TH1F *PStandMuon = new TH1F ("PStandMuon" , "PassingProbeStandAloneMuon", 100,0,1.5);
        TH1F *PGlobalMuon = new TH1F ("PGlobalMuon" , "PassingProbeGlobalMuon", 100,0,1.5);
        
        TH1F *FTrackingMuon = new TH1F ("FTrackingMuon" , "FailingProbeTrackingMuon", 100,0,1.5);
        TH1F *FStandMuon = new TH1F ("FStandMuon" , "FailingProbeStandAloneMuon", 100,0,1.5);
        TH1F *FGlobalMuon = new TH1F ("FGlobalMuon" , "FailingProbeGlobalMuon", 100,0,1.5);

       //Cria o loop para as particulas
       Long64_t nentries = t->GetEntries();
       for (int i = 0; i < nentries; i++)
        {
        t-> GetEntry(i);	
        //Preenche os histogramas com as particulas selecionadas
        I_Mass->Fill(InvariantMass);
        PStandMuon->Fill(PassingProbeStandAloneMuon);
        PGlobalMuon->Fill(PassingProbeGlobalMuon);
        PTrackingMuon->Fill(PassingProbeTrackingMuon);
        
        FTrackingMuon->Fill(FailingProbeTrackingMuon);
        FStandMuon->Fill(FailingProbeStandAloneMuon);
        FGlobalMuon->Fill(FailingProbeGlobalMuon);
        }
        
        //Criando o canvas para os histogramas  
	TCanvas *c1 = new TCanvas("c1","selected_Muons", 600, 600);	
        c1->Divide(2,2);
        c1->cd(1);
           
           //Canvas p/o Pt
           PTrackingMuon->GetXaxis()->SetTitle("PassingProbeTrackingMuon");
           PTrackingMuon->GetYaxis()->SetTitle("Events");
           PTrackingMuon->SetLineColor(kRed);
           PTrackingMuon->Draw();

          // Canvas p/o Eta
          c1->cd(2);  
          I_Mass->GetXaxis()->SetTitle("InvariantMass");
          I_Mass->GetYaxis()->SetTitle("Events");
          I_Mass->SetLineColor(kOrange);
          I_Mass->Draw();

          //Canvas p/o Phi
          c1->cd(3);  
          PStandMuon->GetXaxis()->SetTitle("PassingProbeStandAloneMuon");
          PStandMuon->GetYaxis()->SetTitle("Events");
          PStandMuon->SetLineColor(kYellow);
          PStandMuon->Draw();

          //Canvas p/a Massa  
          c1->cd(4);  
          PGlobalMuon->GetXaxis()->SetTitle("PassingProbeGlobalMuon");
          PGlobalMuon->GetYaxis()->SetTitle("Events");
          PGlobalMuon->Draw();


          c1->cd(5);  
          FTrackingMuon->GetXaxis()->SetTitle("FailingProbeTrackingMuon");
          FTrackingMuon->GetYaxis()->SetTitle("Events");
          FTrackingMuon->Draw();

          c1->cd(6);  
          FStandMuon->GetXaxis()->SetTitle("FailingProbeStandAloneMuon");
          FStandMuon->GetYaxis()->SetTitle("Events");
          FStandMuon->Draw();


          c1->cd(7);  
          FGlobalMuon->GetXaxis()->SetTitle("FailingProbeGlobalMuon");
          FGlobalMuon->GetYaxis()->SetTitle("Events");
          FGlobalMuon->Draw();
}

