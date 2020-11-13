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

    h_pT->Draw();
    h_pT->SetLineColor(kAzure-1);
    c1->Print(pdf, "pdf");
    c1->Clear();

    c1->Divide(3,2);
    for(int j=0;j<20;j++){
        int Num=(j+1)%6;
        if(Num==0){Num=6;}
        c1->cd(Num);
        h_pTresidual[j]->Draw();
        h_pTresidual[j]->SetStats(0);
        h_pTresidual[j]->SetLineColor(kAzure-1);
        h_pTresidual[j]->SetFillColor(kAzure);
        h_pTresidual[j]->SetFillStyle(3015);
        if(Num==6||j==19){
            c1->Print(pdf, "pdf");
            c1->Clear();
            c1->Divide(3,2);
        }
    }
    c1->Print(pdf,"pdf");
    c1->Clear();

    float Mean[20];
    float MeanError[20];
    float StdDev[20];
    float StdDevError[20];
    
    float x[20]={0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5};
    float ex[20]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};

    for(int p=0;p!=20;p++){
        Mean[p]=mean[p]/Integral[p];
        MeanError[p]=Mean[p]/sqrt(Integral[p]);
        StdDev[p]=sqrt(scatter[p]/Integral[p]);
        StdDevError[p]=StdDev[p]/sqrt(Integral[p]);
    }

    TGraphErrors *h_mean = new TGraphErrors(20,x,Mean,ex,MeanError);
    TGraphErrors *h_StdDev = new TGraphErrors(20,x,StdDev,ex,StdDevError);

    //hist_mean->GetYaxis()->SetRangeUser(-0.14,0.5);
    h_mean->SetTitle(";p^{offline}_{T} [GeV];Mean");
    h_mean->Draw("ap");
    h_mean->SetMarkerStyle(8);
    h_mean->SetMarkerSize(2);
    h_mean->SetMarkerColor(kAzure-1);
    h_mean->SetLineColor(kAzure-1);
    h_mean->Write();
    c1->Print(pdf,"pdf");

    //hist_StdDev->GetYaxis()->SetRangeUser(0,0.7);
    h_StdDev->SetTitle(";p^{offline}_{T} [GeV];#sigma");
    h_StdDev->Draw("ap");
    h_StdDev->SetMarkerStyle(8);
    h_StdDev->SetMarkerSize(2);
    h_StdDev->SetMarkerColor(kAzure-1);
    h_StdDev->SetLineColor(kAzure-1);
    h_StdDev->Write();
    c1->Print(pdf,"pdf");

    c1 -> Print( pdf + "]", "pdf" );
    delete c1;
}
