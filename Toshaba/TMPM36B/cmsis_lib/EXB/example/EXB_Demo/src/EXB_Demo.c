/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of EXB demo for the 
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include <stdio.h>
#include <string.h>
#include "tmpm36b_exb.h"
#include "tmpm36b_gpio.h"

#define SRAM_RW

#ifdef SRAM_RW
#define TEST_DATA_LEN           ((uint16_t)0x0010)
#define EXB_SRAM_START_ADDR     ((uint32_t)0x60000000)
void EXB_GPIOConfig(void);
Result rw_result = ERROR;


#endif
/*******************************************************************************
* Function Name  : main
* Description    : main function:demo for external 16-bit SRAM, multiplex bus mode
* Input          : None.
* Return         : None.
*******************************************************************************/

int EXB_Demo(void)
{
    uint8_t chip = EXB_CS0;
    uint8_t BusMode = EXB_BUS_MULTIPLEX;        /* Address bus and data bus are multiplexed */
    uint8_t Cycle = EXB_CYCLE_QUADRUPLE;
    /* Initial process demo */

#ifdef SRAM_RW
    uint32_t w_data[TEST_DATA_LEN] = { 0U };
    uint32_t r_data[TEST_DATA_LEN] = { 0U };
    uint16_t rw_cnt = 0U;
    uint32_t *addr = NULL;
    uint16_t i = 0U;
    EXB_InitTypeDef InitStruct = { 0U };
#endif

    InitStruct.AddrSpaceSize = EXB_128K_BYTE;
    InitStruct.StartAddr = 0x00;
    InitStruct.BusWidth = EXB_BUS_WIDTH_BIT_16;
    /* Set cycles time according to AC timing of SRAM datasheet,base clock: EXBCLK(fsys) */
    InitStruct.Cycles.InternalWait = EXB_INTERNAL_WAIT_8;
    InitStruct.Cycles.ReadSetupCycle = EXB_CYCLE_2;
    InitStruct.Cycles.WriteSetupCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ALEWaitCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ReadRecoveryCycle = EXB_CYCLE_2;
    InitStruct.Cycles.WriteRecoveryCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ChipSelectRecoveryCycle = EXB_CYCLE_2;

#ifdef SRAM_RW
    EXB_GPIOConfig();
#endif

    EXB_SetBusMode(BusMode);
    EXB_SetBusCycleExtension(Cycle);
    EXB_Init(chip, &InitStruct);
    EXB_Enable(chip);

#ifdef SRAM_RW
    /* SRAM Read/Write demo */
    addr = (uint32_t *) (((uint32_t) InitStruct.StartAddr) | EXB_SRAM_START_ADDR);
    for (i = 0U; i < TEST_DATA_LEN; i++) {
        w_data[i] = i;
    }

    rw_cnt = TEST_DATA_LEN * (sizeof(w_data[0]));
    memcpy(addr, w_data, (uint32_t) rw_cnt);
    __DSB();
    memcpy(r_data, addr, (uint32_t) rw_cnt);
    /* check rw_result to see if SRAM write/read is sucessful or not */
    if (memcmp(w_data, r_data, (uint32_t) rw_cnt) == 0U) {
        rw_result = SUCCESS;
    } else {
        rw_result = ERROR;
    }
#endif
    while (1) {
        /* Do nothing */
    }

}

/**
  * @brief  Configure GPIO to EXB
  * @param  None
  * @retval None
  */


void EXB_GPIOConfig(void)
{
    /* PBFR1 */
    GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_ALL, ENABLE);
    GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_1, 0x7FU);
    GPIO_SetInputEnableReg(GPIO_PB, 0x3FU, ENABLE);
    GPIO_SetPullUp(GPIO_PB, 0x7FU, DISABLE);

    /* PE PORT[0:7]address bus(A16-A23) */

    GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_ALL, ENABLE);
    GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_3, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_ALL, ENABLE);

    /* PFFR1 as DATA(D0-D7)/AD0-AD7  bus */
    GPIO_SetOutputEnableReg(GPIO_PF, GPIO_BIT_ALL, ENABLE);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_1, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PF, GPIO_BIT_ALL, ENABLE);

    /* PGFR1 as DATA(D8-D15)/AD8-AD15  bus */
    GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_ALL, ENABLE);
    GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_1, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_ALL, ENABLE);
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
