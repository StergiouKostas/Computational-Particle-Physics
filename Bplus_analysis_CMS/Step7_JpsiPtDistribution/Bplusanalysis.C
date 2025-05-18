#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TH1F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

void Bplusanalysis::Loop() {
    // 1. Initialize histogram
    TH1F* h_jpsi_pt = new TH1F("h_jpsi_pt", "J/#psi p_{T} distribution (1 pb^{-1}); p_{T} [MeV/c]; Events", 
                               100, 0, 20000);

    // Constants
    const double cross_section = 0.0409 * 1e-3; // Convert mbarn to pb
    const double luminosity = 1.0; // 1 pb^-1
    double scaling_factor = cross_section * luminosity;

    // 2. Event processing
    Long64_t nentries = fChain->GetEntriesFast();
    double mc_events = nentries; // Total MC events processed
    scaling_factor /= mc_events; // Normalize to MC statistics

    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        fChain->GetEntry(jentry);

        // Find J/ψ → μ+μ-
        for (int i = 0; i < chains; i++) {
            for (int j = 0; j < particles[i]; j++) {
                if (id[i][j] == 443) { // J/ψ PDG ID
                    TLorentzVector jpsi;
                    jpsi.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], mass[i][j]);
                    h_jpsi_pt->Fill(jpsi.Pt(), scaling_factor);
                }
            }
        }
    }

    // 3. Plotting
    TCanvas* c1 = new TCanvas("c1", "J/psi pT Distribution", 800, 600);
    h_jpsi_pt->SetLineColor(kBlue);
    h_jpsi_pt->SetStats(1);
    h_jpsi_pt->Draw();

    // 5. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    std::cout << "J/ψ pT distribution saved. Expected events in 1 pb^-1: " 
              << h_jpsi_pt->Integral() << std::endl;

    c1->WaitPrimitive();
}