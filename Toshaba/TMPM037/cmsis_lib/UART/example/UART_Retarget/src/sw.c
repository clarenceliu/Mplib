/**
 ******************************************************************************
 * @file     sw.c
 * @brief    SW driver for the TOSHIBA 'TMPM037' Device Series
 * @version  V2.0.2.1
 * @date     2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "sw.h"

/*******************************************************************************
* Function Name  : SW_Init
* Description    : Initialize the GPIO to SW 
* Input          : None 
* Return         : None.
*******************************************************************************/
void SW_Init(void)
{
    GPIO_SetInput(GPIO_PA, GPIO_BIT_4 | GPIO_BIT_5 | GPIO_BIT_6);
    GPIO_SetInput(GPIO_PB, GPIO_BIT_5);
}

/*******************************************************************************
* Function Name  : SW_Get
* Description    : Get SW Value
* Input          : SW (choose from SW0 ~ SW7).
* Return         : SW value.
*******************************************************************************/
uint8_t SW_Get(uint8_t sw)
{
    uint8_t tmp = 0U;
    switch (sw) {
    case SW0:
    case SW4:
        if (GPIO_ReadDataBit(GPIO_PB, GPIO_BIT_5) == 1U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW1:
    case SW5:
        if (GPIO_ReadDataBit(GPIO_PA, GPIO_BIT_4) == 1U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW2:
    case SW6:
        if (GPIO_ReadDataBit(GPIO_PA, GPIO_BIT_5) == 1U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW3:
    case SW7:
        if (GPIO_ReadDataBit(GPIO_PA, GPIO_BIT_6) == 1U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    default:
        break;
    }
    return tmp;

}
