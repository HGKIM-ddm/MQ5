/***********************************************************************************************************************
 * File        : Lin.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : LIN 인터페이스 (프레임 수신 / 응답 설정)
 ***********************************************************************************************************************/
#ifndef LIN_H
#define LIN_H

#include "Global_Fixed_Cfg.h"
#include "Lin_Cfg.h"

#define LIN_DATA_MAX_BYTE   (8U)                            /* LIN 프레임 최대 데이터 바이트 (버퍼 크기) */

void    Lin_Init(void);                                     /* 차종별 필터 설정 (SetupLIN 다음, EnableLIN 전) */
boolean Lin_GetRxData(Lin_IdType ID, uint8 *Data);          /* 새 수신 데이터 있으면 TRUE + 복사 */
void    Lin_SetTxData(Lin_IdType ID, const uint8 *Data);    /* 응답 데이터 설정 + 응답 허용 */
void    Lin_SetNoResponse(Lin_IdType ID);                   /* 응답 안 함 */
uint32  Lin_GetLastRxMs(void);                              /* 마지막 헤더/데이터 수신 시각 (ms) */

#endif /* LIN_H */
