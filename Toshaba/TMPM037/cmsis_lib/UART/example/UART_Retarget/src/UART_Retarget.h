/** 
 *******************************************************************************
 * @file    main.h
 * @brief   The application functions of UART_Retarget demo for the TOSHIBA
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
#include "tmpm037_gpio.h"
#include "tmpm037_uart_int.h"
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
