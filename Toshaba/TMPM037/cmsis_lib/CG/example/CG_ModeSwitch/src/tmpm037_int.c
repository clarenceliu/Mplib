/**
 *******************************************************************************
 * @file    tmpm037_int.c
 * @brief   all interrupt request functions definition of CG_ModeSwitch 
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_int.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  INT0_IRQHandler
  * @param  None
  * @retval None
  */
void INT0_IRQHandler(void)
{
    CG_ClearINTReq(CG_INT_SRC_0);
}
