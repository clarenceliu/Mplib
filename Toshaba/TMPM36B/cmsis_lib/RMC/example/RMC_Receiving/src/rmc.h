/** 
 *******************************************************************************
 * @file    rmc.h
 * @brief   the application functions of RMC_Receiving demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RMC_H
#define __RMC_H

/* Includes ------------------------------------------------------------------*/
#include "RMC_Receiving.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum { RMC_NON = 0, RMC_DONE = 1 } RMCSTAT;
typedef enum { RELEASE = 0, PRESS = 1 } RMCPRS;
typedef union tag_IO_SFR32_u {
    uint32_t reg;
    uint8_t byte[4];
} IO_SFR32_u;

/* Private define ------------------------------------------------------------*/
/**************   CHOOSE ONE FORMAT   **************/
/*  #define RMC_1 */
/*  #define RMC_2 */
/*  #define RMC_3 */
/*  #define RMC_4 */
/*  #define RMC_5 */
#define RMC_6

#ifdef RMC_1                    /*TOSHIBA format */
/************** FOR RMC_1 FORMAT ****************/
#define RMC_MAX_CYCLE                   ((uint8_t)0x71U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x5AU)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x4CU)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x49U)

#define RMC_TRG_LOW_WIDTH               ((uint8_t)0xFFU)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0xFEU)

#define RMC_LARGER_THRESHOLD            ((uint8_t)0x00U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x2EU)

#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x0DU)
#endif

#ifdef RMC_2                    /*RC5 */
/************** FOR RMC_2 FORMAT ****************/
/* no leader */
#define RMC_MAX_CYCLE                   ((uint8_t)0x00U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x00U)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x00U)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x00U)

#define RMC_TRG_LOW_WIDTH               ((uint8_t)0x47U)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0x83U)

#define RMC_LARGER_THRESHOLD            ((uint8_t)0x63U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x44U)

#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x0FU)

#endif

#ifdef RMC_3                    /*¼ÒÑu…f */
/************** FOR RMC_3 FORMAT ****************/
#define RMC_MAX_CYCLE                   ((uint8_t)0x21U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x17U)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x11U)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x0BU)

#define RMC_TRG_LOW_WIDTH               ((uint8_t)0xFFU)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0x62U)

#define RMC_LARGER_THRESHOLD            ((uint8_t)0x00U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x27U)

#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x00U)
#endif

#ifdef RMC_4 /*SONY*/
/************** FOR RMC_4 FORMAT ****************/
#define RMC_MAX_CYCLE                   ((uint8_t)0x19U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x0FU)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x00U)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x00U)
#define RMC_TRG_LOW_WIDTH               ((uint8_t)0xFFU)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0x85U)
#define RMC_LARGER_THRESHOLD            ((uint8_t)0x00U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x31U)
#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x0DU)
#endif
#ifdef RMC_5 /*SHARP*/
/************** FOR RMC_5 FORMAT ****************/
/* no leader */
#define RMC_MAX_CYCLE                   ((uint8_t)0x00U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x00U)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x00U)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x00U)
#define RMC_TRG_LOW_WIDTH               ((uint8_t)0xFFU)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0x85U)
#define RMC_LARGER_THRESHOLD            ((uint8_t)0x00U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x32U)
#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x03U)
#endif
#ifdef RMC_6 /*NEC*/
/************** FOR RMC_6 FORMAT ****************/
#define RMC_MAX_CYCLE                   ((uint8_t)0x52U)
#define RMC_MIN_CYCLE                   ((uint8_t)0x42U)
#define RMC_MAX_LOW_WIDTH               ((uint8_t)0x29U)
#define RMC_MIN_LOW_WIDTH               ((uint8_t)0x21U)
#define RMC_TRG_LOW_WIDTH               ((uint8_t)0xFFU)
#define RMC_TRG_MAX_DATA_BIT_CYCLE      ((uint8_t)0xFEU)
#define RMC_LARGER_THRESHOLD            ((uint8_t)0x00U)
#define RMC_SMALLER_THRESHOLD           ((uint8_t)0x25U)
#define RMC_NOISE_CANCELLATION_TIME     ((uint8_t)0x03U)
#endif
/* external variables --------------------------------------------------------*/
extern RMCSTAT fRMCDone;
extern RMCPRS fRMCPress;
/* Private function prototypes -----------------------------------------------*/
void RMC_Configuration(TSB_RMC_TypeDef * RMCx);
void RMC_ChInit(TSB_RMC_TypeDef * RMCx);
void RMCRcv(void);

#endif                          /* __RMC_H */
