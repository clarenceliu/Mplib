/**
 *******************************************************************************
 * @file    tmpm037_wdt.c
 * @brief   This file provides API functions for WDT driver.
 * @version V2.0.2.1
 * @date    2014/02/11
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_wdt.h"


#if defined(__TMPM037_WDT_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @defgroup WDT 
  * @brief WDT driver modules
  * @{
  */
/** @defgroup WDT_Private_Defines
  * @{
  */

#define WDT_CR_CLR_CODE        ((uint32_t)0x0000004E)
#define WDT_CR_DISABLE_CODE    ((uint32_t)0x000000B1)

#define MOD_WDTP_MASK          ((uint32_t)0x00000086)
#define MOD_I2WDT_SET          ((uint32_t)0x00000004)
#define MOD_I2WDT_CLEAR        ((uint32_t)0xFFFFFFFB)
#define MOD_RESCR_SET          ((uint32_t)0x00000002)
#define MOD_RESCR_CLEAR        ((uint32_t)0xFFFFFFFD)
#define MOD_WDTE_SET           ((uint32_t)0x00000080)
#define MOD_WDTE_CLEAR         ((uint32_t)0xFFFFFF7F)

/** @} */
/* End of group WDT_Private_Defines */

/** @defgroup WDT_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group WDT_Private_FunctionPrototypes */

/** @defgroup WDT_Private_Functions
  * @{
  */

/** @} */
/* End of group group WDT_Private_Functions */

/** @defgroup WDT_Exported_Functions
  * @{
  */

/**
  * @brief  Set detection time of watchdog.
  * @param  DetectTime: Set the Detection time.
  *     This parameter can be one of the following values:
  *     WDT_DETECT_TIME_EXP_15, WDT_DETECT_TIME_EXP_17, WDT_DETECT_TIME_EXP_19,
  *     WDT_DETECT_TIME_EXP_21, WDT_DETECT_TIME_EXP_23 or WDT_DETECT_TIME_EXP_25.
  * @retval None
  */
void WDT_SetDetectTime(uint32_t DetectTime)
{

    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_WDT_DETECT_TIME(DetectTime));

    /* Set WDT Detection time */
    tmp = TSB_WD->MOD;
    tmp &= MOD_WDTP_MASK;
    tmp |= DetectTime;
    TSB_WD->MOD = tmp;

}

/**
  * @brief  Run or stop the WDT counter when the system enters IDLE mode. 
  * @param  NewState: Select the state of the WDT before enter IDLE mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDT_SetIdleMode(FunctionalState NewState)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    tmp = TSB_WD->MOD;
    if (NewState == ENABLE) {
        /* Set WDMOD<I2WDT> to start the WDT counter before enter IDLE mode */
        tmp |= MOD_I2WDT_SET;
    } else {
        /* Set WDMOD<I2WDT> to stop the WDT counter before enter IDLE mode */
        tmp &= MOD_I2WDT_CLEAR;
    }
    TSB_WD->MOD = tmp;
}

/**
  * @brief  Set WDT generate NMI interrupt or reset when counter overflow.
  * @param  OverflowOutput: Select function of WDT when counter overflow.
  *   This parameter can be: WDT_WDOUT or WDT_NMIINT.  
  * @retval None
  */
void WDT_SetOverflowOutput(uint32_t OverflowOutput)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_WDT_OUTPUT(OverflowOutput));

    tmp = TSB_WD->MOD;
    if (OverflowOutput == WDT_WDOUT) {
        /* Set WDMOD<RESCR> to 1 */
        tmp |= MOD_RESCR_SET;
    } else {
        /* Clear WDMOD<RESCR> to 0 */
        tmp &= MOD_RESCR_CLEAR;
    }
    TSB_WD->MOD = tmp;
}

/**
  * @brief  Initialize WDT. 
  * @param  InitStruct: The structure containing basic WD configuration.
  * @retval None
  */
void WDT_Init(WDT_InitTypeDef * InitStruct)
{
    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_WDT_DETECT_TIME(InitStruct->DetectTime));
    assert_param(IS_WDT_OUTPUT(InitStruct->OverflowOutput));

    /* Set WDT Detection time */
    WDT_SetDetectTime(InitStruct->DetectTime);
    /* Set WDTMOD<RESCR> to Select function of WDT when counter overflow */
    WDT_SetOverflowOutput(InitStruct->OverflowOutput);
}

/**
  * @brief  Enable the WDT.
  * @param  None
  * @retval None
  */
void WDT_Enable(void)
{
    /* Set WDMOD<WDTE> to enable WDT */
    TSB_WD->MOD |= MOD_WDTE_SET;
}

/**
  * @brief  Disable the WDT.
  * @param  None
  * @retval None
  */
void WDT_Disable(void)
{
    /* Clear WDMOD<WDTE> and (B1H) be written to the WDCR register to disable WDT */
    TSB_WD->MOD &= MOD_WDTE_CLEAR;
    TSB_WD->CR = WDT_CR_DISABLE_CODE;

}

/**
  * @brief  Write the clear code.
  * @param  None
  * @retval None
  */
void WDT_WriteClearCode(void)
{
    /* Set WDTCR to clear the binary counter */
    TSB_WD->CR = WDT_CR_CLR_CODE;

}

/** @} */
/* End of group WDT_Exported_Functions */

/** @} */
/* End of group WDT */

/** @} */
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM037_WDT_H) */
