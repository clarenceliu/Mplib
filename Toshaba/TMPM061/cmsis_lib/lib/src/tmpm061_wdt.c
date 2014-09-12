/**
 *******************************************************************************
 * @file    tmpm061_wdt.c
 * @brief   This file provides API functions for WDT driver.
 * @version V2.0.2.2
 * @date    2013/03/21
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
 * (C)Copyright TOSHIBA CORPORATION 2013 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm061_wdt.h"


#if defined(__TMPM061_WDT_H)
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
    uint32_t reg = 0U;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    reg = TSB_WD->MOD;
    reg &= 0xF2U;
    reg |= ((uint32_t)NewState << 2U);
    TSB_WD->MOD = reg;

}

/**
  * @brief  Set WDT generate NMI interrupt or reset when counter overflow.
  * @param  OverflowOutput: Select function of WDT when counter overflow.
  *   This parameter can be: WDT_WDOUT or WDT_NMIINT.  
  * @retval None
  */
void WDT_SetOverflowOutput(uint32_t OverflowOutput)
{
    uint32_t reg = 0U;
    /* Check the parameters */
    assert_param(IS_WDT_OUTPUT(OverflowOutput));

    reg = TSB_WD->MOD;
    reg &= 0xF4U;
    reg |= (OverflowOutput << 1);
    TSB_WD->MOD = reg;

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
    uint32_t reg = 0U;

    /* Set WDxMOD<WDTE> to enable WDT */
    reg = TSB_WD->MOD;
    reg |= 0x80U;
    TSB_WD->MOD = reg;
}

/**
  * @brief  Disable the WDT.
  * @param  None
  * @retval None
  */
void WDT_Disable(void)
{
    uint32_t reg = 0U;

    /* Clear WDxMOD<WDTE> and (B1H) be written to the WDCR register to disable WDT */
    reg = TSB_WD->MOD;
    reg &= 0x76U;
    TSB_WD->MOD = reg;
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
#endif                          /* defined(__TMPM061_WDT_H) */
