// analyze_55Fe.C
// ROOT script for 55Fe spectrum analysis

void analyze_55Fe() {
    // 1. Create histogram
    TH1F *spc4 = new TH1F("spc4", "55Fe Spectrum;Channel;Counts", 1024, 0, 1024);

    // 2. Read data file
    FILE *fp4 = fopen("QMO_5310.TXT", "r");
    if (!fp4) {
        std::cerr << "Error: Cannot open file!" << std::endl;
        return;
    }

    char line[80];
    int chnl, entr, nn;
    while (fgets(line, 80, fp4)) {
        sscanf(line, "%d,%d %d", &chnl, &entr, &nn);
        spc4->SetBinContent(chnl, entr);
    }
    fclose(fp4);

    // 3. Define fit function (3 Gaussians + linear background)
    TF1 *fitFunc = new TF1("fitFunc", 
        "[0]*exp(-0.5*((x-[1])/[2])^2) + "  // 5.9 keV peak
        "[3]*exp(-0.5*((x-[4])/[5])^2) + "  // 6.5 keV peak
        "[6]*exp(-0.5*((x-[7])/[8])^2) + "  // Escape peak (~2.7 keV)
        "[9] + [10]*x",                     // Linear background
        0, 1024);

    // 4. Initial parameters (adjust based on your data)
    fitFunc->SetParameters(
        1120, 220, 30,    // 5.9 keV peak (amplitude, mean, sigma)
        350, 430, 100,     // 6.5 keV peak
        5850, 180, 20,     // Escape peak
        -3, 0.1           // Background (constant + slope)
    );

    // 5. Perform the fit
    spc4->Fit("fitFunc", "R");  // "R" for fit range
    
    // 6. Plot results
    TCanvas *c2 = new TCanvas("c2", "55Fe Fit Results", 1000, 800);
    spc4->Draw();
    fitFunc->Draw("same");

    // Draw individual components
    TF1 *g1 = new TF1("g1", "gaus", 0, 1024);
    g1->SetParameters(fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2));
    g1->SetLineColor(kRed);
    g1->Draw("same");

    TF1 *g2 = new TF1("g2", "gaus", 0, 1024);
    g2->SetParameters(fitFunc->GetParameter(3), fitFunc->GetParameter(4), fitFunc->GetParameter(5));
    g2->SetLineColor(kBlue);
    g2->Draw("same");

    TF1 *g3 = new TF1("g3", "gaus", 0, 1024);
    g3->SetParameters(fitFunc->GetParameter(6), fitFunc->GetParameter(7), fitFunc->GetParameter(8));
    g3->SetLineColor(kGreen);
    g3->Draw("same");

    // 7. Calculate peak ratios
    double area_59keV = g1->Integral(g1->GetParameter(1)-3*g1->GetParameter(2), 
                             g1->GetParameter(1)+3*g1->GetParameter(2));
    double area_escape = g3->Integral(g3->GetParameter(1)-3*g3->GetParameter(2), 
                             g3->GetParameter(1)+3*g3->GetParameter(2));

    std::cout << "\nResults:\n";
    std::cout << "5.9 keV peak area: " << area_59keV << "\n";
    std::cout << "Escape peak area: " << area_escape << "\n";
    std::cout << "Ratio (5.9keV/Escape): " << area_59keV/area_escape << "\n";

    // 7. Save results
    c2->SaveAs("55Fe_fit_results.png");
}