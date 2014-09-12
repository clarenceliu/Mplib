
/**************************************************************************//**
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/


#include <stdio.h>
#include "NUC123Series.h"
#include "CLOCK.h"
#include "SYS.h"
#include "GPIO.h"
#include "I2S.h"
#include "I2C.h"

#include "hello.h"

#define WAU8822_SLA			0x1A

#define AUDIO_RATE			8000
#define AUDIO_CHANNELS		1
#define AUDIO_BIT_RATE		16

static void RoughDelay(uint32_t t);
void I2C_Init(void);
int I2C_TX(uint8_t addr, uint8_t *buffer, uint8_t size);
static int I2C_WriteWAU8822(uint8_t u8addr, uint16_t u16data);
void I2S_Init(void);
static void WAU8822_Setup(void);

/*---------------------------------------------------------------------------------------------------------*/
/* Main function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int I2S_Example (void)
{
    uint32_t u32PlayPos = 0;

    UNLOCKREG();							// ��:�����Ĵ���//en: Unlock the locked registers

    GPIO_XT1();						// ��:ʹ��HXT����//en: Enable HXT PINs
    CLK_HXT_ENABLE();						// ��:ʹ��HXT//en: Enable HXT
    while(!CLK_IS_STABLE(CLK_HXT_STB));				// ��:�ȴ�HXT�ȶ�//en: Wait HXT Stable

    SystemCoreClockUpdate();					// ��:����ϵͳʱ������//en: Update system core clock

    I2C_Init();							// ��:I2C��ʼ��//en: Initialize I2C
    I2S_Init();							// ��:I2S��ʼ��//en: Initialize I2S
    WAU8822_Setup();						// ��:WAU8822��ʼ��//en: Initialize WAU8822
    I2S_ENABLE_TX();						// ��:ʹ��I2S����//en: Enable I2S Tx

    while (1)
    {
        if (!(I2S_GET_STATUS() & I2S_STAT_TX_FULL))
        {
#if AUDIO_BIT_RATE == 8
            uint32_t data = ((uint32_t)APU_SOURCE[u32PlayPos + 0] <<  0) +
                            ((uint32_t)APU_SOURCE[u32PlayPos + 1] <<  8) +
                            ((uint32_t)APU_SOURCE[u32PlayPos + 2] << 16) +
                            ((uint32_t)APU_SOURCE[u32PlayPos + 3] << 24);
#elif AUDIO_BIT_RATE == 16
            uint32_t data = ((uint32_t)APU_SOURCE[u32PlayPos + 0] <<  0) +
                            ((uint32_t)APU_SOURCE[u32PlayPos + 1] << 16);
#elif (AUDIO_BIT_RATE == 24) || (AUDIO_BIT_RATE == 32)
            uint32_t data = APU_SOURCE[u32PlayPos];
#else
            #error invalid AUDIO_BIT_RATE for NUC
#endif
            I2S_SET_DATA(data);				// ��:����I2S����//en: Set I2S Data
            u32PlayPos += 32 / AUDIO_BIT_RATE;
            if (u32PlayPos >= (sizeof(APU_SOURCE) / sizeof(APU_SOURCE[0])))
            {
                u32PlayPos = 0;
            }
        }
    }
}


static void RoughDelay(uint32_t t)
{
    volatile int32_t delay;

    delay = t;

    while(delay-- >= 0);
}

/**
 * @brief       I2C0 Initialize
 *
 * @param       None
 *
 * @return      None
 *
 * @details     Initialize I2C module
 */
void I2C_Init(void)
{
    GPIO_I2C0();
    DrvI2C_Init(I2C0, 100000, FALSE);
}

/**
 * @brief       I2C0 sent a frame data
 *
 * @param       addr			Address of slave I2C chip
 *              buffer			Data buffer to be sent to slave I2C chip
 *              size                    Size of Data buffer
 *
 * @return      ErrCode			0 for no error, non-0 for error.
 *
 * @details     I2C0 sent a frame data
 */
int I2C_TX(uint8_t addr, uint8_t *buffer, uint8_t size)
{
    uint8_t txByte_Count;

    I2C_START_WAIT_AND_CLEAR(I2C0);                             //��:����ʼ�ź�//en: Send START

    if (I2C_GET_I2CSTATUS(I2C0) != 0x08)                        //��:�����ʼ�ź��Ƿ��Ѿ��ɹ�������//en:Check if START signal has been transmitted successfully
    {
        return 1;
    }

    I2C_SENT_DATA(I2C0, addr<<1);                 //��:д�ӵ�ַ//en: Write Slave address

    if (I2C_GET_I2CSTATUS(I2C0) != 0x18)                         //��:���SLA+W�Ƿ��Ѿ����ɹ�����//en:Check if SLA+W has been transmitted successfully
    {
        return 1;
    }

    for(txByte_Count=0;txByte_Count<size;txByte_Count++)
    {
        I2C_SENT_DATA(I2C0,buffer[txByte_Count]);                             //��:д����//en:Write data

        if ((I2C_GET_I2CSTATUS(I2C0) != 0x28)&&(I2C_GET_I2CSTATUS(I2C0) != 0x30))  //��:���һ�ֽ������Ƿ��Ѿ����ɹ�����//en:Check if a byte data has been transmitted successfully
        {
            return 1;
        }
    }

    I2C_STOP(I2C0);                                   //��:����ֹͣ�ź�//en:Send STO signal
    return 0;
}

/**
 * @brief       Write WAU8822 Register
 *
 * @param       u8addr			Register Address
 *              u16data                 16-bit data to be written to the target register
 *
 * @return      ErrCode			0 for no error, non-0 for error.
 *
 * @details     Write WAU8822 Register through I2C
 */
static int I2C_WriteWAU8822(uint8_t u8addr, uint16_t u16data)
{
    uint8_t Tx_Data[2];

    Tx_Data[0] = (uint8_t)((u8addr << 1) | (u16data >> 8));
    Tx_Data[1] = (uint8_t)(u16data & 0x00FF);

    return I2C_TX(WAU8822_SLA, Tx_Data, 2);
}

/**
 * @brief       Setup WAU8822
 *
 * @param       None
 *
 * @return      None
 *
 * @details     Configure WAU8822 Registers
 */
static void WAU8822_Setup(void)
{
    I2C_WriteWAU8822(0,  0x000);   /* ��:��λ���мĴ���//en: Reset all registers */
    RoughDelay(0x200);

    I2C_WriteWAU8822(1,  0x03F);
    I2C_WriteWAU8822(2,  0x1BF);
    I2C_WriteWAU8822(3,  0x07F);
    I2C_WriteWAU8822(4,
#if AUDIO_BIT_RATE == 16
                        0x000
#elif AUDIO_BIT_RATE == 20
                        0x020
#elif AUDIO_BIT_RATE == 24
                        0x040
#elif AUDIO_BIT_RATE == 32
                        0x060
#else
    #error invalid AUDIO_BIT_RATE for WAU8822
#endif
                        |
#if AUDIO_CHANNELS == 1
                        0x000
#elif AUDIO_CHANNELS == 2
                        0x001
#else
	#error invalid AUDIO_CHANNELS for WAU8822
#endif
                        | 0x012);
    I2C_WriteWAU8822(5,  0x000);

    I2C_WriteWAU8822(6,  0x0AD);
    I2C_WriteWAU8822(7,  0x006);

    I2C_WriteWAU8822(10, 0x008);
    I2C_WriteWAU8822(14, 0x108);
    I2C_WriteWAU8822(15, 0x0EF);
    I2C_WriteWAU8822(16, 0x1EF);

    I2C_WriteWAU8822(43, 0x010);

    I2C_WriteWAU8822(44, 0x003);
    I2C_WriteWAU8822(45, 0x03F);
    I2C_WriteWAU8822(46, 0x13F);
    I2C_WriteWAU8822(47, 0x107);
    I2C_WriteWAU8822(48, 0x107);
    I2C_WriteWAU8822(49, 0x047);

    I2C_WriteWAU8822(50, 0x001);
    I2C_WriteWAU8822(51, 0x000);

    I2C_WriteWAU8822(54, 0x139);
    I2C_WriteWAU8822(55, 0x139);

    // ��:ʹ��Line Out//en: Enable Line Out
    GPIO_SET_MODE(PC, 4, GPIO_OUTPUT);
    GPIO_CLR_PIN(PC4);
}

/**
 * @brief       I2S Initialize
 *
 * @param       None
 *
 * @return      None
 *
 * @details     Initialize I2S module
 */
void I2S_Init(void)
{
    uint32_t divider;

    // ��:����I2S����//en: Configure I2S PINs
    GPIO_I2S();
    GPIO_I2S_MCLK_PC12();

    SET_I2S_CLKSRC(CLK_I2S_HXT);				// ��:����I2Sʱ��Դ//en: Select I2S Clock Source
    APBCLK_ENABLE(CLK_I2S);					// ��:ʹ��I2Sʱ��//en: Enable I2S Clock
    SYS_RESET_IP2(SYS_RST_I2S);					// ��:��λI2Sģ��//en: Reset I2S Module

    I2S_SET_MCK_DIV(0);						// ��:����MCLKʱ�ӷ�Ƶ//en: set MCLK divider
    divider = ((__XTAL*10)/((AUDIO_RATE * (AUDIO_BIT_RATE / 8) * 16) * 2) + 5) / 10 - 1;
    I2S_SET_BITCLK_DIV(divider);					// ��:����BCLKʱ�ӷ�Ƶ//en: set BCLK divider

    // ��:����I2S����//en: Configure I2S
    I2S_ASSIGN_CONFIG(I2S_CFG_SLAVE|I2S_CFG_MCK_EN|
#if 2 == AUDIO_CHANNELS
                      I2S_CFG_CHANNEL_STEREO|
#elif 1 == AUDIO_CHANNELS
                      I2S_CFG_CHANNEL_MONO_LEFT|
#else
    #error invalid AUDIO_CHANNELS
#endif
#if 32 == AUDIO_BIT_RATE
                      I2S_CFG_WORDWIDTH_32|
#elif 24 == AUDIO_BIT_RATE
                      I2S_CFG_WORDWIDTH_24|
#elif 16 == AUDIO_BIT_RATE
                      I2S_CFG_WORDWIDTH_16|
#elif 8 == AUDIO_BIT_RATE
                      I2S_CFG_WORDWIDTH_8|
#else
    #error invalid AUDIO_BIT_RATE for NUC
#endif
                      I2S_CFG_EN);
}







