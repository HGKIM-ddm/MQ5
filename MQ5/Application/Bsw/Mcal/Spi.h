/***********************************************************************************************************************
 * File        : Spi.h
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : SPI1 인터페이스 (16bit 송수신)
 ***********************************************************************************************************************/
#ifndef SPI_H
#define SPI_H

#include "Std_Types.h"

uint16 Spi_Transfer(uint16 TxData);                /* 16bit 1워드 송신 후 수신값 반환 */

#endif /* SPI_H */
