#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TH2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

void Bplusanalysis::Loop() {
    // 1. Initialize histograms
    TH1F* h_dR = new TH1F("h_dR", "#Delta R between #mu^{+} and #mu^{-}; #Delta R; Counts", 100, 0, 5);
    TH2F* h_dR_vs_pt = new TH2F("h_dR_vs_pt", "#Delta R vs J/#psi p_{T}; J/#psi p_{T} [GeV/c]; #Delta R", 
                                100, 0, 20, 100, 0, 5);  // Changed to GeV

    // 2. Event processing
    Long64_t nentries = fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        fChain->GetEntry(jentry);

        TLorentzVector muplus, muminus, jpsi;
        bool found_pair = false;

        // Find μ+ and μ- pairs
        for (int i = 0; i < chains; i++) {
            for (int j = 0; j < particles[i]; j++) {
                if (id[i][j] == -13) { // μ+
                    muplus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], 0.10566);
                }
                if (id[i][j] == 13) { // μ-
                    muminus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], 0.10566);
                }
            }
        }

        // Calculate ΔR and J/ψ properties if both muons found
        if (muplus.P() > 0 && muminus.P() > 0) {
            jpsi = muplus + muminus;
            double deltaEta = muplus.Eta() - muminus.Eta();
            double deltaPhi = TVector2::Phi_mpi_pi(muplus.Phi() - muminus.Phi());
            double deltaR = TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);

            h_dR->Fill(deltaR);
            h_dR_vs_pt->Fill(jpsi.Pt()/1000., deltaR);  // Convert to GeV when filling
        }
    }

    // 3. Plotting
    TCanvas* c1 = new TCanvas("c1", "Delta R Analysis", 1200, 600);
    c1->Divide(2, 1);

    c1->cd(1);
    h_dR->SetLineColor(kBlue);
    h_dR->Draw();

    c1->cd(2);
    h_dR_vs_pt->Draw("COLZ");
    gPad->SetLogz();

    // 4. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    
    c1->WaitPrimitive();
}