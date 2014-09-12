/** 
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of TMR16A_TIMER demo for the TOSHIBA
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
#include "TMR16A_TIMER.h"

/**
  * @brief  The main function of TMR16A_TIMER demo
  * @param  None
  * @retval None
  */
int TMR16A_TIMER(void)
{

    LED_Init();                 /* LED initialize */
    LED_On(LED_ALL);            /* Turn on LED_ALL */

    TMR16A_SetRunState(TSB_T16A0, TMR16A_STOP); /* Counter stops */
    TMR16A_SetSrcClk(TSB_T16A0, TMR16A_SYSCK);  /* Set source clock to system clock */
    TMR16A_ChangeCycle(TSB_T16A0, TMR16A_1MS);  /* Set counter value to 1ms */

    NVIC_EnableIRQ(INTT16A0_IRQn);
    TMR16A_SetRunState(TSB_T16A0, TMR16A_RUN);

    while (1) {
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
    while (1) {
        __NOP();
    }
}
#endif
