/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of GPIO demo for the
 *          TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/19 
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* include file */
#include "GPIO_LED.h"
/*  Function declaration */

/* main function */
int GPIO_LED(void)
{
    LED_Init();
    SW_Init();
    for (;;) {
        if (SW_Get(SW0) || SW_Get(SW4)) {
            LED_On(LED0);
        } else {
            LED_Off(LED0);
        }
        if (SW_Get(SW1) || SW_Get(SW5)) {
            LED_On(LED1);
        } else {
            LED_Off(LED1);
        }
        if (SW_Get(SW2) || SW_Get(SW6)) {
            LED_On(LED2);
        } else {
            LED_Off(LED2);
        }
        if (SW_Get(SW3) || SW_Get(SW7)) {
            LED_On(LED3);
        } else {
            LED_Off(LED3);
        }
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
