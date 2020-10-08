#include "ptresidual.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TROOT.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TString.h"
#include <vector>
#include <iostream>

using namespace std;

void ptresidual::InitHist(){

    h_pT = new TH1D("h_pT","",30,0,30);
    for(int i=0;i<20;i++){
        h_pTresidual[i]=new TH1D(Form("h_pTresidual%d",i),Form("%dGeV<offline p_{T}<%dGeV;p_{T}residual;Events",i+1,i+2),90,-1.5,1.5);
        Integral[i]=0;
        mean[i]=0;
        scatter[i]=0;
    }
}

void ptresidual::EndHist(){
    if(h_pT!=0){delete h_pT;}
    for(int i=0;i<20;i++){
        if(h_pTresidual[i]!=0){delete h_pTresidual[i];}
    }
}

