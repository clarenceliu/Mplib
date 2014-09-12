/**
 *******************************************************************************
 * @file    main.c
 * @brief   The main functions of I2C slave demo for the
 *          TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "I2C_SLAVE.h"

I2C_InitTypeDef myI2C;
volatile uint32_t gI2CRCnt;
uint32_t uSlaveAddr;

char gI2CRxData[8] = { 0 };

volatile uint32_t gI2CMode;

/**
  * @brief  The main routine of I2C
  * @param  None
  * @retval None
  */
int I2C_SLAVE(void)
{
    volatile uint32_t gI2CRxDataLen = 7;
    uint32_t gICnt;

    SW_Init();
    hardware_init(UART_RETARGET);

    /* Initialize IO for I2C */
    I2C_IO_Configuration();
    /* Initialize I2C channel */
    myI2C.I2CSelfAddr = SLAVE_ADDR;
    myI2C.I2CDataLen = I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = I2C_SCK_CLK_DIV_32;
    myI2C.PrescalerClkDiv = I2C_PRESCALER_DIV_12;

    I2C_SWReset();
    I2C_Init(&myI2C);
    NVIC_EnableIRQ(INTI2C0_IRQn);
    I2C_SetINTReq(ENABLE);

    common_uart_disp("K1: I2C SLAVE RECV");
    common_uart_disp("\r\n\r\n");
    /* Initialize variables for I2C */
    gI2CRCnt = 0U;
    gI2CMode = MODE_I2C_INITIAL;

    while (1) {
        switch (gI2CMode) {
        case MODE_I2C_INITIAL:
            for (gICnt = 0U; gICnt < 8U; gICnt++) {
                gI2CRxData[gICnt] = 0U;
            }
            gI2CMode = MODE_I2C_RCV;
            break;

        case MODE_I2C_RCV:
            if (SW_Get(SW1)) {
                if (gI2CRCnt > 7) {
                    for (gICnt = 1U; gICnt <= gI2CRxDataLen; gICnt++) {
                        gI2CRxData[gICnt - 1] = gI2CRxData[gICnt];
                    }
                    gI2CRxData[gI2CRxDataLen] = '\0';
                    common_uart_disp(gI2CRxData);
                    common_uart_disp("\r\n");
                    common_uart_disp("MASTER I2C to SLAVE I2C OK");
                    common_uart_disp("\r\n");
                    gI2CMode = MODE_I2C_INITIAL;
                    gI2CRCnt = 0U;

                } else {
                    /* Do nothing */
                }
            } else {
                /* Do nothing */
            }
            break;

        default:
            gI2CRCnt = 0U;
            gI2CMode = MODE_I2C_INITIAL;
            break;
        }
    }
}

/**
  * @brief  Config the GPIO for I2C
  * @param  None
  * @retval None
  */
void I2C_IO_Configuration(void)
{
    GPIO_EnableFuncReg(GPIO_PC, GPIO_FUNC_REG_1, GPIO_BIT_0);
    GPIO_EnableFuncReg(GPIO_PC, GPIO_FUNC_REG_1, GPIO_BIT_1);
    GPIO_SetOutputEnableReg(GPIO_PC, GPIO_BIT_0, ENABLE);
    GPIO_SetOutputEnableReg(GPIO_PC, GPIO_BIT_1, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PC, GPIO_BIT_0, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PC, GPIO_BIT_1, ENABLE);
    GPIO_SetOpenDrain(GPIO_PC, GPIO_BIT_0, ENABLE);
    GPIO_SetOpenDrain(GPIO_PC, GPIO_BIT_1, ENABLE);
}


#ifdef DEBUG
/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
