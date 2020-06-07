#ifndef FMCV2_INCLUDE_EEPROM_CONTROL_H_
#define FMCV2_INCLUDE_EEPROM_CONTROL_H_

#include "ti_fee.h"

uint16 Status;
unsigned char read_data[10]={0};
uint8 SpecialRamBlock[10];

unsigned int BlockNumber = 0x1;
unsigned int BlockOffset = 0;
unsigned int Length = 0xFFFF;
unsigned char *Read_Ptr=read_data;
unsigned int loop;

void delay(void);

void initializeEEPROM(void)
{
    TI_Fee_Init();
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0 );
    }
    while(Status!= IDLE);
    Serialprintln("FEE initialized...");
}

void updateEEPROM()
{
    TI_Fee_WriteSync(BlockNumber, &SpecialRamBlock[0]);
}

void readEEPROM()
{
    TI_Fee_ReadSync(BlockNumber,BlockOffset,Read_Ptr,Length);
}

void invalidateEPROM()
{
    TI_Fee_InvalidateBlock(BlockNumber);
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0);
    }
    while(Status!=IDLE);
}

void formatEEPROM()
{
    TI_Fee_Format(0xA5A5A5A5U);
}

void delay(void)
{
    unsigned int dummycnt=0x0000FFU;
    do
    {
        dummycnt--;
    }
    while(dummycnt>0);
}

#endif
