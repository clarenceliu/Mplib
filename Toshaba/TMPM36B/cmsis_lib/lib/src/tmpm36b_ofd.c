/**
 *******************************************************************************
 * @file    tmpm36b_ofd.c
 * @brief   This file provides API functions for OFD driver.
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_ofd.h"

#if defined(__TMPM36B_OFD_H)

/** @addtogroup TX03_Periph_Driver
  * @{
  */
/** @defgroup OFD
  * @brief OFD driver modules
  * @{
  */

/** @defgroup OFD_Private_Defines
  * @{
  */
#define OFD_REG_WRITE_DISABLE ((uint32_t)0x00000006U)
#define OFD_REG_WRITE_ENABLE  ((uint32_t)0x000000F9U)
#define OFD_DISABLE           ((uint32_t)0x00000000U)
#define OFD_ENABLE            ((uint32_t)0x000000E4U)
/** @} */
/* End of group OFD_Private_Defines */

/** @defgroup OFD_Exported_Functions
  * @{
  */

/**
  * @brief  Enable or disable the writing of all OFD registers except OFDCR1.
  * @param  NewState: the new state of enable or disable
  *   This parameter can be one of the following values:
  *   ENABLE or DISABLE
  * @retval None
  */
void OFD_SetRegWriteMode(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Set OFDCR1<OFDWEN0-7> to enable or disable the writing of OFDCR2/OFDMN/OFDMX. */
    if (NewState == ENABLE) {
        TSB_OFD->CR1 = OFD_REG_WRITE_ENABLE;
    } else {
        TSB_OFD->CR1 = OFD_REG_WRITE_DISABLE;
    }
}

/**
  * @brief  Enable the OFD function.
  * @param  None
  * @retval None
  */
void OFD_Enable(void)
{
    /* OFDCR2<OFDEN0-7> = 0xE4 */
    TSB_OFD->CR2 = OFD_ENABLE;
}

/**
  * @brief  Disable the OFD function.
  * @param  None
  * @retval None
  */
void OFD_Disable(void)
{
    /* OFDCR2<OFDEN0-7> = 0x00 */
    TSB_OFD->CR2 = OFD_DISABLE;
}

/**
  * @brief  Set the count value for higher and lower of detection frequency for internal or external oscillation.
  * @param  Source: select internal or external oscillation source for the count value setting.
  *   This parameter can be one of the following values:
  *   OFD_IHOSC or OFD_EHOSC
  *   HigherDetectionCount: the count value of higher detection frequency, Max is 0x1FFU.
  *   LowerDetectionCount: the count value of lower detection frequency, Max is 0x1FFU.
  * @retval None
  */
void OFD_SetDetectionFrequency(OFD_OSCSource Source, uint32_t HigherDetectionCount,
                               uint32_t LowerDetectionCount)
{
    assert_param(IS_OFD_OSC_SOURCE(Source));
    assert_param(IS_OFD_DETECT_FREQ_HIGHER(HigherDetectionCount));
    assert_param(IS_OFD_DETECT_FREQ_HIGHER(LowerDetectionCount));

    /* Set the OFDMNy<OFDMN0-8> and OFDMXy<OFDMX0-8> bits. y = 0 or 1 */
    if (Source == OFD_IHOSC) {
        TSB_OFD->MN0 = (uint32_t) LowerDetectionCount;
        TSB_OFD->MX0 = (uint32_t) HigherDetectionCount;
    } else {
        TSB_OFD->MN1 = (uint32_t) LowerDetectionCount;
        TSB_OFD->MX1 = (uint32_t) HigherDetectionCount;
    }
}

/**
  * @brief  Enable or disable the OFD reset.
  * @param  NewState: the new state of enable or disable
  *   This parameter can be one of the following values:
  *   ENABLE or DISABLE
  * @retval None
  */
void OFD_Reset(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Set OFDRST<OFDRSTEN> to enable or disable the OFD reset. */
    if (NewState == ENABLE) {
        TSB_OFD_RST_OFDRSTEN = 1U;
    } else {
        TSB_OFD_RST_OFDRSTEN = 0U;
    }
}

/**
  * @brief  Get the OFD run/stop and frequency error information
  * @param  None
  * @retval The structure includes the OFD run/stop and frequency error status.
  */
OFD_Status OFD_GetStatus(void)
{
    OFD_Status status = { 0U };

    /*Read the ofd status from OFDSTAT<OFDBUSY><FRQEER> register. */
    status.All = TSB_OFD->STAT;
    return status;
}

/**
  * @brief  Set the external high frequency oscillation clock monitor register to select intended detection mode.
  * @param  Mode: Select intended detection mode.
  *   This parameter can be one of the following values:
  *   OFD_NORMAL or OFD_MONITOR 
  * @retval None
  */
void OFD_SetDetectionMonitor(OFD_MonitorMode Mode)
{
    assert_param(IS_OFD_MONITOR_MODE(Mode));
    if (Mode == OFD_NORMAL) {
        TSB_OFD_MON_OFDMON = 0U;
    } else {
        TSB_OFD_MON_OFDMON = 1U;
    }
}

/** @} */
/* End of group OFD_Exported_Functions */
/** @} */
/* End of group OFD */
/** @} */
/* End of group TX03_Periph_Driver */

#endif                          /* defined(__TMPM36B_OFD_H) */
