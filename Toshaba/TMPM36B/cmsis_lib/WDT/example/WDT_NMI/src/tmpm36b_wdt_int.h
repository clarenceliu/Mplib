/**
 *******************************************************************************
 * @file    tmpm36b_wdt_int.h
 * @brief   All interrupt request functions prototypes of WDT
 *          for the TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_WDT_INT_H
#define __TMPM36B_WDT_INT_H

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tmpm36b_wdt.h"
#include "tmpm36b_cg.h"
/* #include "led.h" */


#define FLG_WDT    ((uint8_t)0x00000001)
#define FLG_NMI    ((uint8_t)0x00000002)

void NMI_Handler(void);

#endif                          /* __TMPM36B_WDT_INT_H */
