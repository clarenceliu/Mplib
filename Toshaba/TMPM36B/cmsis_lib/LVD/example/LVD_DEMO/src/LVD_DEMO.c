/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of LVD demo
 *          for the TOSHIBA 'TMPM36B' Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "LVD_DEMO.h"

int LVD_DEMO(void)
{
    LVD_EnableVD2();
    LVD_SetVD2Level(LVD_VDLVL2_315);
    hardware_init(UART_RETARGET);
    while (1) {
        if (LVD_GetVD2Status() == LVD_VD_UPPER) {
            common_uart_disp("UPPER\n");
        } else {
            common_uart_disp("LOWER\n");
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
