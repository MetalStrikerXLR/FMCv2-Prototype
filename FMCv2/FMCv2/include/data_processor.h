#ifndef FMCV2_INCLUDE_DATA_PROCESSOR_H_
#define FMCV2_INCLUDE_DATA_PROCESSOR_H_

#include "HL_rti.h"

int Tank_FWD_mass = 0;
int Tank_MID_mass = 0;
int Tank_REAR_mass = 0;
int Tank_LT_mass = 0;
int Tank_RT_mass = 0;

int Tank_FWD_per = 0;
int Tank_MID_per = 0;
int Tank_REAR_per = 0;
int Tank_LT_per = 0;
int Tank_RT_per = 0;

int Tank_FWD_vol = 0;
int Tank_MID_vol = 0;
int Tank_REAR_vol = 0;
int Tank_LT_vol = 0;
int Tank_RT_vol = 0;

int Tank_FWD_lvl = 0;
int Tank_MID_lvl = 0;
int Tank_REAR_lvl = 0;
int Tank_LT_lvl = 0;
int Tank_RT_lvl = 0;

int Sys_temp = 0;

int FWD_to_REAR_pres = 0;
int REAR_to_FWD_pres = 0;
int ENG_Feed_pres = 0;
int Extra_Sen_pres = 0;

float Fuel_flow_LM = 0;
float Fuel_flow_GH = 0;

void calcPercent();
void calcMass();
void calcVol();
void calcLvL();

void initializeRTI()
{
    rtiInit();
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);
}

void processFuelData(float fsen1_v, float fsen2_v, float fsen3_v, float fsen4_v, float fsen5_v)
{
    calcPercent();
    calcMass();
    calcVol();
    calcLvL();
}

void processTempData(float tsen_v)
{
    Sys_temp = (25 * tsen_v) - 40;
}

void processPresData(float psen1_v, float psen2_v, float psen3_v, float psen4_v)
{
    FWD_to_REAR_pres = 87 * psen1_v;
    REAR_to_FWD_pres = 87 * psen2_v;
    ENG_Feed_pres = 87 * psen3_v;
    Extra_Sen_pres = 87 * psen4_v;
}

void processFuelFlow(int pulses)
{
    Fuel_flow_GH = pulses/(68000 * 3600);
    Fuel_flow_LM = Fuel_flow_GH/15.85;
}

void calcPercent()
{}

void calcMass()
{}

void calcVol()
{}

void calcLvL()
{}
#endif
