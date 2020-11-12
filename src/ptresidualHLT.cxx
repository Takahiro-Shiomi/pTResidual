#include "ptresidual.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <typeinfo>
#include "TH1.h"
#include "TVector2.h"

using namespace std;

Bool_t ptresidual::Tag(int tag)
{
    float tag_eta = (*muon_eta)[tag];
    float tag_phi = (*muon_phi)[tag];
    float dR = 100;
    for(int i=0;i!=HLT_info_n;i++){
        if((*HLT_info_isPassed)[i]==0){continue;}
        if((*HLT_info_chain)[i] !="HLT_mu20_2mu2noL1_JpsimumuFS"){continue;}
        float HLT_dR=100;
        for(int j=0;j!=HLT_info_etaVec->at(i).size();j++){
            if((*HLT_info_ptVec)[i][j]/1000<20){continue;}
            float HLT_eta = (*HLT_info_etaVec)[i][j];
            float HLT_phi = (*HLT_info_phiVec)[i][j];
            float tag_deta = abs(tag_eta-HLT_eta);
            float tag_dphi = TVector2::Phi_mpi_pi(HLT_phi-tag_phi);
            float deltaR = sqrt(pow(tag_deta,2)+pow(tag_dphi,2));
            if(deltaR<HLT_dR){HLT_dR=deltaR;}
        }
        if(HLT_dR<dR){
            dR=HLT_dR;
        }
    }
    if(dR<=0.005){return true;}
    else{return false;}
}

