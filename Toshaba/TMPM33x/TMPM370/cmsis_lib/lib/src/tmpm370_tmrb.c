/**
 *******************************************************************************
 * @file    tmpm370_tmrb.c
 * @brief   This file provides API functions for TMRB driver.
 * @version V2.2.0
 * @date    2011/06/09
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 *
 * (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm370_tmrb.h"

#if defined(__TMPM370_TMRB_H) || defined(__TMPM372_TMRB_H) || defined(__TMPM373_TMRB_H) || defined(__TMPM374_TMRB_H)
/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @defgroup TMRB
  * @brief TMRB driver modules
  * @{
  */

/** @defgroup TMRB_Private_Defines
  * @{
  */
#define EN_TBEN_SET           ((uint32_t)0x00000080)
#define EN_TBEN_CLEAR         ((uint32_t)0xFFFFFF7F)

#define CR_I2TB_SET           ((uint32_t)0x00000008)
#define CR_I2TB_CLEAR         ((uint32_t)0xFFFFFFF7)
#define CR_TBWBF_SET          ((uint32_t)0x00000080)
#define CR_TBWBF_CLEAR        ((uint32_t)0xFFFFFF7F)
#define CR_CSSEL_SET          ((uint32_t)0x00000001)
#define CR_CSSEL_CLEAR        ((uint32_t)0xFFFFFFFE)
#define CR_TRGSEL_CLEAR       ((uint32_t)0xFFFFFF9D)

#define MOD_CLK_CLE_CLEAR     ((uint32_t)0xFFFFFFF8)
#define MOD_TBCPM_CLEAR       ((uint32_t)0xFFFFFFE7)
#define MOD_TBCP_CLEAR        ((uint32_t)0xFFFFFFDF)
#define MOD_TBRSWR_CLEAR      ((uint32_t)0xFFFFFFBF)

#define TB_ST_MASK            ((uint32_t)0x00000007)

/** @} */
/* End of group TMRB_Private_Defines */

/** @defgroup TMRB_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group TMRB_Private_FunctionPrototypes */

/** @defgroup TMRB_Private_Functions
  * @{
  */

/** @} */
/* End of group TMRB_Private_Functions */

/** @defgroup TMRB_Exported_Functions
  * @{
  */

/**
  * @brief  Enable the specified TMRB channel.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @retval None
  */
void TMRB_Enable(TSB_TB_TypeDef * TBx)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    /* Set TBxEN<TBEN> to enable TBx */
    TBx->EN |= EN_TBEN_SET;
}

/**
  * @brief  Disable the specified TMRB channel.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @retval None
  */
void TMRB_Disable(TSB_TB_TypeDef * TBx)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    /* Clear TBxEN<TBEN> to disable TBx */
    TBx->EN &= EN_TBEN_CLEAR;
}

/**
  * @brief  Start or stop counter of the specified TMRB channel.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  Cmd: The command for the counter.
  *   This parameter can be TMRB_RUN or TMRB_STOP.
  * @retval None
  */
void TMRB_SetRunState(TSB_TB_TypeDef * TBx, uint32_t Cmd)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_CMD(Cmd));

    /* Write command into RUN register */
    TBx->RUN = Cmd;
}

/**
  * @brief  Initialize the specified TMRB channel.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  InitStruct: The structure containing basic TMRB configuration.
  * @retval None
  */
void TMRB_Init(TSB_TB_TypeDef * TBx, TMRB_InitTypeDef * InitStruct)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_MODE(InitStruct->Mode));
    if (InitStruct->Mode != 0U) {
        assert_param(IS_TMRB_CLK_DIV(InitStruct->ClkDiv));
    } else {
        assert_param(IS_TMRB_IN_PERIPH(TBx));
    }
    assert_param(IS_TMRB_VALUE(InitStruct->Cycle));
    assert_param(IS_TMRB_UC_CTRL(InitStruct->UpCntCtrl));
    assert_param(IS_TMRB_VALUE(InitStruct->Duty));
    assert_param(IS_VALID_DUTY(InitStruct->Duty, InitStruct->Cycle));

    /* Configure source clock for TBx */
    tmp = TBx->MOD;
    tmp &= MOD_CLK_CLE_CLEAR;
    if (InitStruct->Mode != 0U) {
        /* Use internal clock, set the prescaler */
        tmp |= InitStruct->ClkDiv;
    } else {
        /* Use external clock */
        tmp |= InitStruct->Mode;
    }
    /* Set up-counter running mode */
    tmp |= InitStruct->UpCntCtrl;
    TBx->MOD = tmp;

    /* Write duty into RG0 */
    TBx->RG0 = InitStruct->Duty;

    /* Write cycle into RG1 */
    TBx->RG1 = InitStruct->Cycle;
}

/**
  * @brief  Configure the capture timing.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   M370: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  *   M372: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB6, TSB_TB7.
  *   M373: TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7. 
  *   M374: TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7.
  * @param  CaptureTiming: Specify TMRB capture timing.
  *    This parameter can be one of the following values:
  *    TMRB_DISABLE_CAPTURE, TMRB_CAPTURE_IN_RISING,
  *    TMRB_CAPTURE_IN_RISING_FALLING.
  * @retval None
  */
void TMRB_SetCaptureTiming(TSB_TB_TypeDef * TBx, uint32_t CaptureTiming)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_TMRB_IN_PERIPH(TBx));
    assert_param(IS_TMRB_CAPTURE_TIMING(CaptureTiming));

    /* Configure capture timing */
    tmp = TBx->MOD & MOD_TBCPM_CLEAR;
    tmp |= CaptureTiming;
    TBx->MOD = tmp;
}

/**
  * @brief  Configure the flip-flop function.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   M370: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  *   M372: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB6, TSB_TB7.
  *   M373: TSB_TB3, TSB_TB6, TSB_TB7. 
  *   M374: TSB_TB3, TSB_TB6.
  * @param FFStruct: The structure containing TMRB flip-flop configuration
  * @retval None
  */
void TMRB_SetFlipFlop(TSB_TB_TypeDef * TBx, TMRB_FFOutputTypeDef * FFStruct)
{
    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(FFStruct));
    assert_param(IS_TMRB_OUT_PERIPH(TBx));
    assert_param(IS_TMRB_FLIPFLOP_CTRL(FFStruct->FlipflopCtrl));
    assert_param(IS_TMRB_FLIPFLOP_TRG(FFStruct->FlipflopReverseTrg));

    /* Configure the flip-flop function of TBx */
    TBx->FFCR = (FFStruct->FlipflopCtrl | FFStruct->FlipflopReverseTrg);
}

/**
  * @brief  Indicate what causes the interrupt.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @retval The interrupt factor of TBx.
  */
TMRB_INTFactor TMRB_GetINTFactor(TSB_TB_TypeDef * TBx)
{
    TMRB_INTFactor retval;

    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));

    retval.All = 0U;
    retval.All = TBx->ST & TB_ST_MASK;
    return retval;
}

/**
  * @brief  Mask some TMRB interrupt.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  INTMask: Select the mask of TMRB interrupt.
  *   This parameter can be one of the following values:
  *   TMRB_NO_INT_MASK, TMRB_MASK_MATCH_DUTY_INT, TMRB_MASK_MATCH_CYCLE_INT,
  *   or TMRB_MASK_OVERFLOW_INT.
  * @retval None
  */
void TMRB_SetINTMask(TSB_TB_TypeDef * TBx, uint32_t INTMask)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_INT_MASK(INTMask));

    /* Mask the specified interrupt */
    TBx->IM = INTMask;
}

/**
  * @brief  Change duty value of TBx.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  Duty: New duty value, max 0xFFFF.
  * @retval None
  */
void TMRB_ChangeDuty(TSB_TB_TypeDef * TBx, uint32_t Duty)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_VALUE(Duty));
    assert_param(IS_VALID_DUTY(Duty, TBx->RG1));

    /* Write duty into RG0 */
    TBx->RG0 = Duty;
}

/**
  * @brief  Change cycle value of TBx.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  Cycle: New cycle value, max 0xFFFF.
  * @retval None
  */
void TMRB_ChangeCycle(TSB_TB_TypeDef * TBx, uint32_t Cycle)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_VALUE(Cycle));
    assert_param(IS_VALID_DUTY(TBx->RG0, Cycle));

    /* Write cycle into RG1 */
    TBx->RG1 = Cycle;
}

/**
  * @brief  Get up-counter value of TBx.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @retval Up-counter value of TBx
  */
uint16_t TMRB_GetUpCntValue(TSB_TB_TypeDef * TBx)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));

    /* Return up-counter value */
    return (uint16_t) TBx->UC;
}

/**
  * @brief  Get TMRB capture value of TBx.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   CapReg= TMRB_CAPTURE_0 : 
  *     TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  *   CapReg= TMRB_CAPTURE_1 :
  *     M370: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  *     M372: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB6, TSB_TB7.
  *     M373: TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7. 
  *     M374: TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7.
  * @param  CapReg: Select the capture register to read.
  *   This parameter can be: TMRB_CAPTURE_0 or TMRB_CAPTURE_1.
  * @retval Capture value of TBx
  */
uint16_t TMRB_GetCaptureValue(TSB_TB_TypeDef * TBx, uint8_t CapReg)
{
    /* Check the parameters */
    assert_param(IS_TMRB_CAPTURE_REG(CapReg));
    if (CapReg == TMRB_CAPTURE_1) {
        assert_param(IS_TMRB_IN_PERIPH(TBx));
    } else {
        assert_param(IS_TMRB_ALL_PERIPH(TBx));
    }

    return CapReg ? (uint16_t) TBx->CP1 : (uint16_t) TBx->CP0;
}

/**
  * @brief  Capture counter by software and take them into capture register 0.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @retval None
  */
void TMRB_ExecuteSWCapture(TSB_TB_TypeDef * TBx)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));

    /* Set software capture */
    TBx->MOD &= MOD_TBCP_CLEAR;
}

/**
  * @brief  Enable or disable TMRB when system is in idle mode.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  NewState: New state of TMRB in system idle mode.
  *   This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void TMRB_SetIdleMode(TSB_TB_TypeDef * TBx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set TBxCR<I2TB> to enable TBx in system idle mode */
        TBx->CR |= CR_I2TB_SET;
    } else {
        /* Clear TBxCR<I2TB> to disable TBx in system idle mode */
        TBx->CR &= CR_I2TB_CLEAR;
    }
}

/**
  * @brief  Enable or disable double buffer of TBx and set the timing to write to timer register.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  NewState: New state of TBx double buffer.
  *   This parameter can be ENABLE or DISABLE.
  * @param  WriteRegMode: Timing to write to timer register.
  *   This parameter can be TMRB_WRITE_REG_SEPARATE or TMRB_WRITE_REG_SIMULTANEOUS.
  * @retval None
  */
void TMRB_SetDoubleBuf(TSB_TB_TypeDef * TBx, FunctionalState NewState, uint8_t WriteRegMode)
{
    uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_TMRB_WRITE_REG_MODE(WriteRegMode));

    if (NewState == ENABLE) {
        /* Set TBxCR<TBWBF> to enable TBx double buffer */
        TBx->CR |= CR_TBWBF_SET;
    } else {
        /* Clear TBxCR<TBWBF> to disable TBx double buffer */
        TBx->CR &= CR_TBWBF_CLEAR;
    }
    /* Write timer register timing */
    tmp = TBx->MOD & MOD_TBRSWR_CLEAR;
    tmp |= (uint32_t) WriteRegMode;
    TBx->MOD = tmp;

}

/**
  * @brief  Enable or disable external trigger to start count and set the active edge.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *     M370: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  *     M372: TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB6, TSB_TB7.
  *     M373: TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7. 
  *     M374: TSB_TB2, TSB_TB3, TSB_TB6, TSB_TB7.
  * @param  NewState: New state of external trigger.
  *   This parameter can be ENABLE or DISABLE.
  * @param  TrgMode: Active edge of the external trigger signal.
  *   This parameter can be TMRB_TRG_EDGE_RISING or TMRB_TRG_EDGE_FALLING.
  * @retval None
  */
void TMRB_SetExtStartTrg(TSB_TB_TypeDef * TBx, FunctionalState NewState, uint8_t TrgMode)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_TMRB_IN_PERIPH(TBx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_TMRB_TRG_EDGE(TrgMode));

    tmp = TBx->CR;
    if (NewState == ENABLE) {
        /* Set TBxCR<CSSEL> to choose external trigger */
        tmp |= CR_CSSEL_SET;
    } else {
        /* Clear TBxCR<CSSEL> to choose software start */
        tmp &= CR_CSSEL_CLEAR;
    }

    /* external trigger selection */
    tmp &= CR_TRGSEL_CLEAR;
    tmp |= (uint32_t) TrgMode;
    TBx->CR = tmp;
}

/**
  * @brief  Enable or disable clock operation during debug HALT.
  * @param  TBx: Select the TMRB channel.
  *   This parameter can be one of the following values:
  *   TSB_TB0, TSB_TB1, TSB_TB2, TSB_TB3, TSB_TB4, TSB_TB5, TSB_TB6, TSB_TB7.
  * @param  ClkState: Timer state in HALT mode.
  *   This parameter can be TMRB_RUNNING_IN_CORE_HALT or TMRB_STOP_IN_CORE_HALT.
  * @retval None
  */
#if defined(__TMPM372_TMRB_H) || defined(__TMPM373_TMRB_H) || defined(__TMPM374_TMRB_H)
void TMRB_SetClkInCoreHalt(TSB_TB_TypeDef * TBx, uint8_t ClkState)
{
    /* Check the parameters */
    assert_param(IS_TMRB_ALL_PERIPH(TBx));
    assert_param(IS_TMRB_CLK_IN_CORE_HALT(ClkState));

    if (ClkState == TMRB_STOP_IN_CORE_HALT) {
        /* Set TBEN<TBHALT> */
        TBx->EN |= (uint32_t) TMRB_STOP_IN_CORE_HALT;
    } else {
        /* Clear TBEN<TBHALT> */
        TBx->EN &= ~(uint32_t) TMRB_STOP_IN_CORE_HALT;
    }
}
#endif                          /* defined(__TMPM372_TMRB_H) || (__TMPM373_TMRB_H) || (__TMPM374_TMRB_H) */
/** @} */
/* End of group TMRB_Exported_Functions */

/** @} */
/* End of group TMRB */

/** @} */
/* End of group TX03_Periph_Driver */

#endif                          /* defined(__TMPM370_TMRB_H) || (__TMPM372_TMRB_H) || (__TMPM373_TMRB_H) || (__TMPM374_TMRB_H) */
