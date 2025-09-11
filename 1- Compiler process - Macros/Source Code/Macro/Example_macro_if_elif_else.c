#define ESP32       1 
#define STM32       2 
#define ATmega324   3 

#define MCU STM32

#if MCU == STM32 
    void digitalWrite(Pin pin, Status state) {
        if (state == HIGH){
            GPIOA->ODR |= (1 << pin);
        }
        else {
            GPIOA->BSRR &= ~(1<<pin);
        } 
}

#elif MCU == ESP32
   void digitalWrite(Pin pin, Status state) {
       if (state == HIGH){
           GPIO.out_w1ts |= (1<< pin);
       }
       else {
           GPIO.out_w1tc =  (1<<pin);
       }
}

#else 
    void digitalWrite(Pin pin, Status state) {
        if (state == HIGH){
            PORTA |= (1<<pin);
        }
        else {
            PORTA &= ~(1<<pin);
        } 
}

#endif

int main()
{
    printf("Hello World");

    return 0;
}