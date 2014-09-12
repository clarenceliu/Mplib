/** 
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of UART_FIFO_Demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "UART_FIFO_Demo.h"
#include "tmpm037_uart.h"
#include <stdio.h>

#define BufSize (sizeof(TxBuffer) / sizeof(*(TxBuffer)))
#define BufSize1 (sizeof(TxBuffer1) / sizeof(*(TxBuffer1)))

uint8_t TxBuffer[] = "TMPM0371";
uint8_t RxBuffer[BufSize] = { 0U };

uint8_t TxBuffer1[] = "TMPM0372";
uint8_t RxBuffer1[BufSize1] = { 0U };

const uint8_t NumToBeTx = BufSize - 1U;
const uint8_t NumToBeTx1 = BufSize1 - 1U;

uint8_t TxCounter = 0U;
uint8_t RxCounter = 0U;

uint8_t TxCounter1 = 0U;
uint8_t RxCounter1 = 0U;

UART_InitTypeDef myUART;

void SIO_Configuration(TSB_SC_TypeDef * SCx);
void ResetIdx(void);

int UART_FIFO_Demo(void)
{
    /* Initialize system */
    SIO_Configuration(UART0);
    SIO_Configuration(UART3);

    myUART.BaudRate = (uint32_t) 115200;
    myUART.DataBits = UART_DATA_BITS_8;
    myUART.StopBits = UART_STOP_BITS_1;
    myUART.Parity = UART_NO_PARITY;
    myUART.Mode = UART_ENABLE_TX | UART_ENABLE_RX;
    myUART.FlowCtrl = UART_NONE_FLOW_CTRL;

    UART_Enable(UART0);
    UART_Init(UART0, &myUART);

    UART_Enable(UART3);
    UART_Init(UART3, &myUART);

    UART_RxFIFOByteSel(UART0, UART_RXFIFO_RXFLEVEL);
    UART_RxFIFOByteSel(UART3, UART_RXFIFO_RXFLEVEL);

    UART_TxFIFOINTCtrl(UART0, ENABLE);
    UART_TxFIFOINTCtrl(UART3, ENABLE);

    UART_RxFIFOINTCtrl(UART0, ENABLE);
    UART_RxFIFOINTCtrl(UART3, ENABLE);

    UART_TRxAutoDisable(UART0, UART_RXTXCNT_AUTODISABLE);
    UART_TRxAutoDisable(UART3, UART_RXTXCNT_AUTODISABLE);

    UART_FIFOConfig(UART0, ENABLE);
    UART_FIFOConfig(UART3, ENABLE);

    UART_RxFIFOFillLevel(UART0, UART_RXFIFO4B_FLEVLE_4_2B);
    UART_RxFIFOFillLevel(UART3, UART_RXFIFO4B_FLEVLE_4_2B);

    UART_RxFIFOINTSel(UART0, UART_RFIS_REACH_EXCEED_FLEVEL);
    UART_RxFIFOINTSel(UART3, UART_RFIS_REACH_EXCEED_FLEVEL);

    UART_RxFIFOClear(UART0);
    UART_RxFIFOClear(UART3);

    UART_TxBufferClear(UART0);
    UART_TxBufferClear(UART3);

    UART_TxFIFOFillLevel(UART0, UART_TXFIFO4B_FLEVLE_0_0B);
    UART_TxFIFOFillLevel(UART3, UART_TXFIFO4B_FLEVLE_0_0B);

    UART_TxFIFOINTSel(UART0, UART_TFIS_REACH_NOREACH_FLEVEL);
    UART_TxFIFOINTSel(UART3, UART_TFIS_REACH_NOREACH_FLEVEL);

    UART_TxFIFOClear(UART0);
    UART_TxFIFOClear(UART3);

    NVIC_EnableIRQ(INTTX0_IRQn);
    NVIC_EnableIRQ(INTRX3_IRQn);

    NVIC_EnableIRQ(INTTX3_IRQn);
    NVIC_EnableIRQ(INTRX0_IRQn);
    while (1) {
        UART_SetTxData(UART0, (uint32_t) (TxBuffer[TxCounter++]));
        UART_SetTxData(UART3, (uint32_t) (TxBuffer1[TxCounter1++]));
        while (RxCounter < NumToBeTx) {
            /* Do nothing */
        }

        while (RxCounter1 < NumToBeTx1) {
            /* Do nothing */
        }
#ifdef DEBUG
        printf("%s\n", RxBuffer1);
        printf("%s\n", RxBuffer);
#endif
        ResetIdx();
    }

}

void ResetIdx(void)
{
    uint8_t i = 0U;

    for (i = 0U; i <= RxCounter; i++) {
        RxBuffer[i] = 0U;
    }
    for (i = 0U; i <= RxCounter1; i++) {
        RxBuffer1[i] = 0U;
    }
    TxCounter = 0U;
    RxCounter = 0U;

    TxCounter1 = 0U;
    RxCounter1 = 0U;
}

void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == TSB_SC0) {
        TSB_PD->CR |= GPIO_BIT_3;
        TSB_PD->FR1 |= GPIO_BIT_3;
        TSB_PD->FR1 |= GPIO_BIT_2;
        TSB_PD->IE |= GPIO_BIT_2;
    } else if (SCx == TSB_SC1) {
        TSB_PG->CR |= GPIO_BIT_2;
        TSB_PG->FR1 |= GPIO_BIT_2;
        TSB_PG->FR1 |= GPIO_BIT_1;
        TSB_PG->IE |= GPIO_BIT_1;
    } else if (SCx == TSB_SC2) {
        TSB_PE->CR |= GPIO_BIT_4;
        TSB_PE->FR1 |= GPIO_BIT_4;
        TSB_PE->FR1 |= GPIO_BIT_3;
        TSB_PE->IE |= GPIO_BIT_3;
    } else if (SCx == TSB_SC3) {
        TSB_PF->CR |= GPIO_BIT_3;
        TSB_PF->FR1 |= GPIO_BIT_3;
        TSB_PF->FR1 |= GPIO_BIT_2;
        TSB_PF->IE |= GPIO_BIT_2;
    }
}


/**
  * @brief  Delay some time
  * @param  None
  * @retval None
  */
void delay(void)
{
    uint32_t i = 0U;
    for (i = 0U; i < 0xFFFFU; i++) {
        /* Do nothing */
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    printf("Err!");
    while (1) {
        __NOP();
    }
}
#endif
