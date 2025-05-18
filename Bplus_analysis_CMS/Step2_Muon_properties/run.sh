#!/bin/bash

cd "$(dirname "$0")"
OUTPUT_DIR="$PWD"  # Remember current directory

cd ..
root -l <<EOF
.L Step2_Muon_properties/Bplusanalysis.C+
TFile::Open("data/Bplus_JpsiKplus.root")
Bplusanalysis t((TTree*)gFile->Get("CollectionTree"))
gSystem->cd("$OUTPUT_DIR")  // Change saving folder
t.Loop()
.q
EOF