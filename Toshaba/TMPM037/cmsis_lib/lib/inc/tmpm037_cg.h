/**
 *******************************************************************************
 * @file    tmpm037_cg.h
 * @brief   This file provides all the functions prototypes for CG driver.
 * @version V2.0.2.2
 * @date    2014/05/06
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_CG_H
#define __TMPM037_CG_H

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tx00_common.h"

#if defined(__TMPM037_CG_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @addtogroup CG
  * @{
  */

/** @addtogroup CG_Exported_types
  * @{
  */

    typedef enum {
        CG_DIVIDE_1 = 0U,
        CG_DIVIDE_2 = 1U,
        CG_DIVIDE_4 = 2U,
        CG_DIVIDE_8 = 3U,
        CG_DIVIDE_16 = 4U,
        CG_DIVIDE_32 = 5U,
        CG_DIVIDE_64 = 6U,
        CG_DIVIDE_128 = 7U,
        CG_DIVIDE_256 = 8U,
        CG_DIVIDE_512 = 9U,
        CG_DIVIDE_UNKNOWN = 10U,
        CG_DIVIDE_MAX = 11U
    } CG_DivideLevel;
#define IS_CG_GEAR_DIVIDE_LEVEL(param)  (((param) == CG_DIVIDE_1) || \
                                         ((param) == CG_DIVIDE_2) || \
                                         ((param) == CG_DIVIDE_4) || \
                                         ((param) == CG_DIVIDE_8) || \
                                         ((param) == CG_DIVIDE_16))

#define IS_CG_FC_DIDIDE_LEVEL(param)    (((param) == CG_DIVIDE_1) || \
                                         ((param) == CG_DIVIDE_2) || \
                                         ((param) == CG_DIVIDE_4) || \
                                         ((param) == CG_DIVIDE_8) || \
                                         ((param) == CG_DIVIDE_16)|| \
                                         ((param) == CG_DIVIDE_32))

#define IS_CG_DIVIDE_FC_LEVEL(param)    (((param) == CG_DIVIDE_1) || \
                                         ((param) == CG_DIVIDE_2) || \
                                         ((param) == CG_DIVIDE_4) || \
                                         ((param) == CG_DIVIDE_8) || \
                                         ((param) == CG_DIVIDE_16) || \
                                         ((param) == CG_DIVIDE_32) || \
                                         ((param) == CG_DIVIDE_64)|| \
                                         ((param) == CG_DIVIDE_128) || \
                                         ((param) == CG_DIVIDE_256) || \
                                         ((param) == CG_DIVIDE_512))

    typedef enum {
        CG_FOSC_OSC_EXT = 0U,
        CG_FOSC_OSC_INT = 1U,
        CG_FOSC_CLKIN_EXT = 2U
    } CG_FoscSrc;
#define IS_CG_FOSC_SRC(param)           (((param) == CG_FOSC_OSC_EXT) || \
                                         ((param) == CG_FOSC_OSC_INT) || \
                                         ((param) == CG_FOSC_CLKIN_EXT))

#define IS_CG_FOSC_STATE(param)         (((param) == CG_FOSC_OSC_EXT) || \
                                         ((param) == CG_FOSC_OSC_INT) )

    typedef enum {
        CG_WARM_UP_SRC_OSC_INT_HIGH = 0U,
        CG_WARM_UP_SRC_OSC_EXT_HIGH = 1U,
    } CG_WarmUpSrc;
#define IS_CG_WARM_UP_SRC(param)        (((param) == CG_WARM_UP_SRC_OSC_INT_HIGH) || \
                                         ((param) == CG_WARM_UP_SRC_OSC_EXT_HIGH))

    typedef enum {
        CG_FC_SRC_FOSC = 0U,
        CG_FC_SRC_FPLL = 1U
    } CG_FcSrc;
#define IS_CG_FC_SRC(param)    (((param) == CG_FC_SRC_FOSC) || \
                                ((param) == CG_FC_SRC_FPLL))

#define CG_MUL_2_FPLL          (0x0000609FUL<<1U)       /* 2 fold */

#define IS_CG_FPLL_VALUE(param)        ((param) == CG_MUL_2_FPLL)

    typedef enum {
        CG_STBY_MODE_UNKNOWN = 0U,
        CG_STBY_MODE_STOP1 = 1U,
        CG_STBY_MODE_IDLE = 3U,
        CG_STBY_MODE_MAX = 8U
    } CG_STBYMode;
#define IS_CG_STBY_MODE(param)         (((param) == CG_STBY_MODE_STOP1) || \
                                        ((param) == CG_STBY_MODE_IDLE))

    typedef enum {
        CG_PHIT0_SRC_FGEAR = 0U,
        CG_PHIT0_SRC_FC = 1U,
        CG_PHIT0_SRC_MAX = 2U
    } CG_PhiT0Src;
#define IS_CG_PHIT0_SRC(param)  (((param) == CG_PHIT0_SRC_FGEAR) || \
                                 ((param) == CG_PHIT0_SRC_FC))

    typedef enum {
        CG_INT_SRC_0 = 0U,
        CG_INT_SRC_1 = 1U,
        CG_INT_SRC_2 = 2U,
        CG_INT_SRC_3 = 3U,
        CG_INT_SRC_4 = 4U,
        CG_INT_SRC_5 = 5U,
    } CG_INTSrc;

#define IS_CG_INT_SRC(param)    (((param) == CG_INT_SRC_0) || \
                                 ((param) == CG_INT_SRC_1) || \
                                 ((param) == CG_INT_SRC_2) || \
                                 ((param) == CG_INT_SRC_3) || \
                                 ((param) == CG_INT_SRC_4) || \
                                 ((param) == CG_INT_SRC_5))

    typedef enum {
        CG_INT_ACTIVE_STATE_L = 0x00U,
        CG_INT_ACTIVE_STATE_H = 0x10U,
        CG_INT_ACTIVE_STATE_FALLING = 0x20U,
        CG_INT_ACTIVE_STATE_RISING = 0x30U,
        CG_INT_ACTIVE_STATE_BOTH_EDGES = 0x40U,
        CG_INT_ACTIVE_STATE_INVALID = 0x50U
    } CG_INTActiveState;
#define IS_CG_INT_ACTIVE_STATE(param)        (((param) == CG_INT_ACTIVE_STATE_L) || \
                                              ((param) == CG_INT_ACTIVE_STATE_H) || \
                                              ((param) == CG_INT_ACTIVE_STATE_FALLING) || \
                                              ((param) == CG_INT_ACTIVE_STATE_RISING) || \
                                              ((param) == CG_INT_ACTIVE_STATE_BOTH_EDGES))

    typedef union {
        uint32_t All;
        struct {
            uint32_t WDT:1;
            uint32_t Reserved1:1;
            uint32_t DetectLowVoltage1:1;
            uint32_t DetectLowVoltage2:1;
            uint32_t Reserved2:28;
        } Bit;
    } CG_NMIFactor;

    typedef union {
        uint32_t All;
        struct {
            uint32_t PowerOnReset:1;
            uint32_t PinReset:1;
            uint32_t WDTReset:1;
            uint32_t Reserved1:1;
            uint32_t DebugReset:1;
            uint32_t Reserved2:1;
            uint32_t LVDReset:1;
            uint32_t Reserved3:25;
        } Bit;
    } CG_ResetFlag;

/** @} */
/* End of group CG_Exported_types */

/** @defgroup CG_Exported_FunctionPrototypes
  * @{
  */
    void CG_SetFgearLevel(CG_DivideLevel DivideFgearFromFc);
    CG_DivideLevel CG_GetFgearLevel(void);
    void CG_SetPhiT0Src(CG_PhiT0Src PhiT0Src);
    CG_PhiT0Src CG_GetPhiT0Src(void);
    Result CG_SetPhiT0Level(CG_DivideLevel DividePhiT0FromFc);
    CG_DivideLevel CG_GetPhiT0Level(void);
    void CG_SetWarmUpTime(CG_WarmUpSrc Source, uint16_t Time);
    void CG_StartWarmUp(void);
    WorkState CG_GetWarmUpState(void);
    Result CG_SetFPLLValue(uint32_t NewValue);
    uint32_t CG_GetFPLLValue(void);
    Result CG_SetPLL(FunctionalState NewState);
    FunctionalState CG_GetPLLState(void);
    Result CG_SetFosc(CG_FoscSrc Source, FunctionalState NewState);
    void CG_SetFoscSrc(CG_FoscSrc Source);
    CG_FoscSrc CG_GetFoscSrc(void);
    FunctionalState CG_GetFoscState(CG_FoscSrc Source);
    void CG_SetSTBYMode(CG_STBYMode Mode);
    CG_STBYMode CG_GetSTBYMode(void);
    Result CG_SetFcSrc(CG_FcSrc Source);
    CG_FcSrc CG_GetFcSrc(void);
    void CG_SetProtectCtrl(FunctionalState NewState);
    void CG_SetSTBYReleaseINTSrc(CG_INTSrc INTSource,
                                 CG_INTActiveState ActiveState, FunctionalState NewState);
    CG_INTActiveState CG_GetSTBYReleaseINTState(CG_INTSrc INTSource);
    void CG_ClearINTReq(CG_INTSrc INTSource);
    CG_NMIFactor CG_GetNMIFlag(void);
    CG_ResetFlag CG_GetResetFlag(void);
    void CG_SetADCClkSupply(FunctionalState NewState);

/** @} */
/* End of group CG_Exported_FunctionPrototype */

/** @} */
/* End of group CG */

/** @} */
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM037_CG_H) */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM037_CG_H */
