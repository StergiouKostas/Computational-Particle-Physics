#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TH2F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

void Bplusanalysis::Loop() {
    // 1. Initialize histograms for optimization
    TH2F* h_acceptance = new TH2F("h_acceptance", "Optimal Detector Coverage; Rapidity (y); p_{T} [MeV/c]",
                                  100, -5, 5,    // Rapidity range
                                  100, 0, 10000); // pT range

    TH1F* h_eff_vs_pt = new TH1F("h_eff_vs_pt", "Reconstruction Efficiency vs p_{T}; p_{T} [GeV/c]; Efficiency",
                                 100, 0, 10);  // Changed to GeV

    // Counters
    int nTotal = 0, nReconstructed = 0;

    // 2. Event processing
    Long64_t nentries = fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        fChain->GetEntry(jentry);
        nTotal++;

        TLorentzVector bPlus, jpsi, kPlus;
        bool foundBplus = false;

        // Particle identification
        for (int i = 0; i < chains; i++) {
            for (int j = 0; j < particles[i]; j++) {
                if (id[i][j] == 521) { // B+
                    bPlus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], mass[i][j]);
                    foundBplus = true;
                }
                else if (id[i][j] == 443) { // J/ψ
                    jpsi.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], mass[i][j]);
                }
                else if (id[i][j] == 321) { // K+
                    kPlus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], mass[i][j]);
                }
            }
        }

        // 3. Fill histograms if B+ → J/ψ K+ is found
        if (foundBplus && jpsi.P() > 0 && kPlus.P() > 0) {
            nReconstructed++;
            
            // Acceptance map
            h_acceptance->Fill(bPlus.Rapidity(), bPlus.Pt());
            
            // Efficiency vs pT (convert to GeV when filling)
            h_eff_vs_pt->Fill(bPlus.Pt()/1000.);
        }
    }

    // 4. Calculate efficiency
    if (nTotal > 0) {
        h_eff_vs_pt->Scale(1.0/nTotal);
    }

    // 5. Plotting
    TCanvas* c1 = new TCanvas("c1", "Detector Optimization", 1200, 600);
    c1->Divide(2, 1);
    
    c1->cd(1);
    h_acceptance->Draw("COLZ");
    
    c1->cd(2);
    h_eff_vs_pt->Draw();

    // 5. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    std::cout << "Optimal coverage: |y| < " << h_acceptance->GetMean(1) 
              << ", pT > " << h_eff_vs_pt->GetMean()*1000 << " MeV/c" << std::endl;

    c1->WaitPrimitive();
}