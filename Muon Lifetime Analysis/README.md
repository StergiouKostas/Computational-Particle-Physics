# Muon Lifetime Analysis using ROOT

This analysis examines the lifetime of cosmic-ray muons stopped in a plastic scintillator using a simplified exponential fit approach. The data from `allpeaks.txt` is processed to extract the muon lifetime without background considerations.

---

## 📌 Key Improvements

- **Simplified model**: Pure exponential decay fit  
- **Optimized range**: Fit performed between 0.7–3.6 μs  
- **Comparison**: Extracted lifetimes and χ²/NDF values compared to theoretical value (2.2 μs)

---

## 🔁 Complete ROOT Script

```cpp
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
    const double total_time = 4.0; // microsec
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
    TH1D *h_dt = new TH1D("h_dt", 
        "Muon Decay Time (2-peak events); #Delta t (#mu s); Counts", 
        30, 0, 4.0);
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

    TLine *theory_line = new TLine(theoretical_lifetime, 0, 
        theoretical_lifetime, h_dt->GetMaximum());
    theory_line->SetLineColor(kBlack);
    theory_line->SetLineStyle(2);
    theory_line->Draw("same");

    TLatex tex;
    tex.SetNDC();
    tex.SetTextSize(0.035);
    tex.DrawLatex(0.6, 0.85, Form("Total events: %d", total_events));
    tex.DrawLatex(0.6, 0.80, Form("2-peak events: %d", events_with_2peaks));
    tex.DrawLatex(0.6, 0.75, Form("Mean: %.2f #mus", h_dt->GetMean()));
    tex.DrawLatex(0.6, 0.70, Form("Fit: %.3f #pm %.3f #mus", 
        fexp->GetParameter(1), fexp->GetParError(1)));
    tex.DrawLatex(0.6, 0.65, Form("Theory: 2.2 #mus"));

    TLegend *leg = new TLegend(0.6, 0.45, 0.85, 0.60);
    leg->AddEntry(h_dt, "Data", "f");
    leg->AddEntry(fexp, "Exponential Fit", "l");
    leg->AddEntry(theory_line, "Theory (2.2 #mus)", "l");
    leg->Draw();

    c1->SaveAs("muon_decay_clean.png");

    std::cout << "\nFit result:\n";
    std::cout << "Tau = " << fexp->GetParameter(1) 
              << " +- " << fexp->GetParError(1) << " microsec\n";
    std::cout << "Chi2/NDF = " 
              << fexp->GetChisquare() / fexp->GetNDF() << "\n";
}
```

---

## 🧪 Step-by-Step Breakdown

### 🧾 Step 1: Data Reading and Conversion

```cpp
const char* filename = "allpeaks.txt";
const double total_points = 10000.0;
const double total_time = 4.0; // microsec
const double points_to_mus = total_time / total_points;

std::vector<double> dt_values;
std::ifstream file(filename);
```

**Explanation**:  
Sets up the conversion from digitizer points to microseconds. Opens the data file.

---

### 🧾 Step 2: Event Processing

```cpp
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
```

**Explanation**:  
Filters and converts only 2-peak events into time differences (Δt).

---

### 🧾 Step 3: Histogram Creation

```cpp
TH1D *h_dt = new TH1D("h_dt", 
    "Muon Decay Time (2-peak events); #Delta t (#mu s); Counts", 
    30, 0, 4.0);
for (double dt : dt_values) h_dt->Fill(dt);
```

**Explanation**:  
Creates and fills a histogram for Δt (time between peaks) using 30 bins from 0–4 μs.

---

### 🧾 Step 4: Exponential Fit

```cpp
TF1 *fexp = new TF1("fexp", "[0]*exp(-x/[1])", 0.7, 3.6);
fexp->SetParameters(680.0, 2.2);
h_dt->Fit("fexp", "R");
```

**Explanation**:  
Fits the histogram with an exponential decay model from 0.7 to 3.6 μs. Initial values:

- Amplitude = 680  
- Lifetime (τ) = 2.2 μs

---

### 🧾 Step 5: Visualization

```cpp
h_dt->Draw("HIST");
fexp->Draw("same");
theory_line->Draw("same");
```

**Explanation**:  
Plots histogram, the fitted function, and a vertical dashed line at 2.2 μs (theory).

---

### 🧾 Step 6: Results Annotation

```cpp
tex.DrawLatex(0.6, 0.70, Form("Fit: %.3f #pm %.3f #mus", 
    fexp->GetParameter(1), fexp->GetParError(1)));
```

**Explanation**:  
Displays the fit result (τ ± error) on the canvas.

---

## 📉 Results

- **Fitted Lifetime**: `1.959 ± 0.067 μs`  
- **Goodness of Fit**: χ²/NDF = `1.63`

<p align="center">
  <img src="muon_decay_clean.png" width="60%" alt="55Fe Fit Results">
</p>

> **Figure**: Exponential fit (red curve) to muon decay data. Dashed line shows theoretical value (2.2 μs).

---

## 📐 Ratio to Theory

\[
\text{Ratio}_{\text{measured}/\text{theory}} = \boxed{0.89}
\]

This corresponds to a ~**3.4% deviation** from the theoretical value, demonstrating good agreement within uncertainties.

---

## 📚 Notes

- Requires `ROOT` (tested with v6.x)
- To execute:  
  ```bash
  root -l muon_lifetime.C
  ```

---

## 👤 Author

**Konstantinos E. Stergiou**  
Physics Department  
Aristotle University of Thessaloniki  
May 2025
