# Projeto-Meson-Upsilon
Projetos desenvolvidos para a iniciação cientifícia em fisica de altas energias no ramo de fisica de partículas.

Esta macro foi desenvolvida para determinar a massa invariante da partícula meson upsilon. Especificarei abaixo como o estudo esta sendo 
elaborado. 

1) A Particula Meson Upsilon

O Meson Upsilon (Υ), é uma partícula constituida por um quark bottom e um antiquark bottom. Seu decaimento pode ocorrer em dimuons(pares de muons de cargas opostas),
sua massa é aproximadamente 9,46030 GeV/c². No caso da macro, haverá um loop que terá a função de selecionar os dimuons para determinar a massa invariante do 
Meson Upsilon ao final.

 2) A Massa Invariante 
 
A massa invariante  ́e uma grandeza muito importante a ser estudada na analise da dados em física de partıculas. Isso porque ela  ́e calculada a partir de grandezas f ́ısicas conservativas,
sendo essas momentum(p) e a energia(E) da partícula ao qual estamos interessados em estudar. 
Como as grandezas momemtum e energia são conservadas nas colisões de partículas nos aceleradores, podemos utilizá-las para, a partir delas, calcular a massa invariante de uma partícula.


3) Desenvolvendo a Macro

#include "TFile.h"

#include "TCanvas.h"

#include "TTree.h"

#include "TH1F.h"

#include "TBranch.h"

#include vector

#include "TLorentzVector.h"



void upsilon4()
{
 
 // ---------------*----------------------------------------------------*----------------------------------------------------  
 
        //Declarando as variaveis
   
      std::vector<double>* leadingMuon_Pt = new std::vector<double> ();
	    
      std::vector<double>* leadingMuon_Eta = new std::vector<double> ();
	    
      std::vector<double>* leadingMuon_Phi = new std::vector<double> ();
	    
      std::vector<double>* leadingMuon_Mass = new std::vector<double> ();
        
      std::vector<int>* leadingMuon_Charge = new std::vector<int> ();
 
 //---------------*---------------------------------------------------*----------------------------------------------------              
      
      std::vector<double>* trailingMuon_Pt = new std::vector<double> ();
	    
      std::vector<double>* trailingMuon_Eta = new std::vector<double> ();
	    
      std::vector<double>* trailingMuon_Phi = new std::vector<double> ();
	    
      std::vector<double>* trailingMuon_Mass = new std::vector<double> ();
        
      std::vector<int>* trailingMuon_Charge = new std::vector<int> ();        

//---------------*---------------------------------------------------*----------------------------------------------------                 
         
        //TLorentzVector P/ os Dimuons
     
        TLorentzVector Muons1;
        
	TLorentzVector Muons2;

 //---------------*---------------------------------------------------*----------------------------------------------------//               
       
       // Quantidades Cinematicas       
        
        double M = 0.;
        
        double Pt = 0.;
	      
        double Eta = 0;
  
        double Rapidity = 0.;

//---------------*---------------------------------------------------*----------------------------------------------------//        
        
        // Criando os histogramas para as quantidades cinemáticas

//---------------*---------------------------------------------------*----------------------------------------------------//         
        
        // Histograma para a massa invanriante com 100 bins e intervalo de 7 a 13
        
        TH1F* h1_Massa = new TH1F("h_Dimuons_Mass","h_Dimuons_M",100,7,13);
	
        h1_Massa->SetTitle("Distribuicao Massa Invariante dos Dimuons; #mu#mu [GeV] ; Eventos ");
	
        h1_Massa->SetName("h_Dimuons_M");
  
 //---------------*---------------------------------------------------*----------------------------------------------------//                
 
     //Histograma para o momemtum tranversal com 100 bins e intervalo de 0 a 50
	
      TH1F* h1_Pt = new TH1F("h_Dimuons_Pt","h_Dimuons_Pt",100,0,50);
	
      h1_Pt->SetTitle("Distribuicao Pt dos Dimuons; #mu#mu p_{T} [GeV] ; Eventos ");
	
      h1_Pt->SetName("h_Dimuons_Pt");
 
 //---------------*---------------------------------------------------*----------------------------------------------------//                
     
       //Histograma para o eta com 100 bins e intervalo de -4 a 4 
        
        TH1F* h1_Eta = new TH1F("h_Dimuons_Eta","h_Dimuons_Eta",100,-4,4);
	
        h1_Eta->SetTitle("Distribuicao Pseudo-Rapidez dos Dimuons; #eta ; Eventos ");
	
        h1_Eta->SetName("h_Dimuons_Eta");

//---------------*---------------------------------------------------*----------------------------------------------------//                 
        
        //Histograma para a massa a rapidez com intervalo de -4 a 4
	
        TH1F* h1_Rapidity = new TH1F("h_Dimuons_Rapidity","h_Dimuons_Rapidity",100,-4,4);
	
        h1_Rapidity->SetTitle("Distribuicao Rapidez dos Muons; y ; Eventos ");
	
        h1_Rapidity->SetName("h_Dimuons_Rapidity");
        
 //---------------*----------------------------------------------------*----------------------------------------------------//
       
       //Histogramas para o Dimuons de cargas opostas

//---------------*----------------------------------------------------*----------------------------------------------------//
        
        
        //Histograma para a massa invariante com 100 bins e intervalo de 0 a 10
       
        TH1F* h_DimuonsCargasOpostas_M = new TH1F("h_DimuonsOppositeCharge_Pt","h_DimuonsOppositeCharge_M",100,0,10);
	
        h_DimuonsCargasOpostas_M ->SetTitle("Distribuicao Massa Invariante dos muons; #mu#mu [GeV] ; Eventos ");
	
        h_DimuonsCargasOpostas_M -> SetName("h_DimuonsOppositeCharge_M");

//---------------*---------------------------------------------------*------------------------------------------------------//                
         
	 // Histograma para o momemtum tranversal com 100 bins e intervalo  a 50
	
        TH1F* h_DimuonsCargasOpostas_Pt = new TH1F("h_DimuonsOppositeCharge_Pt","h_DimuonsOppositeCharge_Pt",100,0,50);
	
        h_DimuonsCargasOpostas_Pt->SetTitle("Distribuicao Pt dos muons; #mu#mu p_{T} [GeV] ; Eventos ");
	
        h_DimuonsCargasOpostas_Pt->SetName("h_DimuonsOppositeCharge_Pt");

//---------------*---------------------------------------------------*----------------------------------------------------//                
       
       // Histograma para o Eta com 100 bins e intervalo -4 a 4
	
       TH1F* h_DimuonsCargasOpostas_Eta = new TH1F("h_DimuonsOppositeCharge_Eta","h_DimuonsOppositeCharge_Eta",100,-4,4);
	
       h_DimuonsCargasOpostas_Eta->SetTitle("Distribuicao Pseudo-Rapidez dos Dimuons; #eta ; Eventos ");
	
       h_DimuonsCargasOpostas_Eta->SetName("h_DimuonsOppositeCharge_Eta");
 
 //---------------*---------------------------------------------------*-----------------------------------------------------//                
        
        // Histograma para a rapidez com 100 bins intervalo de -4 a 4
	
       TH1F* h_DimuonsCargasOpostas_Rapidity = new TH1F("h_DimuonsOppositeCharge_Rapidity","h_DimuonsOppositeCharge_Rapidity",100,-4,4);
	
       h_DimuonsCargasOpostas_Rapidity->SetTitle("Distribuicao Rapidez dos muons; y ; Eventos ");
	
       h_DimuonsCargasOpostas_Rapidity->SetName("h_DimuonsOppositeCharge_Rapidity");
 
//---------------*----------------------------------------------------*----------------------------------------------------//

       //Acessando o arquivo root.file
        
        TFile *f = new TFile("data_histoall.root");	
	      
        TTree *t = (TTree*) f->Get("demo/AnalysisTree");		

// ---------------*----------------------------------------------------*----------------------------------------------------//
    
    //Acessando os Branchs     
    
    t->SetBranchAddress("leadingMuon_Pt", &leadingMuon_Pt);
    
    t->SetBranchAddress("leadingMuon_Eta", &leadingMuon_Eta); 
    
    t->SetBranchAddress("leadingMuon_Phi", &leadingMuon_Phi);
    
    t->SetBranchAddress("leadingMuon_Mass", &leadingMuon_Mass);
    
    t->SetBranchAddress("leadingMuon_Charge", &leadingMuon_Charge);
	
//---------------*---------------------------------------------------*----------------------------------------------------             
    
    t->SetBranchAddress("trailingMuon_Pt",  &trailingMuon_Pt);
    
    t->SetBranchAddress("trailingMuon_Eta", &trailingMuon_Eta); 
    
    t->SetBranchAddress("trailingMuon_Phi", &trailingMuon_Phi);
    
    t->SetBranchAddress("trailingMuon_Mass", &trailingMuon_Mass); 
    
    t->SetBranchAddress("trailingMuon_Charge",&trailingMuon_Charge);
        
// ---------------*----------------------------------------------------*----------------------------------------------------//
   
     //Criando um loop para selecionar as particulas
     
     //loop nDimuon
     
     for(Long64_t i=0; i<trailingMuon_Pt->size();i++) {
	
// ---------------*----------------------------------------------------*----------------------------------------------------//
			
      
      //TLorentz Vector P/ Muon 1   	
       
       TLorentzVectorMuons1;
       
       Muons1.SetPtEtaPhiM(leadingMuon_Pt->at(i), leadingMuon_Eta->at(i), leadingMuon_Phi->at(i), leadingMuon_Mass->at(i));
			
      
//---------------*---------------------------------------------------*----------------------------------------------------                                
        
        //TLorentz Vector P/ Muon 2              
       
         TLorentzVectorMuons2;
        
        Muons2.SetPtEtaPhiM(trailingMuon_Pt->at(i), trailingMuon_Eta->at(i), trailingMuon_Phi->at(i), trailingMuon_Mass->at(i));

//---------------*---------------------------------------------------*--------------------------------------------------------//         			
                        
      //Calculo das quantidades cinematicas
			
      M = (Muons1 + Muons2).Mag();	                 //Massa invariante dos pares de muons 
			
      Pt = (Muons1 + Muons2).Pt();                      //Momemtum tranverso o par de muons
			
      Eta = (Muons1 + Muons2).Eta();                   //Pseudorapidez(Eta) do par de muons
			
      Rapidity = (Muons1 + Muons2).Rapidity();        //Rapidez P/ o par de muons
			
 //---------------*----------------------------------------------------*----------------------------------------------------//
   
                        
     //Preenchendo oa histogramas das variaveis cinematicas 
			
      h1_Massa->Fill(M)[Mag];
			
      h1_Pt->Fill(Pt)[Pt];
			
      h1_Eta->Fill(Eta)[Eta];
			
      h1_Rapidity->Fill(Rapidity)[Rapidity];

//---------------*---------------------------------------------------*----------------------------------------------------//                         
                        
     // loop para a carga 

// ------------------------------------------------*--------------------------------*-------------------------------------//                       

       //Se leadingMuon_Charge for diferente de trailingMuon_Charge, continuar

       if ( leadingMuon_Charge->at(i) != trailingMuon_Charge->at(i) )  
			
        {
	 count_OppositeCharge_pythia++;
				
        h_DimuonsCargasOpostas_M->Fill(M)[Mag];
				
        h_DimuonsCargasOpostas_Pt->Fill(Pt)[Pt];
				
        h_DimuonsCargasOpostas_Eta->Fill(Eta)[Eta];
				
        h_DimuonsCargasOpostas_Rapidity->Fill(Rapidity)[Rapidity];
        }

// ----------*----------------------------------------------------*----------------------------------------------------//
        
       //Creating Canvas
	
       TCanvas* c2 = new TCanvas("c2","Canvas 2 - behavior of the dimuons after quality selection",1200,600);
	
      c2->Divide(2,2);
	
      c2->cd(1);
 
 //---------------*---------------------------------------------------*----------------------------------------------------//                
  
      //Editando o histograma da massa
	
     h1_Massa->SetLineColor(kRed);
	
     h_DimuonsCargasOpostas_M->SetLineColor(kBlue);

 //---------------*---------------------------------------------------*----------------------------------------------------//                     
  
       // Adicionando a legenda  
  
      TLegend* leg_dimuons_M = new TLegend(0.75,0.81,0.97,0.97);
	
     leg_dimuons_M->SetFillColor(kWhite);
	
      leg_dimuons_M->SetFillStyle(1001);
	
      leg_dimuons_M->AddEntry(h_DimuonsCargasOpostas_M,"#mu^{+}#mu^{-}","L");
	
  //---------------*---------------------------------------------------*----------------------------------------------------//         
	
      //Desenhando o histograma da massa
	
       h1_Massa->Draw();
	
       h_DimuonsCargasOpostas_M->Draw("sames");
	
        leg_dimuons_M->Draw();

//---------------*---------------------------------------------------*----------------------------------------------------//         
   
    c2->cd(2);  
 
     //Editando o histograma da momemtum transversal 
	
    1_Pt->SetLineColor(kRed);
	
    h_DimuonsCargasOpostas_Pt->SetLineColor(kBlue);
	
//---------------*---------------------------------------------------*----------------------------------------------------//         	
  
       //Adicionando a legenda
        
	TLegend* leg_dimuons_Pt = new TLegend(0.75,0.81,0.97,0.97);
	
        leg_dimuons_Pt->SetFillColor(kWhite);
	
        leg_dimuons_Pt->SetFillStyle(1001);
	
        leg_dimuons_Pt->AddEntry(h_DimuonsCargasOpostas_Pt,"#mu^{+}#mu^{-} ","L");
	
//---------------*---------------------------------------------------*----------------------------------------------------//         	
    
      //Desenhando o histograma do momemtum tranversal
	
     h1_Pt->Draw();
	
    h_DimuonsCargasOpostas_Pt->Draw("sames");
	
     leg_dimuons_Pt->Draw();


//-----------------------------*---------------------------------------*------------------------------------------//
       
       c2->cd(3);
        
       //Editando o histograma do Eta
	
        h1_Eta->SetLineColor(kRed);
	
        h_DimuonsCargasOpostas_Eta->SetLineColor(kBlue);
	
//---------------*---------------------------------------------------*----------------------------------------------------//               
  
         //Adicionando as legendas
	
          TLegend* leg_dimuons_Eta = new TLegend(0.75,0.81,0.97,0.97);
	
          leg_dimuons_Eta->SetFillColor(kWhite);
	
          leg_dimuons_Eta->SetFillStyle(1001);
	
           leg_dimuons_Eta->AddEntry(h_DimuonsCargasOpostas_Eta,"#mu^{+}#mu^{-} ","L");
        
//---------------*---------------------------------------------------*----------------------------------------------------//           
  
             //Desenhando o histograma do Eta
	
                 h1_Eta->Draw();
	
                 h_DimuonsCargasOpostas_Eta->Draw("sames");
	
                   leg_dimuons_Eta->Draw();
	
//-----------------------------------------------------------------------------------------------------------------------------//
	
          c2->cd(4);
         
          //Editando o histograma da rapidez 
	
           h1_Rapidity->SetLineColor(kRed);
	
            h_DimuonsCargasOpostas_Rapidity->SetLineColor(kBlue);
	
 //---------------*---------------------------------------------------*----------------------------------------------------//                 
        
           //Adicionando a legenda
       
	TLegend* leg_dimuons_Rapidity = new TLegend(0.75,0.81,0.97,0.97);

        leg_dimuons_Rapidity->SetFillColor(kWhite);

        leg_dimuons_Rapidity->SetFillStyle(1001);
	
        leg_dimuons_Rapidity->AddEntry(h_DimuonsCargasOpostas_Rapidity,"#mu^{+}#mu^{-} ","L");
        
 //---------------*---------------------------------------------------*----------------------------------------------------//           
   
    //Desenhando o histograma 
	
    h1_Rapidity->Draw();
	
    h_DimuonsCargasOpostas_Rapidity->Draw("sames");
	
    leg_dimuons_Rapidity->Draw();        
}



