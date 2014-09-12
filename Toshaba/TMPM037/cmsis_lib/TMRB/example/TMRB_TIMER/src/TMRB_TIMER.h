/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMRB_TIMER demo for the TOSHIBA
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
#include "tmpm037_tmrb.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/

#define TMRB_1MS        0x07D0U /* fsys = fc = fosc = 16MHz, fphiT0 = fperiph = fgear = fc */
                                 /* ftmrb = 1/8fphiT0 = 1/8 * 16 = 2MHz, Ttmrb = 0.5us, 1000us/0.5us = 2000U = 0x07D0U */

/* Private function prototypes -----------------------------------------------*/

/* External function prototypes ----------------------------------------------*/

#endif
