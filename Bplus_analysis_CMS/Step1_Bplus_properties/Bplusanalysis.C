#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>

void Bplusanalysis::Loop()
{
   // 1. Initialization -------------------------------------------------------
   if (fChain == 0) {
      std::cerr << "Error: fChain is null!" << std::endl;
      return;
   }

   // 2. Create histograms ----------------------------------------------------
   // Angular variables
   TH1F *h_rapidity = new TH1F("h_rapidity", "B+ Rapidity; y; Counts", 100, -10, 10);
   TH1F *h_pseudorapidity = new TH1F("h_pseudorapidity", "B+ Pseudorapidity; #eta; Counts", 100, -5, 5);
   TH1F *h_phi = new TH1F("h_phi", "B+ Azimuthal Angle; #phi [rad]; Counts", 100, -TMath::Pi(), TMath::Pi());
   
   // Momenta (adjusted ranges)
   TH1F *h_pt = new TH1F("h_pt", "B+ Transverse Momentum; p_{T} [MeV/c]; Counts", 100, 0, 25000);
   TH1F *h_p = new TH1F("h_p", "B+ Momentum; p [MeV/c]; Counts", 100, 0, 60000);
   
   // 3. Event loop ------------------------------------------------------------
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "Processing " << nentries << " events..." << std::endl;

   for (Long64_t jentry = 0; jentry < nentries; jentry++) {
      if (fChain->GetEntry(jentry) <= 0) continue;

      for (int i = 0; i < chains; i++) {
         for (int j = 0; j < particles[i]; j++) {
            if (id[i][j] == 521) {  // PDG ID for B+
               // Fill angular variables
               h_rapidity->Fill(rapidity[i][j]);
               h_pseudorapidity->Fill(pseudorapidity[i][j]);
               h_phi->Fill(phi[i][j]);
               
               // Fill momenta (in MeV)
               h_pt->Fill(pt[i][j]);
               Double_t p = sqrt(px[i][j]*px[i][j] + py[i][j]*py[i][j] + pz[i][j]*pz[i][j]);
               h_p->Fill(p);
            }
         }
      }
   }

   // 4. Drawing histograms ---------------------------------------------------
   TCanvas *c1 = new TCanvas("c1", "B+ Properties", 1200, 800);
   c1->Divide(3, 2);
   
   // Angular distributions
   c1->cd(1); 
   h_rapidity->SetLineColor(kBlue);
   h_rapidity->Draw();
   
   c1->cd(2);
   h_pseudorapidity->SetLineColor(kRed);
   h_pseudorapidity->Draw();
   
   c1->cd(3);
   h_phi->SetLineColor(kGreen+2);
   h_phi->Draw();

   // Momentum distributions (log scale)
   c1->cd(4); 
   gPad->SetLogy();
   h_pt->SetLineColor(kMagenta);
   h_pt->Draw();
   
   c1->cd(5);
   gPad->SetLogy();
   h_p->SetLineColor(kOrange+1);
   h_p->Draw();

   // 5. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    
    c1->WaitPrimitive();
}
