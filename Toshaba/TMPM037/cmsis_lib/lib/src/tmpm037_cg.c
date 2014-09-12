/**
 *******************************************************************************
 * @file    tmpm037_cg.c
 * @brief   This file provides API functions for CG driver 
 * @version V2.0.2.2
 * @date    2014/05/06
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm037_cg.h"

#if defined(__TMPM037_CG_H)
/** @addtogroup TX00_Periph_Driver
  * @{
  */

/** @defgroup CG
  * @brief CG driver modules
  * @{
  */

/** @defgroup CG_Private_Defines
  * @{
  */

#define CG_SYSCR_FCSTOP_CLEAR                ((uint32_t)0xFFEFFFFF)
#define CG_SYSCR_FCSTOP_SET                  ((uint32_t)0x00100000)

#define ADC_MOD0_ADBFN_MASK                  ((uint32_t)0x00000040)
#define ADC_MOD2_ADBFHP_MASK                 ((uint32_t)0x00000040)

#define CG_FC_GEAR_MASK                      ((uint32_t)0xFFFFFFF8)
#define CG_PRCK_MASK                         ((uint32_t)0xFFFFF8FF)
#define CG_SCOUT_MASK                        ((uint32_t)0xFFFEFFFF)

#define CG_WUP_START_SET                     ((uint32_t)0x00000001)
#define CG_WUEF_VALUE_MASK                   ((uint32_t)0x00000002)
#define CG_OSCCR_XEN1_SET                    ((uint32_t)0x00000100)
#define CG_OSCCR_XEN1_CLEAR                  ((uint32_t)0xFFFFFEFF)
#define CG_OSCCR_XEN2_SET                    ((uint32_t)0x00010000)
#define CG_OSCCR_XEN2_CLEAR                  ((uint32_t)0xFFFEFFFF)

#define CG_OSCCR_EHOSCSEL_SET                ((uint32_t)0x00040000)
#define CG_OSCCR_EHOSCSEL_CLEAR              ((uint32_t)0xFFFBFFFF)
#define CG_OSCCR_OSCSEL_SET                  ((uint32_t)0x00020000)
#define CG_OSCCR_OSCSEL_CLEAR                ((uint32_t)0xFFFDFFFF)
#define CG_OSCCR_OSCF_SET                    ((uint32_t)0x00000200)
#define CG_OSCCR_WUODR_MASK                  ((uint32_t)0x0000FFF0)

#define CG_OSCCR_PLLON_SET                   ((uint32_t)0x00000004)
#define CG_OSCCR_PLLON_CLEAR                 ((uint32_t)0xFFFFFFFB)
#define CG_PLLSEL_PLLSEL_SET                 ((uint32_t)0x00000001)
#define CG_PLLSEL_PLLSEL_CLEAR               ((uint32_t)0xFFFFFFFE)
#define CG_PLLSEL_PLLST_SET                  ((uint32_t)0x00040000)

#define CG_PLLSET_VALUE_MASK                 ((uint32_t)0x0000FFFE)
#define CG_PLLSEL_PLLSET_MASK                ((uint32_t)0xFFFF0001)

#define CG_STBY_MODE_MASK                    ((uint32_t)0xFFFFFFF8)
#define CG_NMIFLG_MASK                       ((uint32_t)0xFFFFFFF2)
#define CG_RESET_FLAG_MASK                   ((uint32_t)0xFFFFFFA8)

#define CG_FPSEL_MASK                        ((uint32_t)0xFFFFEFFF)

#define FC_GEAR_1_1                          ((uint32_t)0x00000000)
#define FC_GEAR_1_2                          ((uint32_t)0x00000004)
#define FC_GEAR_1_4                          ((uint32_t)0x00000005)
#define FC_GEAR_1_8                          ((uint32_t)0x00000006)
#define FC_GEAR_1_16                         ((uint32_t)0x00000007)

#define WARM_UP_SEL_OSC_INT_HIGH             ((uint32_t)0x00000000)
#define WARM_UP_SEL_OSC_EXT_HIGH             ((uint32_t)0x00080000)

#define CG_PROTECT_SET                       ((uint32_t)0x000000C1)
#define CG_PROTECT_CLEAR                     ((uint32_t)0x0000003E)

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
    CG_STBY_MODE_UNKNOWN,
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
    if (PhiT0_src == CG_PHIT0_SRC_FC) { /* phiT0 src == fc , max divider: 32 */
        /* Check the parameters */
        assert_param(IS_CG_FC_DIDIDE_LEVEL(DividePhiT0FromFc));

        fprclk = (uint32_t) DividePhiT0FromFc;
        regval &= CG_PRCK_MASK;
        fprclk <<= 8U;
        regval |= fprclk;
        TSB_CG->SYSCR = regval;
        retval = SUCCESS;
    } else {                    /* phiT0 src == fgear, max divider: 512 */
        /* Check the parameters */
        assert_param(IS_CG_DIVIDE_FC_LEVEL(DividePhiT0FromFc));

        fgear = CG_GetFgearLevel();
        if (fgear != CG_DIVIDE_UNKNOWN) {
            if (DividePhiT0FromFc >= fgear) {
                fprclk = (uint32_t) DividePhiT0FromFc - (uint32_t) fgear;
                if (fprclk <= CG_DIVIDE_32) {
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
  * @brief  Set the warm up time 
  * @param  Source: Select source of warm-up counter
  *   This parameter can be one of the following values:
  *   CG_WARM_UP_SRC_OSC_INT_HIGH, CG_WARM_UP_SRC_OSC_EXT_HIGH.
  *   Warm-up function is not necessary when using stable external clock.
  * @param  Time: Set number of warm-up cycle. It is between 0x0000 and 0xFFFF.
  * @retval None
  */
void CG_SetWarmUpTime(CG_WarmUpSrc Source, uint16_t Time)
{
    uint32_t wuodr = 0U;
    uint32_t regval = TSB_CG->OSCCR;

    /* Check the parameters */
    assert_param(IS_CG_WARM_UP_SRC(Source));

    /* Get high 12 bits of warm-up time */
    wuodr = (((uint32_t) Time) & CG_OSCCR_WUODR_MASK) << 16U;

    switch (Source) {
    case CG_WARM_UP_SRC_OSC_INT_HIGH:
        regval |= wuodr;
        regval |= WARM_UP_SEL_OSC_INT_HIGH;
        break;
    case CG_WARM_UP_SRC_OSC_EXT_HIGH:
        regval |= wuodr;
        regval |= WARM_UP_SEL_OSC_EXT_HIGH;
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
    uint32_t regval = TSB_CG->OSCCR;
    regval |= CG_WUP_START_SET;
    TSB_CG->OSCCR = regval;
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
    uint32_t wuef = 0U;
    uint32_t regval = TSB_CG->OSCCR;

    wuef = regval & CG_WUEF_VALUE_MASK;
    if (wuef == 0U) {
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
  *   CG_MUL_2_FPLL
  * @retval Success or not
  *   The value returned can be one of the following values:
  *   SUCCESS or ERROR
  */
Result CG_SetFPLLValue(uint32_t NewValue)
{
    Result retval = SUCCESS;

    /* read PLLSEL and clear PLLSET(bit14:0) */
    uint32_t tmp = TSB_CG->PLLSEL & CG_PLLSEL_PLLSET_MASK;

    /* Check the parameters */
    assert_param(IS_CG_FPLL_VALUE(NewValue));

    /* Don't use the PLL when internal high-speed oscillator (IHOSC) is used as system clock */
    /* When PLL is on, don't change the PLL setting value */
    if (CG_FOSC_OSC_INT == CG_GetFoscSrc()) {
        retval = ERROR;
    } else if (ENABLE == CG_GetPLLState()) {
        retval = ERROR;
    } else {
        tmp |= NewValue;
        TSB_CG->PLLSEL = tmp;
    }

    return retval;
}

/**
  * @brief  Get the value of PLL setting
  * @param  None
  * @retval Get the value of PLL setting.  
  *   CG_MUL_2_FPLL or other unknown value
  */
uint32_t CG_GetFPLLValue(void)
{
    uint32_t pllsel = TSB_CG->PLLSEL & CG_PLLSET_VALUE_MASK;

    return pllsel;
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
    uint32_t regval = TSB_CG->OSCCR;
    CG_FcSrc fcsrc = CG_FC_SRC_FPLL;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        regval |= CG_OSCCR_PLLON_SET;
        retval = SUCCESS;
    } else {
        fcsrc = CG_GetFcSrc();
        if (fcsrc == CG_FC_SRC_FOSC) {  /* PLL is not used. So it can be shut off */
            /* Set register to disable PLL */
            regval &= CG_OSCCR_PLLON_CLEAR;
            retval = SUCCESS;
        } else {                /*fcsrc == CG_FC_SRC_FPLL. PLL is in use, so disabling it should be invalid */
            /* Do nothing */
        }
    }
    TSB_CG->OSCCR = regval;
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
    uint32_t regval = TSB_CG->OSCCR;

    regval &= CG_OSCCR_PLLON_SET;
    if (regval == CG_OSCCR_PLLON_SET) {
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
    uint32_t regval = TSB_CG->OSCCR;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_CG_FOSC_STATE(Source));

    switch (Source) {
    case CG_FOSC_OSC_EXT:
        if (NewState == ENABLE) {
            /* Enable external high-speed oscillator */
            regval |= CG_OSCCR_XEN1_SET;
            /*Selects external high-speed oscillator */
            regval |= CG_OSCCR_EHOSCSEL_SET;
            retval = SUCCESS;
        } else {
            fosc_src = CG_GetFoscSrc();
            if (fosc_src == CG_FOSC_OSC_EXT) {
                /* external oscillator is in  use, so it can't be disabled */
                retval = ERROR;
            } else {
                /* Disable external high-speed oscillator */
                regval &= CG_OSCCR_XEN1_CLEAR;
                retval = SUCCESS;
            }
        }

        break;
    case CG_FOSC_OSC_INT:
        if (NewState == ENABLE) {
            /* Enable internal high-speed oscillator */
            regval |= CG_OSCCR_XEN2_SET;
            retval = SUCCESS;
        } else {
            fosc_src = CG_GetFoscSrc();
            if (fosc_src == CG_FOSC_OSC_INT) {
                /* internal high-speed oscillator is in  use, so it can't be disabled */
                retval = ERROR;
            } else {
                /* Disable internal high-speed oscillator */
                regval &= CG_OSCCR_XEN2_CLEAR;
                retval = SUCCESS;
            }
        }
        break;
    default:
        /* Do nothing */
        break;
    }
    TSB_CG->OSCCR = regval;
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
        TSB_CG->OSCCR &= CG_OSCCR_OSCSEL_CLEAR;
    } else {
        if (Source == CG_FOSC_OSC_EXT) {
            /*Selects external high-speed oscillator */
            TSB_CG->OSCCR |= CG_OSCCR_EHOSCSEL_SET;
            /*Selects external high-speed oscillator */
            TSB_CG->OSCCR |= CG_OSCCR_OSCSEL_SET;
        } else {
            /*Selects an external clock input */
            TSB_CG->OSCCR &= CG_OSCCR_EHOSCSEL_CLEAR;
            /*Selects external high-speed oscillator */
            TSB_CG->OSCCR |= CG_OSCCR_OSCSEL_SET;
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
    uint32_t regval = TSB_CG->OSCCR;
    uint32_t oscf = 0U;
    uint32_t ehoscsel = 0U;
    CG_FoscSrc fosc_src = CG_FOSC_CLKIN_EXT;

    oscf = regval & CG_OSCCR_OSCF_SET;
    ehoscsel = regval & CG_OSCCR_EHOSCSEL_SET;
    if (oscf == 0U) {
        fosc_src = CG_FOSC_OSC_INT;
    } else {
        if (ehoscsel == CG_OSCCR_EHOSCSEL_SET) {
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
    uint32_t regval = TSB_CG->OSCCR;
    uint32_t xen1 = 0U;
    uint32_t xen2 = 0U;
    FunctionalState state = DISABLE;

    /* Check the parameters */
    assert_param(IS_CG_FOSC_STATE(Source));

    xen1 = regval & CG_OSCCR_XEN1_SET;
    xen2 = regval & CG_OSCCR_XEN2_SET;

    if (Source == CG_FOSC_OSC_EXT) {
        if (xen1 == CG_OSCCR_XEN1_SET) {
            state = ENABLE;
        } else {
            /* Do nothing */
        }
    } else if (xen2 == CG_OSCCR_XEN2_SET) {
        state = ENABLE;
    } else {
        /* Do nothing */
    }

    return state;
}


/**
  * @brief  Set the specified low-power mode
  * @param  Low power mode
  *   The value can be one of the following values:
  *   CG_STBY_MODE_STOP1, CG_STBY_MODE_IDLE.
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
  *   CG_STBY_MODE_STOP1, CG_STBY_MODE_IDLE, CG_STBY_MODE_UNKNOWN.
  */
CG_STBYMode CG_GetSTBYMode(void)
{
    CG_STBYMode stby_mode = CG_STBY_MODE_UNKNOWN;
    uint8_t regval = (uint8_t) (TSB_CG->STBYCR & (~CG_STBY_MODE_MASK));

    stby_mode = numToSTBYMode_table[regval];

    return stby_mode;
}

/**
  * @brief  Set the source of fc
  * @param  Source:  The source of fc
  *   This parameter can be one of the following values:
  *   CG_FC_SRC_FOSC or CG_FC_SRC_FPLL
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
    uint32_t regval = TSB_CG->PLLSEL;

    /* Check the parameters */
    assert_param(IS_CG_FC_SRC(Source));

    if (Source == CG_FC_SRC_FOSC) {
        fosc_src = CG_GetFoscSrc();
        switch (fosc_src) {
        case CG_FOSC_OSC_EXT:
            fosc_on = CG_GetFoscState(CG_FOSC_OSC_EXT);
            if (fosc_on == ENABLE) {
                regval &= CG_PLLSEL_PLLSEL_CLEAR;
                retval = SUCCESS;
            } else {
                /* Do nothing */
            }
            break;
        case CG_FOSC_OSC_INT:
            fosc_on = CG_GetFoscState(CG_FOSC_OSC_INT);
            if (fosc_on == ENABLE) {
                regval &= CG_PLLSEL_PLLSEL_CLEAR;
                retval = SUCCESS;
            } else {
                /* Do nothing */
            }
            break;
        case CG_FOSC_CLKIN_EXT:
            regval &= CG_PLLSEL_PLLSEL_CLEAR;
            retval = SUCCESS;
            break;
        default:
            /* Do nothing */
            break;
        }

    } else {
        pllon = CG_GetPLLState();
        if (pllon == ENABLE) {
            regval |= CG_PLLSEL_PLLSEL_SET;
            retval = SUCCESS;
        } else {
            /* Do nothing */
        }
    }
    TSB_CG->PLLSEL = regval;
    return retval;
}

/**
  * @brief  Get the source of fc
  * @param  None
  * @retval The source of fc
  *   The value returned can be one of the following values:
  *   CG_FC_SRC_FOSC or CG_FC_SRC_FPLL
  */
CG_FcSrc CG_GetFcSrc(void)
{
    uint32_t regval = TSB_CG->PLLSEL;
    CG_FcSrc fcsrc = CG_FC_SRC_FOSC;

    regval &= CG_PLLSEL_PLLST_SET;
    if (regval == CG_PLLSEL_PLLST_SET) {
        fcsrc = CG_FC_SRC_FPLL;
    } else {
        /* Do nothing */
    }

    return fcsrc;
}

/**
  * @brief  Enable or disable to protect CG registers
  * @param  NewState: New state of the CG protect register
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
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2,
  *   CG_INT_SRC_3, CG_INT_SRC_4, CG_INT_SRC_5.
  * @param  ActiveState: select the active state for release trigger
  *   This parameter can be one of the following values:
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
    CG_Byte4 regval = { 0U };

    /* Check the parameters */
    assert_param(IS_CG_INT_SRC(INTSource));
    assert_param(IS_CG_INT_ACTIVE_STATE(ActiveState));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    num = (uint32_t) INTSource;
    i = (uint8_t) (num / 4U);
    j = (uint8_t) (num % 4U);

    switch (i) {
    case 0U:                   /* IMCGA */
        regval.byte4 = TSB_CG->IMCGA;
        regval.byte[j] &= 0x8CU;
        regval.byte[j] |= ActiveState;
        TSB_CG->IMCGA = regval.byte4;
        regval.byte[j] |= NewState;
        TSB_CG->IMCGA = regval.byte4;
        break;
    case 1U:                   /* IMCGB */
        regval.byte4 = TSB_CG->IMCGB;
        regval.byte[j] &= 0x8CU;
        regval.byte[j] |= ActiveState;
        TSB_CG->IMCGB = regval.byte4;
        regval.byte[j] |= NewState;
        TSB_CG->IMCGB = regval.byte4;
        break;
    default:
        /* Do nothing */
        break;
    }
}

/**
  * @brief  Get the active state of INT source standby clear request
  * @param  INTSource: Select the release INT source
  *   This parameter can be one of the following values:  
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2, CG_INT_SRC_3,
  *   CG_INT_SRC_4, CG_INT_SRC_5.
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
    CG_Byte4 regval[2] = { {0U}
    , {0U}
    };

    /* Check the parameters */
    assert_param(IS_CG_INT_SRC(INTSource));

    regval[0].byte4 = TSB_CG->IMCGA;
    regval[1].byte4 = TSB_CG->IMCGB;

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
  *   CG_INT_SRC_0, CG_INT_SRC_1, CG_INT_SRC_2,
  *   CG_INT_SRC_3, CG_INT_SRC_4, CG_INT_SRC_5.
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

/**
  * @brief  Enable or disable supplying clock fsys for ADC.
  * @param  NewState: New state of clock fsys supply setting for ADC.
  *   This parameter can be one of the following values:
  *   ENABLE or DISABLE.
  * @retval None.
  */
void CG_SetADCClkSupply(FunctionalState NewState)
{
    volatile uint32_t tmp = 0U;
    volatile uint32_t tmp1 = 0U;
    uint32_t tmp2 = 0U;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Check ADC is not during conversion */
    do {
        tmp1 = TSB_AD->MOD0 & ADC_MOD0_ADBFN_MASK;
        tmp2 = TSB_AD->MOD2 & ADC_MOD2_ADBFHP_MASK;
        tmp = tmp1 | tmp2;
    }
    while (tmp);

    /* Set CGSYSCR<FCSTOP>  */
    tmp = TSB_CG->SYSCR;
    if (NewState == ENABLE) {
        tmp &= CG_SYSCR_FCSTOP_CLEAR;
    } else {
        tmp |= CG_SYSCR_FCSTOP_SET;
    }
    TSB_CG->SYSCR = tmp;
}

/** @} */
/* End of group CG_Exported_Functions */

/** @} */
/* End of group CG */

/** @} */
/* End of group TX00_Periph_Driver */

#endif                          /* defined(__TMPM037_CG_H) */
