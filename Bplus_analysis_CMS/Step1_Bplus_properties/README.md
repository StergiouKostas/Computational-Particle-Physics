# B⁺ Kinematic Analysis - Step 1

## Description
This code performs the first step of the B⁺ → J/ψ K⁺ analysis, focusing on the kinematic properties of the B⁺ meson. The analysis includes:

## Key Features
- **Histogram Creation** for:
  - Rapidity (y)
  - Pseudorapidity (η)
  - Azimuthal angle (φ)
  - Transverse momentum (p<sub>T</sub>)
  - Total momentum (p)

- **Event Processing**:
  - Processes Monte Carlo events from ROOT TTree
  - Identifies B⁺ mesons (PDG ID 521)
  - Fills histograms with kinematic variables

- **Visualization**:
  - Creates a 3×2 grid canvas
  - Displays all kinematic distributions
  - Uses logarithmic scale for momentum plots
  - Applies distinct colors for each variable

## Physics Quantities Studied
| Variable | Range | Units |
|----------|-------|-------|
| Rapidity | [-10, 10] | - |
| Pseudorapidity | [-5, 5] | - |
| φ | [-π, π] | radians |
| p<sub>T</sub> | [0, 25000] | MeV/c |
| p | [0, 60000] | MeV/c |

## Usage
The code keeps the plots open for manual inspection and saving through ROOT's GUI interface. Close the window to terminate the program.

![B+ Properties Visualization](figures/Bplus_properties.png)
