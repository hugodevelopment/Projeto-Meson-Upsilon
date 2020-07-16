#ifndef dimuon_h
#define dimuon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
rigger
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLatex.h>
#include <TF1.h>
#include "TMath.h"
#include "TLegend.h"
#include "TLorentzVector.h"

// auxiliary function for fitting
Double_t signal(Double_t *x, Double_t *par);
Double_t backgr(Double_t *x, Double_t *par);
Double_t fitfun(Double_t *x, Double_t *par);

class dimuon {

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile    *_outFile; 
   Double_t _nev;
   Double_t _mmin;
   Double_t _mmax;

   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   
       vector<double>* leadingMuon_Pt;
	vector<double>* leadingMuon_Eta;
	vector<double>* leadingMuon_Phi;
	vector<double>* leadingMuon_Mass;
        vector<int>*    leadingMuon_Charge;
        
        vector<double>* trailingMuon_Pt; 
	vector<double>* trailingMuon_Eta;
	vector<double>* trailingMuon_Phi;
	vector<double>* trailingMuon_Mass;
        vector<int>* trailingMuon_Charge;

       TLorentzVector  *HLTriggername;
 

   // List of branches
      TBranch                                              *b_HLTriggername;                                    //!
      TBranch                                              *b_ leadingMuon_Pt;                               //!
      TBranch                                              * b_leadingMuon_Eta;                           //!
      TBranch                                              *b_leadingMuon_Phi;                            //!   
       TBranch                                             *b_leadingMuon_Mass;                      //!
       TBranch                                             *b_leadingMuon_Charge;                //!
         
        TBranch                                           *b_ trailingMuon_Pt;                          //!
	TBranch                                           *b_trailingMuon_Eta;                       //!
	 TBranch                                           *b_ trailingMuon_Phi;                    //!
	 TBranch                                            *b_ trailingMuon_Mass;             //!
         TBranch                                             *b_ trailingMuon_Charge;       //!

   dimuon(TTree *tree=0);
   virtual ~dimuon();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     GetSpectrum();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     FitPeak();
   virtual void     FillHisto(TH1F* hist);
   virtual void     SaveHisto(TH1F* hist, Int_t log = 0);
   virtual void     SelectPeak();

};

#endif

#ifdef dimuon_cxx
dimuon::dimuon(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data_histoall.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data_histoall.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("data_histoall.root:/");
      dir->GetObject("AnalysisTree",tree);
   }
   Init(tree);

   _outFile = new TFile("plots/histos.root","update"); 

}

dimuon::~dimuon()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
 _outFile->Close();
 delete _outFile;
}

Int_t dimuon::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t dimuon::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dimuon::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer


leadingMuon_Pt =    0;
leadingMuon_Eta =   0;
leadingMuon_Phi =   0;
 leadingMuon_Mass =  0;
 leadingMuon_Charge= 0;

trailingMuon_Pt   =  0; 
trailingMuon_Eta  =  0;
trailingMuon_Phi  =  0;
 trailingMuon_Mass =  0;
 trailingMuon_Charge  =  0;    



   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HLTriggername", &HLTriggername, &b_HLTriggername);
   fChain->SetBranchAddress("leadingMuon_Pt", &leadingMuon_Pt, &b_leadingMuon_Pt);
   fChain->SetBranchAddress("leadingMuon_Phi", &leadingMuon_Phi, &b_leadingMuon_Phi);
   fChain->SetBranchAddress("leadingMuon_Eta", &leadingMuon_Eta, &b_leadingMuon_Eta);
   fChain->SetBranchAddress("leadingMuon_Mass", &leadingMuon_Mass, &b_leadingMuon_Mass);
   fChain->SetBranchAddress("leadingMuon_Charge", &leadingMuon_Charge, &b_leadingMuon_Charge);
    
   fChain->SetBranchAddress("trailingMuon_Pt", &trailingMuon_Pt, &b_trailingMuon_Pt);
    fChain->SetBranchAddress("trailiningMuon_Eta", &trailingMuon_Eta, &b_trailingMuon_Eta);
    fChain->SetBranchAddress("trailingMuon_Phi", &trailingMuon_Phi, &b_trailingMuon_Phi);
    fChain->SetBranchAddress("trailingMuon_Mass", &trailingMuon_Mass, &b_trailingMuon_Mass);
   fChain->SetBranchAddress("trailingMuon_Charge", &trailingMuon_Charge, &b_trailingMuon_Charge);


   Notify();
}

Bool_t dimuon::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dimuon::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t dimuon::Cut(Long64_t entry) 
{

// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.

  double mass =  leadingMuon_Mass->M();
  double pt1 =      leadingMuon_Pt->Pt();
  double pt2 =      trailingMuon_Pt->Pt();
  
//if(pt1<10 || pt2<10) return -1;
  if(mass>200) return -1;
  //cout << "Cut mass:" << mass << endl;

   return 1;
}

#endif // #ifdef dimuon_cxx
