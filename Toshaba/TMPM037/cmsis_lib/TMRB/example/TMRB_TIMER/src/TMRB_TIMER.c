/** 
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of TMRB_TIMER demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "TMRB_TIMER.h"
#include "led.h"
/**
  * @brief  The main function of TMRB_TIMER demo
  * @param  None
  * @retval None
  */
int TMRB_TIMER(void)
{
    TMRB_InitTypeDef m_tmrb;

    LED_Init();                 /* LED initialize */
    LED_Off(LED_ALL);

    m_tmrb.Mode = TMRB_INTERVAL_TIMER;
    m_tmrb.ClkDiv = TMRB_CLK_DIV_8;
    m_tmrb.TrailingTiming = TMRB_1MS;   /* periodic time is 1ms */
    m_tmrb.UpCntCtrl = TMRB_AUTO_CLEAR;
    m_tmrb.LeadingTiming = TMRB_1MS;    /* periodic time is 1ms */

    TMRB_Enable(TSB_TB0);
    TMRB_Init(TSB_TB0, &m_tmrb);
    TMRB_SetINTMask(TSB_TB0, TMRB_MASK_MATCH_LEADINGTIMING_INT);        /*leadingtiming is not used in TMRB_INTERVAL_TIMER mode */
    NVIC_EnableIRQ(INTTMRB0_IRQn);
    TMRB_SetRunState(TSB_TB0, TMRB_RUN);
    while (1U) {
        /* Do nothing */
    }
}

/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
