/**
 *******************************************************************************
 * @file    tmpm36b_pmd.h
 * @brief   This file provides all the functions prototypes for PMD driver. 
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_PMD_H
#define __TMPM36B_PMD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
  * @{
  */
/** @addtogroup PMD
  * @{
  */

/** @addtogroup PMD Exported_types
  * @{
  */

/** @brief PMD initialization structure definition
  * @{
  */
    typedef struct {
        uint32_t CycleMode;     /* Specify PWM cycle extension mode */
        uint32_t DutyMode;      /* Choose DUTY mode */
        uint32_t IntTiming;     /* Choose PWM interrupt timing when PWM mode 1 (triangle wave) is set */
        uint32_t IntCycle;      /* Choose PWM interrupt cycle */
        uint32_t CarrierMode;   /* Specify PWM carrier wave */
        uint32_t CycleTiming;   /* Set PWM cycle */
    } PMD_InitTypeDef;

/** @} */
/* End of PMD_Exported_types */

/** @defgroup PMD_Exported_Constants
  * @{
  */
#define PMD0                               TSB_MTPD0
#define IS_PMD_PERIPH(param)               ((param) == PMD0)

#define PMD_PORT_HIGH_IMPEDANCE            ((uint32_t)0x00000000)       /* High-impedance */
#define PMD_PORT_PMD_OUTPUT                ((uint32_t)0x00000001)       /* PMD output */
#define IS_PMD_PORT_MODE(param)            ((param) <= PMD_PORT_PMD_OUTPUT)

#define PMD_PWM_NORMAL_CYCLE               ((uint32_t)0x00000000)       /* Normal cycle */
#define PMD_PWM_4_FOLD_CYCLE               ((uint32_t)0x00000001)       /* 4-fold cycle */
#define IS_PMD_CYCLE_MODE(param)           ((param) <= PMD_PWM_4_FOLD_CYCLE)

#define PMD_DUTY_MODE_U_PHASE              ((uint32_t)0x00000000)       /* U-phase in common */
#define PMD_DUTY_MODE_3_PHASE              ((uint32_t)0x00000001)       /* 3-phase independent */
#define IS_PMD_DUTY_MODE(param)            ((param) <= PMD_DUTY_MODE_3_PHASE)

#define PMD_PWM_INT_TIMING_MINIMUM         ((uint32_t)0x00000000)       /* When PWM count MDCNT="1" is set, (minimum) interrupt request occurs */
#define PMD_PWM_INT_TIMING_MAXIMUM         ((uint32_t)0x00000001)       /* When PWM count MDCNT=MTPDxMDPRD<MDPRD> is set, (maximum) interrupt request occurs */
#define IS_PMD_PWM_INT_TIMING(param)       ((param) <= PMD_PWM_INT_TIMING_MAXIMUM)

#define PMD_PWM_INT_CYCLE_HALF             ((uint32_t)0x00000000)       /* Every PWM 0.5 cycle (can be set in PWM mode1 (triangle wave) */
#define PMD_PWM_INT_CYCLE_1                ((uint32_t)0x00000001)       /* Every PWM 1 cycle */
#define PMD_PWM_INT_CYCLE_2                ((uint32_t)0x00000002)       /* Every PWM 2 cycles */
#define PMD_PWM_INT_CYCLE_4                ((uint32_t)0x00000003)       /* Every PWM 4 cycles */
#define IS_PMD_PWM_INT_CYCLE_MODE_0(param) (((param) == PMD_PWM_INT_CYCLE_1)||\
                                            ((param) == PMD_PWM_INT_CYCLE_2)||\
                                            ((param) == PMD_PWM_INT_CYCLE_4))

#define IS_PMD_PWM_INT_CYCLE_MODE_1(param) (((param) == PMD_PWM_INT_CYCLE_HALF)||\
                                            ((param) == PMD_PWM_INT_CYCLE_1)||\
                                            ((param) == PMD_PWM_INT_CYCLE_2)||\
                                            ((param) == PMD_PWM_INT_CYCLE_4))

#define PMD_CARRIER_WAVE_MODE_0            ((uint32_t)0x00000000)       /* PWM mode 0 (edge PWM, sawtooth) */
#define PMD_CARRIER_WAVE_MODE_1            ((uint32_t)0x00000001)       /* PWM mode 1 (center PWM, triangle wave) */
#define IS_PMD_CARRIER_WAVE_MODE(param)    ((param) <= PMD_CARRIER_WAVE_MODE_1)

#define PMD_COUNTER_UP                     ((uint32_t)0x00000000)       /* Up-counting */
#define PMD_COUNTER_DOWN                   ((uint32_t)0x00000001)       /* Down-counting */

#define PMD_PHASE_U                        ((uint32_t)0x00000000)
#define PMD_PHASE_V                        ((uint32_t)0x00000001)
#define PMD_PHASE_W                        ((uint32_t)0x00000002)
#define PMD_PHASE_ALL                      ((uint32_t)0x00000003)
#define IS_PMD_PHASE(param)                ((param) <= PMD_PHASE_ALL)

#define PMD_PORT_OUTPUT_MODE_0             ((uint32_t)0x00000000)
#define PMD_PORT_OUTPUT_MODE_1             ((uint32_t)0x00000001)
#define IS_PMD_PORT_OUTPUT_MODE(param)     ((param) <= PMD_PORT_OUTPUT_MODE_1)

#define PMD_OUTPUT_PHASE_LOWER             ((uint32_t)0x00000000)       /* Lower phase output port */
#define PMD_OUTPUT_PHASE_UPPER             ((uint32_t)0x00000001)       /* Upper phase output port */
#define IS_PMD_OUTPUT_PHASE(param)         ((param) <= PMD_OUTPUT_PHASE_UPPER)

#define PMD_POLARITY_LOW                   ((uint32_t)0x00000000)       /* Low active */
#define PMD_POLARITY_HIGH                  ((uint32_t)0x00000001)       /* High active */
#define IS_PMD_POLARITY(param)             ((param) <= PMD_POLARITY_HIGH)

#define PMD_REFLECTED_TIME_WRITE           ((uint32_t)0x00000000)       /* Reflect when write */
#define PMD_REFLECTED_TIME_MIN             ((uint32_t)0x00000001)       /* Reflect when PWM counter MDCNT="1"(minimum) */
#define PMD_REFLECTED_TIME_MAX             ((uint32_t)0x00000002)       /* Reflect when PWM counter MDCNT=MTPDxMDPRD<MDPRD>(maximum) */
#define PMD_REFLECTED_TIME_MIN_MAX         ((uint32_t)0x00000003)       /* Reflect when PWM counter MDCNT="1"(minimum) or MTPDxMDPRD<MDPRD>(maximum) */
#define IS_PMD_REFLECTED_TIME(param)       ((param) <= PMD_REFLECTED_TIME_MIN_MAX)

#define PMD_NOISE_ELIMINATION_NONE         ((uint32_t)0x00000000)       /* Noise filter is not used */
#define PMD_NOISE_ELIMINATION_16           ((uint32_t)0x00000001)       /* Input noise elimination time 1*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_32           ((uint32_t)0x00000002)       /* Input noise elimination time 2*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_48           ((uint32_t)0x00000003)       /* Input noise elimination time 3*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_64           ((uint32_t)0x00000004)       /* Input noise elimination time 4*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_80           ((uint32_t)0x00000005)       /* Input noise elimination time 5*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_96           ((uint32_t)0x00000006)       /* Input noise elimination time 6*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_112          ((uint32_t)0x00000007)       /* Input noise elimination time 7*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_128          ((uint32_t)0x00000008)       /* Input noise elimination time 8*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_144          ((uint32_t)0x00000009)       /* Input noise elimination time 9*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_160          ((uint32_t)0x0000000A)       /* Input noise elimination time 10*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_176          ((uint32_t)0x0000000B)       /* Input noise elimination time 11*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_192          ((uint32_t)0x0000000C)       /* Input noise elimination time 12*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_208          ((uint32_t)0x0000000D)       /* Input noise elimination time 13*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_224          ((uint32_t)0x0000000E)       /* Input noise elimination time 14*16/fsys[s] */
#define PMD_NOISE_ELIMINATION_240          ((uint32_t)0x0000000F)       /* Input noise elimination time 15*16/fsys[s] */
#define IS_PMD_NOISE_ELIMINATION(param)    ((param) <= PMD_NOISE_ELIMINATION_240)

#define PMD_BREAK_STATUS_PMD               ((uint32_t)0x00000000)       /* PMD output is continued */
#define PMD_BREAK_STATUS_HIGH_IMPEDANCE    ((uint32_t)0x00000001)       /* High-impedance */
#define IS_PMD_BREAK_STATUS(param)         ((param) <= PMD_BREAK_STATUS_HIGH_IMPEDANCE)

#define PMD_EMG_MODE_0                     ((uint32_t)0x00000000)       /* All phase are on/PORT output and high-impedance */
#define PMD_EMG_MODE_1                     ((uint32_t)0x00000001)       /* All phase are off/PORT output and high-impedance */
#define PMD_EMG_MODE_2                     ((uint32_t)0x00000002)       /* All phase are on/PORT output is enabled. */
#define PMD_EMG_MODE_3                     ((uint32_t)0x00000003)       /* All phase are off/PORT output is high-impedance. */
#define IS_PMD_EMG_MODE(param)             ((param) <= PMD_EMG_MODE_3)

#define PMD_TRG_MODE_0                     ((uint32_t)0x00000000)       /* Trigger output disabled */
#define PMD_TRG_MODE_1                     ((uint32_t)0x00000001)       /* Trigger output at down-count match  */
#define PMD_TRG_MODE_2                     ((uint32_t)0x00000002)       /* Trigger output at up-count match */
#define PMD_TRG_MODE_3                     ((uint32_t)0x00000003)       /* Trigger output at up-/down-count match */
#define PMD_TRG_MODE_4                     ((uint32_t)0x00000004)       /* Trigger output at PWM carrier peak */
#define PMD_TRG_MODE_5                     ((uint32_t)0x00000005)       /* Trigger output at PWM carrier bottom */
#define PMD_TRG_MODE_6                     ((uint32_t)0x00000006)       /* Trigger output at PWM carrier peak/bottom */
#define PMD_TRG_MODE_7                     ((uint32_t)0x00000007)       /* Trigger output disabled */
#define IS_PMD_TRG_MODE(param)             ((param) <= PMD_TRG_MODE_7)

#define PMD_TRG_UPDATE_SYNC                ((uint32_t)0x00000000)
#define PMD_TRG_UPDATE_ASYNC               ((uint32_t)0x00000001)
#define IS_PMD_TRG_TIMING(param)           ((param) <= PMD_TRG_UPDATE_ASYNC)

#define PMD_ABNORMAL_LEVEL_L               ((uint32_t)0x00000000)       /* Abnormal condition input level is "L" */
#define PMD_ABNORMAL_LEVEL_H               ((uint32_t)0x00000002)       /* Abnormal condition input level is "H" */

#define PMD_ADC_TRG_0                      ((uint32_t)0x00000000)       /* Select trigger 0 */
#define IS_PMD_ADC_TRG(param)              ((param) <= PMD_ADC_TRG_0)

#define IS_PMD_VALUE(param)                ((param) <= 0x0000FFFFU)
#define IS_PMD_DEAD_TIME(param)            ((param) <= 0x000000FFU)

#define PMD_OUTPUT_L_L                     ((uint8_t)0x00)
#define PMD_OUTPUT_L_H                     ((uint8_t)0x01)
#define PMD_OUTPUT_H_L                     ((uint8_t)0x02)
#define PMD_OUTPUT_H_H                     ((uint8_t)0x03)
#define PMD_OUTPUT_IPWM_PWM                ((uint8_t)0x04)

#define PMD_OUTPUT_PWM_IPWM                ((uint8_t)0x07)
#define PMD_OUTPUT_L_PWM                   ((uint8_t)0x05)
#define PMD_OUTPUT_L_IPWM                  ((uint8_t)0x05)
#define PMD_OUTPUT_IPWM_H                  ((uint8_t)0x05)

#define PMD_OUTPUT_PWM_L                   ((uint8_t)0x06)
#define PMD_OUTPUT_H_IPWM                  ((uint8_t)0x06)
#define PMD_OUTPUT_H_PWM                   ((uint8_t)0x06)

#define IS_PMD_OUTPUT(param)               ((param) <= 7U)


/** @} */
/* End of group PMD_Exported_Constants */


/** @defgroup PMD_Exported_FunctionPrototypes
  * @{
  */
    void PMD_Enable(TSB_MTPD_TypeDef * PMDx);
    void PMD_Disable(TSB_MTPD_TypeDef * PMDx);
    void PMD_SetPortControl(TSB_MTPD_TypeDef * PMDx, uint32_t PortMode);
    void PMD_Init(TSB_MTPD_TypeDef * PMDx, PMD_InitTypeDef * InitStruct);
    void PMD_ChangePWMCycle(TSB_MTPD_TypeDef * PMDx, uint32_t CycleTiming);
    uint32_t PMD_GetCntFlag(TSB_MTPD_TypeDef * PMDx);
    uint16_t PMD_GetCntValue(TSB_MTPD_TypeDef * PMDx);
    void PMD_SetCompareValue(TSB_MTPD_TypeDef * PMDx, uint32_t PMDPhase, uint32_t Timing);
    void PMD_SetPortOutputMode(TSB_MTPD_TypeDef * PMDx, uint32_t Mode);
    void PMD_SetOutputPhasePolarity(TSB_MTPD_TypeDef * PMDx, uint32_t OutputPhase,
                                    uint32_t Polarity);
    void PMD_SetReflectTime(TSB_MTPD_TypeDef * PMDx, uint32_t ReflectedTime);
    void PMD_EnableEMG(TSB_MTPD_TypeDef * PMDx);
    void PMD_DisableEMG(TSB_MTPD_TypeDef * PMDx);
    void PMD_SetEMGNoiseElimination(TSB_MTPD_TypeDef * PMDx, uint32_t NoiseElimination);
    void PMD_SetToolBreakOutput(TSB_MTPD_TypeDef * PMDx, uint32_t Status);
    void PMD_SetEMGMode(TSB_MTPD_TypeDef * PMDx, uint32_t Mode);
    void PMD_EMGRelease(TSB_MTPD_TypeDef * PMDx);
    uint32_t PMD_GetEMGAbnormalLevel(TSB_MTPD_TypeDef * PMDx);
    uint32_t PMD_GetEMGCondition(TSB_MTPD_TypeDef * PMDx);
    void PMD_SetDeadTime(TSB_MTPD_TypeDef * PMDx, uint32_t Time);
    void PMD_SetAllPhaseCompareValue(TSB_MTPD_TypeDef * PMDx, uint32_t UPhaseTiming,
                                     uint32_t VPhaseTiming, uint32_t WPhaseTiming);
    void PMD_ChangeDutyMode(TSB_MTPD_TypeDef * PMDx, uint32_t DutyMode);
    Result PMD_SetPortOutput(TSB_MTPD_TypeDef * PMDx, uint32_t PMDPhase, uint8_t Output);
    void PMD_SetTrgMode(TSB_MTPD_TypeDef * PMDx, uint32_t PMDTrg, uint32_t Mode);
    void PMD_SetTrgUpdate(TSB_MTPD_TypeDef * PMDx, uint32_t PMDTrg, uint32_t UpdateTiming);
    void PMD_SetEMGTrg(TSB_MTPD_TypeDef * PMDx, FunctionalState NewState);
    void PMD_SetTrgCmpValue(TSB_MTPD_TypeDef * PMDx, uint32_t TRGCMP0Timing);
/** @} */
/* End of group PMD_Exported_FunctionPrototypes */

/** @} */
/* End of group PMD */

/** @} */
/* End of group TX03_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_PMD_H */
