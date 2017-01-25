#include<iostream>
#include <sstream>
using namespace std;


#include "/afs/cern.ch/user/c/cprouve/Gamma/scripts/loadCuts.h"

void makePlots(string plotname, vector<TTree*> trees)
{
  vector<string> vars = {"D0_ENDVERTEX_CHI2", "D0_IPCHI2_OWNPV", "D0_DIRA_OWNPV", "D0_FDCHI2_OWNPV", "Bu_DTF_CHI2" };
  
  TCanvas cPlot("hasi", "masi");
  cPlot.Divide(3,2);
  cPlot.cd(1);
  trees.at(0)->Draw("D0_ENDVERTEX_CHI2", "", "norm");
  trees.at(1)->Draw("D0_ENDVERTEX_CHI2", "", "norm same");
  trees.at(2)->Draw("D0_ENDVERTEX_CHI2", "", "norm same");
  cPlot.cd(2);
  trees.at(2)->Draw("D0_IPCHI2_OWNPV", "D0_IPCHI2_OWNPV < 1000", "norm");
  trees.at(1)->Draw("D0_IPCHI2_OWNPV", "", "norm same");
  trees.at(0)->Draw("D0_IPCHI2_OWNPV", "", "norm same");
  cPlot.cd(3);
  trees.at(0)->Draw("D0_DIRA_OWNPV", "D0_DIRA_OWNPV > 0.999", "norm");
  trees.at(1)->Draw("D0_DIRA_OWNPV", "", "norm same");
  trees.at(2)->Draw("D0_DIRA_OWNPV", "", "norm same");
  cPlot.cd(4);
  trees.at(2)->Draw("D0_FDCHI2_OWNPV", "D0_FDCHI2_OWNPV < 5000", "norm");
  trees.at(1)->Draw("D0_FDCHI2_OWNPV", "", "norm same");
  trees.at(0)->Draw("D0_FDCHI2_OWNPV", "", "norm same");
  cPlot.cd(5);
  trees.at(0)->Draw("Bu_DTF_CHI2", "", "norm");
  trees.at(1)->Draw("Bu_DTF_CHI2", "", "norm same");
  trees.at(2)->Draw("Bu_DTF_CHI2", "", "norm same");
  cPlot.cd(6);
  trees.at(2)->Draw("D0_FD_OWNPV", "D0_FD_OWNPV < 120", "norm");
  trees.at(1)->Draw("D0_FD_OWNPV", "", "norm same");
  trees.at(0)->Draw("D0_FD_OWNPV", "", "norm same");
  cPlot.SaveAs(plotname.c_str());
  
  
}



void optVetoCuts()
{
  TFile* mcfile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_recPreSel.root", "READ");
  TTree* mctree = (TTree*)mcfile->Get("DecayTree");

  TFile* file = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21_recPreSel.root", "READ");  
  TTree* tree = (TTree*)file->Get("DecayTree");
  
  TFile* kspipifile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi_recPreSel.root", "READ"); 
  TTree* kspipitree = (TTree*)kspipifile->Get("DecayTree");
  
  mctree->SetLineColor(kPink);
  kspipitree->SetLineColor(kGreen);
  tree->SetLineColor(kBlue);
  
  vector<TTree*> trees = {mctree, kspipitree, tree};
  //makePlots("plots/BkgOpt.pdf", trees);
  
  string dtfstring;

  TCanvas cPlot("miez", "muz");
  cPlot.Divide(3,2);
  int count = 1;
  
  loadCuts();
  for(int i = 35; i > 9; i-=5 )
  {
    dtfstring = "D0_ENDVERTEX_CHI2 < " + to_string(i);
    TCut dtfCut(dtfstring.c_str());
  
    cout << dtfstring << endl;
    cout << "    mc signal: " << mctree->GetEntries(dtfCut) << " ==> " << 100 * (float) mctree->GetEntries(dtfCut)/(float)mctree->GetEntries() << " % " << endl;
    cout << "    data bkg : " << tree->GetEntries(dtfCut && bkgCut) << " ==> " << 100 * (float) tree->GetEntries(dtfCut && bkgCut)/(float)tree->GetEntries(bkgCut) << " % " << endl;
    
    cout << "    data lbkg : " << tree->GetEntries(dtfCut && "Bu_MM < 5200") << " ==> " << 100 * (float) tree->GetEntries(dtfCut && "Bu_MM < 5200")/(float)tree->GetEntries("Bu_MM < 5200") << " % " << endl;  
  
    cout << "    mc kspipi: " << kspipitree->GetEntries(dtfCut) << " ==> " << 100 * (float) kspipitree->GetEntries(dtfCut)/(float)kspipitree->GetEntries() <<" % " << endl << endl;
  
    cPlot.cd(count);
    tree->Draw("KSCand_12", dtfCut);
    tree->Draw("KSCand_14", dtfCut, "same");
    tree->Draw("KSCand_32", dtfCut, "same");
    tree->Draw("KSCand_34", dtfCut, "same");
    tree->Draw("KSCand_13", dtfCut, "same");
    count++;

  }
  cPlot.SaveAs("plots/KSCand.pdf");
  
  
  

}
