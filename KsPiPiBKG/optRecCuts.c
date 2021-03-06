#include<iostream>
#include <sstream>
using namespace std;


#include "/afs/cern.ch/user/c/cprouve/Gamma/scripts/loadCuts.h"

void optRecCuts()
{
  loadCuts();
  
  TFile* mcfile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_recCuts.root", "READ");
  //TTree* mctree = (TTree*)mcfile->Get("Bu2D0KTuple/DecayTree");
  TTree* mctree = (TTree*)mcfile->Get("DecayTree");

  TFile* file = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21_recCuts.root", "READ");  
  //TTree* tree = (TTree*)file->Get("Bu2D0KTuple/DecayTree");
  TTree* tree = (TTree*)file->Get("DecayTree");
  
  TFile* kspipifile = new TFile("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi_recCuts.root", "READ"); 
  //TTree* kspipitree = (TTree*)kspipifile->Get("Bu2D0KTuple/DecayTree");
  TTree* kspipitree = (TTree*)kspipifile->Get("DecayTree");
  
  //TCut kp1("Kaon_P > 8000");
  //TCut kp2("Kaon_P > 10000");
  TCanvas cPlot("cPlot", "cPlot");
  string dtfstring;
  int count = 1;  
  tree->Draw("Bu_MM");
  
  for(int i = 25; i < 81; i+=5 )
  {
    dtfstring = "Bu_DTF_CHI2 < " + to_string(i);
    TCut dtfCut(dtfstring.c_str());
    cout << dtfstring << endl;
    cout << "    mc signal: " << mctree->GetEntries(dtfCut) << " ==> " << 100 * (float) mctree->GetEntries(dtfCut)/(float)mctree->GetEntries() << " % " << endl;
    cout << "    data bkg : " << tree->GetEntries(dtfCut && bkgCut) << " ==> " << 100 * (float) tree->GetEntries(dtfCut && bkgCut)/(float)tree->GetEntries(bkgCut) << " % " << endl;
    cout << "    data lbkg : " << tree->GetEntries(dtfCut && "Bu_MM < 5200") << " ==> " << 100 * (float) tree->GetEntries(dtfCut && "Bu_MM < 5200")/(float)tree->GetEntries("Bu_MM < 5200") << " % " << endl;
    cout << "    mc kspipi: " << kspipitree->GetEntries(dtfCut) << " ==> " << 100 * (float) kspipitree->GetEntries(dtfCut)/(float)kspipitree->GetEntries() << " % " << endl << endl;

    tree->Draw("Bu_MM", dtfCut, "same");
  
  }
  cPlot.SaveAs("plots/Bu_MM_DTF.pdf");
  
  /*
  int n_mc = mctree->GetEntries();                                                                                               
  int n_bkg = tree->GetEntries();                                    
  int n_datasig = tree->GetEntries("Bu_MM > 5220 && Bu_MM < 5350");        
  int n_kspipi = kspipitree->GetEntries();
   
  int n_mc_kp1 = mctree->GetEntries(kp1);
  int n_bkg_kp1 = tree->GetEntries(kp1);
  int n_datasig_kp1 = tree->GetEntries(kp1 && "Bu_MM > 5220 && Bu_MM < 5350");
  int n_kspipi_kp1 = kspipitree->GetEntries(kp1);

  int n_mc_kp2 = mctree->GetEntries(kp2);
  int n_bkg_kp2 = tree->GetEntries(kp2);
  int n_datasig_kp2 = tree->GetEntries(kp2 && "Bu_MM > 5220 && Bu_MM < 5350");  
  int n_kspipi_kp2 = kspipitree->GetEntries(kp2);

  
   cout << "    mc signal: " << n_mc << endl;                                                                       
  cout << "    data bkg : " << n_bkg << endl;                                                                  
  cout << "    data sig : " << n_datasig << endl;                                                               
  cout << "    mc kspipi: " << n_kspipi << endl;
  
  cout << "After kp1: " << endl;              
  cout << "    mc signal: " << n_mc_kp1 << " ==> " << 100 * (float)n_mc_kp1/(float)n_mc << " % " << endl;
  cout << "    data bkg : " << n_bkg_kp1 << " ==> " << 100 * (float)n_bkg_kp1/(float)n_bkg << " % " << endl;
  cout << "    data sig : " << n_datasig_kp1 << " ==> " << 100 * (float)n_datasig_kp1/(float)n_datasig << " % " << endl;
  cout << "    mc kspipi: " << n_kspipi_kp1 << " ==> " << 100 * (float)n_kspipi_kp1/(float)n_kspipi << " % " << endl;
  
  cout << "After kp2: " << endl;
  cout << "    mc signal: " << n_mc_kp2 << " ==> " << 100 * (float)n_mc_kp2/(float)n_mc << " % " << endl;
  cout << "    data bkg : " << n_bkg_kp2 << " ==> " << 100 * (float)n_bkg_kp2/(float)n_bkg << " % " << endl;
  cout << "    data sig : " << n_datasig_kp2 << " ==> " << 100 * (float)n_datasig_kp2/(float)n_datasig << " % " << endl;
  cout << "    mc kspipi: " << n_kspipi_kp2 << " ==> " << 100 * (float)n_kspipi_kp2/(float)n_kspipi << " % " << endl;
  
  
  tree->SetLineColor(kBlue);        
  kspipitree->SetLineColor(kGreen);
  mctree->SetLineColor(kPink);

  TCanvas cPlot("cPlot", "cPlot");
  //cPlot.Divide(2,2);
  //cPlot.cd(1);
  tree->Draw("Bu_MM", "Bu_MM > 4800 && Bu_MM < 5900");                                                                                                      
  tree->SetLineColor(kGreen);
  tree->Draw("Bu_MM", kp1 && "Bu_MM > 4800 && Bu_MM < 5900", "same");     
  tree->SetLineColor(kBlue);
  
  //cPlot.cd(2);                                          
  //tree->Draw("Bu_DTF_CHI2", bkgCut, "norm");                         
  //mctree->Draw("Bu_DTF_CHI2", "", "same norm");
  //kspipitree->Draw("Bu_DTF_CHI2", "", "same norm");
  
  //cPlot.cd(3);
  //tree->Draw("Bu_DTF_CHI2", bkgCut && kp1, "norm");
  //mctree->Draw("Bu_DTF_CHI2", kp1, "same norm");
  //kspipitree->Draw("Bu_DTF_CHI2", kp1, "same norm");
  cPlot.SaveAs("plots/Bu_MM_opti.pdf");
  

  int n_mc = mctree->GetEntries(tmCut);
  int n_bkg = tree->GetEntries(bkgCut);
  int n_datasig = tree->GetEntries("Bu_MM > 5220 && Bu_MM < 5350");
  int n_kspipi = kspipitree->GetEntries();
  
  int n_mc_pre = mctree->GetEntries(tmCut && preselectionCut);
  int n_bkg_pre = tree->GetEntries(bkgCut && preselectionCut);  
  int n_datasig_pre = tree->GetEntries("Bu_MM > 5220 && Bu_MM < 5350" && preselectionCut);
  int n_kspipi_pre = kspipitree->GetEntries(preselectionCut);
  */
  //int n_mc_rec = mctree->GetEntries(tmCut && preselectionCut && rectangularCut);
  //int n_bkg_rec = tree->GetEntries(bkgCut && preselectionCut && rectangularCut);
  //int n_datasig_rec = tree->GetEntries("Bu_MM > 5220 && Bu_MM < 5350" && preselectionCut && rectangularCut);
  //int n_kspipi_rec = kspipitree->GetEntries(preselectionCut && rectangularCut);
  
  /*cout << "After stripping: " << endl;
  cout << "    mc signal: " << n_mc << endl;
  cout << "    data bkg : " << n_bkg << endl;
  cout << "    data sig : " << n_datasig << endl;  
  cout << "    mc kspipi: " << n_kspipi << endl;

  cout << "After preselection: " << endl;
  cout << "    mc signal: " << n_mc_pre << " ==> " << 100 * (float)n_mc_pre/(float)n_mc << " % " << endl;
  cout << "    data bkg : " << n_bkg_pre << " ==> " << 100 * (float)n_bkg_pre/(float)n_bkg << " % " << endl;
  cout << "    data sig : " << n_datasig_pre << " ==> " << 100 * (float)n_datasig_pre/(float)n_datasig << " % " << endl;
  cout << "    mc kspipi: " << n_kspipi_pre << " ==> " << 100 * (float)n_kspipi_pre/(float)n_kspipi << " % " << endl;
 
  cout << "After rectangular Cuts: " << endl;
  cout << "    mc signal: " << n_mc_rec << " ==> " << 100 * (float)n_mc_rec/(float)n_mc << " % " << endl;
  cout << "    data bkg : " << n_bkg_rec << " ==> " << 100 * (float)n_bkg_rec/(float)n_bkg << " % " << endl;
  cout << "    data sig : " << n_datasig_rec << " ==> " << 100 * (float)n_datasig_rec/(float)n_datasig << " % " << endl;
  cout << "    mc kspipi: " << n_kspipi_rec << " ==> " << 100 * (float)n_kspipi_rec/(float)n_kspipi << " % " << endl;


  
  
  tree->SetLineColor(kBlue);
  mctree->SetLineColor(kPink);
  kspipitree->SetLineColor(kGreen);
  
  TCanvas cPlot("cPlot", "cPlot");
  cPlot.Divide(2,2);
  cPlot.cd(1);
  //tree->Draw("Bu_MM", "Bu_MM > 4800 && Bu_MM < 5900");
  //tree->Draw("Bu_MM", preselectionCut && "Bu_MM > 4800 && Bu_MM < 5900");

  tree->Draw("Bu_MM", preselectionCut && rectangularCut && "Bu_MM > 4800 && Bu_MM < 5900");
  cPlot.cd(2);
  tree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120" && preselectionCut && rectangularCut && bkgCut, "norm");
  tree->SetLineColor(kMagenta);
  tree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120" && preselectionCut && rectangularCut && "Bu_MM < 5200", "norm same");
  
  mctree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120"&& preselectionCut && rectangularCut && tmCut, "same norm");
  kspipitree->Draw("Bu_DTF_CHI2", "Bu_DTF_CHI2 < 120" && preselectionCut && rectangularCut, "same norm");
  cPlot.cd(3);
  tree->SetLineColor(kBlue);
  tree->Draw("Kaon_P", "Kaon_P < 160000" && preselectionCut && rectangularCut && bkgCut, "norm");
  tree->SetLineColor(kMagenta);
  tree->Draw("Kaon_P", "Kaon_P < 160000" && preselectionCut && rectangularCut && "Bu_MM < 5200", "norm same");
  mctree->Draw("Kaon_P", "Kaon_P < 160000" && preselectionCut && rectangularCut && tmCut, "same norm");
  kspipitree->Draw("Kaon_P", "Kaon_P < 160000" && preselectionCut && rectangularCut, "same norm");
  cPlot.SaveAs("plots/CutVars.pdf");
  */  

}
