/***********************************************************************************************************************
 * File        : Global_Cfg.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL
 *                 - Common        <== HERE
 * Description : 코드명 선택 (빌드 시 변경) 및 코드명별 설정
 ***********************************************************************************************************************/
#ifndef GLOBAL_CFG_H
#define GLOBAL_CFG_H

#include "Global_Fixed_Cfg.h"

/* ====================================================================
 * 선택 항목 (빌드 전 이 한 줄만 변경)
 * ==================================================================== */
#define VEHICLE_CODENAME    MQ5_ICE_AAF1    /* Global_Fixed_Cfg.h 코드명 중 선택 */

/* ====================================================================
 * 코드명별 설정 (코드명 추가 시 블록 추가)
 * ==================================================================== */
#if   (VEHICLE_CODENAME == MQ5_ICE_AAF1)
    #define VEHICLE_TYPE    ICE
    #define AAF_INDEX       AAF_1

#elif (VEHICLE_CODENAME == MQ5_ICE_AAF2)
    #define VEHICLE_TYPE    ICE
    #define AAF_INDEX       AAF_2

#elif (VEHICLE_CODENAME == MQ5_ICE_AAF3)
    #define VEHICLE_TYPE    ICE
    #define AAF_INDEX       AAF_3

#elif (VEHICLE_CODENAME == MQ5_EV_AAF1)
    #define VEHICLE_TYPE    EV
    #define AAF_INDEX       AAF_1

#elif (VEHICLE_CODENAME == MQ5_EV_AAF2)
    #define VEHICLE_TYPE    EV
    #define AAF_INDEX       AAF_2

#elif (VEHICLE_CODENAME == MQ5_EV_AAF3)
    #define VEHICLE_TYPE    EV
    #define AAF_INDEX       AAF_3

#else
    #error "VEHICLE_CODENAME : Global_Fixed_Cfg.h 코드명 중 선택"
#endif

/* ====================================================================
 * 선택 값 검사
 * ==================================================================== */
#if (VEHICLE_TYPE != ICE) && (VEHICLE_TYPE != EV)
#error "VEHICLE_TYPE : ICE or EV"
#endif

#if (AAF_INDEX != AAF_1) && (AAF_INDEX != AAF_2) && (AAF_INDEX != AAF_3)
#error "AAF_INDEX : AAF_1 / AAF_2 / AAF_3"
#endif

#endif /* GLOBAL_CFG_H */
