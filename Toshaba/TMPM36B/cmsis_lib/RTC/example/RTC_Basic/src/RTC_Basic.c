/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of RTC_Basic demo for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "RTC_Basic.h"

/**
  * @brief  main function.
  * @param  None
  * @retval None
  */

int RTC_Basic(void)
{
    CG_SetFs(ENABLE);
    hardware_init(UART_RETARGET);
    __disable_irq();
    /* enable RTC interrupt */
    NVIC_ClearPendingIRQ(INTRTC_IRQn);

    /* enable RTC interrupt */
    CG_SetSTBYReleaseINTSrc(CG_INT_SRC_RTC, CG_INT_ACTIVE_STATE_FALLING, ENABLE);
    RTC_Init();
    NVIC_EnableIRQ(INTRTC_IRQn);
    __enable_irq();

    /* waiting for RTC register set finish */
    while (fRTC_1HZ_INT != 1U) {
        /* Do nothing */
    }
    fRTC_1HZ_INT = 0U;

    /* Enable RTC Clock function */
    RTC_EnableClock();

    while (1) {
        if (fRTC_1HZ_INT == 1U) {
            fRTC_1HZ_INT = 0U;

            RTC_Display();
        } else {
            /* Do nothing */
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
