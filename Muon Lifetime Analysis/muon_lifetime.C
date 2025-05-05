#include <TH1D.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLine.h>
#include <TLatex.h>
#include <TLegend.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

void muon_lifetime() {
    const char* filename = "allpeaks.txt";
    const double total_points = 10000.0;
    const double total_time = 4.0; // μs
    const double points_to_mus = total_time / total_points;
    const double theoretical_lifetime = 2.2;

    std::vector<double> dt_values;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int total_events = 0, events_with_2peaks = 0;
    while (std::getline(file, line)) {
        total_events++;
        std::istringstream iss(line);
        int evt, peaks;
        double pos0, volt0, pos, volt;
        if (!(iss >> evt >> peaks >> pos0 >> volt0 >> pos >> volt)) continue;
        if (peaks == 2) {
            events_with_2peaks++;
            double delta_time = (pos - pos0) * points_to_mus;
            dt_values.push_back(delta_time);
        }
    }
    file.close();

    TCanvas *c1 = new TCanvas("c1", "Muon Decay Time", 800, 600);
    TH1D *h_dt = new TH1D("h_dt", "Muon Decay Time (2-peak events); #Delta t (#mu s); Counts", 30, 0, 4.0);
    for (double dt : dt_values) h_dt->Fill(dt);

    TF1 *fexp = new TF1("fexp", "[0]*exp(-x/[1])", 0.7, 3.6);
    fexp->SetParameters(680.0, 2.2);
    fexp->SetLineColor(kRed);
    fexp->SetLineWidth(3);
    h_dt->Fit("fexp", "R");

    h_dt->SetFillColor(kBlue-9);
    h_dt->SetLineColor(kBlue);
    h_dt->Draw("HIST");
    fexp->Draw("same");

    TLine *theory_line = new TLine(theoretical_lifetime, 0, theoretical_lifetime, h_dt->GetMaximum());
    theory_line->SetLineColor(kBlack);
    theory_line->SetLineStyle(2);
    theory_line->Draw("same");

    TLatex tex;
    tex.SetNDC();
    tex.SetTextSize(0.035);
    tex.DrawLatex(0.6, 0.85, Form("Total events: %d", total_events));
    tex.DrawLatex(0.6, 0.80, Form("2-peak events: %d", events_with_2peaks));
    tex.DrawLatex(0.6, 0.75, Form("Mean: %.2f #mus", h_dt->GetMean()));
    tex.DrawLatex(0.6, 0.70, Form("Fit: %.3f #pm %.3f #mus", fexp->GetParameter(1), fexp->GetParError(1)));
    tex.DrawLatex(0.6, 0.65, Form("Theory: 2.2 #mus"));

    TLegend *leg = new TLegend(0.6, 0.45, 0.85, 0.60);
    leg->AddEntry(h_dt, "Data", "f");
    leg->AddEntry(fexp, "Exponential Fit", "l");
    leg->AddEntry(theory_line, "Theory (2.2 #mus)", "l");
    leg->Draw();

    c1->SaveAs("muon_decay_clean.png");

    std::cout << "\nFit result:\n";
    std::cout << "Tau = " << fexp->GetParameter(1) << " ± " << fexp->GetParError(1) << " μs\n";
    std::cout << "Chi2/NDF = " << fexp->GetChisquare() / fexp->GetNDF() << "\n";
}
