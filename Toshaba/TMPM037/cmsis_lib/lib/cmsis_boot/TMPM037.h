/**
 *******************************************************************************
 * @file    TMPM037.h
 * @brief   CMSIS Cortex-M0 Core Peripheral Access Layer Header File for the
 *          TOSHIBA 'TMPM037' Device Series
 * @version V2.0.2.5 (Tentative)
 * @date    2014/07/11
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/** @addtogroup TOSHIBA_TX00_MICROCONTROLLER
  * @{
  */
  
/** @addtogroup TMPM037
  * @{
  */

#ifndef __TMPM037_H__
#define __TMPM037_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/** Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************************/
  NonMaskableInt_IRQn           = -14,       /*!< 2 Non Maskable Interrupt                                    */
  HardFault_IRQn                = -13,       /*!< 3 Cortex-M0 Hard Fault Interrupt                            */
  SVCall_IRQn                   = -5,        /*!< 11 Cortex-M0 SV Call Interrupt                              */
  PendSV_IRQn                   = -2,        /*!< 14 Cortex-M0 Pend SV Interrupt                              */
  SysTick_IRQn                  = -1,        /*!< 15 Cortex-M0 System Tick Interrupt                          */

/******  TMPM037 Specific Interrupt Numbers *******************************************************************/
  INT0_IRQn                     = 0,         /*!< Interrupt Pin0(PB5)                                         */
  INT1_IRQn                     = 1,         /*!< Interrupt Pin1(PB6)                                         */
  INT2_IRQn                     = 2,         /*!< Interrupt Pin2(PB7)                                         */
  INT3_IRQn                     = 3,         /*!< Interrupt Pin3(PE7)                                         */
  INT4_IRQn                     = 4,         /*!< Interrupt Pin4(PE6)                                         */
  INT5_IRQn                     = 5,         /*!< Interrupt Pin5(PE5)                                         */
  INTRX0_IRQn                   = 6,         /*!< Serial reception (channel.0)                                */
  INTTX0_IRQn                   = 7,         /*!< Serial transmission (channel.0)                             */
  INTRX1_IRQn                   = 8,         /*!< Serial reception (channel.1)                                */
  INTTX1_IRQn                   = 9,         /*!< Serial transmission (channel.1)                             */
  INTI2C0_IRQn                  = 12,        /*!< Serial bus interface                                        */
  INTDMAC_IRQn                  = 13,        /*!< DMAC interrupt                                              */
  INTT16A0_IRQn                 = 14,        /*!< 16-bit TMR16A match detection (channel.0)                   */
  INTT16A1_IRQn                 = 15,        /*!< 16-bit TMR16A match detection (channel.1)                   */
  INTTMRB0_IRQn                 = 16,        /*!< 16-bit TMRB interrupt(channel.0)                            */
  INTTMRB1_IRQn                 = 17,        /*!< 16-bit TMRB interrupt(channel.1)                            */
  INTTMRB2_IRQn                 = 18,        /*!< 16-bit TMRB interrupt(channel.2)                            */
  INTTMRB3_IRQn                 = 19,        /*!< 16-bit TMRB interrupt(channel.3)                            */
  INTTMRB4_IRQn                 = 20,        /*!< 16-bit TMRB interrupt(channel.4)                            */
  INTTMRB5_IRQn                 = 21,        /*!< 16-bit TMRB interrupt(channel.5)                            */
  INTTMRB6_IRQn                 = 22,        /*!< 16-bit TMRB interrupt(channel.6)                            */
  INTTMRB7_IRQn                 = 23,        /*!< 16-bit TMRB interrupt(channel.7)                            */
  INTRX2_IRQn                   = 24,        /*!< Serial reception (channel.2)                                */
  INTTX2_IRQn                   = 25,        /*!< Serial transmission (channel.2)                             */
  INTRX3_IRQn                   = 26,        /*!< Serial reception (channel.3)                                */
  INTTX3_IRQn                   = 27,        /*!< Serial transmission (channel.3)                             */
  INTRX4_IRQn                   = 28,        /*!< Serial reception (channel.4)                                */
  INTTX4_IRQn                   = 29,        /*!< Serial transmission (channel.4)                             */
  INTADC_IRQn                   = 30,        /*!< A/D conversion combined interrupt                           */
  INTAD_IRQn                    = 31         /*!< Normal A/D conversion completion interrupt                  */
} IRQn_Type;

/** Processor and Core Peripheral Section */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __CM0_REV              0x0000       /*!< Cortex-M0 Core Revision                           */
#define __MPU_PRESENT             0         /*!< MPU present or not                                */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels           */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used      */

/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0.h"                       /* Cortex-M0 processor and core peripherals            */
#include "system_TMPM037.h"                 /* TMPM037 System                                      */

/** @addtogroup Device_Peripheral_registers
  * @{
  */

/** Device Specific Peripheral registers structures */

/**
  * @brief DMA Controller
  */
typedef struct
{
  __I  uint32_t INTSTATUS;         /*!< DMAC Interrupt status register               */
  __I  uint32_t INTTCSTATUS;       /*!< DMAC Interrupt Terminal Count Status Register*/
  __O  uint32_t INTTCCLEAR;        /*!< DMAC Interrupt Terminal Count Clear Register */
  __I  uint32_t INTERRORSTATUS;    /*!< DMAC Interrupt Error Status Register         */
  __O  uint32_t INTERRCLR;         /*!< DMAC Interrupt Error Clear Register          */
  __I  uint32_t RAWINTTCSTATUS;    /*!< DMAC Raw Interrupt Terminal Count Status Register*/
  __I  uint32_t RAWINTERRORSTATUS; /*!< DMAC Raw Error Interrupt Status Register     */
  __I  uint32_t ENBLDCHNS;         /*!< DMAC Enabled Channel Register                */
  __IO uint32_t SOFTBREQ;          /*!< DMAC Software Burst Request Register         */
  __IO uint32_t SOFTSREQ;          /*!< DMAC Software Single Request Register        */
       uint32_t RESERVED0[2];
  __IO uint32_t CONFIGURATION;     /*!< DMAC Configuration Register                  */
       uint32_t RESERVED1[51];
  __IO uint32_t C0SRCADDR;         /*!< DMAC Channel0 Source Address Register        */
  __IO uint32_t C0DESTADDR;        /*!< DMAC Channel0 Destination Address Register   */
  __IO uint32_t C0LLI;             /*!< DMAC Channel0 Linked List Item Register      */
  __IO uint32_t C0CONTROL;         /*!< DMAC Channel0 Control Register               */
  __IO uint32_t C0CONFIGURATION;   /*!< DMAC Channel0 Configuration Register         */
       uint32_t RESERVED2[3];
  __IO uint32_t C1SRCADDR;         /*!< DMAC Channel1 Source Address Register        */
  __IO uint32_t C1DESTADDR;        /*!< DMAC Channel1 Destination Address Register   */
  __IO uint32_t C1LLI;             /*!< DMAC Channel1 Linked List Item Register      */
  __IO uint32_t C1CONTROL;         /*!< DMAC Channel1 Control Register               */
  __IO uint32_t C1CONFIGURATION;   /*!< DMAC Channel1 Configuration Register         */
} TSB_DMAC_TypeDef;

/**
  * @brief DMAC Request Control
  */
typedef struct
{
  __IO uint32_t REDGE;             /*!< DMAC Request Edge setting Register           */
  __O  uint32_t RCLR;              /*!< DMAC Request Clear Register                  */
} TSB_DMACRQ_TypeDef;

/**
  * @brief 16-bit TimerA
  */
typedef struct
{
  __IO uint32_t EN;                /*!< Enable Register                              */
  __IO uint32_t RUN;               /*!< RUN Register                                 */
  __IO uint32_t CR;                /*!< Control Register                             */
  __IO uint32_t RG;                /*!< Timer Register                               */
  __I  uint32_t CP;                /*!< Capture Register                             */
} TSB_T16A_TypeDef;

#if defined ( __CC_ARM   )           /* RealView Compiler */
#pragma anon_unions
#elif (defined (__ICCARM__))         /*  ICC Compiler     */
#pragma language=extended
#endif

/**
  * @brief I2C 
  */
typedef struct
{
  __IO uint32_t CR1;               /*!< I2C Control Register 1                       */
  __IO uint32_t DBR;               /*!< Data Buffer Register                         */
  __IO uint32_t AR;                /*!< Bus address Register                         */
union {
  __O  uint32_t CR2;               /*!< Control Register 2                          */
  __I  uint32_t SR;                /*!< Status Register                              */
  };
  __IO uint32_t PRS;               /*!< Prescaler clcok setting Register             */
  __IO uint32_t IE;                /*!< Interrupt Enable Register                    */
  __IO uint32_t IR;                /*!< Interrupt Register                           */
} TSB_I2C_TypeDef;

/**
  * @brief Port A
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PA Data Register                             */
  __IO uint32_t CR;                /*!< PA Control Register                          */
       uint32_t RESERVED0[8];
  __IO uint32_t OD;                /*!< PA Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PA Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PA Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PA Input Enable Control Register             */
} TSB_PA_TypeDef;

/**
  * @brief Port B
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PB Data Register                             */
  __IO uint32_t CR;                /*!< PB Control Register                          */
  __IO uint32_t FR1;               /*!< PB Function Register 1                       */
  __IO uint32_t FR2;               /*!< PB Function Register 2                       */
       uint32_t RESERVED0[6];
  __IO uint32_t OD;                /*!< PB Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PB Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PB Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PB Input Enable Control Register             */
} TSB_PB_TypeDef;

/**
  * @brief Port C
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PC Data Register                             */
  __IO uint32_t CR;                /*!< PC Control Register                          */
  __IO uint32_t FR1;               /*!< PC Function Register 1                       */
       uint32_t RESERVED0[7];
  __IO uint32_t OD;                /*!< PC Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PC Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PC Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PC Input Enable Control Register             */
} TSB_PC_TypeDef;

/**
  * @brief Port D
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PD Data Register                             */
  __IO uint32_t CR;                /*!< PD Control Register                          */
  __IO uint32_t FR1;               /*!< PD Function Register 1                       */
       uint32_t RESERVED0[7];
  __IO uint32_t OD;                /*!< PD Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PD Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PD Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PD Input Enable Control Register             */
} TSB_PD_TypeDef;

/**
  * @brief Port E
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PE Data Register                             */
  __IO uint32_t CR;                /*!< PE Control Register                          */
  __IO uint32_t FR1;               /*!< PE Function Register 1                       */
       uint32_t RESERVED0[7];
  __IO uint32_t OD;                /*!< PE Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PE Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PE Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PE Input Enable Control Register             */
} TSB_PE_TypeDef;

/**
  * @brief Port F 
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PF Data Register                             */
  __IO uint32_t CR;                /*!< PF Control Register                          */
  __IO uint32_t FR1;               /*!< PF Function Register 1                       */
       uint32_t RESERVED0[7];
  __IO uint32_t OD;                /*!< PF Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PF Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PF Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PF Input Enable Control Register             */
} TSB_PF_TypeDef;

/**
  * @brief Port G
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< PG Data Register                             */
  __IO uint32_t CR;                /*!< PG Control Register                          */
  __IO uint32_t FR1;               /*!< PG Function Register 1                       */
       uint32_t RESERVED0[7];
  __IO uint32_t OD;                /*!< PG Open Drain Control Register               */
  __IO uint32_t PUP;               /*!< PG Pull-up Control Register                  */
  __IO uint32_t PDN;               /*!< PG Pull-Down Control Register                */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< PG Input Enable Control Register             */
} TSB_PG_TypeDef;

/**
  * @brief 16-bit Timer/Event Counter (TB)
  */
typedef struct
{
  __IO uint32_t EN;                /*!< TB Enable Register                           */
  __IO uint32_t RUN;               /*!< TB RUN Register                              */
  __IO uint32_t CR;                /*!< TB Control Register                          */
  __IO uint32_t MOD;               /*!< TB Mode Register                             */
  __IO uint32_t FFCR;              /*!< TB Flip-Flop Control Register                */
  __I  uint32_t ST;                /*!< TB Status Register                           */
  __IO uint32_t IM;                /*!< TB Interrupt Mask Register                   */
  __I  uint32_t UC;                /*!< TB Read Capture Register                     */
  __IO uint32_t RG0;               /*!< TB RG0 Timer Register                        */
  __IO uint32_t RG1;               /*!< TB RG1 Timer Register                        */
  __I  uint32_t CP0;               /*!< TB CP0 Capture Register                      */
  __I  uint32_t CP1;               /*!< TB CP1 Capture Register                      */
  __IO uint32_t DMA;               /*!< TB DMA Enable Register                       */
} TSB_TB_TypeDef;

/**
  * @brief SC
  */
typedef struct
{
  __IO uint32_t EN;                /*!< SC Enable Register                           */
  __IO uint32_t BUF;               /*!< SC Buffer Register                           */
  __IO uint32_t CR;                /*!< SC Control Register                          */
  __IO uint32_t MOD0;              /*!< SC Mode Control Register 0                   */
  __IO uint32_t BRCR;              /*!< SC Baud Rate Generator Control Register      */
  __IO uint32_t BRADD;             /*!< SC Baud Rate Generator Control Register 2    */
  __IO uint32_t MOD1;              /*!< SC Mode Control Register 1                   */
  __IO uint32_t MOD2;              /*!< SC Mode Control Register 2                   */
  __IO uint32_t RFC;               /*!< SC RX FIFO Configuration Register            */
  __IO uint32_t TFC;               /*!< SC TX FIFO Configuration Register            */
  __I  uint32_t RST;               /*!< SC RX FIFO Status Register                   */
  __I  uint32_t TST;               /*!< SC TX FIFO Status Register                   */
  __IO uint32_t FCNF;              /*!< SC FIFO Configuration Register               */
  __IO uint32_t DMA;               /*!< SC DMA Request Register                      */
} TSB_SC_TypeDef;

/**
  * @brief WDT
  */
typedef struct
{
  __IO uint32_t MOD;               /*!< WD Mode Register                             */
  __O  uint32_t CR;                /*!< WD Control Register                          */
} TSB_WD_TypeDef;

/**
  * @brief CG
  */
typedef struct
{
  __IO uint32_t SYSCR;             /*!< System Control Register                      */
  __IO uint32_t OSCCR;             /*!< Oscillation Control Register                 */
  __IO uint32_t STBYCR;            /*!< Standby Control Register                     */
  __IO uint32_t PLLSEL;            /*!< PLL Selection Register                       */
       uint32_t RESERVED0[11];
  __IO uint32_t PROTECT;           /*!< Protect Register                             */
  __IO uint32_t IMCGA;             /*!< CG Interrupt Mode Control Register A         */
  __IO uint32_t IMCGB;             /*!< CG Interrupt Mode Control Register B         */
       uint32_t RESERVED1[6];
  __O  uint32_t ICRCG;             /*!< CG Interrupt Request Clear Register          */
  __IO uint32_t RSTFLG;            /*!< Reset Flag Register                          */
  __I  uint32_t NMIFLG;            /*!< NMI Flag Register                            */
} TSB_CG_TypeDef;

/**
  * @brief LVD
  */
typedef struct
{
       uint32_t RESERVED0;
  __IO uint32_t CR1;               /*!< LVD Control register                         */
} TSB_LVD_TypeDef;

/**
  * @brief ADC
  */
typedef struct
{
  __IO uint32_t CLK;               /*!< AD Conversion Clock Setting Register         */
  __IO uint32_t MOD0;              /*!< AD Mode Control Register 0                   */
  __IO uint32_t MOD1;              /*!< AD Mode Control Register 1                   */
  __IO uint32_t MOD2;              /*!< AD Mode Control Register 2                   */
  __IO uint32_t MOD3;              /*!< AD Mode Control Register 3                   */
  __IO uint32_t MOD4;              /*!< AD Mode Control Register 4                   */
  __IO uint32_t MOD5;              /*!< AD Mode Control Register 5                   */
  __IO uint32_t MOD6;              /*!< AD Mode Control Register 6                   */
       uint32_t RESERVED0[4];
  __I  uint32_t REG0;              /*!< AD Conversion Result Register 0              */
  __I  uint32_t REG1;              /*!< AD Conversion Result Register 1              */
  __I  uint32_t REG2;              /*!< AD Conversion Result Register 2              */
  __I  uint32_t REG3;              /*!< AD Conversion Result Register 3              */
  __I  uint32_t REG4;              /*!< AD Conversion Result Register 4              */
  __I  uint32_t REG5;              /*!< AD Conversion Result Register 5              */
  __I  uint32_t REG6;              /*!< AD Conversion Result Register 6              */
  __I  uint32_t REG7;              /*!< AD Conversion Result Register 7              */
       uint32_t RESERVED1[4];
  __I  uint32_t REGSP;             /*!< AD Conversion Result Register SP             */
  __IO uint32_t CMP0;              /*!< AD Conversion Result comparing register0     */
  __IO uint32_t CMP1;              /*!< AD Conversion result comparing register1     */
} TSB_AD_TypeDef;

/**
  * @brief FC
  */
typedef struct
{
       uint32_t RESERVED0[4];
  __IO uint32_t SECBIT;            /*!< FC Security Bit Register                     */
       uint32_t RESERVED1[3];
  __I  uint32_t SR;                /*!< FC Flash Status Register                     */
       uint32_t RESERVED2[3];
  __I  uint32_t PSRA;              /*!< FC Protect status register                   */
} TSB_FC_TypeDef;


/* Memory map */
#define FLASH_BASE            (0x00000000UL)
#define RAM_BASE              (0x20000000UL)
#define PERI_BASE             (0x40000000UL)


#define TSB_DMAC_BASE              (PERI_BASE  + 0x0000000UL)
#define TSB_DMACRQ_BASE            (PERI_BASE  + 0x005F000UL)
#define TSB_T16A0_BASE             (PERI_BASE  + 0x008D000UL)
#define TSB_T16A1_BASE             (PERI_BASE  + 0x008E000UL)
#define TSB_I2C_BASE               (PERI_BASE  + 0x00A0000UL)
#define TSB_PA_BASE                (PERI_BASE  + 0x00C0000UL)
#define TSB_PB_BASE                (PERI_BASE  + 0x00C0100UL)
#define TSB_PC_BASE                (PERI_BASE  + 0x00C0200UL)
#define TSB_PD_BASE                (PERI_BASE  + 0x00C0300UL)
#define TSB_PE_BASE                (PERI_BASE  + 0x00C0400UL)
#define TSB_PF_BASE                (PERI_BASE  + 0x00C0500UL)
#define TSB_PG_BASE                (PERI_BASE  + 0x00C0600UL)
#define TSB_TB0_BASE               (PERI_BASE  + 0x00C4000UL)
#define TSB_TB1_BASE               (PERI_BASE  + 0x00C4100UL)
#define TSB_TB2_BASE               (PERI_BASE  + 0x00C4200UL)
#define TSB_TB3_BASE               (PERI_BASE  + 0x00C4300UL)
#define TSB_TB4_BASE               (PERI_BASE  + 0x00C4400UL)
#define TSB_TB5_BASE               (PERI_BASE  + 0x00C4500UL)
#define TSB_TB6_BASE               (PERI_BASE  + 0x00C4600UL)
#define TSB_TB7_BASE               (PERI_BASE  + 0x00C4700UL)
#define TSB_SC0_BASE               (PERI_BASE  + 0x00E1000UL)
#define TSB_SC1_BASE               (PERI_BASE  + 0x00E1100UL)
#define TSB_SC2_BASE               (PERI_BASE  + 0x00E1200UL)
#define TSB_SC3_BASE               (PERI_BASE  + 0x00E1300UL)
#define TSB_SC4_BASE               (PERI_BASE  + 0x00E1400UL)
#define TSB_WD_BASE                (PERI_BASE  + 0x00F2000UL)
#define TSB_CG_BASE                (PERI_BASE  + 0x00F3000UL)
#define TSB_LVD_BASE               (PERI_BASE  + 0x00F4000UL)
#define TSB_AD_BASE                (PERI_BASE  + 0x00FC000UL)
#define TSB_FC_BASE                (PERI_BASE  + 0x1FFF000UL)


/* Peripheral declaration */
#define TSB_DMAC                   ((   TSB_DMAC_TypeDef *)  TSB_DMAC_BASE)
#define TSB_DMACRQ                 (( TSB_DMACRQ_TypeDef *)TSB_DMACRQ_BASE)
#define TSB_T16A0                  ((   TSB_T16A_TypeDef *) TSB_T16A0_BASE)
#define TSB_T16A1                  ((   TSB_T16A_TypeDef *) TSB_T16A1_BASE)
#define TSB_I2C                    ((    TSB_I2C_TypeDef *)   TSB_I2C_BASE)
#define TSB_PA                     ((     TSB_PA_TypeDef *)    TSB_PA_BASE)
#define TSB_PB                     ((     TSB_PB_TypeDef *)    TSB_PB_BASE)
#define TSB_PC                     ((     TSB_PC_TypeDef *)    TSB_PC_BASE)
#define TSB_PD                     ((     TSB_PD_TypeDef *)    TSB_PD_BASE)
#define TSB_PE                     ((     TSB_PE_TypeDef *)    TSB_PE_BASE)
#define TSB_PF                     ((     TSB_PF_TypeDef *)    TSB_PF_BASE)
#define TSB_PG                     ((     TSB_PG_TypeDef *)    TSB_PG_BASE)
#define TSB_TB0                    ((     TSB_TB_TypeDef *)   TSB_TB0_BASE)
#define TSB_TB1                    ((     TSB_TB_TypeDef *)   TSB_TB1_BASE)
#define TSB_TB2                    ((     TSB_TB_TypeDef *)   TSB_TB2_BASE)
#define TSB_TB3                    ((     TSB_TB_TypeDef *)   TSB_TB3_BASE)
#define TSB_TB4                    ((     TSB_TB_TypeDef *)   TSB_TB4_BASE)
#define TSB_TB5                    ((     TSB_TB_TypeDef *)   TSB_TB5_BASE)
#define TSB_TB6                    ((     TSB_TB_TypeDef *)   TSB_TB6_BASE)
#define TSB_TB7                    ((     TSB_TB_TypeDef *)   TSB_TB7_BASE)
#define TSB_SC0                    ((     TSB_SC_TypeDef *)   TSB_SC0_BASE)
#define TSB_SC1                    ((     TSB_SC_TypeDef *)   TSB_SC1_BASE)
#define TSB_SC2                    ((     TSB_SC_TypeDef *)   TSB_SC2_BASE)
#define TSB_SC3                    ((     TSB_SC_TypeDef *)   TSB_SC3_BASE)
#define TSB_SC4                    ((     TSB_SC_TypeDef *)   TSB_SC4_BASE)
#define TSB_WD                     ((     TSB_WD_TypeDef *)    TSB_WD_BASE)
#define TSB_CG                     ((     TSB_CG_TypeDef *)    TSB_CG_BASE)
#define TSB_LVD                    ((    TSB_LVD_TypeDef *)   TSB_LVD_BASE)
#define TSB_AD                     ((     TSB_AD_TypeDef *)    TSB_AD_BASE)
#define TSB_FC                     ((     TSB_FC_TypeDef *)    TSB_FC_BASE)


/* Bit-Band for Device Specific Peripheral Registers */
#define BITBAND_OFFSET (0x02000000UL)
#define BITBAND_PERI_BASE (PERI_BASE + BITBAND_OFFSET)
#define BITBAND_PERI(addr, bitnum) (BITBAND_PERI_BASE + (((uint32_t)(addr) - PERI_BASE) << 5) + ((uint32_t)(bitnum) << 2))


/* DMA Controller */
#define TSB_DMAC_INTSTATUS_INTSTATUS0             (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTSTATUS,0)))
#define TSB_DMAC_INTSTATUS_INTSTATUS1             (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTSTATUS,1)))
#define TSB_DMAC_INTTCSTATUS_INTTCSTATUS0         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTTCSTATUS,0)))
#define TSB_DMAC_INTTCSTATUS_INTTCSTATUS1         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTTCSTATUS,1)))
#define TSB_DMAC_INTERRORSTATUS_INTERRSTATUS0     (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTERRORSTATUS,0)))
#define TSB_DMAC_INTERRORSTATUS_INTERRSTATUS1     (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->INTERRORSTATUS,1)))
#define TSB_DMAC_RAWINTTCSTATUS_RAWINTTCS0        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->RAWINTTCSTATUS,0)))
#define TSB_DMAC_RAWINTTCSTATUS_RAWINTTCS1        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->RAWINTTCSTATUS,1)))
#define TSB_DMAC_RAWINTERRORSTATUS_RAWINTERRS0    (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->RAWINTERRORSTATUS,0)))
#define TSB_DMAC_RAWINTERRORSTATUS_RAWINTERRS1    (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->RAWINTERRORSTATUS,1)))
#define TSB_DMAC_ENBLDCHNS_ENABLEDCH0             (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->ENBLDCHNS,0)))
#define TSB_DMAC_ENBLDCHNS_ENABLEDCH1             (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->ENBLDCHNS,1)))
#define TSB_DMAC_C0CONTROL_SI                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONTROL,26)))
#define TSB_DMAC_C0CONTROL_DI                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONTROL,27)))
#define TSB_DMAC_C0CONTROL_I                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONTROL,31)))
#define TSB_DMAC_C0CONFIGURATION_E                (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,0)))
#define TSB_DMAC_C0CONFIGURATION_IE               (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,14)))
#define TSB_DMAC_C0CONFIGURATION_ITC              (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,15)))
#define TSB_DMAC_C0CONFIGURATION_LOCK             (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,16)))
#define TSB_DMAC_C0CONFIGURATION_ACTIVE           (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,17)))
#define TSB_DMAC_C0CONFIGURATION_HALT             (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C0CONFIGURATION,18)))
#define TSB_DMAC_C1CONTROL_SI                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONTROL,26)))
#define TSB_DMAC_C1CONTROL_DI                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONTROL,27)))
#define TSB_DMAC_C1CONTROL_I                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONTROL,31)))
#define TSB_DMAC_C1CONFIGURATION_E                (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,0)))
#define TSB_DMAC_C1CONFIGURATION_IE               (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,14)))
#define TSB_DMAC_C1CONFIGURATION_ITC              (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,15)))
#define TSB_DMAC_C1CONFIGURATION_LOCK             (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,16)))
#define TSB_DMAC_C1CONFIGURATION_ACTIVE           (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,17)))
#define TSB_DMAC_C1CONFIGURATION_HALT             (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAC->C1CONFIGURATION,18)))

/* 16-bit TimerA */
#define TSB_T16A0_EN_I2T16A                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->EN,0)))
#define TSB_T16A0_EN_HALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->EN,1)))
#define TSB_T16A0_RUN_RUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->RUN,0)))
#define TSB_T16A0_CR_CLK                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->CR,0)))
#define TSB_T16A0_CR_FFEN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->CR,7)))

#define TSB_T16A1_EN_I2T16A                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A1->EN,0)))
#define TSB_T16A1_EN_HALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A1->EN,1)))
#define TSB_T16A1_RUN_RUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A1->RUN,0)))
#define TSB_T16A1_CR_CLK                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A1->CR,0)))
#define TSB_T16A1_CR_FFEN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A1->CR,7)))


/* I2C  */
#define TSB_I2C_CR1_NOACK                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_I2C->CR1,3)))
#define TSB_I2C_CR1_ACK                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_I2C->CR1,4)))
#define TSB_I2C_AR_ALS                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_I2C->AR,0)))
#define TSB_I2C_CR2_I2CM                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_I2C->CR2,3)))
#define TSB_I2C_CR2_PIN                           (*((__O  uint32_t *)BITBAND_PERI(&TSB_I2C->CR2,4)))
#define TSB_I2C_CR2_BB                            (*((__O  uint32_t *)BITBAND_PERI(&TSB_I2C->CR2,5)))
#define TSB_I2C_CR2_TRX                           (*((__O  uint32_t *)BITBAND_PERI(&TSB_I2C->CR2,6)))
#define TSB_I2C_CR2_MST                           (*((__O  uint32_t *)BITBAND_PERI(&TSB_I2C->CR2,7)))
#define TSB_I2C_SR_LRB                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,0)))
#define TSB_I2C_SR_ADO                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,1)))
#define TSB_I2C_SR_AAS                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,2)))
#define TSB_I2C_SR_AL                             (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,3)))
#define TSB_I2C_SR_PIN                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,4)))
#define TSB_I2C_SR_BB                             (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,5)))
#define TSB_I2C_SR_TRX                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,6)))
#define TSB_I2C_SR_MST                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_I2C->SR,7)))
#define TSB_I2C_IE_IE                             (*((__IO uint32_t *)BITBAND_PERI(&TSB_I2C->IE,0)))
#define TSB_I2C_IR_ISIC                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_I2C->IR,0)))


/* Port A */
#define TSB_PA_DATA_PA0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,0)))
#define TSB_PA_DATA_PA1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,1)))
#define TSB_PA_DATA_PA2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,2)))
#define TSB_PA_DATA_PA3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,3)))
#define TSB_PA_DATA_PA4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,4)))
#define TSB_PA_DATA_PA5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,5)))
#define TSB_PA_DATA_PA6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,6)))
#define TSB_PA_DATA_PA7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,7)))
#define TSB_PA_CR_PA0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,0)))
#define TSB_PA_CR_PA1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,1)))
#define TSB_PA_CR_PA2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,2)))
#define TSB_PA_CR_PA3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,3)))
#define TSB_PA_CR_PA4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,4)))
#define TSB_PA_CR_PA5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,5)))
#define TSB_PA_CR_PA6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,6)))
#define TSB_PA_CR_PA7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,7)))
#define TSB_PA_OD_PA0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,0)))
#define TSB_PA_OD_PA1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,1)))
#define TSB_PA_OD_PA2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,2)))
#define TSB_PA_OD_PA3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,3)))
#define TSB_PA_OD_PA4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,4)))
#define TSB_PA_OD_PA5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,5)))
#define TSB_PA_OD_PA6OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,6)))
#define TSB_PA_OD_PA7OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->OD,7)))
#define TSB_PA_PUP_PA0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,0)))
#define TSB_PA_PUP_PA1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,1)))
#define TSB_PA_PUP_PA2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,2)))
#define TSB_PA_PUP_PA3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,3)))
#define TSB_PA_PUP_PA4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,4)))
#define TSB_PA_PUP_PA5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,5)))
#define TSB_PA_PUP_PA6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,6)))
#define TSB_PA_PUP_PA7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,7)))
#define TSB_PA_PDN_PA0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,0)))
#define TSB_PA_PDN_PA1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,1)))
#define TSB_PA_PDN_PA2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,2)))
#define TSB_PA_PDN_PA3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,3)))
#define TSB_PA_PDN_PA4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,4)))
#define TSB_PA_PDN_PA5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,5)))
#define TSB_PA_PDN_PA6DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,6)))
#define TSB_PA_PDN_PA7DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PDN,7)))
#define TSB_PA_IE_PA0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,0)))
#define TSB_PA_IE_PA1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,1)))
#define TSB_PA_IE_PA2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,2)))
#define TSB_PA_IE_PA3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,3)))
#define TSB_PA_IE_PA4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,4)))
#define TSB_PA_IE_PA5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,5)))
#define TSB_PA_IE_PA6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,6)))
#define TSB_PA_IE_PA7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,7)))


/* Port B */
#define TSB_PB_DATA_PB0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,0)))
#define TSB_PB_DATA_PB1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,1)))
#define TSB_PB_DATA_PB2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,2)))
#define TSB_PB_DATA_PB3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,3)))
#define TSB_PB_DATA_PB4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,4)))
#define TSB_PB_DATA_PB5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,5)))
#define TSB_PB_DATA_PB6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,6)))
#define TSB_PB_DATA_PB7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,7)))
#define TSB_PB_CR_PB0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,0)))
#define TSB_PB_CR_PB1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,1)))
#define TSB_PB_CR_PB2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,2)))
#define TSB_PB_CR_PB3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,3)))
#define TSB_PB_CR_PB4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,4)))
#define TSB_PB_CR_PB5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,5)))
#define TSB_PB_CR_PB6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,6)))
#define TSB_PB_CR_PB7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,7)))
#define TSB_PB_FR1_PB1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,1)))
#define TSB_PB_FR1_PB2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,2)))
#define TSB_PB_FR1_PB3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,3)))
#define TSB_PB_FR2_PB1F2                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR2,1)))
#define TSB_PB_FR2_PB2F2                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR2,2)))
#define TSB_PB_OD_PB0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,0)))
#define TSB_PB_OD_PB1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,1)))
#define TSB_PB_OD_PB2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,2)))
#define TSB_PB_OD_PB3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,3)))
#define TSB_PB_OD_PB4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,4)))
#define TSB_PB_OD_PB5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,5)))
#define TSB_PB_OD_PB6OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,6)))
#define TSB_PB_OD_PB7OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->OD,7)))
#define TSB_PB_PUP_PB0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,0)))
#define TSB_PB_PUP_PB1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,1)))
#define TSB_PB_PUP_PB2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,2)))
#define TSB_PB_PUP_PB3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,3)))
#define TSB_PB_PUP_PB4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,4)))
#define TSB_PB_PUP_PB5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,5)))
#define TSB_PB_PUP_PB6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,6)))
#define TSB_PB_PUP_PB7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,7)))
#define TSB_PB_PDN_PB0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,0)))
#define TSB_PB_PDN_PB1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,1)))
#define TSB_PB_PDN_PB2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,2)))
#define TSB_PB_PDN_PB3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,3)))
#define TSB_PB_PDN_PB4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,4)))
#define TSB_PB_PDN_PB5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,5)))
#define TSB_PB_PDN_PB6DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,6)))
#define TSB_PB_PDN_PB7DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PDN,7)))
#define TSB_PB_IE_PB0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,0)))
#define TSB_PB_IE_PB1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,1)))
#define TSB_PB_IE_PB2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,2)))
#define TSB_PB_IE_PB3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,3)))
#define TSB_PB_IE_PB4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,4)))
#define TSB_PB_IE_PB5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,5)))
#define TSB_PB_IE_PB6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,6)))
#define TSB_PB_IE_PB7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,7)))


/* Port C */
#define TSB_PC_DATA_PC0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,0)))
#define TSB_PC_DATA_PC1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,1)))
#define TSB_PC_DATA_PC2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,2)))
#define TSB_PC_DATA_PC3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,3)))
#define TSB_PC_DATA_PC4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,4)))
#define TSB_PC_DATA_PC5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,5)))
#define TSB_PC_CR_PC0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,0)))
#define TSB_PC_CR_PC1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,1)))
#define TSB_PC_CR_PC2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,2)))
#define TSB_PC_CR_PC3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,3)))
#define TSB_PC_CR_PC4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,4)))
#define TSB_PC_CR_PC5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,5)))
#define TSB_PC_FR1_PC0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,0)))
#define TSB_PC_FR1_PC1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,1)))
#define TSB_PC_FR1_PC2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,2)))
#define TSB_PC_FR1_PC3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,3)))
#define TSB_PC_FR1_PC4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,4)))
#define TSB_PC_FR1_PC5F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,5)))
#define TSB_PC_OD_PC0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,0)))
#define TSB_PC_OD_PC1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,1)))
#define TSB_PC_OD_PC2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,2)))
#define TSB_PC_OD_PC3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,3)))
#define TSB_PC_OD_PC4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,4)))
#define TSB_PC_OD_PC5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->OD,5)))
#define TSB_PC_PUP_PC0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,0)))
#define TSB_PC_PUP_PC1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,1)))
#define TSB_PC_PUP_PC2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,2)))
#define TSB_PC_PUP_PC3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,3)))
#define TSB_PC_PUP_PC4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,4)))
#define TSB_PC_PUP_PC5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,5)))
#define TSB_PC_PDN_PC0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,0)))
#define TSB_PC_PDN_PC1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,1)))
#define TSB_PC_PDN_PC2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,2)))
#define TSB_PC_PDN_PC3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,3)))
#define TSB_PC_PDN_PC4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,4)))
#define TSB_PC_PDN_PC5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,5)))
#define TSB_PC_IE_PC0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,0)))
#define TSB_PC_IE_PC1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,1)))
#define TSB_PC_IE_PC2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,2)))
#define TSB_PC_IE_PC3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,3)))
#define TSB_PC_IE_PC4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,4)))
#define TSB_PC_IE_PC5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,5)))


/* Port D */
#define TSB_PD_DATA_PD0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,0)))
#define TSB_PD_DATA_PD1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,1)))
#define TSB_PD_DATA_PD2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,2)))
#define TSB_PD_DATA_PD3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,3)))
#define TSB_PD_DATA_PD4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,4)))
#define TSB_PD_DATA_PD5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,5)))
#define TSB_PD_CR_PD0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,0)))
#define TSB_PD_CR_PD1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,1)))
#define TSB_PD_CR_PD2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,2)))
#define TSB_PD_CR_PD3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,3)))
#define TSB_PD_CR_PD4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,4)))
#define TSB_PD_CR_PD5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,5)))
#define TSB_PD_FR1_PD0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->FR1,0)))
#define TSB_PD_FR1_PD1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->FR1,1)))
#define TSB_PD_FR1_PD2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->FR1,2)))
#define TSB_PD_FR1_PD3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->FR1,3)))
#define TSB_PD_FR1_PD4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->FR1,4)))
#define TSB_PD_OD_PD0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,0)))
#define TSB_PD_OD_PD1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,1)))
#define TSB_PD_OD_PD2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,2)))
#define TSB_PD_OD_PD3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,3)))
#define TSB_PD_OD_PD4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,4)))
#define TSB_PD_OD_PD5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->OD,5)))
#define TSB_PD_PUP_PD0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,0)))
#define TSB_PD_PUP_PD1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,1)))
#define TSB_PD_PUP_PD2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,2)))
#define TSB_PD_PUP_PD3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,3)))
#define TSB_PD_PUP_PD4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,4)))
#define TSB_PD_PUP_PD5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,5)))
#define TSB_PD_PDN_PD0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,0)))
#define TSB_PD_PDN_PD1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,1)))
#define TSB_PD_PDN_PD2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,2)))
#define TSB_PD_PDN_PD3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,3)))
#define TSB_PD_PDN_PD4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,4)))
#define TSB_PD_PDN_PD5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PDN,5)))
#define TSB_PD_IE_PD0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,0)))
#define TSB_PD_IE_PD1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,1)))
#define TSB_PD_IE_PD2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,2)))
#define TSB_PD_IE_PD3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,3)))
#define TSB_PD_IE_PD4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,4)))
#define TSB_PD_IE_PD5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,5)))


/* Port E */
#define TSB_PE_DATA_PE0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,0)))
#define TSB_PE_DATA_PE1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,1)))
#define TSB_PE_DATA_PE2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,2)))
#define TSB_PE_DATA_PE3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,3)))
#define TSB_PE_DATA_PE4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,4)))
#define TSB_PE_DATA_PE5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,5)))
#define TSB_PE_DATA_PE6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,6)))
#define TSB_PE_DATA_PE7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->DATA,7)))
#define TSB_PE_CR_PE0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,0)))
#define TSB_PE_CR_PE1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,1)))
#define TSB_PE_CR_PE2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,2)))
#define TSB_PE_CR_PE3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,3)))
#define TSB_PE_CR_PE4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,4)))
#define TSB_PE_CR_PE5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,5)))
#define TSB_PE_CR_PE6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,6)))
#define TSB_PE_CR_PE7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->CR,7)))
#define TSB_PE_FR1_PE2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->FR1,2)))
#define TSB_PE_FR1_PE3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->FR1,3)))
#define TSB_PE_FR1_PE4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->FR1,4)))
#define TSB_PE_OD_PE0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,0)))
#define TSB_PE_OD_PE1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,1)))
#define TSB_PE_OD_PE2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,2)))
#define TSB_PE_OD_PE3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,3)))
#define TSB_PE_OD_PE4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,4)))
#define TSB_PE_OD_PE5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,5)))
#define TSB_PE_OD_PE6OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,6)))
#define TSB_PE_OD_PE7OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->OD,7)))
#define TSB_PE_PUP_PE0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,0)))
#define TSB_PE_PUP_PE1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,1)))
#define TSB_PE_PUP_PE2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,2)))
#define TSB_PE_PUP_PE3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,3)))
#define TSB_PE_PUP_PE4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,4)))
#define TSB_PE_PUP_PE5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,5)))
#define TSB_PE_PUP_PE6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,6)))
#define TSB_PE_PUP_PE7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PUP,7)))
#define TSB_PE_PDN_PE0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,0)))
#define TSB_PE_PDN_PE1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,1)))
#define TSB_PE_PDN_PE2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,2)))
#define TSB_PE_PDN_PE3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,3)))
#define TSB_PE_PDN_PE4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,4)))
#define TSB_PE_PDN_PE5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,5)))
#define TSB_PE_PDN_PE6DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,6)))
#define TSB_PE_PDN_PE7DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->PDN,7)))
#define TSB_PE_IE_PE0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,0)))
#define TSB_PE_IE_PE1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,1)))
#define TSB_PE_IE_PE2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,2)))
#define TSB_PE_IE_PE3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,3)))
#define TSB_PE_IE_PE4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,4)))
#define TSB_PE_IE_PE5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,5)))
#define TSB_PE_IE_PE6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,6)))
#define TSB_PE_IE_PE7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PE->IE,7)))


/* Port F  */
#define TSB_PF_DATA_PF0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,0)))
#define TSB_PF_DATA_PF1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,1)))
#define TSB_PF_DATA_PF2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,2)))
#define TSB_PF_DATA_PF3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,3)))
#define TSB_PF_DATA_PF4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,4)))
#define TSB_PF_DATA_PF5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,5)))
#define TSB_PF_DATA_PF6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,6)))
#define TSB_PF_DATA_PF7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->DATA,7)))
#define TSB_PF_CR_PF0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,0)))
#define TSB_PF_CR_PF1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,1)))
#define TSB_PF_CR_PF2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,2)))
#define TSB_PF_CR_PF3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,3)))
#define TSB_PF_CR_PF4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,4)))
#define TSB_PF_CR_PF5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,5)))
#define TSB_PF_CR_PF6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,6)))
#define TSB_PF_CR_PF7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->CR,7)))
#define TSB_PF_FR1_PF0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,0)))
#define TSB_PF_FR1_PF1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,1)))
#define TSB_PF_FR1_PF2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,2)))
#define TSB_PF_FR1_PF3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,3)))
#define TSB_PF_FR1_PF4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,4)))
#define TSB_PF_FR1_PF5F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->FR1,5)))
#define TSB_PF_OD_PF0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,0)))
#define TSB_PF_OD_PF1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,1)))
#define TSB_PF_OD_PF2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,2)))
#define TSB_PF_OD_PF3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,3)))
#define TSB_PF_OD_PF4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,4)))
#define TSB_PF_OD_PF5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,5)))
#define TSB_PF_OD_PF6OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,6)))
#define TSB_PF_OD_PF7OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->OD,7)))
#define TSB_PF_PUP_PF0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,0)))
#define TSB_PF_PUP_PF1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,1)))
#define TSB_PF_PUP_PF2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,2)))
#define TSB_PF_PUP_PF3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,3)))
#define TSB_PF_PUP_PF4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,4)))
#define TSB_PF_PUP_PF5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,5)))
#define TSB_PF_PUP_PF6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,6)))
#define TSB_PF_PUP_PF7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PUP,7)))
#define TSB_PF_PDN_PF0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,0)))
#define TSB_PF_PDN_PF1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,1)))
#define TSB_PF_PDN_PF2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,2)))
#define TSB_PF_PDN_PF3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,3)))
#define TSB_PF_PDN_PF4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,4)))
#define TSB_PF_PDN_PF5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,5)))
#define TSB_PF_PDN_PF6DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,6)))
#define TSB_PF_PDN_PF7DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->PDN,7)))
#define TSB_PF_IE_PF0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,0)))
#define TSB_PF_IE_PF1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,1)))
#define TSB_PF_IE_PF2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,2)))
#define TSB_PF_IE_PF3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,3)))
#define TSB_PF_IE_PF4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,4)))
#define TSB_PF_IE_PF5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,5)))
#define TSB_PF_IE_PF6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,6)))
#define TSB_PF_IE_PF7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PF->IE,7)))


/* Port G */
#define TSB_PG_DATA_PG0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,0)))
#define TSB_PG_DATA_PG1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,1)))
#define TSB_PG_DATA_PG2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,2)))
#define TSB_PG_DATA_PG3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,3)))
#define TSB_PG_DATA_PG4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,4)))
#define TSB_PG_DATA_PG5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,5)))
#define TSB_PG_DATA_PG6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,6)))
#define TSB_PG_DATA_PG7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->DATA,7)))
#define TSB_PG_CR_PG0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,0)))
#define TSB_PG_CR_PG1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,1)))
#define TSB_PG_CR_PG2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,2)))
#define TSB_PG_CR_PG3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,3)))
#define TSB_PG_CR_PG4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,4)))
#define TSB_PG_CR_PG5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,5)))
#define TSB_PG_CR_PG6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,6)))
#define TSB_PG_CR_PG7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->CR,7)))
#define TSB_PG_FR1_PG0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,0)))
#define TSB_PG_FR1_PG1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,1)))
#define TSB_PG_FR1_PG2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,2)))
#define TSB_PG_FR1_PG3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,3)))
#define TSB_PG_FR1_PG4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,4)))
#define TSB_PG_FR1_PG5F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,5)))
#define TSB_PG_FR1_PG6F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,6)))
#define TSB_PG_FR1_PG7F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->FR1,7)))
#define TSB_PG_OD_PG0OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,0)))
#define TSB_PG_OD_PG1OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,1)))
#define TSB_PG_OD_PG2OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,2)))
#define TSB_PG_OD_PG3OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,3)))
#define TSB_PG_OD_PG4OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,4)))
#define TSB_PG_OD_PG5OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,5)))
#define TSB_PG_OD_PG6OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,6)))
#define TSB_PG_OD_PG7OD                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->OD,7)))
#define TSB_PG_PUP_PG0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,0)))
#define TSB_PG_PUP_PG1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,1)))
#define TSB_PG_PUP_PG2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,2)))
#define TSB_PG_PUP_PG3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,3)))
#define TSB_PG_PUP_PG4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,4)))
#define TSB_PG_PUP_PG5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,5)))
#define TSB_PG_PUP_PG6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,6)))
#define TSB_PG_PUP_PG7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PUP,7)))
#define TSB_PG_PDN_PG0DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,0)))
#define TSB_PG_PDN_PG1DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,1)))
#define TSB_PG_PDN_PG2DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,2)))
#define TSB_PG_PDN_PG3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,3)))
#define TSB_PG_PDN_PG4DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,4)))
#define TSB_PG_PDN_PG5DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,5)))
#define TSB_PG_PDN_PG6DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,6)))
#define TSB_PG_PDN_PG7DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->PDN,7)))
#define TSB_PG_IE_PG0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,0)))
#define TSB_PG_IE_PG1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,1)))
#define TSB_PG_IE_PG2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,2)))
#define TSB_PG_IE_PG3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,3)))
#define TSB_PG_IE_PG4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,4)))
#define TSB_PG_IE_PG5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,5)))
#define TSB_PG_IE_PG6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,6)))
#define TSB_PG_IE_PG7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PG->IE,7)))


/* 16-bit Timer/Event Counter (TB) */
#define TSB_TB0_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->EN,6)))
#define TSB_TB0_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->EN,7)))
#define TSB_TB0_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->RUN,0)))
#define TSB_TB0_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->RUN,2)))
#define TSB_TB0_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,0)))
#define TSB_TB0_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,1)))
#define TSB_TB0_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,3)))
#define TSB_TB0_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,5)))
#define TSB_TB0_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,7)))
#define TSB_TB0_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->MOD,3)))
#define TSB_TB0_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB0->MOD,6)))
#define TSB_TB0_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,2)))
#define TSB_TB0_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,3)))
#define TSB_TB0_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,4)))
#define TSB_TB0_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,5)))
#define TSB_TB0_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,0)))
#define TSB_TB0_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,1)))
#define TSB_TB0_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,2)))
#define TSB_TB0_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->DMA,0)))
#define TSB_TB0_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->DMA,1)))
#define TSB_TB0_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->DMA,2)))

#define TSB_TB1_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->EN,6)))
#define TSB_TB1_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->EN,7)))
#define TSB_TB1_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->RUN,0)))
#define TSB_TB1_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->RUN,2)))
#define TSB_TB1_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,0)))
#define TSB_TB1_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,1)))
#define TSB_TB1_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,3)))
#define TSB_TB1_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,5)))
#define TSB_TB1_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,7)))
#define TSB_TB1_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->MOD,3)))
#define TSB_TB1_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB1->MOD,6)))
#define TSB_TB1_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,2)))
#define TSB_TB1_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,3)))
#define TSB_TB1_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,4)))
#define TSB_TB1_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,5)))
#define TSB_TB1_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,0)))
#define TSB_TB1_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,1)))
#define TSB_TB1_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,2)))
#define TSB_TB1_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->DMA,0)))
#define TSB_TB1_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->DMA,1)))
#define TSB_TB1_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->DMA,2)))

#define TSB_TB2_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->EN,6)))
#define TSB_TB2_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->EN,7)))
#define TSB_TB2_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->RUN,0)))
#define TSB_TB2_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->RUN,2)))
#define TSB_TB2_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,0)))
#define TSB_TB2_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,1)))
#define TSB_TB2_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,3)))
#define TSB_TB2_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,5)))
#define TSB_TB2_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,7)))
#define TSB_TB2_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->MOD,3)))
#define TSB_TB2_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB2->MOD,6)))
#define TSB_TB2_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,2)))
#define TSB_TB2_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,3)))
#define TSB_TB2_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,4)))
#define TSB_TB2_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,5)))
#define TSB_TB2_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,0)))
#define TSB_TB2_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,1)))
#define TSB_TB2_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,2)))
#define TSB_TB2_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->DMA,0)))
#define TSB_TB2_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->DMA,1)))
#define TSB_TB2_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->DMA,2)))

#define TSB_TB3_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->EN,6)))
#define TSB_TB3_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->EN,7)))
#define TSB_TB3_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->RUN,0)))
#define TSB_TB3_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->RUN,2)))
#define TSB_TB3_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,0)))
#define TSB_TB3_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,1)))
#define TSB_TB3_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,3)))
#define TSB_TB3_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,5)))
#define TSB_TB3_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,7)))
#define TSB_TB3_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->MOD,3)))
#define TSB_TB3_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB3->MOD,6)))
#define TSB_TB3_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,2)))
#define TSB_TB3_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,3)))
#define TSB_TB3_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,4)))
#define TSB_TB3_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,5)))
#define TSB_TB3_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,0)))
#define TSB_TB3_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,1)))
#define TSB_TB3_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,2)))
#define TSB_TB3_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->DMA,0)))
#define TSB_TB3_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->DMA,1)))
#define TSB_TB3_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->DMA,2)))

#define TSB_TB4_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->EN,6)))
#define TSB_TB4_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->EN,7)))
#define TSB_TB4_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->RUN,0)))
#define TSB_TB4_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->RUN,2)))
#define TSB_TB4_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->CR,0)))
#define TSB_TB4_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->CR,1)))
#define TSB_TB4_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->CR,3)))
#define TSB_TB4_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->CR,5)))
#define TSB_TB4_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->CR,7)))
#define TSB_TB4_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->MOD,3)))
#define TSB_TB4_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB4->MOD,6)))
#define TSB_TB4_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->FFCR,2)))
#define TSB_TB4_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->FFCR,3)))
#define TSB_TB4_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->FFCR,4)))
#define TSB_TB4_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->FFCR,5)))
#define TSB_TB4_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->IM,0)))
#define TSB_TB4_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->IM,1)))
#define TSB_TB4_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->IM,2)))
#define TSB_TB4_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->DMA,0)))
#define TSB_TB4_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->DMA,1)))
#define TSB_TB4_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB4->DMA,2)))

#define TSB_TB5_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->EN,6)))
#define TSB_TB5_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->EN,7)))
#define TSB_TB5_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->RUN,0)))
#define TSB_TB5_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->RUN,2)))
#define TSB_TB5_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->CR,0)))
#define TSB_TB5_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->CR,1)))
#define TSB_TB5_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->CR,3)))
#define TSB_TB5_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->CR,5)))
#define TSB_TB5_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->CR,7)))
#define TSB_TB5_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->MOD,3)))
#define TSB_TB5_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB5->MOD,6)))
#define TSB_TB5_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->FFCR,2)))
#define TSB_TB5_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->FFCR,3)))
#define TSB_TB5_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->FFCR,4)))
#define TSB_TB5_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->FFCR,5)))
#define TSB_TB5_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->IM,0)))
#define TSB_TB5_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->IM,1)))
#define TSB_TB5_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->IM,2)))
#define TSB_TB5_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->DMA,0)))
#define TSB_TB5_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->DMA,1)))
#define TSB_TB5_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB5->DMA,2)))

#define TSB_TB6_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->EN,6)))
#define TSB_TB6_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->EN,7)))
#define TSB_TB6_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->RUN,0)))
#define TSB_TB6_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->RUN,2)))
#define TSB_TB6_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->CR,0)))
#define TSB_TB6_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->CR,1)))
#define TSB_TB6_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->CR,3)))
#define TSB_TB6_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->CR,5)))
#define TSB_TB6_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->CR,7)))
#define TSB_TB6_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->MOD,3)))
#define TSB_TB6_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB6->MOD,6)))
#define TSB_TB6_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->FFCR,2)))
#define TSB_TB6_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->FFCR,3)))
#define TSB_TB6_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->FFCR,4)))
#define TSB_TB6_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->FFCR,5)))
#define TSB_TB6_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->IM,0)))
#define TSB_TB6_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->IM,1)))
#define TSB_TB6_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->IM,2)))
#define TSB_TB6_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->DMA,0)))
#define TSB_TB6_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->DMA,1)))
#define TSB_TB6_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB6->DMA,2)))

#define TSB_TB7_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->EN,6)))
#define TSB_TB7_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->EN,7)))
#define TSB_TB7_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->RUN,0)))
#define TSB_TB7_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->RUN,2)))
#define TSB_TB7_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->CR,0)))
#define TSB_TB7_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->CR,1)))
#define TSB_TB7_CR_I2TB                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->CR,3)))
#define TSB_TB7_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->CR,5)))
#define TSB_TB7_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->CR,7)))
#define TSB_TB7_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->MOD,3)))
#define TSB_TB7_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB7->MOD,6)))
#define TSB_TB7_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->FFCR,2)))
#define TSB_TB7_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->FFCR,3)))
#define TSB_TB7_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->FFCR,4)))
#define TSB_TB7_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->FFCR,5)))
#define TSB_TB7_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->IM,0)))
#define TSB_TB7_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->IM,1)))
#define TSB_TB7_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->IM,2)))
#define TSB_TB7_DMA_TBDMAEN0                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->DMA,0)))
#define TSB_TB7_DMA_TBDMAEN1                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->DMA,1)))
#define TSB_TB7_DMA_TBDMAEN2                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB7->DMA,2)))


/* SC */
#define TSB_SC0_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->EN,0)))
#define TSB_SC0_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->EN,1)))
#define TSB_SC0_MOD0_WU                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,4)))
#define TSB_SC0_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,5)))
#define TSB_SC0_MOD0_CTSE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,6)))
#define TSB_SC0_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,7)))
#define TSB_SC0_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->BRCR,6)))
#define TSB_SC0_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD1,4)))
#define TSB_SC0_MOD1_I2SC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD1,7)))
#define TSB_SC0_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,2)))
#define TSB_SC0_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,3)))
#define TSB_SC0_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,4)))
#define TSB_SC0_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,5)))
#define TSB_SC0_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,6)))
#define TSB_SC0_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,7)))
#define TSB_SC0_RST_ROR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->RST,7)))
#define TSB_SC0_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->TST,7)))
#define TSB_SC0_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,0)))
#define TSB_SC0_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,1)))
#define TSB_SC0_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,2)))
#define TSB_SC0_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,3)))
#define TSB_SC0_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,4)))
#define TSB_SC0_DMA_DMAEN0                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->DMA,0)))
#define TSB_SC0_DMA_DMAEN1                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->DMA,1)))

#define TSB_SC1_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->EN,0)))
#define TSB_SC1_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->EN,1)))
#define TSB_SC1_MOD0_WU                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD0,4)))
#define TSB_SC1_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD0,5)))
#define TSB_SC1_MOD0_CTSE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD0,6)))
#define TSB_SC1_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD0,7)))
#define TSB_SC1_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->BRCR,6)))
#define TSB_SC1_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD1,4)))
#define TSB_SC1_MOD1_I2SC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD1,7)))
#define TSB_SC1_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,2)))
#define TSB_SC1_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,3)))
#define TSB_SC1_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,4)))
#define TSB_SC1_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,5)))
#define TSB_SC1_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,6)))
#define TSB_SC1_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC1->MOD2,7)))
#define TSB_SC1_RST_ROR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC1->RST,7)))
#define TSB_SC1_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC1->TST,7)))
#define TSB_SC1_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->FCNF,0)))
#define TSB_SC1_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->FCNF,1)))
#define TSB_SC1_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->FCNF,2)))
#define TSB_SC1_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->FCNF,3)))
#define TSB_SC1_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->FCNF,4)))
#define TSB_SC1_DMA_DMAEN0                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->DMA,0)))
#define TSB_SC1_DMA_DMAEN1                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC1->DMA,1)))

#define TSB_SC2_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->EN,0)))
#define TSB_SC2_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->EN,1)))
#define TSB_SC2_MOD0_WU                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD0,4)))
#define TSB_SC2_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD0,5)))
#define TSB_SC2_MOD0_CTSE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD0,6)))
#define TSB_SC2_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD0,7)))
#define TSB_SC2_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->BRCR,6)))
#define TSB_SC2_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD1,4)))
#define TSB_SC2_MOD1_I2SC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD1,7)))
#define TSB_SC2_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,2)))
#define TSB_SC2_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,3)))
#define TSB_SC2_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,4)))
#define TSB_SC2_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,5)))
#define TSB_SC2_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,6)))
#define TSB_SC2_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC2->MOD2,7)))
#define TSB_SC2_RST_ROR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC2->RST,7)))
#define TSB_SC2_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC2->TST,7)))
#define TSB_SC2_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->FCNF,0)))
#define TSB_SC2_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->FCNF,1)))
#define TSB_SC2_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->FCNF,2)))
#define TSB_SC2_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->FCNF,3)))
#define TSB_SC2_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->FCNF,4)))
#define TSB_SC2_DMA_DMAEN0                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->DMA,0)))
#define TSB_SC2_DMA_DMAEN1                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC2->DMA,1)))

#define TSB_SC3_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->EN,0)))
#define TSB_SC3_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->EN,1)))
#define TSB_SC3_MOD0_WU                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD0,4)))
#define TSB_SC3_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD0,5)))
#define TSB_SC3_MOD0_CTSE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD0,6)))
#define TSB_SC3_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD0,7)))
#define TSB_SC3_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->BRCR,6)))
#define TSB_SC3_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD1,4)))
#define TSB_SC3_MOD1_I2SC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD1,7)))
#define TSB_SC3_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,2)))
#define TSB_SC3_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,3)))
#define TSB_SC3_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,4)))
#define TSB_SC3_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,5)))
#define TSB_SC3_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,6)))
#define TSB_SC3_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC3->MOD2,7)))
#define TSB_SC3_RST_ROR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC3->RST,7)))
#define TSB_SC3_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC3->TST,7)))
#define TSB_SC3_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->FCNF,0)))
#define TSB_SC3_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->FCNF,1)))
#define TSB_SC3_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->FCNF,2)))
#define TSB_SC3_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->FCNF,3)))
#define TSB_SC3_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->FCNF,4)))
#define TSB_SC3_DMA_DMAEN0                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->DMA,0)))
#define TSB_SC3_DMA_DMAEN1                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC3->DMA,1)))

#define TSB_SC4_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->EN,0)))
#define TSB_SC4_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->EN,1)))
#define TSB_SC4_MOD0_WU                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD0,4)))
#define TSB_SC4_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD0,5)))
#define TSB_SC4_MOD0_CTSE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD0,6)))
#define TSB_SC4_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD0,7)))
#define TSB_SC4_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->BRCR,6)))
#define TSB_SC4_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD1,4)))
#define TSB_SC4_MOD1_I2SC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD1,7)))
#define TSB_SC4_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,2)))
#define TSB_SC4_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,3)))
#define TSB_SC4_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,4)))
#define TSB_SC4_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,5)))
#define TSB_SC4_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,6)))
#define TSB_SC4_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC4->MOD2,7)))
#define TSB_SC4_RST_ROR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC4->RST,7)))
#define TSB_SC4_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC4->TST,7)))
#define TSB_SC4_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->FCNF,0)))
#define TSB_SC4_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->FCNF,1)))
#define TSB_SC4_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->FCNF,2)))
#define TSB_SC4_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->FCNF,3)))
#define TSB_SC4_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->FCNF,4)))
#define TSB_SC4_DMA_DMAEN0                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->DMA,0)))
#define TSB_SC4_DMA_DMAEN1                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC4->DMA,1)))


/* WDT */
#define TSB_WD_MOD_RESCR                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_WD->MOD,1)))
#define TSB_WD_MOD_I2WDT                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_WD->MOD,2)))
#define TSB_WD_MOD_WDTE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_WD->MOD,7)))


/* CG */
#define TSB_CG_SYSCR_FPSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->SYSCR,12)))
#define TSB_CG_SYSCR_FCSTOP                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->SYSCR,20)))
#define TSB_CG_OSCCR_WUEON                        (*((__O  uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,0)))
#define TSB_CG_OSCCR_WUEF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,1)))
#define TSB_CG_OSCCR_PLLON                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,2)))
#define TSB_CG_OSCCR_XEN1                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,8)))
#define TSB_CG_OSCCR_OSCF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,9)))
#define TSB_CG_OSCCR_XEN2                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,16)))
#define TSB_CG_OSCCR_OSCSEL                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,17)))
#define TSB_CG_OSCCR_EHOSCSEL                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,18)))
#define TSB_CG_OSCCR_HWUPSEL                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->OSCCR,19)))
#define TSB_CG_PLLSEL_PLLSEL                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->PLLSEL,0)))
#define TSB_CG_PLLSEL_PLLST                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_CG->PLLSEL,18)))
#define TSB_CG_IMCGA_INT0EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGA,0)))
#define TSB_CG_IMCGA_INT1EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGA,8)))
#define TSB_CG_IMCGA_INT2EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGA,16)))
#define TSB_CG_IMCGA_INT3EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGA,24)))
#define TSB_CG_IMCGB_INT4EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGB,0)))
#define TSB_CG_IMCGB_INT5EN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->IMCGB,8)))
#define TSB_CG_RSTFLG_PONRSTF                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->RSTFLG,0)))
#define TSB_CG_RSTFLG_PINRSTF                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->RSTFLG,1)))
#define TSB_CG_RSTFLG_WDTRSTF                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->RSTFLG,2)))
#define TSB_CG_RSTFLG_SYSRSTF                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->RSTFLG,4)))
#define TSB_CG_RSTFLG_LVDRSTF                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG->RSTFLG,6)))


/* LVD */
#define TSB_LVD_CR1_EN                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_LVD->CR1,0)))
#define TSB_LVD_CR1_INTSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_LVD->CR1,4)))
#define TSB_LVD_CR1_INTEN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_LVD->CR1,5)))
#define TSB_LVD_CR1_RSTEN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_LVD->CR1,6)))
#define TSB_LVD_CR1_ST                            (*((__I  uint32_t *)BITBAND_PERI(&TSB_LVD->CR1,7)))


/* ADC */
#define TSB_AD_MOD1_I2AD                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD1,6)))
#define TSB_AD_MOD1_VREFON                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD1,7)))
#define TSB_AD_MOD3_ADOBSV0                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD3,0)))
#define TSB_AD_MOD3_ADOBIC0                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD3,5)))
#define TSB_AD_MOD4_ADHTG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD4,4)))
#define TSB_AD_MOD4_ADHS                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD4,5)))
#define TSB_AD_MOD4_HADHTG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD4,6)))
#define TSB_AD_MOD4_HADHS                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD4,7)))
#define TSB_AD_MOD5_ADOBSV1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD5,0)))
#define TSB_AD_MOD5_ADOBIC1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD5,5)))
#define TSB_AD_MOD6_ADDMA                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD6,0)))
#define TSB_AD_MOD6_ADHPDMA                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD6,1)))
#define TSB_AD_MOD6_ADM0DMA                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD6,2)))
#define TSB_AD_MOD6_ADM1DMA                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_AD->MOD6,3)))

/** @} */ /* End of group Device_Peripheral_registers */

#ifdef __cplusplus
}
#endif

#endif  /* __TMPM037_H__ */

/** @} */ /* End of group TMPM037 */
/** @} */ /* End of group TOSHIBA_TX00_MICROCONTROLLER */
