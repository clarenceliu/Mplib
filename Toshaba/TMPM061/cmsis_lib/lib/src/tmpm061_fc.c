/**
 *******************************************************************************
 * @file    tmpm061_fc.c
 * @brief   This file provides API functions for FC driver.
 * @version V2.0.2.1
 * @date    2012/03/30
 * 
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 * 
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2012 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm061_fc.h"

#if defined(__TMPM061_FC_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @defgroup FC 
  * @brief FC driver modules
  * @{
  */

/** @defgroup FC_Private_Defines
  * @{
  */
#define SECBIT_SECBIT_PASSWORD   ((uint32_t)0xA74A9D23)
#define SECBIT_SECBIT_SET        ((uint32_t)0x00000001)
#define SECBIT_SECBIT_CLEAR      ((uint32_t)0xFFFFFFFE)

#define SECBIT_SECURITY_MASK     ((uint32_t)0x00000001)
#define SECBIT_DISABLE_FLAG      ((uint32_t)0x00000000)

#define FLCS_BUSY_MASK           ((uint32_t)0x00000001)
#define FLCS_BUSY_FLAG           ((uint32_t)0x00000000)

#define FLCS_BLOCK0_MASK         ((uint32_t)0x00010000)
#define FLCS_BLOCK1_MASK         ((uint32_t)0x00020000)
#define FLCS_BLOCK2_MASK         ((uint32_t)0x00040000)
#define FLCS_BLOCK3_MASK         ((uint32_t)0x00080000)

#define FLCS_BLOCK_FLAG          ((uint32_t)0x00000000)

#define FC_CMD_BC1_ADDR                     ((uint32_t)0x00000550)
#define FC_CMD_BC2_ADDR                     ((uint32_t)0x00000AA0)

#define FC_ERASE_CHIP_OVER_TIME             ((uint32_t)0x000FFFFF)      /* FC_ERASE_CHIP_OVER_TIME > 0.2s */
#define FC_ERASE_BLOCK_OVER_TIME            ((uint32_t)0x0003FFFF)      /* FC_ERASE_BLOCK_OVER_TIME > 0.1s */
#define FC_WRITE_PAGE_OVER_TIME             ((uint32_t)0x00000FFF)      /* FC_WRITE_PAGE_OVER_TIME > 1.25ms */
#define FC_SET_PROTECT_STATE_OVER_TIME      ((uint32_t)0x0007FFFF)

#define FLASH_AREA                  ((uint32_t)(FLASH_START_ADDR & 0xFFF80000U))
#define FC_PBA_BLOCK_0              ((uint32_t *) (FLASH_AREA + 0x00000000U))
#define FC_PBA_BLOCK_1              ((uint32_t *) (FLASH_AREA + 0x00000080U))
#define FC_PBA_BLOCK_2              ((uint32_t *) (FLASH_AREA + 0x00000100U))
#define FC_PBA_BLOCK_3              ((uint32_t *) (FLASH_AREA + 0x00000180U))

#define FC_PBA_BLOCK_GROUP_0        ((uint32_t *) (FLASH_AREA + 0x00000000U))

#define FC_BLOCK_ADDR_MASK          ((uint32_t)0xFFFFC000)

#define FC_BLOCK_SIZE_32KB          ((uint32_t)0x00008000)

#define FC_PAGE_SIZE                ((uint32_t)(FLASH_PAGE_SIZE/4U))

/** @} */
/* End of group FC_Private_Defines */

/** @defgroup FC_Private_FunctionPrototypes
  * @{
  */
uint8_t FC_AddrToBlockNum(uint32_t Addr);

/** @} */
/* End of group FC_Private_FunctionPrototypes */

/** @defgroup FC_Private_Functions
  * @{
  */
/**
  * @brief  Convert address to block number
  * @param  Addr
  * @retval BlockNum
  *
  */
uint8_t FC_AddrToBlockNum(uint32_t Addr)
{
    uint8_t BlockNum = FC_BLOCK_0;
    uint32_t temp = (Addr - FLASH_START_ADDR) / FC_BLOCK_SIZE_32KB;
    switch (temp) {
    case 0U:
        BlockNum = FC_BLOCK_0;
        break;
    case 1U:
        BlockNum = FC_BLOCK_1;
        break;
    case 2U:
        BlockNum = FC_BLOCK_2;
        break;
    case 3U:
        BlockNum = FC_BLOCK_3;
        break;
    default:
        /* Do nothing */
        break;
    }
    return BlockNum;
}

/** @} */
/* End of group FC_Private_Functions */

/** @defgroup FC_Exported_Functions
  * @{
  */

/**
  * @brief  Set the value of SECBIT register.
  * @param  NewState: The value of SECBIT register.
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE.
  * @retval None.
  */
void FC_SetSecurityBit(FunctionalState NewState)
{
    uint32_t tmp = TSB_FC->SECBIT;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set FCSECBIT<SECBIT> to "1" that enable security function  */
        tmp |= SECBIT_SECBIT_SET;
    } else {
        /* Set FCSECBIT<SECBIT> to "0" that disable security function  */
        tmp &= SECBIT_SECBIT_CLEAR;
    }
    TSB_FC->SECBIT = SECBIT_SECBIT_PASSWORD;
    TSB_FC->SECBIT = tmp;
}

/**
  * @brief  Get the value of SECBIT register.
  * @param  None.
  * @retval DISABLE or ENABLE.
  *
  */
FunctionalState FC_GetSecurityBit(void)
{
    uint32_t tmp = 0U;
    FunctionalState retval = ENABLE;

    tmp = TSB_FC->SECBIT & SECBIT_SECURITY_MASK;

    /* Check disable flag */
    if (tmp == SECBIT_DISABLE_FLAG) {
        retval = DISABLE;
    } else {                    /* Check enable flag */
        retval = ENABLE;
    }
    return retval;
}

/**
  * @brief  Get the status of the flash auto operation.
  * @param  None.
  * @retval BUSY or DONE.
  *
  */
WorkState FC_GetBusyState(void)
{
    uint32_t tmp = 0U;
    WorkState retval = DONE;

    tmp = TSB_FC->FLCS & FLCS_BUSY_MASK;

    /* Check busy flag */
    if (tmp == FLCS_BUSY_FLAG) {
        retval = BUSY;
    } else {                    /* Check ready flag */
        retval = DONE;
    }
    return retval;
}

/**
  * @brief  Get the specified block protection state.
  * @param  BlockNum: The flash block number.
  *   This parameter can be one of the following values:
  *   FC_BLOCK_0, FC_BLOCK_1, FC_BLOCK_2, FC_BLOCK_3.
  * @retval DISABLE or ENABLE.
  *
  */
FunctionalState FC_GetBlockProtectState(uint8_t BlockNum)
{
    uint32_t tmp = FLCS_BLOCK_FLAG;
    FunctionalState retval = ENABLE;

    /* Check the parameters */
    assert_param(IS_FC_BLOCK_NUM(BlockNum));

    switch (BlockNum) {
    case FC_BLOCK_0:
        tmp = TSB_FC->FLCS & FLCS_BLOCK0_MASK;
        break;
    case FC_BLOCK_1:
        tmp = TSB_FC->FLCS & FLCS_BLOCK1_MASK;
        break;
    case FC_BLOCK_2:
        tmp = TSB_FC->FLCS & FLCS_BLOCK2_MASK;
        break;
    case FC_BLOCK_3:
        tmp = TSB_FC->FLCS & FLCS_BLOCK3_MASK;
        break;
    default:
        /* Do nothing */
        break;
    }
    if (tmp == FLCS_BLOCK_FLAG) {
        /* Return protection status of each block */
        retval = DISABLE;
    } else {
        retval = ENABLE;
    }
    return retval;
}

/**
  * @brief  Program the protection bit to make the specified block protected.
  * @param  BlockNum: The flash block number.
  *   This parameter can be one of the following values:
  *   FC_BLOCK_0, FC_BLOCK_1, FC_BLOCK_2, FC_BLOCK_3.
  * @retval FC_SUCCESS, FC_ERROR_PROTECTED, FC_ERROR_OVER_TIME.
  *
  */
FC_Result FC_ProgramBlockProtectState(uint8_t BlockNum)
{
    FC_Result retval = FC_SUCCESS;
    volatile uint32_t *addr1 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC1_ADDR);
    volatile uint32_t *addr2 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC2_ADDR);
    volatile uint32_t *PBA = FC_PBA_BLOCK_0;
    uint32_t counter = FC_SET_PROTECT_STATE_OVER_TIME;

    /* Check the parameters */
    assert_param(IS_FC_BLOCK_NUM(BlockNum));

    switch (BlockNum) {
    case FC_BLOCK_0:
        PBA = FC_PBA_BLOCK_0;
        break;
    case FC_BLOCK_1:
        PBA = FC_PBA_BLOCK_1;
        break;
    case FC_BLOCK_2:
        PBA = FC_PBA_BLOCK_2;
        break;
    case FC_BLOCK_3:
        PBA = FC_PBA_BLOCK_3;
        break;
    default:
        /* Do nothing */
        break;
    }

    if (ENABLE == FC_GetBlockProtectState(BlockNum)) {
        retval = FC_ERROR_PROTECTED;
    } else {
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 1 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 2 */
        *addr1 = (uint32_t) 0x0000009A; /* bus cycle 3 */
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 4 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 5 */
        *addr1 = (uint32_t) 0x0000009A; /* bus cycle 6 */
        *PBA = (uint32_t) 0x0000009A;   /* bus cycle 7 */
        __DSB();

        while (BUSY == FC_GetBusyState()) {     /* check if FLASH is busy with overtime counter */
            if (!(counter--)) { /* check overtime */
                retval = FC_ERROR_OVER_TIME;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return retval;
}

/**
  * @brief  Erase the protection bits to make the specified blocks unprotected.
  * @param  BlockGroup: Block group for erasing of the protection bits.
  *   This parameter can be one of the following values:
  *   FC_BLOCK_GROUP_0: block 0 through 3.
  * @retval FC_SUCCESS, FC_ERROR_OVER_TIME.
  *
  */
FC_Result FC_EraseBlockProtectState(uint8_t BlockGroup)
{
    FC_Result retval = FC_SUCCESS;
    volatile uint32_t *addr1 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC1_ADDR);
    volatile uint32_t *addr2 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC2_ADDR);
    volatile uint32_t *PBA = FC_PBA_BLOCK_GROUP_0;
    uint32_t counter = FC_SET_PROTECT_STATE_OVER_TIME;

    /* Check the parameters */
    assert_param(IS_FC_BLOCK_GROUP(BlockGroup));

    *addr1 = (uint32_t) 0x000000AA;     /* bus cycle 1 */
    *addr2 = (uint32_t) 0x00000055;     /* bus cycle 2 */
    *addr1 = (uint32_t) 0x0000006A;     /* bus cycle 3 */
    *addr1 = (uint32_t) 0x000000AA;     /* bus cycle 4 */
    *addr2 = (uint32_t) 0x00000055;     /* bus cycle 5 */
    *addr1 = (uint32_t) 0x0000006A;     /* bus cycle 6 */
    *PBA = (uint32_t) 0x0000006A;       /* bus cycle 7 */
    __DSB();

    while (BUSY == FC_GetBusyState()) { /* check if FLASH is busy with overtime counter */
        if (!(counter--)) {     /* check overtime */
            retval = FC_ERROR_OVER_TIME;
            break;
        } else {
            /* Do nothing */
        }
    }

    return retval;
}

/**
  * @brief  Write data to the specified page.
  * @param  PageAddr: The page start address.
  *         Data: The pointer to data buffer to be written into the page.
  *         The data size should be 128Byte.
  * @retval FC_SUCCESS, FC_ERROR_PROTECTED, FC_ERROR_OVER_TIME.
  *
  */
FC_Result FC_WritePage(uint32_t PageAddr, uint32_t * Data)
{
    FC_Result retval = FC_SUCCESS;
    volatile uint32_t *addr1 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC1_ADDR);
    volatile uint32_t *addr2 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC2_ADDR);
    volatile uint32_t *addr3 = (uint32_t *) PageAddr;
    uint32_t counter = FC_WRITE_PAGE_OVER_TIME;
    uint32_t i = 0U;
    uint32_t *source = Data;
    uint8_t BlockNum = FC_BLOCK_0;

    assert_param(IS_FC_ADDR(PageAddr)); /* Check whether it is in the flash address range */
    assert_param(IS_FC_PAGE_ADDR(PageAddr));    /* Check whether it is a page start address */
    assert_param(IS_POINTER_NOT_NULL(Data));

    BlockNum = FC_AddrToBlockNum(PageAddr);

    if (ENABLE == FC_GetBlockProtectState(BlockNum)) {
        retval = FC_ERROR_PROTECTED;
    } else {
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 1 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 2 */
        *addr1 = (uint32_t) 0x000000A0; /* bus cycle 3 */
        for (i = 0U; i < FC_PAGE_SIZE; i++) {   /* bus cycle 4~35 */
            *addr3 = *source;
            source++;
        }
        __DSB();

        while (BUSY == FC_GetBusyState()) {     /* check if FLASH is busy with overtime counter */
            if (!(counter--)) { /* check overtime */
                retval = FC_ERROR_OVER_TIME;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return retval;
}

/**
  * @brief  Erase the contents of the specified block.
  * @param  BlockAddr: The block start address.
  * @retval FC_SUCCESS, FC_ERROR_PROTECTED, FC_ERROR_OVER_TIME.
  *
  */
FC_Result FC_EraseBlock(uint32_t BlockAddr)
{
    FC_Result retval = FC_SUCCESS;
    volatile uint32_t *addr1 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC1_ADDR);
    volatile uint32_t *addr2 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC2_ADDR);
    volatile uint32_t *BA = (uint32_t *) (BlockAddr & FC_BLOCK_ADDR_MASK);
    uint32_t counter = FC_ERASE_BLOCK_OVER_TIME;
    uint8_t BlockNum = FC_BLOCK_0;

    assert_param(IS_FC_ADDR(BlockAddr));        /* Check whether it is in the flash address range */

    BlockNum = FC_AddrToBlockNum(BlockAddr);

    if (ENABLE == FC_GetBlockProtectState(BlockNum)) {
        retval = FC_ERROR_PROTECTED;
    } else {
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 1 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 2 */
        *addr1 = (uint32_t) 0x00000080; /* bus cycle 3 */
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 4 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 5 */
        *BA = (uint32_t) 0x00000030;    /* bus cycle 6 */
        __DSB();

        while (BUSY == FC_GetBusyState()) {     /* check if FLASH is busy with overtime counter */
            if (!(counter--)) { /* check overtime */
                retval = FC_ERROR_OVER_TIME;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return retval;
}

/**
  * @brief  Erase the contents of the entire chip.
  * @param  None.
  * @retval FC_SUCCESS, FC_ERROR_PROTECTED, FC_ERROR_OVER_TIME.
  *
  */
FC_Result FC_EraseChip(void)
{
    FC_Result retval = FC_SUCCESS;
    volatile uint32_t *addr1 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC1_ADDR);
    volatile uint32_t *addr2 = (uint32_t *) (FLASH_START_ADDR + FC_CMD_BC2_ADDR);
    uint32_t counter = FC_ERASE_CHIP_OVER_TIME;

    FunctionalState result0 = FC_GetBlockProtectState(FC_BLOCK_0);
    FunctionalState result1 = FC_GetBlockProtectState(FC_BLOCK_1);
    FunctionalState result2 = FC_GetBlockProtectState(FC_BLOCK_2);
    FunctionalState result3 = FC_GetBlockProtectState(FC_BLOCK_3);

    if ((ENABLE == result0) && (ENABLE == result1) && (ENABLE == result2) && (ENABLE == result3)) {
        retval = FC_ERROR_PROTECTED;
    } else {
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 1 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 2 */
        *addr1 = (uint32_t) 0x00000080; /* bus cycle 3 */
        *addr1 = (uint32_t) 0x000000AA; /* bus cycle 4 */
        *addr2 = (uint32_t) 0x00000055; /* bus cycle 5 */
        *addr1 = (uint32_t) 0x00000010; /* bus cycle 6 */
        __DSB();

        while (BUSY == FC_GetBusyState()) {     /* check if FLASH is busy with overtime counter */
            if (!(counter--)) { /* check overtime */
                retval = FC_ERROR_OVER_TIME;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return retval;
}

/** @} */
/* End of group FC_Exported_Functions */

/** @} */
/* End of group FC */

/** @} */
/* End of group TX00_Periph_Driver */
#endif                          /* defined(__TMPM061_FC_H)*/
