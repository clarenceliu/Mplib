/**
 *******************************************************************************
 * @file    tmpm341_cg.c
 * @brief   This file provides API functions for CG driver 
 * @version V2.0.2.5
 * @date    2011/03/23
 * 
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 * 
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm341_cg.h"

#if defined(__TMPM341_CG_H)
/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @defgroup CG
  * @brief CG driver modules
  * @{
  */

/** @defgroup CG_Private_Defines
  * @{
  */
#define CG_FC_GEAR_MASK             ((uint32_t)0xFFFFFFF8)
#define CG_PRCK_MASK                ((uint32_t)0xFFFFF8FF)
#define CG_SCOUT_MASK               ((uint32_t)0xFFFCFFFF)
#define CG_WUP_TIME_MASK            ((uint32_t)0x00070107)
#define CG_WUP_COUNTER_MASK         ((uint32_t)0x00000030)

#define CG_PLLSET_VALUE_MASK        ((uint32_t)0x0000FFFE)
#define CG_FTMRD_GEAR_MASK          ((uint32_t)0xFFFFFFCF)

#define CG_STBY_MODE_MASK           ((uint32_t)0xFFFFFFF8)
#define CG_NMIFLG_MASK              ((uint32_t)0xFFFFFFFC)
#define CG_RESET_FLAG_MASK          ((uint32_t)0xFFFFFFC2)
#define CG_FPSEL_MASK               ((uint32_t)0xFFFFEFFF)

#define FC_GEAR_1_1                 ((uint32_t)0x00000000)
#define FC_GEAR_1_2                 ((uint32_t)0x00000004)
#define FC_GEAR_1_4                 ((uint32_t)0x00000005)
#define FC_GEAR_1_8                 ((uint32_t)0x00000006)
#define FC_GEAR_1_16                ((uint32_t)0x00000007)

#define FPLL_MULTIPLY_8_VALUE       ((uint32_t)0x0000503A)
#define FPLL_MULTIPLY_16_VALUE      ((uint32_t)0x0000607A)

#define WARM_UP_SEL_OSC_EXT         ((uint32_t)0x00080000)
#define WARM_UP_SEL_OSC_INT         ((uint32_t)0x00000000)


#define SCOUT_SRC_HALF_FSYS         ((uint32_t)0x00010000)
#define SCOUT_SRC_FSYS              ((uint32_t)0x00020000)
#define SCOUT_SRC_PHIT0             ((uint32_t)0x00030000)

#define FTMRD_GEAR_1_1              ((uint32_t)0x00000000)
#define FTMRD_GEAR_1_2              ((uint32_t)0x00000010)
#define FTMRD_GEAR_1_4              ((uint32_t)0x00000020)

#define CG_PROTECT_MASK             ((uint32_t)0xFFFFFF00)
#define CG_PROTECT_SET              ((uint32_t)0x000000C1)
#define CG_PROTECT_CLEAR            ((uint32_t)0x0000003E)

typedef union {
    uint32_t byte4;
    uint8_t byte[4];
} CG_Byte4;

static CG_DivideLevel numToDivideLevel_table[CG_DIVIDE_MAX] = {
    CG_DIVIDE_1,
    CG_DIVIDE_2,
    CG_DIVIDE_4,
    CG_DIVIDE_8,
    CG_DIVIDE_16,
    CG_DIVIDE_32,
    CG_DIVIDE_64,
    CG_DIVIDE_128,
    CG_DIVIDE_256,
    CG_DIVIDE_512,
    CG_DIVIDE_UNKNOWN,
};

static CG_PhiT0Src numPhiT0Src_table[CG_PHIT0_SRC_MAX] = {
    CG_PHIT0_SRC_FGEAR,
    CG_PHIT0_SRC_FC,
};

static CG_STBYMode numToSTBYMode_table[CG_STBY_MODE_MAX] = {
    CG_STBY_MODE_UNKNOWN,
    CG_STBY_MODE_STOP1,
    CG_STBY_MODE_UNKNOWN,
    CG_STBY_MODE_IDLE,
    CG_STBY_MODE_UNKNOWN,
    CG_STBY_MODE_STOP2,
    CG_STBY_MODE_UNKNOWN,
    CG_STBY_MODE_UNKNOWN,
};

/** @} */
/* End of group CG_Private_Defines */

/** @defgroup CG_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group CG_Private_FunctionPrototypes */

/** @defgroup CG_Private_Functions
  * @{
  */

/** @} */
/* End of group CG_Private_Functions */

/** @defgroup CG_Exported_Functions
  * @{
  */

/**
  * @brief  Set dividing level between clock fgear and fc.
  * @param  DivideFgearFromFc: Dividing level between fgear and fc.
  *   This parameter can be one of the following values:
  *   CG_DIVIDE_1, CG_DIVIDE_2, CG_DIVIDE_4, CG_DIVIDE_8, CG_DIVIDE_16
  * @retval None
  */
void CG_SetFgearLevel(CG_DivideLevel DivideFgearFromFc)
{
    uint32_t gear = FC_GEAR_1_1;
    uint32_t regval = TSB_CG->SYSCR;

    /* Check the parameters */
    assert_param(IS_CG_GEAR_DIVIDE_LEVEL(DivideFgearFromFc));

    /* Set the value of fgear */
    switch (DivideFgearFromFc) {
    case CG_DIVIDE_1:
        gear = FC_GEAR_1_1;
        break;
    case CG_DIVIDE_2:
        gear = FC_GEAR_1_2;
        break;
    case CG_DIVIDE_4:
        gear = FC_GEAR_1_4;
        break;
    case CG_DIVIDE_8:
        gear = FC_GEAR_1_8;
        break;
    case CG_DIVIDE_16:
        gear = FC_GEAR_1_16;
        break;
    default:
        /* Do nothing */
        break;
    }

    regval &= CG_FC_GEAR_MASK;
    regval |= gear;
    TSB_CG->SYSCR = regval;
}

/**
  * @brief  Get dividing level between clock fgear and fc.
  * @param  None
  * @retval The dividing level between clock fgear and fc
  *   The value returned can be one of the following values:
  *   CG_DIVIDE_1, CG_DIVIDE_2, CG_DIVIDE_4,
  *   CG_DIVIDE_8, CG_DIVIDE_16 or CG_DIVIDE_UNKNOWN
  */
CG_DivideLevel CG_GetFgearLevel(void)
{
    CG_DivideLevel DivideFgearFromFc = CG_DIVIDE_UNKNOWN;
    uint32_t syscr = TSB_CG->SYSCR;
    syscr &= (~CG_FC_GEAR_MASK);

    switch (syscr) {
    case FC_GEAR_1_1:
        DivideFgearFromFc = CG_DIVIDE_1;
        break;
    case FC_GEAR_1_2:
        DivideFgearFromFc = CG_DIVIDE_2;
        break;
    case FC_GEAR_1_4:
        DivideFgearFromFc = CG_DIVIDE_4;
        break;
    case FC_GEAR_1_8:
        DivideFgearFromFc = CG_DIVIDE_8;
        break;
    case FC_GEAR_1_16:
        DivideFgearFromFc = CG_DIVIDE_16;
        break;
    default:
        /* Do nothing */
        break;
    }

    return DivideFgearFromFc;
}

/**
  * @brief  Set fperiph for PhiT0
  * @param  PhiT0Src: Set PhiT0 Source
  *   This parameter can be one of the following values:
  *   CG_PHIT0_SRC_FGEAR or CG_PHIT0_SRC_FC
  * @retval None
  */
void CG_SetPhiT0Src(CG_PhiT0Src PhiT0Src)
{
    uint32_t regval = 0U;
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_CG_PHIT0_SRC(PhiT0Src));

    regval = TSB_CG->SYSCR;
    regval &= CG_FPSEL_MASK;
    tmp = (uint32_t) PhiT0Src;
    regval |= (tmp << 12U);

    TSB_CG->SYSCR = regval;
}

/**
  * @brief  Get PhiT0 Source
  * @param  None
  * @retval The source of PhiT0
  *   The value returned can be one of the following values:
  *   CG_PHIT0_SRC_FGEAR or CG_PHIT0_SRC_FC
  */
CG_PhiT0Src CG_GetPhiT0Src(void)
{
    uint32_t regval = 0U;
    CG_PhiT0Src source = CG_PHIT0_SRC_FGEAR;

    regval = TSB_CG->SYSCR;
    regval &= (~CG_FPSEL_MASK);
    regval = (regval >> 12U);
    source = numPhiT0Src_table[regval];

    return source;
}

/**
  * @brief  Set dividing level between clock PhiT0 and fc.
  * @param  DividePhiT0FromFc: Dividing level between PhiT0 and fc.
  *   This parameter can be one of the following values:
  *   CG_DIVIDE_1, CG_DIVIDE_2, CG_DIVIDE_4, CG_DIVIDE_8,
  *   CG_DIVIDE_16, CG_DIVIDE_32, CG_DIVIDE_64, CG_DIVIDE_128,
  *   CG_DIVIDE_256 or CG_DIVIDE_512
  * @retval  Success or not
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetPhiT0Level(CG_DivideLevel DividePhiT0FromFc)
{
    uint32_t fprclk = 0U;
    CG_DivideLevel fgear = CG_DIVIDE_UNKNOWN;
    CG_PhiT0Src PhiT0_src = CG_PHIT0_SRC_FGEAR;
    Result retval = ERROR;
    uint32_t regval = TSB_CG->SYSCR;

    PhiT0_src = CG_GetPhiT0Src();
    if (PhiT0_src == CG_PHIT0_SRC_FC) {
        /* Check the parameters */
        assert_param(IS_CG_DIVIDE_FC_LEVEL(DividePhiT0FromFc));

        fprclk = (uint32_t) DividePhiT0FromFc;
        regval &= CG_PRCK_MASK;
        fprclk <<= 8U;
        regval |= fprclk;
        TSB_CG->SYSCR = regval;
        retval = SUCCESS;
    } else {
        /* Check the parameters */
        assert_param(IS_CG_DIVIDE_FC_LEVEL(DividePhiT0FromFc));

        fgear = CG_GetFgearLevel();
        if (fgear != CG_DIVIDE_UNKNOWN) {
            if (DividePhiT0FromFc >= fgear) {
                fprclk = (uint32_t) DividePhiT0FromFc - (uint32_t) fgear;
                if (fprclk < CG_DIVIDE_64) {
                    regval &= CG_PRCK_MASK;
                    fprclk <<= 8U;
                    regval |= fprclk;
                    TSB_CG->SYSCR = regval;
                    retval = SUCCESS;
                } else {
                    /* Do nothing */
                }
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
    }

    return retval;
}

/**
  * @brief  Get dividing level between clock phiT0 and fc.
  * @param  None
  * @retval The divide level between clock phiT0 and fc
  *   The value returned can be one of the following values:
  *   CG_DIVIDE_1, CG_DIVIDE_2, CG_DIVIDE_4, CG_DIVIDE_8,
  *   CG_DIVIDE_16, CG_DIVIDE_32, CG_DIVIDE_64, CG_DIVIDE_128,
  *   CG_DIVIDE_256, CG_DIVIDE_512 or CG_DIVIDE_UNKNOWN
  */
CG_DivideLevel CG_GetPhiT0Level(void)
{
    uint32_t fprclk = 0U;
    CG_DivideLevel fgear = CG_DIVIDE_UNKNOWN;
    CG_DivideLevel phiT0Level = CG_DIVIDE_UNKNOWN;
    CG_PhiT0Src PhiT0_src = CG_PHIT0_SRC_FGEAR;

    fprclk = TSB_CG->SYSCR & (~CG_PRCK_MASK);
    fprclk = (uint32_t) (fprclk >> 8U);
    PhiT0_src = CG_GetPhiT0Src();

    if (PhiT0_src == CG_PHIT0_SRC_FC) {
        phiT0Level = numToDivideLevel_table[fprclk];
    } else {
        fgear = CG_GetFgearLevel();
        if (fgear != CG_DIVIDE_UNKNOWN) {
            fprclk = fprclk + fgear;
            if (fprclk < CG_DIVIDE_UNKNOWN) {
                phiT0Level = numToDivideLevel_table[fprclk];
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
    }

    return phiT0Level;
}

/**
  * @brief Set the source of SCOUT output
  * @param Source: Select source of SCOUT
  *   This parameter can be one of the following values:
  *   CG_SCOUT_SRC_HALF_FSYS, CG_SCOUT_SRC_FSYS
  *   or CG_SCOUT_SRC_PHIT0
  * @retval None
  */
void CG_SetSCOUTSrc(CG_SCOUTSrc Source)
{
    /* Get the original SCOUT SRC value */
    uint32_t tmp = 0U;
    uint32_t regval = TSB_CG->SYSCR;

    /* Check the parameters */
    assert_param(IS_CG_SCOUT_SRC(Source));

    switch (Source) {
    case CG_SCOUT_SRC_HALF_FSYS:
        tmp = SCOUT_SRC_HALF_FSYS;
        break;
    case CG_SCOUT_SRC_FSYS:
        tmp = SCOUT_SRC_FSYS;
        break;
    case CG_SCOUT_SRC_PHIT0:
        tmp = SCOUT_SRC_PHIT0;
        break;
    default:
        /* Do nothing */
        break;
    }

    regval &= CG_SCOUT_MASK;
    regval |= tmp;
    TSB_CG->SYSCR = regval;
}

/**
  * @brief  Get the source of SCOUT output.
  * @param  None
  * @retval Source of SCOUT output
  *   The value returned can be one of the following values:
  *   CG_SCOUT_SRC_FSYS, CG_SCOUT_SRC_PHIT0
  *   CG_SCOUT_SRC_HALF_FSYS or CG_SCOUT_SRC_UNKNOWN
  */
CG_SCOUTSrc CG_GetSCOUTSrc(void)
{
    uint32_t tmp = 0U;
    CG_SCOUTSrc source = CG_SCOUT_SRC_UNKNOWN;
    tmp = TSB_CG->SYSCR & (~CG_SCOUT_MASK);

    switch (tmp) {
    case SCOUT_SRC_HALF_FSYS:
        source = CG_SCOUT_SRC_HALF_FSYS;
        break;
    case SCOUT_SRC_FSYS:
        source = CG_SCOUT_SRC_FSYS;
        break;
    case SCOUT_SRC_PHIT0:
        source = CG_SCOUT_SRC_PHIT0;
        break;
    default:
        /* Do nothing */
        break;
    }

    return source;
}

/**
  * @brief  Set the warm up time 
  * @param  Source: Select source of warm-up counter
  *   This parameter can be one of the following values:
  *   CG_WARM_UP_SRC_OSC_EXT or CG_WARM_UP_SRC_OSC_INT
  *   Warm-up function is not necessary when using stable external clock.
  * @param  Time: Set count time for warm-up timer
  * @retval None
  */
void CG_SetWarmUpTime(CG_WarmUpSrc Source, uint16_t Time)
{
    uint32_t tmp = 0U;
    uint32_t regval = TSB_CG->OSCCR;

    /* Check the parameters */
    assert_param(IS_CG_WARM_UP_SRC(Source));

    regval &= CG_WUP_TIME_MASK;
    regval |= CG_WUP_COUNTER_MASK;

    switch (Source) {
    case CG_WARM_UP_SRC_OSC_EXT:
        /* Check the parameters */
        assert_param(IS_CG_WARM_UP_TIME(Time));
        tmp = Time;
        /*Round lower 4 bit off, set the value to CGOSCCR<WUODR[11:0]> */
        tmp = tmp >> 4U;
        tmp = tmp << 20U;
        regval |= tmp;
        regval |= WARM_UP_SEL_OSC_EXT;
        break;
    case CG_WARM_UP_SRC_OSC_INT:
        /* Check the parameters */
        assert_param(IS_CG_WARM_UP_TIME(Time));
        tmp = Time;
        /*Round lower 4 bit off, set the value to CGOSCCR<WUODR[11:0]> */
        tmp = tmp >> 4U;
        tmp = tmp << 20U;
        regval |= tmp;
        regval |= WARM_UP_SEL_OSC_INT;
        break;

    default:
        /* Do nothing */
        break;
    }

    TSB_CG->OSCCR = regval;
}

/**
  * @brief  Start operation of warm up timer for oscillator.
  * @param  None
  * @retval None
  */
void CG_StartWarmUp(void)
{
    TSB_CG_OSCCR_WUEON = 1U;
}

/**
  * @brief Check whether warm up is completed or not.
  * @param  None
  * @retval The state of warm-up
  *   The value returned can be one of the following values:
  *   DONE or BUSY
  */
WorkState CG_GetWarmUpState(void)
{
    WorkState state = BUSY;

    if (TSB_CG_OSCCR_WUEF == 0U) {
        state = DONE;
    } else {
        /* Do nothing */
    }

    return state;
}

/**
  * @brief  Set PLL multiplying value
  * @param  NewValue: PLL multiplying value
  *   This parameter can be one of the following values:
  *   CG_FPLL_MULTIPLY_8 or CG_FPLL_MULTIPLY_16
  * @retval Success or not
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetFPLLValue(CG_FpllValue NewValue)
{
    Result retval = ERROR;
    FunctionalState pllon = DISABLE;
    CG_FoscSrc fosc_src = CG_FOSC_OSC_INT;

    /* Check the parameters */
    assert_param(IS_CG_FPLL_VALUE(NewValue));

    fosc_src = CG_GetFoscSrc();
    pllon = CG_GetPLLState();
    if ((fosc_src == CG_FOSC_OSC_INT) || (pllon == ENABLE)) {
        /*  When using internal high-speed oscillator (IHOSC) as system clock, do not use PLL multiplying */
        retval = ERROR;
    } else {
        if (NewValue == CG_FPLL_MULTIPLY_8) {
            TSB_CG->PLLSEL = FPLL_MULTIPLY_8_VALUE;
            retval = SUCCESS;
        } else {
            if (NewValue == CG_FPLL_MULTIPLY_16) {
                TSB_CG->PLLSEL = FPLL_MULTIPLY_16_VALUE;
                retval = SUCCESS;
            } else {
                retval = ERROR;
            }
        }
    }

    return retval;
}

/**
  * @brief  Get the value of PLL setting
  * @param  None
  * @retval Get the value of PLL setting.
  *   The value returned can be one of the following values:
  *   CG_FPLL_MULTIPLY_8 ,  CG_FPLL_MULTIPLY_16 or
  *   CG_FPLL_MULTIPLY_UNKNOWN
  */
CG_FpllValue CG_GetFPLLValue(void)
{
    CG_FpllValue retval = CG_FPLL_MULTIPLY_UNKNOWN;
    uint32_t pllsel = TSB_CG->PLLSEL;

    pllsel &= CG_PLLSET_VALUE_MASK;

    switch (pllsel) {
    case FPLL_MULTIPLY_8_VALUE:
        retval = CG_FPLL_MULTIPLY_8;
        break;
    case FPLL_MULTIPLY_16_VALUE:
        retval = CG_FPLL_MULTIPLY_16;
        break;
    default:
        /* Do nothing */
        break;
    }

    return retval;
}

/**
  * @brief  Enable PLL or disable it.
  * @param  NewState: New state of PLL
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE
  * @retval Success or not
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetPLL(FunctionalState NewState)
{
    Result retval = ERROR;
    CG_FcSrc fcsrc = CG_FC_SRC_QUARTER_FPLL;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        TSB_CG_OSCCR_PLLON = 1U;
        retval = SUCCESS;
    } else {
        fcsrc = CG_GetFcSrc();
        if (fcsrc == CG_FC_SRC_FOSC) {  /* PLL is not used. So it can be shut off */
            /* Set register to disable PLL */
            TSB_CG_OSCCR_PLLON = 0U;
            retval = SUCCESS;
        } else {                /*fcsrc == CG_FC_SRC_QUARTER_FPLL. PLL is in use, so disabling it should be invalid */
            /* Do nothing */
        }
    }

    return retval;
}

/**
  * @brief  Get the status of PLL operation
  * @param  None
  * @retval Run or stop
  *   The value returned can be one of the following values:
  *   ENABLE or DISABLE
  */
FunctionalState CG_GetPLLState(void)
{
    FunctionalState pllstate = DISABLE;

    if (TSB_CG_OSCCR_PLLON == 1U) {
        pllstate = ENABLE;
    } else {
        /* Do nothing */
    }

    return pllstate;
}

/**
  * @brief  Enable or disable high-speed oscillator (fosc)
  * @param  Source: Select clock source for fosc
  *   This parameter can be one of the following values:
  *   CG_FOSC_OSC_EXT or CG_FOSC_OSC_INT
  * @param  NewState: oscillator is enabled or disabled
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE
  * @retval Success or failure
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetFosc(CG_FoscSrc Source, FunctionalState NewState)
{
    CG_FoscSrc fosc_src = CG_FOSC_OSC_INT;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_CG_FOSC_STATE(Source));

    switch (Source) {
    case CG_FOSC_OSC_EXT:
        if (NewState == ENABLE) {
            /* Enable external high-speed oscillator */
            TSB_CG_OSCCR_XEN1 = 1U;
            /*Selects external high-speed oscillator */
            TSB_CG_OSCCR_EHOSCSEL = 1U;
            retval = SUCCESS;
        } else {
            fosc_src = CG_GetFoscSrc();
            if (fosc_src == CG_FOSC_OSC_EXT) {
                /* external oscillator is in  use, so it can't be disabled */
                retval = ERROR;
            } else {
                /* Disable external high-speed oscillator */
                TSB_CG_OSCCR_XEN1 = 0U;
                retval = SUCCESS;
            }
        }

        break;
    case CG_FOSC_OSC_INT:
        if (NewState == ENABLE) {
            /* Enable internal high-speed oscillator */
            TSB_CG_OSCCR_XEN2 = 1U;
            retval = SUCCESS;
        } else {
            fosc_src = CG_GetFoscSrc();
            if (fosc_src == CG_FOSC_OSC_INT) {
                /* internal high-speed oscillator is in  use, so it can't be disabled */
                retval = ERROR;
            } else {
                /* Disable internal high-speed oscillator */
                TSB_CG_OSCCR_XEN2 = 0U;
                retval = SUCCESS;
            }
        }
        break;
    default:
        /* Do nothing */
        break;
    }

    return retval;
}

/**
  * @brief  Set the source of high-speed oscillator (fosc)
  * @param  Source: Select clock source for fosc
  *   This parameter can be one of the following values:
  *   CG_FOSC_OSC_EXT , CG_FOSC_CLKIN_EXT or CG_FOSC_OSC_INT
  * @retval None
  */
void CG_SetFoscSrc(CG_FoscSrc Source)
{
    /* Check the parameters */
    assert_param(IS_CG_FOSC_SRC(Source));

    if (Source == CG_FOSC_OSC_INT) {
        /*Selects internal high-speed oscillator */
        TSB_CG_OSCCR_OSCSEL = 0U;
    } else {
        if (Source == CG_FOSC_OSC_EXT) {
            /*Selects external high-speed oscillator */
            TSB_CG_OSCCR_EHOSCSEL = 1U;
            /*Selects external high-speed oscillator */
            TSB_CG_OSCCR_OSCSEL = 1U;
        } else {
            /*Selects an external clock input */
            TSB_CG_OSCCR_EHOSCSEL = 0U;
            /*Selects external high-speed oscillator */
            TSB_CG_OSCCR_OSCSEL = 1U;
        }
    }
}

/**
  * @brief  Get the source of high-speed oscillator (fosc)
  * @param  None
  * @retval Source of fosc
  *   The value returned can be one of the following values:
  *   CG_FOSC_OSC_EXT , CG_FOSC_CLKIN_EXT or CG_FOSC_OSC_INT
  */
CG_FoscSrc CG_GetFoscSrc(void)
{
    CG_FoscSrc fosc_src = CG_FOSC_CLKIN_EXT;

    if (TSB_CG_OSCCR_OSCSEL == 0U) {
        fosc_src = CG_FOSC_OSC_INT;
    } else {
        if (TSB_CG_OSCCR_EHOSCSEL == 1U) {
            fosc_src = CG_FOSC_OSC_EXT;
        } else {
            /* Do nothing */
        }
    }

    return fosc_src;
}

/**
  * @brief  Get the state of high-speed oscillator (fosc)
  * @param  Source: Select fosc source
  *   This parameter can be one of the following values:
  *   CG_FOSC_OSC_EXT or CG_FOSC_OSC_INT
  * @retval State of fosc
  *   The value returned can be one of the following values:
  *   ENABLE or DISABLE
  */
FunctionalState CG_GetFoscState(CG_FoscSrc Source)
{
    FunctionalState state = DISABLE;

    /* Check the parameters */
    assert_param(IS_CG_FOSC_STATE(Source));

    if (Source == CG_FOSC_OSC_EXT) {
        if (TSB_CG_OSCCR_XEN1 == 1U) {
            state = ENABLE;
        } else {
            /* Do nothing */
        }
    } else if (TSB_CG_OSCCR_XEN2 == 1U) {
        state = ENABLE;
    } else {
        /* Do nothing */
    }

    return state;
}


/**
  * @brief  Set to the specified low-power mode
  * @param  Low power mode
  *   The value can be one of the following values:
  *   CG_STBY_MODE_STOP1, CG_STBY_MODE_IDLE, CG_STBY_MODE_STOP2
  * @retval None
  */
void CG_SetSTBYMode(CG_STBYMode Mode)
{
    uint32_t regval = TSB_CG->STBYCR;

    /* Check the parameter */
    assert_param(IS_CG_STBY_MODE(Mode));

    regval &= CG_STBY_MODE_MASK;
    regval |= (uint32_t) Mode;

    TSB_CG->STBYCR = regval;
}

/**
  * @brief  Get the low-power consumption mode
  * @param  None
  * @retval Low power mode
  *   The value returned can be one of the following values:
  *   CG_STBY_MODE_STOP1, CG_STBY_MODE_IDLE, 
  *   CG_STBY_MODE_STOP2, CG_STBY_MODE_UNKNOWN
  */
CG_STBYMode CG_GetSTBYMode(void)
{
    CG_STBYMode stby_mode = CG_STBY_MODE_UNKNOWN;
    uint8_t regval = (uint8_t) (TSB_CG->STBYCR & (~CG_STBY_MODE_MASK));

    stby_mode = numToSTBYMode_table[regval];

    return stby_mode;
}

/**
  * @brief  Set pin status in stop1 mode
  * @param  NewState: enable or disable
  *   This parameter can be one of the following values:
  *   ENABLE or DISABLE
  * @retval None
  */
void CG_SetPinStateInStop1Mode(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        TSB_CG_STBYCR_DRVE = 1U;
    } else {
        TSB_CG_STBYCR_DRVE = 0U;
    }
}

/**
  * @brief  Get pin status in stop1 mode
  * @param  None
  * @retval State of pin in stop mode
  *   The value returned can be one of the following values:
  *   DISABLE or ENABLE
  */
FunctionalState CG_GetPinStateInStop1Mode(void)
{
    FunctionalState state = DISABLE;

    if (TSB_CG_STBYCR_DRVE == 1U) {
        /* Pin status in stop mode is active */
        state = ENABLE;
    } else {
        /* Do nothing */
    }
    return state;
}

/**
  * @brief  Enables or disables to keep IO control signal in stop2 mode
  * @param  NewState: enable or disable
  *   This parameter can be one of the following values:
  *   ENABLE or DISABLE
  * @retval None
  */
void CG_SetPortKeepInStop2Mode(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        TSB_CG_STBYCR_PTKEEP = 1U;
    } else {
        TSB_CG_STBYCR_PTKEEP = 0U;
    }
}

/**
  * @brief  Get the status of  IO control signal in stop2 mode
  * @param  None
  * @retval State of IO control signal in stop2 mode
  *   The value returned can be one of the following values:
  *   DISABLE or ENABLE
  */
FunctionalState CG_GetPortKeepInStop2Mode(void)
{
    FunctionalState state = DISABLE;

    if (TSB_CG_STBYCR_PTKEEP == 1U) {
        /* Pin status in stop mode is active */
        state = ENABLE;
    } else {
        /* Do nothing */
    }
    return state;
}

/**
  * @brief  Set the source of fc
  * @param  Source:  The source of fc
  *   This parameter can be one of the following values:
  *   CG_FC_SRC_FOSC or CG_FC_SRC_QUARTER_FPLL
  * @retval success or failure
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetFcSrc(CG_FcSrc Source)
{
    Result retval = ERROR;
    FunctionalState fosc_on = DISABLE;
    FunctionalState pllon = DISABLE;
    CG_FoscSrc fosc_src = CG_FOSC_OSC_EXT;

    /* Check the parameters */
    assert_param(IS_CG_FC_SRC(Source));

    if (Source == CG_FC_SRC_FOSC) {
        fosc_src = CG_GetFoscSrc();
        switch (fosc_src) {
        case CG_FOSC_OSC_EXT:
            fosc_on = CG_GetFoscState(CG_FOSC_OSC_EXT);
            if (fosc_on == ENABLE) {
                TSB_CG_PLLSEL_PLLSEL = 0U;
                retval = SUCCESS;
            } else {
                /* Do nothing */
            }
            break;
        case CG_FOSC_OSC_INT:
            fosc_on = CG_GetFoscState(CG_FOSC_OSC_INT);
            if (fosc_on == ENABLE) {
                TSB_CG_PLLSEL_PLLSEL = 0U;
                retval = SUCCESS;
            } else {
                /* Do nothing */
            }
            break;
        case CG_FOSC_CLKIN_EXT:
            TSB_CG_PLLSEL_PLLSEL = 0U;
            retval = SUCCESS;
            break;
        default:
            /* Do nothing */
            break;
        }

    } else {
        pllon = CG_GetPLLState();
        if (pllon == ENABLE) {
            TSB_CG_PLLSEL_PLLSEL = 1U;
            retval = SUCCESS;
        } else {
            /* Do nothing */
        }
    }

    return retval;
}

/**
  * @brief  Get the source of fc
  * @param  None
  * @retval The source of fc
  *   The value returned can be one of the following values:
  *   CG_FC_SRC_FOSC or CG_FC_SRC_QUARTER_FPLL
  */
CG_FcSrc CG_GetFcSrc(void)
{
    CG_FcSrc fcsrc = CG_FC_SRC_FOSC;

    if (TSB_CG_PLLSEL_PLLSEL == 1U) {
        fcsrc = CG_FC_SRC_QUARTER_FPLL;
    } else {
        /* Do nothing */
    }

    return fcsrc;
}

/**
  * @brief  Set the source of high-resolution PPG clock (ftmrd)
  * @param  FtmrdSrc: Select clock source for ftmrd
  *   This parameter can be one of the following values:
  *   CG_FTMRD_SRC_FPLL , CG_FTMRD_SRC_HALF_FPLL  or
  *   CG_FTMRD_SRC_QUARTER_FPLL 
  * @retval None
  */
void CG_SetFtmrdSrc(CG_FtmrdSrc FtmrdSrc)
{
    uint32_t pwmgear = ~CG_FTMRD_GEAR_MASK;
    uint32_t regval = TSB_CG->PWMGEAR;

    /* Check the parameters */
    assert_param(IS_CG_FTMRD_SRC(FtmrdSrc));

    /* Set the value of fgear */
    switch (FtmrdSrc) {
    case CG_FTMRD_SRC_FPLL:
        pwmgear = FTMRD_GEAR_1_1;
        break;
    case CG_FTMRD_SRC_HALF_FPLL:
        pwmgear = FTMRD_GEAR_1_2;
        break;
    case CG_FTMRD_SRC_QUARTER_FPLL:
        pwmgear = FTMRD_GEAR_1_4;
        break;
    default:
        /* Do nothing */
        break;
    }

    regval &= CG_FTMRD_GEAR_MASK;
    regval |= pwmgear;
    TSB_CG->PWMGEAR = regval;
}

/**
  * @brief  Get the source of high-resolution PPG clock (ftmrd)
  * @param  None
  * @retval Source of ftmrd
  *   The value returned can be one of the following values:
  *   CG_FTMRD_SRC_FPLL , CG_FTMRD_SRC_HALF_FPLL 
  *   CG_FTMRD_SRC_QUARTER_FPLL or  CG_FTMRD_SRC_UNKNOWN
  */
CG_FtmrdSrc CG_GetFtmrdSrc(void)
{
    CG_FtmrdSrc source = CG_FTMRD_SRC_UNKNOWN;
    uint32_t pwmgear = TSB_CG->PWMGEAR;
    pwmgear &= (~CG_FTMRD_GEAR_MASK);

    switch (pwmgear) {
    case FTMRD_GEAR_1_1:
        source = CG_FTMRD_SRC_FPLL;
        break;
    case FTMRD_GEAR_1_2:
        source = CG_FTMRD_SRC_HALF_FPLL;
        break;
    case FTMRD_GEAR_1_4:
        source = CG_FTMRD_SRC_QUARTER_FPLL;
        break;
    default:
        /* Do nothing */
        break;
    }

    return source;
}

/**
  * @brief  Enable or disable to provide TMRD clock
  * @param  NewState: New state of PLL
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE
  * @retval None
  */
void CG_SetTMRDClk(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        TSB_CG_PWMGEAR_TMRDCLKEN = 1U;
    } else {
        TSB_CG_PWMGEAR_TMRDCLKEN = 0U;
    }
}

/**
  * @brief  Get the state of TMRD clock
  * @param  None
  * @retval state of TMRD clock
  *   The value returned can be one of the following values:
  *   ENABLE or DISABLE
  */
FunctionalState CG_GetTMRDClkState(void)
{
    FunctionalState state = DISABLE;

    if (TSB_CG_PWMGEAR_TMRDCLKEN == 1U) {
        state = ENABLE;
    } else {
        /* Do nothing */
    }

    return state;
}

/**
  * @brief  Enable or disable to protect CG registers
  * @param  NewState: New state of PLL
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE
  * @retval None
  */
void CG_SetProtectCtrl(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        TSB_CG->PROTECT = CG_PROTECT_SET;
    } else {
        TSB_CG->PROTECT = CG_PROTECT_CLEAR;
    }
}

/**
  * @brief  Setup the INT source for releasing low power mode.
  * @param  INTSource: Select the release INT source
  *   This parameter can be one of the following values:
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2, CG_INT_SRC_3,
  *   CG_INT_SRC_4, CG_INT_SRC_5, CG_INT_SRC_6, CG_INT_SRC_7,
  *   CG_INT_SRC_PHT_00, CG_INT_SRC_PHT_01,
  *   CG_INT_SRC_PHT_10, CG_INT_SRC_PHT_11,
  *   CG_INT_SRC_PHT_20, CG_INT_SRC_PHT_21,
  *   CG_INT_SRC_PHT_30, CG_INT_SRC_PHT_31,
  *   CG_INT_SRC_PHEVRY_0, CG_INT_SRC_PHEVRY_1,
  *   CG_INT_SRC_PHEVRY_2, CG_INT_SRC_PHEVRY_3,
  *   CG_INT_SRC_8, CG_INT_SRC_9, CG_INT_SRC_A, CG_INT_SRC_B
  * @param  ActiveState: select the active state for release trigger
  *   For INTPHT00 to INTPHT31 and INTPHEVRY0 to INTPHEVRY0, 
  *   only CG_INT_ACTIVE_STATE_RISING can be set.
  *   For INT0 to INTB, one of the following values can be set.
  *   CG_INT_ACTIVE_STATE_L, 
  *   CG_INT_ACTIVE_STATE_H, 
  *   CG_INT_ACTIVE_STATE_FALLING, 
  *   CG_INT_ACTIVE_STATE_RISING or 
  *   CG_INT_ACTIVE_STATE_BOTH_EDGES.
  * @param  NewState: Enable or disable this release trigger
  *   This parameter can be one of the following values:
  *   DISABLE or ENABLE
  * @retval None
  */
void CG_SetSTBYReleaseINTSrc(CG_INTSrc INTSource,
                             CG_INTActiveState ActiveState, FunctionalState NewState)
{
    uint32_t num = 0U;
    uint8_t i = 0U;
    uint8_t j = 0U;
    CG_Byte4 regval[6] = { {0U}
    , {0U}
    , {0U}
    , {0U}
    , {0U}
    , {0U}
    };

    /* Check the parameters */
    assert_param(IS_CG_INT_SRC(INTSource));
    assert_param(IS_CG_INT_ACTIVE_STATE(ActiveState));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    num = (uint32_t) INTSource;
    i = (uint8_t) (num / 4U);
    j = (uint8_t) (num % 4U);

    switch (i) {
    case 0U:                   /* IMCGA */
        regval[0].byte4 = TSB_CG->IMCGA;
        regval[0].byte[j] &= 0x8CU;
        regval[0].byte[j] |= ActiveState;
        TSB_CG->IMCGA = regval[0].byte4;
        regval[0].byte[j] |= NewState;
        TSB_CG->IMCGA = regval[0].byte4;
        break;

    case 1U:                   /* IMCGB */
        regval[1].byte4 = TSB_CG->IMCGB;
        regval[1].byte[j] &= 0x8CU;
        regval[1].byte[j] |= ActiveState;
        TSB_CG->IMCGB = regval[1].byte4;
        regval[1].byte[j] |= NewState;
        TSB_CG->IMCGB = regval[1].byte4;
        break;

    case 2U:                   /* IMCGC */
        regval[2].byte4 = TSB_CG->IMCGC;
        regval[2].byte[j] &= 0x8CU;

        ActiveState = CG_INT_ACTIVE_STATE_RISING;
        regval[2].byte[j] |= ActiveState;
        TSB_CG->IMCGC = regval[2].byte4;
        regval[2].byte[j] |= NewState;
        TSB_CG->IMCGC = regval[2].byte4;
        break;

    case 3U:                   /* IMCGD */
        regval[3].byte4 = TSB_CG->IMCGD;
        regval[3].byte[j] &= 0x8CU;

        ActiveState = CG_INT_ACTIVE_STATE_RISING;
        regval[3].byte[j] |= ActiveState;
        TSB_CG->IMCGD = regval[3].byte4;
        regval[3].byte[j] |= NewState;
        TSB_CG->IMCGD = regval[3].byte4;
        break;

    case 4U:                   /* IMCGE */
        regval[4].byte4 = TSB_CG->IMCGE;
        regval[4].byte[j] &= 0x8CU;

        ActiveState = CG_INT_ACTIVE_STATE_RISING;
        regval[4].byte[j] |= ActiveState;
        TSB_CG->IMCGE = regval[4].byte4;
        regval[4].byte[j] |= NewState;
        TSB_CG->IMCGE = regval[4].byte4;
        break;

    case 5U:                   /* IMCGF */
        regval[5].byte4 = TSB_CG->IMCGF;
        regval[5].byte[j] &= 0x8CU;
        regval[5].byte[j] |= ActiveState;
        TSB_CG->IMCGF = regval[5].byte4;
        regval[5].byte[j] |= NewState;
        TSB_CG->IMCGF = regval[5].byte4;
        break;
    default:
        /* Do nothing */
        break;
    }
}

/**
  * @brief  Gets the active state of INT source standby clear request
  * @param  INTSource: Select the release INT source
  *   This parameter can be one of the following values:
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2, CG_INT_SRC_3,
  *   CG_INT_SRC_4, CG_INT_SRC_5, CG_INT_SRC_6, CG_INT_SRC_7,
  *   CG_INT_SRC_PHT_00, CG_INT_SRC_PHT_01,
  *   CG_INT_SRC_PHT_10, CG_INT_SRC_PHT_11,
  *   CG_INT_SRC_PHT_20, CG_INT_SRC_PHT_21,
  *   CG_INT_SRC_PHT_30, CG_INT_SRC_PHT_31,
  *   CG_INT_SRC_PHEVRY_0, CG_INT_SRC_PHEVRY_1,
  *   CG_INT_SRC_PHEVRY_2, CG_INT_SRC_PHEVRY_3,
  *   CG_INT_SRC_8, CG_INT_SRC_9, CG_INT_SRC_A, CG_INT_SRC_B
  * @retval Active state of the input INT
  *   The value returned can be one of the following values:
  *   CG_INT_ACTIVE_STATE_FALLING, CG_INT_ACTIVE_STATE_RISING,
  *   CG_INT_ACTIVE_STATE_BOTH_EDGES or CG_INT_ACTIVE_STATE_INVALID
  */
CG_INTActiveState CG_GetSTBYReleaseINTState(CG_INTSrc INTSource)
{
    CG_INTActiveState int_active_state = CG_INT_ACTIVE_STATE_INVALID;
    uint8_t i = 0U;
    uint8_t j = 0U;
    uint8_t tmp = 0U;
    uint32_t num = 0U;
    CG_Byte4 regval[6] = { {0U}
    , {0U}
    , {0U}
    , {0U}
    , {0U}
    , {0U}
    };

    /* Check the parameters */
    assert_param(IS_CG_INT_SRC(INTSource));

    regval[0].byte4 = TSB_CG->IMCGA;
    regval[1].byte4 = TSB_CG->IMCGB;
    regval[2].byte4 = TSB_CG->IMCGC;
    regval[3].byte4 = TSB_CG->IMCGD;
    regval[4].byte4 = TSB_CG->IMCGE;
    regval[5].byte4 = TSB_CG->IMCGF;

    num = (uint32_t) INTSource;
    i = (uint8_t) (num / 4U);
    j = (uint8_t) (num % 4U);
    tmp = regval[i].byte[j];
    tmp &= 0x0CU;

    switch (tmp) {
    case 0x04U:
        int_active_state = CG_INT_ACTIVE_STATE_RISING;
        break;
    case 0x08U:
        int_active_state = CG_INT_ACTIVE_STATE_FALLING;
        break;
    case 0x0CU:
        int_active_state = CG_INT_ACTIVE_STATE_BOTH_EDGES;
        break;
    default:
        /* Do nothing */
        break;
    }

    return (int_active_state);
}

/**
  * @brief  Clears the input INT request.
  * @param  INTSource: Select the release INT source
  *   This parameter can be one of the following values:
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2, CG_INT_SRC_3,
  *   CG_INT_SRC_4, CG_INT_SRC_5, CG_INT_SRC_6, CG_INT_SRC_7,
  *   CG_INT_SRC_PHT_00, CG_INT_SRC_PHT_01,
  *   CG_INT_SRC_PHT_10, CG_INT_SRC_PHT_11,
  *   CG_INT_SRC_PHT_20, CG_INT_SRC_PHT_21,
  *   CG_INT_SRC_PHT_30, CG_INT_SRC_PHT_31,
  *   CG_INT_SRC_PHEVRY_0, CG_INT_SRC_PHEVRY_1,
  *   CG_INT_SRC_PHEVRY_2, CG_INT_SRC_PHEVRY_3,
  *   CG_INT_SRC_8, CG_INT_SRC_9, CG_INT_SRC_A, CG_INT_SRC_B
  * @retval None
  */
void CG_ClearINTReq(CG_INTSrc INTSource)
{
    uint32_t regval = INTSource;

    /* Check the parameters */
    assert_param(IS_CG_INT_SRC(INTSource));

    TSB_CG->ICRCG = regval;
}

/**
  * @brief  Get the NMI flag that shows who triggered NMI.
  * @param  None
  * @retval NMI flag
  */
CG_NMIFactor CG_GetNMIFlag(void)
{
    CG_NMIFactor cg_nmi_factor = { 0U };

    cg_nmi_factor.All = TSB_CG->NMIFLG & (~CG_NMIFLG_MASK);

    return cg_nmi_factor;
}

/**
  * @brief  Get the type of reset reason and clear the reset flag.
  * @param  None
  * @retval Reset flag
  */
CG_ResetFlag CG_GetResetFlag(void)
{
    CG_ResetFlag reset_flag = { 0U };

    reset_flag.All = TSB_CG->RSTFLG & (~CG_RESET_FLAG_MASK);
    TSB_CG->RSTFLG = 0U;

    return reset_flag;
}

/** @} */
/* End of group CG_Exported_Functions */

/** @} */
/* End of group CG */

/** @} */
/* End of group TX03_Periph_Driver */
#endif                          /* defined(__TMPM341_CG_H) */
