/** 
 *******************************************************************************
 * @file    tmpm36b_int.c
 * @brief   all interrupt request functions definition of RMC_Receiving 
 *          for the TOSHIBA 'TMPM36B' Device Series 
 * @version V0.201
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_int.h"

/* Private variables ---------------------------------------------------------*/
uint16_t gRMCTimeOut = 0U;
uint8_t fTMRB0_INT = 0U;
#ifdef  RMC_5
uint8_t gRMC_5_Cnt = 0U;
#endif
/* external variables --------------------------------------------------------*/
extern IO_SFR32_u uRMCBuf;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  INTRMCRX Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTRMCRX_IRQHandler(void)
{
    RMC_INTFactor myRMC_INTFactor;
    RMC_RxDataTypeDef myRMC_RxDataDef;

#ifdef RMC_1
    RMC_LeaderDetection myRMC_LeaderDetection;
#endif
#ifdef RMC_4
    RMC_LeaderDetection myRMC_LeaderDetection;
#endif
#ifdef RMC_6
    RMC_LeaderDetection myRMC_LeaderDetection;
#endif
    myRMC_INTFactor = RMC_GetINTFactor(TSB_RMC0);
#ifdef RMC_1
    /********************* FOR RMC_1 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.MaxDataBitCycle) {  /*Max data bit cycle detection interrupt factor */

        myRMC_LeaderDetection = RMC_GetLeader(TSB_RMC0);

        if (myRMC_LeaderDetection == RMC_LEADER_DETECTED) {     /*Leader has been detected */

            myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);
            if (myRMC_RxDataDef.RxDataBits == 0x20U) {  /*32 bits data received */

                uRMCBuf.reg = myRMC_RxDataDef.RxBuf1;   /* save the RMC data for print in main() */

                gRMCTimeOut = 0U;       /* reset time-out count */
                if (fRMCPress == RELEASE) {
                    fRMCPress = PRESS;
                } else {
                    /* Do nothing */
                }
            } else {
                if (fRMCPress) {        /* repeat */
                    gRMCTimeOut = 0U;   /* reset time-out count */
                } else {
                    /* Do nothing */
                }
            }
        }
    }
#endif

#ifdef RMC_2
    /********************* FOR RMC_2 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.LowWidthDetection) {        /*Low width detection interrupt factor */

        myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);

        if (myRMC_RxDataDef.RxDataBits == 0x0EU) {      /*14 bits data received */

            uRMCBuf.reg = myRMC_RxDataDef.RxBuf1;       /* save the RMC data for print in main() */

            if (fRMCPress == RELEASE) {
                fRMCPress = PRESS;
            } else {
                /* Do nothing */
            }
        }
    }
#endif

#ifdef RMC_3
    /********************* FOR RMC_3 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.MaxDataBitCycle) {  /*Max data bit cycle detection interrupt factor */

        myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);

        if (myRMC_RxDataDef.RxDataBits == 0x30U) {      /*48 bits data received */

            uRMCBuf.reg = myRMC_RxDataDef.RxBuf1;       /* save the RMC data for print in main() */
            uRMCBuf_KA.reg = myRMC_RxDataDef.RxBuf2;
            gRMCTimeOut = 0U;   /* reset time-out count */
            if (fRMCPress == RELEASE) {
                fRMCPress = PRESS;
            } else {
                /* Do nothing */
            }
        }
    }
#endif

#ifdef RMC_4
    /********************* FOR RMC_4 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.MaxDataBitCycle) {  /*Max data bit cycle detection interrupt factor */

        myRMC_LeaderDetection = RMC_GetLeader(TSB_RMC0);

        if (myRMC_LeaderDetection == RMC_LEADER_DETECTED) {     /*Leader has been detected */

            myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);

            if (myRMC_RxDataDef.RxDataBits == 0x0CU) {  /*12 bits data received */

                gRMC_4Address = 5U;

            } else if (myRMC_RxDataDef.RxDataBits == 0x0FU) {   /*15 bits data received */

                gRMC_4Address = 8U;

            } else if (myRMC_RxDataDef.RxDataBits == 0x14U) {   /*20 bits data received */
                gRMC_4Address = 13U;
            } else {
                gRMC_4Address = 0U;
            }
        }

        if (gRMC_4Address) {
            uRMCBuf.reg = myRMC_RxDataDef.RxBuf1;       /* save the RMC data for print in main() */
            gRMCTimeOut = 0U;   /* reset time-out count */
            if (fRMCPress == RELEASE) {
                fRMCPress = PRESS;
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
    }
#endif

#ifdef RMC_5
    /********************* FOR RMC_5 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.MaxDataBitCycle) {  /*Max data bit cycle detection interrupt factor */

        myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);

        if (myRMC_RxDataDef.RxDataBits == 0x0FU) {      /*15 bits data received */

            static IO_SFR32_u RMC_5_data[2];

            if (gRMC_5_Cnt < 2U) {
                RMC_5_data[gRMC_5_Cnt++].reg = myRMC_RxDataDef.RxBuf1;  /* save the RMC data for print in main() */
                uRMCBuf.reg = RMC_5_data[0].reg;
            } else {
                if ((RMC_5_data[0].byte[0] + RMC_5_data[1].byte[0]) != 0xFFU) {
                    gRMC_5_Cnt = 0U;
                } else {
                    uRMCBuf.reg = RMC_5_data[0].reg;
                }
            }
            gRMCTimeOut = 0U;   /* reset time-out count */
            if (fRMCPress == RELEASE) {
                fRMCPress = PRESS;
            } else {
                /* Do nothing */
            }
        }
    }
#endif

#ifdef RMC_6
    /********************* FOR RMC_6 FORMAT  ***********************/

    if (myRMC_INTFactor.Bit.MaxDataBitCycle) {  /*Max data bit cycle detection interrupt factor */

        myRMC_LeaderDetection = RMC_GetLeader(TSB_RMC0);

        if (myRMC_LeaderDetection == RMC_LEADER_DETECTED) {     /*15 bits data received */

            myRMC_RxDataDef = RMC_GetRxData(TSB_RMC0);

            if (myRMC_RxDataDef.RxDataBits == 0x20U) {  /*32 bits data received */
                uRMCBuf.reg = myRMC_RxDataDef.RxBuf1;   /* save the RMC data for print in main() */

                gRMCTimeOut = 0U;       /* reset time-out count */
                if (fRMCPress == RELEASE) {
                    fRMCPress = PRESS;
                } else {
                    /* Do nothing */
                }
            } else {
                if (fRMCPress) {        /* repeat */
                    gRMCTimeOut = 0U;   /* reset time-out count */
                } else {
                    /* Do nothing */
                }
            }
        }
    }
#endif

    /* Detect RMC input TIMEOUT */
    if ((fRMCPress) == PRESS && !fTMRB0_INT) {  /* receive correct RMC data and TMBR is not running */
        fTMRB0_INT = 1U;        /* set TMRB0 INT flag */

        TMRB_SetRunState(TSB_TB0, TMRB_STOP);
        NVIC_EnableIRQ(INTTB0_IRQn);
        TMRB_SetRunState(TSB_TB0, TMRB_RUN);

    } else {
        /* Do nothing */
    }

    CG_ClearINTReq(CG_INT_SRC_RMCRX);   /* clear RMC0 INT */
}

/**
  * @brief  INTTB0 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTTB0_IRQHandler(void)
{
    if (++gRMCTimeOut > 3000U) { /* no RMC input for more than 300ms */
        gRMCTimeOut = 0U;
        fTMRB0_INT = 0U;        /* clear TMRB0 INT flag */
#ifdef RMC_5
        gRMC_5_Cnt = 0U;
#endif

        fRMCPress = RELEASE;
        fRMCDone = RMC_DONE;    /* RMC reception finish */
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  INTTX0 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTTX0_IRQHandler(void)
{
    if (gSIORdIndex < gSIOWrIndex) {    /* buffer is not empty */
        UART_SetTxData(UART0, (uint32_t) gSIOTxBuffer[gSIORdIndex++]);  /* send data */
        fSIO_INT = SET;         /* SIO INT is enable */
    } else {
        /* disable SIO0 INT */
        fSIO_INT = CLEAR;
        NVIC_DisableIRQ(INTTX0_IRQn);
    }
    if (gSIORdIndex >= gSIOWrIndex) {   /* reset buffer index */
        gSIOWrIndex = CLEAR;
        gSIORdIndex = CLEAR;
    } else {
        /* Do nothing */
    }
}
