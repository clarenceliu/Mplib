/**
 ****************************************************************************
 * @file     system_TMPM037.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File for the
 *           TOSHIBA 'TMPM037' Device Series 
 * @version  V2.0.2.2 (Tentative)
 * @date     2014/05/06
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *****************************************************************************
 */

#include "TMPM037.h"

/*-------- <<< Start of configuration section >>> ----------------------------*/

/* Watchdog Timer (WD) Configuration */
#define WD_SETUP                1U
#define WDMOD_Val               (0x00000000UL)
#define WDCR_Val                (0x000000B1UL)

/* Clock Generator (CG) Configuration */
#define CLOCK_SETUP             1U
#define SYSCR_Val               (0x00001000UL)

/* #define INTERNAL_OSCILLATION */
#ifdef  INTERNAL_OSCILLATION
    #define OSCCR_Val           (0x00000000UL) /* Use the internal high speed oscillation */
#else
    #define OSCCR_Val           (0x00020000UL)     /*Bit17,OSCSEL = 1:Ex.OSC*/
#endif

#define CG_MUL_2_FPLL           (0x0000609FUL<<1U)
#define PLLSEL_Val              CG_MUL_2_FPLL
#define PLLSEL_MASK             (0x0000FFFEUL)


/*-------- <<< End of configuration section >>> ------------------------------*/

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define OSC_10M                 (10000000UL)
#define OSC_16M                 (16000000UL)

#define XTALH                   OSC_10M  /* Internal high-speed oscillator freq */
#define EXTALH                  OSC_16M  /* External high-speed oscillator freq */


/* Configure Warm-up time */
#define HZ_1M                   (1000000UL)
#define WU_TIME_EXT             (5000UL)          /* warm-up time for EXT is 5ms   */
#define WU_TIME_PLL             (100UL)           /* warm-up time for PLL is 100us */
#define OSCCR_WUODR_MASK        (0x000FFFFFUL)
#define OSCCR_WUODR_EXT         ((WU_TIME_EXT * EXTALH / HZ_1M / 16U) << 20U) /* OSCCR<WUPODR11:0> = warm-up time(us) * EXTALH(MHz) / 16 */
#define OSCCR_WUODR_PLL         ((WU_TIME_PLL * EXTALH / HZ_1M /16UL) << 20U)


/* Determine core clock frequency according to settings */
#if (OSCCR_Val & (1U<<17))
    #if((EXTALH <= OSC_10M)&&((PLLSEL_Val & PLLSEL_MASK) == CG_MUL_2_FPLL))
        #define  __CORE_CLK         (EXTALH * 2U )
    #else
        #define  __CORE_CLK         (EXTALH)
    #endif
#else
    #define __CORE_CLK           (XTALH)           /* If use Internal-speed oscillator */
#endif
     

        
#if   ((SYSCR_Val & 7U) == 0U)        /* Gear -> fc                         */
    #define __CORE_SYS          (__CORE_CLK)
#elif ((SYSCR_Val & 7U) == 4U)        /* Gear -> fc/2                       */
    #define __CORE_SYS          (__CORE_CLK / 2U)
#elif ((SYSCR_Val & 7U) == 5U)        /* Gear -> fc/4                       */
    #define __CORE_SYS          (__CORE_CLK / 4U)
#elif ((SYSCR_Val & 7U) == 6U)        /* Gear -> fc/8                       */
    #define __CORE_SYS          (__CORE_CLK / 8U)
#elif ((SYSCR_Val & 7U) == 7U)        /* Gear -> fc/16                      */
    #define __CORE_SYS          (__CORE_CLK / 16U)
#else                                 /* Gear -> reserved                   */
    #define __CORE_SYS          (0U)
#endif

/* Clock Variable definitions */
uint32_t SystemCoreClock = __CORE_SYS;  /*!< System Clock Frequency (Core Clock) */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Update SystemCoreClock according register values.
 */
void SystemCoreClockUpdate(void)
{                               /* Get Core Clock Frequency       */
    uint32_t CoreClock = 0U;
    
    if (TSB_CG->OSCCR & ((uint32_t)0x01 << 17U) ) {      /* If system clock is External high-speed oscillator freq */
        CoreClock = EXTALH;
        if (TSB_CG_PLLSEL_PLLSEL && TSB_CG_PLLSEL_PLLST&&TSB_CG_OSCCR_PLLON) {
            if (CoreClock <= OSC_10M){
                if((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_MUL_2_FPLL){
                    CoreClock = CoreClock * 2U;
                } else {
                    /* Do nothing */
                }
            } else {
                /* Do nothing */
            }
        } else {
            /* Do nothing */
        }
    } else {
        CoreClock = XTALH;                              /* If system clock is Internal high-speed oscillator freq */
    }

    switch (TSB_CG->SYSCR & 7U) {
    case 0U:               /* Gear -> fc          */
        SystemCoreClock = CoreClock;
        break;
    case 1U:
    case 2U:
    case 3U:               /* Gear -> reserved    */
        SystemCoreClock = 0U;
        break;
    case 4U:               /* Gear -> fc/2        */
        SystemCoreClock = CoreClock / 2U;
        break;
    case 5U:               /* Gear -> fc/4        */
        SystemCoreClock = CoreClock / 4U;
        break;
    case 6U:               /* Gear -> fc/8        */
        SystemCoreClock = CoreClock / 8U;
        break;
    case 7U:               /* Gear -> fc/16       */
        SystemCoreClock = CoreClock / 16U;
        break;
    default:
        SystemCoreClock = 0U;
        break;
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
    uint32_t tmp = 0U;
    
#if (WD_SETUP)                          /* Watchdog Setup */
  TSB_WD->MOD = WDMOD_Val;
  if (!TSB_WD_MOD_WDTE) {               /* If watchdog is to be disabled */
    TSB_WD->CR = WDCR_Val;
  }
#endif

#if (CLOCK_SETUP)                       /* Clock Setup */
    TSB_CG->SYSCR = SYSCR_Val;
    TSB_CG_OSCCR_EHOSCSEL = 1U;
    TSB_CG_OSCCR_HWUPSEL = 1U;
    TSB_CG_OSCCR_XEN1 = 1U;
    
    tmp = TSB_CG->OSCCR;                /*Set warm up time*/
    tmp &= OSCCR_WUODR_MASK;
    tmp |= OSCCR_WUODR_EXT;
    tmp |= (0x06UL<<3U);
    TSB_CG->OSCCR = tmp;
    TSB_CG_OSCCR_WUEON = 1U;            /*Warm up start*/
    while (TSB_CG_OSCCR_WUEF) { }       /* Warm-up */
    TSB_CG_OSCCR_OSCSEL = 1U;
    while (TSB_CG_OSCCR_OSCF == 0U) { }
    TSB_CG_OSCCR_XEN2 = 0U;
    
    if(EXTALH <= OSC_10M){               /*Set PLL Multiply*/
        TSB_CG->PLLSEL = PLLSEL_Val;
        tmp = TSB_CG->OSCCR;            /*100us Warm-up*/
        tmp &= OSCCR_WUODR_MASK;
        tmp |= OSCCR_WUODR_PLL;
        tmp |= (0x06UL<<3U);
        TSB_CG->OSCCR = tmp;
        TSB_CG_OSCCR_WUEON = 1U;         /*Warm up start*/
        while (TSB_CG_OSCCR_WUEF) { }    /* Warm-up */
        
        TSB_CG_OSCCR_PLLON = 1U;
        tmp = TSB_CG->OSCCR;            /*100us Warm-up*/
        tmp &= OSCCR_WUODR_MASK;
        tmp |= OSCCR_WUODR_PLL;
        tmp |= (0x06UL<<3U);
        TSB_CG->OSCCR = tmp;
        TSB_CG_OSCCR_WUEON = 1U;         /*Warm up start*/
        while (TSB_CG_OSCCR_WUEF) { }    /* Warm-up */
        
        TSB_CG_PLLSEL_PLLSEL = 1U;
    }else{
        TSB_CG->PLLSEL = 0U;            /* No Multiply*/
    }
#endif
}
