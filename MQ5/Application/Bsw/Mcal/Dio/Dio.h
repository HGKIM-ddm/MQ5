/***********************************************************************************************************************
 * File        : Dio.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 디지털 입출력 인터페이스 (타입, 함수 선언)
 ***********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H

#include "Config.h"
#include "Dio_Tune.h"

typedef uint8 Dio_LevelType;    /* STD_HIGH / STD_LOW */

void          Dio_WriteChannel(Dio_ChannelType ID, Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ID);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ID);

#endif /* DIO_H */
