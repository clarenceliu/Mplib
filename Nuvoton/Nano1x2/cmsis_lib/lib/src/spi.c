/****************************************************************************//**
 * @file     spi.c
 * @version  V0.10
 * $Revision: 2 $
 * $Date: 14/01/14 10:58a $
 * @brief    NANO1X2 series SPI driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "nano1x2series.h"

/** @addtogroup NANO1X2_Device_Driver NANO1X2 Device Driver
  @{
*/

/** @addtogroup NANO1X2_SPI_Driver SPI Driver
  @{
*/


/** @addtogroup NANO1X2_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief  This function make SPI module be ready to transfer.
  *         By default, the SPI transfer sequence is MSB first and
  *         the automatic slave select function is disabled. In
  *         Slave mode, the u32BusClock must be NULL and the SPI clock
  *         divider setting will be 0.
  * @param  spi is the base address of SPI module.
  * @param  u32MasterSlave decides the SPI module is operating in master mode or in slave mode. (SPI_SLAVE, SPI_MASTER)
  * @param  u32SPIMode decides the transfer timing. (SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_03)
  * @param  u32DataWidth decides the data width of a SPI transaction.
  * @param  u32BusClock is the expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI peripheral clock.
  */
uint32_t SPI_Open(SPI_T *spi,
                  uint32_t u32MasterSlave,
                  uint32_t u32SPIMode,
                  uint32_t u32DataWidth,
                  uint32_t u32BusClock)
{
    uint32_t u32Pclk, u32Div;

    // assert if is as slave but bus clock isn't equal 0
    //

    if(u32DataWidth == 32)
        u32DataWidth = 0;

    spi->CTL = u32MasterSlave | (u32DataWidth << SPI_CTL_TX_BIT_LEN_Pos) | (u32SPIMode);

    u32Pclk = CLK_GetHCLKFreq();

    u32Div = 0xffff;

    if(u32BusClock !=0 ) {
        u32Div = (((u32Pclk / u32BusClock) + 1) >> 1) - 1;
        if(u32Div > 0xFFFF)
            u32Div = 0xFFFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xffff) | u32Div;
    } else
        spi->CLKDIV = 0;

    return ( u32Pclk / ((u32Div+1)*2) );
}

/**
  * @brief Reset SPI module and disable SPI peripheral clock.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_Close(SPI_T *spi)
{
    /* Reset SPI */
    if((uint32_t)spi == SPI0_BASE) {
        SYS->IPRST_CTL2 |= SYS_IPRST_CTL2_SPI0_RST_Msk;
        SYS->IPRST_CTL2 &= ~SYS_IPRST_CTL2_SPI0_RST_Msk;
    } else {
        SYS->IPRST_CTL2 |= SYS_IPRST_CTL2_SPI1_RST_Msk;
        SYS->IPRST_CTL2 &= ~SYS_IPRST_CTL2_SPI1_RST_Msk;
    }

    /* Disable SPI clock */
    if((uint32_t)spi == SPI0_BASE)
        CLK->APBCLK &= ~CLK_APBCLK_SPI0_EN_Msk;
    else
        CLK->APBCLK &= ~CLK_APBCLK_SPI1_EN_Msk;
}

/**
  * @brief Clear Rx FIFO buffer.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_ClearRxFIFO(SPI_T *spi)
{
    spi->FFCTL |= SPI_FFCTL_RX_CLR_Msk;
}

/**
  * @brief Clear Tx FIFO buffer.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_ClearTxFIFO(SPI_T *spi)
{
    spi->FFCTL |= SPI_FFCTL_TX_CLR_Msk;
}

/**
  * @brief Disable the automatic slave select function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_DisableAutoSS(SPI_T *spi)
{
    spi->SSR &= ~SPI_SSR_AUTOSS_Msk;
}

/**
  * @brief Enable the automatic slave select function. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @param  u32SSPinMask specifies slave select pins. (SPI_SS)
  * @param  u32ActiveLevel specifies the active level of slave select signal. (SPI_SS_ACTIVE_HIGH, SPI_SS_ACTIVE_LOW)
  * @return none
  */
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel)
{
    spi->SSR |= (u32SSPinMask | u32ActiveLevel) | SPI_SSR_AUTOSS_Msk;
}

/**
  * @brief Set the SPI bus clock. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @param  u32BusClock is the expected frequency of SPI bus clock.
  * @return Actual frequency of SPI peripheral clock.
  */
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock)
{
    uint32_t u32Pclk = CLK_GetHCLKFreq();
    uint32_t u32Div = 0xffff;

    if(u32BusClock !=0 ) {
        u32Div = (((u32Pclk / u32BusClock) + 1) >> 1) - 1;
        if(u32Div > 0xFFFF)
            u32Div = 0xFFFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xffff) | u32Div;
    } else
        spi->CLKDIV = 0;

    return ( u32Pclk / ((u32Div+1)*2) );
}

/**
  * @brief Enable FIFO mode with user-specified Tx FIFO threshold and Rx FIFO threshold configurations.
  * @param  spi is the base address of SPI module.
  * @param  u32TxThreshold decides the Tx FIFO threshold.
  * @param  u32RxThreshold decides the Rx FIFO threshold.
  * @return none
  */
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    spi->FFCTL = (spi->FFCTL & ~(SPI_FFCTL_TX_THRESHOLD_Msk | SPI_FFCTL_RX_THRESHOLD_Msk) |
                  (u32TxThreshold << SPI_FFCTL_TX_THRESHOLD_Pos) |
                  (u32RxThreshold << SPI_FFCTL_RX_THRESHOLD_Pos));

    spi->CTL |= SPI_CTL_FIFOM_Msk;
}

/**
  * @brief Disable FIFO mode.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_DisableFIFO(SPI_T *spi)
{
    spi->CTL &= ~SPI_CTL_FIFOM_Msk;
}

/**
  * @brief Get the actual frequency of SPI bus clock. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @return Actual SPI bus clock frequency.
  */
uint32_t SPI_GetBusClock(SPI_T *spi)
{
    uint32_t u32Div;
    uint32_t u32ApbClock;

    u32ApbClock = CLK_GetHCLKFreq();
    u32Div = spi->CLKDIV & 0xff;
    return ((u32ApbClock >> 1) / (u32Div + 1));
}

/**
  * @brief Enable FIFO related interrupts specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt enable bits.
  *         Each bit corresponds to a interrupt bit.
  *         This parameter decides which interrupts will be enabled. Valid values are:
  *           - \ref SPI_IE_MASK
  *           - \ref SPI_SSTA_INTEN_MASK
  *           - \ref SPI_FIFO_TX_INTEN_MASK
  *           - \ref SPI_FIFO_RX_INTEN_MASK
  *           - \ref SPI_FIFO_RXOV_INTEN_MASK
  *           - \ref SPI_FIFO_TIMEOUT_INTEN_MASK
  * @return none
  */
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask)
{
    if((u32Mask & SPI_IE_MASK) == SPI_IE_MASK)
        spi->CTL |= SPI_CTL_INTEN_Msk;

    if((u32Mask & SPI_SSTA_INTEN_MASK) == SPI_SSTA_INTEN_MASK)
        spi->SSR |= SPI_SSR_SSTA_INTEN_Msk;

    if((u32Mask & SPI_FIFO_TX_INTEN_MASK) == SPI_FIFO_TX_INTEN_MASK)
        spi->FFCTL |= SPI_FFCTL_TX_INTEN_Msk;

    if((u32Mask & SPI_FIFO_RX_INTEN_MASK) == SPI_FIFO_RX_INTEN_MASK)
        spi->FFCTL |= SPI_FFCTL_RX_INTEN_Msk;

    if((u32Mask & SPI_FIFO_RXOV_INTEN_MASK) == SPI_FIFO_RXOV_INTEN_MASK)
        spi->FFCTL |= SPI_FFCTL_RXOVE_INTEN_Msk;

    if((u32Mask & SPI_FIFO_TIMEOUT_INTEN_MASK) == SPI_FIFO_TIMEOUT_INTEN_MASK)
        spi->FFCTL |= SPI_FFCTL_TIMEOUT_EN_Msk;
}

/**
  * @brief Disable FIFO related interrupts specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt enable bits.
  *         Each bit corresponds to a interrupt bit.
  *         This parameter decides which interrupts will be enabled. Valid values are:
  *           - \ref SPI_IE_MASK
  *           - \ref SPI_SSTA_INTEN_MASK
  *           - \ref SPI_FIFO_TX_INTEN_MASK
  *           - \ref SPI_FIFO_RX_INTEN_MASK
  *           - \ref SPI_FIFO_RXOV_INTEN_MASK
  *           - \ref SPI_FIFO_TIMEOUT_INTEN_MASK
  * @return none
  */
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask)
{
    if((u32Mask & SPI_IE_MASK) == SPI_IE_MASK)
        spi->CTL &= ~SPI_CTL_INTEN_Msk;

    if((u32Mask & SPI_SSTA_INTEN_MASK) == SPI_SSTA_INTEN_MASK)
        spi->SSR &= ~SPI_SSR_SSTA_INTEN_Msk;

    if((u32Mask & SPI_FIFO_TX_INTEN_MASK) == SPI_FIFO_TX_INTEN_MASK)
        spi->FFCTL &= ~SPI_FFCTL_TX_INTEN_Msk;

    if((u32Mask & SPI_FIFO_RX_INTEN_MASK) == SPI_FIFO_RX_INTEN_MASK)
        spi->FFCTL &= ~SPI_FFCTL_RX_INTEN_Msk;

    if((u32Mask & SPI_FIFO_RXOV_INTEN_MASK) == SPI_FIFO_RXOV_INTEN_MASK)
        spi->FFCTL &= ~SPI_FFCTL_RXOVE_INTEN_Msk;

    if((u32Mask & SPI_FIFO_TIMEOUT_INTEN_MASK) == SPI_FIFO_TIMEOUT_INTEN_MASK)
        spi->FFCTL &= ~SPI_FFCTL_TIMEOUT_EN_Msk;
}

/**
  * @brief Enable wake-up function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_EnableWakeup(SPI_T *spi)
{
    spi->CTL |= SPI_CTL_WKEUP_EN_Msk;
}

/**
  * @brief Disable wake-up function.
  * @param  spi is the base address of SPI module.
  * @return none
  */
void SPI_DisableWakeup(SPI_T *spi)
{
    spi->CTL &= ~SPI_CTL_WKEUP_EN_Msk;
}

/*@}*/ /* end of group NANO1X2_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NANO1X2_SPI_Driver */

/*@}*/ /* end of group NANO1X2_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
