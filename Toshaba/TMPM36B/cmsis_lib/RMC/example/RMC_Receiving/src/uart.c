/** 
 *******************************************************************************
 * @file    uart.c
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
#include "uart.h"

/* Private define ------------------------------------------------------------*/
char gSIOTxBuffer[BUFFER_SIZE] = { 0 };

uint8_t gSIORdIndex = 0U;
uint8_t gSIOWrIndex = 0U;
uint8_t fSIO_INT = 0U;

/**
  * @brief  SIO Configuration.
  * @param  SCx
  * @retval None
  */
void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == UART0) {
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_2, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_2, DISABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_2);
    } else {
        /*  Do Nothing */
    }
}

/**
  * @brief  SIO Configuration Initialize the uart port (SIO0).
  * @param  None
  * @retval None
  */
void SIO_ChInit(void)
{
    UART_InitTypeDef myUART;

    /* configure SIO0 for reception */
    UART_Enable(UART0);
    myUART.BaudRate = 115200U;  /* baud rate = 115200 */
    myUART.DataBits = UART_DATA_BITS_8; /* no handshake, 8-bit data, clock by baud rate generator */
    myUART.StopBits = UART_STOP_BITS_1; /* 1-bit stop, LSB,  W-buff enable */
    myUART.Parity = UART_NO_PARITY;
    myUART.Mode = UART_ENABLE_TX;
    myUART.FlowCtrl = UART_NONE_FLOW_CTRL;
    UART_Init(UART0, &myUART);
}

/**
  * @brief  Send character by SIO0
  * @param  Character to be sent
  * @retval Character to be sent
  */
uint8_t send_char(uint8_t ch)
{
    while (gSIORdIndex != gSIOWrIndex) {        /* wait for finishing sending */
        /* Do nothing */
    }
    gSIOTxBuffer[gSIOWrIndex++] = ch;   /* fill TxBuffer */
    if (fSIO_INT == CLEAR) {    /* if SIO INT disable, enable it */
        fSIO_INT = SET;         /* set SIO INT flag */
        UART_SetTxData(UART0, gSIOTxBuffer[gSIORdIndex++]);
        NVIC_EnableIRQ(INTTX0_IRQn);
    }

    return ch;
}
