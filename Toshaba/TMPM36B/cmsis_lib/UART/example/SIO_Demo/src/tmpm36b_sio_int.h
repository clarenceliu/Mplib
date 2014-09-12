/** 
 *******************************************************************************
 * @file    tmpm36b_sio_int.h
 * @brief   the header file of SIO interrupt
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIOINT_H
#define __SIOINT_H
/* Includes ------------------------------------------------------------------*/

#include "tmpm36b_uart.h"
#include <stdio.h>


extern volatile uint8_t fSIO0TxOK;
extern volatile uint8_t fSIO1TxOK;
extern volatile uint8_t gSIO1RdIndex;
extern volatile uint8_t gSIO0RdIndex;
extern uint8_t SIO1_RxBuffer[];
extern uint8_t SIO0_RxBuffer[];

void INTTX0_IRQHandler(void);
void INTRX1_IRQHandler(void);
void INTTX1_IRQHandler(void);
void INTRX0_IRQHandler(void);
#endif
