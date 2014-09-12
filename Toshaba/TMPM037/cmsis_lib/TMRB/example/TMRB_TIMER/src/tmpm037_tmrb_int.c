/**
 *******************************************************************************
 * @file    tmpm037_tmrb_int.c
 * @brief   all interrupt request functions definition of TMRB_TIMER demo
 *          for the TOSHIBA 'tmpm037' Device Series 
 * @version V0.100
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "tmpm037_tmrb_int.h"
#include "led.h"
/**
  * @brief  TMRB0 interrupt service routine (1ms)
  * @param  None
  * @retval None
  */

void INTTMRB0_IRQHandler(void)
{
    static uint16_t tbcount = 0U;
    static uint8_t ledon = 1U;
    tbcount++;
    if (tbcount >= 500U) {
        tbcount = 0U;
        /* reverse LED output */
        ledon = (ledon == 0U) ? 1U : 0U;
        if (0U == ledon) {
            LED_Off(LED_ALL);
        } else {
            LED_On(LED_ALL);
        }
    } else {
        /* Do nothing */
    }
}

/*********************************** END OF FILE ******************************/
