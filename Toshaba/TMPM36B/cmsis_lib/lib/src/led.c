/**
 ******************************************************************************
 * @file     led.c
 * @brief    LED driver for the TOSHIBA 'TMPM36B' Device Series
 * @version  V2.0.2.3
 * @date     2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 ******************************************************************************
 */

/** include files **/

#include "led.h"

/*************************************************************************
 * Function Name: LED_Init
 * Parameters:None
 *
 * Return:None  
 *
 * Description: Init LED ports
 *
 *************************************************************************/
void LED_Init(void)
{
    /*Set PB bit0~3 output and turn off all leds */
    GPIO_SetOutput(GPIO_PG, GPIO_BIT_0 | GPIO_BIT_1 | GPIO_BIT_2 | GPIO_BIT_3);
    GPIO_WriteDataBit(GPIO_PG, GPIO_BIT_0 | GPIO_BIT_1 | GPIO_BIT_2 | GPIO_BIT_3, GPIO_BIT_VALUE_0);
}

/*************************************************************************
 * Function Name: LED_On
 * Parameters:LED number, choose from LED0, LED1, LED2, LED3 or LED_ALL.
 *
 * Return:None  
 *
 * Description: The choosen Led is ON.
 *
 *************************************************************************/

void LED_On(uint8_t led)
{
    uint8_t tmp;
    tmp = GPIO_ReadData(GPIO_PG);
    tmp |= led;
    GPIO_WriteData(GPIO_PG, tmp);
}

/*************************************************************************
 * Function Name: LED_Off
 * Parameters:LED number, choose from LED0, LED1, LED2, LED3 or LED_ALL.
 *
 * Return:None  
 *
 * Description: The choosen Led is Off.
 *
 *************************************************************************/
void LED_Off(uint8_t led)
{
    uint8_t tmp;
    tmp = GPIO_ReadData(GPIO_PG);
    tmp &= (uint8_t) (~led);
    GPIO_WriteData(GPIO_PG, tmp);
}
