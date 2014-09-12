/** 
 *******************************************************************************
 * @file    main.h
 * @brief   The application functions of UART FIFO demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
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
#include "tmpm36b_uart.h"
#include "tmpm36b_uart_int.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/

void delay(void);
#define GPIO_BIT_0                      ((uint8_t)0x01)
#define GPIO_BIT_1                      ((uint8_t)0x02)
#define GPIO_BIT_2                      ((uint8_t)0x04)
#define GPIO_BIT_3                      ((uint8_t)0x08)
#define GPIO_BIT_4                      ((uint8_t)0x10)
#define GPIO_BIT_5                      ((uint8_t)0x20)
#define GPIO_BIT_6                      ((uint8_t)0x40)


/* Private function prototypes -----------------------------------------------*/

#endif
