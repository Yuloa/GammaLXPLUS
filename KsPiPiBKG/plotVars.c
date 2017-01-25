#include<iostream>
#include <sstream>
using namespace std;

#include "loadRectangularCuts.h"

void plotVars()
{
  TFile* mcfile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi.root", "READ");
  TTree* mctree = (TTree*)mcfile->Get("Bu2D0KTuple/DecayTree");
  
  TFile* file = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21.root", "READ");
  TTree* tree = (TTree*)file->Get("Bu2D0KTuple/DecayTree");
  
  TCut bkgCut("Bu_MM > 5400 && Bu_MM < 5900");
  
  TCut L0DecCut("Bu_L0Global_Dec==1") ;
  TCut L0HadTOSCut("Bu_L0HadronDecision_TOS") ;
  TCut L0TISCut("Bu_L0Global_TIS==1 && Bu_L0HadronDecision_TOS==0" );
  TCut Hlt1TOSCut("Bu_Hlt1TrackAllL0Decision_TOS==1") ;
  TCut Hlt2TopoTOSCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS==1||Bu_Hlt2Topo3BodyBBDTDecision_TOS==1||Bu_Hlt2Topo4BodyBBDTDecision_TOS==1)") ;
  TCut triggerCut = L0DecCut && Hlt1TOSCut && Hlt2TopoTOSCut && (L0HadTOSCut || L0TISCut);
  TCut sanityCut(" Pion1_PT<20000 && Pion2_PT<20000 && Pion3_PT<20000 && Pion4_PT<20000 && Kaon_PT<20000");
  TCut D0Mass("abs(D0_MM -1864) <= 25 && D0_OWNPV_Z - Bu_OWNPV_Z >= 0");
  TCut KaonCut("Kaon_hasRich==1 && Kaon_PIDK > 4");
  
  TCut idcut("abs(Bu_TRUEID)==521 && abs(Kaon_TRUEID)==321 && abs(D0_TRUEID)==421 && abs(Pion1_TRUEID)==211 && abs(Pion2_TRUEID)==211 && abs(Pion3_TRUEID)==211 && abs(Pion4_TRUEID)==211");  
  TCut motherid("abs(D0_MC_MOTHER_ID)==521 && abs(Kaon_MC_MOTHER_ID)==521 && abs(Pion1_MC_MOTHER_ID)==421 && abs(Pion2_MC_MOTHER_ID)==421 && abs(Pion3_MC_MOTHER_ID)==421 && abs(Pion4_MC_MOTHER_ID)==421 && D0_MC_MOTHER_ID == Kaon_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion2_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion3_MC_MOTHER_ID && Pion1_MC_MOTHER_ID == Pion4_MC_MOTHER_ID");
  TCut tmCut = idcut && motherid;
  
  TCut mycut = triggerCut && sanityCut && D0Mass && KaonCut;
  
  vector<string> plotVar = { "Bu_MM", "Bu_DIRA_OWNPV", "Bu_FDCHI2_OWNPV", "Bu_IPCHI2_OWNPV", "D0_MM", "D0_DIRA_OWNPV", "D0_IPCHI2_OWNPV", "D0_OWNPV_Z - Bu_OWNPV_Z", "Kaon_PIDK", "Kaon_P", "Kaon_IPCHI2_OWNPV", "Bu_DTF_CHI2"};
  

  TCanvas cPlot("cPlot", "cPlot");
  cPlot.Divide(3,3);
  tree->SetLineColor(kBlue);
  mctree->SetLineColor(kPink);
  
  cPlot.cd(1);
  mctree->Draw("Bu_DIRA_OWNPV", "Bu_DIRA_OWNPV > 0.9998" && tmCut && mycut, "norm");
  tree->Draw("Bu_DIRA_OWNPV", "Bu_DIRA_OWNPV > 0.9998"&& bkgCut && mycut, "norm same");

  cPlot.cd(2);
  tree->Draw("Bu_FDCHI2_OWNPV", "Bu_FDCHI2_OWNPV < 1000"&& bkgCut && mycut, "norm");
  mctree->Draw("Bu_FDCHI2_OWNPV", "Bu_FDCHI2_OWNPV < 1000" && tmCut && mycut, "norm same");
  
  cPlot.cd(3);
  mctree->Draw("D0_DIRA_OWNPV", "D0_DIRA_OWNPV > 0.985" && tmCut && mycut, "norm");
  tree->Draw("D0_DIRA_OWNPV", "D0_DIRA_OWNPV > 0.985"&& bkgCut && mycut, "norm same");
  
  cPlot.cd(4);
  tree->Draw("D0_IPCHI2_OWNPV", "D0_IPCHI2_OWNPV < 100"&& bkgCut && mycut, "norm ");
  mctree->Draw("D0_IPCHI2_OWNPV", "D0_IPCHI2_OWNPV < 100" && tmCut && mycut, "norm same");
  
  cPlot.cd(5);
  tree->Draw("Kaon_P", "Kaon_P < 150000"&& bkgCut && mycut, "norm");
  mctree->Draw("Kaon_P", "Kaon_P < 150000" && tmCut && mycut, "norm same");
  
  cPlot.cd(6);
  tree->Draw("Kaon_IPCHI2_OWNPV", "Kaon_IPCHI2_OWNPV < 100"&& bkgCut && mycut, "norm");
  mctree->Draw("Kaon_IPCHI2_OWNPV", "Kaon_IPCHI2_OWNPV <  100" && mycut, "norm same");
  
  cPlot.cd(7);
  mctree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120" && tmCut && mycut, "norm");
  tree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120"&& bkgCut && mycut, "norm same");
  
  cPlot.cd(8);
  tree->Draw("Pion1_PIDK", "Pion1_PIDK < 30 && Pion1_PIDK > -80"&& bkgCut && mycut, "norm");
  mctree->Draw("Pion1_PIDK", "Pion1_PIDK < 30 && Pion1_PIDK > -80" && tmCut && mycut, "norm same");  
  
  cPlot.cd(9);
  tree->Draw("Pion2_PIDK", "Pion2_PIDK < 30 && Pion2_PIDK > -80"&& bkgCut && mycut, "norm");
  mctree->Draw("Pion2_PIDK", "Pion2_PIDK < 30 && Pion2_PIDK > -80" && tmCut && mycut, "norm same");


  cPlot.SaveAs("plots/cutVars.pdf");  
}
