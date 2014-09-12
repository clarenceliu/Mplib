/**
 *******************************************************************************
 * @file    tmpm037_lvd.c
 * @brief   This file provides API functions for LVD driver. 
 * @version V2.0.2.2
 * @date    2014/05/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_lvd.h"

#if defined(__TMPM037_LVD_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */
/** @defgroup LVD
  * @brief LVD driver modules
  * @{
  */

/** @defgroup LVD_Private_Defines
  * @{
  */
#define LVD_EN_SET              ((uint32_t)0x00000001)
#define LVD_EN_CLEAR            ((uint32_t)0xFFFFFFFE)

#define LVD_VD1LVL_CLEAR        ((uint32_t)0xFFFFFFF1)

#define LVD_VD1ST_MASK          ((uint32_t)0x00000080)

#define LVD_VD1RSTEN_SET        ((uint32_t)0x00000040)
#define LVD_VD1RSTEN_CLEAR      ((uint32_t)0xFFFFFFBF)
#define LVD_VD1INTEN_SET        ((uint32_t)0x00000020)
#define LVD_VD1INTEN_CLEAR      ((uint32_t)0xFFFFFFDF)

#define LVD_INTSEL_SET          ((uint32_t)0x00000010)


/** @} */
/* End of group LVD_Private_Defines */

/** @defgroup LVD_Exported_Functions
  * @{
  */

/**
  * @brief  Enable the operation of voltage detection 1.
  * @param  None
  * @retval None
  */
void LVD_EnableVD1(void)
{
    /* Set LVDCR1<EN> to enable voltage detection 1 */
    TSB_LVD->CR1 |= LVD_EN_SET;
}

/**
  * @brief  Disable the operation of voltage detection 1.
  * @param  None
  * @retval None
  */
void LVD_DisableVD1(void)
{
    /* Clear LVDCR1<EN> to disable voltage detection 1 */
    TSB_LVD->CR1 &= LVD_EN_CLEAR;
}

/**
  * @brief  Select detection voltage 1 level.
  * @param  VDLevel : voltage detection 1 level, which can be:
  *             LVD_VDLVL1_250, LVD_VDLVL1_260,
  *             LVD_VDLVL1_270, LVD_VDLVL1_280, LVD_VDLVL1_290.
  * @retval None
  */
void LVD_SetVD1Level(uint32_t VDLevel)
{
    uint32_t regval = TSB_LVD->CR1;

    /* Check the parameter */
    assert_param(IS_LVD_VD1_LEVEL(VDLevel));

    regval &= LVD_VD1LVL_CLEAR;
    regval |= VDLevel;
    TSB_LVD->CR1 = regval;
}

/**
  * @brief  Get voltage detection 1 interrupt status.
  * @param  None
  * @retval LVD_VD_UPPER, LVD_VD_LOWER.
  */
LVD_VDStatus LVD_GetVD1Status(void)
{
    LVD_VDStatus result = LVD_VD_UPPER;
    uint32_t regval = TSB_LVD->CR1;
    regval &= LVD_VD1ST_MASK;

    if (regval) {
        result = LVD_VD_LOWER;
    } else {
        /* Do nothing */
    }
    return result;
}

/**
  * @brief  Enable or disable LVD reset output of voltage detection 1.
  * @param  ENABLE or DISABLE
  * @retval None
  */
void LVD_SetVD1ResetOutput(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set LVDCR1<RSTEN> to 1 */
        TSB_LVD->CR1 |= LVD_VD1RSTEN_SET;
    } else {
        /* Clear LVDCR1<RSTEN> to 0 */
        TSB_LVD->CR1 &= LVD_VD1RSTEN_CLEAR;
    }
}

/**
  * @brief  Enable or disable LVD interrupt output of voltage detection 1.
  * @param  ENABLE or DISABLE
  * @retval None
  */
void LVD_SetVD1INTOutput(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set LVDCR1<INTEN> to 1 */
        TSB_LVD->CR1 |= LVD_VD1INTEN_SET;
    } else {
        /* Clear LVDCR1<INTEN> to 0 */
        TSB_LVD->CR1 &= LVD_VD1INTEN_CLEAR;
    }
}

/**
  * @brief  Get voltage detection interrupt generation condition.
  * @param  None
  * @retval LVD_INTSEL_LOWER, LVD_INTSEL_LOWER_UPPER.
  */
uint32_t LVD_GetINTCondition(void)
{
    uint32_t retval = LVD_INTSEL_LOWER;
    uint32_t tmp = 0U;

    /* Get LVDCR1<INTSEL> */
    tmp = TSB_LVD->CR1 & LVD_INTSEL_SET;
    if (tmp == LVD_INTSEL_SET) {
        retval = LVD_INTSEL_LOWER_UPPER;
    } else {
        /* Do nothing */
    }

    return retval;
}

/** @} */
/* End of group LVD_Exported_Functions */
/** @} */
/* End of group LVD */
/** @} */
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM037_LVD_H) */
