#include "../include/ptresidual.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <typeinfo>

using namespace std;

void ptresidual::FillHist()
{
    //Offline Start
    for(int i=0;i!=muon_n;i++){
        if(muon_author->at(i)!=1 || muon_Type->at(i)!=0)continue;
        float offline_pt=muon_pt->at(i);
        float offline_eta =muon_eta->at(i);
        float offline_phi =muon_phi->at(i);
        if(abs(offline_eta)<=1.05){continue;}
        if(abs(offline_eta)>=2.4){continue;}
        int thre = Thre(offline_pt/1000);
        if(thre == 999){continue;}
        if(Offline(i, ext_mu_size->at(i))==false)continue;

        //TGC Run-3 Start
        int pT = TGC_Run3(offline_pt/1000);
        //int pTRun2 = TGC_Run2(offline_pt/1000);

        //Residual Fill
        if(pT>=3&&pT<=20){
            h_pT->Fill(offline_pt/1000);
            float ptresidual = ((float)pT-(offline_pt/1000))/(offline_pt/1000);
            h_pTresidual[thre-1]->Fill(ptresidual);

            Integral[thre-1]=Integral[thre-1]+1;
            mean[thre-1]=mean[thre-1]+ptresidual;
            scatter[thre-1]=scatter[thre-1]+pow(ptresidual,2);
        }
    }
}
