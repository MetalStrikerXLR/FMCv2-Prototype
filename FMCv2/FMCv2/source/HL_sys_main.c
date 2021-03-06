#include "HL_sys_common.h"
#include "HL_system.h"
#include "serial_com.h"
#include "ADC_read.h"
#include "EEPROM_control.h"
#include "data_processor.h"
#include "digital_control.h"
#include "fuelFeed.h"
#include "systemStatus.h"
#include "CAN_com.h"


void main()
{
    Serialbegin(9600);
    initializeCAN();
    initializeADC();
    initializeGIO();
    initializeNHET();
    initializeRTI();
    initializeEEPROM();

    while(1)
    {
        if(SACT_status == 1)
        {
            readSensors();

            //displayADC_raw();       // Debug
            //displayADC_volts();     // Debug

            readDigitalFeed();
            processFuelData(Fuel_sen_1, Fuel_sen_2, Fuel_sen_3, Fuel_sen_4, Fuel_sen_5);
            processTempData(Temp_sen);
            processPresData(Pres_sen_1, Pres_sen_2, Pres_sen_3, Pres_sen_4);

            //displaySensor_data();   // Debug

            updateSysStatus();

            if(ControlM_status == 1 | ControlM_status == 2)
            {
                manualControlUpdate();
            }
            else
            {
                calculateCG();
                calculateBurnSQ();
                manageBurn();
            }

            generatePackets();
            updatePackets();
        }
        else
        {
            manualControlUpdate();
        }
    }
}

void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    if(SACT_status == 1)
    {
        if(notification==rtiNOTIFICATION_COMPARE1)
        {
            transmitPackets();
        }
    }

    if(notification==rtiNOTIFICATION_COMPARE0)
    {
        processFuelFlow(pulse_counter);
        pulse_counter = 0;
    }
}

void edgeNotification( hetBASE_t *  hetREG, uint32  edge)
{
    pulse_counter = pulse_counter + 1;
}

