/**
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of OFD demo for the
 *          TOSHIBA 'TMPM36B' Device Series
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
#include "TMPM36B.h"
#include "tmpm36b_ofd.h"
#include "tmpm36b_cg.h"
#include "led.h"

#define OFD_LOWER_COUNT_16M           ((uint32_t)0x5FU) /* target clock is 16M */
#define OFD_HIGHER_COUNT_16M          ((uint32_t)0x6FU) /* target clock is 16M */

#define OFD_LOWER_COUNT_10M           ((uint32_t)0x3BU) /* target clock is 10M */
#define OFD_HIGHER_COUNT_10M          ((uint32_t)0x46U) /* target clock is 10M */

#define OFD_LOWER_COUNT_NORMAL        OFD_LOWER_COUNT_10M
#define OFD_HIGHER_COUNT_NORMAL       OFD_HIGHER_COUNT_10M
#define OFD_LOWER_COUNT_ABNORMAL      OFD_LOWER_COUNT_16M
#define OFD_HIGHER_COUNT_ABNORMAL     OFD_HIGHER_COUNT_16M

/* Watchdog Timer (WD) Configuration */
#define WD_SETUP    1U
#define WDMOD_Val   (0x00000000UL)
#define WDCR_Val    (0x000000B1UL)

void System_Init (void);
#endif                          /* __MAIN_H */
