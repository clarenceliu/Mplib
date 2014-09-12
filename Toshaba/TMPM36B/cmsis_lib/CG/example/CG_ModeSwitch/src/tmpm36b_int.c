/**
 *******************************************************************************
 * @file    tmpm36b_int.c
 * @brief   all interrupt request functions definition of CG_ModeSwitch 
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
#include "tmpm36b_int.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  INT9_IRQHandler
  * @param  None
  * @retval None
  */
void INT9_IRQHandler(void)
{
    CG_ClearINTReq(CG_INT_SRC_9);
}
