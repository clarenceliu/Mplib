/** 
 *******************************************************************************
 * @file    main.h
 * @brief   The header file of FUART_LoopBack demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.201
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
#include "tmpm36b_fuart.h"
#include "tmpm36b_gpio.h"
#include "led.h"
#include "sw.h"
#include "stdio.h"
#include "common_uart.h"

typedef enum {
    DIFF = 0U,
    SAME = 1U
} TestResult;

extern void Delay(uint32_t time);
void LED_TXDataDisplay(uint32_t dat);
TestResult Buffercompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len);
void FUART_GPIOConfig(void);
void FUART_ChInit(void);

#endif
