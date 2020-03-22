#ifndef FMCV2_INCLUDE_ADC_READ_H_
#define FMCV2_INCLUDE_ADC_READ_H_

#include "HL_esm.h"
#include "HL_adc.h"

adcData_t adc_data[10];
uint32 ch_count = 0;

int Fuel_sen_1_raw = 0;
int Fuel_sen_2_raw = 0;
int Fuel_sen_3_raw = 0;
int Fuel_sen_4_raw = 0;
int Fuel_sen_5_raw = 0;
int Temp_sen_raw = 0;
int Pres_sen_1_raw = 0;
int Pres_sen_2_raw = 0;
int Pres_sen_3_raw = 0;
int Pres_sen_4_raw = 0;

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

void wait(uint32 time);

void initializeADC()
{
    adcInit();
}

void readSensors(int debug, int raw)
{
    adcStartConversion(adcREG1, adcGROUP1);

    while ((adcIsConversionComplete(adcREG1, adcGROUP1)) == 0);

    ch_count = adcGetData(adcREG1, adcGROUP1, &adc_data[0]);

    Fuel_sen_1_raw = adc_data[0].value;
    Fuel_sen_2_raw = adc_data[1].value;
    Fuel_sen_3_raw = adc_data[2].value;
    Fuel_sen_4_raw = adc_data[3].value;
    Fuel_sen_5_raw = adc_data[4].value;
    Temp_sen_raw = adc_data[5].value;
    Pres_sen_1_raw = adc_data[6].value;
    Pres_sen_2_raw = adc_data[7].value;
    Pres_sen_3_raw = adc_data[8].value;
    Pres_sen_4_raw = adc_data[9].value;

    Fuel_sen_1 = (Fuel_sen_1_raw * 5)/1023;
    Fuel_sen_2 = (Fuel_sen_2_raw * 5)/1023;
    Fuel_sen_3 = (Fuel_sen_3_raw * 5)/1023;
    Fuel_sen_4 = (Fuel_sen_4_raw * 5)/1023;
    Fuel_sen_5 = (Fuel_sen_5_raw * 5)/1023;
    Temp_sen = (Temp_sen_raw * 5)/1023;
    Pres_sen_1 = (Pres_sen_1_raw * 5)/1023;
    Pres_sen_2 = (Pres_sen_2_raw * 5)/1023;
    Pres_sen_3 = (Pres_sen_3_raw * 5)/1023;
    Pres_sen_4 = (Pres_sen_4_raw * 5)/1023;

    if(debug == 1)
    {
        if(raw == 1)
        {
            Serialprint("Number of Channels: ");
            Serialprint_n(ch_count);
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
        }
        else
        {
            Serialprint("Number of Channels: ");
            Serialprint_n(ch_count);
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
        }
    }

    wait(0xFFFFF);
}

void wait(uint32 time)
{
    while (time)
    {
        time--;
    };
}

#endif /* FMCV2_INCLUDE_ADC_READ_H_ */
