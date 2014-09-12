/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMRB_PPG demo for the TOSHIBA
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
#include "tmpm037_gpio.h"
#include "sw.h"

/* Private define ------------------------------------------------------------*/

#define TMRB0TIME       0x03E8U /* TMRB0 for PPG , Ttmrb = 0.5us, 500us/0.5us = 1000U = 0x03E8U */
#define LEADINGTIMINGMAX         0x05U  /* LEADINGTIMING RATE COUNTER MAX */
#define LEADINGTIMINGINIT        0U     /* LEADINGTIMING RATE COUNTER Initialize */

/* External function prototypes ----------------------------------------------*/
#endif
