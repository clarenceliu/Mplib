/** 
 *******************************************************************************
 * @file    timer.h
 * @brief   the application functions of RMC_Receiving demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.102
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "RMC_Receiving.h"

/* Private define ------------------------------------------------------------*/
#ifdef TSB_M36BFY
#define TMRB_1ms 0x2710U        /* fsys = fc = 10MHz * 8(PLL) = 80MHz, fphiT0 = fperiph = fgear = fc */
                                /* ftmrb = 1/8fphiT0 = 1/8 * 80 = 10MHz, Ttmrb = 1/10us, 1000us/£¨1/10£©us = 10000 = 0x2710 */
#elif defined (TSB_M36BF10 ) 
#define TMRB_1ms 0x1D4CU        /* fsys = fc = 10MHz * 6(PLL) = 60MHz, fphiT0 = fperiph = fgear = fc */
                                /* ftmrb = 1/8fphiT0 = 1/8 * 60 = 7.5MHz, Ttmrb = 1/7.5us, 1000us/£¨1/7.5£©us = 7500 = 0x1D4C */
#endif 
/* Private function prototypes -----------------------------------------------*/
void Timer_ChInit(TSB_TB_TypeDef * TBx);
#endif
