/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of OFD demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

//#define ABNORMAL_DEMO
#include "OFD_example.h"

/* declaration ---------------------------------------------------------------*/
void ChangeToEHOSC(void);
void Delay(void);

/**
  * @brief  The main routine of OFD demo
  * @param  None
  * @retval None
  */
int OFD_example(void)
{
    uint8_t OFDReset = 0U;
    CG_ResetFlag resetFlag = { 0U };
    OFD_Status OFD_St = { 0U };
    LED_Init();
    resetFlag = CG_GetResetFlag();
    if (resetFlag.Bit.OFDReset == 0U) {
        /*Change to external oscillator */
        ChangeToEHOSC();
        /* OFD initial */
        OFD_SetRegWriteMode(ENABLE);
        OFD_Disable();
        OFD_Reset(DISABLE);
        OFD_SetDetectionMonitor(OFD_MONITOR);
        OFD_SetDetectionFrequency(OFD_IHOSC, OFD_HIGHER_COUNT_10M, OFD_LOWER_COUNT_10M);
#ifdef ABNORMAL_DEMO
        OFD_SetDetectionFrequency(OFD_EHOSC, OFD_HIGHER_COUNT_ABNORMAL, OFD_LOWER_COUNT_ABNORMAL);
#else
        OFD_SetDetectionFrequency(OFD_EHOSC, OFD_HIGHER_COUNT_NORMAL, OFD_LOWER_COUNT_NORMAL);
#endif

        OFD_Enable();
        while (OFD_St.Bit.OFDBusy == 0U) {
            OFD_St = OFD_GetStatus();
        }
        if (OFD_St.Bit.FrequencyError == 0U) {
            OFD_Disable();
            OFD_SetDetectionMonitor(OFD_NORMAL);
            OFD_Reset(ENABLE);
            OFD_Enable();
            OFD_SetRegWriteMode(DISABLE);
        } else {
            /* Do nothing */
        }
    } else {
        OFD_Disable();
        OFDReset = 1U;
    }
    while (1U) {
        if (OFDReset == 1U) {
            LED_On(LED2);
            Delay();
            LED_Off(LED2);
            Delay();
        } else {
            LED_On(LED1);
            Delay();
            LED_Off(LED1);
            Delay();
        }
    }
}

/**
  * @brief  Change the system clock to external oscillator.
  * @param  None
  * @retval None
  */
void ChangeToEHOSC(void)
{
    /* Use the external oscillation */
    TSB_CG->OSCCR &= 0x000FFFFFUL;
    TSB_CG->OSCCR |= 0xFFF00000UL;      /*Set the warm up time WUODR[13:2] */
    TSB_CG_OSCCR_EHOSCSEL = 1U;   /*Select external crystal oscillator */
    TSB_CG_OSCCR_XEN1 = 1U;     /*Enable external oscillator */
    TSB_CG_OSCCR_WUPSEL2 = 1U;
    TSB_CG_OSCCR_WUPSEL1 = 0U;  /*Select warm-up clock */
    TSB_CG_OSCCR_WUEON = 1U;    /*Start warm up */
    while (TSB_CG_OSCCR_WUEF) {
    }                           /* Warm-up */
    TSB_CG_OSCCR_OSCSEL = 1U;   /* Use the external oscillation */
    TSB_CG_OSCCR_XEN2 = 1U;     /* Enable internal oscillator for OFD */
}

/**
  * @brief  Delay.
  * @param  None
  * @retval None
  */
void Delay(void)
{
    uint32_t tmp;
    for (tmp = 0U; tmp < 0x5ffffU; tmp++);

}

/**
 * @brief Initialize the system
 * @param  none
 * @return none
 */
void System_Init(void)
{
#if (WD_SETUP)                  /* Watchdog Setup */
    TSB_WD->MOD = WDMOD_Val;
    if (!TSB_WD_MOD_WDTE) {     /* If watchdog is to be disabled */
        TSB_WD->CR = WDCR_Val;
    }
#endif
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
    while (1U) {
        __NOP();
    }
}
#endif
