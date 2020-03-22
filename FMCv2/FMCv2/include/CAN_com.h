#ifndef FMCV2_INCLUDE_CAN_COM_H_
#define FMCV2_INCLUDE_CAN_COM_H_

#include "HL_can.h"
#include "HL_sys_core.h"

#define D_COUNT  8

uint32 cnt=0, error =0, tx_done =0;
uint8 tx_data1[D_COUNT] = {1,2,3,4,5,6,7,8};
uint8 tx_data2[D_COUNT] = {11,12,13,14,15,16,17,18};

uint8 rx_data1[D_COUNT] = {0};
uint8 rx_data2[D_COUNT] = {0};

uint8 *dptr=0;

void initializeCAN()
{
    _enable_IRQ_interrupt_();
    canInit();
    canEnableErrorNotification(canREG1);
    canEnableErrorNotification(canREG2);
}

void generatePackets()
{}

void transmitPackets()
{
    canTransmit(canREG1, canMESSAGE_BOX1, (const uint8 *) &tx_data1[0]);
}

void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
     if(node==canREG1)
     {
         canGetData(canREG1, canMESSAGE_BOX2, (uint8 * )&rx_data1[0]); /* copy to RAM */
         Serialprintln("Recieved on CAN1");
     }
     if(node==canREG2)
     {
         canGetData(canREG2, canMESSAGE_BOX2, (uint8 * )&rx_data2[0]); /* copy to RAM */
         Serialprintln("Recieved on CAN2");
     }
}

uint32_t checkPackets(uint8_t *src_packet, uint8_t *dst_packet, uint32_t psize)
{
    uint32_t err=0;
    uint32_t cnt=psize;
    while(cnt--)
    {
      if((*src_packet++) != (*dst_packet++))                                  // Check if source packet == destination packet
      err++;                                                                  // If true increment the error variable
    }
    return (err);                                                             // Return error, used to monitor no. of errors occured
}

#endif
