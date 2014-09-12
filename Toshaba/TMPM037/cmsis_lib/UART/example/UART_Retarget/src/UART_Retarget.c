/** 
 *******************************************************************************
 * @file    main.c
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
#include "UART_Retarget.h"
void delay(void);
/**
  * @brief  main  function
  * @param  None
  * @retval int
  */
int UART_Retarget(void)
{
    uint8_t SW_info;
    uint8_t wait_SW0 = 1U;
    char TxBuffer[] = "TMPM037";

    /* Initialize system */
    SW_Init();
    SIO_Configuration(UART_RETARGET);
    SIO_ChInit();

    /* enable retarget Channel TX interrupt */
    NVIC_EnableIRQ(RETARGET_INT);

    while (1) {

        while (wait_SW0) {
            /* read switch SW0 input */
            SW_info = SW_Get(SW_PORT);
            delay();
            if (SW_info == 1) {
                /* wait for switch SW0 released */
                do {
                    wait_SW0 = 0U;
                    SW_info = SW_Get(SW_PORT);
                    delay();
                } while (SW_info != SWRELEASE);
            }
        }

        delay();
        printf("%s\r\n", TxBuffer);     /* SIO0 send data */

        while (fSIOTxOK == NO) {        /* wait for UART_RETARGET finish send */
            /* Do nothing */
        }
        fSIOTxOK = NO;
        wait_SW0 = 1U;
    }
}

/**
  * @brief  Delay some time
  * @param  None
  * @retval None
  */
void delay(void)
{
    uint32_t i = 0U;
    for (i = 0U; i < 0xFFFFU; i++) {
        /* Do nothing */
    }
}

/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
