/**
 *******************************************************************************
 * @file    tmpm037_uart_int.h
 * @brief   All interrupt request functions prototypes of UART (Serial Channel)
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_UART_INT_H
#define __TMPM037_UART_INT_H

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tmpm037_uart.h"


void INTTX0_IRQHandler(void);
void INTRX3_IRQHandler(void);

void INTRX0_IRQHandler(void);
void INTTX3_IRQHandler(void);
#endif                          /* __TMPM037_UART_INT_H */
