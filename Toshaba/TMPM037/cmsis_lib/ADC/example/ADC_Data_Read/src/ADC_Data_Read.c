/**
 *******************************************************************************
 * @file    main.c
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
#include "ADC_Data_Read.h"

/**
  * @brief  main function.
  * @param  None
  * @retval None
  */
int ADC_Data_Read(void)
{
    hardware_init(UART_RETARGET);

    ADC_Init();                 /* Initialize the ADC module */
    ADC_Start();                /* Start ADC */
    NVIC_EnableIRQ(INTAD_IRQn); /* Enable ADC Interrupt */

    while (1) {
        if (fIntADC == 1U) {    /* Wait for Interrupt flag */
            fIntADC = 0U;
            ADC_Display();      /* Display ADC value on UART */
        }
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
