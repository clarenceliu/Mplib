/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of LVD demo
 *          for the TOSHIBA 'TMPM037' Device Series
 * @version V0.100
 * @date    2014/05/19
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "LVD_DEMO.h"

int LVD_DEMO(void)
{
    LVD_EnableVD1();
    LVD_SetVD1Level(LVD_VDLVL1_290);
    hardware_init(UART_RETARGET);
    while (1) {
        if (LVD_GetVD1Status() == LVD_VD_UPPER) {
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
