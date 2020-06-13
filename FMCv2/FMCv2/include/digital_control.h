#ifndef FMCV2_INCLUDE_DIGITAL_CONTROL_H_
#define FMCV2_INCLUDE_DIGITAL_CONTROL_H_

#include "HL_gio.h"
#include "HL_het.h"

//Trigger States
int FWD_to_REAR_pump_state = 0;  //TP13
int REAR_to_FWD_pump_state = 0;  //TP31
int LTW_Svalve_state = 0;        //SVLW
int RTW_Svalve_state = 0;        //SVRW
int NOPEN1_Svalve_state = 0;     //SV1
int NOPEN2_Svalve_state = 0;     //SV2

//Manual Command States
int M_FTRP_State = 0;
int M_RTFP_State = 0;
int M_LTWS_State = 0;
int M_RTWS_State = 0;
int M_NO1S_State = 0;
int M_NO2S_State = 0;

//Feedbacks
int TP1D_OV_F = 0;
int TP2D_OV_F = 0;
int Svalve1D_OV_F = 0;
int Svalve2D_OV_F = 0;
int Svalve3D_OV_F = 0;
int Svalve4D_OV_F = 0;

int pulse_counter = 0;

void initializeGIO()
{
    gioInit();

    gioSetBit(gioPORTB,7,0); //Pump 1

    gioEnableNotification(gioPORTA, 0);
}

void initializeNHET()
{
    hetInit();

    gioSetBit(hetPORT1, 1, 0); // Pump 2
    gioSetBit(hetPORT1, 3, 0); // SVl 1 - LFT
    gioSetBit(hetPORT1, 5, 0); // SVL 2 - RHT
    gioSetBit(hetPORT1, 7, 0); // SVL 3
    gioSetBit(hetPORT1, 9, 0); // SVL 4

    edgeEnableNotification (hetREG1, 0);
}

void readDigitalFeed()
{
    TP1D_OV_F = gioGetBit(hetPORT1, 0);
    TP2D_OV_F = gioGetBit(hetPORT1, 2);
    Svalve1D_OV_F = gioGetBit(hetPORT1, 4);
    Svalve2D_OV_F = gioGetBit(hetPORT1, 6);
    Svalve3D_OV_F = gioGetBit(hetPORT1, 8);
    Svalve4D_OV_F = gioGetBit(hetPORT1, 10);
}

void triggerFTRP(int state)
{
    if(state == 1)
    {
        gioSetBit(gioPORTB,7,1);
        FWD_to_REAR_pump_state = 1;
    }
    else
    {
        gioSetBit(gioPORTB,7,0);
        FWD_to_REAR_pump_state = 0;
    }
}

void triggerRTFP(int state)
{
    if(state == 1)
    {
        gioSetBit(hetPORT1, 1, 1);
        REAR_to_FWD_pump_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 1, 0);
        REAR_to_FWD_pump_state = 0;
    }
}

void triggerLTV(int state)
{
    if(state == 1)
    {
        gioSetBit(hetPORT1, 3, 1);
        LTW_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 3, 0);
        LTW_Svalve_state = 0;
    }
}

void triggerRTV(int state)
{
    if(state == 1)
    {
        gioSetBit(hetPORT1, 5, 1);
        RTW_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 5, 0);
        RTW_Svalve_state = 0;
    }
}

void triggerNO1V(int state)
{
    if(state == 1)
    {
        gioSetBit(hetPORT1, 7, 1);
        NOPEN1_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 7, 0);
        NOPEN1_Svalve_state = 0;
    }
}

void triggerNO2V(int state)
{
    if(state == 1)
    {
        gioSetBit(hetPORT1, 9, 1);
        NOPEN2_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 9, 0);
        NOPEN2_Svalve_state = 0;
    }
}

void manualControlUpdate()
{
    if(M_FTRP_State == 1)
    {
        gioSetBit(gioPORTB,7,1);
        FWD_to_REAR_pump_state = 1;
    }
    else
    {
        gioSetBit(gioPORTB,7,0);
        FWD_to_REAR_pump_state = 0;
    }

    if(M_RTFP_State == 1)
    {
        gioSetBit(hetPORT1, 1, 1);
        REAR_to_FWD_pump_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 1, 0);
        REAR_to_FWD_pump_state = 0;
    }

    if(M_LTWS_State == 1)
    {
        gioSetBit(hetPORT1, 3, 1);
        LTW_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 3, 0);
        LTW_Svalve_state = 0;
    }

    if(M_RTWS_State == 1)
    {
        gioSetBit(hetPORT1, 5, 1);
        RTW_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 5, 0);
        RTW_Svalve_state = 0;
    }

    if(M_NO1S_State == 1)
    {
        gioSetBit(hetPORT1, 7, 1);
        NOPEN1_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 7, 0);
        NOPEN1_Svalve_state = 0;
    }

    if(M_NO2S_State == 2)
    {
        gioSetBit(hetPORT1, 9, 1);
        NOPEN2_Svalve_state = 1;
    }
    else
    {
        gioSetBit(hetPORT1, 9, 0);
        NOPEN2_Svalve_state = 0;
    }
}

#endif
