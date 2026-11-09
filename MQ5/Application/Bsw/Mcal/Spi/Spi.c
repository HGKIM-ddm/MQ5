/***********************************************************************************************************************
 * File        : Spi.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : SPI1 16bit 송수신 (Composer 함수 사용)
 ***********************************************************************************************************************/
#include "Spi.h"
#include "device_LX61101.h"

/*
 * Composer 함수 사용 : 이전 잔여 수신값 비우기 → 송신 → 수신
 *  - ReceiveDataSPI1() 은 수신 대기 중 LX61101_DelayUs(100) 을 호출하며, 이 동안 인터럽트가 100us 씩 막힌다.
 *  - 타임아웃(1s) 시 0xFFFF 를 반환하며, 정상 수신값 0xFFFF 와 구분되지 않는다.
 */
uint16 Spi_Transfer(uint16 TxData)
{
    FlushSPI1RX();
    SendDataSPI1(TxData);

    return (uint16)ReceiveDataSPI1();
}
