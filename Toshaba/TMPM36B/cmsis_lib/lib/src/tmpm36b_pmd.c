/**
 *******************************************************************************
 * @file    tmpm36b_pmd.c
 * @brief   This file provides API functions for PMD driver.
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_pmd.h"

#if defined(__TMPM36B_PMD_H)

/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @defgroup PMD
  * @brief PMD driver modules
  * @{
  */

/** @defgroup PMD_Private_Defines
  * @{
  */

#define PMD_MDEN_PWMEN_SET                  ((uint32_t)0x00000001)
#define PMD_MDEN_PWMEN_CLEAR                ((uint32_t)0x00000000)

#define PMD_CNTSTA_UPDWN_MASK               ((uint32_t)0x00000001)

#define PMD_MDCR_SYNTMD_MASK                ((uint32_t)0xFFFFFFDF)
#define PMD_MDCR_DTYMD_MASK                 ((uint32_t)0xFFFFFFEF)

#define PMD_MDOUT_UOC_MASK                  ((uint32_t)0xFFFFFEFC)
#define PMD_MDOUT_VOC_MASK                  ((uint32_t)0xFFFFFDF3)
#define PMD_MDOUT_WOC_MASK                  ((uint32_t)0xFFFFFBCF)
#define PMD_MDOUT_ALL_CLEAR                 ((uint32_t)0x00000000)

#define PMD_MDPOT_POLH_MASK                 ((uint32_t)0xFFFFFFF7)
#define PMD_MDPOT_POLL_MASK                 ((uint32_t)0xFFFFFFFB)
#define PMD_MDPOT_PSYNCS_MASK               ((uint32_t)0xFFFFFFFC)

#define PMD_EMGCR_EMGEN_SET                 ((uint32_t)0x00000001)
#define PMD_EMGCR_EMGEN_CLEAR               ((uint32_t)0xFFFFFFFE)
#define PMD_EMGCR_EMGCNT_MASK               ((uint32_t)0xFFFFF0FF)
#define PMD_EMGCR_INHEN_MASK                ((uint32_t)0xFFFFFFDF)
#define PMD_EMGCR_EMGMD_MASK                ((uint32_t)0xFFFFFFE7)
#define PMD_EMGCR_EMGRS_SET                 ((uint32_t)0x00000002)

#define PMD_EMGREL_DISABLE_COMMAND_1        ((uint32_t)0x0000005A)
#define PMD_EMGREL_DISABLE_COMMAND_2        ((uint32_t)0x000000A5)

#define PMD_EMGSTA_EMGI_MASK                ((uint32_t)0x00000002)
#define PMD_EMGSTA_EMGST_MASK               ((uint32_t)0x00000001)

#define PMD_TRGCR_TRG0MD_MASK               ((uint32_t)0xFFFFFFF8)
#define PMD_TRGCR_TRG0BE_MASK               ((uint32_t)0xFFFFFFF7)

#define PMD_TRGMD_EMGTGE_SET                ((uint32_t)0x00000001)
#define PMD_TRGMD_EMGTGE_CLEAR              ((uint32_t)0xFFFFFFFE)

static uint8_t t_PMDPortOutput[2][8] = {
    /*L_L    L_H   H_L    H_H   IPWM_PWM    IPWM_H     H_IPWM/PWM  PWM_IPWM *//*POLH POLL  = 00b */
    {0x03U, 0x02U, 0x01U, 0x00U, 0x03U, 0x02U, 0x01U, 0x00U},
    /*L_L   L_H    H_L    H_H   IPWM_PWM   L_PWM/IPWM   PWM_L       PWM_IPWM *//*POLH POLL  = 11b */
    {0x00U, 0x01U, 0x02U, 0x03U, 0x00U, 0x01U, 0x02U, 0x03U}
};
uint32_t t_MDOUTMask[4] = { PMD_MDOUT_UOC_MASK, PMD_MDOUT_VOC_MASK, PMD_MDOUT_WOC_MASK, 0U };


/** @} */
/* End of group PMD_Private_Defines */


/** @defgroup PMD_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group PMD_Private_FunctionPrototypes */

/** @defgroup PMD_Private_Functions
  * @{
  */

/** @} */
/* End of group group PMD_Private_Functions */

/** @defgroup PMD_Exported_Functions
  * @{
  */

/**
  * @brief  Enable the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval None.
  */
void PMD_Enable(TSB_MTPD_TypeDef * PMDx)
{
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Set MTPDxMDEN <PWMEN> to enable PMD operation */
    PMDx->MDEN = PMD_MDEN_PWMEN_SET;
}

/**
  * @brief  Disable the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval None.
  */
void PMD_Disable(TSB_MTPD_TypeDef * PMDx)
{
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Clear MTPDxMDEN <PWMEN> to disable PMD operation */
    PMDx->MDEN = PMD_MDEN_PWMEN_CLEAR;
}

/**
  * @brief  Set PMD port control of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  PortMode: The port output mode of PMD.
  *   This parameter can be one of the following values:
  *   PMD_PORT_HIGH_IMPEDANCE, PMD_PORT_PMD_OUTPUT.
  * @retval None.
  */
void PMD_SetPortControl(TSB_MTPD_TypeDef * PMDx, uint32_t PortMode)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_PORT_MODE(PortMode));
    /* Set MTPDxPORTMD <PORTMD> to control PMD port mode */
    PMDx->PORTMD = PortMode;
}

/**
  * @brief  Initialize the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  InitStruct: The structure containing basic PMD configuration.
  * @retval None.
  */
void PMD_Init(TSB_MTPD_TypeDef * PMDx, PMD_InitTypeDef * InitStruct)
{
    uint32_t tmp = 0U;
    tmp = PMDx->MDCR & (~PMD_MDCR_SYNTMD_MASK);
    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_CYCLE_MODE(InitStruct->CycleMode));
    assert_param(IS_PMD_DUTY_MODE(InitStruct->DutyMode));
    assert_param(IS_PMD_CARRIER_WAVE_MODE(InitStruct->CarrierMode));
    assert_param(IS_PMD_VALUE(InitStruct->CycleTiming));
    /* Set MTPDxMDCR <PWMMD> to specify PWM carrier wave */
    tmp |= InitStruct->CarrierMode;
    /* Judge the PWM carrier wave */
    if (InitStruct->CarrierMode == PMD_CARRIER_WAVE_MODE_1) {
        /* Check the parameters */
        assert_param(IS_PMD_PWM_INT_TIMING(InitStruct->IntTiming));
        assert_param(IS_PMD_PWM_INT_CYCLE_MODE_1(InitStruct->IntCycle));
        /* Set MTPDxMDCR <PINT> to choose PWM interrupt timing when PWM mode 1 (triangle wave) is set */
        tmp |= (InitStruct->IntTiming << 3U);
    } else {
        /* Check the parameter */
        assert_param(IS_PMD_PWM_INT_CYCLE_MODE_0(InitStruct->IntCycle));
    }
    /* Set MTPDxMDCR <PWMCK> to specify PWM cycle extension mode */
    tmp |= (InitStruct->CycleMode << 6U);
    /* Set MTPDxMDCR <DTYMD> to choose DUTY mode */
    tmp |= (InitStruct->DutyMode << 4U);
    /* Set MTPDxMDCR <INTPRD> to choose PWM interrupt cycle */
    tmp |= (InitStruct->IntCycle << 1U);
    PMDx->MDCR = tmp;
    /* Specify MTPDxMDPRD <MDPRD> to set PWM cycle */
    PMDx->MDPRD = InitStruct->CycleTiming;
}

/**
  * @brief  Change the PWM cycle of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  CycleTiming: PWM cycle, from 0x0000 to 0xFFFF
  * @retval None.
  */
void PMD_ChangePWMCycle(TSB_MTPD_TypeDef * PMDx, uint32_t CycleTiming)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_VALUE(CycleTiming));
    /* Specify MTPDxMDPRD <MDPRD> to set PWM cycle */
    PMDx->MDPRD = CycleTiming;
}

/**
  * @brief  Get the PWM counter flag of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval The PWM counter flag.
  *   The value returned can be one of the following values:
  *   PMD_COUNTER_UP, PMD_COUNTER_DOWN.
  */
uint32_t PMD_GetCntFlag(TSB_MTPD_TypeDef * PMDx)
{
    uint32_t tmp = 0U;
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Read MTPDxCNTSTA <UPDWN> to get the PWM counter flag */
    tmp = PMDx->CNTSTA & PMD_CNTSTA_UPDWN_MASK;
    return tmp;
}


/**
  * @brief  Get the count value of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval Count value of the specified PMD channel.
  */
uint16_t PMD_GetCntValue(TSB_MTPD_TypeDef * PMDx)
{
    uint16_t tmp = 0U;
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Read MTPDxMDCNT <MDCNT> to get the count value */
    tmp = (uint16_t) PMDx->MDCNT;
    return tmp;
}

/**
  * @brief  Set the compare value of the specified phase of the specified PMD channel. 
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  PMDPhase: Select the phase of PMD channel.
  *   This parameter can be one of the following values:
  *   PMD_PHASE_U, PMD_PHASE_V, PMD_PHASE_W, PMD_PHASE_ALL.
  * @param  Timing: Compare value, from 0x0000 to 0xFFFF.
  * @retval None.
  */
void PMD_SetCompareValue(TSB_MTPD_TypeDef * PMDx, uint32_t PMDPhase, uint32_t Timing)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_PHASE(PMDPhase));
    assert_param(IS_PMD_VALUE(Timing));
    /* Judge the phase */
    switch (PMDPhase) {
    case PMD_PHASE_U:
        /* Set MTPDxCMPU <CMPU> to specify compare value in phase U */
        PMDx->CMPU = Timing;
        break;
    case PMD_PHASE_V:
        /* Set MTPDxCMPV <CMPV> to specify compare value in phase V */
        PMDx->CMPV = Timing;
        break;
    case PMD_PHASE_W:
        /* Set MTPDxCMPW <CMPW> to specify compare value in phase W */
        PMDx->CMPW = Timing;
        break;
    case PMD_PHASE_ALL:
        /* Set MTPDxCMPU <CMPU> to specify compare value in phase U */
        PMDx->CMPU = Timing;
        /* Set MTPDxCMPV <CMPV> to specify compare value in phase V */
        PMDx->CMPV = Timing;
        /* Set MTPDxCMPW <CMPW> to specify compare value in phase W */
        PMDx->CMPW = Timing;
        break;
    default:
        /* Do nothing */
        break;
    }
}

/**
  * @brief  Set the mode of port output of the specified PMD channel. 
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  Mode: The mode of port output.
  *   This parameter can be one of the following values:
  *   PMD_PORT_OUTPUT_MODE_0, PMD_PORT_OUTPUT_MODE_1.
  * @retval None.
  */
void PMD_SetPortOutputMode(TSB_MTPD_TypeDef * PMDx, uint32_t Mode)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_PORT_OUTPUT_MODE(Mode));
    /* Set MTPDxMDCR <SYNTMD> to choose port output mode */
    tmp = PMDx->MDCR & PMD_MDCR_SYNTMD_MASK;
    tmp |= (Mode << 5U);
    PMDx->MDCR = tmp;
}

/**
  * @brief  Set polarity of the specified output port phase of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  OutputPhase: Select the specified output port phase.
  *   This parameter can be one of the following values:
  *   PMD_OUTPUT_PHASE_LOWER, PMD_OUTPUT_PHASE_UPPER.
  * @param  Polarity: Select the polarity.
  *   This parameter can be one of the following values:
  *   PMD_POLARITY_LOW, PMD_POLARITY_HIGH.
  * @retval None.
  */
void PMD_SetOutputPhasePolarity(TSB_MTPD_TypeDef * PMDx, uint32_t OutputPhase, uint32_t Polarity)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_OUTPUT_PHASE(OutputPhase));
    assert_param(IS_PMD_POLARITY(Polarity));
    /* Judge the output port phase */
    if (OutputPhase == PMD_OUTPUT_PHASE_UPPER) {
        /* Specify MTPDxMDPOT <POLH> to select the polarity */
        tmp = PMDx->MDPOT & PMD_MDPOT_POLH_MASK;
        tmp |= (Polarity << 3U);
        PMDx->MDPOT = tmp;
    } else {
        /* Specify MTPDxMDPOT <POLL> to select the polarity */
        tmp = PMDx->MDPOT & PMD_MDPOT_POLL_MASK;
        tmp |= (Polarity << 2U);
        PMDx->MDPOT = tmp;
    }
}

/**
  * @brief  Choose the timing when port outputs of U-, V- and W- phase output setting is reflected of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  ReflectedTime: Select the reflected time.
  *   This parameter can be one of the following values:
  *   PMD_REFLECTED_TIME_WRITE, PMD_REFLECTED_TIME_MIN,
  *   PMD_REFLECTED_TIME_MAX, PMD_REFLECTED_TIME_MIN_MAX.
  * @retval None.
  */
void PMD_SetReflectTime(TSB_MTPD_TypeDef * PMDx, uint32_t ReflectedTime)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_REFLECTED_TIME(ReflectedTime));
    /* Specify MTPDxMDPOT <PSYNCS> to select the reflected time */
    tmp = PMDx->MDPOT & PMD_MDPOT_PSYNCS_MASK;
    tmp |= ReflectedTime;
    PMDx->MDPOT = tmp;
}

/**
  * @brief  Enable EMG protection of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval None.
  */
void PMD_EnableEMG(TSB_MTPD_TypeDef * PMDx)
{
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Set MTPDxEMGCR <EMGEN> to enable EMG protection */
    PMDx->EMGCR |= PMD_EMGCR_EMGEN_SET;
}

/**
  * @brief  Disable EMG protection of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval None.
  */
void PMD_DisableEMG(TSB_MTPD_TypeDef * PMDx)
{
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* To prohibit EMG function, three instructions must be executed consecutively */
    /* Step1: Set "0x5A" to MTPDxEMGREL <EMGREL> */
    PMDx->EMGREL = PMD_EMGREL_DISABLE_COMMAND_1;
    /* Step2: Set "0xA5" to MTPDxEMGREL <EMGREL> */
    PMDx->EMGREL = PMD_EMGREL_DISABLE_COMMAND_2;
    /* Step3: Set "0" to MTPDxEMGCR <EMGEN> */
    PMDx->EMGCR &= PMD_EMGCR_EMGEN_CLEAR;
}

/**
  * @brief  Set the noise elimination time for abnormal condition detection input of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  NoiseElimination: Select the noise elimination time.
  *   This parameter can be one of the following values:
  *   PMD_NOISE_ELIMINATION_NONE, PMD_NOISE_ELIMINATION_16, PMD_NOISE_ELIMINATION_32,
  *   PMD_NOISE_ELIMINATION_48, PMD_NOISE_ELIMINATION_64, PMD_NOISE_ELIMINATION_80,
  *   PMD_NOISE_ELIMINATION_96, PMD_NOISE_ELIMINATION_112, PMD_NOISE_ELIMINATION_128,
  *   PMD_NOISE_ELIMINATION_144, PMD_NOISE_ELIMINATION_160, PMD_NOISE_ELIMINATION_176,
  *   PMD_NOISE_ELIMINATION_192, PMD_NOISE_ELIMINATION_208, PMD_NOISE_ELIMINATION_224,
  *   PMD_NOISE_ELIMINATION_240.
  * @retval None.
  */
void PMD_SetEMGNoiseElimination(TSB_MTPD_TypeDef * PMDx, uint32_t NoiseElimination)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_NOISE_ELIMINATION(NoiseElimination));
    /* Set MTPDxEMGCR <EMGCNT> to select the noise elimination time */
    tmp = PMDx->EMGCR & PMD_EMGCR_EMGCNT_MASK;
    tmp |= (NoiseElimination << 8U);
    PMDx->EMGCR = tmp;
}

/**
  * @brief  Choose PMD output status at tool break of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  Status: PMD output status at tool break.
  *   This parameter can be one of the following values:
  *   PMD_BREAK_STATUS_PMD, PMD_BREAK_STATUS_HIGH_IMPEDANCE.
  * @retval None.
  */
void PMD_SetToolBreakOutput(TSB_MTPD_TypeDef * PMDx, uint32_t Status)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_BREAK_STATUS(Status));
    /* Set MTPDxEMGCR <INHEN> to select output status */
    tmp = PMDx->EMGCR & PMD_EMGCR_INHEN_MASK;
    tmp |= (Status << 5U);
    PMDx->EMGCR = tmp;
}

/**
  * @brief  Set EMG protection mode of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  Mode: EMG protection mode.
  *   This parameter can be one of the following values:
  *   PMD_EMG_MODE_0, PMD_EMG_MODE_1, PMD_EMG_MODE_2, PMD_EMG_MODE_3.
  * @retval None.
  */
void PMD_SetEMGMode(TSB_MTPD_TypeDef * PMDx, uint32_t Mode)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_EMG_MODE(Mode));
    /* Set MTPDxEMGCR <EMGMD> to select EMG protection mode */
    tmp = PMDx->EMGCR & PMD_EMGCR_EMGMD_MASK;
    tmp |= (Mode << 3U);
    PMDx->EMGCR = tmp;
}

/**
  * @brief  Release EMG protection status of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval None.
  */
void PMD_EMGRelease(TSB_MTPD_TypeDef * PMDx)
{
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* There are two steps to release EMG protection */
    /* Step1: Set MTPDxMDOUT<WPWM><VPWM><UPWM><WOC><VOC><UOC> to 0 */
    PMDx->MDOUT = PMD_MDOUT_ALL_CLEAR;
    /* Step2: Set MTPDxEMGCR <EMGRS> to release EMG protection */
    PMDx->EMGCR |= PMD_EMGCR_EMGRS_SET;
}

/**
  * @brief  Get the level of abnormal condition input of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval The level of abnormal condition input.
  *   The value returned can be one of the following values:
  *   PMD_ABNORMAL_LEVEL_L, PMD_ABNORMAL_LEVEL_H.
  */
uint32_t PMD_GetEMGAbnormalLevel(TSB_MTPD_TypeDef * PMDx)
{
    uint32_t tmp = 0U;
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Read MTPDxEMGSTA <EMGI> to get the level of abnormal condition input */
    tmp = PMDx->EMGSTA & PMD_EMGSTA_EMGI_MASK;
    return tmp;
}

/**
  * @brief  Get the EMG protection condition of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @retval The EMG protection condition.
  *   The value returned can be 0 or 1.
  *   0 means normal operation.
  *   1 means during in EMG protection.
  */
uint32_t PMD_GetEMGCondition(TSB_MTPD_TypeDef * PMDx)
{
    uint32_t tmp = 0U;
    /* Check the parameter */
    assert_param(IS_PMD_PERIPH(PMDx));
    /* Read MTPDxEMGSTA <EMGST> to get the EMG protection condition */
    tmp = PMDx->EMGSTA & PMD_EMGSTA_EMGST_MASK;
    return tmp;
}

/**
  * @brief  Set dead time of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  Time: Dead time, from 0x00 to 0xFF.
  * @retval None.
  */
void PMD_SetDeadTime(TSB_MTPD_TypeDef * PMDx, uint32_t Time)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_DEAD_TIME(Time));
    /* Set MTPDxDTR <DTR> to select dead time */
    PMDx->DTR = Time;
}

/**
  * @brief  Set the compare values of the all phases of the specified PMD channel. 
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  UPhaseTiming: Compare value of phase U, from 0x0000 to 0xFFFF.
  * @param  VPhaseTiming: Compare value of phase V, from 0x0000 to 0xFFFF.
  * @param  WPhaseTiming: Compare value of phase W, from 0x0000 to 0xFFFF.
  * @retval None.
  */
void PMD_SetAllPhaseCompareValue(TSB_MTPD_TypeDef * PMDx, uint32_t UPhaseTiming,
                                 uint32_t VPhaseTiming, uint32_t WPhaseTiming)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_VALUE(UPhaseTiming));
    assert_param(IS_PMD_VALUE(VPhaseTiming));
    assert_param(IS_PMD_VALUE(WPhaseTiming));

    /* Set MTPDxCMPU <CMPU> to specify compare value in phase U */
    PMDx->CMPU = UPhaseTiming;
    /* Set MTPDxCMPV <CMPV> to specify compare value in phase V */
    PMDx->CMPV = VPhaseTiming;
    /* Set MTPDxCMPW <CMPW> to specify compare value in phase W */
    PMDx->CMPW = WPhaseTiming;
}

/**
  * @brief  Change duty mode of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  DutyMode: The duty mode of PMD.
  *   This parameter can be one of the following values:
  *   PMD_DUTY_MODE_U_PHASE, PMD_DUTY_MODE_3_PHASE.
  * @retval None.
  */
void PMD_ChangeDutyMode(TSB_MTPD_TypeDef * PMDx, uint32_t DutyMode)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_DUTY_MODE(DutyMode));
    /* Change MTPDxMDCR <DTYMD> to choose DUTY mode */
    tmp = PMDx->MDCR & PMD_MDCR_DTYMD_MASK;
    tmp |= (DutyMode << 4U);
    PMDx->MDCR = tmp;
}

/**
  * @brief  Set the specified output of the specified phase of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  PMDPhase: Select the phase of PMD channel.
  *   This parameter can be one of the following values:
  *   PMD_PHASE_U, PMD_PHASE_V, PMD_PHASE_W, PMD_PHASE_ALL.
  * @param  Output: Select the output.
  *   This parameter can be one of the following values:
  *   0: PMD_OUTPUT_L_L,  1: PMD_OUTPUT_L_H,        2: PMD_OUTPUT_H_L,
  *   3: PMD_OUTPUT_H_H,  4: PMD_OUTPUT_PWM_IPWM,
  *   5: PMD_OUTPUT_L_PWM/PMD_OUTPUT_L_IPWM/PMD_OUTPUT_IPWM_H,
  *   6: PMD_OUTPUT_PWM_L/PMD_OUTPUT_H_IPWM/PMD_OUTPUT_H_PWM,
  *   7: PMD_OUTPUT_PWM_IPWM.
  * @retval  Success or not
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result PMD_SetPortOutput(TSB_MTPD_TypeDef * PMDx, uint32_t PMDPhase, uint8_t Output)
{
    Result retval = ERROR;
    uint8_t fPOLHL = 0U;
    uint32_t value_PWM = 0U;
    uint32_t value_OC = 0U;
    uint32_t reg = 0U;

    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_PHASE(PMDPhase));
    assert_param(IS_PMD_OUTPUT(Output));

    /* Get the value of MTPDxMDPOT <POLH> and MTPDxMDPOT <POLL> */
    fPOLHL = (uint8_t) (PMDx->MDPOT >> 2U);
    fPOLHL &= 0x03U;

    value_PWM = (uint32_t) Output / 4U;
    reg = PMDx->MDOUT & t_MDOUTMask[PMDPhase];

    if ((fPOLHL == 3U) || (fPOLHL == 0U)) {
        fPOLHL >>= 1U;
        value_OC = (uint32_t) t_PMDPortOutput[fPOLHL][Output];
        value_PWM <<= 8U;
        if (PMDPhase == PMD_PHASE_ALL) {
            reg = value_OC | (value_OC << 2U) | (value_OC << 4U) |
                value_PWM | (value_PWM << 1U) | (value_PWM << 2U);
        } else {
            value_PWM <<= PMDPhase;
            PMDPhase <<= 1U;
            reg |= (value_PWM | (value_OC << PMDPhase));
        }
        PMDx->MDOUT = reg;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }
    return retval;
}

/**
  * @brief  Set the ADC trigger compare registers' value of the specified PMD channel. 
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  TRGCMP0Timing: Value of ADC trigger compare register 0, from 0x0001 to [MDPRD set value ¨C 1].
  * @retval None.
  * @note MTPDxTRGCMP0 should be set in a range of 1 to [MDPRD set value ¨C 1].
  */
void PMD_SetTrgCmpValue(TSB_MTPD_TypeDef * PMDx, uint32_t TRGCMP0Timing)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_VALUE(TRGCMP0Timing));

    /* Set MTPDxTRGCMP0 <TRGCMP0> */
    PMDx->TRGCMP0 = TRGCMP0Timing;
}

/**
  * @brief  Set trigger mode of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  PMDTrg: Select the PMD Trigger.
  *   This parameter can be one of the following values:
  *   PMD_ADC_TRG_0.
  * @param  Mode: PMD trigger mode.
  *   This parameter can be one of the following values:
  *   PMD_TRG_MODE_0, PMD_TRG_MODE_1, PMD_TRG_MODE_2, PMD_TRG_MODE_3,
  *   PMD_TRG_MODE_4, PMD_TRG_MODE_5, PMD_TRG_MODE_6, PMD_TRG_MODE_7.
  * @retval None.
  */
void PMD_SetTrgMode(TSB_MTPD_TypeDef * PMDx, uint32_t PMDTrg, uint32_t Mode)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_ADC_TRG(PMDTrg));
    assert_param(IS_PMD_TRG_MODE(Mode));

    /* Set MTPDxTRGCR <TRG0MD> to select trigger 0 mode */
    tmp = PMDx->TRGCR & PMD_TRGCR_TRG0MD_MASK;
    tmp |= (Mode << 0U);
    PMDx->TRGCR = tmp;
}

/**
  * @brief  Set trigger buffer update timing of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  PMDTrg: Select the PMD Trigger.
  *   This parameter can be one of the following values:
  *   PMD_ADC_TRG_0.
  * @param  UpdateTiming: PMDTRG0 to PMDTRG1 buffer update timing.
  *   This parameter can be one of the following values:
  *   PMD_TRG_UPDATE_SYNC, PMD_TRG_UPDATE_ASYNC.
  * @retval None.
  */
void PMD_SetTrgUpdate(TSB_MTPD_TypeDef * PMDx, uint32_t PMDTrg, uint32_t UpdateTiming)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_PMD_ADC_TRG(PMDTrg));
    assert_param(IS_PMD_TRG_TIMING(UpdateTiming));

    /* Set MTPDxTRGCR <TRG0BE> to select trigger 0 buffer update timing */
    tmp = PMDx->TRGCR & PMD_TRGCR_TRG0BE_MASK;
    tmp |= (UpdateTiming << 3U);
    PMDx->TRGCR = tmp;

}

/**
  * @brief  Enable or disable trigger output in EMG protection state of the specified PMD channel.
  * @param  PMDx: Select the PMD channel.
  *   This parameter can be one of the following values:
  *   PMD0.
  * @param  NewState: Output enable in EMG protection state.
  *   This parameter can be one of the following values:
  *   ENABLE, DIABLE.
  * @retval None.
  */
void PMD_SetEMGTrg(TSB_MTPD_TypeDef * PMDx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PMD_PERIPH(PMDx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        PMDx->TRGMD |= PMD_TRGMD_EMGTGE_SET;
    } else {
        PMDx->TRGMD &= PMD_TRGMD_EMGTGE_CLEAR;
    }
}

/** @} */
/* End of group PMD_Exported_Functions */

/** @} */
/* End of group PMD */

/** @} */
/* End of group TX03_Periph_Driver */

#endif                          /* defined(__TMPM36B_PMD_H) */
