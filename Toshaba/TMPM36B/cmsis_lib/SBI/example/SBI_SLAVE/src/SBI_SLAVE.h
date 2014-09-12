/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file for main.c of SBI slave demo for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
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

#include "sw.h"
#include "common_uart.h"
#include "tmpm36b_gpio.h"
#include "tmpm36b_sbi.h"
#include "tmpm36b_uart.h"

#define SELF_ADDR                 ((uint8_t)0xE0)
#define SLAVE_ADDR                ((uint8_t)0xB0)
#define SBI_I2C_SEND             ((uint32_t)0x00000000)
#define SBI_I2C_RECEIVE          ((uint32_t)0x00000001)

#define MODE_SBI_I2C_IDLE        ((uint8_t)0x00)
#define MODE_SBI_I2C_INITIAL     ((uint8_t)0x10)
#define MODE_SBI_I2C_START       ((uint8_t)0x20)
#define MODE_SBI_I2C_TRX         ((uint8_t)0x21)
#define MODE_SBI_I2C_FINISHED    ((uint8_t)0x30)
#define MODE_SBI_I2C_CHECK       ((uint8_t)0x31)

extern uint32_t gI2CWCnt;
extern uint32_t gI2CRCnt;
extern uint32_t gI2CTxDataLen;
extern char gI2CTxData[16];
extern uint32_t gI2CRxDataLen;
extern char gI2CRxData[16];

void SBI2_IO_Configuration(void);
void SBI0_IO_Configuration(void);

#endif                          /* __MAIN_H */
