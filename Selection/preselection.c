#include<iostream>
#include <sstream>
using namespace std;


void makePreselection(string oldfile, string newfile)
{
  TCut L0DecCut("Bu_L0Global_Dec==1") ;
  TCut L0HadTOSCut("Bu_L0HadronDecision_TOS") ;
  TCut L0TISCut("Bu_L0Global_TIS==1 && Bu_L0HadronDecision_TOS==0" );
  TCut Hlt1TOSCut("Bu_Hlt1TrackAllL0Decision_TOS==1") ;
  TCut Hlt2TopoTOSCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS==1||Bu_Hlt2Topo3BodyBBDTDecision_TOS==1||Bu_Hlt2Topo4BodyBBDTDecision_TOS==1)") ;
  TCut triggerCut = L0DecCut && Hlt1TOSCut && Hlt2TopoTOSCut && (L0HadTOSCut || L0TISCut);
  
  TCut sanityCut(" Pion1_PT<20000 && Pion2_PT<20000 && Pion3_PT<20000 && Pion4_PT<20000 && Kaon_PT<20000");
  
  // might have to change to ProbNN once I know what that is :D
  TCut pidK("Kaon_PIDK>0");
  TCut pidPi("Pion1_PIDK<5 && Pion2_PIDK<5 && Pion3_PIDK<5 && Pion4_PIDK<5 ");
  TCut pidCut = pidK && pidPi;
  
  TCut D0Mass("abs(D0_MM -1864) <= 25");
  
  // not sure about the momentum cut here...
  TCut KaonCut("Kaon_hasRich==1 && Kaon_P<100000");
  
  TCut preselection = triggerCut && sanityCut && pidCut && D0Mass && KaonCut;
  
  TFile* file = new TFile(oldfile.c_str(), "READ");  
  TTree* tree = (TTree*) file->Get("Bu2D0KTuple/DecayTree");
  
  TFile* file2 = new TFile(newfile.c_str(), "RECREATE");
  TTree* tree2 = tree->CopyTree(preselection);
  file2->Write();
    
  cout << oldfile << ":" << endl;  
  cout << "  before preselection: " << tree->GetEntries() << endl;
  cout << "  after preselection : " << tree2->GetEntries() << endl;
  file2->Close();
  
}

void listEff(string filename)
{
  TCut L0DecCut("Bu_L0Global_Dec==1") ;
  TCut L0HadTOSCut("Bu_L0HadronDecision_TOS") ;
  TCut L0TISCut("Bu_L0Global_TIS==1 && Bu_L0HadronDecision_TOS==0" );
  TCut Hlt1TOSCut("Bu_Hlt1TrackAllL0Decision_TOS==1") ;
  TCut Hlt2TopoTOSCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS==1||Bu_Hlt2Topo3BodyBBDTDecision_TOS==1||Bu_Hlt2Topo4BodyBBDTDecision_TOS==1)") ;
  TCut triggerCut = L0DecCut && Hlt1TOSCut && Hlt2TopoTOSCut && (L0HadTOSCut || L0TISCut);

  TCut sanityCut(" Pion1_PT<20000 && Pion2_PT<20000 && Pion3_PT<20000 && Pion4_PT<20000 && Kaon_PT<20000");
  

  // might have to change to ProbNN once I know what that is :D                                                                                              
  TCut pidK("Kaon_PIDK>0");
  TCut pidPi("Pion1_PIDK<5 && Pion2_PIDK<5 && Pion3_PIDK<5 && Pion4_PIDK<5 ");
  TCut pidCut = pidK && pidPi;

  TCut D0Mass("abs(D0_MM -1864) <= 25");

  // not sure about the momentum cut here...                                                                                                                 
  TCut KaonCut("Kaon_hasRich==1 && Kaon_P<100000");

  TCut preselection = triggerCut && sanityCut && pidCut && D0Mass && KaonCut;
  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* tree = (TTree*) file->Get("Bu2D0KTuple/DecayTree");
  

  cout << filename << endl;
  cout << tree->GetEntries() << endl;
  cout << "after trigger " << tree->GetEntries(triggerCut)<< " =  " << (float)tree->GetEntries(triggerCut)/(float)tree->GetEntries() << endl;
  cout << "after sanity  " << tree->GetEntries(triggerCut && sanityCut) << " =  " << (float)tree->GetEntries(triggerCut && sanityCut)/(float)tree->GetEntries() << endl;
  cout << "after D0 Mass " << tree->GetEntries(triggerCut && sanityCut && D0Mass)<< " =  " << (float)tree->GetEntries(triggerCut && sanityCut && D0Mass)/(float)tree->GetEntries() << endl;
  cout << "after PID     " << tree->GetEntries(triggerCut && sanityCut && D0Mass && pidCut)<< " =  " << (float)tree->GetEntries(triggerCut && sanityCut && D0Mass && pidCut)/(float)tree->GetEntries() << endl;
  cout << "after Kaon P  " << tree->GetEntries(triggerCut && sanityCut && D0Mass && pidCut && KaonCut)<< " =  " << (float)tree->GetEntries(triggerCut && sanityCut && D0Mass && pidCut && KaonCut)/(float)tree->GetEntries() << endl;
  
  
  
}



void preselection()
{
  listEff("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi.root");
  
  
  makePreselection("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21.root", 
                  "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/Data2012/B2DK_D24Pi_Stripping21_presel.root");
  
  makePreselection("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi.root",
                   "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D24Pi/MC2012/MC2012_B2DK_D24Pi_presel.root");
  
  
  makePreselection("/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi.root",
                   "/afs/cern.ch/work/c/cprouve/private/NTuples/B2DK_D2KsPiPi/MC2012/MC2012_B2DK_D2KsPiPi_as_B2DK_D24Pi_presel.root");
  
  
}
