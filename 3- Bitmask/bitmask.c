#include <stdio.h>
#include <stdint.h>

#define LED1 1<<0 //bit 0: Mở chân led 1
#define LED2 1<<1 //bit 0: Mở chân led 2
#define LED3 1<<2 //bit 0: Mở chân led 2
#define LED4 1<<3 //bit 0: Mở chân led 2

void enableLED(uint8_t *ledODR, uint8_t LEDPin)
{
    *ledODR |= LEDPin;
}

void disableLED(uint8_t *ledODR, uint8_t LEDPin)
{
    *ledODR &= ~LEDPin;
}

uint8_t checkLEDOn(uint8_t LedODR, uint8_t LedPin)
{
    return ((LedODR & LedPin) ? 1:0);
}

void checkallLED(uint8_t LedODR)
{
    const char* LedPin[] = {"LED_1 On", "LED_2 On","LED_3 On", "LED_4 On"};
    for(int i=0; i<3; ++i)
    {
        if((LedODR>>i)&1)
          printf("%s\n",LedPin[i]);
    }
}

int main()
{
    uint8_t LedODR =  0; //Led output GPIO data
    enableLED(&LedODR,LED1);
    printf("Chan Led 1 dang %s\n",checkLEDOn(LedODR,LED1)? "mo" : "dong");

    disableLED(&LedODR,LED1);
    printf("Chan Led 1 dang %s\n",checkLEDOn(LedODR,LED1)? "mo" : "dong");

    enableLED(&LedODR,LED2);
    enableLED(&LedODR,LED3);
    checkallLED(LedODR);
}