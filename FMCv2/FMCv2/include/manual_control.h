#ifndef FMCV2_INCLUDE_MANUAL_CONTROL_H_
#define FMCV2_INCLUDE_MANUAL_CONTROL_H_

#include "HL_gio.h"

int counter = 0;

initializeGIO()
{
    gioInit();

    gioSetBit(gioPORTA,0,0); //Fuel Flow Sensor

    gioSetBit(gioPORTB,1,0); //Pump 1
    gioSetBit(gioPORTB,2,0); //Pump 2

    gioSetBit(gioPORTB,4,0); //Valve 1
    gioSetBit(gioPORTB,5,0); //Valve 2
    gioSetBit(gioPORTB,6,0); //Valve 3
    gioSetBit(gioPORTB,7,0); //Valve 4

    gioEnableNotification(gioPORTA, 0);
}

void manualControlUpdate(int command)
{
    if(command == 001)
    {
        gioSetBit(gioPORTB,1,1);
    }
    else
    {
        gioSetBit(gioPORTB,1,0);
    }

    if(command == 010)
    {
        gioSetBit(gioPORTB,2,1);
    }
    else
    {
        gioSetBit(gioPORTB,2,0);
    }

    if(command == 100)
    {
        gioSetBit(gioPORTB,4,1);
    }
    else
    {
        gioSetBit(gioPORTB,4,0);
    }

    if(command == 111)
    {
        gioSetBit(gioPORTB,5,1);
    }
    else
    {
        gioSetBit(gioPORTB,5,0);
    }

    if(command == 11)
    {
        gioSetBit(gioPORTB,6,1);
    }
    else
    {
        gioSetBit(gioPORTB,6,0);
    }

    if(command == 101)
    {
        gioSetBit(gioPORTB,7,1);
    }
    else
    {
        gioSetBit(gioPORTB,7,0);
    }
}

#endif
