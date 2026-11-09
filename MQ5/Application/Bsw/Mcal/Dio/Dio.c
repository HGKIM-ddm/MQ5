/***********************************************************************************************************************
 * File        : Dio.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 디지털 입출력 핀 읽기/쓰기
 ***********************************************************************************************************************/
#include "Dio.h"
#include "device_LX61101.h"     


void Dio_WriteChannel(Dio_ChannelType ID, Dio_LevelType Level)
{
    // Level 값이 STD_LOW 이면 0, 아니라면 1 로 변환
    uint32 BitValue = (Level == (Dio_LevelType)STD_LOW) ? 0U : 1U;

    /* PB_GPxxx : Composer 생성 레지스터 비트 1개를 변수처럼 쓰게 해 주는 매크로 */
    switch (ID)
    {
        case DIO_CH_DRVOFF:     PB_GPA00 = BitValue;    break;
        case DIO_CH_DRV_SLEEP:  PB_GPA03 = BitValue;    break;
        case DIO_CH_DIR:        PB_GPA05 = BitValue;    break;
        case DIO_CH_NSCS:       PB_GPB03 = BitValue;    break;
        default:                                        break;    /* DIO_CH_NFAULT : 입력 핀 */
    }
}

/*
 * 출력 채널 : ODR(현재 출력 중인 값)  /  입력 채널 : IDR(핀 전압 레벨)
 * PB_GPC00 은 Composer 가 입력 핀으로 생성해 IDR 을 가리킨다.
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ID)
{
    uint32 BitValue = 0U;

    switch (ID)
    {
        case DIO_CH_DRVOFF:     BitValue = PB_GPA00;    break;
        case DIO_CH_DRV_SLEEP:  BitValue = PB_GPA03;    break;
        case DIO_CH_DIR:        BitValue = PB_GPA05;    break;
        case DIO_CH_NSCS:       BitValue = PB_GPB03;    break;
        case DIO_CH_NFAULT:     BitValue = PB_GPC00;    break;
        default:                                        break;
    }

    return (BitValue == 0U) ? (Dio_LevelType)STD_LOW : (Dio_LevelType)STD_HIGH;
}

//토글 기능 : 현재 레벨이 STD_LOW 이면 STD_HIGH 로, 아니면 STD_LOW 로 바꾼다.   
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ID)
{
    Dio_LevelType NewLevel;
    NewLevel = (Dio_ReadChannel(ID) == (Dio_LevelType)STD_LOW) ? (Dio_LevelType)STD_HIGH
                                                                       : (Dio_LevelType)STD_LOW;

    Dio_WriteChannel(ID, NewLevel);

    return NewLevel;
}
