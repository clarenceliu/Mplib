/**
 *******************************************************************************
 * @file    tmpm36b_rtc_int.c
 * @brief   All interrupt request functions definition of RTC
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

#include "tmpm36b_rtc_int.h"

uint8_t fRTC_1HZ_INT = 0U;

/**
  * @brief  The RTC interrupt request function.
  * @param  None
  * @retval None
  */
void INTRTC_IRQHandler(void)
	{
    fRTC_1HZ_INT = 1U;
    /*clear RTC interrupt request */
    CG_ClearINTReq(CG_INT_SRC_RTC);
}
