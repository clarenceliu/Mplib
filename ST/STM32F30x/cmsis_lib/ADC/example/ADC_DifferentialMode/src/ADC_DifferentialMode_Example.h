/**
  ******************************************************************************
  * @file    ADC/ADC_DifferentialMode/main.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-October-2012
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAINADC_DIFFERENTIALMODE_EXAMPLE_H
#define __MAINADC_DIFFERENTIALMODE_EXAMPLE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "stm32f30x_adc.h"
#include "stm32f30x.h"
#include "stm32303c_eval.h"
#include "stm32303c_eval_lcd.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Delay(__IO uint32_t nTime);
void Display_Init(void);
void Display(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/