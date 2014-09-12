/**
 *******************************************************************************
 * @file    tmpm037_dmac.h
 * @brief   This file provides all the functions prototypes for DMAC driver.
 * @version V2.0.2.1
 * @date    2014/02/10
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_DMAC_H
#define __TMPM037_DMAC_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tx00_common.h"

#if defined(__TMPM037_DMAC_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @addtogroup DMAC
  * @{
  */

/** @defgroup DMAC_Exported_Constants
  * @{
  */

#define IS_DMAC_TX_SIZE(param)   ((param) <= 0x0FFFU)
#define IS_DMAC_LINK_ADDR_MAX_VALUE(param)   ((param) <= 0xFFFFFFF0U)

#define DMAC_MEMORY_TO_MEMORY         ((uint32_t)0x00000000)
#define DMAC_MEMORY_TO_PERIPH         ((uint32_t)0x00000800)
#define DMAC_PERIPH_TO_MEMORY         ((uint32_t)0x00001000)
#define DMAC_PERIPH_TO_PERIPH         ((uint32_t)0x00001800)
#define IS_DMAC_TX_DIRECTION(param) (((param) == DMAC_MEMORY_TO_MEMORY) || \
                                     ((param) == DMAC_MEMORY_TO_PERIPH) || \
                                     ((param) == DMAC_PERIPH_TO_PERIPH) || \
                                     ((param) == DMAC_PERIPH_TO_MEMORY))

/** @} */
/* End of group DMAC_Exported_Constants */

/** @defgroup DMAC_Exported_Types
  * @{
  */
    typedef enum {
        DMAC_CHANNEL_0 = 0U,
        DMAC_CHANNEL_1 = 1U
    } DMAC_Channel;
#define IS_DMAC_CHANNEL(param) (((param) == DMAC_CHANNEL_0) || \
                                ((param) == DMAC_CHANNEL_1))

    typedef enum {
        DMAC_BYTE = 0U,
        DMAC_HALF_WORD = 1U,
        DMAC_WORD = 2U
    } DMAC_BitWidth;
#define IS_DMAC_BIT_WIDTH(param) (((param) == DMAC_BYTE) || \
                                  ((param) == DMAC_HALF_WORD) || \
                                  ((param) == DMAC_WORD))

    typedef enum {
        DMAC_TX_NO_REQ = 0U,
        DMAC_TX_END_REQ = 1U,
        DMAC_TX_ERR_REQ = 2U,
        DMAC_TX_REQS = 3U
    } DMAC_TxINTReq;

    typedef union {
        uint32_t All;
        struct {
            uint32_t CH0_INTReq:1;
            uint32_t CH1_INTReq:1;
        } Bit;
    } DMAC_INTReq;

    typedef enum {
        DMAC_INT_TX_END = 0U,
        DMAC_INT_TX_ERR = 1U
    } DMAC_INTSrc;

#define IS_DMAC_INT_SRC(param)  (((param) == DMAC_INT_TX_END) || \
                                 ((param) == DMAC_INT_TX_ERR))

    typedef enum {
        DMAC_1_BEAT = 0U,
        DMAC_4_BEATS = 1U,
        DMAC_8_BEATS = 2U,
        DMAC_16_BEATS = 3U,
        DMAC_32_BEATS = 4U,
        DMAC_64_BEATS = 5U,
        DMAC_128_BEATS = 6U,
        DMAC_256_BEATS = 7U
    } DMAC_BurstSize;

#define IS_DMAC_BURST_SIZE(param)  (((param) == DMAC_1_BEAT) || \
                                    ((param) == DMAC_4_BEATS) || \
                                    ((param) == DMAC_8_BEATS) || \
                                    ((param) == DMAC_16_BEATS) || \
                                    ((param) == DMAC_32_BEATS) || \
                                    ((param) == DMAC_64_BEATS) || \
                                    ((param) == DMAC_128_BEATS) || \
                                    ((param) == DMAC_256_BEATS))

    typedef enum {
        DMAC_SIO0_UART0_RX = 0U,
        DMAC_SIO0_UART0_TX = 1U,
        DMAC_SIO1_UART1_RX = 2U,
        DMAC_SIO1_UART1_TX = 3U,
        DMAC_SIO2_UART2_RX = 4U,
        DMAC_SIO2_UART2_TX = 5U,
        DMAC_SIO3_UART3_RX = 6U,
        DMAC_SIO3_UART3_TX = 7U,
        DMAC_I2C0_RX_TX = 8U,
        DMAC_SIO4_UART4_RX = 10U,
        DMAC_SIO4_UART4_TX = 11U,
        DMAC_TMRB0_3 = 12U,
        DMAC_TMRB4_7 = 13U,
        DMAC_TOP_PRIORITY_ADC = 14U,
        DMAC_AD_CONVERT_COMPLETE = 15U
    } DMAC_ReqNum;

#define IS_DMAC_REQ_NUM(param)  (((param) == DMAC_SIO0_UART0_RX) || \
                                   ((param) == DMAC_SIO0_UART0_TX) || \
                                   ((param) == DMAC_SIO1_UART1_RX) || \
                                   ((param) == DMAC_SIO1_UART1_TX) || \
                                   ((param) == DMAC_SIO2_UART2_RX) || \
                                   ((param) == DMAC_SIO2_UART2_TX) || \
                                   ((param) == DMAC_SIO3_UART3_RX) || \
                                   ((param) == DMAC_SIO3_UART3_TX) || \
                                   ((param) == DMAC_I2C0_RX_TX) || \
                                   ((param) == DMAC_SIO4_UART4_RX) || \
                                   ((param) == DMAC_SIO4_UART4_TX) || \
                                   ((param) == DMAC_TMRB0_3) || \
                                   ((param) == DMAC_TMRB4_7) || \
                                   ((param) == DMAC_TOP_PRIORITY_ADC) || \
                                   ((param) == DMAC_AD_CONVERT_COMPLETE ))

#define IS_DMAC_BURST_REQ_NUM(param)  (((param) == DMAC_SIO0_UART0_RX) || \
                                   ((param) == DMAC_SIO0_UART0_TX) || \
                                   ((param) == DMAC_SIO1_UART1_RX) || \
                                   ((param) == DMAC_SIO1_UART1_TX) || \
                                   ((param) == DMAC_SIO2_UART2_RX) || \
                                   ((param) == DMAC_SIO2_UART2_TX) || \
                                   ((param) == DMAC_SIO3_UART3_RX) || \
                                   ((param) == DMAC_SIO3_UART3_TX) || \
                                   ((param) == DMAC_I2C0_RX_TX) || \
                                   ((param) == DMAC_SIO4_UART4_RX) || \
                                   ((param) == DMAC_SIO4_UART4_TX) || \
                                   ((param) == DMAC_TMRB0_3) || \
                                   ((param) == DMAC_TMRB4_7) || \
                                   ((param) == DMAC_TOP_PRIORITY_ADC) || \
                                   ((param) == DMAC_AD_CONVERT_COMPLETE ))

    typedef union {
        uint32_t All;
        struct {
            uint32_t SIO0_UART0_RX:1;
            uint32_t SIO0_UART0_TX:1;
            uint32_t SIO1_UART1_RX:1;
            uint32_t SIO1_UART1_TX:1;
            uint32_t SIO2_UART2_RX:1;
            uint32_t SIO2_UART2_TX:1;
            uint32_t SIO3_UART3_RX:1;
            uint32_t SIO3_UART3_TX:1;
            uint32_t I2C0_RX_TX:1;
            uint32_t Reserved1:1;
            uint32_t SIO4_UART4_RX:1;
            uint32_t SIO4_UART4_TX:1;
            uint32_t TMRB0_3:1;
            uint32_t TMRB4_7:1;
            uint32_t TOP_PRIORITY_ADC:1;
            uint32_t AD_CONVERT_COMPLETE:1;
            uint32_t Reserved2:16;
        } Bit;
    } DMAC_BurstReqState;

/** @} */
/* End of group DMAC_Exported_Types */

/** @defgroup DMAC_Exported_Types
  * @{
  */

/** 
  * @brief  DMA Structure definition  
  */

    typedef struct {
        uint32_t TxDirection;   /*!< Set transfer direction  */
        uint32_t SrcAddr;       /*!< Set source address  */
        uint32_t DstAddr;       /*!< Set destination address  */
        FunctionalState SrcIncrementState;      /*!< Specifies whether the source
                                                   address is incremented or not  */
        FunctionalState DstIncrementState;      /*!< Specifies whether the destination
                                                   address is incremented or not  */
        DMAC_BitWidth SrcBitWidth;      /*!< Set transfer source bit width  */
        DMAC_BitWidth DstBitWidth;      /*!< Set transfer destination bit width  */
        DMAC_BurstSize SrcBurstSize;    /* Set transfer source burst size */
        DMAC_BurstSize DstBurstSize;    /* Set transfer destination burst size */
        uint32_t TxSize;        /*!< Set the total number of transfer  */
        DMAC_ReqNum TxDstPeriph;        /*!< Set transfer destination  */
        DMAC_ReqNum TxSrcPeriph;        /*!< Set transfer source peripheral  */
        FunctionalState TxINT;  /*!< Set transfer interrupt */
    } DMAC_InitTypeDef;

/** @} */
/* End of group DMAC_Exported_Types */

/** @defgroup DMAC_Exported_FunctionPrototypes
  * @{
  */
    void DMAC_Enable(void);
    void DMAC_Disable(void);
    DMAC_INTReq DMAC_GetINTReq(void);
    DMAC_TxINTReq DMAC_GetTxINTReq(DMAC_Channel Chx);
    void DMAC_ClearTxINTReq(DMAC_Channel Chx, DMAC_INTSrc INTSource);
    DMAC_TxINTReq DMAC_GetRawTxINTReq(DMAC_Channel Chx);
    WorkState DMAC_GetChannelTxState(DMAC_Channel Chx);
    void DMAC_SetSWBurstReq(DMAC_ReqNum BurstReq);
    DMAC_BurstReqState DMAC_GetSWBurstReqState(void);
    void DMAC_SetLinkedList(DMAC_Channel Chx, uint32_t LinkedAddr);
    WorkState DMAC_GetFIFOState(DMAC_Channel Chx);
    void DMAC_SetDMAHalt(DMAC_Channel Chx, FunctionalState NewState);
    void DMAC_SetLockedTx(DMAC_Channel Chx, FunctionalState NewState);
    void DMAC_SetTxINTConfig(DMAC_Channel Chx, DMAC_INTSrc INTSource, FunctionalState NewState);
    void DMAC_SetDMAChannel(DMAC_Channel Chx, FunctionalState NewState);
    void DMAC_Init(DMAC_Channel Chx, DMAC_InitTypeDef * InitStruct);
/** @} */
/* End of group DMAC_Exported_FunctionPrototype */

/** @} */
/* End of group DMAC */

/** @} */
/* End of group TX00_Periph_Driver */

#endif                          /* defined(__TMPM037_DMAC_H) */

#ifdef __cplusplus
}
#endif
#endif                          /* __TMPM037_DMAC_H */
