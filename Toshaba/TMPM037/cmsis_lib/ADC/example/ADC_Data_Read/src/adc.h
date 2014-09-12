/**
 *******************************************************************************
 * @file    adc.h
 * @brief   The application functions of ADC_Data_Read demo for the
 *          TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "ADC_Data_Read.h"

/* Private function prototypes -----------------------------------------------*/
void ADC_Init(void);
void ADC_Display(void);
void Delay(int time);

#endif                          /* __ADC_H */
