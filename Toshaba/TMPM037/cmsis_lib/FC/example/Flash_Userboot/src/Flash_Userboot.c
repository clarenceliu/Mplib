/**
 *******************************************************************************
 * @file    main.c
 * @brief   main function of Flash demo(user boot mode)
 * @version V0.100
 * @date    2014/05/22
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "Flash_Userboot.h"


void (*startup) (void);
uint8_t Flash_Swap(void);
uint8_t Write_Flash(uint32_t * addr_dest, uint32_t * addr_source, uint32_t len);


uint32_t Load$$FLASH_CODE_RAM$$Base;
uint32_t Image$$FLASH_CODE_RAM$$Base;
uint32_t Load$$FLASH_CODE_RAM$$Length;
uint32_t Image$$FLASH_DEMO_A$$Base;
uint32_t Image$$FLASH_DEMO_B$$Base;
uint32_t Image$$RAM_DEMO_A$$Base;
uint32_t Image$$RAM_DEMO_B$$Base;
uint32_t Image$$FLASH_DEMO_A$$ZI$$Length;
uint32_t Image$$FLASH_DEMO_B$$ZI$$Length;

/**
  * @brief  Reset SP
  * @param  None.
  * @retval None.
  */
#if defined ( __CC_ARM )        /* RealView Compiler */
__ASM void ResetSP(void)
{
    MOV R0,
#0
     LDR SP,[R0]
}
#elif defined ( __ICCARM__ )    /* IAR Compiler */
#pragma section = "FLASH_CODE_RAM"
#pragma section = "FLASH_CODE_ROM"
#pragma section = "FLASH_DEMO_A"
#pragma section = "FLASH_DEMO_B"
#pragma section = "RAM_DEMO_A"
#pragma section = "RAM_DEMO_B"
#endif

/**
  * @brief  main function to run flash userboot mode demo
  * @param  None.
  * @retval result to return to system.
  */

int Flash_Userboot(void)
{
#if defined ( __ICCARM__ )      /* IAR Compiler */
    volatile uint32_t *c_stack;
#endif
    LED_Init();
    SW_Init();


    if (Mode_Judgement() == USER_BOOT_MODE) {   /* if SW0 is turned on, enter user boot mode */

        LED_On(LED3);           /* enter user boot mode */

        Copy_Routine(FLASH_API_RAM, FLASH_API_ROM, SIZE_FLASH_API);     /* copy flash API to RAM */

        if (FC_SUCCESS == Flash_Swap()) {       /* swap the flash content */
            /* Do nothing */
        } else {
            LED_On(LED0 | LED1 | LED3); /* if have any error, turn on all leds */

        }

    } else {                    /* if SW1 is turned off, enter normal mode */
#if defined ( __CC_ARM   )      /* RealView Compiler */
        ResetSP();              /* reset SP */
#elif defined ( __ICCARM__ )    /* IAR Compiler */

        c_stack = 0;
        __set_MSP(*c_stack);    /* reset SP */
#endif

        startup = CODE_START;
        startup();              /* jump to code start address to run */

    }


    return 0U;
}


/**
  * @brief  delay some time
  * @param  delay time
  * @retval None.
  */
void delay(uint32_t time)
{
    uint32_t i;
    for (i = 0U; i < time; i++) {
        /* Do nothing */
    }
}

/**
  * @brief  judge current mode is USER_BOOT_MODE or NORMAL_MODE
  * @param  None.
  * @retval None.
  */
uint8_t Mode_Judgement(void)
{
    return (SW_Get(SW0) == 1U) ? USER_BOOT_MODE : NORMAL_MODE;
}

/**
  * @brief  copy 32-bit data from source to dest
  * @param  the address of source and dast, the data size
  * @retval None.
  */
void Copy_Routine(uint32_t * dest, uint32_t * source, uint32_t size)
{
    uint32_t *dest_addr, *source_addr, tmpsize;
    uint32_t i, tmps, tmpd, mask;

    dest_addr = dest;
    source_addr = source;

    tmpsize = size >> 2U;

    for (i = 0U; i < tmpsize; i++) {    /* 32bits copy */
        *dest_addr = *source_addr;
        dest_addr++;
        source_addr++;
    }
    if (size & 0x00000003U) {   /* if the last data size is not 0(maybe 1,2 or 3), copy the last data */
        mask = 0xFFFFFF00U;
        i = size & 0x00000003U;
        tmps = *source_addr;
        tmpd = *dest_addr;
        while (i - 1U) {
            mask = mask << 8U;
            i--;
        }
        tmps = tmps & (~mask);
        tmpd = tmpd & (mask);
        *dest_addr = tmps + tmpd;       /* 32bits copy, but only change the bytes need to be changed */
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  swap two code in flash, and runs at RAM, then software reset
  * @param  None.
  * @retval ERROR or SUCCESS.
  */
#if defined ( __CC_ARM   )      /* RealView Compiler */
#pragma arm section code="FLASH_ROM"
#elif defined ( __ICCARM__ )    /* IAR Compiler */
#pragma location = "FLASH_ROM"
#endif
uint8_t Flash_Swap(void)
{
    Copy_Routine(DEMO_A_RAM, DEMO_A_FLASH, SIZE_DEMO_A);        /* copy A to RAM */
    Copy_Routine(DEMO_B_RAM, DEMO_B_FLASH, SIZE_DEMO_B);        /* copy B to RAM */

    if (FC_SUCCESS == FC_EraseBlock((uint32_t) DEMO_A_FLASH)) { /* erase A */
        /* Do nothing */
    } else {
        return ERROR;
    }

    if (FC_SUCCESS == Write_Flash(DEMO_A_FLASH, DEMO_B_RAM, SIZE_DEMO_B)) {     /* write B to A */
        /* Do nothing */
    } else {
        return ERROR;
    }

    if (FC_SUCCESS == FC_EraseBlock((uint32_t) DEMO_B_FLASH)) { /* erase B */
        /* Do nothing */
    } else {
        return ERROR;
    }

    if (FC_SUCCESS == Write_Flash(DEMO_B_FLASH, DEMO_A_RAM, SIZE_DEMO_A)) {     /* write A to B */
        /* Do nothing */
    } else {
        return ERROR;
    }

    delay(0x0FFFFF);

    LED_On(LED1);

    /* wait for Key SW0 to release */
    while (SW_Get(SW0) == 1U) {
    }
    NVIC_SystemReset();
    return SUCCESS;
}

/**
  * @brief  write flash
  * @param  destination address, source address, lenth of data.
  * @retval ERROR or SUCCESS.
  */
#if defined ( __CC_ARM   )      /* RealView Compiler */
#pragma arm section code="FLASH_ROM"
#elif defined ( __ICCARM__ )    /* IAR Compiler */
#pragma location = "FLASH_ROM"
#endif
uint8_t Write_Flash(uint32_t * addr_dest, uint32_t * addr_source, uint32_t len)
{
    uint32_t size;
    uint32_t *source;
    uint32_t *dest;

    dest = addr_dest;
    source = addr_source;
    size = len;
    while (size > FLASH_PAGE_SIZE) {
        if (FC_SUCCESS == FC_WritePage((uint32_t) dest, source)) {      /* write one page every time */
            /* Do nothing */
        } else {
            return ERROR;
        }
        size = size - FLASH_PAGE_SIZE;
        dest = dest + FLASH_PAGE_SIZE / 4U;
        source = source + FLASH_PAGE_SIZE / 4U;
    }
    if (FC_SUCCESS == FC_WritePage((uint32_t) dest, source)) {  /* write the last data, no more than one page */
        /* Do nothing */
    } else {
        return ERROR;
    }
    return SUCCESS;
}





#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif

/*************************** END OF FILE **************************************/
