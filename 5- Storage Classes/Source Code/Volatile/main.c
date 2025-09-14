#include "stm32f4xx.h"

uint8_t* reg = (uint8_t *)0x20000000;
volatile uint8_t* value = 0;

int main()
{
    while(1)
    {
        value = *reg;
        if (value != 0)break;
    }
    return 0;
}