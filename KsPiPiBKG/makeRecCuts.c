#include<iostream>
#include <sstream>
using namespace std;

#include "/afs/cern.ch/user/c/cprouve/Gamma/scripts/loadCuts.h"

void makeCuts(string oldname, string newname, TCut addCut)
{
  TFile* oldfile = new TFile(oldname.c_str(), "READ");  
  TTree* oldtree = (TTree*)oldfile->Get("Bu2D0KTuple/DecayTree");
  
  TFile* newfile = new TFile(newname.c_str(), "RECREATE");
  TTree* newtree = oldtree->CopyTree(preselectionCut && rectangularCut && addCut);
  newfile->Write();
  newfile->Close();
  

}



void makeRecCuts()
{
  loadCuts();
  

  TCut idcut("abs(Bu_TRUEID)==521 && abs(Kaon_TRUEID)==321 && abs(D0_TRUEID)==421 && abs(Pion1_TRUEID)==211 && abs(Pion2_TRUEID)==211 && abs(Pion3_TRUEID)==211 && abs(Pion4_TRUEID)==211");
  TCut motherid("abs(D0_MC_MOTHER_ID)==521 && abs(Kaon_MC_MOTHER_ID)==521 && abs(Pion1_MC_MOTHER_ID)==421 && abs(Pion2_MC_MOTHER_ID)==421 && abs(Pion3_MC_MOTHER_ID)==421 && abs(Pion4_MC_MOTHER_ID)==421 && D0_MC_MOTHER_ID == Kaon_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion2_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion3_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion4_MC_MOTHER_ID");
  TCut tmCut = idcut && motherid;

  TCut addCut("Bu_DTF_CHI2 < 60 && Kaon_P > 8000");
  
  //makeCuts("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21.root",
  //        "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21_recPreSel.root", addCut);
  

  makeCuts("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi.root",
           "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_recPreSel.root", tmCut && addCut);

  //makeCuts("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi.root",
  //        "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi_recPreSel.root", addCut);

}

  
