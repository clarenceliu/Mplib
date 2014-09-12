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


void delay(uint32_t DelayTime)
{
    uint32_t time;
    for (time = 0U; time < DelayTime; time++) {
    }
}
/* main function */
int DemoA(void)
{
    LED_Init();
    LED_On(LED2);
    delay(400000);

    while (1) {
        LED_On(LED0);
        delay(4000000);
        LED_Off(LED0);
        delay(4000000);
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
