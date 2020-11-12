#include "ptresidual.h"
#include "/home/shiomi/RootUtils/RootUtils/TLegend_addfunc.h"
#include "/home/shiomi/RootUtils/RootUtils/TCanvas_opt.h"
#include "TStyle.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraphErrors.h"

using namespace std;

void ptresidual::DrawHist(TString pdf)
{
    TCanvas_opt *c1 = new TCanvas_opt();
    gStyle->SetOptStat(0);
    c1->SetGrid();
    c1->SetTopMargin(0.20);
    c1->Print(pdf + "[", "pdf");

    P_pT->Draw();
    P_pT->SetLineColor(kAzure-1);
    c1->Print(pdf, "pdf");

    J_dPhi->Draw();
    J_dPhi->SetLineColor(kAzure-1);
    c1->Print(pdf, "pdf");

    J_dR->Draw();
    J_dR->SetLineColor(kAzure-1);
    c1->Print(pdf, "pdf");

    J_M->Draw();
    J_M->SetLineColor(kAzure-1);
    c1->Print(pdf, "pdf");

    c1->Divide(3,2);
    for(int j=0;j<20;j++){
        B_resi[j]->Draw();
        B_resi[j]->SetStats(0);
        B_resi[j]->SetLineColor(kOrange+8);
        B_resi[j]->SetFillColor(kOrange+8);
        B_resi[j]->SetFillStyle(3004);
        A_resi[j]->Draw("same");
        A_resi[j]->SetLineColor(kAzure+10);
        A_resi[j]->SetFillColor(kAzure+10);
        A_resi[j]->SetFillStyle(3335);
        c1->Print(pdf, "pdf");
    }
    c1->Clear();

    float B_Mean[20];
    float B_MErr[20];
    float B_StdDev[20];
    float B_SDErr[20];
    float A_Mean[20];
    float A_MErr[20];
    float A_StdDev[20];
    float A_SDErr[20];
    
    float x[20]={0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5};
    float ex[20]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};

    for(int p=0;p!=20;p++){
        B_Mean[p]=B_mean[p]/B_inte[p];
        B_MErr[p]=B_Mean[p]/sqrt(B_inte[p]);
        B_StdDev[p]=sqrt(B_scat[p]/B_inte[p]);
        B_SDErr[p]=B_StdDev[p]/sqrt(B_inte[p]);
        A_Mean[p]=A_mean[p]/A_inte[p];
        A_MErr[p]=A_Mean[p]/sqrt(A_inte[p]);
        A_StdDev[p]=sqrt(A_scat[p]/A_inte[p]);
        A_SDErr[p]=A_StdDev[p]/sqrt(A_inte[p]);
    }

    TGraphErrors *b_mean = new TGraphErrors(20,x,B_Mean,ex,B_MErr);
    TGraphErrors *b_StdDev = new TGraphErrors(20,x,B_StdDev,ex,B_SDErr);

    TGraphErrors *a_mean = new TGraphErrors(20,x,A_Mean,ex,A_MErr);
    TGraphErrors *a_StdDev = new TGraphErrors(20,x,A_StdDev,ex,A_SDErr);

    //hist_mean->GetYaxis()->SetRangeUser(-0.14,0.5);
    b_mean->SetTitle(";p^{offline}_{T} [GeV];Mean");
    b_mean->Draw("ap");
    b_mean->SetMarkerStyle(4);
    b_mean->SetMarkerSize(2);
    b_mean->SetMarkerColor(kOrange+8);
    b_mean->SetLineColor(kOrange+8);
    a_mean->Draw("p same");
    a_mean->SetMarkerStyle(4);
    a_mean->SetMarkerSize(2);
    a_mean->SetMarkerColor(kAzure+10);
    a_mean->SetLineColor(kAzure+10);
    b_mean->Write();
    a_mean->Write();
    c1->Print(pdf,"pdf");

    //hist_StdDev->GetYaxis()->SetRangeUser(0,0.7);
    b_StdDev->SetTitle(";p^{offline}_{T} [GeV];#sigma");
    b_StdDev->Draw("ap");
    b_StdDev->SetMarkerStyle(4);
    b_StdDev->SetMarkerSize(2);
    b_StdDev->SetMarkerColor(kOrange+8);
    b_StdDev->SetLineColor(kOrange+8);
    a_StdDev->Draw("p same");
    a_StdDev->SetMarkerStyle(4);
    a_StdDev->SetMarkerSize(2);
    a_StdDev->SetMarkerColor(kAzure+10);
    a_StdDev->SetLineColor(kAzure+10);
    b_StdDev->Write();
    a_StdDev->Write();
    c1->Print(pdf,"pdf");

    c1 -> Print( pdf + "]", "pdf" );
    delete c1;
}
