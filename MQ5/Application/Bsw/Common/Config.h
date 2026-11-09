/***********************************************************************************************************************
 * File        : Config.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL
 *                 - Common        <== HERE
 * Description : 모든 계층에서 사용하는 공통 타입 / 고정 정의 (변경 없음)
 ***********************************************************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

#include "common.h"

//USE_DEPRECATED_DEFINITION 정의가 없으면 빌드 중단 + 메시지 출력
#ifndef USE_DEPRECATED_DEFINITION 
#error "Keil Target Options > C/C++ > Define : USE_DEPRECATED_DEFINITION is required" 
#endif

/* ====================================================================
 * 코드명 (Config_Tune.h VEHICLE_CODENAME 선택 값)
 * ==================================================================== */
#define MQ5_ICE_AAF1        (1U)
#define MQ5_ICE_AAF2        (2U)
#define MQ5_ICE_AAF3        (3U)
#define MQ5_EV_AAF1         (4U)
#define MQ5_EV_AAF2         (5U)
#define MQ5_EV_AAF3         (6U)

/* ====================================================================
 * 차종 (코드명별 VEHICLE_TYPE 값)
 * ==================================================================== */
#define ICE                 (1U)            /* ICE 차종 (EMS)         */
#define EV                  (2U)            /* EV 차종 (VCU(VPC))     */

/* ====================================================================
 * AAF 번호 (코드명별 AAF_INDEX 값, signal : AAF_Index)
 * ==================================================================== */
#define AAF_1               (1U)
#define AAF_2               (2U)
#define AAF_3               (3U)

#endif /* CONFIG_H */
