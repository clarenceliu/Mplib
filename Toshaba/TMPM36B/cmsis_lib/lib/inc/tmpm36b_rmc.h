/**
 *******************************************************************************
 * @file    tmpm36b_rmc.h
 * @brief   This file provides all the functions prototypes for RMC driver.
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_RMC_H
#define __TMPM36B_RMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
  * @{
  */
/** @addtogroup RMC
  * @{
  */
/** @addtogroup RMC_Exported_Types
  * @{
  */
#if defined(TSB_RMC)
#define TSB_RMC0 TSB_RMC
#define IS_RMC_PERIPH(PERIPH)      ((PERIPH) == TSB_RMC0)
#endif                          /* TSB_RMC */

    typedef enum {
        RMC_RX_IN_CYCLE_METHOD = 0U,
        RMC_RX_IN_PHASE_METHOD = 1U
    } RMC_RxMethod;
#define IS_RMC_RX_METHOD(param)    (((param) == RMC_RX_IN_CYCLE_METHOD) || \
                                    ((param) == RMC_RX_IN_PHASE_METHOD))

    typedef enum {
        RMC_NO_LEADER = 0U,
        RMC_LEADER_DETECTED = 1U
    } RMC_LeaderDetection;
#define IS_RMC_LEADER_DETECTION(param)  (((param) == RMC_NO_LEADER) || \
                                         ((param) == RMC_LEADER_DETECTED))

#define IS_RMC_PHASE_LARGER_THRESHOLD(param)     ((param)<0x80U)

#define IS_RMC_PHASE_SMALLER_THRESHOLD(param)    ((param)<0x80U)

#define IS_RMC_NOISE_CANCELLATION_TIME(param)    ((param)<0x10U)

    typedef struct {
        FunctionalState LeaderDetectionState;
        FunctionalState LeaderINTState;
        uint8_t MaxCycle;
        uint8_t MinCycle;
        uint8_t MaxLowWidth;
        uint8_t MinLowWidth;
    } RMC_LeaderParameterTypeDef;
#define IS_RMC_LEADER_PARAMETER(MaxCycle,MinCycle,MaxLowWidth,MinLowWidth)  ((((MaxCycle)>(MinCycle))&&((MaxLowWidth)>(MinLowWidth))&&((MinCycle)>(MaxLowWidth))) ||\
                         (((MaxCycle)>(MinCycle))&&((MaxLowWidth)==0x00U))||\
                         ((MaxCycle)==0x00U))

    typedef enum {
        RMC_RX_END_BITS_REG_1 = 0U,
        RMC_RX_END_BITS_REG_2 = 1U,
        RMC_RX_END_BITS_REG_3 = 2U
    } RMC_RxEndBitsReg;
#define IS_RMC_RX_END_BITS_REG(param)        (((param) == RMC_RX_END_BITS_REG_1)|| \
                                              ((param) == RMC_RX_END_BITS_REG_2)|| \
                                              ((param) == RMC_RX_END_BITS_REG_3))

#define IS_RMC_RX_END_BITS(param)            ((param)<0x49U)

    typedef enum {
        RMC_CLK_LOW_FREQUENCY = 0U,
        RMC_CLK_TB1OUT = 1U
    } RMC_SrcClk;
#define IS_RMC_SRC_CLK(param)           (((param) == RMC_CLK_LOW_FREQUENCY) || \
                                         ((param) == RMC_CLK_TB1OUT))

    typedef struct {
        uint32_t RxBuf1;
        uint32_t RxBuf2;
        uint8_t RxBuf3;
        uint8_t RxDataBits;
    } RMC_RxDataTypeDef;

    typedef struct {
        RMC_LeaderParameterTypeDef LeaderPara;
        FunctionalState FallingEdgeINTState;
        RMC_RxMethod SignalRxMethod;
        FunctionalState InputSignalReversedState;
        uint8_t NoiseCancellationTime;
        uint8_t LowWidth;
        uint8_t MaxDataBitCycle;
        uint8_t LargerThreshold;
        uint8_t SmallerThreshold;
    } RMC_InitTypeDef;

    typedef union {
        uint32_t All;
        struct {
            uint32_t Reserved:12;
            uint32_t InputFallingEdge:1;
            uint32_t MaxDataBitCycle:1;
            uint32_t LowWidthDetection:1;
            uint32_t LeaderDetection:1;
        } Bit;
    } RMC_INTFactor;

/** @} */
/* End of group RMC_Exported_Types */

/** @defgroup RMC_Exported_FunctionPrototypes
  * @{
  */
    void RMC_Enable(TSB_RMC_TypeDef * RMCx);
    void RMC_Disable(TSB_RMC_TypeDef * RMCx);
    void RMC_Init(TSB_RMC_TypeDef * RMCx, RMC_InitTypeDef * RMC_InitStruct);
    void RMC_SetRxCtrl(TSB_RMC_TypeDef * RMCx, FunctionalState NewState);
    RMC_RxDataTypeDef RMC_GetRxData(TSB_RMC_TypeDef * RMCx);
    void RMC_SetLeaderDetection(TSB_RMC_TypeDef * RMCx, RMC_LeaderParameterTypeDef LeaderPara);
    void RMC_SetFallingEdgeINT(TSB_RMC_TypeDef * RMCx, FunctionalState NewState);
    void RMC_SetSignalRxMethod(TSB_RMC_TypeDef * RMCx, RMC_RxMethod Method);
    void RMC_SetRxTrg(TSB_RMC_TypeDef * RMCx, uint8_t LowWidth, uint8_t MaxDataBitCycle);
    void RMC_SetThreshold(TSB_RMC_TypeDef * RMCx, uint8_t LargerThreshold,
                          uint8_t SmallerThreshold);
    void RMC_SetInputSignalReversed(TSB_RMC_TypeDef * RMCx, FunctionalState NewState);
    void RMC_SetNoiseCancellation(TSB_RMC_TypeDef * RMCx, uint8_t NoiseCancellationTime);
    RMC_INTFactor RMC_GetINTFactor(TSB_RMC_TypeDef * RMCx);
    RMC_LeaderDetection RMC_GetLeader(TSB_RMC_TypeDef * RMCx);
    void RMC_SetRxEndBitNum(TSB_RMC_TypeDef * RMCx, RMC_RxEndBitsReg Reg_x, uint8_t BitNum);
    void RMC_SetSrcClk(TSB_RMC_TypeDef * RMCx, RMC_SrcClk Clk);
/** @} */
/* End of group RMC_Exported_FunctionPrototypes */
/** @} */
/* End of group RMC */
/** @} */
/* End of group TX03_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_RMC_H */
