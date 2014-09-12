/**
 *******************************************************************************
 * @file    tmpm36b_int.c
 * @brief   all interrupt request functions definition of CG Demo
 *          for the TOSHIBA 'TMPM36B' Device Series
 * @version V0.100
 * @date    2014/06/26
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "CG_Idle.h"

/**
  * @brief  ExtINTSrc_IRQHandler
  * @param  None
  * @retval None
  */
void ExtINTSrc_IRQHandler(void)
{
    uint8_t ledval;
    CG_ClearINTReq(CG_ExtINTSrc);
    ledval = LED_EXT | LED_OTHER;
    LED_On(ledval);
    LED_Off(~ledval);
}
