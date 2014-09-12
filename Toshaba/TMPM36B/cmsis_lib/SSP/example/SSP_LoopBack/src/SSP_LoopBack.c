/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of SSP demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 *
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* include file */
#include "tmpm36b_ssp.h"
#include "led.h"
#include "tmpm36b_uart.h"
#include "common_uart.h"
#include <stdio.h>

typedef enum { SAME = 1U, NOT_SAME = !SAME } TestResult;
TestResult result = NOT_SAME;

void DisplayLED(uint16_t dat);
TestResult Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len);

#define MAX_BUFSIZE  64U

/* to check the effect due to too low speed, uncomment the line below */
#define BITRATE_MIN

/*--------------------------------------------------------------------
 This demo will enable the "loop back mode" of SSP module to send data
 and receive it. user can define BITRATE_MIN to see the effect due to
 too slow transmit bit rate.
 the four LEDs will blink to show the data is being received.
---------------------------------------------------------------------*/
/* main function */
int SSP_LoopBack(void)
{
    SSP_InitTypeDef initSSP;
    SSP_FIFOState fifoState;

    uint16_t datTx = 0U;        /* must use 16bit type */
    uint32_t cntTx = 0U;
    uint32_t cntRx = 0U;

    uint16_t receive = 0U;
    char SSP_UART_Data[16];

    uint16_t Rx_Buf[MAX_BUFSIZE] = { 0U };
    uint16_t Tx_Buf[MAX_BUFSIZE] = { 0U };

    /* configure the SSP module */
    initSSP.FrameFormat = SSP_FORMAT_SPI;

    /* default is to run at maximum bit rate */
    initSSP.PreScale = 2U;
    initSSP.ClkRate = 1U;
    /* define BITRATE_MIN to run at minimum bit rate */
    /*   BitRate = fSYS / (PreScale x (1 + ClkRate)) */
#ifdef BITRATE_MIN
    initSSP.PreScale = 254U;
    initSSP.ClkRate = 255U;
#endif
    initSSP.ClkPolarity = SSP_POLARITY_LOW;
    initSSP.ClkPhase = SSP_PHASE_FIRST_EDGE;
    initSSP.DataSize = 16U;
    initSSP.Mode = SSP_MASTER;
    SSP_Init(TSB_SSP0, &initSSP);

    /* enable loop back mode for self test */
    SSP_SetLoopBackMode(TSB_SSP0, ENABLE);

    /* enable and run SSP module */
    SSP_Enable(TSB_SSP0);

    /* initialize LEDs on M36B board before display something */
    LED_Init();
    hardware_init(UART_RETARGET);

    while (1) {

        datTx++;
        /* send data if Tx FIFO is available */
        fifoState = SSP_GetFIFOState(TSB_SSP0, SSP_TX);
        if ((fifoState == SSP_FIFO_EMPTY) || (fifoState == SSP_FIFO_NORMAL)) {
            SSP_SetTxData(TSB_SSP0, datTx);
            if (cntTx < MAX_BUFSIZE) {
                Tx_Buf[cntTx] = datTx;
                cntTx++;
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }

        /* check if there is data arrived */
        fifoState = SSP_GetFIFOState(TSB_SSP0, SSP_RX);
        if ((fifoState == SSP_FIFO_FULL) || (fifoState == SSP_FIFO_NORMAL)) {
            receive = SSP_GetRxData(TSB_SSP0);
            if (cntRx < MAX_BUFSIZE) {
                Rx_Buf[cntRx] = receive;
                cntRx++;
            } else {
                /* Place a break point here to check if receive data is right.                */
                /* Success Criteria:                                                          */
                /*               Every data transmited from Tx_Buf is received in Rx_Buf.     */
                /* When the line "#define BITRATE_MIN" is commented, the SSP is run in maxium */
                /*  bit rate, so we can find there is enough time to transmit date from 1 to  */
                /*  MAX_BUFSIZE one by one. but if we uncomment that line, SSP is run in      */
                /*  minimum bit rate, we will find that receive data can't catch "datTx++",   */
                /*  in this so slow bit rate, when the Tx FIFO is available, the cntTx has    */
                /*  been increased so much.                                                   */
                __NOP();
                result = Buffercompare(Tx_Buf, Rx_Buf, MAX_BUFSIZE);
                if (result == NOT_SAME) {
                    LED_On(LED0);
                    LED_On(LED1);
                } else {
                    LED_On(LED2);
                    LED_On(LED3);
                }
            }

        } else {
            /* Do nothing */
        }

        sprintf((char *) SSP_UART_Data, "%d", receive);

        common_uart_disp("SSP RX DATA:");
        common_uart_disp("\n");
        common_uart_disp(SSP_UART_Data);
        common_uart_disp("\n");
    }
}

/**
  * @brief  To compare two half word buffer
  * @param  Src : pointer to point source buffer
  * @param  Dst : pointer to point destination buffer
  * @param  Len : how many data will be compared
  * @retval SAME: two buffer contain same data
            NOT_SAME: two buffer contain different data
  */
TestResult Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    TestResult result = NOT_SAME;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            break;
        } else {
            result = SAME;
        }
    }

    return result;
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
