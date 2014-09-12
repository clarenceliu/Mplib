/**
 *******************************************************************************
 * @file    tmpm037_int.c
 * @brief   all interrupt request functions definition of CG Demo
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/06/28
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
    CG_ClearINTReq(CG_ExtINTSrc);
}
