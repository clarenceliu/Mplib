/** 
 *******************************************************************************
 * @file    retarget.c
 * @brief   the application functions of UART_Retarget demo for the TOSHIBA
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
#include "UART_Retarget.h"
/* External function prototypes ----------------------------------------------*/
extern uint8_t send_char(uint8_t ch);

/**
  * @brief  Retarget printf to uart.
  * @param  IAR:Character to be sent.KEIL:Character to be sent.
  * @retval Character to be sent
  */

#if defined ( __CC_ARM   )      /* RealView Compiler */
struct __FILE {
    int handle;                 /* Add whatever you need here */
};
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE * f)
#elif defined ( __ICCARM__ )    /*IAR Compiler */
int putchar(int ch)
#endif
{
    return (send_char(ch));
}
