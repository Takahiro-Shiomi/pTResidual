#include "../include/TurnoncurvE.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <typeinfo>

using namespace std;

Bool_t ptresidual::Offline(int i, int j)
{
    extEta=-100;
    extPhi=-100;
    bool Flag=false;
    float Z=9999;

    if(ext_mu_type->at(i)==1){
        for(int ext=0;ext<j;ext++){
            int extTarget=ext_mu_targetVec->at(i).at(ext);
            float extDistance=ext_mu_targetDistanceVec->at(i).at(ext);
            float exteta=ext_mu_targetEtaVec->at(i).at(ext);
            float extphi=ext_mu_targetPhiVec->at(i).at(ext);
            if(abs(extphi)>(TMath::Pi()))continue;

            if(extTarget==1){
                if(abs(extDistance)<15000 || abs(extDistance)>15300)continue;
                if(abs(exteta)<=1.05)continue;
                if(abs(15280-abs(extDistance))<Z){
                    Z=abs(15280-abs(extDistance));
                    extEta=exteta;
                    extPhi=extphi;
                    Flag=true;
                }
            }
        }
    }
    return Flag;
}

Int_t ptresidual::Thre(float k)
{
    int Thre=999;
    if(k>=1&&k<=2){Thre=1;}
    if(k>=2&&k<=3){Thre=2;}
    if(k>=3&&k<=4){Thre=3;}
    if(k>=4&&k<=5){Thre=4;}
    if(k>=5&&k<=6){Thre=5;}
    if(k>=6&&k<=7){Thre=6;}
    if(k>=7&&k<=8){Thre=7;}
    if(k>=8&&k<=9){Thre=8;}
    if(k>=9&&k<=10){Thre=9;}
    if(k>=10&&k<=11){Thre=10;}
    if(k>=11&&k<=12){Thre=11;}
    if(k>=12&&k<=13){Thre=12;}
    if(k>=13&&k<=14){Thre=13;}
    if(k>=14&&k<=15){Thre=14;}
    if(k>=15&&k<=16){Thre=15;}
    if(k>=16&&k<=17){Thre=16;}
    if(k>=17&&k<=18){Thre=17;}
    if(k>=18&&k<=19){Thre=18;}
    if(k>=19&&k<=20){Thre=19;}

    return Thre;
}
