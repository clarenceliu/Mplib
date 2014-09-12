/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of RMC_Receiving demo for the TOSHIBA
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
#include "RMC_Receiving.h"

void PrintCode(char *ch, uint16_t addr, uint32_t cmd);
/**
  * @brief  main  function
  * @param  None
  * @retval None
  */
int RMC_Receiving(void)
{
    CG_SetFs(ENABLE);

    SIO_Configuration(UART0);
    SIO_ChInit();

    Timer_ChInit(TSB_TB0);

    RMC_Configuration(TSB_RMC0);        /*RMC0 IO initial */
    RMC_ChInit(TSB_RMC0);       /* configure RMC0 */

    /* Initialize Variables */
    gSIORdIndex = 0U;
    gSIOWrIndex = 0U;
    fSIO_INT = 0U;
    fTMRB0_INT = 0U;

    fRMCDone = RMC_NON;
    fRMCPress = RELEASE;

    NVIC_EnableIRQ(INTTX0_IRQn);
    NVIC_EnableIRQ(INTRMCRX_IRQn);
    printf("TMPM36B RMC Receiving DEMO\n");
    for (;;) {
        if (fRMCDone == RMC_DONE) {     /* RMC reception complete */
            RMC_SetRxCtrl(TSB_RMC0, DISABLE);   /* stop RMC receiving */
            RMCRcv();           /* get TSB_RMC0 gAddress and gCommand */

            PrintCode(FORMAT, gRMC_Address, gRMC_Command);      /*Print code received by RMC */
            RMC_SetRxCtrl(TSB_RMC0, ENABLE);    /* start RMC receiving */
        } else {
            /* Do nothing */
        }
    }
}

/**
  * @brief  Print code received by RMC.
  * @param  Format name, address, command
  * @retval None
  */
void PrintCode(char *ch, uint16_t addr, uint32_t cmd)
{
#ifdef RMC_1
    printf("%s: %02x %02x\r\n", ch, addr, cmd);
#endif

#ifdef RMC_2
    printf("%s: %02x %02x\r\n", ch, addr, cmd);
#endif

#ifdef RMC_3
    printf("%s: %04x %06x\r\n", ch, addr, cmd);
#endif

#ifdef RMC_4
    if (gRMC_4Address != 13U) {
        printf("%s: %02x %02x\r\n", ch, addr, cmd);
    } else {
        printf("%s: %04x %02x\r\n", ch, addr, cmd);
    }
#endif

#ifdef RMC_5
    printf("%s: %02x %02x\r\n", ch, addr, cmd);
#endif
#ifdef RMC_6
    printf("%s: %02x %02x\r\n", ch, addr, cmd);
#endif
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
