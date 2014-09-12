/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file for main.c of I2C slave demo for the
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
#ifndef __MAIN_H
#define __MAIN_H

#include "sw.h"
#include "common_uart.h"
#include "tmpm037_gpio.h"
#include "tmpm037_i2c.h"
#include "tmpm037_uart.h"

#define SELF_ADDR                 ((uint8_t)0xE0)
#define SLAVE_ADDR                ((uint8_t)0xB0)
#define I2C_SEND             ((uint32_t)0x00000000)
#define I2C_RECEIVE          ((uint32_t)0x00000001)

#define MODE_I2C_IDLE        ((uint8_t)0x00)
#define MODE_I2C_INITIAL     ((uint8_t)0x10)
#define MODE_I2C_START       ((uint8_t)0x20)
#define MODE_I2C_TRX         ((uint8_t)0x21)
#define MODE_I2C_FINISHED    ((uint8_t)0x30)
#define MODE_I2C_CHECK       ((uint8_t)0x31)
#define MODE_I2C_RCV         ((uint8_t)0x40)


volatile extern uint32_t gI2CRCnt;
extern char gI2CRxData[8];
extern uint32_t uSlaveAddr;

void I2C_IO_Configuration(void);

#endif                          /* __MAIN_H */
