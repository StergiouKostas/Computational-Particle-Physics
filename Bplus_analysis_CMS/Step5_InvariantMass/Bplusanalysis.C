#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TLorentzVector.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>

void Bplusanalysis::Loop() {
    // 1. Initialize histograms
    // B+ mass range: 4000-7000 MeV/c² (expected peak at 5279 MeV/c²)
    TH1F* h_inv_mass = new TH1F("h_inv_mass", "B^{+} Invariant Mass; Mass [MeV/c^{2}]; Counts", 
                                200, 4000, 7000);

    // 2. Event processing
    Long64_t nentries = fChain->GetEntriesFast();
    std::cout << "Processing " << nentries << " events..." << std::endl;

    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        fChain->GetEntry(jentry);

        // Store all particles in the event
        std::vector<TLorentzVector> muons_plus, muons_minus, positive_particles;

        // Loop through all particles
        for (int i = 0; i < chains; i++) {
            for (int j = 0; j < particles[i]; j++) {
                TLorentzVector p;
                p.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], mass[i][j]);

                // Particle selection:
                if (id[i][j] == -13) {         // μ⁻
                    muons_minus.push_back(p);
                }
                else if (id[i][j] == 13) {     // μ⁺
                    muons_plus.push_back(p);
                }
                else if (id[i][j] > 0) {       // Positive particles (π⁺, K⁺, p, e⁺, etc.)
                    positive_particles.push_back(p);
                }
            }
        }

        // 3. Calculate invariant mass for all combinations
        // First pair muons to reconstruct J/ψ
        for (size_t i = 0; i < muons_plus.size(); i++) {
            for (size_t j = 0; j < muons_minus.size(); j++) {
                TLorentzVector jpsi = muons_plus[i] + muons_minus[j];
                
                // Select only J/ψ candidates (mass window 3.0-3.2 GeV)
                if (jpsi.M() < 3000 || jpsi.M() > 3200) continue;

                // Combine with all positive particles
                for (size_t k = 0; k < positive_particles.size(); k++) {
                    // Avoid double-counting the muon from J/ψ
                    if (&positive_particles[k] == &muons_plus[i]) continue;
                    
                    // Reconstruct B+ candidate
                    TLorentzVector B_candidate = jpsi + positive_particles[k];
                    h_inv_mass->Fill(B_candidate.M());
                }
            }
        }
    }

    // 4. Plotting
    TCanvas* c1 = new TCanvas("c1", "B+ Invariant Mass", 800, 600);
    h_inv_mass->SetLineColor(kRed);
    h_inv_mass->SetStats(1);  // Show statistics box
    h_inv_mass->Draw();

    // Optional: Fit Gaussian around B+ mass peak
    // h_inv_mass->Fit("gaus", "", "", 5200, 5400);

    // 5. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    
    c1->WaitPrimitive();
}