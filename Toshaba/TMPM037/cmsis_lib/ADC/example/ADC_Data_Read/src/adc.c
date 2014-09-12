/**
 *******************************************************************************
 * @file    adc.c
 * @brief   The application functions of ADC_Data_Read demo for the
 *          TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

#define DEMO_TITLE "*************************\r\n M037 ADC Data Read Demo \r\n*************************\r\n"

#define INDEX_MAX 5000U
static uint32_t index = 0;
static char displaybuf[32];

/**
  * @brief  Initialize ADC register and variables
  * @param  None
  * @retval None
  */
void ADC_Init(void)
{
    /* set ADC clock */
    ADC_SetClk(ADC_CONVERSION_42_CLOCK, ADC_FC_DIVIDE_LEVEL_16);

    /* select ADC input channel */
    ADC_SetInputChannel(ADC_AN_0);

    /* Enable ADC repeat mode */
    ADC_SetRepeatMode(ENABLE);

    /* Set interrupt mode */
    ADC_SetINTMode(ADC_INT_CONVERSION_8);

    /* Turn VREF on */
    ADC_SetVref(ENABLE);

    /* Wait at least 3us to ensure the voltage is stable */
    Delay(10U);
}

/**
  * @brief  Send ADC Date value Time value to UART.
  * @param  None
  * @retval None
  */
void ADC_Display(void)
{
    ADC_ResultTypeDef ADC_Result = ADC_GetConvertResult(ADC_REG_0);

    if (++index == INDEX_MAX) {
        index = 0U;

        sprintf(displaybuf, "ADC Value: %4d\0", ADC_Result.ADCResultValue);
        common_uart_disp(DEMO_TITLE);   /* display title */
        common_uart_disp(displaybuf);   /* display ADC Value */
        common_uart_disp("\r\n");
    }
}

void Delay(int time)
{
    volatile int i = 0;

    for (i = 0; i < (time * 800); ++i);
}
