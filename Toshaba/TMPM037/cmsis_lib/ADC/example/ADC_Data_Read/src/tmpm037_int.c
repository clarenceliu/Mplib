/**
 *******************************************************************************
 * @file    tmpm037_int.c
 * @brief   All interrupt request functions definition of ADC
 *          for the TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_int.h"

/* Private define ------------------------------------------------------------*/
uint8_t fIntADC = 0U;

/**
  * @brief  The ADC interrupt request function.
  * @param  None
  * @retval None
  */
void INTAD_IRQHandler(void)
{
    fIntADC = 1U;
}
