#ifndef FMCV2_INCLUDE_ADC_READ_H_
#define FMCV2_INCLUDE_ADC_READ_H_

#include "HL_esm.h"
#include "HL_adc.h"

adcData_t adc_data1[16];
adcData_t adc_data2[8];
uint32 ch_count1 = 0;
uint32 ch_count2 = 0;

// Raw Values
int Fuel_sen_1_raw = 0;
int Fuel_sen_2_raw = 0;
int Fuel_sen_3_raw = 0;
int Fuel_sen_4_raw = 0; //*left
int Fuel_sen_5_raw = 0; //*right
int Temp_sen_raw = 0;
int Pres_sen_1_raw = 0;
int Pres_sen_2_raw = 0;
int Pres_sen_3_raw = 0;
int Pres_sen_4_raw = 0;

int TP_1_CF_raw = 0;
int TP_2_CF_raw = 0;
int Svalve_1_CF_raw = 0;
int Svalve_2_CF_raw = 0;
int Svalve_3_CF_raw = 0;
int Svalve_4_CF_raw = 0;

int MPIN_V1_SF_raw = 0;
int MPIN_V2_SF_raw = 0;
int PS1_OV_SF_raw = 0;
int PS2_OV_SF_raw = 0;
int PS3_OV_SF_raw = 0;
int PS4_OV_SF_raw = 0;
int MPIN_C1_SF_raw = 0;
int MPIN_C2_SF_raw = 0;

//Filtered Values
float Fuel_sen_1 = 0;
float Fuel_sen_2 = 0;
float Fuel_sen_3 = 0;
float Fuel_sen_4 = 0;
float Fuel_sen_5 = 0;
float Temp_sen = 0;
float Pres_sen_1 = 0;
float Pres_sen_2 = 0;
float Pres_sen_3 = 0;
float Pres_sen_4 = 0;

float TP_1_CF = 0;
float TP_2_CF = 0;
float Svalve_1_CF = 0;
float Svalve_2_CF = 0;
float Svalve_3_CF = 0;
float Svalve_4_CF = 0;

float MPIN_V1_SF = 0;
float MPIN_V2_SF = 0;
float PS1_OV_SF = 0;
float PS2_OV_SF = 0;
float PS3_OV_SF = 0;
float PS4_OV_SF = 0;
float MPIN_C1_SF = 0;
float MPIN_C2_SF = 0;

void wait(uint32 time);

void initializeADC()
{
    adcInit();
}

void readSensors()
{
    adcStartConversion(adcREG1, adcGROUP1);
    while ((adcIsConversionComplete(adcREG1, adcGROUP1)) == 0);
    ch_count1 = adcGetData(adcREG1, adcGROUP1, &adc_data1[0]);

    adcStartConversion(adcREG2, adcGROUP1);
    while ((adcIsConversionComplete(adcREG2, adcGROUP1)) == 0);
    ch_count2 = adcGetData(adcREG2, adcGROUP1, &adc_data2[0]);

    Fuel_sen_1_raw = adc_data2[0].value;
    Fuel_sen_2_raw = adc_data2[2].value;
    Fuel_sen_3_raw = adc_data2[4].value;
    Fuel_sen_4_raw = adc_data1[8].value;
    Fuel_sen_5_raw = adc_data2[6].value;
    Temp_sen_raw = adc_data1[10].value;
    Pres_sen_1_raw = adc_data1[0].value;
    Pres_sen_2_raw = adc_data1[2].value;
    Pres_sen_3_raw = adc_data1[4].value;
    Pres_sen_4_raw = adc_data1[6].value;

    TP_1_CF_raw = adc_data1[1].value;
    TP_2_CF_raw = adc_data1[3].value;
    Svalve_1_CF_raw = adc_data1[5].value;
    Svalve_2_CF_raw = adc_data1[7].value;
    Svalve_3_CF_raw = adc_data2[1].value;
    Svalve_4_CF_raw = adc_data2[3].value;

    MPIN_V1_SF_raw = adc_data1[13].value;
    MPIN_V2_SF_raw = adc_data1[15].value;
    PS1_OV_SF_raw = adc_data1[11].value;
    PS2_OV_SF_raw = adc_data1[9].value;
    PS3_OV_SF_raw = adc_data2[7].value;
    PS4_OV_SF_raw = adc_data2[5].value;
    MPIN_C1_SF_raw = adc_data1[14].value;
    MPIN_C2_SF_raw = adc_data1[12].value;

    Fuel_sen_1 = (Fuel_sen_1_raw * 5.00)/1023.00;
    Fuel_sen_2 = (Fuel_sen_2_raw * 5.00)/1023.00;
    Fuel_sen_3 = (Fuel_sen_3_raw * 5.00)/1023.00;
    Fuel_sen_4 = (Fuel_sen_4_raw * 5.00)/1023.00;
    Fuel_sen_5 = (Fuel_sen_5_raw * 5.00)/1023.00;
    Temp_sen = (Temp_sen_raw * 5.00)/1023.00;
    Pres_sen_1 = (Pres_sen_1_raw * 5.00)/1023.00;
    Pres_sen_2 = (Pres_sen_2_raw * 5.00)/1023.00;
    Pres_sen_3 = (Pres_sen_3_raw * 5.00)/1023.00;
    Pres_sen_4 = (Pres_sen_4_raw * 5.00)/1023.00;

    TP_1_CF = (TP_1_CF_raw * 5.00)/1023.00;
    TP_2_CF = (TP_2_CF_raw * 5.00)/1023.00;
    Svalve_1_CF = (Svalve_1_CF_raw * 5.00)/1023.00;
    Svalve_2_CF = (Svalve_2_CF_raw * 5.00)/1023.00;
    Svalve_3_CF = (Svalve_3_CF_raw * 5.00)/1023.00;
    Svalve_4_CF = (Svalve_4_CF_raw * 5.00)/1023.00;

    MPIN_V1_SF = (MPIN_V1_SF_raw * 5.00)/1023.00;
    MPIN_V2_SF = (MPIN_V2_SF_raw * 5.00)/1023.00;
    PS1_OV_SF = (PS1_OV_SF_raw * 5.00)/1023.00;
    PS2_OV_SF = (PS2_OV_SF_raw * 5.00)/1023.00;
    PS3_OV_SF = (PS3_OV_SF_raw * 5.00)/1023.00;
    PS4_OV_SF = (PS4_OV_SF_raw * 5.00)/1023.00;
    MPIN_C1_SF = (MPIN_C1_SF_raw * 5.00)/1023.00;
    MPIN_C2_SF = (MPIN_C2_SF_raw * 5.00)/1023.00;

    wait(0xFFFFF);
}

void displayADC_raw()
{
    Serialprint("Number of Channels ADC1: ");
    Serialprint_n(ch_count1);
    Serialprintln("");
    Serialprint("Number of Channels ADC2: ");
    Serialprint_n(ch_count2);
    Serialprintln("");
    Serialprintln("");

    Serialprintln("Sensors:");
    Serialprintln("");

    Serialprint("Fuel Sensor 1: ");
    Serialprint_n(Fuel_sen_1_raw);
    Serialprintln("");
    Serialprint("Fuel Sensor 2: ");
    Serialprint_n(Fuel_sen_2_raw);
    Serialprintln("");
    Serialprint("Fuel Sensor 3: ");
    Serialprint_n(Fuel_sen_3_raw);
    Serialprintln("");
    Serialprint("Fuel Sensor 4: ");
    Serialprint_n(Fuel_sen_4_raw);
    Serialprintln("");
    Serialprint("Fuel Sensor 5: ");
    Serialprint_n(Fuel_sen_5_raw);
    Serialprintln("");
    Serialprint("Temperature Sensor: ");
    Serialprint_n(Temp_sen_raw);
    Serialprintln("");
    Serialprint("Pressure Sensor 1: ");
    Serialprint_n(Pres_sen_1_raw);
    Serialprintln("");
    Serialprint("Pressure Sensor 2: ");
    Serialprint_n(Pres_sen_2_raw);
    Serialprintln("");
    Serialprint("Pressure Sensor 3: ");
    Serialprint_n(Pres_sen_3_raw);
    Serialprintln("");
    Serialprint("Pressure Sensor 4: ");
    Serialprint_n(Pres_sen_4_raw);
    Serialprintln("");
    Serialprintln("");

    Serialprintln("Feedbacks:");
    Serialprintln("");

    Serialprint("Pump 1 Current Feedback: ");
    Serialprint_n(TP_1_CF_raw);
    Serialprintln("");
    Serialprint("Pump 2 current Feedback: ");
    Serialprint_n(TP_2_CF_raw);
    Serialprintln("");
    Serialprint("Solenoid Valve 1 Current Feedback: ");
    Serialprint_n(Svalve_1_CF_raw);
    Serialprintln("");
    Serialprint("Solenoid Valve 2 Current Feedback: ");
    Serialprint_n(Svalve_2_CF_raw);
    Serialprintln("");
    Serialprint("Solenoid Valve 3 Current Feedback: ");
    Serialprint_n(Svalve_3_CF_raw);
    Serialprintln("");
    Serialprint("Solenoid Valve 4 Current Feedback: ");
    Serialprint_n(Svalve_4_CF_raw);
    Serialprintln("");
    Serialprint("Main Power 1 Sense Feedback: ");
    Serialprint_n(MPIN_V1_SF_raw);
    Serialprintln("");
    Serialprint("Main Power 2 Sense Feedback: ");
    Serialprint_n(MPIN_V2_SF_raw);
    Serialprintln("");
    Serialprint("Power Supply 1 Output Voltage Sense Feedback: ");
    Serialprint_n(PS1_OV_SF_raw);
    Serialprintln("");
    Serialprint("Power Supply 2 Output Voltage Sense Feedback: ");
    Serialprint_n(PS2_OV_SF_raw);
    Serialprintln("");
    Serialprint("Power Supply 3 Output Voltage Sense Feedback: ");
    Serialprint_n(PS3_OV_SF_raw);
    Serialprintln("");
    Serialprint("Power Supply 4 Output Voltage Sense Feedback: ");
    Serialprint_n(PS4_OV_SF_raw);
    Serialprintln("");
    Serialprint("Main Power In 1 Current Sense Feedback: ");
    Serialprint_n(MPIN_C1_SF_raw);
    Serialprintln("");
    Serialprint("Main Power In 2 Current Sense Feedback ");
    Serialprint_n(MPIN_C2_SF_raw);
    Serialprintln("");

    Serialprintln("");
}

void displayADC_volts()
{
    Serialprint("Number of Channels ADC1: ");
    Serialprint_n(ch_count1);
    Serialprintln("");
    Serialprint("Number of Channels ADC2: ");
    Serialprint_n(ch_count2);
    Serialprintln("");
    Serialprintln("");

    Serialprintln("Sensors:");
    Serialprintln("");

    Serialprint("Fuel Sensor 1: ");
    Serialprint_n(Fuel_sen_1);
    Serialprintln("");
    Serialprint("Fuel Sensor 2: ");
    Serialprint_n(Fuel_sen_2);
    Serialprintln("");
    Serialprint("Fuel Sensor 3: ");
    Serialprint_n(Fuel_sen_3);
    Serialprintln("");
    Serialprint("Fuel Sensor 4: ");
    Serialprint_n(Fuel_sen_4);
    Serialprintln("");
    Serialprint("Fuel Sensor 5: ");
    Serialprint_n(Fuel_sen_5);
    Serialprintln("");
    Serialprint("Temperature Sensor: ");
    Serialprint_n(Temp_sen);
    Serialprintln("");
    Serialprint("Pressure Sensor 1: ");
    Serialprint_n(Pres_sen_1);
    Serialprintln("");
    Serialprint("Pressure Sensor 2: ");
    Serialprint_n(Pres_sen_2);
    Serialprintln("");
    Serialprint("Pressure Sensor 3: ");
    Serialprint_n(Pres_sen_3);
    Serialprintln("");
    Serialprint("Pressure Sensor 4: ");
    Serialprint_n(Pres_sen_4);
    Serialprintln("");
    Serialprintln("");

    Serialprintln("Feedbacks:");
    Serialprintln("");

    Serialprint("Pump 1 Current Feedback: ");
    Serialprint_n(TP_1_CF);
    Serialprintln("");
    Serialprint("Pump 2 current Feedback: ");
    Serialprint_n(TP_2_CF);
    Serialprintln("");
    Serialprint("Solenoid Valve 1 Current Feedback: ");
    Serialprint_n(Svalve_1_CF);
    Serialprintln("");
    Serialprint("Solenoid Valve 2 Current Feedback: ");
    Serialprint_n(Svalve_2_CF);
    Serialprintln("");
    Serialprint("Solenoid Valve 3 Current Feedback: ");
    Serialprint_n(Svalve_3_CF);
    Serialprintln("");
    Serialprint("Solenoid Valve 4 Current Feedback: ");
    Serialprint_n(Svalve_4_CF);
    Serialprintln("");
    Serialprint("Main Power 1 Sense Feedback: ");
    Serialprint_n(MPIN_V1_SF);
    Serialprintln("");
    Serialprint("Main Power 2 Sense Feedback: ");
    Serialprint_n(MPIN_V2_SF);
    Serialprintln("");
    Serialprint("Power Supply 1 Output Voltage Sense Feedback: ");
    Serialprint_n(PS1_OV_SF);
    Serialprintln("");
    Serialprint("Power Supply 2 Output Voltage Sense Feedback: ");
    Serialprint_n(PS2_OV_SF);
    Serialprintln("");
    Serialprint("Power Supply 3 Output Voltage Sense Feedback: ");
    Serialprint_n(PS3_OV_SF);
    Serialprintln("");
    Serialprint("Power Supply 4 Output Voltage Sense Feedback: ");
    Serialprint_n(PS4_OV_SF);
    Serialprintln("");
    Serialprint("Main Power In 1 Current Sense Feedback: ");
    Serialprint_n(MPIN_C1_SF);
    Serialprintln("");
    Serialprint("Main Power In 2 Current Sense Feedback ");
    Serialprint_n(MPIN_C2_SF);
    Serialprintln("");

    Serialprintln("");
}

void wait(uint32 time)
{
    while (time)
    {
        time--;
    };
}

#endif /* FMCV2_INCLUDE_ADC_READ_H_ */
