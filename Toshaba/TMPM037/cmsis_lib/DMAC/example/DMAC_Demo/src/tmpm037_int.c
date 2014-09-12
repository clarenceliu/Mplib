/**
 *******************************************************************************
 * @file    tmpm037_dmac_int.c
 * @brief   All interrupt request functions definition of DMA
 *           for the TOSHIBA 'TMPM366' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_int.h"

volatile WorkState TxEndFlag = BUSY;

/**
  * @brief  DMA transfer end interrupt request function.
  * @param  None
  * @retval None
  */
void INTDMAC_IRQHandler(void)
{
    DMAC_TxINTReq tmp = DMAC_TX_NO_REQ;
    DMAC_INTReq state;
    TxEndFlag = BUSY;

    state = DMAC_GetINTReq();

    if (state.Bit.CH1_INTReq == 1U) {
        tmp = DMAC_GetTxINTReq(DMAC_CHANNEL_1);
        if (tmp == DMAC_TX_END_REQ) {
            TxEndFlag = DMAC_GetChannelTxState(DMAC_CHANNEL_1);
            DMAC_ClearTxINTReq(DMAC_CHANNEL_1, DMAC_INT_TX_END);
        } else {
            /* Do nothing */
        }
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  Interrupt Service Routine for SIO1 Reception
  * @param  None
  * @retval None
  */
void INTRX1_IRQHandler(void)
{
    volatile UART_Err err;
    err = UART_GetErrState(UART1);
    if (UART_NO_ERR == err) {
        UART_Rx_Buffer[UART_Rx_Cnt] = (uint8_t) UART_GetRxData(UART1);
        UART_Rx_Cnt++;
    } else {
        /* Do nothing */
    }
}
