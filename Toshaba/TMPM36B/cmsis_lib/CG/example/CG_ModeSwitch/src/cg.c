/**
 *******************************************************************************
 * @file    cg.c
 * @brief   The driver functions of CG for the TOSHIBA 'TMPM36B' Device Series 
 * @version V0.102
 * @date    2014/06/12
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
#define CG_WUODR_EXT     ((uint16_t)0x09C4)
#define CG_WUODR_PLL     ((uint16_t)0x09C4)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
Result CG_EnableClkMulCircuit(void);
void switchFromIHOSCtoEHOSC(void);
/* Private functions ---------------------------------------------------------*/

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

/* CG_SetSystem */
void CG_SetSystem(void)
{    
    TSB_CG->SYSCR &= 0x10000;
    if (CG_GetFoscSrc() == CG_FOSC_OSC_INT){
      /* Switch over from IHOSC to EHOSC*/
       switchFromIHOSCtoEHOSC();
    }
    /* Set up pll and wait for pll to warm up, set fc source to fpll */
    CG_EnableClkMulCircuit();
    /* Set fgear = fc/2 */
    CG_SetFgearLevel(CG_DIVIDE_2);
    /* Set fperiph to fgear */
    CG_SetPhiT0Src(CG_PHIT0_SRC_FGEAR);
    CG_SetPhiT0Level(CG_DIVIDE_8);
    /* Set low power consumption mode stop */
    CG_SetSTBYMode(CG_STBY_MODE_STOP1);
    /* Set pin status in stop mode to "active" */
    CG_SetPinStateInStop1Mode(ENABLE);
}

/* CG_NormalToStop */
void CG_NormalToStop(void)
{
    /* Set CG module: Normal ->Stop mode */
    CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_EXT_HIGH, CG_WUODR_EXT);
    /* Enter stop mode */
    __WFI();
}

/* CG_EnableClkMulCircuit */
Result CG_EnableClkMulCircuit(void)
{
    Result retval = ERROR;
    WorkState st = BUSY;
    CG_SetPLL(DISABLE);
#ifdef TSB_M36BFY
    CG_SetFPLLValue(CG_FPLL_10M_MULTIPLY_8);
#elif defined (TSB_M36BF10 )
    CG_SetFPLLValue(CG_FPLL_8M_10M_MULTIPLY_6);
#endif
    retval = CG_SetPLL(ENABLE);
    if (retval == SUCCESS) {
        /* Set warm up time */
        CG_SetWarmUpTime(CG_WARM_UP_SRC_OSC_EXT_HIGH, CG_WUODR_PLL);
        CG_StartWarmUp();

        do {
            st = CG_GetWarmUpState();
        } while (st != DONE);

        retval = CG_SetFcSrc(CG_FC_SRC_FPLL);
    } else {
        /*Do nothing */
    }

    return retval;
}

/*********************************** END OF FILE ******************************/
