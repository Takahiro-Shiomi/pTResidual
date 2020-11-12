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

    P_pT = new TH1D("P_pT",";p^{probe}_{T}",50,0,25);
    J_dPhi = new TH1D("J_dPhi",";#Delta#phi^{Tag-Probe};Events",100,0,3.14);
    J_dR = new TH1D("J_dR",";#DeltaR^{Tag-Probe};Events",100,0,3.14);
    J_M = new TH1D("J_M",";M^{offline}_{#mu#mu} [GeV];Events",50,2,3);
    B_dR = new TH2D("B_dR","Run2;p^{offline}_{T} [GeV];#DeltaR",100,0,25,100,0,0.1);
    A_dR = new TH2D("A_dR","Run3;p^{offline}_{T} [GeV];#DeltaR",100,0,25,100,0,0.1);
    for(int i=0;i<20;i++){
        B_resi[i]=new TH1D(Form("B_resi%d",i),Form("%d<p^{offline}_{T}<%dGeV;p_{T} residual;Events",i+1,i+2),60,-1.5,1.5);
        A_resi[i]=new TH1D(Form("A_resi%d",i),Form("%d<p^{offline}_{T}<%dGeV;p_{T} residual;Events",i+1,i+2),60,-1.5,1.5);
        B_inte[i]=0;
        A_inte[i]=0;
        B_mean[i]=0;
        A_mean[i]=0;
        B_scat[i]=0;
        A_scat[i]=0;
    }
}

void ptresidual::EndHist(){
    if(P_pT!=0){delete P_pT;}
    if(J_dPhi!=0){delete J_dPhi;}
    if(J_dR!=0){delete J_dR;}
    if(J_M!=0){delete J_M;}
    if(B_dR!=0){delete B_dR;}
    if(A_dR!=0){delete A_dR;}
    for(int i=0;i<20;i++){
        if(B_resi[i]!=0){delete B_resi[i];}
        if(A_resi[i]!=0){delete A_resi[i];}
    }
}

