/**
 *******************************************************************************
 * @file    system_TMPM36B.c
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Source File for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V2.0.2.4
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "TMPM36B.h"

/*-------- <<< Start of configuration section >>> ----------------------------*/

/* Watchdog Timer (WD) Configuration */
#define WD_SETUP                1
#define WDMOD_Val               (0x00000000UL)
#define WDCR_Val                (0x000000B1UL)

/* Clock Generator (CG) Configuration */
#define CLOCK_SETUP             1
#define SYSCR_Val               (0x00010000UL)
#define OSCCR_Val               (0x000E0134UL) /* OSCCR<OSCSEL> = 1, OSCCR<XEN2> = 0, OSCCR<XEN1> = 1, OSCCR<PLLON> = 1, <EHOSCSEL> = 1 */

#define STBYCR_Val              (0x00000003UL)

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define OSC_8M                  ( 8000000UL)
#define OSC_10M                 (10000000UL)
#define OSC_12M                 (12000000UL)
#define OSC_16M                 (16000000UL)
#define EXTALH                  OSC_10M     /* External high-speed oscillator freq */
#define XTALH                   OSC_10M     /* Internal high-speed oscillator freq */

/* Configure Warm-up time */
#define HZ_1M                   1000000UL
#define WU_TIME_EXT             5000UL          /* warm-up time for EXT is 5ms   */
#define WU_TIME_PLL             100UL           /* warm-up time for PLL is 100us */
#define OSCCR_WUODR_MASK        (0x000FFFFFUL)
#define OSCCR_WUODR_EXT         ((WU_TIME_EXT * EXTALH / HZ_1M /16U) << 20U) /* OSCCR<WUPODR11:0> = warm-up time(us) * EXTALH(MHz) / 16 */
#define OSCCR_WUODR_PLL         ((WU_TIME_PLL * EXTALH / HZ_1M /16U) << 20U)

#if defined (TSB_M36BFY)                /*TSB_M36BFY MCU type*/

#define CG_8M_MUL_6_FPLL        (0x00007117UL<<1U)
#define CG_8M_MUL_10_FPLL       (0x000071A6UL<<1U)

#define CG_10M_MUL_8_FPLL       (0x0000711EUL<<1U)

#define CG_12M_MUL_4_FPLL       (0x0000610FUL<<1U)
#define CG_12M_MUL_6_FPLL       (0x00006195UL<<1U)

#define CG_16M_MUL_3_FPLL       (0x00006A8BUL<<1U)
#define CG_16M_MUL_5_FPLL       (0x00007292UL<<1U)

#define PLLSEL_Ready            CG_10M_MUL_8_FPLL
#define PLLSEL_Val              (PLLSEL_Ready|1U)
#define PLLSEL_MASK             0x0000FFFEUL

/*-------- <<< End of configuration section >>> ------------------------------*/

#if (CLOCK_SETUP)               /* Clock(external) Setup */
/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
#if (OSCCR_Val & (1U<<17))
  #define CORE_TALH (EXTALH)
#else
  #define CORE_TALH (XTALH)
#endif

#if ((PLLSEL_Val & (1U<<0)) && (OSCCR_Val & (1U<<2)))   /* If PLL selected and enabled */
  #if (CORE_TALH == OSC_8M)                             /* If input is 8MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_6_FPLL))
      #define __CORE_CLK   (CORE_TALH * 6U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_10_FPLL))
      #define __CORE_CLK   (CORE_TALH * 10U )           /* output clock is 80MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 8MHz */
  #elif (CORE_TALH == OSC_10M)                       /* If input is 10MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_8_FPLL))
      #define __CORE_CLK   (CORE_TALH * 8U )            /* output clock is 80MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 10MHz */
  #elif (CORE_TALH == OSC_12M)                       /* If input is 12MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_12M_MUL_4_FPLL)
      #define __CORE_CLK   (CORE_TALH * 4U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_12M_MUL_6_FPLL)
      #define __CORE_CLK   (CORE_TALH * 6U )            /* output clock is 72MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 12MHz */
  #elif (CORE_TALH == OSC_16M)                       /* If input is 16MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_3_FPLL)
      #define __CORE_CLK   (CORE_TALH * 3U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_5_FPLL)
      #define __CORE_CLK   (CORE_TALH * 5U )            /* output clock is 80MHz */
    #else                                               /* fc -> reserved        */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 16MHz    */
  #else                                                 /* input clock not known */
    #define __CORE_CLK   (0U)
    #error "Core Oscillator Frequency invalid!"
  #endif                                                /* End switch input clock */
#else
  #define __CORE_CLK   (CORE_TALH)
#endif

#if   ((SYSCR_Val & 7U) == 0U)                          /* Gear -> fc             */
  #define __CORE_SYS   (__CORE_CLK)
#elif ((SYSCR_Val & 7U) == 4U)                          /* Gear -> fc/2           */
  #define __CORE_SYS   (__CORE_CLK / 2U)
#elif ((SYSCR_Val & 7U) == 5U)                          /* Gear -> fc/4           */
  #define __CORE_SYS   (__CORE_CLK / 4U)
#elif ((SYSCR_Val & 7U) == 6U)                          /* Gear -> fc/8           */
  #define __CORE_SYS   (__CORE_CLK / 8U)
#elif ((SYSCR_Val & 7U) == 7U)                          /* Gear -> fc/16          */
  #define __CORE_SYS   (__CORE_CLK / 16U)
#else                                                   /* Gear -> reserved       */
  #define __CORE_SYS   (0U)
#endif

#else
  #define __CORE_SYS   (XTALH)
#endif                                                  /* clock Setup */
                                        /* END TSB_M36BFY MCU type*/
#elif defined  (TSB_M36BF10)           /*TSB_M36BF10 MCU type*/
#define CG_8M_MUL_6_FPLL        (0x00007817UL<<1U)
#define CG_8M_MUL_8_FPLL        (0x0000789FUL<<1U)

#define CG_10M_MUL_4_FPLL       (0x0000780FUL<<1U)
#define CG_10M_MUL_6_FPLL       (0x00007817UL<<1U)

#define CG_12M_MUL_4_FPLL       (0x0000790FUL<<1U)
#define CG_12M_MUL_5_FPLL       (0x00007993UL<<1U)

#define CG_16M_MUL_3_FPLL       (0x0000710BUL<<1U)
#define CG_16M_MUL_4_FPLL       (0x0000790FUL<<1U)


#define PLLSEL_Ready            CG_10M_MUL_6_FPLL
#define PLLSEL_Val              (PLLSEL_Ready|1U)
#define PLLSEL_MASK             0x0000FFFEUL

/*-------- <<< End of configuration section >>> ------------------------------*/


#if (CLOCK_SETUP)               /* Clock(external) Setup */
/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
#if (OSCCR_Val & (1U<<17))
  #define CORE_TALH (EXTALH)
#else
  #define CORE_TALH (XTALH)
#endif

#if ((PLLSEL_Val & (1U<<0)) && (OSCCR_Val & (1U<<2)))   /* If PLL selected and enabled */
  #if (CORE_TALH == OSC_8M)                             /* If input is 8MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_6_FPLL))
      #define __CORE_CLK   (CORE_TALH * 6U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_8_FPLL))
      #define __CORE_CLK   (CORE_TALH * 8U )           /* output clock is 64MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 8MHz */
  #elif (CORE_TALH == OSC_10M)                       /* If input is 10MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_4_FPLL))
      #define __CORE_CLK   (CORE_TALH * 4U )            /* output clock is 40MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_6_FPLL))
      #define __CORE_CLK   (CORE_TALH * 6U )           /* output clock is 60MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 10MHz */
  #elif (CORE_TALH == OSC_12M)                       /* If input is 12MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_12M_MUL_4_FPLL)
      #define __CORE_CLK   (CORE_TALH * 4U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_12M_MUL_5_FPLL)
      #define __CORE_CLK   (CORE_TALH * 5U )            /* output clock is 60MHz */
    #else                                               /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 12MHz */
  #elif (CORE_TALH == OSC_16M)                       /* If input is 16MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_3_FPLL)
      #define __CORE_CLK   (CORE_TALH * 3U )            /* output clock is 48MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_4_FPLL)
      #define __CORE_CLK   (CORE_TALH * 4U )            /* output clock is 64MHz */
    #else                                               /* fc -> reserved        */
      #define __CORE_CLK   (0U)
    #endif                                              /* End input is 16MHz    */
  #else                                                 /* input clock not known */
    #define __CORE_CLK   (0U)
    #error "Core Oscillator Frequency invalid!"
  #endif                                                /* End switch input clock */
#else
  #define __CORE_CLK   (CORE_TALH)
#endif

#if   ((SYSCR_Val & 7U) == 0U)                          /* Gear -> fc             */
  #define __CORE_SYS   (__CORE_CLK)
#elif ((SYSCR_Val & 7U) == 4U)                          /* Gear -> fc/2           */
  #define __CORE_SYS   (__CORE_CLK / 2U)
#elif ((SYSCR_Val & 7U) == 5U)                          /* Gear -> fc/4           */
  #define __CORE_SYS   (__CORE_CLK / 4U)
#elif ((SYSCR_Val & 7U) == 6U)                          /* Gear -> fc/8           */
  #define __CORE_SYS   (__CORE_CLK / 8U)
#elif ((SYSCR_Val & 7U) == 7U)                          /* Gear -> fc/16          */
  #define __CORE_SYS   (__CORE_CLK / 16U)
#else                                                   /* Gear -> reserved       */
  #define __CORE_SYS   (0U)
#endif

#else
  #define __CORE_SYS   (XTALH)
#endif                                                  /* clock Setup */

#endif                                  /*End TSB_M36BF10 MCU type*/
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
{                               /* Get Core Clock Frequency */
    uint32_t CoreClock = 0U;
    uint32_t CoreClockInput = 0U;
    /* Determine clock frequency according to clock register values */
    /* System clock is high-speed clock */
    if (TSB_CG_OSCCR_OSCSEL) {  /* If system clock is External high-speed oscillator freq */
        CoreClock = EXTALH;
    } else {                    /* If system clock is Internal high-speed oscillator freq */
        CoreClock = XTALH;
    }
    if (TSB_CG_PLLSEL_PLLSEL && TSB_CG_OSCCR_PLLON) {                        /* If PLL enabled  */
        if (CoreClock == OSC_8M) {                                          /* If input is 8MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_6_FPLL) {     
                CoreClockInput = CoreClock * 6U;                             /* output clock is 48MHz */
#if defined (TSB_M36BFY)
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_10_FPLL) {
                CoreClockInput = CoreClock * 10U;                            /* output clock is 80MHz */
#elif defined  (TSB_M36BF10)
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_8_FPLL) {
                CoreClockInput = CoreClock * 8U;                            /* output clock is 64MHz */
#endif                
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved            */
            }
        } else if (CoreClock == OSC_10M) {                                  /* If input is 10MHz */
#if defined (TSB_M36BFY)
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_8_FPLL) {
                CoreClockInput = CoreClock * 8U;                             /* output clock is 80MHz */
#elif defined  (TSB_M36BF10)
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_4_FPLL) {
                CoreClockInput = CoreClock * 4U;                             /* output clock is 40MHz */
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_6_FPLL) {
                CoreClockInput = CoreClock * 6U;                            /* output clock is 60MHz */
#endif
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved */
            }
        } else if (CoreClock == OSC_12M) {                                  /* If input is 12MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_12M_MUL_4_FPLL) {
                CoreClockInput = CoreClock * 4U;                             /* output clock is 48MHz */
#if defined (TSB_M36BFY)
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_12M_MUL_6_FPLL) {
                CoreClockInput = CoreClock * 6U;                             /* output clock is 72MHz */
#elif defined  (TSB_M36BF10)
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_12M_MUL_5_FPLL) {
                CoreClockInput = CoreClock * 5U;                             /* output clock is 60MHz */
#endif                
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved */
            }
        } else if (CoreClock == OSC_16M) {                                  /* If input is 16MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_16M_MUL_3_FPLL) {
                CoreClockInput = CoreClock * 3U;                             /* output clock is 48MHz */
#if defined (TSB_M36BFY)                
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_16M_MUL_5_FPLL) {
                CoreClockInput = CoreClock * 5U;                             /* output clock is 80MHz */
#elif defined  (TSB_M36BF10)
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_16M_MUL_4_FPLL) {
                CoreClockInput = CoreClock * 4U;                             /* output clock is 64MHz */
#endif
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved        */
            }
        } else {
            CoreClockInput = 0U;
        }
    } else {
        CoreClockInput = CoreClock;
    }
    switch (TSB_CG->SYSCR & 7U) {
    case 0U:
        SystemCoreClock = CoreClockInput;                                    /* Gear -> fc      */
        break;                                                              
    case 1U:
    case 2U:
    case 3U:                                                                 /* Gear -> reserved */
        SystemCoreClock = 0U;
        break;
    case 4U:                                                                 /* Gear -> fc/2     */
        SystemCoreClock = CoreClockInput / 2U;
        break;
    case 5U:                                                                 /* Gear -> fc/4     */
        SystemCoreClock = CoreClockInput / 4U;
        break;
    case 6U:                                                                 /* Gear -> fc/8     */
        SystemCoreClock = CoreClockInput / 8U;
        break;
    case 7U:                                                                 /* Gear -> fc/16     */
        if (CoreClockInput >= OSC_16M){
        SystemCoreClock = CoreClockInput / 16U;
      }else{
      	SystemCoreClock = 0U;
      }
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

#if (WD_SETUP)                  /* Watchdog Setup */
    TSB_WD->MOD = WDMOD_Val;
    if (!TSB_WD_MOD_WDTE) {     /* If watchdog is to be disabled */
        TSB_WD->CR = WDCR_Val;
    }
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->SYSCR = SYSCR_Val;
    TSB_CG->OSCCR &= OSCCR_WUODR_MASK;
    TSB_CG->OSCCR |= OSCCR_WUODR_EXT;
    TSB_CG_OSCCR_EHOSCSEL = 1U;
    TSB_CG_OSCCR_XEN1 = 1U;
    TSB_CG_OSCCR_WUPSEL2 = 1U;
    TSB_CG_OSCCR_WUEON = 1U;
    TSB_CG->PLLSEL = PLLSEL_Ready;
    while (TSB_CG_OSCCR_WUEF) {
    }                           /* Warm-up */
    TSB_CG_OSCCR_OSCSEL = 1U;
    TSB_CG_OSCCR_XEN2 = 0U;

    TSB_CG->OSCCR &= OSCCR_WUODR_MASK;
    TSB_CG->OSCCR |= OSCCR_WUODR_PLL;
    TSB_CG_OSCCR_PLLON = 1U;    /* PLL enabled */
    TSB_CG->STBYCR = STBYCR_Val;
    TSB_CG_OSCCR_WUEON = 1U;
    while (TSB_CG_OSCCR_WUEF) {
    }                           /* Warm-up */

    TSB_CG->PLLSEL = PLLSEL_Val;
#endif
}
