//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May  9 13:04:24 2022 by ROOT version 6.18/05
// from TTree CollectionTree/CollectionTree
// found on file: Bplus_JpsiKplus.root
//////////////////////////////////////////////////////////

#ifndef Bplusanalysis_h
#define Bplusanalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class Bplusanalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
   Char_t          _ref;
   Char_t          Token;
   Int_t           chains;
   Int_t           particles[8];   //[chains]
   Int_t           event_number[8][100];   //[chains]
   Int_t           chain_number[8][100];   //[chains]
   Int_t           particle_number[8][100];   //[chains]
   Int_t           id[8][100];   //[chains]
   Int_t           status[8][100];   //[chains]
   Int_t           child_of[8][100];   //[chains]
   Double_t        px[8][100];   //[chains]
   Double_t        py[8][100];   //[chains]
   Double_t        pz[8][100];   //[chains]
   Double_t        pe[8][100];   //[chains]
   Double_t        pt[8][100];   //[chains]
   Double_t        mass[8][100];   //[chains]
   Double_t        phi[8][100];   //[chains]
   Double_t        rapidity[8][100];   //[chains]
   Double_t        pseudorapidity[8][100];   //[chains]
   Int_t           Run;
   Int_t           Event;
   Int_t           Time;
   Int_t           LumiBlock;
   Int_t           BCID;
   Int_t           LVL1ID;
   Double_t        Weight;
   Int_t           IEvent;
   Int_t           StatusElement;
   Int_t           LVL1TriggerType;
   vector<unsigned int> *LVL1TriggerInfo;
   vector<unsigned int> *LVL2TriggerInfo;
   vector<unsigned int> *EventFilterInfo;
   vector<string>  *StreamTagName;
   vector<string>  *StreamTagType;
   UInt_t          NPar;
   vector<long>    *Type;
   vector<float>   *PtGen;
   vector<float>   *PhiGen;
   vector<float>   *EtaGen;
   vector<float>   *MGen;
   vector<float>   *Charge;
   vector<long>    *GenStat;
   vector<long>    *GenRef;
   vector<long>    *KMothNt;
   vector<long>    *KFDauNt;
   vector<long>    *KLDauNt;
   vector<long>    *KOriVNt;
   vector<long>    *KEndVNt;
   vector<long>    *BunchNum;
   vector<float>   *RVGen;
   vector<float>   *PhiVGen;
   vector<float>   *ZVGen;
   UInt_t          NVer;
   vector<long>    *BunchV;
   vector<float>   *RV;
   vector<float>   *PhiV;
   vector<float>   *ZV;
   vector<long>    *GenRefV;
   vector<long>    *KVMothNt;
   vector<long>    *KVFDauNt;
   vector<long>    *KVLDauNt;
   UInt_t          IVPrimary;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b__ref;   //!
   TBranch        *b_Token;   //!
   TBranch        *b_chains;   //!
   TBranch        *b_particles;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_chain_number;   //!
   TBranch        *b_particle_number;   //!
   TBranch        *b_id;   //!
   TBranch        *b_status;   //!
   TBranch        *b_child_of;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_pe;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_rapidity;   //!
   TBranch        *b_pseudorapidity;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Time;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_LVL1ID;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_IEvent;   //!
   TBranch        *b_StatusElement;   //!
   TBranch        *b_LVL1TriggerType;   //!
   TBranch        *b_LVL1TriggerInfo;   //!
   TBranch        *b_LVL2TriggerInfo;   //!
   TBranch        *b_EventFilterInfo;   //!
   TBranch        *b_StreamTagName;   //!
   TBranch        *b_StreamTagType;   //!
   TBranch        *b_NPar;   //!
   TBranch        *b_Type;   //!
   TBranch        *b_PtGen;   //!
   TBranch        *b_PhiGen;   //!
   TBranch        *b_EtaGen;   //!
   TBranch        *b_MGen;   //!
   TBranch        *b_Charge;   //!
   TBranch        *b_GenStat;   //!
   TBranch        *b_GenRef;   //!
   TBranch        *b_KMothNt;   //!
   TBranch        *b_KFDauNt;   //!
   TBranch        *b_KLDauNt;   //!
   TBranch        *b_KOriVNt;   //!
   TBranch        *b_KEndVNt;   //!
   TBranch        *b_BunchNum;   //!
   TBranch        *b_RVGen;   //!
   TBranch        *b_PhiVGen;   //!
   TBranch        *b_ZVGen;   //!
   TBranch        *b_NVer;   //!
   TBranch        *b_BunchV;   //!
   TBranch        *b_RV;   //!
   TBranch        *b_PhiV;   //!
   TBranch        *b_ZV;   //!
   TBranch        *b_GenRefV;   //!
   TBranch        *b_KVMothNt;   //!
   TBranch        *b_KVFDauNt;   //!
   TBranch        *b_KVLDauNt;   //!
   TBranch        *b_IVPrimary;   //!

   Bplusanalysis(TTree *tree=0);
   virtual ~Bplusanalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Bplusanalysis_cxx
Bplusanalysis::Bplusanalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Bplus_JpsiKplus.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Bplus_JpsiKplus.root");
      }
      f->GetObject("CollectionTree",tree);

   }
   Init(tree);
}

Bplusanalysis::~Bplusanalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Bplusanalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Bplusanalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Bplusanalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   LVL1TriggerInfo = 0;
   LVL2TriggerInfo = 0;
   EventFilterInfo = 0;
   StreamTagName = 0;
   StreamTagType = 0;
   Type = 0;
   PtGen = 0;
   PhiGen = 0;
   EtaGen = 0;
   MGen = 0;
   Charge = 0;
   GenStat = 0;
   GenRef = 0;
   KMothNt = 0;
   KFDauNt = 0;
   KLDauNt = 0;
   KOriVNt = 0;
   KEndVNt = 0;
   BunchNum = 0;
   RVGen = 0;
   PhiVGen = 0;
   ZVGen = 0;
   BunchV = 0;
   RV = 0;
   PhiV = 0;
   ZV = 0;
   GenRefV = 0;
   KVMothNt = 0;
   KVFDauNt = 0;
   KVLDauNt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("_ref", &_ref, &b__ref);
   fChain->SetBranchAddress("Token", &Token, &b_Token);
   fChain->SetBranchAddress("chains", &chains, &b_chains);
   fChain->SetBranchAddress("particles", particles, &b_particles);
   fChain->SetBranchAddress("event_number", event_number, &b_event_number);
   fChain->SetBranchAddress("chain_number", chain_number, &b_chain_number);
   fChain->SetBranchAddress("particle_number", particle_number, &b_particle_number);
   fChain->SetBranchAddress("id", id, &b_id);
   fChain->SetBranchAddress("status", status, &b_status);
   fChain->SetBranchAddress("child_of", child_of, &b_child_of);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("pe", pe, &b_pe);
   fChain->SetBranchAddress("pt", pt, &b_pt);
   fChain->SetBranchAddress("mass", mass, &b_mass);
   fChain->SetBranchAddress("phi", phi, &b_phi);
   fChain->SetBranchAddress("rapidity", rapidity, &b_rapidity);
   fChain->SetBranchAddress("pseudorapidity", pseudorapidity, &b_pseudorapidity);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Time", &Time, &b_Time);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("LVL1ID", &LVL1ID, &b_LVL1ID);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("IEvent", &IEvent, &b_IEvent);
   fChain->SetBranchAddress("StatusElement", &StatusElement, &b_StatusElement);
   fChain->SetBranchAddress("LVL1TriggerType", &LVL1TriggerType, &b_LVL1TriggerType);
   fChain->SetBranchAddress("LVL1TriggerInfo", &LVL1TriggerInfo, &b_LVL1TriggerInfo);
   fChain->SetBranchAddress("LVL2TriggerInfo", &LVL2TriggerInfo, &b_LVL2TriggerInfo);
   fChain->SetBranchAddress("EventFilterInfo", &EventFilterInfo, &b_EventFilterInfo);
   fChain->SetBranchAddress("StreamTagName", &StreamTagName, &b_StreamTagName);
   fChain->SetBranchAddress("StreamTagType", &StreamTagType, &b_StreamTagType);
   fChain->SetBranchAddress("NPar", &NPar, &b_NPar);
   fChain->SetBranchAddress("Type", &Type, &b_Type);
   fChain->SetBranchAddress("PtGen", &PtGen, &b_PtGen);
   fChain->SetBranchAddress("PhiGen", &PhiGen, &b_PhiGen);
   fChain->SetBranchAddress("EtaGen", &EtaGen, &b_EtaGen);
   fChain->SetBranchAddress("MGen", &MGen, &b_MGen);
   fChain->SetBranchAddress("Charge", &Charge, &b_Charge);
   fChain->SetBranchAddress("GenStat", &GenStat, &b_GenStat);
   fChain->SetBranchAddress("GenRef", &GenRef, &b_GenRef);
   fChain->SetBranchAddress("KMothNt", &KMothNt, &b_KMothNt);
   fChain->SetBranchAddress("KFDauNt", &KFDauNt, &b_KFDauNt);
   fChain->SetBranchAddress("KLDauNt", &KLDauNt, &b_KLDauNt);
   fChain->SetBranchAddress("KOriVNt", &KOriVNt, &b_KOriVNt);
   fChain->SetBranchAddress("KEndVNt", &KEndVNt, &b_KEndVNt);
   fChain->SetBranchAddress("BunchNum", &BunchNum, &b_BunchNum);
   fChain->SetBranchAddress("RVGen", &RVGen, &b_RVGen);
   fChain->SetBranchAddress("PhiVGen", &PhiVGen, &b_PhiVGen);
   fChain->SetBranchAddress("ZVGen", &ZVGen, &b_ZVGen);
   fChain->SetBranchAddress("NVer", &NVer, &b_NVer);
   fChain->SetBranchAddress("BunchV", &BunchV, &b_BunchV);
   fChain->SetBranchAddress("RV", &RV, &b_RV);
   fChain->SetBranchAddress("PhiV", &PhiV, &b_PhiV);
   fChain->SetBranchAddress("ZV", &ZV, &b_ZV);
   fChain->SetBranchAddress("GenRefV", &GenRefV, &b_GenRefV);
   fChain->SetBranchAddress("KVMothNt", &KVMothNt, &b_KVMothNt);
   fChain->SetBranchAddress("KVFDauNt", &KVFDauNt, &b_KVFDauNt);
   fChain->SetBranchAddress("KVLDauNt", &KVLDauNt, &b_KVLDauNt);
   fChain->SetBranchAddress("IVPrimary", &IVPrimary, &b_IVPrimary);
   Notify();
}

Bool_t Bplusanalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Bplusanalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Bplusanalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Bplusanalysis_cxx
