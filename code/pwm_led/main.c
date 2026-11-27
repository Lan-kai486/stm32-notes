#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"

int main(void)
{
    uint8_t i;

    LED_Init();

    while (1)
    {
        for (i = 0; i <= 100; i++)
        {
            TIM_SetCompare1(TIM2, i);
            Delay_ms(10);
        }
        for (i = 0; i <= 100; i++)
        {
            TIM_SetCompare1(TIM2, 100 - i);
            Delay_ms(10);
        }
    }
}
