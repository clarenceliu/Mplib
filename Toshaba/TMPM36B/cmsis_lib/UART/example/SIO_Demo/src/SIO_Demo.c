/** 
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of SIO Demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "SIO_Demo.h"

uint8_t SIO0_TxBuffer[BufSize] = "MasterToSlave";
uint8_t SIO1_RxBuffer[BufSize] = { 0U };

uint8_t SIO1_TxBuffer[BufSize] = "SlaveToMaster";
uint8_t SIO0_RxBuffer[BufSize] = { 0U };

volatile uint8_t fSIO0TxOK = 1U;
volatile uint8_t fSIO1TxOK = 1U;
volatile uint8_t gSIO0WrIndex = 0U;
volatile uint8_t gSIO1RdIndex = 0U;
volatile uint8_t gSIO1WrIndex = 0U;
volatile uint8_t gSIO0RdIndex = 0U;

void SIO_Configure(void);

/**
  * @brief  main  function
  * @param  None
  * @retval int
  */
int SIO_Demo(void)
{
    SIO_InitTypeDef SIO0_Init, SIO1_Init;

    /*configure the IO port of SIO */
    SIO_Configure();
    /*configure the SIO0 channel */
    SIO_Enable(SIO0);

    /*initialize the SIO0 struct */
    SIO0_Init.InputClkEdge = SIO_SCLKS_TXDF_RXDR;
    SIO0_Init.IntervalTime = SIO_SINT_TIME_SCLK_1;
    SIO0_Init.TransferMode = SIO_TRANSFER_FULLDPX;
    SIO0_Init.TransferDir = SIO_LSB_FRIST;
    SIO0_Init.Mode = SIO_ENABLE_TX | SIO_ENABLE_RX;
    SIO0_Init.DoubleBuffer = SIO_WBUF_ENABLE;
    SIO0_Init.BaudRateClock = SIO_BR_CLOCK_T4;
    SIO0_Init.Divider = SIO_BR_DIVIDER_2;

    SIO_Init(SIO0, SIO_CLK_BAUDRATE, &SIO0_Init);

    /*configure the SIO1 channel */
    SIO_Enable(SIO1);

    /*initialize the SIO1 struct */
    SIO1_Init.InputClkEdge = SIO_SCLKS_TXDF_RXDR;
    SIO1_Init.IntervalTime = SIO_SINT_TIME_SCLK_1;
    SIO1_Init.TransferMode = SIO_TRANSFER_FULLDPX;
    SIO1_Init.TransferDir = SIO_LSB_FRIST;
    SIO1_Init.Mode = SIO_ENABLE_TX | SIO_ENABLE_RX;
    SIO1_Init.DoubleBuffer = SIO_WBUF_ENABLE;

    SIO_Init(SIO1, SIO_CLK_SCLKINPUT, &SIO1_Init);


    /* enable SIO0 Channel TX interrupt */
    NVIC_EnableIRQ(INTTX0_IRQn);
    /* enable SIO1 Channel RX interrupt */
    NVIC_EnableIRQ(INTRX1_IRQn);

    /* enable SIO1 Channel TX interrupt */
    NVIC_EnableIRQ(INTTX1_IRQn);
    /* enable SIO0 Channel RX interrupt */
    NVIC_EnableIRQ(INTRX0_IRQn);

    while (1) {
        /*SIO1 send data from TXD1 */
        if (fSIO1TxOK == 1U) {
            fSIO1TxOK = 0U;
            SIO_SetTxData(SIO1, SIO1_TxBuffer[gSIO1WrIndex++]);
        } else {
            /*Do Nothing */
        }

        /*SIO0 send data from TXD0 */
        if (fSIO0TxOK == 1U) {
            fSIO0TxOK = 0U;
            SIO_SetTxData(SIO0, SIO0_TxBuffer[gSIO0WrIndex++]);
        } else {
            /*Do Nothing */
        }
       
       /*SIO0 receive data end */
        if (gSIO0RdIndex >= BufSize) {
            fSIO1TxOK = 0U;
            SIO_Disable(SIO1);
        } else {
            /*Do Nothing */
        }
        /*SIO1 receive data end */
        if (gSIO1RdIndex >= BufSize) {
            fSIO0TxOK = 0U;
            SIO_Disable(SIO0);
        } else {
            /*Do Nothing */
        }

    }
}

/**
  * @brief  configure the IO port of SIO
  * @param  None
  * @retval None
  */
void SIO_Configure(void)
{
    /*SET PE2 AS TXD0 */
    TSB_PE->FR1 |= (1U << 2U);
    TSB_PE->CR |= (1U << 2U);

    /*SET PE6 AS RXD1 */
    TSB_PE->FR1 |= (1U << 6U);
    TSB_PE->IE |= (1U << 6U);

    /*SET PE3 AS SCLK0 output */
    TSB_PE->FR1 |= (1U << 3U);
    TSB_PE->CR |= (1U << 3U);

    /*SET PE4 AS SCLK1 input */
    TSB_PE->FR1 |= (1U << 4U);
    TSB_PE->IE |= (1U << 4U);

    /*SET PE1 AS RXD0 */
    TSB_PE->FR1 |= (1U << 1U);
    TSB_PE->IE |= (1U << 1U);

    /*SET PE5 AS TXD1 */
    TSB_PE->FR1 |= (1U << 5U);
    TSB_PE->CR |= (1U << 5U);
}

/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
