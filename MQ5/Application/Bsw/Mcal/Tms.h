/***********************************************************************************************************************
 * File        : Tms.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 타이머 인터페이스 (1ms 틱, 1us 틱)
 ***********************************************************************************************************************/
#ifndef TMS_H
#define TMS_H

#include "Global_Fixed_Cfg.h"

uint32 Tms_GetTickMs(void);                        /* 1 = 1ms (TMS01) */
uint32 Tms_GetTickUs(void);                        /* 1 = 1us (TMS00) */

#endif /* TMS_H */
