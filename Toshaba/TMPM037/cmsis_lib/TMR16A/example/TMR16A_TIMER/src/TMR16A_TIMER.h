/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMR16A_TIMER demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/19
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
#include "tmpm037_tmr16a.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/
#define TMR16A_1MS        0x3E80U       /* fsys = fc = 16MHz, ftmrb = fperiph = fgear = fc */
                                 /* Ttmrb = 1/16us, 1000us*16us = 16000 = 0x3E80 */
/* Private function prototypes -----------------------------------------------*/

/* External function prototypes ----------------------------------------------*/

#endif
