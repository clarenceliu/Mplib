/**
 *****************************************************************************
 * @file     system_TMPM037.h
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Header File for the
 *           TOSHIBA 'TMPM037' Device Series 
 * @version  V2.0.2.1 (Tentative)
 * @date     2014/02/07
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *****************************************************************************
 */

#include <stdint.h>

#ifndef __SYSTEM_TMPM037_H
#define __SYSTEM_TMPM037_H

#ifdef __cplusplus
extern "C" {
#endif

    extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
    extern void SystemInit(void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock 
 *         retrieved from cpu registers.
 */
    extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif
#endif
