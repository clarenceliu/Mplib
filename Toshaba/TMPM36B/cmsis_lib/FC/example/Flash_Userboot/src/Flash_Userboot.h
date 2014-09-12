/**
 *******************************************************************************
 * @file    main.h
 * @brief   header file for main.c, included some address definition and
 *          function prototypes
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#ifndef MAIN_H
#define MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "tmpm36b_fc.h"
#include "led.h"
#include "common_uart.h"

/* Private define ------------------------------------------------------------*/
#define USER_BOOT_MODE          ((uint8_t)0x01)
#define NORMAL_MODE             ((uint8_t)0x00)

#if defined ( __CC_ARM   )      /* RealView Compiler */
#define FLASH_API_ROM           (uint32_t *)&Load$$FLASH_CODE_RAM$$Base

#define FLASH_API_RAM           (uint32_t *)&Image$$FLASH_CODE_RAM$$Base
#define SIZE_FLASH_API          (uint32_t)&Load$$FLASH_CODE_RAM$$Length

#define DEMO_A_FLASH            (uint32_t *)&Image$$FLASH_DEMO_A$$Base
#define DEMO_B_FLASH            (uint32_t *)&Image$$FLASH_DEMO_B$$Base

#define DEMO_A_RAM              (uint32_t *)&Image$$RAM_DEMO_A$$Base
#define DEMO_B_RAM              (uint32_t *)&Image$$RAM_DEMO_B$$Base

#define SIZE_DEMO_A               (uint32_t)&Image$$FLASH_DEMO_A$$ZI$$Length
#define SIZE_DEMO_B               (uint32_t)&Image$$FLASH_DEMO_B$$ZI$$Length

#elif defined ( __ICCARM__ )    /* IAR Compiler */
#define FLASH_API_ROM           ((uint32_t *)__section_begin("FLASH_CODE_ROM"))

#define FLASH_API_RAM           ((uint32_t *)__section_begin("FLASH_CODE_RAM"))
#define SIZE_FLASH_API          ((uint32_t)__section_size("FLASH_CODE_ROM"))

#define DEMO_A_FLASH            ((uint32_t *)__section_begin("FLASH_DEMO_A"))
#define DEMO_B_FLASH            ((uint32_t *)__section_begin("FLASH_DEMO_B"))

#define DEMO_A_RAM              ((uint32_t *)__section_begin("RAM_DEMO_A"))
#define DEMO_B_RAM              ((uint32_t *)__section_begin("RAM_DEMO_B"))

#define SIZE_DEMO_A             ((uint32_t)__section_size("FLASH_DEMO_A"))
#define SIZE_DEMO_B             ((uint32_t)__section_size("FLASH_DEMO_B"))
#endif

/* code start address */
#define DEMO_START_ADDR         ((uint32_t)DEMO_A_FLASH)
#define CODE_START              ((void (*)(void))(*(uint32_t *)(DEMO_START_ADDR + 4U)))

/* Private function prototypes -----------------------------------------------*/
void Copy_Routine(uint32_t * dest, uint32_t * source, uint32_t size);
uint8_t Flash_Swap(void);
uint8_t Mode_Judgement(void);
uint8_t Write_Flash(uint32_t * addr_dest, uint32_t * addr_source, uint32_t len);
void delay(uint32_t DelayTime);
#endif
/*************************** END OF FILE **************************************/
