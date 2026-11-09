/***********************************************************************************************************************
 * File        : Drv8889.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD           <== HERE
 *                 - MCAL
 *                 - Common
 * Description : DRV8889-Q1 제어 (핀 / SPI 레지스터)
 ***********************************************************************************************************************/
#include "Drv8889.h"
#include "Drv8889_Tune.h"
#include "Dio.h"
#include "Spi.h"
#include "Tms.h"

/* [Drv8889.c 내부 전용] SPI 프레임 : B14 = 읽기(1) / 쓰기(0), B13~B8 = 주소 필드(DRV_xxx), B7~B0 = 데이터 */
#define DRV8889_FRAME_READ(Addr)        ((uint16)(0x4000U | ((uint16)(Addr) << 8)))
#define DRV8889_FRAME_WRITE(Addr, Data) ((uint16)(((uint16)(Addr) << 8) | (uint16)(Data)))

/* [Drv8889.c 내부 전용] 칩 타이밍 (기존 feature/Drv8889 값) */
#define DRV8889_SPI_GAP_US          (2U)                    /* 프레임 사이 대기                */
#define DRV8889_SPI_GAP_CLEAR_US    (10U)                   /* Fault Clear 후 대기             */
#define DRV8889_WAKEUP_MS           (1U)                    /* Wakeup 후 SPI 시작 전 대기      */

static uint16 Drv8889_Status = 0U;                          /* 마지막 SDO 응답 */

/* us 대기 (인터럽트 차단 없음) */
static void Drv8889_WaitUs(uint32 Us)
{
    uint32 Start = Tms_GetTickUs();

    while ((Tms_GetTickUs() - Start) < Us) { }
}

/* 1프레임 송수신 : nSCS Low → 16bit 송수신 → nSCS High → 프레임 간격 대기 */
static uint16 Drv8889_Transfer(uint16 TxFrame, uint32 GapUs)
{
    uint16 RxFrame;

    Dio_WriteChannel(DIO_CH_NSCS, STD_LOW);
    RxFrame = Spi_Transfer(TxFrame);
    Dio_WriteChannel(DIO_CH_NSCS, STD_HIGH);

    Drv8889_WaitUs(GapUs);

    Drv8889_Status = RxFrame;

    return RxFrame;
}

/* CTRL1~6 설정 쓰기. Wakeup 후 DRV8889_WAKEUP_MS 대기 뒤 시작 */
void Drv8889_Init(void)
{
    uint32 Start = Tms_GetTickMs();

    while ((Tms_GetTickMs() - Start) < DRV8889_WAKEUP_MS) { }

    (void)Drv8889_WriteReg(DRV_CTRL1, DRV8889_CTRL1);
    (void)Drv8889_WriteReg(DRV_CTRL2, DRV8889_CTRL2);
    (void)Drv8889_WriteReg(DRV_CTRL3, DRV8889_CTRL3);
    (void)Drv8889_WriteReg(DRV_CTRL4, DRV8889_CTRL4);
    (void)Drv8889_WriteReg(DRV_CTRL5, DRV8889_CTRL5);
    (void)Drv8889_WriteReg(DRV_CTRL6, DRV8889_CTRL6);
}

void Drv8889_Wakeup(void)
{
    Dio_WriteChannel(DIO_CH_DRVOFF,    STD_HIGH);
    Dio_WriteChannel(DIO_CH_DRV_SLEEP, STD_HIGH);
}

void Drv8889_Sleep(void)
{
    Dio_WriteChannel(DIO_CH_DRVOFF,    STD_HIGH);
    Dio_WriteChannel(DIO_CH_DRV_SLEEP, STD_LOW);
    Dio_WriteChannel(DIO_CH_DIR,       STD_LOW);
}

void Drv8889_Enable(void)
{
    Dio_WriteChannel(DIO_CH_DRVOFF, STD_LOW);
}

void Drv8889_Disable(void)
{
    Dio_WriteChannel(DIO_CH_DRVOFF, STD_HIGH);
}

void Drv8889_SetDirection(Drv8889_DirType Dir)
{
    Dio_WriteChannel(DIO_CH_DIR, (Dir == DRV8889_DIR_CW) ? STD_HIGH : STD_LOW);
}

uint16 Drv8889_ReadReg(uint8 Addr)
{
    return Drv8889_Transfer(DRV8889_FRAME_READ(Addr), DRV8889_SPI_GAP_US);
}

uint16 Drv8889_WriteReg(uint8 Addr, uint8 Data)
{
    return Drv8889_Transfer(DRV8889_FRAME_WRITE(Addr, Data), DRV8889_SPI_GAP_US);
}

void Drv8889_WriteCtrl1(Drv_TrqDac_t Trq, Drv_SlewRate_t Slew)
{
    (void)Drv8889_WriteReg(DRV_CTRL1, (uint8)((uint8)Trq | (uint8)Slew));
}

void Drv8889_WriteCtrl6(uint8 StallTh)
{
    (void)Drv8889_WriteReg(DRV_CTRL6, StallTh);
}

/* CTRL4 에 CLR_FLT 를 더해 쓰고(자동 해제), CTRL7(TRQ_COUNT) 을 읽어 상태 갱신 */
void Drv8889_FaultClear(void)
{
    (void)Drv8889_Transfer(DRV8889_FRAME_WRITE(DRV_CTRL4, (uint8)(DRV8889_CTRL4 | CLR_FLT_CLEAR)), DRV8889_SPI_GAP_CLEAR_US);
    (void)Drv8889_Transfer(DRV8889_FRAME_READ(DRV_CTRL7), DRV8889_SPI_GAP_CLEAR_US);
}

uint16 Drv8889_GetStatus(void)
{
    return Drv8889_Status;
}

boolean Drv8889_IsStallBitSet(void)
{
    return ((Drv8889_Status & DRV_STS_STL) != 0U) ? TRUE : FALSE;
}
