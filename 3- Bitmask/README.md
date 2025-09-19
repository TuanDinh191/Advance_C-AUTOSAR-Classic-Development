
# Bai 3 Bitmask
#### 1. Bitmask
#### - Định nghĩa:
 - Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xóa và kiểm tra trạng thái của các bit cụ thể trong một từ (word).
- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.
#### - Cách dùng:
- Not bitwise: Thực hiện phép đảo ngược bit.
```bash
int a = 0b10010001;
int result = ~a; //(0b01101110)
```
- AND bitwise: Thực hiện hiện phép AND. Trả về kết quả là 1 nếu cả 2 là 1 ngược lại là 0.
```bash
int a = 0b10100011;
int b = 0b00001111;
int result;
result = a & b; //(0b000000011);
```
- OR bitwise: Thực hiện phép OR.Trả về kết quả trả về là 0 nếu cả 2 bit so sánh là 0 hoặc bằng 1 nếu 1 trong 2 bit so sánh bằng 1 hoặc cả 2 bit đều bằng 1.
```bash
int a = 0b10100011;
int b = 0b00001110;
int result;
result = a | b; //(0b10101111);
```
- XOR bitwise: Thực hiện phép XOR. Trả về kết quả là 1 nếu 1 trong 2 bit so sánh là 1.
```bash
int a = 0b10100011;
int b = 0b00001110;
int result;
result = a ^ b; //(0b10101101);
```
- Shift bitwise: Thực hiện phép dịch chuyển bit sang trái hoặc bên phải dựa vào giá trị đặt.
```bash
int a = 0b10100011;
int result_shiftleft;
int result_shiftright;

//Dịch bit bên trai 3 lan
result_shiftleft = a << 3;
//(0b010100011000)

//Dich bit ben phai 2 lan;
result_shiftright = a >>2;
//(0b00010100)
```
### - Ứng dụng:
```javascript
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
```

