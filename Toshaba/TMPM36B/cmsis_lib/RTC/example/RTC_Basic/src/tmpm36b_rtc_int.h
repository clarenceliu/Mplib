/**
 *******************************************************************************
 * @file    tmpm36b_rtc_int.h
 * @brief   All interrupt request functions prototypes of RTC
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
#ifndef __TMPM36B_RTC_INT_H
#define __TMPM36B_RTC_INT_H

/* Includes ------------------------------------------------------------------*/
#include "RTC_Basic.h"

/* User ram declaration    */
extern uint8_t fRTC_1HZ_INT;

void INTRTC_IRQHandler(void);

#endif                          /* __TMPM36B_RTC_INT_H */
