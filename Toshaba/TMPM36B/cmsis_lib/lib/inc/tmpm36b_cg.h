/**
 *******************************************************************************
 * @file    tmpm36b_cg.h
 * @brief   This file provides all the functions prototypes for CG driver.
 * @version V2.0.2.3
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_CG_H
#define __TMPM36B_CG_H

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
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
        CG_SCOUT_SRC_UNKNOWN = 0U,
        CG_SCOUT_SRC_HALF_FSYS = 1U,
        CG_SCOUT_SRC_FSYS = 2U,
        CG_SCOUT_SRC_PHIT0 = 3U
    } CG_SCOUTSrc;
#define IS_CG_SCOUT_SRC(param)          (((param) == CG_SCOUT_SRC_HALF_FSYS) || \
                                         ((param) == CG_SCOUT_SRC_FSYS) || \
                                         ((param) == CG_SCOUT_SRC_PHIT0))

    typedef enum {
        CG_WARM_UP_SRC_OSC_INT_HIGH = 0U,
        CG_WARM_UP_SRC_OSC_EXT_HIGH = 1U,
        CG_WARM_UP_SRC_OSC_EXT_LOW = 2U
    } CG_WarmUpSrc;
#define IS_CG_WARM_UP_SRC(param)        (((param) == CG_WARM_UP_SRC_OSC_INT_HIGH) || \
                                         ((param) == CG_WARM_UP_SRC_OSC_EXT_HIGH) || \
                                         ((param) == CG_WARM_UP_SRC_OSC_EXT_LOW))

#define IS_CG_WARM_UP_TIME_HIGH(param)     ((param) < 0x1000U)

#define IS_CG_WARM_UP_TIME_LOW(param)      ((param) < 0x4000U)

    typedef enum {
        CG_FC_SRC_FOSC = 0U,
        CG_FC_SRC_FPLL = 1U
    } CG_FcSrc;
#define IS_CG_FC_SRC(param)    (((param) == CG_FC_SRC_FOSC) || \
                                ((param) == CG_FC_SRC_FPLL))

#ifdef TSB_M36BFY
    typedef enum {
        CG_FPLL_8M_MULTIPLY_6 = 0U,
        CG_FPLL_8M_MULTIPLY_10 = 1U,
        CG_FPLL_10M_MULTIPLY_8 = 2U,
        CG_FPLL_12M_MULTIPLY_4 = 3U,
        CG_FPLL_12M_MULTIPLY_6 = 4U,
        CG_FPLL_16M_MULTIPLY_3 = 5U,
        CG_FPLL_16M_MULTIPLY_5 = 6U,
        CG_FPLL_MULTIPLY_UNKNOWN = 7U
    } CG_FpllValue;
#define IS_CG_FPLL_VALUE(param)        (((param) == CG_FPLL_8M_MULTIPLY_6) || \
                                        ((param) == CG_FPLL_8M_MULTIPLY_10) || \
                                        ((param) == CG_FPLL_10M_MULTIPLY_8) || \
                                        ((param) == CG_FPLL_12M_MULTIPLY_4) || \
                                        ((param) == CG_FPLL_12M_MULTIPLY_6) || \
                                        ((param) == CG_FPLL_16M_MULTIPLY_3) || \
                                        ((param) == CG_FPLL_16M_MULTIPLY_5))

#elif defined (TSB_M36BF10 )
    typedef enum {
        CG_FPLL_8M_MULTIPLY_8 = 0U,
        CG_FPLL_8M_10M_MULTIPLY_6 = 1U,
        CG_FPLL_10M_MULTIPLY_4 = 2U,
        CG_FPLL_12M_MULTIPLY_5 = 3U,
        CG_FPLL_12M_16M_MULTIPLY_4 = 4U,
        CG_FPLL_16M_MULTIPLY_3 = 5U,
        CG_FPLL_MULTIPLY_UNKNOWN = 6U
    } CG_FpllValue;
#define IS_CG_FPLL_VALUE(param)        (((param) == CG_FPLL_8M_MULTIPLY_8) || \
                                        ((param) == CG_FPLL_8M_10M_MULTIPLY_6) || \
                                        ((param) == CG_FPLL_10M_MULTIPLY_4) || \
                                        ((param) == CG_FPLL_12M_MULTIPLY_5) || \
                                        ((param) == CG_FPLL_12M_16M_MULTIPLY_4) || \
                                        ((param) == CG_FPLL_16M_MULTIPLY_3))

#endif

    typedef enum {
        CG_STBY_MODE_UNKNOWN = 0U,
        CG_STBY_MODE_STOP1 = 1U,
        CG_STBY_MODE_IDLE = 3U,
        CG_STBY_MODE_STOP2 = 5U,
        CG_STBY_MODE_MAX = 8U
    } CG_STBYMode;
#define IS_CG_STBY_MODE(param)         (((param) == CG_STBY_MODE_STOP1) || \
                                        ((param) == CG_STBY_MODE_IDLE)|| \
                                        ((param) == CG_STBY_MODE_STOP2))

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
        CG_INT_SRC_6 = 6U,
        CG_INT_SRC_7 = 7U,
        CG_INT_SRC_8 = 8U,
        CG_INT_SRC_9 = 9U,
        CG_INT_SRC_A = 10U,
        CG_INT_SRC_B = 11U,
        CG_INT_SRC_C = 12U,
        CG_INT_SRC_D = 13U,
        CG_INT_SRC_RTC = 14U,
        CG_INT_SRC_RMCRX = 15U
    } CG_INTSrc;

#define IS_CG_INT_SRC(param)    (((param) == CG_INT_SRC_0) || \
                                 ((param) == CG_INT_SRC_1) || \
                                 ((param) == CG_INT_SRC_2) || \
                                 ((param) == CG_INT_SRC_3) || \
                                 ((param) == CG_INT_SRC_4) || \
                                 ((param) == CG_INT_SRC_5) || \
                                 ((param) == CG_INT_SRC_6) || \
                                 ((param) == CG_INT_SRC_7) || \
                                 ((param) == CG_INT_SRC_8) || \
                                 ((param) == CG_INT_SRC_9) || \
                                 ((param) == CG_INT_SRC_A) || \
                                 ((param) == CG_INT_SRC_B) || \
                                 ((param) == CG_INT_SRC_C) || \
                                 ((param) == CG_INT_SRC_D) || \
                                 ((param) == CG_INT_SRC_RTC) || \
                                 ((param) == CG_INT_SRC_RMCRX))

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

#define IS_CG_INT_RTC_ACTIVE_STATE(param)    ((param) == CG_INT_ACTIVE_STATE_FALLING)

#define IS_CG_INT_RMCRX_ACTIVE_STATE(param)  ((param) == CG_INT_ACTIVE_STATE_RISING)

#define CG_FC_PERIPH_UDMACA         (uint32_t)(0x01U << 0U)
#define CG_FC_PERIPH_UDMACB         (uint32_t)(0x01U << 1U)
#define CG_FC_PERIPH_EBIF           (uint32_t)(0x01U << 2U)
#define CG_FC_PERIPH_TMRB0          (uint32_t)(0x01U << 3U)
#define CG_FC_PERIPH_TMRB1          (uint32_t)(0x01U << 4U)
#define CG_FC_PERIPH_TMRB2          (uint32_t)(0x01U << 5U)
#define CG_FC_PERIPH_TMRB3          (uint32_t)(0x01U << 6U)
#define CG_FC_PERIPH_TMRB4          (uint32_t)(0x01U << 7U)
#define CG_FC_PERIPH_TMRB5          (uint32_t)(0x01U << 8U)
#define CG_FC_PERIPH_TMRB6          (uint32_t)(0x01U << 9U)
#define CG_FC_PERIPH_TMRB7          (uint32_t)(0x01U << 10U)
#define CG_FC_PERIPH_SIO_UART0      (uint32_t)(0x01U << 11U)
#define CG_FC_PERIPH_SIO_UART1      (uint32_t)(0x01U << 12U)
#define CG_FC_PERIPH_SIO_UART2      (uint32_t)(0x01U << 13U)
#define CG_FC_PERIPH_SIO_UART3      (uint32_t)(0x01U << 14U)
#define CG_FC_PERIPH_UART4          (uint32_t)(0x01U << 15U)
#define CG_FC_PERIPH_UART5          (uint32_t)(0x01U << 16U)
#define CG_FC_PERIPH_I2C_SIO0       (uint32_t)(0x01U << 17U)
#define CG_FC_PERIPH_I2C_SIO1       (uint32_t)(0x01U << 18U)
#define CG_FC_PERIPH_I2C_SIO2       (uint32_t)(0x01U << 19U)
#define CG_FC_PERIPH_SSP0           (uint32_t)(0x01U << 20U)
#define CG_FC_PERIPH_SSP1           (uint32_t)(0x01U << 21U)
#define CG_FC_PERIPH_SSP2           (uint32_t)(0x01U << 22U)
#define CG_FC_PERIPH_RMC            (uint32_t)(0x01U << 23U)
#define CG_FC_PERIPH_MPT0           (uint32_t)(0x01U << 24U)
#define CG_FC_PERIPH_MPT1           (uint32_t)(0x01U << 25U)
#define CG_FC_PERIPH_MPT2           (uint32_t)(0x01U << 26U)
#define CG_FC_PERIPH_MPT3           (uint32_t)(0x01U << 27U)
#define CG_FC_PERIPH_PMD            (uint32_t)(0x01U << 28U)
#define CG_FC_PERIPH_ENC            (uint32_t)(0x01U << 29U)
#define CG_FC_PERIPH_LVD            (uint32_t)(0x01U << 30U)
#define CG_FC_PERIPH_TRACECLK       (uint32_t)(0x01U << 31U)
#define CG_FC_PERIPH_ALL            (uint32_t)(0xFFFFFFFFU)
#define IS_CG_FC_PERIPH(param)      ((param) > 0U)

    typedef union {
        uint32_t All;
        struct {
            uint32_t WDT:1;
            uint32_t NMIPin:1;
            uint32_t DetectLowVoltage:1;
            uint32_t ReturnLowVoltage:1;
        } Bit;
    } CG_NMIFactor;

    typedef union {
        uint32_t All;
        struct {
            uint32_t PowerOn:1;
            uint32_t ResetPin:1;
            uint32_t WDTReset:1;
            uint32_t STOP2Reset:1;
            uint32_t DebugReset:1;
            uint32_t OFDReset:1;
            uint32_t LVDReset:1;
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
    void CG_SetSCOUTSrc(CG_SCOUTSrc Source);
    CG_SCOUTSrc CG_GetSCOUTSrc(void);
    void CG_SetWarmUpTime(CG_WarmUpSrc Source, uint16_t Time);
    void CG_StartWarmUp(void);
    WorkState CG_GetWarmUpState(void);
    Result CG_SetFPLLValue(CG_FpllValue NewValue);
    CG_FpllValue CG_GetFPLLValue(void);
    Result CG_SetPLL(FunctionalState NewState);
    FunctionalState CG_GetPLLState(void);
    Result CG_SetFosc(CG_FoscSrc Source, FunctionalState NewState);
    void CG_SetFoscSrc(CG_FoscSrc Source);
    CG_FoscSrc CG_GetFoscSrc(void);
    FunctionalState CG_GetFoscState(CG_FoscSrc Source);
    void CG_SetSTBYMode(CG_STBYMode Mode);
    CG_STBYMode CG_GetSTBYMode(void);
    void CG_SetPinStateInStop1Mode(FunctionalState NewState);
    FunctionalState CG_GetPinStateInStop1Mode(void);
    void CG_SetPortKeepInStop2Mode(FunctionalState NewState);
    FunctionalState CG_GetPortKeepInStop2Mode(void);
    Result CG_SetFcSrc(CG_FcSrc Source);
    CG_FcSrc CG_GetFcSrc(void);
    void CG_SetProtectCtrl(FunctionalState NewState);
    void CG_SetSTBYReleaseINTSrc(CG_INTSrc INTSource,
                                 CG_INTActiveState ActiveState, FunctionalState NewState);
    CG_INTActiveState CG_GetSTBYReleaseINTState(CG_INTSrc INTSource);
    void CG_ClearINTReq(CG_INTSrc INTSource);
    CG_NMIFactor CG_GetNMIFlag(void);
    CG_ResetFlag CG_GetResetFlag(void);
    void CG_SetInternalOscForOFD(FunctionalState NewState);
    void CG_SetFcPeriph(uint32_t Periph, FunctionalState NewState);
    void CG_SetFs(FunctionalState NewState);

/** @} */
/* End of group CG_Exported_FunctionPrototype */

/** @} */
/* End of group CG */

/** @} */
/* End of group TX03_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_CG_H */
