/***********************************************************************************************************************
 * File        : Wdg.h
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
#ifndef WDG_H
#define WDG_H

#include "Global_Fixed_Cfg.h"

void    Wdg_Refresh(void);                                  /* WDT 리프레시 (메인 루프에서 1.671s 안에 호출) */
boolean Wdg_IsResetByWdt(void);                             /* 마지막 리셋 원인이 WDT 인지 */

#endif /* WDG_H */
