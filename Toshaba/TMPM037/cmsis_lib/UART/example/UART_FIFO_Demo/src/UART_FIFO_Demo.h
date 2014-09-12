/** 
 *******************************************************************************
 * @file    main.h
 * @brief   The application functions of UART_FIFO_Demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "tmpm037_uart.h"
#include "tmpm037_uart_int.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/
#define SWRELEASE      0U       /* switch RELEASE */

void delay(void);
#define GPIO_BIT_0                      ((uint8_t)0x0001)
#define GPIO_BIT_1                      ((uint8_t)0x0002)
#define GPIO_BIT_2                      ((uint8_t)0x0004)
#define GPIO_BIT_3                      ((uint8_t)0x0008)
#define GPIO_BIT_4                      ((uint8_t)0x0010)
#define GPIO_BIT_5                      ((uint8_t)0x0020)
#define GPIO_BIT_6                      ((uint8_t)0x0040)
#define GPIO_BIT_7                      ((uint8_t)0x0080)


/* Private function prototypes -----------------------------------------------*/

#endif
