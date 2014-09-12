/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of IGBT Two PPG for the TOSHIBA 'TMPM36B' 
 *          Device Series 
 * @version V0.201
 * @date    2014/05/20
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "IGBT_TwoPPG.h"

/* Global variable define ----------------------------------------------------*/
WorkState counter_state = BUSY;
Result cancel_result = ERROR;
IGBT_InitTypeDef myIGBT;
IGBT_EMGStateTypeDef EMGState = { IGBT_EMG_INPUT_LOW, IGBT_EMG_NORMAL };

int IGBT_TwoPPG(void)
{
    /* LED & swich initialization */
    LED_Init();
    SW_Init();
    LED_On(LED0);

    myIGBT.StartMode = IGBT_CMD_START;  /* IGBT trigger start: command start */
    myIGBT.OperationMode = IGBT_CONTINUOUS_OUTPUT;      /* IGBT operation: continuous operation */
    myIGBT.CntStopState = IGBT_OUTPUT_INACTIVE; /* IGBT stopping status: initial output satus and counter */
    myIGBT.ActiveAcceptTrg = DISABLE;   /* Trigger edge accept mode: Don't accept trigger during active level */
    myIGBT.INTPeriod = IGBT_INT_PERIOD_1;       /* Interrupt cycle: Every one cycle */
    myIGBT.ClkDiv = IGBT_CLK_DIV_2;     /* For M36BFY:fperiph = fc = 10MHz*8 = 80MHz, T0 = fperiph = 80MHz, figbt = T0/2 = 40MHz 
                                           For M36BF10:fperiph = fc = 10MHz*6 = 60MHz, T0 = fperiph = 60MHz, figbt = T0/2 = 30MHz */
    myIGBT.Output0Init = IGBT_OUTPUT_HIGH_ACTIVE;       /* MTOUT00 initial state is Low, and active level is High */
    myIGBT.Output1Init = IGBT_OUTPUT_HIGH_ACTIVE;       /* MTOUT10 initial state is Low, and active level is High */
    myIGBT.TrgDenoiseDiv = IGBT_NO_DENOISE;     /* Trigger input noise elimination time: no use */
    myIGBT.Output0ActiveTiming = 1U;
    myIGBT.Output0InactiveTiming = 1U + IGBT_ACTIVE_PERIOD_20US;
    myIGBT.Output1ActiveTiming = myIGBT.Output0InactiveTiming + IGBT_DEAD_TIME_5US;
    myIGBT.Output1InactiveTiming = myIGBT.Output1ActiveTiming + IGBT_ACTIVE_PERIOD_20US;
    myIGBT.Period = IGBT_PPG_PERIOD_50US;       /* Period: 50us */
    myIGBT.EMGFunction = IGBT_EMG_OUTPUT_HIZ;   /* The polarity of MTOUT0x at EMG protection: High-impedance */
    myIGBT.EMGDenoiseDiv = IGBT_DENOISE_DIV_240;        /* EMG input noise elimination time: 240/fsys */

    IGBT_IO_Configuration(IGBT0, &myIGBT);

    IGBT_Enable(IGBT0);
    NVIC_EnableIRQ(INTMTEMG0_IRQn);     /* Enable IGBT and EMG interrupt */

    do {                        /* If the timer is still running, wait until it stops */
        counter_state = IGBT_GetCntState(IGBT0);
    } while (counter_state == BUSY);
    do {                        /* Cancel the EMG protection state */
        cancel_result = IGBT_CancelEMGState(IGBT0);
    } while (cancel_result == ERROR);

    IGBT_Init(IGBT0, &myIGBT);

    if (SWITCH_ON) {            /* If switch is ON */
        IGBT_SetSWRunState(IGBT0, IGBT_RUN);    /* Start to run IGBT timer */
    } else {
        /* Do nothing */
    }

    while (1) {

        EMGState = IGBT_GetEMGState(IGBT0);     /* Get EMG protection state to check EMG state */

        if (EMGState.EMGProtectState == IGBT_EMG_PROTECT) {     /* If EMG protection is on going */
            do {
                counter_state = IGBT_GetCntState(IGBT0);
            } while (counter_state == BUSY);
            do {                /* Cancel the EMG protection state */
                cancel_result = IGBT_CancelEMGState(IGBT0);
            } while (cancel_result == ERROR);

            LED_Off(LED1);      /* Turn off the LED and start to run again */
            IGBT_Init(IGBT0, &myIGBT);

            IGBT_SetSWRunState(IGBT0, IGBT_RUN);

        } else {
            /* Do nothing */
        }

        if (SWITCH_ON) {
            IGBT_SetSWRunState(IGBT0, IGBT_RUN);        /* If switch is ON, start to run */
        } else {
            IGBT_SetSWRunState(IGBT0, IGBT_STOP);       /* If switch is OFF, stop to run */
        }
    }
}

/**
  * @brief  IRQ for EMG protection
  * @param  None.
  * @retval None.
  */
void INTMTEMG0_IRQHandler(void)
{
    LED_On(LED1);               /* If EMG protection, turn off the LED and stop the timer */
    IGBT_SetSWRunState(IGBT0, IGBT_STOP);
}

/**
  * @brief  IGBT port initialization
  * @param  IGBTx: IGBT channel.
  *         InitTypeDef: initialization structure.
  * @retval None.
  */
void IGBT_IO_Configuration(TSB_MT_TypeDef * IGBTx, IGBT_InitTypeDef * InitTypeDef)
{
    if (IGBTx == IGBT0) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_0, ENABLE);        /* Enable PG0 input */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_0);   /* Set PG0 as MT0IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_0, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_0);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_3, ENABLE);       /* Enable PG3 output */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PG3 as MTOUT00 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_2, ENABLE);       /* Enable PG2 output */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PG2 as MTOUT10 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }

        GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_1, ENABLE);    /* Enable PG1 input */
        GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_1);       /* Set PG1 as GEMG0 */
    }


    if (IGBTx == IGBT1) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_0, ENABLE);        /* Enable PL0 input */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_0);   /* Set PL0 as MT1IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_0, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_0);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_3, ENABLE);       /* Enable PL3 output */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PL3 as MTOUT01 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_2, ENABLE);       /* Enable PL2 output */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PL2 as MTOUT11 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }

        GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_1, ENABLE);    /* Enable PL1 input */
        GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_1);       /* Set PL1 as GEMG1 */
    }

    if (IGBTx == IGBT2) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_0, ENABLE);        /* Enable PH0 input */
            GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_0);   /* Set PH0 as MT2IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_0, DISABLE);
            GPIO_DisableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_0);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_3, ENABLE);       /* Enable PH3 output */
            GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PH3 as MTOUT02 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_2, ENABLE);       /* Enable PH2 output */
            GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PH2 as MTOUT12 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }

        GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_1, ENABLE);    /* Enable PH1 input */
        GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_3, GPIO_BIT_1);       /* Set PH1 as GEMG2 */
    }

    if (IGBTx == IGBT3) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PB, GPIO_BIT_5, ENABLE);        /* Enable PB5 input */
            GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_5);   /* Set PB5 as MT3IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PB, GPIO_BIT_5, DISABLE);
            GPIO_DisableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_5);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_2, ENABLE);       /* Enable PB2 output */
            GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PB2 as MTOUT03 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_3, ENABLE);       /* Enable PB3 output */
            GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PB3 as MTOUT13 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }

        GPIO_SetInputEnableReg(GPIO_PB, GPIO_BIT_4, ENABLE);    /* Enable PB4 input */
        GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_4);       /* Set PB4 as GEMG3 */
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif                          /* DEBUG */
