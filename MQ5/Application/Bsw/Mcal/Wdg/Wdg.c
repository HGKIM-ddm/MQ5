/***********************************************************************************************************************
 * File        : Wdg.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 워치독 인터페이스
 ***********************************************************************************************************************/
#include "Wdg.h"
#include "device_LX61101.h"
#include "system_LX61101.h"

void Wdg_Refresh(void)
{
    RefreshWDT();
}

/* 마지막 리셋 원인이 WDT 인지 
SetupEssential() 에서 저장한 리셋 원인(SystemResetReason, RCU->RIR bit5 WDTRST) 사용
*/ 
boolean Wdg_IsResetByWdt(void)
{
    return ((SystemResetReason & RSTINFO_WDT) != 0U) ? TRUE : FALSE;
}
