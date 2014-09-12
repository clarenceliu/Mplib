/**
 *******************************************************************************
 * @file    tmpm037_wdt_int.h
 * @brief   All interrupt request functions prototypes of WDT
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.102
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_WDT_INT_H
#define __TMPM037_WDT_INT_H

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tmpm037_wdt.h"
#include "tmpm037_cg.h"

#define FLG_WDT    ((uint8_t)0x00000001)
#define FLG_NMI    ((uint8_t)0x00000002)

void NMI_Handler(void);

#endif                          /* __TMPM037_WDT_INT_H */
