/** 
 *******************************************************************************
 * @file    tmpm037_uart_int.c
 * @brief   All interrupt request functions definition of UART_Retarget 
 *          for the TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_uart_int.h"

void INTTX0_IRQHandler(void)
{
    if (gSIORdIndex < gSIOWrIndex) {    /* buffer is not empty */
        UART_SetTxData(UART_RETARGET, gSIOTxBuffer[gSIORdIndex++]);     /* send data */
        fSIO_INT = SET;         /* SIO0 INT is enable */
    } else {
        /* disable SIO0 INT */
        fSIO_INT = CLEAR;
        NVIC_DisableIRQ(RETARGET_INT);
        fSIOTxOK = YES;
    }
    if (gSIORdIndex >= gSIOWrIndex) {   /* reset buffer index */
        gSIOWrIndex = CLEAR;
        gSIORdIndex = CLEAR;
    } else {
        /* Do nothing */
    }
}
