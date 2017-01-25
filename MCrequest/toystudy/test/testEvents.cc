#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <iostream>
using namespace std;

int main(){
  const unsigned int nbody = 4;
  
  const double mass_D0 = 1.86486;    //GeV
  const double mass_pi = 0.13957018;  // GeV
  
  
  TLorentzVector D0( 0.0, 0.0, 0.0, mass_D0 );
  const vector<double> fs_masses = {mass_pi, mass_pi, mass_pi, mass_pi};
  
  TGenPhaseSpace generator;
  generator.SetDecay(D0, nbody, fs_masses.data());

  TFile file("/afs/cern.ch/user/c/cprouve/Gamma/MCrequest/toystudy/test/test2.root", "recreate");
  TTree tree("testtree", "treetest");


  vector<float> p = {-999, -999, -999, -999};
  TBranch* b_p1p = tree.Branch("Pion1_P", &p.at(0), "Pion1_P/f" );
  TBranch* b_p2p = tree.Branch("Pion2_P", &p.at(1), "Pion2_P/f" );
  TBranch* b_p3p = tree.Branch("Pion3_P", &p.at(2), "Pion3_P/f" );  
  TBranch* b_p4p = tree.Branch("Pion4_P", &p.at(3), "Pion4_P/f" );
  

  vector<TBranch*> b_p = {b_p1p, b_p2p, b_p3p, b_p4p};
  
  double event;
  for(int i = 0; i<10; i++)
  {
    event = generator.Generate();
  
    for(int j = 0; j < 4; j++){
      p.at(j) = generator.GetDecay(j)->P();
    }

    b_p.at(0)->Fill();
    b_p.at(1)->Fill();
    b_p.at(2)->Fill();
    b_p.at(3)->Fill();
    tree.Fill();
  }
  
  tree.Write();
  file.Write();

  
}


