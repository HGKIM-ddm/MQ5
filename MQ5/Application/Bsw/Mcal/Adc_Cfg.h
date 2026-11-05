/***********************************************************************************************************************
 * File        : Adc_Cfg.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : ADC 채널 ID 정의 (MQ5_AAF_V0.0 보드 기준)
 ***********************************************************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "Std_Types.h"

typedef uint8 Adc_ChannelType;

/*      Channel ID                                 |  ADC0 CH | Net (schematic)     |                  Note                 */

#define ADC_CH_VBAT         ((Adc_ChannelType)0U)  /* CH01      VBAT_SEN              Battery voltage (x0.0466)             */

#define ADC_CH_COUNT        (1U)

#endif /* ADC_CFG_H */
