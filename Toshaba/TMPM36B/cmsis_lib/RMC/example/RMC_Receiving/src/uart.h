/** 
 *******************************************************************************
 * @file    uart.h
 * @brief   the header file of RMC_Receiving demo for the TOSHIBA
 *          'TMPM36B' Device Series
 * @version V0.201
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "RMC_Receiving.h"

/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE 16U
#define SET     0x01U           /* flag is set */
#define CLEAR   0x00U           /* flag is cleared */

/* external variables --------------------------------------------------------*/
extern char gSIOTxBuffer[BUFFER_SIZE];
extern uint8_t gSIORdIndex;
extern uint8_t gSIOWrIndex;
extern uint8_t fSIO_INT;

/* Exported functions ------------------------------------------------------- */
void SIO_Configuration(TSB_SC_TypeDef * SCx);
void SIO_ChInit(void);
uint8_t send_char(uint8_t ch);
#endif
