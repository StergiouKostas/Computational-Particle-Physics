#!/bin/bash

cd "$(dirname "$0")"
OUTPUT_DIR="$PWD"

cd ..
root -l <<EOF
.L Step7_JpsiPtDistribution/Bplusanalysis.C+
TFile::Open("data/Bplus_JpsiKplus.root")
Bplusanalysis t((TTree*)gFile->Get("CollectionTree"))
gSystem->cd("$OUTPUT_DIR")
t.Loop()
.q
EOF