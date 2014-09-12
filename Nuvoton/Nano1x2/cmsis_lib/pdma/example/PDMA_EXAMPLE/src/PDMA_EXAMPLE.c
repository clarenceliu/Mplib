/**************************************************************************//**
 * @file     main.c
 * @version  V2.10
 * $Date: 13/12/16 4:27p $
 * @brief    Nano1x2 Series PDMA Driver Sample Code
 *
 * @note
 * Copyright (C) 2012 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "nano1x2series.h"

#define TEST_CH     4

uint32_t PDMA_TEST_LENGTH = 64;
uint8_t SrcArray[256];
uint8_t DestArray[256];
uint32_t volatile u32IsTestOver = 0;

void SysInit(void);
void UART0_Init();

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int PDMA_EXAMPLE (void)
{
    /* Init System, IP clock and multi-function I/O */
	SysInit(); //In the end of SYS_Init() will issue SYS_LockReg() to lock protected register. If user want to write protected register, please issue SYS_UnlockReg() to unlock protected register.

    /* Init UART for printf */
    UART0_Init();

    printf("\n\nCPU @ %dHz <%d>\n", SystemCoreClock, TEST_CH);

    printf("+--------------------------------------+ \n");
    printf("|    NANO1x2 PDMA Driver Sample Code   | \n");
    printf("+--------------------------------------+ \n");

    /* Open Channel 2 */
    PDMA_Open(1 << TEST_CH);
    PDMA_SetTransferCnt(TEST_CH, PDMA_WIDTH_32, PDMA_TEST_LENGTH);
    PDMA_SetTransferAddr(TEST_CH, (uint32_t)SrcArray, PDMA_SAR_INC, (uint32_t)DestArray, PDMA_DAR_INC);
    PDMA_SetTransferMode(TEST_CH, PDMA_MEM, 0, 0);
    PDMA_SetTimeOut(TEST_CH, 0, 0x5555);
    PDMA_EnableInt(TEST_CH, PDMA_IER_BLKD_IE_Msk);
    NVIC_EnableIRQ(PDMA_IRQn);
    u32IsTestOver = 0;
    PDMA_Trigger(TEST_CH);
    while(u32IsTestOver == 0);

    if (u32IsTestOver == TEST_CH)
        printf("test done...\n");

    PDMA_Close();
}
/**
 * @brief       DMA IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The DMA default IRQ, declared in startup_nano1x2series.s.
 */

void PDMA_IRQHandler(void)
{
    uint32_t status = PDMA_GET_INT_STATUS();

    if (status & 0x2) { /* CH1 */
        if (PDMA_GET_CH_INT_STS() & 0x2)
            u32IsTestOver = 1;
        PDMA_CLR_CH_INT_FLAG(1, PDMA_ISR_BLKD_IF_Msk);
    } else if (status & 0x4) { /* CH2 */
        if (PDMA_GET_CH_INT_STS() & 0x2)
            u32IsTestOver = 2;
        PDMA_CLR_CH_INT_FLAG(2, PDMA_ISR_BLKD_IF_Msk);
    } else if (status & 0x8) { /* CH3 */
        if (PDMA_GET_CH_INT_STS() & 0x2)
            u32IsTestOver = 3;
        PDMA_CLR_CH_INT_FLAG(3, PDMA_ISR_BLKD_IF_Msk);
    } else if (status & 0x10) { /* CH4 */
        if (PDMA_GET_CH_INT_STS() & 0x2)
            u32IsTestOver = 4;
        PDMA_CLR_CH_INT_FLAG(4, PDMA_ISR_BLKD_IF_Msk);
    } else
        printf("unknown interrupt !!\n");
}

void SysInit(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCTL &= ~CLK_PWRCTL_HXT_EN_Msk;
    CLK->PWRCTL |= (0x1 << CLK_PWRCTL_HXT_EN_Pos); // HXT Enabled

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_CLKSTATUS_HXT_STB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HXT;

    /* Enable IP clock */
    CLK->AHBCLK |= CLK_AHBCLK_DMA_EN_Msk;   /* DMA clock enable */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN; // UART0 Clock Enable

    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART_S_Pos);// Clock source from external 12 MHz or 32 KHz crystal clock

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PB multi-function pins for UART0 RXD and TXD  */
    SYS->PB_H_MFP &= ~(SYS_PB_H_MFP_PB13_MFP_Msk | SYS_PB_H_MFP_PB14_MFP_Msk);
    SYS->PB_H_MFP |= (SYS_PB_H_MFP_PB13_MFP_UART0_RX | SYS_PB_H_MFP_PB14_MFP_UART0_TX);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART_Open(UART0, 115200);
}




