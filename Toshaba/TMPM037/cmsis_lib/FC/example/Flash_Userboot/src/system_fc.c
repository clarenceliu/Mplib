/**
 *******************************************************************************
 * @file    System_fc.c
 * @brief   System initial for Flash Demo
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "TMPM037.h"

/* Only use Internal OSC , not configure the External OSC */
/* Because FC demo cann't run under 100M clock */
void SystemInit(void)
{
    TSB_WD->MOD = 0U;
    if (!TSB_WD_MOD_WDTE) {
        TSB_WD->CR = 0xB1U;     /*Disable WDT */
    }
}
