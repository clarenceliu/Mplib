/**
 *******************************************************************************
 * @file    main.h
 * @brief   the application functions of CG demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/06/28
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "tmpm037_gpio.h"
#include "tmpm037_cg.h"
#include "sw.h"
#include "led.h"
#include "common_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Set External interrupt pin's PORT/Bit, Interrupt Number */
#define     GPIO_ExtINTSrc          GPIO_PB
#define     Bit_ExtINTSrc           GPIO_BIT_5
#define     CG_ExtINTSrc            CG_INT_SRC_0
#define     ExtINTSrc_IRQn          INT0_IRQn
#define     ExtINTSrc_IRQHandler    INT0_IRQHandler

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_ExtIntSrc(void);
void enter_IDLE(void);
void Delay(void);

#endif
/*********************************** END OF FILE ******************************/
