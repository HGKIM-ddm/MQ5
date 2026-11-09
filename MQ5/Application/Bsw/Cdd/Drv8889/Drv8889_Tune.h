/***********************************************************************************************************************
 * File        : Drv8889_Tune.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD           <== HERE
 *                 - MCAL
 *                 - Common
 * Description : DRV8889-Q1 레지스터 설정값 (기존 feature/Drv8889 Drv8889_SpiInit 기준)
 ***********************************************************************************************************************/
#ifndef DRV8889_TUNE_H
#define DRV8889_TUNE_H

#include "Drv8889.h"

#define DRV8889_CTRL1   ((uint8)(TRQ_DAC_62_5 | SLEW_RATE_10V))
#define DRV8889_CTRL2   ((uint8)(DIS_OUT_ENABLE | TOFF_16US | DECAY_SMART_RIPPLE))
#define DRV8889_CTRL3   ((uint8)(SPI_DIR_PIN | SPI_STEP_PIN | MICROSTEP_1_8))
#define DRV8889_CTRL4   ((uint8)(LOCK_UNLOCK | EN_OL_ON | OCP_LATCH | OTSD_RECOVER | TW_NO_REP))
#define DRV8889_CTRL5   ((uint8)(EN_STL_ON | STL_REP_OFF | EN_SR_BLANK_ON))
#define DRV8889_CTRL6   ((uint8)15U)                        /* STALL_TH */

#endif /* DRV8889_TUNE_H */
