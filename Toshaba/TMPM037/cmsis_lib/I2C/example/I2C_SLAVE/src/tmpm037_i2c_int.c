/**
 *******************************************************************************
 * @file    tmpm037_i2c_int.c
 * @brief   The I2C ISR of I2C slave demo for the
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
    uint32_t tmp = 0U;
    I2C_State i2c0_sr;

    i2c0_sr = I2C_GetState();
    if (!i2c0_sr.Bit.MasterSlave) {     /* Slave mode */
        if (!i2c0_sr.Bit.TRx) { /* Rx Mode */
            if (i2c0_sr.Bit.SlaveAddrMatch) {
                /* First read is dummy read for Slave address recognize */
                tmp = I2C_GetReceiveData();
                gI2CRCnt = 0U;
            } else {
                /* Read I2C received data and save to I2C_RxData buffer */
                tmp = I2C_GetReceiveData();
                gI2CRxData[gI2CRCnt] = tmp;
                gI2CRCnt++;
            }
        } else {                /* Tx Mode */
            /* Do nothing */
        }
    } else {                    /* Master mode */
        /* Do nothing */
    }
}
