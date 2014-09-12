/**
 *******************************************************************************
 * @file    tmpm36b_sio_int.c
 * @brief   interrupt request functions definition of SIO Demo 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "SIO_Demo.h"

/**
  * @brief  INTTX0 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
//void INTTX0_IRQHandler(void)
//{
//    fSIO0TxOK = 1U;
//}

/**
  * @brief  INTRX1 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTRX1_IRQHandler(void)
{
    SIO1_RxBuffer[gSIO1RdIndex++] = SIO_GetRxData(SIO1);
}

/**
  * @brief  INTTX1 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTTX1_IRQHandler(void)
{
    fSIO1TxOK = 1U;
}

/**
  * @brief  INTRX0 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTRX0_IRQHandler(void)
{
    SIO0_RxBuffer[gSIO0RdIndex++] = SIO_GetRxData(SIO0);
}
