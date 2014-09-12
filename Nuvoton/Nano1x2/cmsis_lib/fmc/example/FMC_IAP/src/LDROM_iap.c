/******************************************************************************
 * @file     LDROM_main.c
 * @version  V1.00
 * $Revision: 2 $
 * $Date: 13/12/16 4:27p $
 * @brief    FMC LDROM IAP sample program for NANO1X2 series MCU
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "Nano1X2Series.h"




typedef void (FUNC_PTR)(void);
void SysInit(void);
void UART0_Init();
void __set_SP(uint32_t _sp);
char UART_GetChar(void);


int LDROM_iap()
{
    FUNC_PTR    *func;

    /* Init System, IP clock and multi-function I/O */
    SysInit();
    /* Init UART0 for printf */
    UART0_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\n\n");
    printf("+----------------------------------------+\n");
    printf("|     Nano1x2 FMC IAP Sample Code        |\n");
    printf("|           [LDROM code]                 |\n");
    printf("+----------------------------------------+\n");

    SYS_UnlockReg();

    /* Enable FMC ISP function */
    FMC_Open();

    printf("\n\nPress any key to branch to APROM...\n");
    UART_GetChar();

    printf("\n\nChange VECMAP and branch to LDROM...\n");
    while (!(UART0->FSR & UART_FSR_TX_EMPTY_F_Msk));

    /*  NOTE!
     *     Before change VECMAP, user MUST disable all interrupts.
     */
    FMC_SetVectorPageAddr(FMC_APROM_BASE);
    SYS_LockReg();

    func = (FUNC_PTR *)*(uint32_t *)(FMC_APROM_BASE + 4);
    __set_SP(*(uint32_t *)FMC_APROM_BASE);
    func();

    while (1);
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


 void __set_SP(uint32_t _sp)
{
	__asm(
	"MSR MSP, r0\n"
    "BX lr");
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
