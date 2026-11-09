/***********************************************************************************************************************
 * File        : Lin_Tune.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : LIN ID 정의 (기능요구사양서 5.3.2 LIN ID Table 기준)
 ***********************************************************************************************************************/
#ifndef LIN_TUNE_H
#define LIN_TUNE_H

#include "Config.h"
#include "Config_Tune.h"

typedef uint8 Lin_IdType;

/* ====================================================================
 * 5.3.2.1 ICE 차종 (EMS)
 * ==================================================================== */
#define LIN_EMS_AAF_CONTROL     ((Lin_IdType)0x25U)     /* EMS → AAF, 6B (5.3.3)              */
#define LIN_AAF_STATUS          ((Lin_IdType)0x26U)     /* AAF → EMS, 7B (5.3.6), AAF#1~3 공통 */

/* ====================================================================
 * 5.3.2.2 EV 차종 (VCU(VPC))
 * ==================================================================== */
#define LIN_AAF_CTRL            ((Lin_IdType)0x27U)     /* VCU → AAF, 8B (5.3.4)              */
#define LIN_AAF1_RESP           ((Lin_IdType)0x28U)     /* AAF1 → VCU, 7B (5.3.8)             */
#define LIN_AAF2_RESP           ((Lin_IdType)0x29U)     /* AAF2 → VCU, 7B (5.3.8)             */
#define LIN_AAF3_RESP           ((Lin_IdType)0x2AU)     /* AAF3 → VCU, 7B (5.3.8)             */

/* ====================================================================
 * 진단 (공통)
 * ==================================================================== */
#define LIN_MASTER_REQ          ((Lin_IdType)0x3CU)     /* Master Request                     */
#define LIN_SLAVE_RESP          ((Lin_IdType)0x3DU)     /* Slave Response                     */

/* ====================================================================
 * 선택 결과 (Config_Tune.h 의 VEHICLE_TYPE / AAF_INDEX 에 따라 결정)
 * ==================================================================== */
#if (VEHICLE_TYPE == ICE)

    #define LIN_CTRL            LIN_EMS_AAF_CONTROL
    #define LIN_CTRL_BYTE       (6U)
    #define LIN_RESP            LIN_AAF_STATUS
    #define LIN_RESP_BYTE       (7U)

#else /* EV */

    #define LIN_CTRL            LIN_AAF_CTRL
    #define LIN_CTRL_BYTE       (8U)

    #if   (AAF_INDEX == AAF_1)
        #define LIN_RESP        LIN_AAF1_RESP
    #elif (AAF_INDEX == AAF_2)
        #define LIN_RESP        LIN_AAF2_RESP
    #else
        #define LIN_RESP        LIN_AAF3_RESP
    #endif
    #define LIN_RESP_BYTE       (7U)

#endif

#endif /* LIN_TUNE_H */
