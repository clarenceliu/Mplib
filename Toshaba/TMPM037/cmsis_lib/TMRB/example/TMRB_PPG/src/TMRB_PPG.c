/** 
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of TMRB_PPG demo for the TOSHIBA
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
#include "TMRB_PPG.h"
void delay(uint32_t time);
/**
  * @brief  The main function of TMRB_PPG demo
  * @param  None
  * @retval None
  */
int TMRB_PPG(void)
{
    uint8_t Rate = 0U;
    uint32_t LeadingTiming[5] = { 0x384U, 0x2EEU, 0x1F4U, 0xFAU, 0x64U };       /* LeadingTiming: 10%, 25%, 50%, 75%, 90% */
    uint8_t keyvalue = 0U;
    uint8_t changestatus = 0U;

    TMRB_InitTypeDef m_tmrb;
    TMRB_FFOutputTypeDef PPGFFInital;

    SW_Init();                  /* Init sw port to input */

    /* Set PC3 as TB0OUT for PPG output */
    GPIO_SetOutput(GPIO_PC, GPIO_BIT_3);
    GPIO_EnableFuncReg(GPIO_PC, GPIO_FUNC_REG_1, GPIO_BIT_3);

    m_tmrb.Mode = TMRB_INTERVAL_TIMER;  /* internal timer */
    m_tmrb.ClkDiv = TMRB_CLK_DIV_8;     /* 1/8PhiT0 */
    m_tmrb.UpCntCtrl = TMRB_AUTO_CLEAR; /* up-counter auto clear */
    m_tmrb.TrailingTiming = TMRB0TIME;  /* T = 500us */
    m_tmrb.LeadingTiming = LeadingTiming[Rate]; /* leadingtiming, initial value 10% */
    PPGFFInital.FlipflopCtrl = TMRB_FLIPFLOP_CLEAR;
    PPGFFInital.FlipflopReverseTrg =
        TMRB_FLIPFLOP_MATCH_TRAILINGTIMING | TMRB_FLIPFLOP_MATCH_LEADINGTIMING;

    TMRB_Enable(TSB_TB0);
    TMRB_Init(TSB_TB0, &m_tmrb);
    TMRB_SetFlipFlop(TSB_TB0, &PPGFFInital);
    TMRB_SetDoubleBuf(TSB_TB0, ENABLE); /* enable double buffer */
    TMRB_SetRunState(TSB_TB0, TMRB_RUN);

    while (1U) {
        /* change SW1 status to change the leadingtiming */
        keyvalue = SW_Get(SW1);
        if (keyvalue == 1U) {
            delay(0xFFFFU);     /* noise cancel */
            keyvalue = SW_Get(SW1);
            if (keyvalue == 0U) {
                changestatus = 1U;
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
        if (changestatus == 1U) {
            Rate++;             /* change leadingtiming rate */
            if (Rate >= LEADINGTIMINGMAX) {
                Rate = LEADINGTIMINGINIT;
            } else {
                /* Do nothing */
            }
            TMRB_ChangeLeadingTiming(TSB_TB0, LeadingTiming[Rate]);
            changestatus = 0U;
        } else {
            /* Do nothing */
        }
    }
}



/**
  * @brief  delay some time
  * @param  delay time
  * @retval None.
  */
void delay(uint32_t time)
{
    volatile uint32_t i;
    for (i = 0U; i < time; i++) {
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
