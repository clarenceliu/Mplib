/**
 *******************************************************************************
 * @file    tmpm36b_lvd.h
 * @brief   This file provides all the functions prototypes for LVD driver. 
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_LVD_H
#define __TMPM36B_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
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
#define LVD_VDLVL1_240                   ((uint32_t)0x00000000)
#define LVD_VDLVL1_250                   ((uint32_t)0x00000002)
#define LVD_VDLVL1_260                   ((uint32_t)0x00000004)
#define LVD_VDLVL1_270                   ((uint32_t)0x00000006)
#define LVD_VDLVL1_280                   ((uint32_t)0x00000008)
#define LVD_VDLVL1_290                   ((uint32_t)0x0000000A)
#define IS_LVD_VD1_LEVEL(param)         (((param) == LVD_VDLVL1_240) || \
                                         ((param) == LVD_VDLVL1_250) || \
                                         ((param) == LVD_VDLVL1_260) || \
                                         ((param) == LVD_VDLVL1_270) || \
                                         ((param) == LVD_VDLVL1_280) || \
                                         ((param) == LVD_VDLVL1_290))

#define LVD_VDLVL2_280                   ((uint32_t)0x00000000)
#define LVD_VDLVL2_285                   ((uint32_t)0x00000002)
#define LVD_VDLVL2_290                   ((uint32_t)0x00000004)
#define LVD_VDLVL2_295                   ((uint32_t)0x00000006)
#define LVD_VDLVL2_300                   ((uint32_t)0x00000008)
#define LVD_VDLVL2_305                   ((uint32_t)0x0000000A)
#define LVD_VDLVL2_310                   ((uint32_t)0x0000000C)
#define LVD_VDLVL2_315                   ((uint32_t)0x0000000E)
#define IS_LVD_VD2_LEVEL(param)         (((param) == LVD_VDLVL2_280) || \
                                         ((param) == LVD_VDLVL2_285) || \
                                         ((param) == LVD_VDLVL2_290) || \
                                         ((param) == LVD_VDLVL2_295) || \
                                         ((param) == LVD_VDLVL2_300) || \
                                         ((param) == LVD_VDLVL2_305) || \
                                         ((param) == LVD_VDLVL2_300) || \
                                         ((param) == LVD_VDLVL2_310) || \
                                         ((param) == LVD_VDLVL2_315))

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
    void LVD_EnableVD2(void);
    void LVD_DisableVD2(void);
    void LVD_SetVD2Level(uint32_t VDLevel);
    LVD_VDStatus LVD_GetVD2Status(void);
    void LVD_SetResetOutput(FunctionalState NewState);
    void LVD_SetINTOutput(FunctionalState NewState);
    void LVD_SetINTCondition(uint32_t IntCondition);

/** @} */
/* End of LVD_Exported_FunctionPrototypes */

/** @} */
/* End of group LVD */

/** @} */
/* End of group TX03_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_LVD_H */
