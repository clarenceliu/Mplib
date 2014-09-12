/**
 *******************************************************************************
 * @file    tmpm36b_enc_int.c
 * @brief   all interrupt request functions definition of ENC_Roller demo
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

#include "ENC_Roller.h"
extern uint8_t g_flag;
extern uint32_t enccount;

/**
  * @brief  ENC0 interrupt service routine
  * @param  None
  * @retval None
  */
void INTENC0_IRQHandler(void)
{
    if(g_flag == 1U){
        if(enccount < 30U){
            enccount++;
        } else {
            enccount = 10U;
        }
    } else {
        if(enccount > 10U){
            enccount--;
        } else {
            enccount = 30U;
        }
    }
}

/*********************************** END OF FILE ******************************/
