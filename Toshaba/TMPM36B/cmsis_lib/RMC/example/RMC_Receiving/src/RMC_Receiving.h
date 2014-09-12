/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the application functions of RMC_Receiving demo for the TOSHIBA
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
#include "tmpm36b_tmrb.h"
#include "tmpm36b_uart.h"
#include "tmpm36b_rmc.h"
#include "tmpm36b_gpio.h"
#include "tmpm36b_cg.h"
#include "tmpm36b_wdt.h"
#include "tmpm36b_int.h"
#include "uart.h"
#include "timer.h"
#include "rmc.h"
#include <stdio.h>

/* external variables --------------------------------------------------------*/
extern uint8_t gSIORdIndex, gSIOWrIndex, fSIO_INT;
extern uint8_t fTMRB0_INT;
extern uint32_t gRMC_Command;
extern uint16_t gRMC_Address;
#ifdef RMC_4
extern uint8_t gRMC_4Address;
#endif

/* Private define ------------------------------------------------------------*/
#ifdef RMC_1
/************** FOR RMC_1 FORMAT ****************/
#define FORMAT      "RMC_1"     /* FORMAT name */
#endif

#ifdef RMC_2
/************** FOR RMC_2 FORMAT ****************/
#define FORMAT      "RMC_2"     /* FORMAT name */
#endif

#ifdef RMC_3
/************** FOR RMC_3 FORMAT ****************/
#define FORMAT      "RMC_3"     /* FORMAT name */
#endif

#ifdef RMC_4
/************** FOR RMC_4 FORMAT ****************/
#define FORMAT      "RMC_4"     /* FORMAT name */
#endif

#ifdef RMC_5
/************** FOR RMC_5 FORMAT ****************/
#define FORMAT      "RMC_5"     /* FORMAT name */
#endif

#ifdef RMC_6
/************** FOR RMC_6 FORMAT ****************/
#define FORMAT      "RMC_6"     /* FORMAT name */
#endif

/* Private function prototypes -----------------------------------------------*/
void PrintCode(char *ch, uint16_t addr, uint32_t cmd);
#endif
