#include<iostream>
#include <sstream>
using namespace std;

#include "loadRectangularCuts.h"

void dtfCut()
{
  TFile* mcfile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_presel.root", "READ");
  TTree* mctree = (TTree*)mcfile->Get("DecayTree");
  
  TFile* file = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21_presel.root", "READ");
  TTree* tree = (TTree*)file->Get("DecayTree");
  
  TCut bkgCut("Bu_MM > 5400 && Bu_MM < 5900");
  
  TCut mycuts;
  for(int c =0; c < recCuts.size()-1; c++)
    mycuts = mycuts && recCuts.at(c);
  
  vector<string> dtfCuts = {"200", "150", "100", "50", "45", "40", "35", "30", "25", "20", "15", "10", "5"};
  string dtfstring;
    
  for(int i = 0; i < dtfCuts.size(); i++)
  {
    
    dtfstring = "Bu_DTF_CHI2 < " + dtfCuts.at(i);
    TCut varCut(dtfstring.c_str());
    
    cout << "Cut: " << dtfCuts.at(i) << endl;
    cout << "signal efficiency: " << (float)mctree->GetEntries(mycuts && varCut)/(float)mctree->GetEntries(mycuts) << endl;
    cout << "bkg efficiency   : " <<  (float)tree->GetEntries(mycuts && bkgCut && varCut)/(float)tree->GetEntries(mycuts && bkgCut) << endl << endl;
  }

  /*
  TH1D* hist = new TH1D("hist", "hist", 100, 0, 250);                                                                                                       
  TH1D* mchist = new TH1D("mchist", "mchist", 100, 0, 250);                                                                                                 

  tree->Draw("Bu_DTF_CHI2 >> hist", mycuts && bkgCut);
  mctree->Draw("Bu_DTF_CHI2 >> mchist", mycuts );
    hist->SetLineColor(kBlue);
  mchist->SetLineColor(kPink);
  

  TCanvas cPlot("hasi", "masi");
  hist->DrawNormalized();
  mchist->DrawNormalized("same");
  cPlot.SaveAs("DTFCHI2_Cut.pdf");
  */
}
