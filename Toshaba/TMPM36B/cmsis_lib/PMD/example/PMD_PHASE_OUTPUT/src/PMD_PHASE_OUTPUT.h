/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of PMD_PHASE_OUTPUT demo for the TOSHIBA
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
#include "tmpm36b_gpio.h"
#include "tmpm36b_pmd.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/
#define DEAD_TIME        0x70U
#define EMG_PROTECTION   1U

/* Private function prototypes -----------------------------------------------*/
void PMD_PWM_Config(void);
void PMD_IO_Config(void);
void PMD_BackToNormal(void);
void Delay(uint32_t time);
/* External function prototypes ----------------------------------------------*/
#endif
