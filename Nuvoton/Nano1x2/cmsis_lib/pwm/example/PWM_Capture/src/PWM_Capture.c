
/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 7 $
 * $Date: 14/03/27 1:43p $
 * @brief    PWM sample for NANO1X2 series MCU
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "Nano1X2Series.h"

#define SAMPLE_CNT 32

static uint8_t volatile cap_index;
static uint32_t cap_val[SAMPLE_CNT >> 1][2];

void SysInit(void);
void UART0_Init(void);


 PWM_Capture (void)
{
    uint8_t i;

    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SysInit();

    /* Init UART to 115200-8n1 for print message */
    UART0_Init();

    printf("\nPWM0 channel 2 will capture the output of PWM0 channel 0\n");
    printf("So, please connect GPIO port B8 with E8.\n");
    // PWM0 frequency is 25000Hz, duty 30%,
    PWM_ConfigOutputChannel(PWM0, 0, 25000, 30);

    // PWM2
    PWM_ConfigCaptureChannel(PWM0,2,50,0);

    // Enable output of channel 0
    PWM_EnableOutput(PWM0, PWM_CH_0_MASK);

    // Enable capture of channel 2
    PWM_EnableCapture(PWM0, PWM_CH_2_MASK);

    // Enable PWM channel 2 rising and falling edge capture interrupt
    PWM_EnableCaptureInt(PWM0,2,PWM_RISING_FALLING_LATCH_INT_ENABLE);
    NVIC_EnableIRQ(PWM0_IRQn);

    // Start
    PWM_Start(PWM0, (PWM_CH_0_MASK|PWM_CH_2_MASK));

    cap_index = 0;

    while(cap_index < SAMPLE_CNT);

    // Disable PWM channel 2 rising and falling edge capture interrupt
    PWM_DisableCaptureInt(PWM0,2,PWM_RISING_FALLING_LATCH_INT_ENABLE);

    // Stop
    PWM_Stop (PWM0, (PWM_CH_0_MASK|PWM_CH_2_MASK));

    printf("Captured data is as below.\n");
    printf("(rising : falling)\n");
    for(i = 1; i < (SAMPLE_CNT  >> 1); i++) {  // ignore first sampled data. it's wrong
        printf("%d, %d : %d\n", i, cap_val[i][0], cap_val[i][1]);
    }

    while(1);


}


void PWM0_IRQHandler(void)
{
    static uint8_t token = 0;
    uint32_t u32CapIntFlag;
    uint8_t u8Count = cap_index;

    if(u8Count >= SAMPLE_CNT)
        return;

    // Get channel 2 capture interrupt flag
    u32CapIntFlag = PWM_GetCaptureIntFlag(PWM0, 2);

    // Rising latch condition happened
    if ((u32CapIntFlag & PWM_RISING_LATCH_INT_FLAG) && token == 0) {
        cap_val[u8Count >> 1][0] = PWM_GET_CAPTURE_RISING_DATA(PWM0, 2);
        cap_index++;
        token = 1;
    }
    // Falling latch condition happened
    if ((u32CapIntFlag & PWM_FALLING_LATCH_INT_FLAG) && token == 1) {
        cap_val[u8Count >> 1][1] = PWM_GET_CAPTURE_FALLING_DATA(PWM0, 2);
        cap_index++;
        token = 0;
    }

    // Clear channel 2 capture interrupt flag
    PWM_ClearCaptureIntFlag(PWM0, 2, PWM_RISING_FALLING_LATCH_INT_FLAG);
}

/*---------------------------------------------------------------------------------------------------------*/
/* Init System Clock                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
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

#if 1
    SYS->PB_H_MFP &= ~( SYS_PB_H_MFP_PB14_MFP_Msk | SYS_PB_H_MFP_PB13_MFP_Msk);
    SYS->PB_H_MFP |= (SYS_PB_H_MFP_PB14_MFP_UART0_TX | SYS_PB_H_MFP_PB13_MFP_UART0_RX );
    UART0->BAUD = 0x67;              /* Baud Rate:115200  OSC:12MHz */
    //UART0->BAUD = 0x60;            /* Baud Rate:115200  OSC:11.0592 MHz */
    UART0->TLCTL = (UART0->TLCTL & ~0x3) | 0x3; /* character len is 8 bits */
    UART0->TLCTL |= (1<<2);
#endif

    /*  Set HCLK frequency 32MHz */
    CLK_SetCoreClock(32000000);

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable PWM clock */
    CLK_EnableModuleClock(PWM0_CH01_MODULE);
    CLK_EnableModuleClock(PWM0_CH23_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE,CLK_CLKSEL1_UART_S_HIRC,CLK_UART_CLK_DIVIDER(1));

    /* Set HCLK as PWM clock source */
    CLK_SetModuleClock(PWM0_CH01_MODULE, CLK_CLKSEL1_PWM0_CH01_S_HCLK, 0);
    CLK_SetModuleClock(PWM0_CH23_MODULE, CLK_CLKSEL1_PWM0_CH23_S_HCLK, 0);


    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PA multi-function pins for UART0 RXD and TXD */
    SYS->PB_L_MFP &= ~( SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB0_MFP_UART0_TX | SYS_PB_L_MFP_PB1_MFP_UART0_RX );

    /* Set PB multi-function pins for Clock Output */
    SYS->PB_H_MFP = ( SYS->PB_H_MFP & ~SYS_PB_H_MFP_PB12_MFP_Msk ) |  SYS_PB_H_MFP_PB12_MFP_CKO0;

    /* Set PB.8 and PE.8 multi-function pins for PWM channel 0 and 2 */
    SYS->PB_H_MFP = (SYS->PB_H_MFP & ~SYS_PB_H_MFP_PB8_MFP_Msk) | SYS_PB_H_MFP_PB8_MFP_PWM0_CH0;
    SYS->PE_H_MFP = (SYS->PE_H_MFP & ~SYS_PE_H_MFP_PE8_MFP_Msk) | SYS_PE_H_MFP_PE8_MFP_PWM0_CH2;

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



/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

