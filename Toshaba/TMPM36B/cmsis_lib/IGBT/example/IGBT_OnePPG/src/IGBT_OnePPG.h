/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file of IGBT One PPG for the TOSHIBA 'TMPM36B' 
 *          Device Series 
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

#include "tmpm36b_igbt.h"
#include "tmpm36b_gpio.h"
#include "led.h"

#ifdef TSB_M36BFY
/* fperiph = fc = 10MHz*8 = 80MHz, T0 = fperiph = 80MHz, figbt = T0/2 = 40MHz */
#define IGBT_PPG_PERIOD_50US    ((uint16_t)2000)
#elif defined (TSB_M36BF10 )
/* fperiph = fc = 10MHz*6 = 60MHz, T0 = fperiph = 60MHz, figbt = T0/2 = 30MHz */
#define IGBT_PPG_PERIOD_50US    ((uint16_t)1500)
#endif

void IGBT_IO_Configuration(TSB_MT_TypeDef * IGBTx, IGBT_InitTypeDef * InitTypeDef);

#endif                          /* __MAIN_H */
