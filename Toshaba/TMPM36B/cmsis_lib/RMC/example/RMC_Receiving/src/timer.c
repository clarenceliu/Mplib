/** 
 *******************************************************************************
 * @file    timer.c
 * @brief   the application functions of RMC_Receiving demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.201
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/**
  * @brief  Initialize the timer.
  * @param  TMRB channel
  * @retval None
  */
void Timer_ChInit(TSB_TB_TypeDef * TBx)
{
    TMRB_InitTypeDef myTMRB;

    /* Initialize TIMER(TMRB) */
    myTMRB.Mode = TMRB_INTERVAL_TIMER;
    myTMRB.ClkDiv = TMRB_CLK_DIV_8;
    myTMRB.TrailingTiming = TMRB_1ms;    /* Specific value depends on system clock */
    myTMRB.UpCntCtrl = TMRB_AUTO_CLEAR;
    myTMRB.LeadingTiming = TMRB_1ms;     /* Specific value depends on system clock */

    TMRB_Enable(TBx);
    TMRB_Init(TBx, &myTMRB);
    TMRB_SetRunState(TBx, TMRB_STOP);
}
