/**
 *******************************************************************************
 * @file    tmpm36b_sbi.c
 * @brief   This file provides API functions for SBI driver.
 * @version V2.0.2.3
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_sbi.h"

#if defined(__TMPM36B_SBI_H)

/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @defgroup SBI 
  * @brief SBI driver modules
  * @{
  */

/** @defgroup SBI_Private_Defines
  * @{
  */

#define SBICR0_SBIEN_SET                ((uint32_t)0x00000080)
#define SBICR0_SBIEN_CLEAR              ((uint32_t)0xFFFFFF7F)

#define SBICR1_BC_MASK                  ((uint32_t)0x0000001F)
#define SBICR1_ACK_SET                  ((uint32_t)0x00000010)
#define SBICR1_ACK_CLEAR                ((uint32_t)0x000000EF)
#define SBICR1_SCK_MASK                 ((uint32_t)0x000000F8)
#define SBICR1_SWRMON_SET               ((uint32_t)0x00000001)

#define SBICR2_PIN_SET                  ((uint32_t)0x00000010)
#define SBICR2_SBIM_I2C                 ((uint32_t)0x00000008)
#define SBICR2_SWRST_CMD1               ((uint32_t)0x00000002)
#define SBICR2_SWRST_CMD2               ((uint32_t)0x00000001)
#define SBICR2_START_CONDITION          ((uint32_t)0x000000F0)
#define SBICR2_STOP_CONDITION           ((uint32_t)0x000000D0)

#define SBIBR0_I2SBI0_SET               ((uint32_t)0x00000040)
#define SBIBR0_I2SBI0_CLEAR             ((uint32_t)0xFFFFFFBF)

#define SBII2CAR_SA_MASK                ((uint32_t)0x000000FE)
#define SBII2CAR_ALS_SET                ((uint32_t)0x00000001)
#define SBII2CAR_ALS_CLEAR              ((uint32_t)0xFFFFFFFE)
#define SBI_DATA_MASK                   ((uint32_t)0x000000FF)

static uint32_t SBIx_Sck[SBI_CHANNEL_NUMBER];

uint32_t SBI_GetIndex(TSB_SBI_TypeDef * SBIx);

/** @} */
/* End of group SBI_Private_Defines */

/** @defgroup SBI_Exported_Functions
  * @{
  */

/**
  * @brief  Specify the value of index
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval index
  */
uint32_t SBI_GetIndex(TSB_SBI_TypeDef * SBIx)
{
    uint32_t index = 0U;
    assert_param(IS_SBI_PERIPH(SBIx));
    if (SBIx == TSB_SBI0) {
        index = 0U;
    } else if (SBIx == TSB_SBI1) {
        index = 1U;
    } else if (SBIx == TSB_SBI2) {
        index = 2U;
    } else {
        /* Do nothing */
    }
    return index;

}

/**
  * @brief  Enable the specified SBI channel.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_Enable(TSB_SBI_TypeDef * SBIx)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    /* Set SBIxCR0<SBIEN> to enable SBIx */
    SBIx->CR0 |= SBICR0_SBIEN_SET;
}

/**
  * @brief  Disable the specified SBI channel.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_Disable(TSB_SBI_TypeDef * SBIx)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    /* Clear SBIxCR0<SBIEN> to disable SBIx */
    SBIx->CR0 &= SBICR0_SBIEN_CLEAR;
}

/**
  * @brief  Enable or disable the generation of ACK clock. 
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  NewState: New state of ACK clock.
  *   This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void SBI_SetI2CACK(TSB_SBI_TypeDef * SBIx, FunctionalState NewState)
{
    uint32_t tmp = 0U;
    uint32_t index = SBI_GetIndex(SBIx);

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    tmp = SBIx->CR1 & SBICR1_SCK_MASK;
    tmp |= SBIx_Sck[index];
    if (NewState == ENABLE) {
        /* Set SBIxCR1<ACK> to enable generation of ACK clock */
        tmp |= SBICR1_ACK_SET;
    } else {
        /* Clear SBIxCR1<ACK> to disable generation of ACK clock */
        tmp &= SBICR1_ACK_CLEAR;
    }
    SBIx->CR1 = tmp;

}

/**
  * @brief  Initialize the specified SBI channel in I2C mode.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  InitI2CStruct: The structure containing SBI in I2C mode configuration.
  * @retval None
  */
void SBI_InitI2C(TSB_SBI_TypeDef * SBIx, SBI_InitI2CTypeDef * InitI2CStruct)
{
    uint32_t tmp = 0U;
    uint32_t index = SBI_GetIndex(SBIx);

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_POINTER_NOT_NULL(InitI2CStruct));
    assert_param(IS_SBI_I2C_ADDR(InitI2CStruct->I2CSelfAddr));
    assert_param(IS_I2C_BIT_NUM(InitI2CStruct->I2CDataLen));
    assert_param(IS_SBI_I2C_CLK_DIV(InitI2CStruct->I2CClkDiv));
    assert_param(IS_FUNCTIONAL_STATE(InitI2CStruct->I2CACKState));

    /* Set selfaddress for SBIx */
    SBIx->I2CAR = InitI2CStruct->I2CSelfAddr & SBII2CAR_SA_MASK;

    /* Set I2C bit length of transfer data  */
    tmp = SBIx->CR1 & SBICR1_BC_MASK;
    tmp |= (InitI2CStruct->I2CDataLen << 5U);
    /* Set I2C clock division */
    tmp &= SBICR1_SCK_MASK;
    tmp |= InitI2CStruct->I2CClkDiv;
    SBIx_Sck[index] = InitI2CStruct->I2CClkDiv;
    if (InitI2CStruct->I2CACKState) {
        /* Set SBIxCR1<ACK> to enable generation of ACK clock */
        tmp |= SBICR1_ACK_SET;
    } else {
        /* Clear SBIxCR1<ACK> to disable generation of ACK clock */
        tmp &= SBICR1_ACK_CLEAR;
    }
    SBIx->CR1 = tmp;

    /* Intilize SBI to I2C Slave-Rx mode  */
    SBIx->CR2 = SBICR2_PIN_SET | SBICR2_SBIM_I2C;
}

/**
  * @brief  Specify the number of bits per transfer.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  I2CBitNum: Specify the number of bits.
  *   This parameter can be one of the following values:
  *   SBI_I2C_DATA_LEN_8, SBI_I2C_DATA_LEN_1,SBI_I2C_DATA_LEN_2,SBI_I2C_DATA_LEN_3,
  *   SBI_I2C_DATA_LEN_4, SBI_I2C_DATA_LEN_5,SBI_I2C_DATA_LEN_6 and SBI_I2C_DATA_LEN_7.
  * @retval None
  */
void SBI_SetI2CBitNum(TSB_SBI_TypeDef * SBIx, uint32_t I2CBitNum)
{
    uint32_t tmp = 0U;
    uint32_t index = SBI_GetIndex(SBIx);

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_I2C_BIT_NUM(I2CBitNum));

    /* Write number of bits per transfer into SBIxCR1<BC> */
    tmp = SBIx->CR1 & SBICR1_BC_MASK;
    tmp |= ((uint32_t) I2CBitNum << 5U);

    /* Reset the I2C SCL output clock frequency  */
    tmp &= SBICR1_SCK_MASK;
    tmp |= SBIx_Sck[index];

    SBIx->CR1 = tmp;
}

/**
  * @brief  Reset the state of the specified SBI channel.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_SWReset(TSB_SBI_TypeDef * SBIx)
{
    uint32_t index = SBI_GetIndex(SBIx);

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    SBIx->CR2 = SBICR2_SWRST_CMD1;
    SBIx->CR2 = SBICR2_SWRST_CMD2;

    /* Wait for the completion of reset */
    while (!(SBIx->CR1 & SBICR1_SWRMON_SET)) {
        /* Do nothing */
    }
    SBIx_Sck[index] = 0U;
}

/**
  * @brief  Clear SBI interrupt request in I2C mode.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_ClearI2CINTReq(TSB_SBI_TypeDef * SBIx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    /* Set SBIxCR2<PIN> to clear request, and Set SBIM[1:0] to I2C mode */
    tmp = SBIx->SR;
    tmp &= (uint32_t) 0x000000E0;
    tmp |= (SBICR2_PIN_SET | SBICR2_SBIM_I2C);
    SBIx->CR2 = tmp;
}

/**
  * @brief  Set I2c bus to Master mode and Generate start condition in I2C mode.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_GenerateI2CStart(TSB_SBI_TypeDef * SBIx)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    /* Set SBIxCR2<MST>, <TRX>, <BB> and <PIN> to generate start condition */
    SBIx->CR2 = SBICR2_START_CONDITION | SBICR2_SBIM_I2C;
}

/**
  * @brief  Set I2c bus to Master mode and Generate stop condition in I2C mode.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval None
  */
void SBI_GenerateI2CStop(TSB_SBI_TypeDef * SBIx)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    /* Set SBIxCR2<MST>, <TRX>, <PIN> and clear <BB> to generate stop condition */
    SBIx->CR2 = SBICR2_STOP_CONDITION | SBICR2_SBIM_I2C;
}

/**
  * @brief  Get the SBI channel state in I2C mode
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval The state of the SBI channel in I2C bus.
  */
SBI_I2CState SBI_GetI2CState(TSB_SBI_TypeDef * SBIx)
{
    SBI_I2CState state;
    state.All = 0U;

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    state.All = SBIx->SR;
    state.All &= SBI_DATA_MASK;
    return state;
}

/**
  * @brief  Enable or disable the specified SBI channel when system is in IDLE mode. 
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  NewState: New state of the SBI channel in IDLE.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SBI_SetIdleMode(TSB_SBI_TypeDef * SBIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set SBIxBR0<I2SBI0> to enable SBIx in IDLE */
        SBIx->BR0 |= SBIBR0_I2SBI0_SET;
    } else {
        /* Clear SBIxBR0<I2SBI0> to disable SBIx in IDLE */
        SBIx->BR0 &= SBIBR0_I2SBI0_CLEAR;
    }
}

/**
  * @brief  Set data to be sent and MCU starts transmission.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  Data: The data to be sent, max 0xFF.
  * @retval None
  */
void SBI_SetSendData(TSB_SBI_TypeDef * SBIx, uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_SBI_DATA(Data));

    /* Write data into SBIxDBR */
    SBIx->DBR = Data;
}

/**
  * @brief  Get data having been received.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @retval The data having been received
  */
uint32_t SBI_GetReceiveData(TSB_SBI_TypeDef * SBIx)
{
    uint32_t retval = 0U;

    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));

    /* Save the received data */
    retval = SBIx->DBR;
    retval &= SBI_DATA_MASK;

    return retval;
}

/**
  * @brief  Enable or disable I2C free data mode of the SBI channel.
  * @param  SBIx: Select the SBI channel.
  *   This parameter can be one of the following values:
  *   TSB_SBI0,TSB_SBI1,TSB_SBI2
  * @param  NewState: New state of free data mode.
  *   This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void SBI_SetI2CFreeDataMode(TSB_SBI_TypeDef * SBIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SBI_PERIPH(SBIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set SBIxI2CAR<ALS> to use free data mode transfer in I2C mode */
        SBIx->I2CAR |= SBII2CAR_ALS_SET;
    } else {
        /* Clear SBIxI2CAR<ALS> to not use free data mode transfer in I2C mode */
        SBIx->I2CAR &= SBII2CAR_ALS_CLEAR;
    }
}

/** @} */
/* End of group SBI_Exported_Functions */

/** @} */
/* End of group SBI */

/** @} */
/* End of group TX03_Periph_Driver */

#endif                          /*   defined(__TMPM36B_SBI_H) */
