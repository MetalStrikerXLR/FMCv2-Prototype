#ifndef FMCV2_INCLUDE_CAN_COM_H_
#define FMCV2_INCLUDE_CAN_COM_H_

#include "HL_can.h"
#include "HL_esm.h"
#include "HL_sys_core.h"

#define D_COUNT 8
#define mask_1bit 1
#define mask_2bit 3
#define mask_3bit 7
#define mask_4bit 15
#define mask_6bit 63
#define mask_7bit 127
#define mask_8bit 255
#define mask_9bit 511
#define mask_10bit 1023

uint8 SACT_R[D_COUNT] = {0}, ControlM_R[D_COUNT] = {0}, SAIP_R[D_COUNT] = {0}, SAIR_R[D_COUNT] = {0}, TP13_R[D_COUNT] = {0};
uint8 TP31_R[D_COUNT] = {0}, SVRW_R[D_COUNT] = {0}, SVLW_R[D_COUNT] = {0}, SV1_R[D_COUNT] = {0}, SV2_R[D_COUNT] = {0}, rxpack[D_COUNT] = {0};
uint8 Calib_Command[D_COUNT] = {0};

uint8 buffer[D_COUNT]={0};

uint64 SACT = 0;
uint64 ControlM = 0;
uint64 SSIH = 0;
uint64 SSIL = 0;
uint64 SIPH = 0;
uint64 SIPL = 0;
uint64 STF = 0;
uint64 FLSF = 0;
uint64 FLSM = 0;
uint64 FLSR = 0;
uint64 FLSRW = 0;
uint64 FLSLW = 0;
uint64 TS_1 = 0;
uint64 PST13 = 0;
uint64 PST31 = 0;
uint64 PSV = 0;
uint64 PSMFL = 0;
uint64 FFS = 0;
uint64 TP13 = 0;
uint64 TP31 = 0;
uint64 SVRW = 0;
uint64 SVLW = 0;
uint64 SV1 = 0;
uint64 SV2 = 0;

void breakDown(uint64 data);
void clearBuffer();

void initializeCAN()
{
    _enable_IRQ_interrupt_();
    canInit();
    canEnableErrorNotification(canREG1);
    canEnableErrorNotification(canREG2);
}

void generatePackets()
{
    SACT= (0<<1) | (SACT_status & mask_1bit);
    ControlM = (0<<3) | (ControlM_status & mask_3bit);
    SIPH = ((total_mass & mask_10bit)<<54) | ((Tank_FWD_lvl & mask_7bit)<<47)| ((Tank_MID_lvl & mask_7bit)<<40) | ((Tank_REAR_lvl & mask_7bit)<<33) | ((Tank_RT_lvl & mask_7bit)<<26) | ((Tank_LT_lvl & mask_7bit)<<19) | ((Sys_temp & mask_7bit)<<12) | ((FWD_to_REAR_pres & mask_6bit)<<6) | (REAR_to_FWD_pres & mask_6bit);
    SIPL = (0<<27) | ((VENT_Sen_pres & mask_6bit)<<21) | ((MAIN_Flow_pres & mask_6bit)<<15)| ((Fuel_flow_LM & mask_9bit)<<6) | ((FWD_to_REAR_pump_state & mask_1bit)<<5) | ((REAR_to_FWD_pump_state & mask_1bit)<<4) | ((RTW_Svalve_state & mask_1bit)<<3) | ((LTW_Svalve_state & mask_1bit)<<2) | ((NOPEN1_Svalve_state & mask_1bit)<<1) | (NOPEN2_Svalve_state & mask_1bit);
    SSIH = (0<<10) | ((GSS & mask_1bit)<<9) | ((CRR & mask_2bit)<<7)| ((SFS & mask_1bit)<<6) | ((FFPL & mask_1bit)<<5) | ((FFPH & mask_1bit)<<4) | ((VLPH & mask_1bit)<<3) | ((TL1PH & mask_1bit)<<2) | ((TL2PH & mask_1bit)<<1) | (SFTH & mask_1bit);
    SSIL = (0<<19) | ((SFTL & mask_1bit)<<18) | ((RWXV & mask_1bit)<<17)| ((LWXV & mask_1bit)<<16) | ((T1BFV & mask_1bit)<<15) | ((T3BFV & mask_1bit)<<14) | ((BURNSQ & mask_4bit)<<10) | ((PCS5 & mask_1bit)<<9) | ((PCS6 & mask_1bit)<<8) | ((FSC7 & mask_1bit)<<7) | ((FSC6 & mask_1bit)<<6) | ((FSC5 & mask_1bit)<<5) | ((FSC4 & mask_1bit)<<4) | ((FSC3 & mask_1bit)<<3) | ((FSC2 & mask_1bit)<<2) | ((FSC1 & mask_1bit)<<1) | (FSC0 & mask_1bit);
    STF = (0<<10) | (total_vol & mask_10bit);
    FLSF = (0<<7) | (Tank_FWD_per & mask_7bit);
    FLSM = (0<<7) | (Tank_MID_per & mask_7bit);
    FLSR = (0<<7) | (Tank_REAR_per & mask_7bit);
    FLSRW = (0<<7) | (Tank_RT_per & mask_7bit);
    FLSLW = (0<<7) | (Tank_LT_per & mask_7bit);
    TS_1 = (0<<7) | (Sys_temp & mask_7bit);
    PST13 = (0<<6) | (FWD_to_REAR_pres & mask_6bit);
    PST31 = (0<<6) | (REAR_to_FWD_pres & mask_6bit);
    PSV = (0<<6) | (VENT_Sen_pres & mask_6bit);
    PSMFL = (0<<6) | (MAIN_Flow_pres & mask_6bit);
    FFS = (0<<9) | (Fuel_flow_LM & mask_9bit);
    TP13 = (0<<1) | (FWD_to_REAR_pump_state & mask_1bit);
    TP31 = (0<<1) | (REAR_to_FWD_pump_state & mask_1bit);
    SVRW = (0<<1) | (RTW_Svalve_state & mask_1bit);
    SVLW = (0<<1) | (LTW_Svalve_state & mask_1bit);
    SV1 = (0<<1) | (NOPEN1_Svalve_state & mask_1bit);
    SV2 = (0<<1) | (NOPEN2_Svalve_state & mask_1bit);
}

void updatePackets()
{
    breakDown(SACT);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX1, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX1, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(ControlM);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX3, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX3, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(STF);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX11, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX11, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(FLSF);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX12, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX12, (const uint8 * )&buffer[0]);
    clearBuffer();


    breakDown(FLSM);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX13, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX13, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(FLSR);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX14, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX14, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(FLSRW);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX15, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX15, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(FLSLW);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX16, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX16, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(TS_1);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX17, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX17, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(PST13);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX18, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX18, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(PST31);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX19, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX19, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(PSV);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX20, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX20, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(PSMFL);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX21, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX21, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(FFS);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX22, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX22, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(TP13);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX23, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX23, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(TP31);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX25, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX25, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(SVRW);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX27, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX27, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(SVLW);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX29, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX29, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(SV1);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX31, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX31, (const uint8 * )&buffer[0]);
    clearBuffer();

    breakDown(SV2);
    canFillMessageObjectData  (canREG1, canMESSAGE_BOX33, (const uint8 * )&buffer[0]);
    canFillMessageObjectData  (canREG2, canMESSAGE_BOX33, (const uint8 * )&buffer[0]);
    clearBuffer();
}

void transmitPackets()
{
    breakDown(SIPH);
    canTransmit(canREG1, canMESSAGE_BOX5, (const uint8 *)&buffer[0]);
    canTransmit(canREG2, canMESSAGE_BOX5, (const uint8 *)&buffer[0]);
    clearBuffer();

    breakDown(SIPL);
    canTransmit(canREG1, canMESSAGE_BOX6, (const uint8 *)&buffer[0]);
    canTransmit(canREG2, canMESSAGE_BOX6, (const uint8 *)&buffer[0]);
    clearBuffer();

    breakDown(SSIH);
    canTransmit(canREG1, canMESSAGE_BOX7, (const uint8 *)&buffer[0]);
    canTransmit(canREG2, canMESSAGE_BOX7, (const uint8 *)&buffer[0]);
    clearBuffer();

    breakDown(SSIL);
    canTransmit(canREG1, canMESSAGE_BOX8, (const uint8 *)&buffer[0]);
    canTransmit(canREG2, canMESSAGE_BOX8, (const uint8 *)&buffer[0]);
    clearBuffer();
}

void breakDown(uint64 data)
{
    uint8 i=0;
    do buffer[i++]=data&0xFF; while (data>>=8);
}

void clearBuffer()
{
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    buffer[4] = 0;
    buffer[5] = 0;
    buffer[6] = 0;
    buffer[7] = 0;
}

void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
     if(node==canREG1)
     {
         if(messageBox == canMESSAGE_BOX2)
         {
             canGetData(canREG1, canMESSAGE_BOX2, (uint8 * )&SACT_R[0]);

             if(SACT_R[0] == 1)
             {
                 SACT_status = 1;
             }
             else if(SACT_R[0] == 0)
             {
                 SACT_status = 0;
                 M_FTRP_State = 0;
                 M_RTFP_State = 0;
             }
             else
             {
                 // Wrong Input Command
             }
         }

         if(messageBox == canMESSAGE_BOX4)
         {
             canGetData(canREG1, canMESSAGE_BOX4, (uint8 * )&ControlM_R[0]);

             if(ControlM_R[0] == 0)
             {
                 ControlM_status = 0; // Autonomus
                 M_FTRP_State = 0;
                 M_RTFP_State = 0;
                 M_LTWS_State = 0;
                 M_RTWS_State = 0;
                 M_NO1S_State = 0;
                 M_NO2S_State = 0;
             }
             else if(ControlM_R[0] == 1)
             {
                 ControlM_status = 1; // Manual
                 M_FTRP_State = 0;
                 M_RTFP_State = 0;
                 M_LTWS_State = 0;
                 M_RTWS_State = 0;
                 M_NO1S_State = 0;
                 M_NO2S_State = 0;
             }
             else if(ControlM_R[0] == 2)
             {
                 ControlM_status = 2; // Fail Safe - Open all Solenoid Valves
                 M_FTRP_State = 0;
                 M_RTFP_State = 0;
                 M_LTWS_State = 1;
                 M_RTWS_State = 1;
                 M_NO1S_State = 1;
                 M_NO2S_State = 1;
             }
             else
             {
                 // Wrong Input Command
             }

         }

         if(messageBox == canMESSAGE_BOX9)
         {
             canGetData(canREG1, canMESSAGE_BOX9, (uint8 * )&SAIP_R[0]);
             pitch = SAIP_R[0];
         }

         if(messageBox == canMESSAGE_BOX10)
         {
             canGetData(canREG1, canMESSAGE_BOX10, (uint8 * )&SAIR_R[0]);
             roll = SAIR_R[0];
         }

         if(messageBox == canMESSAGE_BOX24)
         {
             canGetData(canREG1, canMESSAGE_BOX24, (uint8 * )&TP13_R[0]);

             if(ControlM_status == 1)
             {
                 M_FTRP_State = TP13_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX26)
         {
             canGetData(canREG1, canMESSAGE_BOX26, (uint8 * )&TP31_R[0]);

             if(ControlM_status == 1)
             {
                 M_RTFP_State = TP31_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX28)
         {
             canGetData(canREG1, canMESSAGE_BOX28, (uint8 * )&SVRW_R[0]);

             if(ControlM_status == 1)
             {
                 M_RTWS_State = SVRW_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX30)
         {
             canGetData(canREG1, canMESSAGE_BOX30, (uint8 * )&SVLW_R[0]);

             if(ControlM_status == 1)
             {
                 M_LTWS_State = SVLW_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX32)
         {
             canGetData(canREG1, canMESSAGE_BOX32, (uint8 * )&SV1_R[0]);

             if(ControlM_status == 1)
             {
                 M_NO1S_State = SV1_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX34)
         {
             canGetData(canREG1, canMESSAGE_BOX34, (uint8 * )&SV2_R[0]);

             if(ControlM_status == 1)
             {
                 M_NO2S_State = SV2_R[0];
             }
         }

         if(messageBox == canMESSAGE_BOX35)
         {
             canGetData(canREG1, canMESSAGE_BOX35, (uint8 * )&Calib_Command[0]);

            if(Calib_Command[0] == 1)
            {
                updateEEPROM(0x1, Fuel_sen_1);
            }
            if(Calib_Command[0] == 2)
            {
                updateEEPROM(0x2, Fuel_sen_1);
            }
            if(Calib_Command[0] == 3)
            {
                updateEEPROM(0x3, Fuel_sen_2);
            }
            if(Calib_Command[0] == 4)
            {
                updateEEPROM(0x4, Fuel_sen_2);
            }
            if(Calib_Command[0] == 5)
            {
                updateEEPROM(0x5, Fuel_sen_3);
            }
            if(Calib_Command[0] == 6)
            {
                updateEEPROM(0x6, Fuel_sen_3);
            }
            if(Calib_Command[0] == 7)
            {
                updateEEPROM(0x7, Fuel_sen_4);
            }
            if(Calib_Command[0] == 8)
            {
                updateEEPROM(0x8, Fuel_sen_4);
            }
            if(Calib_Command[0] == 9)
            {
                updateEEPROM(0x9, Fuel_sen_5);
            }
            if(Calib_Command[0] == 10)
            {
                updateEEPROM(0xA, Fuel_sen_5);
            }
         }

     }
     if(node==canREG2)
     {
         if(messageBox == canMESSAGE_BOX2)
          {
              canGetData(canREG2, canMESSAGE_BOX2, (uint8 * )&SACT_R[0]);

              if(SACT_R[0] == 1)
              {
                  SACT_status = 1;
              }
              else if(SACT_R[0] == 0)
              {
                  SACT_status = 0;
                  M_FTRP_State = 0;
                  M_RTFP_State = 0;
              }
              else
              {
                  // Wrong Input Command
              }
          }

          if(messageBox == canMESSAGE_BOX4)
          {
              canGetData(canREG2, canMESSAGE_BOX4, (uint8 * )&ControlM_R[0]);

              if(ControlM_R[0] == 0)
              {
                  ControlM_status = 0; // Autonomus
                  M_FTRP_State = 0;
                  M_RTFP_State = 0;
                  M_LTWS_State = 0;
                  M_RTWS_State = 0;
                  M_NO1S_State = 0;
                  M_NO2S_State = 0;
              }
              else if(ControlM_R[0] == 1)
              {
                  ControlM_status = 1; // Manual
                  M_FTRP_State = 0;
                  M_RTFP_State = 0;
                  M_LTWS_State = 0;
                  M_RTWS_State = 0;
                  M_NO1S_State = 0;
                  M_NO2S_State = 0;
              }
              else if(ControlM_R[0] == 2)
              {
                  ControlM_status = 2; // Fail Safe - Open all Solenoid Valves
                  M_FTRP_State = 0;
                  M_RTFP_State = 0;
                  M_LTWS_State = 1;
                  M_RTWS_State = 1;
                  M_NO1S_State = 1;
                  M_NO2S_State = 1;
              }
              else
              {
                  // Wrong Input Command
              }

          }

          if(messageBox == canMESSAGE_BOX9)
          {
              canGetData(canREG2, canMESSAGE_BOX9, (uint8 * )&SAIP_R[0]);
              pitch = SAIP_R[0];
          }

          if(messageBox == canMESSAGE_BOX10)
          {
              canGetData(canREG2, canMESSAGE_BOX10, (uint8 * )&SAIR_R[0]);
              roll = SAIR_R[0];
          }

          if(messageBox == canMESSAGE_BOX24)
          {
              canGetData(canREG2, canMESSAGE_BOX24, (uint8 * )&TP13_R[0]);

              if(ControlM_status == 1)
              {
                  M_FTRP_State = TP13_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX26)
          {
              canGetData(canREG2, canMESSAGE_BOX26, (uint8 * )&TP31_R[0]);

              if(ControlM_status == 1)
              {
                  M_RTFP_State = TP31_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX28)
          {
              canGetData(canREG2, canMESSAGE_BOX28, (uint8 * )&SVRW_R[0]);

              if(ControlM_status == 1)
              {
                  M_RTWS_State = SVRW_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX30)
          {
              canGetData(canREG2, canMESSAGE_BOX30, (uint8 * )&SVLW_R[0]);

              if(ControlM_status == 1)
              {
                  M_LTWS_State = SVLW_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX32)
          {
              canGetData(canREG2, canMESSAGE_BOX32, (uint8 * )&SV1_R[0]);

              if(ControlM_status == 1)
              {
                  M_NO1S_State = SV1_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX34)
          {
              canGetData(canREG2, canMESSAGE_BOX34, (uint8 * )&SV2_R[0]);

              if(ControlM_status == 1)
              {
                  M_NO2S_State = SV2_R[0];
              }
          }

          if(messageBox == canMESSAGE_BOX35)
          {
              canGetData(canREG2, canMESSAGE_BOX35, (uint8 * )&Calib_Command[0]);

             if(Calib_Command[0] == 1)
             {
                 updateEEPROM(0x1, Fuel_sen_1);
             }
             if(Calib_Command[0] == 2)
             {
                 updateEEPROM(0x2, Fuel_sen_1);
             }
             if(Calib_Command[0] == 3)
             {
                 updateEEPROM(0x3, Fuel_sen_2);
             }
             if(Calib_Command[0] == 4)
             {
                 updateEEPROM(0x4, Fuel_sen_2);
             }
             if(Calib_Command[0] == 5)
             {
                 updateEEPROM(0x5, Fuel_sen_3);
             }
             if(Calib_Command[0] == 6)
             {
                 updateEEPROM(0x6, Fuel_sen_3);
             }
             if(Calib_Command[0] == 7)
             {
                 updateEEPROM(0x7, Fuel_sen_4);
             }
             if(Calib_Command[0] == 8)
             {
                 updateEEPROM(0x8, Fuel_sen_4);
             }
             if(Calib_Command[0] == 9)
             {
                 updateEEPROM(0x9, Fuel_sen_5);
             }
             if(Calib_Command[0] == 10)
             {
                 updateEEPROM(0xA, Fuel_sen_5);
             }
          }
     }
}

#endif
