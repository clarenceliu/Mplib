/******************************************************************************
 * @file     LCDLIB.c
 * @brief    NANO1x2 LCD Library source file.
 * @version  1.0.0
 * @date     25, October, 2013
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Nano1X2Series.h"
#include "lcd.h"
#include "LCDLIB.h"

/** @addtogroup NANO1X2_Library NANO1X2 Library
  @{
*/

/** @addtogroup NANO1X2_LCDLIB_Driver LCD Library
  @{
*/

/// @cond

/// @endcond



/** @addtogroup NANO1X2_LCDLIB_EXPORTED_VARIABLES LCDLIB Exported Variables
  @{
*/

 extern char *Zone[];
 extern const ZoneInfo_TypeDef LCD_ZoneInfo[];
 extern const uint16_t *Zone_TextDisplay[];

/*@}*/ /* end of group NANO1X2_LCDLIB_EXPORTED_VARIABLES */

/** @addtogroup NANO1X2_LCDLIB_EXPORTED_FUNCTIONS LCDLIB Exported Functions
  @{
*/

/**
 *  @brief Display text on LCD
 *
 *  @param u32Zone  the assigned numbr of display area
 *  @param string  Text string to show on display
 *
 *  @return None
 *
 */
void LCDLIB_Printf(uint32_t  u32Zone, char *string)
{
    int      data, length, index;
    uint16_t bitfield;
    uint32_t com, bit;
    int      i;

    length = strlen(string);
    index  = 0;

    /* fill out all characters on display */
    for (index = 0; index < LCD_ZoneInfo[u32Zone].Sub_Zone_Num; index++) {
        if (index < length) {
            data = (int) *string;
        } else {       /* padding with space */
            data = 0x20; /* SPACE */
        }
        /* defined letters currently starts at "SPACE" - 0x20; */
        data     = data - 0x20;
        bitfield = *(Zone_TextDisplay[u32Zone] + data);

        for (i = 0; i < LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum; i++) {
            bit = *(Zone[u32Zone]
                    + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                    + i*2 + 1);

            com = *(Zone[u32Zone]
                    + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                    + i*2 + 0);

            LCD_SetPixel(com, bit, 0);

            if (bitfield & (1 << i)) {
                /* Turn on segment */
                LCD_SetPixel(com, bit, 1);
            }
        }
        string++;
    }

}


/**
 *  @brief Display number on LCD
 *
 *  @param u32Zone  the assigned numbr of display area
 *  @param value  number to show on display
 *
 *  @return None
 *
 */
void LCDLIB_PrintNumber(uint32_t  u32Zone, long long value)
{
    int      index;
    long long num, i, com, bit, div, len, tmp;
    uint16_t bitpattern;

    if (value < 0) {
        value = abs(value);
    }

    /* Length of number */
    len = 0;
    tmp = value;
    while( 1 ) {
        if( (tmp/10) || (tmp%10) ) {
            tmp = tmp / 10;
            len++;
        } else
            break;
    }


    /* Extract useful digits */
    div = 1;

    /* fill out all characters on display */
    for (index = (LCD_ZoneInfo[u32Zone].Sub_Zone_Num-1); index >= 0; index--) {
        num = (value / div) % 10;
        num += 16;

        bitpattern = *(Zone_TextDisplay[u32Zone] + num);

        for (i = 0; i < LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum; i++) {
            bit = *(Zone[u32Zone]
                    + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                    + i*2 + 1);
            com = *(Zone[u32Zone]
                    + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                    + i*2 + 0);

            LCD_SetPixel(com, bit, 0);

            if (bitpattern & (1 << i)) {
                LCD_SetPixel(com, bit, 1);
            }
        }
        div = div * 10;

    }

}



/**
 *  @brief Display character on LCD
 *
 *  @param u32Zone   the assigned numbr of display area
 *  @param u32Index  the requested display position in zone
 *  @param u8Ch      Character to show on display
 *
 *  @return None
 *
 */
void LCDLIB_PutChar(uint32_t u32Zone, uint32_t u32Index, uint8_t u8Ch)
{
    int      data, index;
    uint16_t bitfield;
    uint32_t com, bit;
    int      i;

    index  = u32Index;

    data = u8Ch;

    if(u32Index > LCD_ZoneInfo[u32Zone].Sub_Zone_Num) return;

    /* defined letters currently starts at "SPACE" - 0x20; */
    data     = data - 0x20;
    bitfield = *(Zone_TextDisplay[u32Zone] + data);

    for (i = 0; i < LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum; i++) {
        bit = *(Zone[u32Zone]
                + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                + i*2 + 1);

        com = *(Zone[u32Zone]
                + index*LCD_ZoneInfo[u32Zone].Zone_Digit_SegNum*2
                + i*2 + 0);

        LCD_SetPixel(com, bit, 0);

        if (bitfield & (1 << i)) {
            /* Turn on segment */
            LCD_SetPixel(com, bit, 1);
        }
    }

}

/**
 *  @brief Display symbol on LCD
 *
 *  @param u32Zone   the assigned numbr of display area
 *  @param u32Index  the requested display position in zone
 *  @param u32OnOff  1: display symbol
 *                   0: not display symbol
 *
 *  @return None
 *
 */
void LCDLIB_SetSymbol(uint32_t u32Zone, uint32_t u32Index, uint32_t u32OnOff)
{
    uint32_t com, bit;

    bit = *(Zone[u32Zone] + u32Index*2 + 1);

    com = *(Zone[u32Zone] + u32Index*2 + 0);

    if (u32OnOff)
        LCD_SetPixel(com, bit, 1); /* Turn on segment */
    else
        LCD_SetPixel(com, bit, 0); /* Turn off segment */

}

/*@}*/ /* end of group NANO1X2_LCDLIB_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NANO1X2_LCDLIB_Driver */

/*@}*/ /* end of group NANO1X2_Library */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
