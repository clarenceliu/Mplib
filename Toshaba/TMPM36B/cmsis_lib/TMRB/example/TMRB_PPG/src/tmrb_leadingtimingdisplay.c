/** 
 *******************************************************************************
 * @file    tmrb_leadingtimingdisplay.c
 * @brief   the application functions of TMRB_PPG demo for the TOSHIBA
 *          'TMPM36B' Device Series 
 * @version V0.201
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmrb_leadingtimingdisplay.h"

/**
  * @brief  LeadingTiming Rate to String
  * @param  leadingtiming number
  * @retval LeadingTiming rate string
  */
char *LeadingTimingRateToString(uint8_t num)
{
    static char leadingtiming[18] = "LeadingTiming:   %";

    switch (num) {
    case 0:
        leadingtiming[15] = '1';
        leadingtiming[16] = '0';
        break;                  /* LeadingTiming: 10% */
    case 1:
        leadingtiming[15] = '2';
        leadingtiming[16] = '5';
        break;                  /* LeadingTiming: 25% */
    case 2:
        leadingtiming[15] = '5';
        leadingtiming[16] = '0';
        break;                  /* LeadingTiming: 50% */
    case 3:
        leadingtiming[15] = '7';
        leadingtiming[16] = '5';
        break;                  /* LeadingTiming: 75% */
    case 4:
        leadingtiming[15] = '9';
        leadingtiming[16] = '0';
        break;                  /* LeadingTiming: 90% */
    default:
        /* Do nothing */
        break;                  /* no other cases */
    }

    return leadingtiming;
}
