/** 
 *******************************************************************************
 * @file    tmpm36b_int.h
 * @brief   all interrupt request functions definition of RMC_Receiving 
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
#ifndef __SYSTEM_IT_H
#define __SYSTEM_IT_H

/* Includes ------------------------------------------------------------------*/
#include "RMC_Receiving.h"

/* external variables --------------------------------------------------------*/
#define BUFFER_SIZE 16U
extern char gSIOTxBuffer[BUFFER_SIZE];
extern uint8_t gSIORdIndex;
extern uint8_t gSIOWrIndex;
extern uint8_t fSIO_INT;

#ifdef RMC_3
extern IO_SFR32_u uRMCBuf_KA;
#endif

#ifdef RMC_4
extern uint8_t gRMC_4Address;
#endif

/* Private function prototypes -----------------------------------------------*/

void INTTX2_IRQHandler(void);
void INTRMCRX_IRQHandler(void);
void INTTB00_IRQHandler(void);

#endif                          /* __SYSTEM_IT_H */
