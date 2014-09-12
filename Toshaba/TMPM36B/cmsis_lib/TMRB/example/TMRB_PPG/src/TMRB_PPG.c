/** 
 *******************************************************************************
 * @file    main.c
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
#include "TMRB_PPG.h"

/* declaration ---------------------------------------------------------------*/
void delay(uint32_t DelayTime);
void leadingtiming_display(void);
uint16_t Tmrb_Calculator(uint16_t Tmrb_Require_us, uint32_t ClkDiv);
uint8_t Rate = 0U;

/**
  * @brief  The main function of TMRB_PPG demo
  * @param  None
  * @retval None
  */
int TMRB_PPG(void)
{
    TMRB_InitTypeDef m_tmrb;
    TMRB_FFOutputTypeDef PPGFFInital;
    uint8_t keyvalue;
    uint32_t i = 0U;
    uint32_t tgtLeadingTiming[5U] = { 10U, 25U, 50U, 75U, 90U }; /* leadingtiming: 10%, 25%, 50%, 75%, 90% */ 
    uint32_t LeadingTimingus[5U] = {0U};
    uint32_t LeadingTiming[5U] = {0U}; 
    
    /* LeadingTimingus: 50, 125, 250, 375, 450 */
    for (i=0U;i<=4U;i++) {
        LeadingTimingus[i] = tgtLeadingTiming[i] * 5U;
    }

    /* UART & switch initialization */
    hardware_init(UART_RETARGET);
    SW_Init();

    /* Set PK1 as TB6OUT for PPG output */
    GPIO_SetOutput(GPIO_PK, GPIO_BIT_1);
    GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_4, GPIO_BIT_1);

    m_tmrb.Mode = TMRB_INTERVAL_TIMER;     /* internal timer */
    m_tmrb.ClkDiv = TMRB_CLK_DIV_8;        /* 1/8PhiT0 */
    m_tmrb.UpCntCtrl = TMRB_AUTO_CLEAR;    /* up-counter auto clear */
    for(i=0U;i<=4U;i++) { 
        LeadingTiming[i] = Tmrb_Calculator(LeadingTimingus[i], m_tmrb.ClkDiv);
    } 
    m_tmrb.TrailingTiming = Tmrb_Calculator(500U, m_tmrb.ClkDiv);  /* T = 500us */ 
    m_tmrb.LeadingTiming = LeadingTiming[Rate];   /* leadingtiming, initial value 10% */
    PPGFFInital.FlipflopCtrl = TMRB_FLIPFLOP_SET;
    PPGFFInital.FlipflopReverseTrg = TMRB_FLIPFLOP_MATCH_TRAILING | TMRB_FLIPFLOP_MATCH_LEADING;

    TMRB_Enable(TSB_TB6);
    TMRB_Init(TSB_TB6, &m_tmrb);
    TMRB_SetFlipFlop(TSB_TB6, &PPGFFInital);
    TMRB_SetDoubleBuf(TSB_TB6, ENABLE, TMRB_WRITE_REG_SEPARATE);        /* enable double buffer */
    TMRB_SetRunState(TSB_TB6, TMRB_RUN);

    do {                        /* Handle the condition that start with the SW1 is high */
        keyvalue = GPIO_ReadDataBit(KEYPORT, GPIO_BIT_0);
        leadingtiming_display();
    } while (GPIO_BIT_VALUE_1 == keyvalue);

    delay(0xFFFFU);             /* noise cancel */

    while (1U) {
        do {
            keyvalue = GPIO_ReadDataBit(KEYPORT, GPIO_BIT_0);   /* display when switch is low */
            leadingtiming_display();
        } while (GPIO_BIT_VALUE_0 == keyvalue);
        delay(0xFFFFU);         /* noise cancel */
        Rate++;
        if (Rate >= LEADINGMAX) {  /* change leadingtiming rate */
            Rate = LEADINGINIT;
        } else {
            /* Do nothing */
        }
        TMRB_ChangeLeadingTiming(TSB_TB6, LeadingTiming[Rate]);
        do {
            keyvalue = GPIO_ReadDataBit(KEYPORT, GPIO_BIT_0);   /* display when switch is high */
            leadingtiming_display();
        } while (GPIO_BIT_VALUE_1 == keyvalue);
        delay(0xFFFFU);         /* noise cancel */
    }
}

/**
  * @brief  delay some time
  * @param  delay time
  * @retval None.
  */
void delay(uint32_t DelayTime)
{
    uint32_t time = 0U;
    for (time = 0U; time < DelayTime; time++) {
        /* Do nothing */
    }
}


/**
  * @brief  Display the string of TMRB_PPG demo
  * @param  None
  * @retval None
  */
void leadingtiming_display()
{
    common_uart_disp("PPG Output");
    common_uart_disp(LeadingTimingRateToString(Rate));
}

/** 
  * @brief  Calculate timer value to set timer register. 
  * @param  Tmrb_Require_us: The require period which the uint is us. 
            ClkDiv: Select the division for TMRB source clock 
  * @retval the value set to Tmrb timer register. 
  */ 
uint16_t Tmrb_Calculator(uint16_t Tmrb_Require_us, uint32_t ClkDiv) 
{      
    uint32_t T0 = 0U; 
    const uint16_t Div[8U] = {1U, 2U, 8U, 32U, 64U, 128U, 256U, 512U}; 
    
    SystemCoreClockUpdate(); 

    T0 = SystemCoreClock / (1U << ((TSB_CG->SYSCR >> 8U) & 7U));   
    T0 = T0/((Div[ClkDiv])*1000000U); 
         
    return(Tmrb_Require_us * T0); 
} 

/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
