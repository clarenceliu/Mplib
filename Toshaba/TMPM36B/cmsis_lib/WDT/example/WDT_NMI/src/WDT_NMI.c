/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of WDT demo for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "tmpm36b_wdt.h"
#include "tmpm36b_gpio.h"
#include "led.h"
#define  DEMO2
extern volatile uint8_t fIntNMI;

void Delay(uint32_t time);

/*******************************************************************************
* Function Name  : main
* Description    : main function
* Input          : None.
* Return         : None.
*******************************************************************************/
int WDT_NMI(void)
{
    WDT_InitTypeDef WDT_InitStruct;
    WDT_InitStruct.DetectTime = WDT_DETECT_TIME_EXP_25;
    WDT_InitStruct.OverflowOutput = WDT_NMIINT;

    LED_Init();

    WDT_Init(&WDT_InitStruct);
    WDT_Enable();

    while (1U) {
        if (fIntNMI == 1U) {
            fIntNMI = 0U;
            WDT_Disable();
            LED_On(LED1);
            Delay(6500U);
            LED_Off(LED1);
            Delay(500U);

        } else {
            /* Do nothing */
        }

#ifdef DEMO2
        Delay(3500U);
        WDT_WriteClearCode();
        LED_On(LED0);
        Delay(3500U);
        LED_Off(LED0);
#endif
    }

}


/*******************************************************************************
* Function Name  : Delay
* Description    : delay time
* Input          : time.
* Return         : None.
*******************************************************************************/
void Delay(uint32_t time)
{
    volatile uint32_t TimeCounter = 0U;
    uint32_t DelayTime = 0U;

    DelayTime = time * 800U;
    for (TimeCounter = 0U; TimeCounter < DelayTime; TimeCounter++) {
        /* Do nothing */
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
