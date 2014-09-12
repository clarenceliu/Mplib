/**
 *******************************************************************************
 * @file    tmpm36b_uart_int.h
 * @brief   all interrupt request functions prototypes of UART FIFO Demo
 *          for the TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_UART_INT_H
#define __TMPM36B_UART_INT_H

/* Includes ------------------------------------------------------------------*/
#include "TMPM36b.h"
#include "tmpm36b_uart.h"


void INTTX0_IRQHandler(void);
void INTRX3_IRQHandler(void);

void INTRX0_IRQHandler(void);
void INTTX3_IRQHandler(void);
#endif                          /* __TMPM36B_UART_INT_H */
