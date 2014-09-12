/**
 *******************************************************************************
 * @file    tmpm037_uart_int.c
 * @brief   All interrupt request functions definition of UART (Serial Channel)
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

extern const uint8_t NumToBeTx;
extern uint8_t TxBuffer[];
extern uint8_t RxBuffer[];
extern uint8_t TxCounter;
extern uint8_t RxCounter;

extern const uint8_t NumToBeTx1;
extern uint8_t TxBuffer1[];
extern uint8_t RxBuffer1[];
extern uint8_t TxCounter1;
extern uint8_t RxCounter1;

/**
  * @brief  The transmission interrupt request function of UART channel 0.
  * @param  None
  * @retval None
  */
void INTTX0_IRQHandler(void)
{
    volatile UART_Err err;

    if (TxCounter < NumToBeTx) {
        UART_SetTxData(UART0, TxBuffer[TxCounter++]);
    } else {
        err = UART_GetErrState(UART0);
    }
}


/**
  * @brief  The transmission interrupt request function of UART channel 3.
  * @param  None
  * @retval None
  */
void INTTX3_IRQHandler(void)
{
    volatile UART_Err err;

    if (TxCounter1 < NumToBeTx1) {
        UART_SetTxData(UART3, TxBuffer1[TxCounter1++]);
    } else {
        err = UART_GetErrState(UART3);
    }
}



/**
  * @brief  The reception interrupt request function of UART channel 0.
  * @param  None
  * @retval None
  */
void INTRX0_IRQHandler(void)
{
    volatile UART_Err err;

    err = UART_GetErrState(UART0);
    if (UART_NO_ERR == err) {
        RxBuffer[RxCounter++] = (uint8_t) UART_GetRxData(UART0);
    }
}

/**
  * @brief  The reception interrupt request function of UART channel 3.
  * @param  None
  * @retval None
  */
void INTRX3_IRQHandler(void)
{
    volatile UART_Err err;

    err = UART_GetErrState(UART3);
    if (UART_NO_ERR == err) {
        RxBuffer1[RxCounter1++] = (uint8_t) UART_GetRxData(UART3);
    }
}
