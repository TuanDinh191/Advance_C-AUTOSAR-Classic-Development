#include <stdio.h>
#include <stdint.h>
union Data
{
    uint8_t var1;  //1 byte + 3 padding 
    uint32_t var2; //4 byte
    uint16_t var3; //2 byte + 2 padding
};

union Data data;


int main()
{
    printf("Size of frame: %zd\n",sizeof(data));
                            //0x03      0x02    0x01     0x00                            
    data.var2 = 4294967200; //11111111 11111111 11111111 10100000

    printf("var1 = %d\n",data.var1); //160 - 0b10100000
    printf("var2 = %u\n",data.var2); //4294967200 - 0b11111111111111111111111110100000
    printf("var3 = %d\n",data.var3); //65440 - 0b11111111 10100000
    
    data.var3 = 600; //0b 00000010 01011000
    printf("var1 = %d\n",data.var1); //88 - 0b01011000
    printf("var2 = %u\n",data.var2); //4294902360 - 0b11111111 11111111 00000010 01011000
    printf("var3 = %d\n",data.var3); //600 - 0b00000010 01011000
    
    
}