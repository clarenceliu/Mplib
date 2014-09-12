/** 
 *******************************************************************************
 * @file    sw.h
 * @brief   SW functions prototypes for the TOSHIBA 'TMPM037' Device Series
 * @version V2.0.2.1
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SW_H
#define __SW_H

#include "TMPM037.h"
#include "tmpm037_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define SW0         0U
#define SW1         1U
#define SW2         2U
#define SW3         3U
#define SW4         4U
#define SW5         5U
#define SW6         6U
#define SW7         7U


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SW_Init(void);
uint8_t SW_Get(uint8_t SW);

#endif                          /* SW_H */
