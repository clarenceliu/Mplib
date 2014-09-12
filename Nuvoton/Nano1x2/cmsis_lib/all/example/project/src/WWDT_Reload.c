/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 2 $
 * $Date: 13/12/16 4:27p $
 * @brief    WWDT sample for Nano1x2 series MCU
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "Nano1x2Series.h"

void SysInit(void);
int32_t WWDT_Reload (void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
	SysInit();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("\nThis sample code demonstrate WWDT reload function\n");

    // WWDT register is locked, so it is necessary to unlock protect register before configure WDT
    SYS_UnlockReg();
    // WWDT timeout every 768 * 64 WWDT clock, compare interrupt trigger at 768 * 32 WWDT clock, enable WWDT counter compare interrupt
    WWDT_Open(WWDT_PRESCALER_768, 0x20, TRUE);

    // Enable WWDT (share with WDT) timeout interrupt
    NVIC_EnableIRQ(WDT_IRQn);

    while(1);

}



// WWDT shares the same IRQ number with WDT, hence use the same IRQ handler name
void WDT_IRQHandler(void)
{

    // Reload WWDT counter and clear WWDT interrupt flag
    WWDT_RELOAD_COUNTER();
    WWDT_CLEAR_INT_FLAG();
    printf("WWDT counter reload\n");

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
    CLK_EnableModuleClock(WDT_MODULE);


    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
    CLK_SetModuleClock(WDT_MODULE, 0, 0);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();


    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->PB_L_MFP &= ~(SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB0_MFP_UART0_TX | SYS_PB_L_MFP_PB1_MFP_UART0_RX);
    /* Lock protected registers */
    SYS_LockReg();
}



/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


