/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of PMD_PHASE_OUTPUT demo for the TOSHIBA 'TMPM36B'
 *          Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Include -------------------------------------------------------------------*/
#include "PMD_PHASE_OUTPUT.h"

/* Global variable define ----------------------------------------------------*/
volatile uint32_t gState = 0U;

/* Choose one demo to define */
/* #define DEMO_U_PHASE */          /* U-, V-, W- phases are same in this demo */
#define DEMO_3_PHASE            /* U-, V-, W- phases are not same in this demo */

/**
  * @brief  Main function
  * @param  None
  * @retval None
  */
int PMD_PHASE_OUTPUT(void)
{
    /* LED initialization */
    LED_Init();

    /* GPIO configuration */
    PMD_IO_Config();

    /* PMD PWM configuration */
    PMD_PWM_Config();

    /* Enable PMD0 */
    PMD_Enable(PMD0);

    while (1) {
        /* Get the EMG protection condition */
        gState = PMD_GetEMGCondition(PMD0);
        /* Judge the EMG protection condition */
        if (gState == EMG_PROTECTION) {
            /* LED1 will light on if the condition is in protection */
            LED_On(LED1);
            /* Back EMG protection to normal */
            PMD_BackToNormal();
            Delay(1000U);
        } else {
            /* LED1 will light off if the condition is not in protection */
            LED_Off(LED1);
        }
    }
}

/**
  * @brief  PMD PWM configuration
  * @param  None.
  * @retval None.
  */
void PMD_PWM_Config(void)
{
    PMD_InitTypeDef m_pmd;

    /* PMD0 initialization */
    m_pmd.CycleMode = PMD_PWM_NORMAL_CYCLE;
#ifdef DEMO_U_PHASE
    m_pmd.DutyMode = PMD_DUTY_MODE_U_PHASE;     /* U-phase in common */
#endif
#ifdef DEMO_3_PHASE
    m_pmd.DutyMode = PMD_DUTY_MODE_3_PHASE;     /* 3-phase independent */
#endif
    m_pmd.IntTiming = PMD_PWM_INT_TIMING_MINIMUM;
    m_pmd.IntCycle = PMD_PWM_INT_CYCLE_1;
    m_pmd.CarrierMode = PMD_CARRIER_WAVE_MODE_1;        /* PWM mode 1 (center PWM, triangle wave) */
    m_pmd.CycleTiming = 0x3FFFU;

    PMD_Init(PMD0, &m_pmd);

    PMD_SetAllPhaseCompareValue(PMD0, 0x0FFFU, 0x1FFFU, 0x2FFFU);
    PMD_SetPortOutput(PMD0, PMD_PHASE_ALL, PMD_OUTPUT_PWM_IPWM);
    PMD_SetPortControl(PMD0, PMD_PORT_PMD_OUTPUT);
    PMD_SetEMGMode(PMD0, PMD_EMG_MODE_0);
    PMD_EnableEMG(PMD0);
    PMD_SetDeadTime(PMD0, DEAD_TIME);
    PMD_SetEMGNoiseElimination(PMD0, PMD_NOISE_ELIMINATION_240);
}

/**
  * @brief  GPIO configuration
  * @param  None.
  * @retval None.
  */
void PMD_IO_Config(void)
{
    /* Set PG7-PG2 as output */
    GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_7 | GPIO_BIT_6 | GPIO_BIT_5 | GPIO_BIT_4 | GPIO_BIT_3 | GPIO_BIT_2, ENABLE);
    /* Set PG7-PG2 as UO0 X00 VO0 YO0 WO0 ZO0 */
    GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_2, GPIO_BIT_7 | GPIO_BIT_6 | GPIO_BIT_5 | GPIO_BIT_4 | GPIO_BIT_3 | GPIO_BIT_2);
    /* Set PG1 as input */
    GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_1, ENABLE);
    /* Set PG1 as EMG0 */
    GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_2, GPIO_BIT_1);

    /* Before config PG1 as EMG0 input, thg EMG0 input level is "L" and the EMG0 is in protection. */
    /* Therefore, it is necessary to release EMG protection status. */
    PMD_EMGRelease(PMD0);
}

/**
  * @brief  Back EMG protection to normal
  * @param  None.
  * @retval None.
  */
void PMD_BackToNormal(void)
{
    PMD_EMGRelease(PMD0);
    /* After calling the function PMD_EMGRelease(), the output selection is cleared to 0 */
    /* Therefore, it is necessary to set again */
    PMD_SetPortOutput(PMD0, PMD_PHASE_ALL, PMD_OUTPUT_PWM_IPWM);
}

/**
  * @brief  Delay time
  * @param  time.
  * @retval None.
  */
void Delay(uint32_t time)
{
    volatile uint32_t TimeCounter = 0U;
    uint32_t DelayTime = 0U;

    DelayTime = time * 800U;
    for (TimeCounter = 0U; TimeCounter < DelayTime; TimeCounter++) {
        /* Do nothing */
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    __NOP();
}
#endif
