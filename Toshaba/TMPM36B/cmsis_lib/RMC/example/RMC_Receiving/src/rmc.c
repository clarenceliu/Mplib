/** 
 *******************************************************************************
 * @file    rmc.c
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

/* Includes ------------------------------------------------------------------*/
#include "rmc.h"

/* Private variables ---------------------------------------------------------*/
uint32_t gRMC_Command = 0U;
uint16_t gRMC_Address = 0U;

RMCSTAT fRMCDone = RMC_NON;
RMCPRS fRMCPress = RELEASE;

IO_SFR32_u uRMCBuf;

#ifdef RMC_3
IO_SFR32_u uRMCBuf_KA;
#endif

#ifdef RMC_4
uint8_t gRMC_4Address = 0U;
#endif


/**
  * @brief  Inital RMC channel I/O port.
  * @param  RMC channel
  * @retval None
  */

void RMC_Configuration(TSB_RMC_TypeDef * RMCx)
{
    if (RMCx == TSB_RMC0) {
        GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_1, GPIO_BIT_4);
        GPIO_SetInputEnableReg(GPIO_PK, GPIO_BIT_4, ENABLE);
    } else {
        /*Do nothing */
    }
}


/**
  * @brief  Configure RMC channel.
  * @param  RMC channel
  * @retval None
  */

void RMC_ChInit(TSB_RMC_TypeDef * RMCx)
{
    RMC_InitTypeDef myRMC;

#ifdef RMC_1
    /*RMC register set for TOSHIBA format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;
    myRMC.LeaderPara.LeaderDetectionState = ENABLE;
    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_CYCLE_METHOD;
    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;
    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;
    myRMC.InputSignalReversedState = DISABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;
#endif

#ifdef RMC_2
    /*RMC register set for RC5 format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;
    myRMC.LeaderPara.LeaderDetectionState = DISABLE;
    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_PHASE_METHOD;
    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;
    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;
    myRMC.InputSignalReversedState = ENABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;
#endif

#ifdef RMC_3
    /*RMC register set for PANASONIC format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;
    myRMC.LeaderPara.LeaderDetectionState = ENABLE;
    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_CYCLE_METHOD;
    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;
    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;
    myRMC.InputSignalReversedState = DISABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;
#endif

#ifdef RMC_4
    /*RMC register set for SONY format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;

    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.LeaderPara.LeaderDetectionState = ENABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_CYCLE_METHOD;
    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;

    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;

    myRMC.InputSignalReversedState = ENABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;

#endif

#ifdef RMC_5
    /*RMC register set for SHARP format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;

    myRMC.LeaderPara.LeaderDetectionState = DISABLE;
    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_CYCLE_METHOD;

    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;

    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;

    myRMC.InputSignalReversedState = DISABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;
#endif

#ifdef RMC_6
    /*RMC register set for NEC format */
    myRMC.LeaderPara.MaxCycle = RMC_MAX_CYCLE;
    myRMC.LeaderPara.MinCycle = RMC_MIN_CYCLE;
    myRMC.LeaderPara.MaxLowWidth = RMC_MAX_LOW_WIDTH;
    myRMC.LeaderPara.MinLowWidth = RMC_MIN_LOW_WIDTH;

    myRMC.LeaderPara.LeaderDetectionState = ENABLE;
    myRMC.LeaderPara.LeaderINTState = DISABLE;
    myRMC.FallingEdgeINTState = DISABLE;
    myRMC.SignalRxMethod = RMC_RX_IN_CYCLE_METHOD;

    myRMC.LowWidth = RMC_TRG_LOW_WIDTH;
    myRMC.MaxDataBitCycle = RMC_TRG_MAX_DATA_BIT_CYCLE;

    myRMC.LargerThreshold = RMC_LARGER_THRESHOLD;
    myRMC.SmallerThreshold = RMC_SMALLER_THRESHOLD;

    myRMC.InputSignalReversedState = DISABLE;
    myRMC.NoiseCancellationTime = RMC_NOISE_CANCELLATION_TIME;
#endif

    RMC_Enable(RMCx);
    RMC_Init(RMCx, &myRMC);
    /* RMC Reception enable */
    RMC_SetRxCtrl(RMCx, ENABLE);
}

/**
  * @brief  Get address & command from data received by RMC.
  * @param  RMC channel
  * @retval None
  */

void RMCRcv(void)
{
    fRMCDone = RMC_NON;
#ifdef RMC_1
    gRMC_Address = uRMCBuf.byte[3];
    gRMC_Command = uRMCBuf.byte[1];
#endif

#ifdef RMC_2
    gRMC_Address = ((uRMCBuf.byte[1] & 0x07U) << 2U) + ((uRMCBuf.byte[0] & 0xC0U) >> 6U);
    gRMC_Command = uRMCBuf.byte[0] & 0x3FU;
#endif

#ifdef RMC_3
    gRMC_Address = (uint16_t) uRMCBuf_KA.reg;
    gRMC_Command = uRMCBuf.reg & 0x00FFFFFFU;
#endif

#ifdef RMC_4
    switch (gRMC_4Address) {
    case 5:                    /* 5-bit address */
        gRMC_Address = uRMCBuf.byte[0] & 0x1FU;
        gRMC_Command = ((uRMCBuf.byte[1] & 0x0FU) << 3U) + ((uRMCBuf.byte[0] & 0xE0U) >> 5U);
        break;
    case 8:                    /* 8-bit address */
        gRMC_Address = uRMCBuf.byte[0];
        gRMC_Command = uRMCBuf.byte[1] & 0x7FU;
        break;
    case 13:                   /* 13-bit address */
        gRMC_Address = ((uRMCBuf.byte[1] & 0x1FU) << 8U) + uRMCBuf.byte[0];
        gRMC_Command = ((uRMCBuf.byte[2] & 0x0FU) << 3U) + ((uRMCBuf.byte[1] & 0xE0U) >> 5U);
        break;
    default:
        printf("RMC RECEIVE ERROR in RMC_4 FORMAT\r\n");
        break;
    }
#endif

#ifdef RMC_5
    gRMC_Address = (uRMCBuf.byte[1] & 0x7CU) >> 2U;
    gRMC_Command = ((uRMCBuf.byte[1] & 0x03U) << 6U) + ((uRMCBuf.byte[0] & 0xFCU) >> 2U);

    if ((uRMCBuf.byte[0] & 0x02U) == 0x00U) {   /* check whether it is the inverted message */
        gRMC_Command ^= 0xffU;
    } else {
        /* Do nothing */
    }
#endif

#ifdef RMC_6
    gRMC_Address = (uRMCBuf.byte[1] & 0x7CU) >> 2U;
    gRMC_Command = ((uRMCBuf.byte[1] & 0x03U) << 6U) + ((uRMCBuf.byte[0] & 0xFCU) >> 2U);

    if ((uRMCBuf.byte[0] & 0x02U) == 0x00U) {   /* check whether it is the inverted message */
        gRMC_Command ^= 0xffU;
    } else {
        /* Do nothing */
    }
#endif
}
