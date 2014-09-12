/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the application functions of UART_Retarget demo for the TOSHIBA
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
#include "tmpm36b_gpio.h"
#include "tmpm36b_uart_int.h"
#include "sw.h"
#include "uart.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/

#define SW_PORT        SW0

#define SWRELEASE      0U       /* switch RELEASE */
#define UART_RETARGET   UART0
#define RETARGET_INT    INTTX0_IRQn

void delay(void);

/* Private function prototypes -----------------------------------------------*/

#endif
