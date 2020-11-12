#include "ptresidual.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <typeinfo>
#include <TVector3.h>
#include "TH1.h"

using namespace std;

Int_t ptresidual::TGC_Run2(float off_pt)
{
    int pT=99999999;
    float dR=100;
    for(int j=0;j!=tgc_coin_n;j++){
        if(tgc_coin_type->at(j)!=2)continue;

        int tgc_pt=tgc_coin_pt->at(j);
        int Run2_pt= -9999999;
        if(tgc_pt==0)continue;
        if(tgc_pt==1){Run2_pt=4;}
        if(tgc_pt==2){Run2_pt=6;}
        if(tgc_pt==3||tgc_pt==4){Run2_pt=10;}
        if(tgc_pt==5||tgc_pt==6){Run2_pt=20;}
        float tgc_x=tgc_coin_x_Out->at(j);
        float tgc_y=tgc_coin_y_Out->at(j);
        float tgc_z=tgc_coin_z_Out->at(j);
        TVector3 v2;
        v2.SetXYZ(tgc_x,tgc_y,tgc_z);
        float tgc_eta=v2.PseudoRapidity();
        float tgc_phi=v2.Phi();

        float delta_eta=extEta-tgc_eta;
        float delta_phi=TVector2::Phi_mpi_pi(extPhi-tgc_phi);
        float tgc_dR=sqrt(delta_eta*delta_eta + delta_phi*delta_phi);
        if(tgc_dR<dR){
            dR=tgc_dR;
            pT=(int)Run2_pt;
        }
    }
    B_dR->Fill(off_pt,dR);
    if(dR<=0.03){return pT;}
    else{return 0;}
}
