#define Bplusanalysis_cxx
#include "Bplusanalysis.h"
#include <TH2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

void Bplusanalysis::Loop() {
    // 1. Initialize histograms
    TH2F *h_pt_corr = new TH2F("h_pt_corr", "p_{T} correlation; #mu^{+} p_{T} [MeV/c]; #mu^{-} p_{T} [MeV/c]", 
                               100, 0, 10000, 100, 0, 10000);
    TH1F *h_pt_ratio = new TH1F("h_pt_ratio", "p_{T} ratio; p_{T}^{#mu^{+}} / p_{T}^{#mu^{-}}; Counts", 
                                100, 0, 5);

    // 2. Event processing
    Long64_t nentries = fChain->GetEntriesFast();
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        fChain->GetEntry(jentry);
        
        TLorentzVector muplus, muminus;
        bool found_muplus = false, found_muminus = false;

        // Find μ+ and μ- in the event
        for (int i = 0; i < chains; i++) {
            for (int j = 0; j < particles[i]; j++) {
                if (id[i][j] == -13) { // μ+
                    muplus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], 0.10566);
                    found_muplus = true;
                }
                if (id[i][j] == 13) { // μ-
                    muminus.SetPtEtaPhiM(pt[i][j], pseudorapidity[i][j], phi[i][j], 0.10566);
                    found_muminus = true;
                }
            }
        }

        // Fill histograms if both muons found
        if (found_muplus && found_muminus) {
            h_pt_corr->Fill(muplus.Pt(), muminus.Pt());
            if (muminus.Pt() > 0) { // Avoid division by zero
                h_pt_ratio->Fill(muplus.Pt() / muminus.Pt());
            }
        }
    }

    // 3. Plotting
    TCanvas *c1 = new TCanvas("c1", "Muon pT Correlations", 1200, 600);
    c1->Divide(2, 1);
    
    c1->cd(1);
    h_pt_corr->Draw("COLZ");
    gPad->SetLogz();
    
    c1->cd(2);
    h_pt_ratio->Draw();
    
    // 4. Keep the plot open without saving
    std::cout << "Plots are displayed. Manually save them from the GUI." << std::endl;
    std::cout << "Close the window to continue..." << std::endl;
    
    c1->WaitPrimitive();
}