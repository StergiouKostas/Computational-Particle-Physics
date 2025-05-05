# Muon Lifetime Analysis using ROOT

This repository contains a ROOT-based analysis of the **muon lifetime** using cosmic-ray data. A plastic scintillator was used to detect muons stopped in the material, and the time between peaks was extracted from digitized waveforms.

![AUTH Logo](auth_logo_bw.png)

---

## 📄 Summary

This simplified analysis:

- Uses only **2-peak events** to estimate decay time
- Applies a **pure exponential fit**
- Fits in the optimized range **0.7–3.6 μs**
- Compares measured lifetime with theoretical value (**2.2 μs**)

---

## 📁 Files

- `muon_lifetime.C`: ROOT macro for processing and fitting
- `allpeaks.txt`: Input data (not included in repo)
- `muon_decay_clean.png`: Output plot with fit
- `README.md`: This file

---

## 🔬 Analysis Steps

### ✅ Step 1: Data Reading and Conversion

```cpp
const char* filename = "allpeaks.txt";
const double total_points = 10000.0;
const double total_time = 4.0; // microsec
const double points_to_mus = total_time / total_points;

std::vector<double> dt_values;
std::ifstream file(filename);
```

### ✅ Step 2: Event Processing

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

### ✅ Step 3: Histogram Creation

```cpp
TH1D *h_dt = new TH1D("h_dt", 
    "Muon Decay Time (2-peak events); #Delta t (#mu s); Counts", 
    30, 0, 4.0);
for (double dt : dt_values) h_dt->Fill(dt);
```

### ✅ Step 4: Exponential Fit

```cpp
TF1 *fexp = new TF1("fexp", "[0]*exp(-x/[1])", 0.7, 3.6);
fexp->SetParameters(680.0, 2.2);
h_dt->Fit("fexp", "R");
```

### ✅ Step 5: Visualization

```cpp
h_dt->Draw("HIST");
fexp->Draw("same");
theory_line->Draw("same");
```

### ✅ Step 6: Results Annotation

```cpp
tex.DrawLatex(0.6, 0.70, Form("Fit: %.3f #pm %.3f #mus", 
    fexp->GetParameter(1), fexp->GetParError(1)));
```

---

## 📊 Final Results

- **Fitted lifetime**: `1.959 ± 0.067 μs`
- **χ²/NDF**: `1.63`
- **Theoretical lifetime**: `2.2 μs`
- **Measured/Theory ratio**: `0.89` (≈ 3.4% deviation)

![Fit plot](muon_decay_clean.png)

---

## 📌 Conclusion

This ROOT-based method effectively estimates the muon lifetime from raw waveform data. The simplified exponential model yields a result close to the expected value with acceptable statistical precision.

---

## 📚 Dependencies

- ROOT (tested with v6.xx)
- Standard C++ headers

To run:

```bash
root -l muon_lifetime.C
```

---

## 👤 Author

Konstantinos E. Stergiou  
Physics Department  
Aristotle University of Thessaloniki  
May 2025
