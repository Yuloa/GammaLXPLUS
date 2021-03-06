vector<TCut> rectangularCuts;
TCut rectangularCut;
vector<TCut> preselectionCuts;
TCut preselectionCut;
TCut bkgCut("Bu_MM > 5400 && Bu_MM < 5900");
//TCut sigCut("");

void loadRectangularCuts()
{
  TCut PionCut("Pion1_IPCHI2_OWNPV > 9 && Pion2_IPCHI2_OWNPV > 9 && Pion3_IPCHI2_OWNPV > 9 && Pion4_IPCHI2_OWNPV > 9 && Pion1_PIDK < 5 && Pion2_PIDK < 5 && Pion3_PIDK < 5 && Pion4_PIDK < 5");
  TCut D0Cut("abs(D0_MM - 1864) <= 25 && D0_DIRA_OWNPV > 0.99 && D0_IPCHI2_OWNPV > 9 && D0_ENDVERTEX_Z - Bu_ENDVERTEX_Z >= 0");
  TCut KaonCut("Kaon_hasRich == 1 && Kaon_PIDK > 0 && Kaon_IPCHI2_OWNPV > 25 && Kaon_P > 8000");
  TCut BuCut("Bu_DIRA_OWNPV > 0.9999 && Bu_FDCHI2_OWNPV > 169 && Bu_IPCHI2_OWNPV < 9 ");
  TCut DTFCut("Bu_DTF_CHI2 < 60");
  
  rectangularCuts.push_back(PionCut);
  rectangularCuts.push_back(D0Cut);
  rectangularCuts.push_back(KaonCut);
  rectangularCuts.push_back(BuCut);
  //rectangularCuts.push_back(DTFCut);
  
  rectangularCut = PionCut && D0Cut && KaonCut && BuCut;
  std::cout << "Variables vector<TCut> rectangularCuts and TCut rectangularCut are loaded." << std::endl;
}

void loadPreselectionCuts()
{
  TCut L0DecCut("Bu_L0Global_Dec==1") ;
  TCut L0HadTOSCut("Bu_L0HadronDecision_TOS") ;
  TCut L0TISCut("Bu_L0Global_TIS==1 && Bu_L0HadronDecision_TOS==0" );
  TCut Hlt1TOSCut("Bu_Hlt1TrackAllL0Decision_TOS==1") ;
  TCut Hlt2TopoTOSCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS==1||Bu_Hlt2Topo3BodyBBDTDecision_TOS==1||Bu_Hlt2Topo4BodyBBDTDecision_TOS==1)") ;
  TCut triggerCut = L0DecCut && Hlt1TOSCut && Hlt2TopoTOSCut && (L0HadTOSCut || L0TISCut);
  TCut sanityCut(" Pion1_PT<20000 && Pion2_PT<20000 && Pion3_PT<20000 && Pion4_PT<20000 && Kaon_PT<20000");
  TCut D0Cut("abs(D0_MM -1864) <= 25 && D0_OWNPV_Z - Bu_OWNPV_Z >= 0");
  TCut KaonCut("Kaon_hasRich==1 && Kaon_PIDK > 4");
  
  preselectionCuts.push_back(triggerCut);
  preselectionCuts.push_back(sanityCut);
  preselectionCuts.push_back(D0Cut);
  preselectionCuts.push_back(KaonCut);
  
  preselectionCut = triggerCut && sanityCut && D0Cut && KaonCut;
  
  std::cout << "Variables vector<TCut> preselectionCuts and TCut preselectionCut are loaded." << std::endl;
  
}


void loadCuts()
{
  std::cout << "LOADING CUTS" << std::endl;
  
  loadRectangularCuts();
  loadPreselectionCuts();  
  std::cout << std::endl;
  
}
