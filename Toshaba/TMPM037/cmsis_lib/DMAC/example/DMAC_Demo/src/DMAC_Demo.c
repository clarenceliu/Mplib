/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of DMAC UART demo for the
 *          TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include "DMAC_Demo.h"

#define UART0_BASE_ADDR   TSB_SC0_BASE

#define UART0_BUF_OFFSET  sizeof(UART0->EN)

typedef enum { FAILED = 0U, PASSED = !FAILED } TestResult;

/* Function declaration */

/* User ram definition and m037 can not use the const to initialize SRC_Buffer like m037*/
uint8_t SRC_Buffer[] = "TOSHIBA";
uint8_t UART_Rx_Buffer[BUFFER_SIZE];
uint8_t UART_Rx_Cnt;

/* main function */
int DMAC_Demo(void)
{
    UART_InitTypeDef UART_InitStruct;
    DMAC_InitTypeDef DMAC_InitStruct;
    DMAC_Channel myChannel = DMAC_CHANNEL_1;
    uint32_t LinkAddr;
    uint8_t size;

    /* Set GPIO as UART */
    GPIO_SetUART();

    /* Set UART1 as reception */
    UART_Rx_Cnt = 0U;
    UART_InitStruct.BaudRate = 115200U;
    UART_InitStruct.DataBits = UART_DATA_BITS_8;
    UART_InitStruct.StopBits = UART_STOP_BITS_1;
    UART_InitStruct.Parity = UART_NO_PARITY;
    UART_InitStruct.Mode = UART_ENABLE_RX;
    UART_InitStruct.FlowCtrl = UART_NONE_FLOW_CTRL;
    UART_Enable(UART1);
    UART_Init(UART1, &UART_InitStruct);

    /* Set UART0 as transmitter */
    UART_InitStruct.Mode = UART_ENABLE_TX;
    UART_Enable(UART0);
    UART_Init(UART0, &UART_InitStruct);
    UART_SetTxDMAReq(UART0, ENABLE);

    /* DMA channel1 configuration */
    size = sizeof(SRC_Buffer);
    DMAC_InitStruct.SrcAddr = (uint32_t) SRC_Buffer;
    DMAC_InitStruct.SrcIncrementState = ENABLE;
    DMAC_InitStruct.SrcBitWidth = DMAC_BYTE;
    DMAC_InitStruct.SrcBurstSize = DMAC_1_BEAT;
    DMAC_InitStruct.DstAddr = (uint32_t) (UART0_BASE_ADDR + UART0_BUF_OFFSET);
    DMAC_InitStruct.DstIncrementState = DISABLE;
    DMAC_InitStruct.DstBitWidth = DMAC_BYTE;
    DMAC_InitStruct.DstBurstSize = DMAC_1_BEAT;
    DMAC_InitStruct.TxSize = size;
    DMAC_InitStruct.TxDirection = DMAC_MEMORY_TO_PERIPH;
    DMAC_InitStruct.TxDstPeriph = DMAC_SIO0_UART0_TX;

    /* CXCONTROL<I> must be set when use transfer interrupt */
    DMAC_InitStruct.TxINT = ENABLE;

    LinkAddr = 0U;

    __disable_irq();
    /* enable DMA interrupt */
    NVIC_ClearPendingIRQ(INTDMAC_IRQn);
    NVIC_EnableIRQ(INTDMAC_IRQn);

    /*Enable DMA circuit */
    DMAC_Enable();
    /* Clear any pending interrupts on the channel */
    DMAC_ClearTxINTReq(myChannel, DMAC_INT_TX_END);
    DMAC_ClearTxINTReq(myChannel, DMAC_INT_TX_ERR);
    /*Initialize DMA channel */
    DMAC_Init(myChannel, &DMAC_InitStruct);
    /* If don't require scatter/gather function, set the DMACCxLLI Register to 0 */
    DMAC_SetLinkedList(myChannel, LinkAddr);
    __enable_irq();

    /* enable UART1 reception interrupt */
    NVIC_ClearPendingIRQ(INTRX1_IRQn);
    NVIC_EnableIRQ(INTRX1_IRQn);

    /*Enable DMA Channel transfer and interrupt */
    DMAC_SetTxINTConfig(myChannel, DMAC_INT_TX_END, ENABLE);
    /* Enable DMA burst transfer request */
    DMAC_SetSWBurstReq(DMAC_SIO0_UART0_TX);

    /*Enable DMA channel */
    DMAC_SetDMAChannel(myChannel, ENABLE);

    /* Wait the end of transmission */
    while (TxEndFlag != DONE) {
        /* Do nothing */
    }
    while (UART_Rx_Cnt < size) {
        /* Do nothing */
    }

    while (1U) {
        /* Do nothing */
    }
}

/**
  * @brief  Configure I/O ports for UART
  * @param  None
  * @retval None
  */
void GPIO_SetUART(void)
{
    /* SET PD3 to SC0TXD,PD2 to SC0RXD */
    TSB_PD->CR |= 0x08U;
    TSB_PD->FR1 |= 0x0CU;
    TSB_PD->IE |= 0x04U;

    /* SET PG2 to SC1TXD,PG1 to SC1RXD */
    TSB_PG->CR |= 0x04U;
    TSB_PG->FR1 |= 0x06U;
    TSB_PG->IE |= 0x02U;
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
