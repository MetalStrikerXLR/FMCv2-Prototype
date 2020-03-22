#include "HL_sys_common.h"
#include "HL_system.h"
#include "serial_com.h"
#include "ADC_read.h"
#include "CAN_com.h"
#include "manual_control.h"
#include "data_processor.h"

void main()
{
    Serialbegin(9600);
    initializeCAN();
    initializeADC();
    initializeGIO();
    initializeRTI();

    canTransmit(canREG1, canMESSAGE_BOX1, (const uint8 *) &tx_data1[0]);

    while(1)
    {
        readSensors(0,1);
        processFuelData(Fuel_sen_1, Fuel_sen_2, Fuel_sen_3, Fuel_sen_4, Fuel_sen_5);
        processTempData(Temp_sen);
        processPresData(Pres_sen_1, Pres_sen_2, Pres_sen_3, Pres_sen_4);

        generatePackets();
        transmitPackets();
    }
}

void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    processFuelFlow(counter);
    counter = 0;
}

void gioNotification(gioPORT_t *port, uint32 bit)
{
    counter = counter + 1;
}

