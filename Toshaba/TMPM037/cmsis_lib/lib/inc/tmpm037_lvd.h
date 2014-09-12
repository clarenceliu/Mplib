/**
 *******************************************************************************
 * @file    tmpm037_lvd.h
 * @brief   This file provides all the functions prototypes for LVD driver. 
 * @version V2.0.2.2
 * @date    2014/05/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_LVD_H
#define __TMPM037_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tx00_common.h"

#if defined(__TMPM037_LVD_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @addtogroup LVD
  * @{
  */

/** @defgroup LVD_Exported_Types
  * @{
  */
    typedef enum {
        LVD_VD_UPPER = 0U,
        LVD_VD_LOWER = 1U
    } LVD_VDStatus;

/** @} */
/* End of group LVD_Exported_Types */

/** @defgroup LVD_Exported_Constants
  * @{
  */
#define LVD_VDLVL1_250                   ((uint32_t)0x00000006)
#define LVD_VDLVL1_260                   ((uint32_t)0x00000008)
#define LVD_VDLVL1_270                   ((uint32_t)0x0000000A)
#define LVD_VDLVL1_280                   ((uint32_t)0x0000000C)
#define LVD_VDLVL1_290                   ((uint32_t)0x0000000E)
#define IS_LVD_VD1_LEVEL(param)         (((param) == LVD_VDLVL1_250) || \
                                         ((param) == LVD_VDLVL1_260) || \
                                         ((param) == LVD_VDLVL1_270) || \
                                         ((param) == LVD_VDLVL1_280) || \
                                         ((param) == LVD_VDLVL1_290))

#define LVD_INTSEL_LOWER                ((uint32_t)0x00000000)
#define LVD_INTSEL_LOWER_UPPER          ((uint32_t)0x00000010)
#define IS_LVD_INT_CONDITION(param)     (((param) == LVD_INTSEL_LOWER) || \
                                         ((param) == LVD_INTSEL_LOWER_UPPER))
/** @} */
/* End of LVD_Exported_Constants */

/** @defgroup LVD_Exported_FunctionPrototypes
  * @{
  */
    void LVD_EnableVD1(void);
    void LVD_DisableVD1(void);
    void LVD_SetVD1Level(uint32_t VDLevel);
    LVD_VDStatus LVD_GetVD1Status(void);
    void LVD_SetVD1ResetOutput(FunctionalState NewState);
    void LVD_SetVD1INTOutput(FunctionalState NewState);
    uint32_t LVD_GetINTCondition(void);

/** @} */
/* End of LVD_Exported_FunctionPrototypes */

/** @} */
/* End of group LVD */

/** @} */
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM037_LVD_H) */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM037_LVD_H */
