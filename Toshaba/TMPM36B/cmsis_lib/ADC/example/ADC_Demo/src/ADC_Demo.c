/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of ADC demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */


/* This demo is to show ADC function with software trigger on M36B-EVAL board    */
/* The loop blinking speed of the 4 LEDs is adjusted by AD conversion result.    */

#include "tmpm36b_adc.h"
#include "led.h"

struct mySoftTimer {
    uint32_t flag_TimeUp;
    uint32_t time_Cnt;
} softT;

#define DELAYCONST  20000U

static void softTimer(void);
void INTAD_IRQHandler(void);

ADC_Result adResult = { 0U };

uint32_t timeUp = 0U;
uint32_t idx = 0U;
uint32_t cnt = 0U;
uint32_t fIntADC = 0U;


/**
  * @brief  The main function of ADC demo
  * @param  None
  * @retval None
  */
int ADC_Demo()
{
    /* Software reset ADC */
    ADC_SWReset(TSB_AD);

    /* Enable ADC clock supply */
    ADC_SetClkSupply(ENABLE);

    /* Set ADC clock */
    ADC_SetClk(TSB_AD, ADC_CONVERSION_CLK_80, ADC_FC_DIVIDE_LEVEL_8);

    /* Select ADC input channel : Channel 0 */
    ADC_SetInputChannel(TSB_AD, ADC_AN_00);

    /* Enable ADC repeat mode */
    ADC_SetRepeatMode(TSB_AD, ENABLE);

    /* Set interrupt mode */
    ADC_SetINTMode(TSB_AD, ADC_INT_CONVERSION_8);

    /* Turn VREF on */
    ADC_SetVref(TSB_AD, ENABLE);

    /* Wait at least 3us to ensure the voltage is stable */
    cnt = 100U;
    while (cnt) {
        cnt--;
    }

    /* Enable AD interrupt */
    NVIC_EnableIRQ(INTAD_IRQn);

    /* Start ADC */
    ADC_Start(TSB_AD);

    /* Initialize LEDs */
    LED_Init();

    softT.time_Cnt = DELAYCONST;
    while (1U) {

        if (fIntADC == 1U) {
            fIntADC = 0U;
            /* Read AD conversion result when it is finished */
            adResult = ADC_GetConvertResult(TSB_AD, ADC_REG_00);

            /* Get the real ADC result without other information */
            /* "/256" is to limit the range of AD value */
            timeUp = 16U - adResult.Bit.ADResult / 256U;

        } else {
            /* Do nothing */
        }

        softTimer();

        if (softT.flag_TimeUp) {
            softT.flag_TimeUp = 0U;
            cnt++;
            if (cnt >= timeUp) {
                cnt = 0U;
                idx++;
                if (idx == 1U) {
                    LED_On(LED0);
                } else if (idx == 2U) {
                    LED_On(LED1);
                    LED_Off(LED0);
                } else if (idx == 3U) {
                    LED_On(LED2);
                    LED_Off(LED1);
                } else if (idx == 4U) {
                    LED_On(LED3);
                    LED_Off(LED2);
                } else if (idx == 5U) {
                    idx = 0U;
                    LED_Off(LED3);
                } else {
                    /* Do nothing */
                }
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
    }
}

/**
  * @brief  Simulate a several mS timer. 
  * @param  None
  * @retval None
  */
static void softTimer(void)
{
    if (softT.time_Cnt == 0U) {
        softT.flag_TimeUp = 1U;
        softT.time_Cnt = DELAYCONST;
    } else {
        softT.time_Cnt--;
    }

}


/**
  * @brief  The ADC interrupt request function.
  * @param  None
  * @retval None
  */
void INTAD_IRQHandler(void)
{
    fIntADC = 1U;
}


#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
