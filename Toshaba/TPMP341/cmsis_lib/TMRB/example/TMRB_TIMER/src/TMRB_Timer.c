/** 
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of TMRB_TIMER demo for the TOSHIBA
 *          'TMPM341' Device Series 
 * @version V0.100
 * @date    2011/03/03
 * 
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 * 
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "tmpm341_tmrb.h"
#include "led.h"
#include "cg.h"

/* Private define ------------------------------------------------------------*/

#define TMRB_1MS        0x1388U /* fsys = fc = 10MHz * PLL = 40MHz, fphiT0 = fperiph = fgear = fc */
                                 /* ftmrb = 1/8fphiT0 = 1/8 * 40 = 5MHz, Ttmrb = 0.2us, 1000us/0.2us = 5000 = 0x1388 */
#define KEYRELEASE      0xf0U   /* KEYRELEASE */

void Tmrb_timer(void);

/**
  * @brief  The main function of TMRB_TIMER demo
  * @param  None
  * @retval None
  */


/*int main(void)*/

void Tmrb_timer(void)
{
    TMRB_InitTypeDef m_tmrb;

    CG_InitSystem();            /* CG_SetSystem */
    LEDInit();                  /* LED initialize */
    LedOff(LED0 | LED1 | LED2);
    LedOn(LED3);                /* Turn on LED3 */

    m_tmrb.Mode = TMRB_INTERVAL_TIMER;
    m_tmrb.ClkDiv = TMRB_CLK_DIV_8;
    m_tmrb.Cycle = TMRB_1MS;    /* periodic time is 1ms */
    m_tmrb.UpCntCtrl = TMRB_AUTO_CLEAR;
    m_tmrb.Duty = TMRB_1MS;     /* periodic time is 1ms */

    TMRB_Enable(TSB_TB0);
    TMRB_Init(TSB_TB0, &m_tmrb);
    NVIC_EnableIRQ(INTTB0_IRQn);
    TMRB_SetRunState(TSB_TB0, TMRB_RUN);

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
