/**
 *******************************************************************************
 * @file    tmpm037_i2c_int.c
 * @brief   The I2C ISR of I2C master demo for the
 *          TOSHIBA 'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "tmpm037_i2c_int.h"



/**
  * @brief  Interrupt Service Routine for I2C
  * @param  None
  * @retval None
  */
void INTI2C0_IRQHandler(void)
{
    I2C_State i2c_sr;
    i2c_sr = I2C_GetState();
    if (i2c_sr.Bit.MasterSlave) {       /* Master mode */
        if (i2c_sr.Bit.TRx) {   /* Tx mode */
            if (i2c_sr.Bit.LastRxBit) { /* LRB=1: the receiver requires no further data. */
                I2C_GenerateStop();
            } else {            /* LRB=0: the receiver requires further data. */
                if (gI2CWCnt <= gI2CTxDataLen) {
                    I2C_SetSendData(gI2CTxData[gI2CWCnt]);      /* Send next data */
                    gI2CWCnt++;
                } else {        /* I2C data send finished. */
                    I2C_GenerateStop(); /* Stop I2C */
                }
            }
        } else {                /* Rx Mode */
            /* Do nothing */
        }
    } else {                    /* master mode */
        /* Do nothing */
    }
}
