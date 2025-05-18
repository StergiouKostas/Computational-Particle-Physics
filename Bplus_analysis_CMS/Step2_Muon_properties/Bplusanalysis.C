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
   // 1. Initialize histograms ------------------------------------------------
   // For μ+
   TH1F *h_muplus_eta = new TH1F("h_muplus_eta", "#mu^{+} Pseudorapidity; #eta; Counts", 100, -5, 5);
   TH1F *h_muplus_phi = new TH1F("h_muplus_phi", "#mu^{+} Azimuthal Angle; #phi [rad]; Counts", 100, -TMath::Pi(), TMath::Pi());
   TH1F *h_muplus_pt = new TH1F("h_muplus_pt", "#mu^{+} p_{T}; p_{T} [MeV/c]; Counts", 100, 0, 10000);
   
   // For μ-
   TH1F *h_muminus_eta = new TH1F("h_muminus_eta", "#mu^{-} Pseudorapidity; #eta; Counts", 100, -5, 5);
   TH1F *h_muminus_phi = new TH1F("h_muminus_phi", "#mu^{-} Azimuthal Angle; #phi [rad]; Counts", 100, -TMath::Pi(), TMath::Pi());
   TH1F *h_muminus_pt = new TH1F("h_muminus_pt", "#mu^{-} p_{T}; p_{T} [MeV/c]; Counts", 100, 0, 10000);

   // 2. Event processing -----------------------------------------------------
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "Processing " << nentries << " events for muons..." << std::endl;

   for (Long64_t jentry = 0; jentry < nentries; jentry++) {
      if (fChain->GetEntry(jentry) <= 0) continue;

      for (int i = 0; i < chains; i++) {
         for (int j = 0; j < particles[i]; j++) {
            
            // Check for μ+ (PDG ID = -13)
            if (id[i][j] == -13) {
               h_muplus_eta->Fill(pseudorapidity[i][j]);
               h_muplus_phi->Fill(phi[i][j]);
               h_muplus_pt->Fill(pt[i][j]);
            }
            
            // Check for μ- (PDG ID = 13)
            if (id[i][j] == 13) {
               h_muminus_eta->Fill(pseudorapidity[i][j]);
               h_muminus_phi->Fill(phi[i][j]);
               h_muminus_pt->Fill(pt[i][j]);
            }
         }
      }
   }

   // 3. Drawing --------------------------------------------------------------
   TCanvas *c_muons = new TCanvas("c_muons", "Muon Properties", 1200, 800);
   c_muons->Divide(3, 2);
   
   // μ+ distributions
   c_muons->cd(1);
   h_muplus_eta->SetLineColor(kRed);
   h_muplus_eta->Draw();
   
   c_muons->cd(2);
   h_muplus_phi->SetLineColor(kRed);
   h_muplus_phi->Draw();
   
   c_muons->cd(3);
   gPad->SetLogy();
   h_muplus_pt->SetLineColor(kRed);
   h_muplus_pt->Draw();

   // μ- distributions
   c_muons->cd(4);
   h_muminus_eta->SetLineColor(kBlue);
   h_muminus_eta->Draw();
   
   c_muons->cd(5);
   h_muminus_phi->SetLineColor(kBlue);
   h_muminus_phi->Draw();
   
   c_muons->cd(6);
   gPad->SetLogy();
   h_muminus_pt->SetLineColor(kBlue);
   h_muminus_pt->Draw();

   // 4. Keep the plot open without saving
   std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
   std::cout << "Close the window to continue..." << std::endl;
    
   c_muons->WaitPrimitive();
}