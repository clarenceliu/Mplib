/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMRB_TIMER demo for the TOSHIBA
 *          'TMPM36B' Device Series 
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

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_tmrb.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint16_t Tmrb_Calculator(uint16_t Tmrb_Require_us, uint32_t ClkDiv);
/* External function prototypes ----------------------------------------------*/

#endif
