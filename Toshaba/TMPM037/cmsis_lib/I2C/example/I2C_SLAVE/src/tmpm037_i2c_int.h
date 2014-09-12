/**
 *******************************************************************************
 * @file    tmpm037_i2c_int.h
 * @brief   The header file for I2C ISR of I2C slave demo for the
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
#ifndef __TMPM037_I2C_INT_H
#define __TMPM037_I2C_INT_H

#include "I2C_SLAVE.h"

void INTI2C0_IRQHandler(void);

#endif                          /* __TMPM037_I2C_INT_H */
