/**
 *******************************************************************************
 * @file  main.c
 * @brief the application functions of STOP2 demo for the TOSHIBA
 *      'TMPM36B' Device Series 
 * @version V0.100
 * @date  2014/06/26
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "CG_Stop2.h"

/**
  * @brief  The main function of demo
  * @param  None
  * @retval None
  */

int CG_Stop2(void)
{
    SW_Init();
    LED_Init();
    hardware_init(UART_RETARGET);

    GPIO_ExtIntSrc();

    /* after release standby mode */
    if (is_StanbyRelease()) {
        LED_On(LED2);
        CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, DISABLE);

        NVIC_EnableIRQ(ExtINTSrc_IRQn);

        CG_SetPortKeepInStop2Mode(DISABLE);
    } else {
        CG_ClearINTReq(CG_ExtINTSrc);
        NVIC_ClearPendingIRQ(ExtINTSrc_IRQn);
        NVIC_EnableIRQ(ExtINTSrc_IRQn);
    }
    LED_On(LED_EXT);
    while (1U) {
        if (SW_Get(CG_SW) == 1) {

            LED_Off(LED_ALL);   /* LED  is off before enter stop2 */
            common_uart_disp("STOP2 MODE\r\n");
            enter_STOP2();

        } else {
            LED_On(LED_SW);
            common_uart_disp("NORMAL MODE\r\n");
        }
    }
}

/**
  * @brief  Enter stop2 low power mode
  * @param  None
  * @retval None
  */
void enter_STOP2(void)
{
    CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, ENABLE);

    config_STOP2();

    __DSB();
    __WFI();
}

/**
  * @brief  Set GPIO of External interrupt source
  * @param  None
  * @retval None
  */
void GPIO_ExtIntSrc(void)
{
    GPIO_SetInput(GPIO_ExtINTSrc, Bit_ExtINTSrc);
    GPIO_EnableFuncReg(GPIO_ExtINTSrc, GPIO_FUNC_REG_1, Bit_ExtINTSrc);
}

/**
  * @brief  Check the reset factor
  * @param  None
  * @retval 0 or 1
  */

int is_StanbyRelease(void)
{
    volatile CG_ResetFlag tmp = CG_GetResetFlag();
    if ((tmp.Bit.ResetPin != 1) && (tmp.Bit.STOP2Reset == 1)) {
        return 1U;
    } else {
        return 0U;
    }
}

/**
  * @brief  Config the stop2 mode
  * @param  None
  * @retval None
  */
void config_STOP2(void)
{
    volatile WorkState st = BUSY;
    volatile uint32_t wuef = 0U;

    CG_SetSTBYMode(CG_STBY_MODE_STOP2); /* Set standby mode as Stop2 */

    TSB_CG->OSCCR &= PLLON_CLEAR;
    TSB_CG->PLLSEL &= PLLSEL_CLEAR;
    while (CG_GetFcSrc() != CG_FC_SRC_FOSC) {
    };                          /* Confirm */

    /* When IHOSC is disable, enable IHOSC */
    if (CG_GetFoscState(CG_FOSC_OSC_INT) == DISABLE) {
        /* Enable IHOSC */
        CG_SetFosc(CG_FOSC_OSC_INT, ENABLE);

        /* Wait until IHOSC become stable */
        CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_EXT_HIGH, OSCCR_WUPT_EXT);
        CG_StartWarmUp();
        wuef = TSB_CG->OSCCR & 0x00000002U;
        while (wuef) {          /* Warm-up */
            wuef = TSB_CG->OSCCR & 0x00000002U;
        }

        /* Set IHOSC as fosc */
        CG_SetFoscSrc(CG_FOSC_OSC_INT);

        /* Wait until fosc become IHOSC */
        while (CG_GetFoscSrc() != CG_FOSC_OSC_INT) {
        };
    }

    CG_SetPortKeepInStop2Mode(ENABLE);
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
