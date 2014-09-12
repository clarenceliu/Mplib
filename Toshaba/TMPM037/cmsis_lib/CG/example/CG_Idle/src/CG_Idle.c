/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of CG IDLE demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/06/28
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "CG_Idle.h"

/**
  * @brief  The main function of demo
  * @param  None
  * @retval None
  */
int CG_Idle(void)
{
    SW_Init();
    LED_Init();
    hardware_init(UART_RETARGET);

    GPIO_ExtIntSrc();
    CG_ClearINTReq(CG_ExtINTSrc);
    NVIC_ClearPendingIRQ(ExtINTSrc_IRQn);

    NVIC_EnableIRQ(ExtINTSrc_IRQn);

    while (1U) {
        if (SW_Get(SW1) == 1U) {
            LED_On(LED_ALL);
            common_uart_disp("IDLE MODE\r\n");
            Delay(); /* Delay sometime to let UART print string. */
            enter_IDLE();

        } else {
            LED_Off(LED_ALL);
            common_uart_disp("NORMAL MODE\r\n");
        }
    }
}

/**
  * @brief  Enter the IDLE low power mode
  * @param  None
  * @retval None
  */
void enter_IDLE(void)
{

    CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, ENABLE);

    /* Set standby mode as IDLE */
    CG_SetSTBYMode(CG_STBY_MODE_IDLE);

    __DSB();
    __WFI();

    /* INT release */
    CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, DISABLE);
}

/**
  * @brief  Set GPIO of External interrupt source
  * @param  None
  * @retval None
  */
void GPIO_ExtIntSrc(void)
{
    GPIO_SetInput(GPIO_ExtINTSrc, Bit_ExtINTSrc);
}

/**
  * @brief  Delay sometime.
  * @param  None
  * @retval None
  */
void Delay(void)
{
    volatile uint32_t i = 0x0U; 
    for(i = 0xFFFU; i>0; i--);
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
