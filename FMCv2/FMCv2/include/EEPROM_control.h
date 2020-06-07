#ifndef FMCV2_INCLUDE_EEPROM_CONTROL_H_
#define FMCV2_INCLUDE_EEPROM_CONTROL_H_

#include "ti_fee.h"

uint16 Status;
unsigned char read_data[2]={0};
uint8 SpecialRamBlock[2] = {0};

unsigned int BlockOffset = 0;
unsigned int Length = 0xFFFF;
unsigned char *Read_Ptr=read_data;

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
}

void updateEEPROM(unsigned int block_num, uint8 value)
{
    SpecialRamBlock[0] = value;
    TI_Fee_WriteSync(block_num, &SpecialRamBlock[0]);
    SpecialRamBlock[0] = 0;
    SpecialRamBlock[1] = 0;
}

unsigned char readEEPROM(unsigned int block_num)
{
    read_data[0] = 0;
    read_data[1] = 0;
    TI_Fee_ReadSync(block_num,BlockOffset,Read_Ptr,Length);
    return read_data[0];
}

void invalidateEPROM(unsigned int block_num)
{
    TI_Fee_InvalidateBlock(block_num);
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
