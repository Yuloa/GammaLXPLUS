#include<iostream>
using namespace std;

void addKsCand(string filename)
{
  TFile* file = new TFile(filename.c_str(),"UPDATE"); 
  TTree *tree = (TTree*)file->Get("Bu2D0KTuple/DecayTree");
  
  Double_t p1_px = -999;
  Double_t p1_py = -999;
  Double_t p1_pz = -999;
  Double_t p1_pe = -999;
  Int_t p1_id = -999;
  
  Double_t p2_px = -999;
  Double_t p2_py = -999;
  Double_t p2_pz = -999;
  Double_t p2_pe = -999;
  Int_t p2_id = -999;
  
  Double_t p3_px = -999;
  Double_t p3_py = -999;
  Double_t p3_pz = -999;
  Double_t p3_pe = -999;
  Int_t p3_id = -999;
  
  Double_t p4_px = -999;
  Double_t p4_py = -999;
  Double_t p4_pz = -999;
  Double_t p4_pe = -999;
  Int_t p4_id = -999;
  
  tree->SetBranchAddress("Pion1_PX" ,&p1_px);
  tree->SetBranchAddress("Pion1_PY" ,&p1_py);
  tree->SetBranchAddress("Pion1_PZ" ,&p1_pz);
  tree->SetBranchAddress("Pion1_PE" ,&p1_pe);
  tree->SetBranchAddress("Pion1_ID" ,&p1_id);
  tree->SetBranchAddress("Pion2_PX" ,&p2_px);
  tree->SetBranchAddress("Pion2_PY" ,&p2_py);
  tree->SetBranchAddress("Pion2_PZ" ,&p2_pz);
  tree->SetBranchAddress("Pion2_PE" ,&p2_pe);
  tree->SetBranchAddress("Pion2_ID" ,&p2_id);
  tree->SetBranchAddress("Pion3_PX" ,&p3_px);
  tree->SetBranchAddress("Pion3_PY" ,&p3_py);
  tree->SetBranchAddress("Pion3_PZ" ,&p3_pz);
  tree->SetBranchAddress("Pion3_PE" ,&p3_pe);
  tree->SetBranchAddress("Pion3_ID" ,&p3_id);
  tree->SetBranchAddress("Pion4_PX" ,&p4_px);
  tree->SetBranchAddress("Pion4_PY" ,&p4_py);
  tree->SetBranchAddress("Pion4_PZ" ,&p4_pz);
  tree->SetBranchAddress("Pion4_PE" ,&p4_pe);
  tree->SetBranchAddress("Pion4_ID" ,&p4_id);
  
  
  
  //Double_t kscand_12 = -999;
  //Double_t kscand_14 = -999;
  //Double_t kscand_32 = -999;
  //Double_t kscand_34 = -999;
  //Double_t kscand_13 = -999;
  //Double_t kscand_24 = -999;
  
  Float_t kscand_12 = -999;
  Float_t kscand_14 = -999;
  Float_t kscand_32 = -999;
  Float_t kscand_34 = -999;
  Float_t kscand_13 = -999;
  Float_t kscand_24 = -999;

  TBranch *newbranch12 = tree->Branch("KSCand_12", &kscand_12, "KSCand_12");
  TBranch *newbranch14 = tree->Branch("KSCand_14", &kscand_14, "KSCand_14");
  TBranch *newbranch32 = tree->Branch("KSCand_32", &kscand_32, "KSCand_32");
  TBranch *newbranch34 = tree->Branch("KSCand_34", &kscand_34, "KSCand_34");
  TBranch *newbranch13 = tree->Branch("KSCand_13", &kscand_13, "KSCand_13");
  TBranch *newbranch24 = tree->Branch("KSCand_24", &kscand_24, "KSCand_24");
  
  Int_t signumberOfEntries = tree->GetEntries();
  for (Int_t loopie = 0; loopie < signumberOfEntries; ++loopie)
  {
    tree->GetEntry(loopie);
    
    //ks 12
      kscand_12 = sqrt( pow(p1_pe + p2_pe ,2) - pow(p1_px + p2_px ,2) - pow(p1_py + p2_py ,2) - pow(p1_pz + p2_pz ,2)  );
      kscand_14 = sqrt( pow(p1_pe + p4_pe ,2) - pow(p1_px + p4_px ,2) - pow(p1_py + p4_py ,2) - pow(p1_pz + p4_pz ,2)  );
      kscand_32 = sqrt( pow(p3_pe + p2_pe ,2) - pow(p3_px + p2_px ,2) - pow(p3_py + p2_py ,2) - pow(p3_pz + p2_pz ,2)  );
      kscand_34 = sqrt( pow(p3_pe + p4_pe ,2) - pow(p3_px + p4_px ,2) - pow(p3_py + p4_py ,2) - pow(p3_pz + p4_pz ,2)  );
      kscand_13 = sqrt( pow(p1_pe + p3_pe ,2) - pow(p1_px + p3_px ,2) - pow(p1_py + p3_py ,2) - pow(p1_pz + p3_pz ,2)  );
      kscand_24 = sqrt( pow(p2_pe + p4_pe ,2) - pow(p2_px + p4_px ,2) - pow(p2_py + p4_py ,2) - pow(p2_pz + p4_pz ,2)  );
    
    newbranch12->Fill();
    newbranch14->Fill();
    newbranch32->Fill();
    newbranch34->Fill();
    newbranch13->Fill();
    newbranch24->Fill();
  }
  file->Write();
  

}


void addVariables_wrong()
{
  //addKsCand("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi.root");
  //addKsCand("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_recPreSel.root");
  addKsCand("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21.root");
  
  
}
