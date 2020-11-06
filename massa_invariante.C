void massa_invariante(){
	


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
	TH1F *h1 = new TH1F("InvariantMass","Invariant Mass;Mass_{#mu^{+}#mu^{-}} (GeV);Counts",60,7.5,13);

	 Long64_t nentries = t->GetEntries();
         for (int i = 0; i < nentries; i++)
        {
                t-> GetEntry(i);		//Acessando a entrada da TTree

		h1->Fill(InvariantMass);       //Preenchendo o  histogram 
	}

	TCanvas *c1 = new TCanvas("c1","Invariant Mass", 600, 500);	//Criando o canvas para o histograma

        
	   c1->SetTopMargin(0.05);
	   c1->SetRightMargin(0.05);
	   c1->SetBottomMargin(0.12);
	   c1->SetLeftMargin(0.13);

	   h1->SetMarkerStyle(20); 
	   h1->SetMarkerColor(kRed);
	   h1->SetLineColor(kRed);	

          // Canvas p/o histograma  
          h1->GetXaxis()->SetTitle("InvariantMass");
          h1->GetYaxis()->SetTitle("Events");
          h1->SetLineColor(kRed);
          h1->Draw();


	TLatex *tx = new TLatex();
	tx->SetTextSize(0.04);
	tx->SetTextAlign(12);
	tx->SetTextFont(42);
	tx->SetNDC(kTRUE);
	
}

