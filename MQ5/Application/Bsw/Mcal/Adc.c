/***********************************************************************************************************************
 * File        : Adc.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : ADC0 채널별 변환값 읽기 (Composer 함수 사용)
 ***********************************************************************************************************************/
#include "Adc.h"
#include "device_LX61101.h"

/*
 *  - ReadADC0() 은 변환 완료(ADST=0)까지 타임아웃 없이 대기한다. ADC 이상 시 무한 대기 가능.
 */
uint16 Adc_GetValue(Adc_ChannelType ID)
{
    uint16 Value = 0U;

    StartADC0();

    switch (ID)
    {
        case ADC_CH_VBAT:   Value = (uint16)ReadADC0(1);    break;    /* ADC0 CH01 */
        default:                                            break;
    }

    return Value;
}
