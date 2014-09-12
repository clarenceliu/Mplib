/**
 *******************************************************************************
 * @file    tmpm36b_fc.h
 * @brief   This file provides all the functions prototypes for FC driver.
 * @version V2.0.2.3
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __TMPM36B_FC_H
#define __TMPM36B_FC_H


/* #define SINGLE_BOOT_MODE */

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "TMPM36B.h"
#include "tx03_common.h"

/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @addtogroup FC
  * @{
  */

/** @defgroup FC_Exported_Types
  * @{
  */
    typedef enum {
        FC_SUCCESS = 0U,
        FC_ERROR_PROTECTED = 1U,
        FC_ERROR_OVER_TIME = 2U
    } FC_Result;

/** @} */
/* End of group FC_Exported_Types */

/** @defgroup FC_Exported_Constants
  * @{
  */
#ifdef TSB_M36BFY
#define FLASH_PAGE_SIZE                 ((uint32_t)0x00000100)  /* TSB_M36BFY Page size is 256 Byte */
#elif defined (TSB_M36BF10 )
#define FLASH_PAGE_SIZE                 ((uint32_t)0x00000200)  /* TSB_M36BF10 Page size is 512 Byte */
#endif

#define FC_BLOCK_0                      ((uint8_t)0x00)
#define FC_BLOCK_1                      ((uint8_t)0x01)
#define FC_BLOCK_2                      ((uint8_t)0x02)
#define FC_BLOCK_3                      ((uint8_t)0x03)
#define FC_BLOCK_4                      ((uint8_t)0x04)
#define FC_BLOCK_5                      ((uint8_t)0x05)

#ifdef TSB_M36BF10              /* TSB_M36BF10 has more than 4 BLOCK */
#define FC_BLOCK_6                      ((uint8_t)0x06)
#define FC_BLOCK_7                      ((uint8_t)0x07)
#define FC_BLOCK_8                      ((uint8_t)0x08)
#define FC_BLOCK_9                      ((uint8_t)0x09)
#endif

#define FC_BLOCK_GROUP_0                 ((uint8_t)0x00)
#define FC_BLOCK_GROUP_1                 ((uint8_t)0x01)

#ifdef TSB_M36BF10              /* TSB_M36BF10 has 3 GROUP */
#define FC_BLOCK_GROUP_2                 ((uint8_t)0x02)
#endif

#ifdef TSB_M36BFY
#define FLASH_CHIP_SIZE                 ((uint32_t)0x00040000)  /* TSB_M36BFY Flash chip size is 256KByte */
#elif defined (TSB_M36BF10 )
#define FLASH_CHIP_SIZE                 ((uint32_t)0x00100000)  /* TSB_M36BF10 Flash chip size is 1024KByte */
#endif

#ifdef TSB_M36BFY
#define IS_FC_BLOCK_NUM(param)          (((param) == FC_BLOCK_0) || \
                                         ((param) == FC_BLOCK_1) || \
                                         ((param) == FC_BLOCK_2) || \
                                         ((param) == FC_BLOCK_3) || \
                                         ((param) == FC_BLOCK_4) || \
                                         ((param) == FC_BLOCK_5))
#elif defined (TSB_M36BF10 )
#define IS_FC_BLOCK_NUM(param)          (((param) == FC_BLOCK_0) || \
                                         ((param) == FC_BLOCK_1) || \
                                         ((param) == FC_BLOCK_2) || \
                                         ((param) == FC_BLOCK_3) || \
                                         ((param) == FC_BLOCK_4) || \
                                         ((param) == FC_BLOCK_5) || \
                                         ((param) == FC_BLOCK_6) || \
                                         ((param) == FC_BLOCK_7) || \
                                         ((param) == FC_BLOCK_8) || \
                                         ((param) == FC_BLOCK_9))
#endif

#ifdef TSB_M36BFY
#define IS_FC_BLOCK_GROUP(param)        (((param) == FC_BLOCK_GROUP_0) || \
                                         ((param) == FC_BLOCK_GROUP_1))
#elif defined (TSB_M36BF10 )
#define IS_FC_BLOCK_GROUP(param)        (((param) == FC_BLOCK_GROUP_0) || \
                                         ((param) == FC_BLOCK_GROUP_1) || \
                                         ((param) == FC_BLOCK_GROUP_2))
#endif

#ifdef SINGLE_BOOT_MODE
#define FLASH_START_ADDR                 ((uint32_t)0x3F800000) /* SINGLE_BOOT_MODE */
#else
#define FLASH_START_ADDR                 ((uint32_t)0x00000000) /* User Boot Mode As Default */
#endif

#define FLASH_END_ADDR                       (FLASH_START_ADDR + FLASH_CHIP_SIZE - 1U)

#ifdef SINGLE_BOOT_MODE
#define IS_FC_ADDR(param)                (((param) >= FLASH_START_ADDR) && \
                                          ((param) <= FLASH_END_ADDR))
#else
#define IS_FC_ADDR(param)                ((param) <= FLASH_END_ADDR)
#endif

#define IS_FC_PAGE_ADDR(param)          ((((param) - FLASH_START_ADDR) % FLASH_PAGE_SIZE) == 0U)

/** @} */
/* End of group FC_Exported_Constants */


/** @defgroup FC_Exported_FunctionPrototypes
  * @{
  */

    void FC_SetSecurityBit(FunctionalState NewState);
    FunctionalState FC_GetSecurityBit(void);
    WorkState FC_GetBusyState(void);
    FunctionalState FC_GetBlockProtectState(uint8_t BlockNum);
    FC_Result FC_ProgramBlockProtectState(uint8_t BlockNum);
    FC_Result FC_EraseBlockProtectState(uint8_t BlockGroup);
    FC_Result FC_WritePage(uint32_t PageAddr, uint32_t * Data);
    FC_Result FC_EraseBlock(uint32_t BlockAddr);
    FC_Result FC_EraseChip(void);

/** @} */
/* End of group FC_Exported_FunctionPrototypes */

/** @} */
/* End of group FC */

/** @} */
/* End of group TX03_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM36B_FC_H */
