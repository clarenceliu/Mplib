/**
 *******************************************************************************
 * @file    main.h
 * @brief   the application functions of CG demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.100
 * @date    2014/06/26
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_gpio.h"
#include "tmpm36b_cg.h"
#include "sw.h"
#include "led.h"
#include "common_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Set External interrupt pin's PORT/Bit, Interrupt Number */
#define     GPIO_ExtINTSrc          GPIO_PJ
#define     Bit_ExtINTSrc           GPIO_BIT_0
#define     CG_ExtINTSrc            CG_INT_SRC_9
#define     ExtINTSrc_IRQn          INT9_IRQn
#define     ExtINTSrc_IRQHandler    INT9_IRQHandler

#define     LED_EXT                 LED3
#define     LED_OTHER               LED0
#define     LED_SW                  LED2

#define     CG_SW                   SW1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_ExtIntSrc(void);
void enter_IDLE(void);

#endif
/*********************************** END OF FILE ******************************/
