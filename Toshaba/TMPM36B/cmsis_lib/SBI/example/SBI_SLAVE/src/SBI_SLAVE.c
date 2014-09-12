/**
 *******************************************************************************
 * @file    main.c
 * @brief   The main functions of SBI slave demo for the
 *          TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20 
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "SBI_SLAVE.h"

Result gTRxResult;
SBI_InitI2CTypeDef myI2C;
uint32_t gI2CWCnt;
uint32_t gI2CRCnt;
uint32_t gI2CTxDataLen;
char gI2CTxData[16] = { 0 };

uint32_t gI2CRxDataLen;
char gI2CRxData[16] = { 0 };

uint32_t gSBIMode;

/**
  * @brief  The main routine of SBI demo I2C
  * @param  None
  * @retval None
  */
int SBI_SLAVE(void)
{
    uint32_t gICnt;
    SBI_I2CState i2c_state;

    SW_Init();
    hardware_init(UART_RETARGET);

    /*  Initialize IO for SBIs */
    SBI2_IO_Configuration();
    SBI0_IO_Configuration();
    /* Initialize SBI channel 2 */
    myI2C.I2CSelfAddr = SELF_ADDR;
    myI2C.I2CDataLen = SBI_I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = SBI_I2C_CLK_DIV_328;
    SBI_Enable(TSB_SBI2);
    SBI_SWReset(TSB_SBI2);
    SBI_InitI2C(TSB_SBI2, &myI2C);
    NVIC_EnableIRQ(INTSBI2_IRQn);
    /* Initialize SBI channel 0 */
    myI2C.I2CSelfAddr = SLAVE_ADDR;
    myI2C.I2CDataLen = SBI_I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = SBI_I2C_CLK_DIV_328;
    SBI_Enable(TSB_SBI0);
    SBI_SWReset(TSB_SBI0);
    SBI_InitI2C(TSB_SBI0, &myI2C);
    NVIC_EnableIRQ(INTSBI0_IRQn);

    common_uart_disp("K3: SBI2 to SBI0");
    common_uart_disp("\r\n");
    common_uart_disp("\r\n");
    /* Initialize variables for SBIs */
    gI2CTxDataLen = 0U;
    gI2CWCnt = 0U;
    gI2CRxDataLen = 0U;
    gI2CRCnt = 0U;
    gSBIMode = MODE_SBI_I2C_IDLE;

    while (1) {
        switch (gSBIMode) {
            /* SW3 input check */
        case MODE_SBI_I2C_IDLE:
            if (SW_Get(SW3)) {
                gSBIMode = MODE_SBI_I2C_INITIAL;
            } else {
                /* Do nothing */
            }
            break;
            /* Initialize TRx buffer and Tx length */
        case MODE_SBI_I2C_INITIAL:
            gI2CTxDataLen = 7U;
            gI2CTxData[0] = gI2CTxDataLen;
            gI2CTxData[1] = 'T';
            gI2CTxData[2] = 'O';
            gI2CTxData[3] = 'S';
            gI2CTxData[4] = 'H';
            gI2CTxData[5] = 'I';
            gI2CTxData[6] = 'B';
            gI2CTxData[7] = 'A';
            gI2CWCnt = 0U;
            for (gICnt = 0U; gICnt < 8U; gICnt++) {
                gI2CRxData[gICnt] = 0U;
            }
            gSBIMode = MODE_SBI_I2C_START;
            break;
            /* Check I2C bus state and start TRx */
        case MODE_SBI_I2C_START:
            i2c_state = SBI_GetI2CState(TSB_SBI2);
            if (!i2c_state.Bit.BusState) {
                SBI_SetSendData(TSB_SBI2, SLAVE_ADDR | SBI_I2C_SEND);
                SBI_GenerateI2CStart(TSB_SBI2);
                gSBIMode = MODE_SBI_I2C_TRX;
            } else {
                /* Do nothing */
            }
            break;
            /* Read I2C bus state to check TRx end */
        case MODE_SBI_I2C_TRX:
            if (gI2CRCnt > gI2CRxData[0]) {
                gI2CRxDataLen = gI2CRxData[0];
                gI2CRCnt = 0U;
                gSBIMode = MODE_SBI_I2C_FINISHED;
            } else {
                /* Do nothing */
            }
            break;
            /* Check transmission result */
        case MODE_SBI_I2C_FINISHED:
            if ((gI2CTxData[gI2CTxDataLen] == gI2CRxData[gI2CRxDataLen])) {
                gTRxResult = SUCCESS;
                common_uart_disp("Write Over");
                common_uart_disp("\r\n");
                common_uart_disp("K1: Show SBI0");
                common_uart_disp("\r\n");
                gSBIMode = MODE_SBI_I2C_CHECK;
            } else {
                gTRxResult = ERROR;
                common_uart_disp("Write ERROR");
                gSBIMode = MODE_SBI_I2C_IDLE;
            }
            break;

        case MODE_SBI_I2C_CHECK:
            if (SW_Get(SW1)) {
                for (gICnt = 1U; gICnt <= gI2CRxDataLen; gICnt++) {
                    gI2CRxData[gICnt - 1] = gI2CRxData[gICnt];
                }
                gI2CRxData[gI2CRxDataLen] = 0U;
                common_uart_disp(gI2CRxData);
                common_uart_disp("\r\n");
                common_uart_disp("SBI2 to SBI0 OK");
                common_uart_disp("\r\n");
                gSBIMode = MODE_SBI_I2C_IDLE;
            } else {
                /* Do nothing */
            }
            break;

        default:
            gI2CTxDataLen = 0U;
            gI2CWCnt = 0U;
            gI2CRxDataLen = 0U;
            gI2CRCnt = 0U;
            gSBIMode = MODE_SBI_I2C_IDLE;
            break;
        }
    }
}

/**
  * @brief  Config the GPIO for SBI2
  * @param  None
  * @retval None
  */
void SBI2_IO_Configuration(void)
{
    GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_5, GPIO_BIT_0);
    GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_5, GPIO_BIT_1);
    GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_1, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_1, ENABLE);
    GPIO_SetOpenDrain(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetOpenDrain(GPIO_PH, GPIO_BIT_1, ENABLE);
    /* Pull up for SDA&SCL */
    GPIO_SetPullUp(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetPullUp(GPIO_PH, GPIO_BIT_1, ENABLE);
}

/**
  * @brief  Config the GPIO for SBI0
  * @param  None
  * @retval None
  */
void SBI0_IO_Configuration(void)
{
    GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_3, GPIO_BIT_2);
    GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_3, GPIO_BIT_3);
    GPIO_SetOutputEnableReg(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetOutputEnableReg(GPIO_PK, GPIO_BIT_3, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PK, GPIO_BIT_3, ENABLE);
    GPIO_SetOpenDrain(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetOpenDrain(GPIO_PK, GPIO_BIT_3, ENABLE);
    /* Pull up for SDA&SCL */
    GPIO_SetPullUp(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetPullUp(GPIO_PK, GPIO_BIT_3, ENABLE);
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
