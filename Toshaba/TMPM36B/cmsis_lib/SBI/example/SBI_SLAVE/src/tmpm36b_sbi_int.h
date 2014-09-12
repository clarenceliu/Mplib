/**
 *******************************************************************************
 * @file    tmpm36b_sbi_int.h
 * @brief   The header file for SBI ISR of SBI slave demo for the
 *          TOSHIBA 'TMPM36B' Device Series 
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM36B_SBI_INT_H
#define __TMPM36B_SBI_INT_H

#include "SBI_SLAVE.h"

void INTSBI2_IRQHandler(void);
void INTSBI0_IRQHandler(void);

#endif                          /* __TMPM36B_SBI_INT_H */
