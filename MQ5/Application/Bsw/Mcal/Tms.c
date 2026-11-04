/***********************************************************************************************************************
 * File        : Tms.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 1ms 틱 카운트 (TMS01), 1us 틱 카운트 (TMS00)
 ***********************************************************************************************************************/
#include "Tms.h"
#include "device_LX61101.h"

static volatile uint32 Tms_1ms = 0U;            /* 인터럽트에서 증가 → volatile */
static uint32 Tms_1Us        = 0U;              /* 누적 us */
static uint32 Tms_Last50ns   = 0U;              /* 지난번 갱신 때의 TMS00 카운트 */
static uint32 Tms_Remain50ns = 0U;              /* 1us 가 안 된 나머지 */

// 인터럽트에서 1ms 마다 호출
void USER_TMS01_Handler(void)
{
    Tms_1ms++;
}

uint32 Tms_GetTickMs(void)
{
    return Tms_1ms;                           
}

// Tms00 은 50ns 단위로 감소 카운트 되므로(감소 타이머), 1us 단위로 변환하여 반환(+오버플로우 처리)
uint32 Tms_GetTickUs(void)
{
    uint32 Primask = __get_PRIMASK();
    uint32 Now50ns;

    __disable_irq();                               /* 메인/인터럽트 동시 호출 보호 */

    Now50ns         = 0xFFFFFFFFU - TMS00->VALUEA; /* 감소 → 증가 값으로 변환 */
    Tms_Remain50ns  += Now50ns - Tms_Last50ns;     /* 지난번 이후 증가분 (오버플로우 처리) */
    Tms_Last50ns    = Now50ns;
    Tms_1Us         += Tms_Remain50ns / 20U;       /* 20 x 50ns = 1us */
    Tms_Remain50ns  = Tms_Remain50ns % 20U;

    __set_PRIMASK(Primask);

    return Tms_1Us;
}

/* 1us 갱신 */
void USER_TMS00_Handler(void)
{
    (void)Tms_GetTickUs();
}





