/***********************************************************************************************************************
 * File        : Adc.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : ADC 인터페이스 (채널별 변환값 읽기)
 ***********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

#include "Global_Fixed_Cfg.h"
#include "Adc_Cfg.h"

uint16 Adc_GetValue(Adc_ChannelType ID);           /* 1회 변환값 (10bit, 0~1023) */

#endif /* ADC_H */
