/**************************************************************************//**
 * @file     acmp.c
 * @version  V1.00
 * $Revision: 10 $
 * $Date: 13/12/20 4:14p $
 * @brief    Nano1x2 series Analog Comparator(ACMP) driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "Nano1X2Series.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NANO1X2_Device_Driver NANO1X2 Device Driver
  @{
*/

/** @addtogroup NANO1X2_ACMP_Driver ACMP Driver
  @{
*/


/** @addtogroup NANO1X2_ACMP_EXPORTED_FUNCTIONS ACMP Exported Functions
  @{
*/


/**
  * @brief  This function open and configure comparator parameters
  *
  * @param[in]  Acmp The base address of ACMP module
  * @param[in]  u32ChNum comparator number.
  * @param[in]  u32NegSrc is comparator0 negative input selection.  Including :
  *                  - \ref ACMP_CMPCR_CN0_PIN
  *                  - \ref ACMP_CMPCR_CN0_CRV
  *                  - \ref ACMP_CMPCR_CN0_VREFI
  *                  - \ref ACMP_CMPCR_CN0_AGND
  *             if select ACMP_CMPCR_CN0_CRV can add comparator reference voltage setting.
  *             The formula is:
  *                       comparator reference voltage = AVDD x (1/6 +CRV/24)
  *             The range of CRV  is 0 ~ 15.
  *             Example : u32NegSrc = (ACMP_CMPCR_CN0_CRV | 10)
  *
  * @param[in]  u32HysteresisEn is charge or discharge pin selection. Including :
  *                  - \ref ACMP_CMPCR_CMP_HYSTERSIS_ENABLE
  *                  - \ref ACMP_CMPCR_CMP_HYSTERSIS_DISABLE
  * @return None
  */
void ACMP_Open(ACMP_T *Acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn)
{
    Acmp->CMPCR[u32ChNum] = (Acmp->CMPCR[u32ChNum] & ~ACMP_CMPCR_CN0_Msk) | (u32NegSrc>>24)<<ACMP_CMPCR_CN0_Pos;

    if((u32NegSrc&(0xFFUL<<24))==ACMP_CMPCR_CN0_CRV)
        Acmp->CMPRVCR = (Acmp->CMPRVCR & ~ACMP_CMPRVCR_CRV_OUT_SEL_Msk) | (u32NegSrc & 0x00FFFFFF) | ACMP_CMPRVCR_CRV_EN_Msk;

    Acmp->CMPCR[u32ChNum] = (Acmp->CMPCR[u32ChNum] & ~ACMP_CMPCR_CMP_HYSEN_Msk) | u32HysteresisEn;
    Acmp->CMPCR[u32ChNum] |= ACMP_CMPCR_CMPEN_Msk;
}

/**
  * @brief  This function close comparator
  *
  * @return None
  */
void ACMP_Close(ACMP_T *Acmp, uint32_t u32ChNum)
{
    Acmp->CMPCR[u32ChNum] &= ~ACMP_CMPCR_CMPEN_Msk;
}

/**
  * @brief  This function configure ACMP to sigma-delta mode.
  *
  * @param  u32TimerNum is set to 0 to use timer0 and timer1, set to 1 to use timer0 and timer1. Including :
  *                  - \ref ACMP_TIMER01
  *                  - \ref ACMP_TIMER23
  * @param  u32TriggerPolarity is set rising trigger or falling trigger. Including :
  *                  - \ref ACMP_CMP0MODCR_TMR_TRI_LV_RISING
  *                  - \ref ACMP_CMP0MODCR_TMR_TRI_LV_FALLING
  * @param  u32PosPin is comparator0 positive input selection.  Including :
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA1
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA2
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA3
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA4
  * @param  u32ChargePin is charge or discharge pin selection. Including :
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA1
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA2
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA3
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA4
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA5
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA6
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA14
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PF5
  *
  * @return None
  */
void ACMP_SetSigmaDeltaConv(uint32_t u32TimerNum, uint32_t u32TriggerPolarity, uint32_t u32PosPin, uint32_t u32ChargePin)
{
    ACMP->CMPCR[0] &= ~ACMP_CMPCR_CPO_SEL_Msk;
    ACMP->CMPCR[0] &= ~ACMP_CMPCR_CMP_INV_Msk;
    ACMP->CMPCR[0] |=  ACMP_CMPCR_COMP_PN_AutoEx_Msk; //Auto Exchange Enabled
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_TMR_SEL_Msk) | (u32TimerNum<<ACMP_CMP0MODCR_TMR_SEL_Pos);
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_MOD_SEL_Msk)| ACMP_CMP0MODCR_MOD_SEL_SIGAMA_DELTA;
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_TMR_TRI_LV_Msk) | u32TriggerPolarity;
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_CH_DIS_PIN_SEL_Msk)  | u32ChargePin ;
}


/**
  * @brief  This function configure ACMP to slope mode.
  *
  * @param  u32TimerNum is set to 0 to use timer0 and timer1, set to 1 to use timer0 and timer1. Including :
  *                  - \ref ACMP_TIMER01
  *                  - \ref ACMP_TIMER23
  * @param  u32TriggerPolarity is set rising trigger or falling trigger. Including :
  *                  - \ref ACMP_CMP0MODCR_TMR_TRI_LV_RISING
  *                  - \ref ACMP_CMP0MODCR_TMR_TRI_LV_FALLING
  * @param  u32PosPin is comparator0 positive input selection.  Including :
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA1
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA2
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA3
  *                  - \ref ACMP_CMP0CR_CPP0SEL_PA4
  * @param  u32ChargePin is charge or discharge pin selection. Including :
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA1
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA2
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA3
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA4
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA5
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA6
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PA14
  *                  - \ref ACMP_CMP0MODCR_CH_DIS_PINSEL_PF5
  *
  * @return None
  */
void ACMP_SetSlopeConv(uint32_t u32TimerNum, uint32_t u32TriggerPolarity, uint32_t u32PosPin, uint32_t u32ChargePin)
{
    ACMP->CMPCR[0] =(ACMP->CMPCR[0] & ~ACMP_CMPCR_CPP0SEL_Msk) | u32PosPin;
    ACMP->CMPCR[0] &= ~ACMP_CMPCR_CPO_SEL_Msk ; /* Comparator output is from internal path */
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_MOD_SEL_Msk)| ACMP_CMP0MODCR_MOD_SEL_SLOPE;
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_TMR_TRI_LV_Msk) | u32TriggerPolarity;
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_CH_DIS_PIN_SEL_Msk)  | u32ChargePin ; /* A Pin Can Only Do Discharging Work */
    ACMP->CMP0MODCR = (ACMP->CMP0MODCR & ~ACMP_CMP0MODCR_TMR_SEL_Msk) | (u32TimerNum<<ACMP_CMP0MODCR_TMR_SEL_Pos);
}


/*@}*/ /* end of group NANO1X2_ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NANO1X2_ACMP_Driver */

/*@}*/ /* end of group NANO1X2_Device_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

