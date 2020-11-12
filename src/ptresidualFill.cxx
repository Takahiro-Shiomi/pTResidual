#include "../include/ptresidual.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <typeinfo>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>

using namespace std;

void ptresidual::FillHist()
{
    //TagAndProbe//
    if(muon_n>=2){
    bool JPsi=false;
    //Tag
    for(int tag=0;tag<muon_n;tag++){
        if((*muon_author)[tag]!=1 || (*muon_Type)[tag]!=0){continue;}
        if((*muon_pt)[tag]/1000<20){continue;}
        if((!Tag(tag))){continue;}
        TLorentzVector Tag;
        Tag.SetPtEtaPhiM((*muon_pt)[tag]/1000,(*muon_eta)[tag],(*muon_phi)[tag],(*muon_m)[tag]/1000);

        for(int pro=0;pro<muon_n;pro++){
            if(tag==pro){continue;}
            if(abs((*muon_eta)[pro])<=1.05){continue;}
            if((*muon_author)[pro]!=1 || (*muon_Type)[pro]!=0){continue;}
            if((*muon_charge)[tag]==(*muon_charge)[pro]){continue;}
            TLorentzVector Pro;
            Pro.SetPtEtaPhiM((*muon_pt)[pro],(*muon_eta)[pro],(*muon_phi)[pro],(*muon_m)[pro]/1000);
            
            float dPhi=TVector2::Phi_mpi_pi((*muon_phi)[tag] - (*muon_phi)[pro]);
            J_dPhi->Fill(abs(dPhi));
            if(abs(dPhi)<0.14 || abs(dPhi)>3.0){continue;}
            float dR = Tag.DeltaR(Pro);
            J_dR->Fill(dR);
            TLorentzVector M = Tag + Pro;
            J_M->Fill(M.M());
            if(M.M()<2.8 || M.M()>3.4){continue;}
            if(Offline(pro,(*ext_mu_size)[pro]) == false){continue;}
            P_pT->Fill((*muon_pt)[pro]/1000);
            JPsi=true;
            int thre = Thre((*muon_pt)[pro]/1000);
            if(thre!=999){
                int pt_Run2 = TGC_Run2((*muon_pt)[pro]/1000);
                if(pt_Run2<=20 && pt_Run2>=4){
                    float resi = ((float)pt_Run2-((*muon_pt)[pro]/1000))/((*muon_pt)[pro]/1000);
                    B_resi[thre-1]->Fill(resi);
                    B_inte[thre-1]=B_inte[thre-1]+1;
                    B_mean[thre-1]=B_mean[thre-1]+resi;
                    B_scat[thre-1]=B_scat[thre-1]+pow(resi,2);
                }

                int pt_Run3 = TGC_Run3((*muon_pt)[pro]/1000);
                if(pt_Run3<=20 && pt_Run3>=3){
                    float resi = ((float)pt_Run3-((*muon_pt)[pro]/1000))/((*muon_pt)[pro]/1000);
                    A_resi[thre-1]->Fill(resi);
                    A_inte[thre-1]=A_inte[thre-1]+1;
                    A_mean[thre-1]=A_mean[thre-1]+resi;
                    A_scat[thre-1]=A_scat[thre-1]+pow(resi,2);
                }
            }
            if(JPsi){break;}
        }
        if(JPsi){break;}
    }
    }
}
