/***********************************************************************************************************************
 * File        : Std_Types.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL
 *                 - Common        <== HERE
 * Description : 모든 계층에서 사용하는 공통 타입 정의
 ***********************************************************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "common.h"

//USE_DEPRECATED_DEFINITION 정의가 없으면 빌드 중단 + 메시지 출력
#ifndef USE_DEPRECATED_DEFINITION 
#error "Keil Target Options > C/C++ > Define : USE_DEPRECATED_DEFINITION is required" 
#endif

#endif /* STD_TYPES_H */
