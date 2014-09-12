/**
 *******************************************************************************
 * @file    tmpm36b_ofd.h
 * @brief   This file provides all the functions prototypes for OFD driver.
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_OFD_H
#define __TMPM36B_OFD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
  * @{
  */
/** @addtogroup OFD
  * @{
  */
/** @addtogroup OFD_Exported_Types
  * @{
  */
#define IS_OFD_DETECT_FREQ_HIGHER(param)    ((param) <= 0x000001FFU)
#define IS_OFD_DETECT_FREQ_LOWER(param)     ((param) <= 0x000001FFU)

    typedef enum {
        OFD_IHOSC = 0U,         /* Internal High Frequency Oscillation */
        OFD_EHOSC = 1U          /* External High Frequency Oscillation */
    } OFD_OSCSource;
#define IS_OFD_OSC_SOURCE(param)            ((param) <= OFD_EHOSC)

    typedef enum {
        OFD_NORMAL = 0U,        /* Normal Detection Mode */
        OFD_MONITOR = 1U        /* Monitor Mode */
    } OFD_MonitorMode;
#define IS_OFD_MONITOR_MODE(param)          ((param) <= OFD_MONITOR)

    typedef union {
        uint32_t All;
        struct {
            uint32_t FrequencyError:1;
            uint32_t OFDBusy:1;
        } Bit;
    } OFD_Status;

/** @} */
/* End of group OFD_Exported_Types */

/** @defgroup OFD_Exported_FunctionPrototypes
  * @{
  */
    void OFD_SetRegWriteMode(FunctionalState NewState);
    void OFD_Enable(void);
    void OFD_Disable(void);
    void OFD_SetDetectionFrequency(OFD_OSCSource Source, uint32_t HigherDetectionCount,
                                   uint32_t LowerDetectionCount);
    void OFD_Reset(FunctionalState NewState);
    OFD_Status OFD_GetStatus(void);
    void OFD_SetDetectionMonitor(OFD_MonitorMode Mode);

/** @} */
/* End of group OFD_Exported_FunctionPrototypes */
/** @} */
/* End of group OFD */
/** @} */
/* End of group TX03_Periph_Driver */
#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_OFD_H */
