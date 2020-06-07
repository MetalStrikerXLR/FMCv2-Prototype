#ifndef FMCV2_INCLUDE_FUELFEED_H_
#define FMCV2_INCLUDE_FUELFEED_H_

int roll = 0;
int pitch = 0;
int CG_X = 0;
int CG_y = 0;
int BURNSQ = 0; //TBD

void calculateCG()
{
    //TBD
}

void calculateBurnSQ()
{
    if(pitch >= -2 && pitch <= 2)
    {
        BURNSQ = 0;
    }

    if(pitch >= -10 && pitch < -2)
    {
        BURNSQ = 1;
    }

    if(pitch > 2 && pitch <= 15)
    {
        BURNSQ = 2;
    }
}

void manageBurn()
{
    if(BURNSQ == 0)
    {
        triggerFTRP(0);
        triggerRTFP(0);
    }

    if(BURNSQ == 1)
    {
        triggerFTRP(1);
        triggerRTFP(0);
    }

    if(BURNSQ == 2)
    {
        triggerFTRP(0);
        triggerRTFP(1);
    }

    if(Tank_MID_per <= 30)
    {
        triggerLTV(1);
        triggerRTV(1);
    }
    else
    {
        triggerLTV(0);
        triggerRTV(0);
        triggerNO1V(0);
        triggerNO2V(0);
    }

}

#endif
