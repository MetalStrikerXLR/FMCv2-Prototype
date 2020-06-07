#ifndef FMCV2_INCLUDE_SYSTEMSTATUS_H_
#define FMCV2_INCLUDE_SYSTEMSTATUS_H_

int GSS = 0;     // General System Status
int CRR = 0;     // Heart beat refresh rate
int SFS = 0;     // System Fuel Level Status
int FFPL = 0;    // Feed Line Fuel Pressure Low
int FFPH = 0;    // Feed Line Fuel Pressure High
int VLPH = 0;    // Vent Line Vapor Pressure High
int TL1PH = 0;   // Transfer Line 1 Pressure High
int TL2PH = 0;   // Transfer Line 2 Pressure High
int SFTH = 0;    // System Fuel Temperature High
int SFTL = 0;    // System Fuel Temperature Low
int RWXV = 0;    // Right Wing Cross-Feed Valve  Error
int LWXV = 0;    // Left Wing Cross-Feed Valve Error
int T1BFV = 0;   // Tank 1 Backup Feed Valve
int T3BFV = 0;   // Tank 3 Backup Feed Valve
int PCS5 = 0;    // Plug 5 Connection Status
int PCS6 = 0;    // Plug 5 Connection Status
int FSC0 = 0;    // Fuel Flow Sensor Error
int FSC1 = 0;    // Pressure Sensor Main Flow Line Error
int FSC2 = 0;    // Pressure Sensor Vent Error
int FSC3 = 0;    // Pressure Sensor T3-T1 Error
int FSC4 = 0;    // Pressure Sensor T1-T3 Error
int FSC5 = 0;    // Temperature Sensor Error
int FSC6 = 0;    // Level Sensor Left Wing Error
int FSC7 = 0;    // Level Sensor Right Wing Error
int SACT_status = 0;
int ControlM_status = 0;

void updateSysStatus()
{
    if(total_vol < 70)
    {
        SFS = 1;
    }
    else
    {
        SFS = 0;
    }

    if(MAIN_Flow_pres < 30)
    {
        FFPL = 1;
    }
    else
    {
        FFPL = 0;
    }

    if(MAIN_Flow_pres > 38)
    {
        FFPH = 1;
    }
    else
    {
        FFPH = 0;
    }

    if(VENT_Sen_pres > 15)
    {
        VLPH = 1;
    }
    else
    {
        VLPH = 0;
    }

    if(FWD_to_REAR_pres > 15)
    {
        TL1PH = 1;
    }
    else
    {
        TL1PH = 0;
    }

    if(REAR_to_FWD_pres > 15)
    {
        TL2PH = 1;
    }
    else
    {
        TL2PH = 0;
    }

    if(Sys_temp > 65)
    {
        SFTH = 1;
    }
    else
    {
        SFTH = 0;
    }

    if(Sys_temp < 0)
    {
        SFTL = 1;
    }
    else
    {
        SFTL = 0;
    }

    if(RTW_Svalve_state == 1)
    {
        RWXV = 1;
    }
    else
    {
        RWXV = 0;
    }

    if(LTW_Svalve_state == 1)
    {
        LWXV = 1;
    }
    else
    {
        LWXV = 0;
    }

    if(NOPEN1_Svalve_state == 1)
    {
        T1BFV = 1;
    }
    else
    {
        T1BFV = 0;
    }

    if(NOPEN2_Svalve_state == 1)
    {
        T3BFV = 1;
    }
    else
    {
        T3BFV = 0;
    }
}

#endif
