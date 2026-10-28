/**
 *******************************************************************************
 * @file    common.h
 * @brief   All common macro and definition for LX61202 peripheral drivers
 * @version V1.0.0
 * @date    2023/01/05
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright LX Semicon CORPORATION 2023 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LX61_COMMON_H_
#define LX61_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup LX61_Periph_Driver
 * @{
 */

/** @addtogroup COMMON
 * @{
 */

/* Exported typedef ----------------------------------------------------------*/
/** @defgroup COMMON_Exported_Types
 * @{
 */
/* Basic Typedef */
typedef unsigned char           boolean;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned long long      uint64;

typedef signed char             sint8;
typedef signed short            sint16;
typedef signed int              sint32;
typedef signed long long        sint64;

typedef float                   float32;
typedef double                  float64;

typedef char                    char_t;

typedef volatile sint8          vint8_t;
typedef volatile uint8          vuint8_t;

typedef volatile sint16         vint16_t;
typedef volatile uint16         vuint16_t;

typedef volatile sint32         vint32_t;
typedef volatile uint32         vuint32_t;

typedef volatile sint64         vint64_t;
typedef volatile uint64         vuint64_t;

#ifdef USE_DEPRECATED_DEFINITION

/* STD_EnableType */
typedef enum
{
    DISABLE     = 0,
    ENABLE      = 1
} STD_EnableType;

typedef enum
{
    ERROR   = 0,
    SUCCESS = 1
} STD_ResultType;
/** @} */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMMON_Exported_Constants
 * @{
 */
#define NULL_PTR        ((void *)0)

#define FALSE           0UL
#define TRUE            1UL

#define STD_HIGH        0x01UL
#define STD_LOW         0x00UL

#define STD_ACTIVE      0x01UL
#define STD_IDLE        0x00UL

#define STD_ON          0x01UL
#define STD_OFF         0x00UL

#define STD_DEFAULT     0xFFUL

#define ERROR_OK                (0x00)
#define ERROR_UNKNOWN           (0x01)
#define ERROR_NOT_AVAILABLE	    (0x02)
#define ERROR_INVALID_ARGUMENT  (0x03)
#define ERROR_TIME_OUT          (0x04)
#define ERROR_NOT_INITIALIZED   (0x05)
#define ERROR_RINGBUF_FULL      (0x06)
#define ERROR_RINGBUF_EMPTY     (0x07)
#define ERROR_NOT_SUPPORTED     (0x08)

/** @} */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMMON_Exported_Macros
 * @{
 */
#define IS_ENABLE_TYPE(Param)       (((Param) == DISABLE) || ((Param) == ENABLE))
#define IS_POINTER_NOT_NULL(Param)  ((void*)(Param) != NULL_PTR)

/*
 * To report the file name, function name and source line number where the
 * ASSERT_PARAM error has occurred, you need to define "DEBUG".
 */
#ifdef DEBUG
void ReportParamError(const char_t *pFile, const char_t *pFunc, uint32 Line);
#define ASSERT_PARAM(Expression)     ((Expression) ? (void)0 : ReportParamError((char_t *)__FILE__, __func__, __LINE__))
#else
#define ASSERT_PARAM(Expression)     
#endif
/** @} */

#endif	// USE_DEPRECATED_DEFINITION

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMMON_Exported_Functions
 * @{
 */
/** @} */

/* Exported variables --------------------------------------------------------*/
/** @defgroup CMC_Exported_Variable
 * @{
 */
/** @} */

/** @} */
/* End of group COMMON */

/** @} */
/* End of group LX61_Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LX61_COMMON_H_ */

