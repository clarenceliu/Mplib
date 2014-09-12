/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of FUART_LoopBack demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.201
 * @date    2014/05/20
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 *
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* include file */
#include "FUART_LoopBack.h"

/* #define RUN_NONE_FLOW_CONTROL */

#define MAX_BUFSIZE  64U

int FUART_LoopBack(void)
{
    TestResult result = DIFF;
    FUART_StorageStatus FIFOStatus;
    uint32_t cntTx = 0U;
    uint32_t cntRx = 0U;
    uint8_t SW0_last = 0U;
    uint8_t SW0_this = 0U;
    char rxnum[2] = { 0 };

    uint32_t receive = 0U;      /* received data */
    uint32_t rxlast = 0U;       /* received data number after last reception */
    uint32_t rxthis = 0U;       /* recevied data number after this reception */
    uint32_t Rx_Buf[MAX_BUFSIZE] = { 0U };
    uint32_t Tx_Buf[MAX_BUFSIZE] = { 0U };

    uint32_t i = 0U;
    for (; i < MAX_BUFSIZE; i++) {
        Tx_Buf[i] = i;
    }

    LED_Init();
    SW_Init();
    hardware_init(UART_RETARGET);
    FUART_GPIOConfig();         /* Congigure GPIO for FUART4 */
    FUART_ChInit();             /* Initialize FUART4 */

    FUART_Enable(FUART4);
    FUART_EnableFIFO(FUART4);
    FUART_SetINTFIFOLevel(FUART4, FUART_RX_FIFO_LEVEL_16, FUART_TX_FIFO_LEVEL_4);

    SW0_this = SW_Get(SW0);
    while (1) {
        if (cntTx < MAX_BUFSIZE) {
            FIFOStatus = FUART_GetStorageStatus(FUART4, FUART_TX);
            if ((FIFOStatus == FUART_STORAGE_EMPTY)
                || (FIFOStatus == FUART_STORAGE_NORMAL)) {
                FUART_SetTxData(FUART4, Tx_Buf[cntTx]);
                LED_TXDataDisplay(Tx_Buf[cntTx]);
                cntTx++;
                if (64U == cntTx) {
                    LED_On(LED_ALL);    /* sending data is finished */
                }
            }
        }

        SW0_last = SW0_this;
        SW0_this = SW_Get(SW0);
        if (SW0_last != SW0_this) {     /* turn the switch SW0 */
            while (FUART_STORAGE_EMPTY != FUART_GetStorageStatus(FUART4, FUART_RX)) {
                receive = FUART_GetRxData(FUART4);
                Rx_Buf[cntRx] = receive;
                cntRx++;
            }

            rxlast = rxthis;
            rxthis = cntRx;

            if (rxlast != rxthis) {     /* there are some data that has been received  */
                common_uart_disp("LAST RX DATA:\n");
                rxnum[0] = ('0' + receive / 10U);
                rxnum[1] = ('0' + receive % 10U);
                common_uart_disp(rxnum);
            } else {            /* receiving data is finished */
                common_uart_disp("RX FINISH\n");
                result = Buffercompare(Tx_Buf, Rx_Buf, MAX_BUFSIZE);
                if (result == SAME) {
                    /* received data are same with trnsmitted data */
                    /* RTS and CTS flow control has worked normally */
                    common_uart_disp("RX TX SAME\n");
                    while (1) {
                    }
                } else {
                    /* received data are different with trnsmitted data */
                    /* RTS and CTS flow control doesn't work */
                    common_uart_disp("RX TX DIFF\n");
                    while (1) {
                    }
                }
            }
        }
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif

/**
  * @brief  Compare Received data and Tranmitted data
  * @param  Src : pointer to point source buffer
  * @param  Dst : pointer to point destination buffer
  * @param  Len : The length of data buffer
  * @retval SAME: received data are same with transmitted data
            DIFF: received data are different with transmitted data
  */
TestResult Buffercompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    TestResult result = SAME;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            result = DIFF;
            break;
        } else {
        }
    }

    return result;
}

/**
  * @brief  use leds todisplay the data set to tranmit FIFO
  * @param  the data set to tranmit FIFO
  * @retval None
  */
void LED_TXDataDisplay(uint32_t dat)
{
    uint8_t tmp = 0U;
    uint32_t portstate = 0U;    /* port B state */

    tmp = (uint8_t) dat;
    tmp = 1 << (dat % 4);
    portstate = GPIO_ReadData(GPIO_PB);
    portstate &= 0xF0U;
    portstate |= tmp;
    GPIO_WriteData(GPIO_PB, portstate);
}

/**
  * @brief  Configure GPIO for Full UART pins, TXD4, RXD4, CTS4, RTS4
  * @param  None
  * @retval None
  */
void FUART_GPIOConfig(void)
{
    /* Configure port PF1 to be TXD4 */
    GPIO_SetOutput(GPIO_PF, GPIO_BIT_1);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_1);

    /* Configure port PF2 to be RXD4 */
    GPIO_SetInput(GPIO_PF, GPIO_BIT_2);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_2);

    /* Configure port PF0 to be CTS4 */
    GPIO_SetInput(GPIO_PF, GPIO_BIT_0);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_0);

    /* Configure port PF3 to be RTS4 */
    GPIO_SetOutput(GPIO_PF, GPIO_BIT_3);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_3);
}

/**
  * @brief  Initialize Full UART channel 4
  * @param  None
  * @retval None
  */
void FUART_ChInit(void)
{
    FUART_InitTypeDef myFUART;

    myFUART.BaudRate = 300U;
    myFUART.DataBits = FUART_DATA_BITS_8;
    myFUART.StopBits = FUART_STOP_BITS_1;
    myFUART.Parity = FUART_1_PARITY;
    myFUART.Mode = FUART_ENABLE_TX | FUART_ENABLE_RX;

#ifdef RUN_NONE_FLOW_CONTROL
    myFUART.FlowCtrl = FUART_NONE_FLOW_CTRL;
#else
    myFUART.FlowCtrl = FUART_CTS_FLOW_CTRL | FUART_RTS_FLOW_CTRL;
#endif

    FUART_Init(FUART4, &myFUART);
}
