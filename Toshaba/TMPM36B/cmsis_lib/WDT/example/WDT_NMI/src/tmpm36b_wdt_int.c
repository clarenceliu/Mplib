/**
 *******************************************************************************
 * @file    tmpm36b_wdt_int.c
 * @brief   All interrupt request functions definition of WDT
 *          for the TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_wdt_int.h"
volatile uint8_t fIntNMI = 0U;

/**
  * @brief  The NMI interrupt request function.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    fIntNMI = 1U;
}
