/***********************************************************************************************************************
 * File        : Dio_Cfg.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 디지털 입출력 채널 ID 정의 (MQ5_AAF_V0.0 보드 기준)
 ***********************************************************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "Global_Fixed_Cfg.h"

typedef uint8 Dio_ChannelType;

/*      Channel ID                                 |  Pin  |  Net (schematic)   | Dir  |            Note                     */

#define DIO_CH_DRVOFF       ((Dio_ChannelType)0U)  /* GPA0   MCU_DRVOFF           Out   High = motor output OFF              */
#define DIO_CH_DRV_SLEEP    ((Dio_ChannelType)1U)  /* GPA3   MCU_DRV_SLEEP_MODE   Out   Low  = DRV8889 sleep (nSLEEP)        */
#define DIO_CH_DIR          ((Dio_ChannelType)2U)  /* GPA5   MCU_DIR              Out                                        */
#define DIO_CH_NSCS         ((Dio_ChannelType)3U)  /* GPB3   MCU_nSCS             Out   Low  = SPI chip select               */
#define DIO_CH_NFAULT       ((Dio_ChannelType)4U)  /* GPC0   MCU_DRV_nFAULT       In    Low  = fault (also Low in DRV sleep) */

#define DIO_CH_COUNT        (5U)

#endif /* DIO_CFG_H */
