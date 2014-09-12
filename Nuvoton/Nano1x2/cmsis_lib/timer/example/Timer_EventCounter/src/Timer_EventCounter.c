
/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 13/12/16 4:27p $
 * @brief    Timer sample for Nano1x2 series MCU
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "Nano1x2Series.h"

void SysInit(void);
char UART_GetChar(void);

int Timer_EventCounter(void)
{
    int i;
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SysInit();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("\nThis sample code use TM0_CNT_OUT(PB.8) to count PB.3 input event\n");
    printf("Please connect PB.8 to PB.3, press any key to continue\n");
    UART_GetChar();

    PB->DOUT |= 1 << 3;                     // Set init state to high
    PB->PMD = (PB->PMD & ~(0x3 << 6)) | (0x1 << 6);  // Set to output mode

    // Give a dummy target frequency here. Will over write prescale and compare value with macro
    TIMER_Open(TIMER0, TIMER_ONESHOT_MODE, 100);

    // Update prescale and compare value to what we need in event counter mode.
    TIMER_SET_PRESCALE_VALUE(TIMER0, 0);
    TIMER_SET_CMP_VALUE(TIMER0, 1000);
    // Counter increase on falling edge
    TIMER_EnableEventCounter(TIMER0, TIMER_COUNTER_FALLING_EDGE);
    // Start Timer 0
    TIMER_Start(TIMER0);
    // Enable timer interrupt
    TIMER_EnableInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);


    for(i = 0; i < 1000; i++) {
        PB->DOUT &= ~(1 << 3); // low
        PB->DOUT |= (1 << 3);  // high
    }

    while(1);

}


void TMR0_IRQHandler(void)
{
    printf("Count 1000 falling events! Test complete\n");
    TIMER_ClearIntFlag(TIMER0);

}

void SysInit(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_CLKSTATUS_HXT_STB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT,CLK_HCLK_CLK_DIVIDER(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);


    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HXT, CLK_TMR0_CLK_DIVIDER(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();


    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->PB_L_MFP &= ~(SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB0_MFP_UART0_TX | SYS_PB_L_MFP_PB1_MFP_UART0_RX);

    /* Set Timer0 event counting/toggle out pin */
    SYS->PB_H_MFP &= ~SYS_PB_H_MFP_PB8_MFP_Msk;
    SYS->PB_H_MFP |= SYS_PB_H_MFP_PB8_MFP_TMR0_EXT;

    /* Lock protected registers */
    SYS_LockReg();

}

char UART_GetChar(void)
{
#if defined(DEBUG_ENABLE_SEMIHOST)
# if defined ( __CC_ARM   )
    int nRet;
    while(SH_DoCommand(0x101, 0, &nRet) != 0) {
        if(nRet != 0) {
            SH_DoCommand(0x07, 0, &nRet);
            return (char)nRet;
        }
    }
# else
    int nRet;
    while(SH_DoCommand(0x7, 0, &nRet) != 0) {
        if(nRet != 0)
            return (char)nRet;
    }
# endif
#endif
#ifndef DISABLE_UART
    while (1) {
        if(!(UART0->FSR & UART_FSR_RX_EMPTY_F_Msk)) {
            return (UART0->RBR);

        }
    }
#else
    return(0);
#endif
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


