/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file for main.c of I2C master demo for the
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
#include "led.h"
#include "tmpm037_gpio.h"
#include "tmpm037_i2c.h"
#include "tmpm037_uart.h"

#define SELF_ADDR                 ((uint8_t)0xE0)
#define SLAVE_ADDR                ((uint8_t)0xB0)
#define I2C_SEND             ((uint32_t)0x00000000)

#define MODE_I2C_IDLE        ((uint8_t)0x00)
#define MODE_I2C_INITIAL     ((uint8_t)0x10)
#define MODE_I2C_START       ((uint8_t)0x20)
#define MODE_I2C_TRX         ((uint8_t)0x21)
#define I2C_TRX_FINISHED     ((uint8_t)0x30)
#define I2C_RCV_FINISHED     ((uint8_t)0x31)
#define MODE_I2C_CHECK       ((uint8_t)0x40)
#define MODE_I2C_ACK         ((uint8_t)0x41)
#define MODE_I2C_RCV_ACK     ((uint8_t)0x50)
#define MODE_I2C_CHECK_RCV   ((uint8_t)0x51)
#define MODE_I2C_MASTER_RECV_FINISHED  (((uint8_t)0x60))


#define I2CCR2_MASTER_RECV_START ((uint32_t)0x000000B0)

#define I2C_ACK              ((uint8_t)0x10)

extern uint32_t gI2CWCnt;
extern uint32_t gI2CTxDataLen;
extern char gI2CTxData[8];

void I2C_IO_Configuration(void);


#endif                          /* __MAIN_H */
