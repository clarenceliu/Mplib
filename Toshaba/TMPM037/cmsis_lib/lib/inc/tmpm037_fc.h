/**
 *******************************************************************************
 * @file    tmpm037_fc.h
 * @brief   This file provides all the functions prototypes for FC driver.
 * @version V2.0.2.2
 * @date    2014/02/17
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM037_FC_H
#define __TMPM037_FC_H


/* #define SINGLE_BOOT_MODE */

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "TMPM037.h"
#include "tx00_common.h"

#if defined(__TMPM037_FC_H)
/** @addtogroup TX00_Periph_Driver
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

#define FLASH_PAGE_SIZE                 ((uint32_t)0x00000080)  /* Page Size 128 Byte/32 words */

#define FC_BLOCK_0                      ((uint8_t)0x00)
#define FC_BLOCK_1                      FC_BLOCK_0 + 1U
#define FC_BLOCK_2                      FC_BLOCK_1 + 1U
#define FC_BLOCK_3                      FC_BLOCK_2 + 1U


#define FLASH_CHIP_SIZE                 ((uint32_t)0x00020000)  /* Flash chip size is 128KByte */
#define FC_BLOCK_MAX    FC_BLOCK_3

#define IS_FC_BLOCK_NUM(param)          ((param) <= FC_BLOCK_MAX)

#define FC_BLOCK_GROUP_0                 ((uint8_t)0x00)

#define IS_FC_BLOCK_GROUP(param)        ((param) == FC_BLOCK_GROUP_0)

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
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM037_FC_H) */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM037_FC_H */
