/** 
 *******************************************************************************
 * @file    common_uart.h
 * @brief   UART functions prototypes for the TOSHIBA 'TMPM037' Device Series
 * @version V2.0.2.1
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_UART_H
#define __COMMON_UART_H

#include "tmpm037_uart.h"


/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE 16U
#define SET     0x01U           /* flag is set */
#define CLEAR   0x00U           /* flag is cleared */
#define NO      0x00U           /* Send finish NG */
#define YES     0x01U           /* Send finish OK */
#define UART_RETARGET   UART0

/* external variables --------------------------------------------------------*/
extern char gSIOTxBuffer[];
extern uint8_t gSIORdIndex;
extern volatile uint8_t gSIOWrIndex;
extern volatile uint8_t fSIO_INT;
extern volatile uint8_t fSIOTxOK;

/* Exported functions ------------------------------------------------------- */
void SIO_Configuration(TSB_SC_TypeDef * SCx);
void SIO_ChInit(void);
void send_char(TSB_SC_TypeDef * USART, char ch);
void send_str(TSB_SC_TypeDef * USART, char *ch);


void common_uart_disp(char *pstr);
void hardware_init(TSB_SC_TypeDef * SCx);
void INTTX0_IRQHandler(void);

#endif
