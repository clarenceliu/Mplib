/**
 *******************************************************************************
 * @file    cg.c
 * @brief   The driver functions of CG for the TOSHIBA 'TMPM037' Device Series 
 * @version V0.101
 * @date    2014/06/16
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "cg.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CG_WUODR_EXT     ((uint16_t)0xC350)
#define CG_WUODR_FOSC     ((uint16_t)0xC350)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
Result CG_DisableClkMulCircuit(void);
void switchFromIHOSCtoEHOSC(void);
/* Private functions ---------------------------------------------------------*/

/* CG_SetSystem */
void CG_SetSystem(void)
{
    if (CG_GetFoscSrc()==CG_FOSC_OSC_INT){
        /* Switch over from IHOSC to EHOSC*/
        switchFromIHOSCtoEHOSC();
    }
    /* Disable PLL. PLL cannot be used, since fosc = 16MHz that larger than 10 MHz. */
    CG_DisableClkMulCircuit();
    /* Set fgear = fc/2 */
    CG_SetFgearLevel(CG_DIVIDE_2);
    /* Set fperiph to fgear */
    CG_SetPhiT0Src(CG_PHIT0_SRC_FGEAR);
    /* Set ¦µT0 = fc/2 */
    CG_SetPhiT0Level(CG_DIVIDE_2);
    /* Set low power consumption mode stop1 */
    CG_SetSTBYMode(CG_STBY_MODE_STOP1);
}

/* CG_NormalToStop */
void CG_NormalToStop(void)
{
    /* Set CG module: Normal ->Stop mode */
    CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_EXT_HIGH, CG_WUODR_EXT);
    /* Enter stop mode */
    __WFI();
}

/* CG_DisableClkMulCircuit */
Result CG_DisableClkMulCircuit(void)
{
    Result retval = ERROR;
    WorkState st = BUSY;
    retval = CG_SetFcSrc(CG_FC_SRC_FOSC);
    if (retval == SUCCESS) {
        /* Set warm up time */
        CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_EXT_HIGH, CG_WUODR_FOSC);
        CG_StartWarmUp();

        do {
            st = CG_GetWarmUpState();
        } while (st != DONE);

        /* fc source is set to fosc, so PLL can be disabled successfully. */
        retval = CG_SetPLL(DISABLE);
    } else {
        /*Do nothing */
    }

    return retval;
}

/* Switch over from IHOSC to EHOSC*/
void switchFromIHOSCtoEHOSC(void)
{
    /* Enable high-speed oscillator */
    CG_SetFosc(CG_FOSC_OSC_EXT, ENABLE);
    /* Select internal(fIHOSC) as warm-up clock */
    CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_INT_HIGH, CG_WUODR_EXT);
    /* Start warm-up */
    CG_StartWarmUp();
    /* Wait until EHOSC become stable */
    while (CG_GetWarmUpState()!=DONE) {
    }
    /* Set fosc source */
    CG_SetFoscSrc(CG_FOSC_OSC_EXT);
    /* Wait for <OSCSEL> to become "1" */
    while (CG_GetFoscSrc()!=CG_FOSC_OSC_EXT) {
    }
    /* Stop IHOSC */
    CG_SetFosc(CG_FOSC_OSC_INT, DISABLE);
}
/*********************************** END OF FILE ******************************/
