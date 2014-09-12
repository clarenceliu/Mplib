/**
 *******************************************************************************
 * @file    main.c
 * @brief   The main functions of I2C master demo for the
 *          TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "I2C_MASTER.h"
I2C_InitTypeDef myI2C;
uint32_t gI2CWCnt;
uint32_t gI2CTxDataLen;
char gI2CTxData[8] = { 0 };

uint32_t gI2CMode;

uint8_t getkey(uint8_t sw);
void I2C_IO_Configuration(void);

/**
  * @brief  The main routine of I2C
  * @param  None
  * @retval None
  */
int I2C_MASTER(void)
{
    I2C_State i2c_state;
    SW_Init();

    /* Initialize IO for I2C */
    I2C_IO_Configuration();
    /* Initialize I2C channel */
    myI2C.I2CSelfAddr = SELF_ADDR;
    myI2C.I2CDataLen = I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = I2C_SCK_CLK_DIV_32;
    myI2C.PrescalerClkDiv = I2C_PRESCALER_DIV_12;

    I2C_SWReset();
    I2C_Init(&myI2C);
    NVIC_EnableIRQ(INTI2C0_IRQn);
    I2C_SetINTReq(ENABLE);

    /* Initialize variables for I2C */
    gI2CTxDataLen = 0U;
    gI2CWCnt = 0U;
    gI2CMode = MODE_I2C_IDLE;

    while (1) {
        switch (gI2CMode) {
            /* SW3 input check */
        case MODE_I2C_IDLE:
            if (getkey(SW3)) {
                while (SW_Get(SW3));
                gI2CMode = MODE_I2C_INITIAL;
            } else {
                /* Do nothing */
            }
            break;
            /* Initialize TRx buffer and Tx length */
        case MODE_I2C_INITIAL:
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
            gI2CMode = MODE_I2C_START;
            break;
            /* Check I2C bus state and start TRx */
        case MODE_I2C_START:
            i2c_state = I2C_GetState();
            if (!i2c_state.Bit.BusState) {
                gI2CMode = MODE_I2C_TRX;
                I2C_SetSendData(SLAVE_ADDR | I2C_SEND);
                I2C_GenerateStart();
            } else {
                /* Do nothing */
            }
            break;
        case MODE_I2C_TRX:
            if (gI2CWCnt > 7) {
                gI2CWCnt = 0U;
                gI2CMode = MODE_I2C_IDLE;
            } else {
                /* Do nothing */
            }
            break;
        default:
            gI2CTxDataLen = 0U;
            gI2CWCnt = 0U;
            gI2CMode = MODE_I2C_IDLE;
            break;
        }
    }
}


/**
  * @brief  Get state of SW3 to check key value is or not same
  * @param  None
  * @retval None
  */
uint8_t getkey(uint8_t sw)
{
    uint32_t i = 20000;
    uint8_t keyflag;
    uint8_t oneflag, twoflag;
    oneflag = SW_Get(sw);
    while (i--);
    twoflag = SW_Get(sw);
    if (oneflag != twoflag) {
        keyflag = 1;
    } else {
        keyflag = 0;
    }
    return keyflag;
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
