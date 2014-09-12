/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of uDMAC demo for the 
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.201
 * @date    2014/04/15
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* This demo is to use uDMAC to transfer RAM data from "src" to "dst" */

#include "tmpm36b_udmac.h"
#include "stdbool.h"

/* select DMA mode */
#define  DMA_DEMOMODE_BASIC
/* #define  DMA_DEMOMODE_AUTOMATIC */

/* Reserve 1K RAM area for control data of each DMAC unit. */
/*  each channel use 4 word, 32 channels, primary and alternative */
/*   so, each unit need: 4 x 32 x 2 = 256 word = 1024 bytes */
#if defined (  __ICCARM__  )    /* IAR EWARM */
/* uDMAC_CFG_A/B are defined in file TMPM36B_Flash_For_uDMAC.icf */
uint32_t uDMAC_A_Control_Data[256U] @ ".uDMAC_CFG_A";
uint32_t uDMAC_B_Control_Data[256U] @ ".uDMAC_CFG_B";
#elif defined ( __CC_ARM  )     /* Keil MDK */
#include <absacc.h>
#define uDMAC_CFG_A     (0x20000400U)
#define uDMAC_CFG_B     (uDMAC_CFG_A + 0x400U)
uint32_t uDMAC_A_Control_Data[256U] __at(uDMAC_CFG_A);
uint32_t uDMAC_B_Control_Data[256U] __at(uDMAC_CFG_B);
#endif

#define  TX_NUMBERS   256U
uint16_t src[TX_NUMBERS];
uint16_t dst[TX_NUMBERS];
uint32_t idx = 0U;

bool isSWTransferFinished(TSB_DMA_TypeDef * DMACx, DMAC_Channel Channel);
Result Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len);

volatile Result dmaResult = ERROR;
uint32_t uDMAC_A_Control_Data[256U];
/**
  * @brief  The main function of uDMAC demo
  * @param  None
  * @retval None
  */
int uDMAC_Demo(void)
{
    DMAC_InitTypeDef init = { 0U };
    uint32_t tmpAddr = 0U;
    bool transferState = true;


    DMAC_SetTransferType(DMAC_UNIT_A, DMAC_SW_TRG, DMAC_BURST);
    DMAC_SetChannel(DMAC_UNIT_A, DMAC_SW_TRG, ENABLE);
    DMAC_SetMask(DMAC_UNIT_A, DMAC_SW_TRG, ENABLE);
    DMAC_SetPrimaryAlt(DMAC_UNIT_A, DMAC_SW_TRG, DMAC_PRIMARY);
    DMAC_SetChannelPriority(DMAC_UNIT_A, DMAC_SW_TRG, DMAC_PRIOTIRY_NORMAL);

    DMAC_SetPrimaryBaseAddr(DMAC_UNIT_A, (uint32_t) & uDMAC_A_Control_Data);

    for (idx = 0U; idx < TX_NUMBERS; idx++) {
        src[idx] = idx;
    }


    /* set the end address of source and destination */
    tmpAddr = (uint32_t) & src;
    init.SrcEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(src[0U]));
    tmpAddr = (uint32_t) & dst;
    init.DstEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(dst[0U]));

#if defined(DMA_DEMOMODE_BASIC )
    init.Mode = DMAC_BASIC;
#elif defined(DMA_DEMOMODE_AUTOMATIC)
    init.Mode = DMAC_AUTOMATIC;
#endif

    init.NextUseBurst = DMAC_NEXT_NOT_USE_BURST;
    init.TxNum = TX_NUMBERS;
    init.ArbitrationMoment = DMAC_AFTER_32_TX;

    /* now both src and dst use uint16_t type which is 2bytes long */
    init.SrcWidth = DMAC_HALF_WORD;
    init.SrcInc = DMAC_INC_2B;
    init.DstWidth = DMAC_HALF_WORD;
    init.DstInc = DMAC_INC_2B;

    /* fill to 'control data' area after all members of structure is set */
    DMAC_FillInitData(DMAC_UNIT_A, DMAC_SW_TRG, &init);


    /* enable DMA unit A after all configuration is finished */
    DMAC_Enable(DMAC_UNIT_A);


    do {
        /* because of "init.Mode = DMAC_BASIC" above, here need to trigger it until transfer is finished, */
        /* if DMAC_AUTOMATIC is used, only need to trigger it once */
        DMAC_SetSWReq(DMAC_UNIT_A, DMAC_SW_TRG);

        transferState = isSWTransferFinished(DMAC_UNIT_A, DMAC_SW_TRG);

    } while (transferState == false);

    dmaResult = DMAC_GetBusErrState(DMAC_UNIT_A);

    /* now DMA is finished */
    /* after function Buffercompare() is called, dmaResult == SUCCESS */
    dmaResult = ERROR;
    dmaResult = Buffercompare(src, dst, TX_NUMBERS);

    dmaResult = dmaResult;      /* just to remove compiler's warning */

    while (1U);

}


/**
  * @brief  To compare two half word buffer
  * @param  Src : pointer to point source buffer 
  * @param  Dst : pointer to point destination buffer   
  * @param  Len : how many data will be compared 
  * @retval SUCCESS: two buffer contain same data
            ERROR: two buffer contain different data  
  */
Result Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    Result result = SUCCESS;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            result = ERROR;
            break;
        } else {
            /* Do nothing */
        }
    }

    return result;
}


/**
  * @brief  Check if DMA transfer by software trigger is finished.
  * @param  DMACx: Select DMA Unit.
  *          This parameter can be one of the following values:
  *            DMAC_UNIT_A :  DMAC unit unit A
  *            DMAC_UNIT_B :  DMAC unit unit B
  * @param  Channel: Select channel.
  *          This parameter can be one of the following values:
  *             DMAC_ADC_END,
  *             DMAC_SSP0_RX,
  *             DMAC_SSP0_TX,
  *             DMAC_SSP1_RX,
  *             DMAC_SSP1_TX,
  *             DMAC_SSP2_RX,
  *             DMAC_SSP2_TX,
  *             DMAC_FUART4_RX,
  *             DMAC_FUART4_TX,
  *             DMAC_FUART5_RX,
  *             DMAC_FUART5_TX,
  *             DMAC_SIO0_RX,
  *             DMAC_SIO0_TX,
  *             DMAC_SIO1_RX,
  *             DMAC_SIO1_TX,
  *             DMAC_SIO2_RX,
  *             DMAC_SIO2_TX,
  *             DMAC_SIO3_RX,
  *             DMAC_SIO3_TX,
  *             DMAC_SBI0_RXTX,
  *             DMAC_SBI1_RXTX,
  *             DMAC_SBI2_RXTX,
  *             DMAC_TMRB0_CMP_MATCH,
  *             DMAC_TMRB1_CMP_MATCH,
  *             DMAC_TMRB2_CMP_MATCH,
  *             DMAC_TMRB3_CMP_MATCH,
  *             DMAC_TMRB4_CMP_MATCH,
  *             DMAC_PIN,
  *             DMAC_SW_TRG
  * @retval 
  *        false: transfer is not finished
  *        true: transfer is finished
  */
bool isSWTransferFinished(TSB_DMA_TypeDef * DMACx, DMAC_Channel Channel)
{
    DMAC_PrimaryAlt PriAlt = DMAC_PRIMARY;
    uint32_t Addr = 0U;
    uint32_t tmpCtrl = 0U;
    bool ret = false;

    assert_param(IS_DMAC_UNIT(DMACx));
    assert_param(IS_DMAC_CHANNEL_ALL(Channel));

    PriAlt = DMAC_GetPrimaryAlt(DMACx, Channel);

    if (PriAlt == DMAC_PRIMARY) {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_PRIMARY);
    } else {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_ALTERNATE);
    }

    /* add offset for channel, each channel use 4 words RAM */
    Addr += (16U * (uint32_t) Channel);

    /* get 'control data' */
    tmpCtrl = *((uint32_t *) (Addr + 8U));

    /* low 3bits is 'cycle_ctrl', it becomes 0 when transfer is finished */
    if (tmpCtrl & 0x07U) {
        /* Do nothing */
    } else {
        ret = true;
    }

    return ret;
}


#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
