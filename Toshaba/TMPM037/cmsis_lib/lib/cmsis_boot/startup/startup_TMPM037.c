//*****************************************************************************
//
//! \file      startup_coide.c
//! \brief     TMPM061 Device series startup code for CooCox CoIDE.
//!            This module performs:
//!               - Set the initial SP
//!               - Set the vector table entries with the exceptions ISR address
//!               - Initialize data and bss
//!               - Setup the microcontroller system.
//!               - Call the application's entry point.
//!               .
//! \version   V2.1.1.0
//! \date      $CURRENT_TIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2013, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Stack Configuration
//
//*****************************************************************************
//
// Stack size (in Words)
//
#define STACK_SIZE       0x00000200
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];

#define WEAK __attribute__ ((weak))

//*****************************************************************************
//
// Declaration of the default fault handlers
//
//*****************************************************************************
void WEAK  Reset_Handler      (void);
void WEAK  NMI_Handler        (void);
void WEAK  HardFault_Handler  (void);
void WEAK  SVC_Handler        (void);
void WEAK  PendSV_Handler     (void);
void WEAK  SysTick_Handler    (void);

// External Interrupts
void WEAK  INT0_IRQHandler      (void);     //0:    PCE interface
void WEAK  INT1_IRQHandler      (void);     //1:    ¦¤¦²A/D conversion complee interrupt (unit0)
void WEAK  INT2_IRQHandler      (void);     //2:    ¦¤¦²A/D conversion complee interrupt (unit1)
void WEAK  INT3_IRQHandler      (void);     //3:    ¦¤¦²A/D conversion complee interrupt (unit2)
void WEAK  INT4_IRQHandler      (void);     //4:    Voltage detector interrupt
void WEAK  INT5_IRQHandler      (void);     //5:    Interrupt pin 0
void WEAK  INTRX0_IRQHandler    (void);     //6:    Interrupt pin 1
void WEAK  INTTX0_IRQHandler    (void);     //7:    Interrupt pin 2
void WEAK  INTRX1_IRQHandler    (void);     //8:    Interrupt pin 3
void WEAK  INTTX1_IRQHandler    (void);     //9:    Serial reception (channel.0)
void WEAK  INTI2C0_IRQHandler   (void);     //10:   Serial transmission (channel.0)
void WEAK  INTDMAC_IRQHandler   (void);     //11:   Serial reception (channel.1)
void WEAK  INTT16A0_IRQHandler  (void);     //12:   Serial transmission (channel.1)
void WEAK  INTT16A1_IRQHandler  (void);     //13:   Serial reception (channel.2)
void WEAK  INTTMRB0_IRQHandler  (void);     //14:   Serial transmission (channel.2)
void WEAK  INTTMRB1_IRQHandler  (void);     //15:   Serial reception (channel.3)
void WEAK  INTTMRB2_IRQHandler  (void);     //16:   Serial transmission (channel.3)
void WEAK  INTTMRB3_IRQHandler  (void);     //17:   Serial bus interface
void WEAK  INTTMRB4_IRQHandler  (void);     //18:   16-bit TMRB match detection 0
void WEAK  INTTMRB5_IRQHandler  (void);     //19:   16-bit TMRB match detection 1
void WEAK  INTTMRB6_IRQHandler  (void);     //20:   16-bit TMRB input capture 0 (channel.0)
void WEAK  INTTMRB7_IRQHandler  (void);     //21:   16-bit TMRB input capture 1 (channel.0)
void WEAK  INTRX2_IRQHandler    (void);     //22:   16-bit TMRB input capture 0 (channel.1)
void WEAK  INTTX2_IRQHandler    (void);     //23:   16-bit TMRB input capture 1 (channel.1)
void WEAK  INTRX3_IRQHandler    (void);     //24:   16-bit TMR16A match detection (channel.0)
void WEAK  INTTX3_IRQHandler    (void);     //25:   16-bit TMR16A match detection (channel.1)
void WEAK  INTRX4_IRQHandler    (void);     //26:   16-bit TMR16A match detection (channel.2)
void WEAK  INTTX4_IRQHandler    (void);     //27:   16-bit TMR16A match detection (channel.3)
void WEAK  INTADC_IRQHandler    (void);     //28:   16-bit TMR16A match detection (channel.5)
void WEAK  INTAD_IRQHandler     (void);     //29:   16-bit TMR16A match detection (channel.6)

//*****************************************************************************
//
// Symbols defined in linker script
//
//*****************************************************************************
//
// Start address for the initialization values of the .data section.
//
extern unsigned long _sidata;

//
// Start address for the .data section
//
extern unsigned long _sdata;

//
// End address for the .data section
//
extern unsigned long _edata;

//
// Start address for the .bss section
//
extern unsigned long _sbss;

//
// End address for the .bss section
//
extern unsigned long _ebss;

//
// End address for ram
//
extern void _eram;

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
extern int main(void);
extern void SystemInit(void);
__attribute__ ((used))
void Default_ResetHandler(void);
static void DefaultIntHandler(void);

//
// The minimal vector table for a Cortex M3.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void *)&pulStack[STACK_SIZE],          // The initial stack pointer
    Reset_Handler                ,          // The reset handler
    NMI_Handler                  ,          // The NMI handler
    HardFault_Handler            ,          // The hard fault handler
    0                            ,          // 
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    0                            ,          // Reserved
    SVC_Handler                  ,          // SVCall handler
    0                            ,          // Reserved
    0                            ,          // Reserved
    PendSV_Handler               ,          // The PendSV handler
    SysTick_Handler              ,          // The SysTick handler

    // External Interrupts
    INT0_IRQHandler              ,          //0: Interrupt Pin0(PB5)   
    INT1_IRQHandler              ,          //1: Interrupt Pin1(PB6)  
    INT2_IRQHandler              ,          //2: Interrupt Pin2(PB7)  
    INT3_IRQHandler              ,          //3: Interrupt Pin3(PE7)  
    INT4_IRQHandler              ,          //4: Interrupt Pin4(PE6)   
    INT5_IRQHandler              ,          //5: Interrupt Pin5(PE5)   
    INTRX0_IRQHandler            ,          //6: Serial reception (channel.0)   
    INTTX0_IRQHandler            ,          //7: Serial transmission (channel.0)   
    INTRX1_IRQHandler            ,          //8: Serial reception (channel.1)   
    INTTX1_IRQHandler            ,          //   Serial transmission (channel.1)
    0                            ,          //9:   
    0                            ,          //10:  
    INTI2C0_IRQHandler           ,          //11:   
    INTDMAC_IRQHandler           ,          //12:   
    INTT16A0_IRQHandler          ,          //13:   
    INTT16A1_IRQHandler          ,          //14:  
    INTTMRB0_IRQHandler          ,          //15:   
    INTTMRB1_IRQHandler          ,          //16:  
    INTTMRB2_IRQHandler          ,          //17:   
    INTTMRB3_IRQHandler          ,          //18:   
    INTTMRB4_IRQHandler          ,          //19:   
    INTTMRB5_IRQHandler          ,          //20:   
    INTTMRB6_IRQHandler          ,          //21:   
    INTTMRB7_IRQHandler          ,          //22:   
    INTRX2_IRQHandler            ,          //23:   
    INTTX2_IRQHandler            ,          //24:  
    INTRX3_IRQHandler            ,          //25:   
    INTTX3_IRQHandler            ,          //26:   
    INTRX4_IRQHandler            ,          //27:   
    INTTX4_IRQHandler            ,           //28:   
    INTADC_IRQHandler            ,          //29:   
    INTAD_IRQHandler             ,          //30:  
};

//*****************************************************************************
//
//! \brief This is the code that gets called when the processor first
//! starts execution following a reset event.
//!
//! \param None.
//!
//! Only the absolutely necessary set is performed, after which the
//! application supplied main() routine is called.
//!
//! \return None.
//
//*****************************************************************************
void Default_ResetHandler(void)
{
    //
    // Initialize data and bss
    //
    unsigned char *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM
    //
    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    //
    // Call the application's entry point.
    //
    SystemInit();
    main();
}

//*****************************************************************************
//
// Provide weak aliases for each Exception handler to the DefaultIntHandler.
// As they are weak aliases, any function with the same name will override
// this definition.
//
//*****************************************************************************

#pragma weak Reset_Handler        = Default_ResetHandler
#pragma weak NMI_Handler          = DefaultIntHandler
#pragma weak HardFault_Handler    = DefaultIntHandler
#pragma weak SVC_Handler          = DefaultIntHandler
#pragma weak PendSV_Handler       = DefaultIntHandler
#pragma weak SysTick_Handler      = DefaultIntHandler

// External Interrupts
#pragma weak INT0_IRQHandler      = DefaultIntHandler //0:    PCE interface
#pragma weak INT1_IRQHandler  	  = DefaultIntHandler //1:    ¦¤¦²A/D conversion complee interrupt (unit0)
#pragma weak INT2_IRQHandler 	  = DefaultIntHandler //2:    ¦¤¦²A/D conversion complee interrupt (unit1)
#pragma weak INT3_IRQHandler  	  = DefaultIntHandler //3:    ¦¤¦²A/D conversion complee interrupt (unit2)
#pragma weak INT4_IRQHandler      = DefaultIntHandler //4:    Voltage detector interrupt
#pragma weak INT5_IRQHandler      = DefaultIntHandler //5:    Interrupt pin 0
#pragma weak INTRX0_IRQHandler    = DefaultIntHandler //6:    Interrupt pin 1
#pragma weak INTTX0_IRQHandler    = DefaultIntHandler //7:    Interrupt pin 2
#pragma weak INTRX1_IRQHandler    = DefaultIntHandler //8:    Interrupt pin 3
#pragma weak INTTX1_IRQHandler    = DefaultIntHandler //9:    Serial reception (channel.0)
#pragma weak INTI2C0_IRQHandler   = DefaultIntHandler //10:   Serial transmission (channel.0)
#pragma weak INTDMAC_IRQHandler   = DefaultIntHandler //11:   Serial reception (channel.1)
#pragma weak INTT16A0_IRQHandler  = DefaultIntHandler //12:   Serial transmission (channel.1)
#pragma weak INTT16A1_IRQHandler  = DefaultIntHandler //13:   Serial reception (channel.2)
#pragma weak INTTMRB0_IRQHandler  = DefaultIntHandler //14:   Serial transmission (channel.2)
#pragma weak INTTMRB1_IRQHandler  = DefaultIntHandler //15:   Serial reception (channel.3)
#pragma weak INTTMRB2_IRQHandler  = DefaultIntHandler //16:   Serial transmission (channel.3)
#pragma weak INTTMRB3_IRQHandler  = DefaultIntHandler //17:   Serial bus interface
#pragma weak INTTMRB4_IRQHandler  = DefaultIntHandler //18:   16-bit TMRB match detection 0
#pragma weak INTTMRB5_IRQHandler  = DefaultIntHandler //19:   16-bit TMRB match detection 1
#pragma weak INTTMRB6_IRQHandler  = DefaultIntHandler //20:   16-bit TMRB input capture 0 (channel.0)
#pragma weak INTTMRB7_IRQHandler  = DefaultIntHandler //21:   16-bit TMRB input capture 1 (channel.0)
#pragma weak INTRX2_IRQHandler    = DefaultIntHandler //22:   16-bit TMRB input capture 0 (channel.1)
#pragma weak INTTX2_IRQHandler    = DefaultIntHandler //23:   16-bit TMRB input capture 1 (channel.1)
#pragma weak INTRX3_IRQHandler    = DefaultIntHandler //24:   16-bit TMR16A match detection (channel.0)
#pragma weak INTTX3_IRQHandler    = DefaultIntHandler //25:   16-bit TMR16A match detection (channel.1)
#pragma weak INTRX4_IRQHandler    = DefaultIntHandler //26:   16-bit TMR16A match detection (channel.2)
#pragma weak INTTX4_IRQHandler    = DefaultIntHandler //27:   16-bit TMR16A match detection (channel.3)
#pragma weak INTADC_IRQHandler    = DefaultIntHandler //28:   16-bit TMR16A match detection (channel.5)
#pragma weak INTAD_IRQHandler     = DefaultIntHandler //29:   16-bit TMR16A match detection (channel.6)

//*****************************************************************************
//
//! \brief This is the code that gets called when the processor receives an
//! unexpected interrupt.
//!
//! \param None.
//!
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//!
//! \return None.
//*****************************************************************************
static void DefaultIntHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while (1)
    {
    }
}

