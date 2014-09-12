/**
 *******************************************************************************
 * @file    tmpm037_int.h
 * @brief   All interrupt request functions prototypes of ADC
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_INT_H
#define __TMPM037_INT_H

/* Includes ------------------------------------------------------------------*/
#include "ADC_Data_Read.h"

/* external variables --------------------------------------------------------*/
extern uint8_t fIntADC;

/* Private function prototypes -----------------------------------------------*/
void INTAD_IRQHandler(void);

#endif                          /* __TMPM037_INT_H */
