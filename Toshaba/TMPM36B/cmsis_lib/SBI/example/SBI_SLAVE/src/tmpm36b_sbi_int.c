/**
 *******************************************************************************
 * @file    tmpm36b_sbi_int.c
 * @brief   The SBI ISR of SBI slave demo for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "tmpm36b_sbi_int.h"



/**
  * @brief  Interrupt Service Routine for SBI2
  * @param  None
  * @retval None
  */
void INTSBI2_IRQHandler(void)
{
    TSB_SBI_TypeDef *SBIx;
    SBI_I2CState sbi_sr;

    SBIx = TSB_SBI2;
    sbi_sr = SBI_GetI2CState(SBIx);

    if (sbi_sr.Bit.MasterSlave) {       /* Master mode */
        if (sbi_sr.Bit.TRx) {   /* Tx mode */
            if (sbi_sr.Bit.LastRxBit) { /* LRB=1: the receiver requires no further data. */
                SBI_GenerateI2CStop(SBIx);
            } else {            /* LRB=0: the receiver requires further data. */
                if (gI2CWCnt <= gI2CTxDataLen) {
                    SBI_SetSendData(SBIx, gI2CTxData[gI2CWCnt]);        /* Send next data */
                    gI2CWCnt++;
                } else {        /* I2C data send finished. */
                    SBI_GenerateI2CStop(SBIx);  /* Stop I2C */
                }
            }
        } else {                /* Rx Mode */
            /* Do nothing */
        }
    } else {                    /* Slave mode */
        /* Do nothing */
    }
}

/**
  * @brief  Interrupt Service Routine for SBI0
  * @param  None
  * @retval None
  */
void INTSBI0_IRQHandler(void)
{
    uint32_t tmp = 0U;
    TSB_SBI_TypeDef *SBIy;
    SBI_I2CState sbi0_sr;

    SBIy = TSB_SBI0;
    sbi0_sr = SBI_GetI2CState(SBIy);

    if (!sbi0_sr.Bit.MasterSlave) {     /* Slave mode */
        if (!sbi0_sr.Bit.TRx) { /* Rx Mode */
            if (sbi0_sr.Bit.SlaveAddrMatch) {
                /* First read is dummy read for Slave address recognize */
                tmp = SBI_GetReceiveData(SBIy);
                gI2CRCnt = 0U;
            } else {
                /* Read I2C received data and save to I2C_RxData buffer */
                tmp = SBI_GetReceiveData(SBIy);
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
