/**************************************************************************//**
 * @file     CRYPTO_TDES.c
 * @version  V1.10
 * $Revision: 3 $
 * $Date: 13/11/10 9:33a $
 * @brief    CRYPTO TDES sample program for NUC400 series MCU
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NUC400Series.h"
#include "SYS.h"
#include "CLK.h"
#include "CRYPTO.h"

#define PLLCON_SETTING      CLK_PLLCON_84MHz_HXT
#define PLL_CLOCK           84000000

uint32_t PllClock         = PLL_CLOCK;


uint8_t au8MyTDESKey[3][8] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
};

uint32_t au32MyTDESIV[2] = {  0x00000000, 0x00000000 };


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8InputData[] = {
#else
__attribute__((aligned(4))) uint8_t au8InputData[] = {
#endif
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8OutputData[1024];
#else
__attribute__((aligned(4))) uint8_t au8OutputData[1024];
#endif

static volatile int  g_TDES_done;

void  dump_buff_hex(uint8_t *pucBuff, int nBytes);
void SYS_Init(void);
void UART0_Init(void);


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t CRYPTO_TDES(void)
{
    /* Lock protected registers */
    if(SYS->REGWRPROT == 1) // In end of main function, program issued CPU reset and write-protection will be disabled.
        SYS_LockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init(); //In the end of SYS_Init() will issue SYS_LockReg() to lock protected register. If user want to write protected register, please issue SYS_UnlockReg() to unlock protected register.

    /* Init UART0 for printf */
    UART0_Init();

    printf("+--------------------------------------------+\n");
    printf("|    NUC400 Crypto TDES Driver Sample Code   |\n");
    printf("+--------------------------------------------+\n");

    NVIC_EnableIRQ(CRYPTO_IRQn);
    TDES_ENABLE_INT();

    /*---------------------------------------
     *  TDES CBC mode encrypt
     *---------------------------------------*/
    TDES_Open(0, 1, TDES_MODE_CBC, TDES_IN_OUT_SWAP);
    TDES_SetKey(0, au8MyTDESKey);
    TDES_SetInitVect(0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(0, (uint32_t)au8InputData, (uint32_t)au8OutputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES encrypt done.\n\n");
    dump_buff_hex(au8OutputData, sizeof(au8InputData));

    /*---------------------------------------
     *  TDES CBC mode decrypt
     *---------------------------------------*/
    TDES_Open(0, 0, TDES_MODE_CBC, TDES_IN_OUT_SWAP);
    TDES_SetKey(0, au8MyTDESKey);
    TDES_SetInitVect(0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(0, (uint32_t)au8InputData, (uint32_t)au8OutputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES decrypt done.\n\n");
    dump_buff_hex(au8OutputData, sizeof(au8InputData));

    while (1);
}


void CRYPTO_IRQHandler()
{
    if (TDES_GET_INT_FLAG()) {
        g_TDES_done = 1;
        TDES_CLR_INT_FLAG();
    }
}


void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0) {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++) {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                printf("%c", pucBuff[nIdx + i]);
            else
                printf(".");
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCON_HXT_EN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_CLKSTATUS_HXT_STB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware.*/
    CLK->PLLCON|= CLK_PLLCON_PD_Msk;

    /* Set PLL frequency */
    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk);

    /* Switch HCLK clock source to PLL */
    CLK->CLKSEL0 = CLK_CLKSEL0_HCLK_S_PLL;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable Crypto clock */
    CLK->AHBCLK |= CLK_AHBCLK_CRYPTO_EN_Msk;

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE,CLK_CLKSEL1_UART_S_HXT,CLK_CLKDIV0_UART(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set GPG multi-function pins for UART0 RXD and TXD */
    SYS->GPG_MFPL = SYS_GPG_MFPL_PG1_MFP_UART0_RXD | SYS_GPG_MFPL_PG2_MFP_UART0_TXD ;

    /* Lock protected registers */
    SYS_LockReg();
}


void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART0->LCR |=0x07;
    UART0->BAUD = 0x30000066;   /* 12MHz reference clock input, for 115200 */
}


