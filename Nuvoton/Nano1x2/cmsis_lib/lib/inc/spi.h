/****************************************************************************//**
 * @file     spi.h
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 14/01/15 3:42p $
 * @brief    NANO1X2 series SPI driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NANO1X2_Device_Driver NANO1X2 Device Driver
  @{
*/

/** @addtogroup NANO1X2_SPI_Driver SPI Driver
  @{
*/


/** @addtogroup NANO1X2_SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/

#define SPI_MODE_0        (SPI_CTL_TX_NEG_Msk)                            /*!< CLKP=0; RX_NEG=0; TX_NEG=1 */
#define SPI_MODE_1        (SPI_CTL_RX_NEG_Msk)                            /*!< CLKP=0; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_2        (SPI_CTL_CLKP_Msk | SPI_CTL_RX_NEG_Msk)         /*!< CLKP=1; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_3        (SPI_CTL_CLKP_Msk | SPI_CTL_TX_NEG_Msk)         /*!< CLKP=1; RX_NEG=0; TX_NEG=1 */

#define SPI_SLAVE        (SPI_CTL_SLAVE_Msk)                              /*!< Set as slave */
#define SPI_MASTER        (0x0)                                           /*!< Set as master */

#define SPI_SS0                (0x1)                                      /*!< Set SS0 */
#define SPI_SS0_ACTIVE_HIGH    (SPI_SSR_SS_LVL_Msk)                       /*!< SS0 active high */
#define SPI_SS0_ACTIVE_LOW     (0x0)                                      /*!< SS0 active low */

#define SPI_SS1                (0x2)                                      /*!< Set SS1 */
#define SPI_SS1_ACTIVE_HIGH    (SPI_SSR_SS_LVL_Msk)                       /*!< SS1 active high */
#define SPI_SS1_ACTIVE_LOW     (0x0)                                      /*!< SS1 active low */

#define SPI_IE_MASK                        (0x01)                         /*!< Interrupt enable mask */
#define SPI_SSTA_INTEN_MASK                (0x04)                         /*!< Slave 3-Wire mode start interrupt enable mask */
#define SPI_FIFO_TX_INTEN_MASK             (0x08)                         /*!< FIFO TX interrupt mask */
#define SPI_FIFO_RX_INTEN_MASK             (0x10)                         /*!< FIFO RX interrupt mask */
#define SPI_FIFO_RXOV_INTEN_MASK           (0x20)                         /*!< FIFO RX overrun interrupt mask */
#define SPI_FIFO_TIMEOUT_INTEN_MASK        (0x40)                         /*!< FIFO timeout interrupt mask */


/*@}*/ /* end of group NANO1X2_SPI_EXPORTED_CONSTANTS */


/** @addtogroup NANO1X2_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief  Abort the current transfer in slave 3-wire mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ABORT_3WIRE_TRANSFER(spi) ( (spi)->SSR |= SPI_SSR_SLV_ABORT_Msk )

/**
  * @brief  Clear the slave 3-wire mode start interrupt flag.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_CLR_3WIRE_START_INT_FLAG(spi)  ( (spi)->STATUS |= SPI_STATUS_SLV_START_INTSTS_Msk )

/**
  * @brief  Clear the unit transfer interrupt flag.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_CLR_UNIT_TRANS_INT_FLAG(spi) ( (spi)->STATUS |= SPI_STATUS_INTSTS_Msk )

/**
  * @brief  Disable slave 3-wire mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_DISABLE_3WIRE_MODE(spi) ( (spi)->SSR &= ~SPI_SSR_NOSLVSEL_Msk )

/**
  * @brief  Enable slave 3-wire mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_3WIRE_MODE(spi) ( (spi)->SSR |= SPI_SSR_NOSLVSEL_Msk )

/**
  * @brief  Get the count of available data in RX FIFO.
  * @param  spi is the base address of SPI module.
  * @return The count of available data in RX FIFO.
  */
#define SPI_GET_RX_FIFO_COUNT(spi) ( (((spi)->STATUS & SPI_STATUS_RX_FIFO_CNT_Msk) >> SPI_STATUS_RX_FIFO_CNT_Pos) & 0xf )

/**
  * @brief  Get the Rx FIFO empty flag.
  * @param  spi is the base address of SPI module.
  * @return Rx FIFO flag
  * @retval 0 Rx FIFO is not empty
  * @retval 1 Rx FIFO is empty
  */
#define SPI_GET_RX_FIFO_EMPTY_FLAG(spi) ( ((spi)->STATUS & SPI_STATUS_RX_EMPTY_Msk) == SPI_STATUS_RX_EMPTY_Msk ? 1:0)

/**
  * @brief  Get the Tx FIFO empty flag.
  * @param  spi is the base address of SPI module.
  * @return Tx FIFO flag
  * @retval 0 Tx FIFO is not empty
  * @retval 1 Tx FIFO is empty
  */
#define SPI_GET_TX_FIFO_EMPTY_FLAG(spi) ( ((spi)->STATUS & SPI_STATUS_TX_EMPTY_Msk) == SPI_STATUS_TX_EMPTY_Msk ? 1:0)

/**
  * @brief  Get the Tx FIFO full flag.
  * @param  spi is the base address of SPI module.
  * @return Tx FIFO flag
  * @retval 0: Tx FIFO is not full
  * @retval 1: Tx FIFO is full
  */
#define SPI_GET_TX_FIFO_FULL_FLAG(spi) ( ((spi)->STATUS & SPI_STATUS_TX_FULL_Msk) == SPI_STATUS_TX_FULL_Msk ? 1:0)

/**
  * @brief  Get the datum read from RX0 FIFO.
  * @param  spi is the base address of SPI module.
  * @return Data in Rx0 register.
  */
#define SPI_READ_RX0(spi) ((spi)->RX0)

/**
  * @brief  Get the datum read from RX1 FIFO.
  * @param  spi is the base address of SPI module.
  * @return Data in Rx1 register.
  */
#define SPI_READ_RX1(spi) ((spi)->RX1)

/**
  * @brief  Write datum to TX0 register.
  * @param  spi is the base address of SPI module.
  * @param  u32TxData is the datum which user attempt to transfer through SPI bus.
  * @return none
  */
#define SPI_WRITE_TX0(spi, u32TxData)  ( (spi)->TX0 = u32TxData )

/**
  * @brief  Write datum to TX1 register.
  * @param  spi is the base address of SPI module.
  * @param  u32TxData is the datum which user attempt to transfer through SPI bus.
  * @return none
  */
#define SPI_WRITE_TX1(spi, u32TxData)  ( (spi)->TX1 = u32TxData )

/**
  * @brief  Disable automatic slave select function and set SPI_SS pin to high state.
  * @param  spi is the base address of SPI module.
  * @return none
  */
static __INLINE void SPI_SET_SS0_HIGH(SPI_T *spi)
{
    spi->SSR &= ~SPI_SSR_AUTOSS_Msk;
    spi->STATUS |= SPI_STATUS_LTRIG_FLAG_Msk;
    spi->SSR |= SPI_SSR_SS_LVL_Msk;
    spi->SSR = (spi->SSR & ~SPI_SSR_SSR_Msk) | 0x1;
}

/**
  * @brief  Disable automatic slave select function and set SPI_SS pin to low state.
  * @param  spi is the base address of SPI module.
  * @return none
  */
static __INLINE void SPI_SET_SS0_LOW(SPI_T *spi)
{
    spi->SSR &= ~SPI_SSR_AUTOSS_Msk;
    spi->STATUS |= SPI_STATUS_LTRIG_FLAG_Msk;
    spi->SSR &= ~SPI_SSR_SS_LVL_Msk;
    spi->SSR = (spi->SSR & ~SPI_SSR_SSR_Msk) | 0x1;
}

/**
  * @brief  Disable automatic slave select function and set SPI_SS pin to high state.
  * @param  spi is the base address of SPI module.
  * @return none
  */
static __INLINE void SPI_SET_SS1_HIGH(SPI_T *spi)
{
    spi->SSR &= ~SPI_SSR_AUTOSS_Msk;
    spi->STATUS |= SPI_STATUS_LTRIG_FLAG_Msk;
    spi->SSR |= SPI_SSR_SS_LVL_Msk;
    spi->SSR = (spi->SSR & ~SPI_SSR_SSR_Msk) | 0x2;
}

/**
  * @brief  Disable automatic slave select function and set SPI_SS pin to low state.
  * @param  spi is the base address of SPI module.
  * @return none
  */
static __INLINE void SPI_SET_SS1_LOW(SPI_T *spi)
{
    spi->SSR &= ~SPI_SSR_AUTOSS_Msk;
    spi->STATUS |= SPI_STATUS_LTRIG_FLAG_Msk;
    spi->SSR |= SPI_SSR_SS_LVL_Msk;
    spi->SSR = (spi->SSR & ~SPI_SSR_SSR_Msk) | 0x2;
}

/**
  * @brief Enable byte reorder function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_BYTE_REORDER(spi) ( (spi)->CTL |= SPI_CTL_REORDER_Msk )

/**
  * @brief  Disable byte reorder function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_DISABLE_BYTE_REORDER(spi) ( (spi)->CTL &= ~SPI_CTL_REORDER_Msk )

/**
  * @brief  Set the length of suspend interval.
  * @param  spi is the base address of SPI module.
  * @param  u32SuspCycle decides the length of suspend interval.
  * @return none
  */
#define SPI_SET_SUSPEND_CYCLE(spi, u32SuspCycle) ( (spi)->CTL = ((spi)->CTL & ~SPI_CTL_SP_CYCLE_Msk) | (u32SuspCycle << SPI_CTL_SP_CYCLE_Pos) )

/**
  * @brief  Set the SPI transfer sequence with LSB first.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_SET_LSB_FIRST(spi) ( (spi)->CTL |= SPI_CTL_LSB_Msk )

/**
  * @brief  Set the SPI transfer sequence with MSB first.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_SET_MSB_FIRST(spi) ( (spi)->CTL &= ~SPI_CTL_LSB_Msk )

/**
  * @brief  Set the data width of a SPI transaction.
  * @param  spi is the base address of SPI module.
  * @param  u32Width is the data width (from 8-32 bits).
  * @return none
  */
static __INLINE void SPI_SET_DATA_WIDTH(SPI_T *spi, uint32_t u32Width)
{
    if(u32Width == 32)
        u32Width = 0;

    spi->CTL = (spi->CTL & ~SPI_CTL_TX_BIT_LEN_Msk) | (u32Width << SPI_CTL_TX_BIT_LEN_Pos);
}

/**
  * @brief  Get the SPI busy state.
  * @param  spi is the base address of SPI module.
  * @return SPI busy status
  * @retval 0 SPI module is not busy
  * @retval 1 SPI module is busy
  */
#define SPI_IS_BUSY(spi) ( ((spi)->CTL & SPI_CTL_GO_BUSY_Msk) == SPI_CTL_GO_BUSY_Msk ? 1:0 )

/**
  * @brief  Set the GO_BUSY bit to trigger SPI transfer.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_TRIGGER(spi) ( (spi)->CTL |= SPI_CTL_GO_BUSY_Msk )

/**
  * @brief  Enable SPI Dual IO function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_DUAL_MODE(spi) ( (spi)->CTL |= SPI_CTL_DUAL_IO_EN_Msk )

/**
  * @brief  Disable SPI Dual IO function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_DISABLE_DUAL_MODE(spi) ( (spi)->CTL &= ~SPI_CTL_DUAL_IO_EN_Msk )

/**
  * @brief  Set SPI Dual IO direction to input.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_DUAL_INPUT_MODE(spi) ( (spi)->CTL &= ~SPI_CTL_DUAL_IO_DIR_Msk )

/**
  * @brief  Set SPI Dual IO direction to output.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_DUAL_OUTPUT_MODE(spi) (  (spi)->CTL |= SPI_CTL_DUAL_IO_DIR_Msk )

/**
  * @brief  Trigger RX PDMA transfer.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_TRIGGER_RX_PDMA(spi) ( (spi)->DMA |= SPI_DMA_RX_DMA_EN_Msk )

/**
  * @brief  Trigger TX PDMA transfer.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_TRIGGER_TX_PDMA(spi) ( (spi)->DMA |= SPI_DMA_TX_DMA_EN_Msk )

/**
  * @brief  Enable 2-bit transfer mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_ENABLE_2BIT_MODE(spi) ( (spi)->CTL |= SPI_CTL_TWOB_Msk )

/**
  * @brief  Disable 2-bit transfer mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
#define SPI_DISABLE_2BIT_MODE(spi) ( (spi)->CTL &= ~SPI_CTL_TWOB_Msk )

/**
  * @brief  Get the status register value.
  * @param  spi is the base address of SPI module.
  * @return status value.
  */
#define SPI_GET_STATUS(spi) ((spi)->STATUS)

uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
void SPI_DisableFIFO(SPI_T *spi);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_EnableWakeup(SPI_T *spi);
void SPI_DisableWakeup(SPI_T *spi);
/*@}*/ /* end of group NANO1X2_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NANO1X2_SPI_Driver */

/*@}*/ /* end of group NANO1X2_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
