#include "stm32f4xx_hal.h"
extern void GPIO_IOToggle_example(void);
int main(void)
{
	GPIO_IOToggle_example();
    while(1)
    {
    }
}
