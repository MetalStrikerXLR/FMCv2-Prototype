#ifndef FMCV2_INCLUDE_DATA_PROCESSOR_H_
#define FMCV2_INCLUDE_DATA_PROCESSOR_H_

#include "HL_rti.h"

long long Tank_FWD_mass = 0;
long long Tank_MID_mass = 0;
long long Tank_REAR_mass = 0;
long long Tank_LT_mass = 0;
long long Tank_RT_mass = 0;
long long total_mass = 0;         //STF

long long Tank_FWD_per = 0;
long long Tank_MID_per = 0;
long long Tank_REAR_per = 0;
long long Tank_LT_per = 0;
long long Tank_RT_per = 0;

long long Tank_FWD_vol = 0;
long long Tank_MID_vol = 0;
long long Tank_REAR_vol = 0;
long long Tank_LT_vol = 0;
long long Tank_RT_vol = 0;
long long total_vol = 0;

long long Tank_FWD_lvl = 0;       //FLSF
long long Tank_MID_lvl = 0;       //FLSM
long long Tank_REAR_lvl = 0;      //FLSR
long long Tank_LT_lvl = 0;        //FLSLW
long long Tank_RT_lvl = 0;        //FLSRW

long long Sys_temp = 0;           //TS-1

long long FWD_to_REAR_pres = 0;   //PST13
long long REAR_to_FWD_pres = 0;   //PST31
long long VENT_Sen_pres = 0;      //PSV
long long MAIN_Flow_pres = 0;     //PSMFL

long long Fuel_flow_LM = 0;     //FFS
float Fuel_flow_GH = 0;

long long FWD_min = 0;
long long FWD_max = 0;
long long MID_min = 0;
long long MID_max = 0;
long long Rear_min = 0;
long long Rear_max = 0;
long long LT_min = 0;
long long LT_max = 0;
long long RT_min = 0;
long long RT_max = 0;

void calcMass();
void calcVol();

void initializeRTI()
{
    rtiInit();
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE1);
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);
}

void processFuelData(float fsen1_v, float fsen2_v, float fsen3_v, float fsen4_v, float fsen5_v)
{
    FWD_min = readEEPROM(0x1);
    FWD_max = readEEPROM(0x2);
    MID_min = readEEPROM(0x3);
    MID_max = readEEPROM(0x4);
    Rear_min = readEEPROM(0x5);
    Rear_max = readEEPROM(0x6);
    LT_min = readEEPROM(0x7);
    LT_max = readEEPROM(0x8);
    RT_min = readEEPROM(0x9);
    RT_max = readEEPROM(0xA);

    Tank_FWD_per = ((fsen1_v - FWD_min)*100.00)/(FWD_max - FWD_min);
    Tank_MID_per = ((fsen2_v - MID_min)*100.00)/(MID_max - MID_min);
    Tank_REAR_per = ((fsen3_v - Rear_min)*100.00)/(Rear_max - Rear_min);
    Tank_LT_per = ((fsen4_v - LT_min)*100.00)/(LT_max - LT_min);
    Tank_RT_per = ((fsen5_v - RT_min)*100.00)/(RT_max - RT_min);

    Tank_FWD_lvl = (Tank_FWD_per * 330.00)/100.00;
    Tank_MID_lvl = (Tank_MID_per * 540.00)/100.00;
    Tank_REAR_lvl = (Tank_REAR_per * 290.00)/100.00;
    Tank_LT_lvl = (Tank_LT_per * 240.00)/100.00;
    Tank_RT_lvl = (Tank_RT_per * 240.00)/100.00;

    calcMass();
    calcVol();
}

void processTempData(float tsen_v)
{
    Sys_temp = (22.7 * tsen_v) - 20.00;
}

void processPresData(float psen1_v, float psen2_v, float psen3_v, float psen4_v)
{
    FWD_to_REAR_pres = 10.00 * (psen1_v - 1.00);
    REAR_to_FWD_pres = 10.00 * (psen2_v - 1.00);
    VENT_Sen_pres = 10.00 * (psen3_v - 1.00);
    MAIN_Flow_pres = 10.00 * (psen4_v - 1.00);
}

void processFuelFlow(int pulses)
{
    Fuel_flow_GH = pulses/(68000.00 * 3600.00);
    Fuel_flow_LM = (Fuel_flow_GH/15.85) * 100.00;
}

void calcMass()
{}

void calcVol()
{}

displaySensor_data()
{
    Serialprintln("Sensor Values:");
    Serialprintln("");

    Serialprintln("FWD Tank Mass: ");
    Serialprint_n(Tank_FWD_mass);
    Serialprintln("");
    Serialprintln("MID Tank Mass: ");
    Serialprint_n(Tank_MID_mass);
    Serialprintln("");
    Serialprintln("REAR Tank Mass: ");
    Serialprint_n(Tank_REAR_mass);
    Serialprintln("");
    Serialprintln("LT-Wing Tank Mass: ");
    Serialprint_n(Tank_LT_mass);
    Serialprintln("");
    Serialprintln("RT-Wing Tank Mass: ");
    Serialprint_n(Tank_RT_mass);
    Serialprintln("");
    Serialprintln("Total Tank Mass: ");
    Serialprint_n(total_mass);
    Serialprintln("");

    Serialprintln("FWD Tank Percentage: ");
    Serialprint_n(Tank_FWD_per);
    Serialprintln("");
    Serialprintln("MID Tank Percentage: ");
    Serialprint_n(Tank_MID_per);
    Serialprintln("");
    Serialprintln("REAR Tank Percentage: ");
    Serialprint_n(Tank_REAR_per);
    Serialprintln("");
    Serialprintln("LT-Wing Tank Percentage: ");
    Serialprint_n(Tank_LT_per);
    Serialprintln("");
    Serialprintln("RT-Wing Tank Percentage: ");
    Serialprint_n(Tank_RT_per);
    Serialprintln("");

    Serialprintln("FWD Tank Volume: ");
    Serialprint_n(Tank_FWD_vol);
    Serialprintln("");
    Serialprintln("MID Tank Volume: ");
    Serialprint_n(Tank_MID_vol);
    Serialprintln("");
    Serialprintln("REAR Tank Volume: ");
    Serialprint_n(Tank_REAR_vol);
    Serialprintln("");
    Serialprintln("LT-Wing Tank Volume: ");
    Serialprint_n(Tank_LT_vol);
    Serialprintln("");
    Serialprintln("RT-Wing Tank Volume: ");
    Serialprint_n(Tank_RT_vol);
    Serialprintln("");
    Serialprintln("Total Tank Volume: ");
    Serialprint_n(total_vol);
    Serialprintln("");

    Serialprintln("FWD Tank Level: ");
    Serialprint_n(Tank_FWD_lvl);
    Serialprintln("");
    Serialprintln("MID Tank Level: ");
    Serialprint_n(Tank_MID_lvl);
    Serialprintln("");
    Serialprintln("REAR Tank Level: ");
    Serialprint_n(Tank_REAR_lvl);
    Serialprintln("");
    Serialprintln("LT-Wing Tank Level: ");
    Serialprint_n(Tank_LT_lvl);
    Serialprintln("");
    Serialprintln("RT-Wing Tank Level: ");
    Serialprint_n(Tank_RT_lvl);
    Serialprintln("");

    Serialprintln("System Temperature: ");
    Serialprint_n(Sys_temp);
    Serialprintln("");

    Serialprintln("FWD - REAR Pressure: ");
    Serialprint_n(FWD_to_REAR_pres);
    Serialprintln("");
    Serialprintln("REAR - FWD Pressure: ");
    Serialprint_n(REAR_to_FWD_pres);
    Serialprintln("");
    Serialprintln("Vent Pressure: ");
    Serialprint_n(VENT_Sen_pres);
    Serialprintln("");
    Serialprintln("Main Flow Pressure: ");
    Serialprint_n(MAIN_Flow_pres);
    Serialprintln("");

    Serialprintln("Fuel Flow Liter/min: ");
    Serialprint_n(Fuel_flow_LM);
    Serialprintln("");
    Serialprintln("Fuel Flow Gallon/hr: ");
    Serialprint_n(Fuel_flow_GH);
    Serialprintln("");
}

#endif
