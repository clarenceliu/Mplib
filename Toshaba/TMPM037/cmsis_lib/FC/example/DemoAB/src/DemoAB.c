/**
 *******************************************************************************
 * @file    DemoA.c
 * @brief   Example Demo for Flash_Userboot Demo
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "led.h"
#define     LED_DEMO    LED0
void delay(void);

/* main function */
int DemoAB(void)
{
    /*LED initial */
    LED_Init();
    delay();

    while (1) {
        LED_On(LED_DEMO);
        delay();
        LED_Off(LED_DEMO);
        delay();
    }
}

void delay(void)
{
    uint32_t i = 0U;
    for (i = 0U; i < 0x1FFFFFU; i++) {
    }
}



#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
