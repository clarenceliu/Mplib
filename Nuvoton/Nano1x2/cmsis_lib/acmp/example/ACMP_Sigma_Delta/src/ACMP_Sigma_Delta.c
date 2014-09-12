/******************************************************************************
 * @file     main.c
 * @brief    Nano1xx ACMP Sigma-Delta Sample code
 * @version  1.0.1
 * @date     04, September, 2013
 *
 * @note
 * Copyright (C) 2012-2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "Nano1X2Series.h"
void SysInit(void);
void UART0_Init(void);


#define PRESCALE  0x30
volatile int32_t tmr0_complete=0;
volatile int32_t tmr0_cap_complete=0;
ACMP_Sigma_Delta (void)
{
    uint32_t sample;
    float val;
    float inVoltage=3.3;
    sample=(uint32_t)(inVoltage*1000);  /* Set sample number */

    SysInit();

    UART0_Init();

    //ACMP CPO0 : PA6
    //ACMP CPN0 : PA5
    //ACMP CPP0 : PA4
    //Charge/Discharge pin : PA14

    CLK_EnableModuleClock(ACMP_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(TMR1_MODULE);
    CLK_SetModuleClock(TMR0_MODULE,CLK_CLKSEL1_TMR0_S_HXT,CLK_TMR0_CLK_DIVIDER(1));
    CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_HXT,CLK_TMR1_CLK_DIVIDER(1));

    TIMER0->PRECNT  = PRESCALE;   // Set timer 0 pre-scale to 1, optional
    TIMER0->CMPR  = sample/2;     // Set timer 0 compare value to 1024
    TIMER0->ECTL  = 0x00001013;   // Enable timer 0 event generator function, choose event generator reference source from ACMP and enable check for timer counter equals to half of comparator
    TIMER0->IER   = 0x00000001;   // Enable timer 0 ACMP enable timer function
    TIMER1->ECTL  = 0x00000100;   // Choose timer 0 event generator out to be timer 1 event count source
    TIMER1->CTL   = 0x00003001;   //  Enable timer 1 event count function
    TIMER0->CTL   = 0x00000040;   // Enable timer 0 ACMP enable timer function

    NVIC_EnableIRQ(TMR0_IRQn);
    NVIC_EnableIRQ(TMR1_IRQn);
    ACMP_Open(ACMP,0,ACMP_CMPCR_CN0_PIN,ACMP_CMPCR_CMP_HYSTERSIS_DISABLE);
    ACMP_SetSigmaDeltaConv(ACMP_TIMER01,ACMP_CMP0MODCR_TMR_TRI_LV_RISING,ACMP_CMP0CR_CPP0SEL_PA4,ACMP_CMP0MODCR_CH_DIS_PINSEL_PA14);

    while(1) {

        ACMP_ENABLE(ACMP,0);
        ACMP_START_CONV(ACMP);    //Start to Charge or Discharge
        while(!tmr0_complete);
        tmr0_complete=0;
        ACMP_DISABLE(ACMP,0);
        val=(double)TIMER1->DR/(float)sample*inVoltage;
        printf("Voltage=%.2f\n",val);
        *(volatile unsigned int *)(TIMER1_BASE+0x014)=0;
    }
}

void SysInit(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set HCLK source form HXT and HCLK source divide 1  */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT,CLK_HCLK_CLK_DIVIDER(1));

    /* Enable external 12MHz HXT, 32KHz LXT and HIRC */
    CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk | CLK_PWRCTL_LXT_EN_Msk | CLK_PWRCTL_HIRC_EN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_HXT_STB_Msk | CLK_CLKSTATUS_LXT_STB_Msk | CLK_CLKSTATUS_HIRC_STB_Msk);

    /*  Set HCLK frequency 32MHz */
    CLK_SetCoreClock(32000000);

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE,CLK_CLKSEL1_UART_S_HIRC,CLK_UART_CLK_DIVIDER(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PA multi-function pins for UART0 RXD and TXD */
    SYS->PB_L_MFP &= ~( SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB0_MFP_UART0_TX | SYS_PB_L_MFP_PB1_MFP_UART0_RX );

    /* Set PB multi-function pins for Clock Output */
    SYS->PB_H_MFP = ( SYS->PB_H_MFP & ~SYS_PB_H_MFP_PB12_MFP_Msk ) |  SYS_PB_H_MFP_PB12_MFP_CKO0;

    /* Set PA multi-function pins for ACMP */
    SYS->PA_L_MFP = (SYS->PA_L_MFP & ~SYS_PA_L_MFP_PA6_MFP_Msk ) | SYS_PA_L_MFP_PA6_MFP_ACMP0_O;  /* ACMP CPO0  */
    SYS->PA_L_MFP = (SYS->PA_L_MFP & ~SYS_PA_L_MFP_PA5_MFP_Msk ) | SYS_PA_L_MFP_PA5_MFP_ACMP0_N;  /* ACMP CPN0  */
    SYS->PA_L_MFP = (SYS->PA_L_MFP & ~SYS_PA_L_MFP_PA4_MFP_Msk ) | SYS_PA_L_MFP_PA4_MFP_ACMP0_P;  /* ACMP CPP0  */
    SYS->PA_H_MFP = (SYS->PA_H_MFP & ~SYS_PA_H_MFP_PA14_MFP_Msk) | SYS_PA_H_MFP_PA14_MFP_ACMP0_C; /* ACMP charge pin  */

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
    UART_Open(UART0, 115200);
}

void TMR0_IRQHandler(void)
{
    int status;
    status=TIMER0->ISR ;
    if(status & 0x1) tmr0_complete=1;
    if(status & 0x2) tmr0_cap_complete=1;
    TIMER0->ISR = status;
}


/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
