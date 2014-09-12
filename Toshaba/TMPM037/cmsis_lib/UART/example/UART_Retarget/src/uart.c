/** 
 *******************************************************************************
 * @file    uart.c
 * @brief   The application functions of UART_Retarget demo for the TOSHIBA
 *          'TMPM037' Device Series 
 * @version V0.100
 * @date    2014/05/21
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"

/* Private define ------------------------------------------------------------*/
volatile char gSIOTxBuffer[BUFFER_SIZE] = { 0 };

uint8_t gSIORdIndex = 0U;
volatile uint8_t gSIOWrIndex = 0U;
volatile uint8_t fSIO_INT = 0U;
volatile uint8_t fSIOTxOK = NO;

/**
  * @brief  SIO Configuration.
  * @param  SCx
  * @retval None
  */
void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == UART_RETARGET) {
        GPIO_SetOutputEnableReg(GPIO_PD, GPIO_BIT_3, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PD, GPIO_BIT_3, DISABLE);
        GPIO_EnableFuncReg(GPIO_PD, GPIO_FUNC_REG_1, GPIO_BIT_3);
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
    UART_Enable(UART_RETARGET);
    myUART.BaudRate = 115200U;  /* baud rate = 115200 */
    myUART.DataBits = UART_DATA_BITS_8; /* no handshake, 8-bit data, clock by baud rate generator */
    myUART.StopBits = UART_STOP_BITS_1; /* 1-bit stop, LSB,  W-buff enable */
    myUART.Parity = UART_NO_PARITY;
    myUART.Mode = UART_ENABLE_TX;
    myUART.FlowCtrl = UART_NONE_FLOW_CTRL;
    UART_Init(UART_RETARGET, &myUART);
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
        UART_SetTxData(UART_RETARGET, gSIOTxBuffer[gSIORdIndex++]);
        NVIC_EnableIRQ(RETARGET_INT);
    }

    return ch;
}

/*********************************** END OF FILE ******************************/
