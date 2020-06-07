#ifndef FMCV2_INCLUDE_FUELFEED_H_
#define FMCV2_INCLUDE_FUELFEED_H_

int roll = 0;
int pitch = 0;
int CG_X = 0;
int CG_y = 0;
int BURNSQ = 0; //0-5

void calculateCG()
{}

void calculateBurnSQ()
{
    BURNSQ = 0;
}

void manageBurn()
{
    if(BURNSQ == 1)
    {

    }

    triggerFTRP(1);
    triggerRTFP(0);
    triggerLTV(1);
    triggerRTV(0);
    triggerNO1V(1);
    triggerNO2V(0);
}

#endif
