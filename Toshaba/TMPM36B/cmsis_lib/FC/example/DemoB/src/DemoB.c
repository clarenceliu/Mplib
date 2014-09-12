/**
 *******************************************************************************
 * @file    main.c
 * @brief   Example Demo for FC Demo
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "led.h"
void delay(uint32_t DelayTime);
/* main function */
int DemoB(void)
{
    LED_Init();
    LED_On(LED3);
    delay(400000);

    while (1) {
        LED_On(LED1);
        delay(10000000);
        LED_Off(LED1);
        delay(10000000);
    }
}

void delay(uint32_t DelayTime)
{
    uint32_t time;
    for (time = 0U; time < DelayTime; time++) {
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
