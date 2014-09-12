/** 
 *******************************************************************************
 * @file    common_uart.c
 * @brief   UART driver for the TOSHIBA 'TMPM36B' Device Series
 * @version V2.0.2.2
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "common_uart.h"
#include "tmpm36b_gpio.h"
#include "stdio.h"
#define RETARGET_INT    INTTX0_IRQn
/* Private define ------------------------------------------------------------*/
char gSIOTxBuffer[BUFFER_SIZE] = { 0 };

uint8_t gSIORdIndex = 0U;
volatile uint8_t gSIOWrIndex = 0U;
volatile uint8_t fSIO_INT = 0U;
volatile uint8_t fSIOTxOK = NO;

/**
  * @brief  INTTX0 Interrupt Service Routine.
  * @param  None
  * @retval None
  */
void INTTX0_IRQHandler(void)
{
    if (gSIORdIndex < gSIOWrIndex) {    /* buffer is not empty */
        UART_SetTxData(UART_RETARGET, gSIOTxBuffer[gSIORdIndex++]);     /* send data */
        fSIO_INT = SET;         /* SIO0 INT is enable */
    } else {
        /* disable SIO0 INT */
        fSIO_INT = CLEAR;
        NVIC_DisableIRQ(RETARGET_INT);
        fSIOTxOK = YES;
    }
    if (gSIORdIndex >= gSIOWrIndex) {   /* reset buffer index */
        gSIOWrIndex = CLEAR;
        gSIORdIndex = CLEAR;
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  SIO0 Configuration.
  * @param  SCx
  * @retval None
  */
void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == UART_RETARGET) {
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_2, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_2, DISABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_2);
    } else {
        /*  Do Nothing */
    }
}

/**
  * @brief  SIO0 Configuration Initialize the uart port (SIO0).
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
  * @retval None
  */
void send_char(TSB_SC_TypeDef * USART, char ch)
{
    while (gSIORdIndex != gSIOWrIndex) {        /* wait for finishing sending */
        /* Do nothing */
    }
    gSIOTxBuffer[gSIOWrIndex++] = ch;   /* fill TxBuffer */
    if (fSIO_INT == CLEAR) {    /* if SIO0 INT disable, enable it */
        fSIO_INT = SET;         /* set SIO0 INT flag */
        UART_SetTxData(USART, gSIOTxBuffer[gSIORdIndex++]);
        NVIC_EnableIRQ(RETARGET_INT);
    }

}

/**
  * @brief  Send character string by SIO0
  * @param  Character string to be sent
  * @retval None
  */
void send_str(TSB_SC_TypeDef * USART, char *ch)
{
    char *pdat = ch;
    while ('\0' != *pdat) {
        send_char(USART, *pdat++);
    }
}

/**
  * @brief  SIO0 Init.
  * @param  SCx
  * @retval None
  */
void hardware_init(TSB_SC_TypeDef * SCx)
{
    /* Initialize system */
    SIO_Configuration(SCx);
    SIO_ChInit();
    /* enable retarget Channel TX interrupt */
    NVIC_EnableIRQ(RETARGET_INT);

}

/**
  * @brief  Send character string
  * @param  Character string to be sent
  * @retval None
  */
void common_uart_disp(char *pstr)
{
    send_str(UART0, pstr);
    while (fSIOTxOK == NO) {    /* wait for UART_RETARGET finish send */
        /* Do nothing */
    }
    fSIOTxOK = NO;

}
