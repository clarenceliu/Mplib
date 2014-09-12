/**
 *******************************************************************************
 * @file    tmpm037_dmac_int.h
 * @brief   All interrupt request functions prototypes of DMAC
 *           for the TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_INT_H
#define __TMPM037_INT_H

/* Includes ------------------------------------------------------------------*/
#include "DMAC_Demo.h"

#define BUFFER_SIZE  32U
/* external variables --------------------------------------------------------*/
extern uint8_t UART_Rx_Buffer[BUFFER_SIZE];
extern uint8_t UART_Rx_Cnt;
extern volatile WorkState TxEndFlag;

/* Private function prototypes -----------------------------------------------*/
void INTRX1_IRQHandler(void);
void INTDMAC_IRQHandler(void);

#endif                          /* __TMPM037_INT_H */
