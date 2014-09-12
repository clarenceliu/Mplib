/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of ENC demo for the TOSHIBA 'TMPM36B'
 *          Device Series
 * @version V0.101
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */
#include "ENC_Roller.h"
uint8_t g_flag;
uint32_t enccount = 15U;

/**
  * @brief  Main function
  * @param  None
  * @retval None
  */
int ENC_Roller(void)
{
    ENC_InitTypeDef m_enc;
    ENC_FlagStatus f_enc;
    
    /* LED initialization */
    LED_Init();

    /* ENC0 initialization */   
    m_enc.ModeType = ENC_ENCODER_MODE;
    m_enc.PhaseType = ENC_TWO_PHASE;
    m_enc.CompareStatus = ENC_COMPARE_DISABLE;
    m_enc.ZphaseStatus = ENC_ZPHASE_DISABLE;
    m_enc.FilterValue = ENC_FILTER_VALUE31;
    m_enc.IntEn = ENC_INTERRUPT_ENABLE;
    m_enc.PulseDivFactor = ENC_PULSE_DIV1;
    
    ENC_Init(EN0,&m_enc);
    ENC_SetCounterReload(EN0,0xFFFU);
    
    /* GPIO initialization */
    GPIO_SetInputEnableReg(GPIO_PF, GPIO_BIT_7, ENABLE);/*Set PF7 as input */
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_2, GPIO_BIT_7);/*Set PF7 as ENCA */
    GPIO_SetInputEnableReg(GPIO_PF, GPIO_BIT_6, ENABLE);/*Set PF6 as input */
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_2, GPIO_BIT_6);/*Set PF6 as ENCB */
    
    /* Enable ENC0*/
    ENC_Enable(EN0);
    /* Enable ENC0 interrupt*/
    NVIC_EnableIRQ(INTENC0_IRQn);   
    
    /* LED1 blink speed based on the rolling of mouse wheel */
    while(1){
        f_enc = ENC_GetENCFlag(EN0);
        g_flag = f_enc.Bit.RotationDirection;  
        LED_On(LED1);
        Delay2(enccount);
        LED_Off(LED1);
        Delay2(enccount);
    } 
}


/**
  * @brief  Delay 10ms
  * @param  None
  * @retval None
  */
void Delay1(void)
{
    uint32_t TimeCounter;
    uint32_t DelayTime = 50000U;
    for (TimeCounter = 0U; TimeCounter < DelayTime; TimeCounter++) {
        /* Do nothing */
    }
}
/**
  * @brief  Delay time
  * @param  time
  * @retval None
  */
void Delay2(uint32_t time)
{
    uint32_t count;
    for (count = 0U; count < time; count++){
        Delay1();
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
