#include <stdio.h>
#include <stdint.h>

// union Data{
//     int a;
//     double b;
//     char c;
// };

// union Data data1, data2;

// typedef union{
//     int a;
//     double b;
//     char c;
// }Data;

union Data
{
    uint8_t var1;  //1 byte + 3 padding 
    uint32_t var2; //4 byte
    uint16_t var3; //2 byte + 2 padding
};

union Data data;


int main()
{
    printf("Size of frame: %d\n",sizeof(data));
    data.var1 = 5;
    data.var2 = 6;
    data.var3 = 50;
    printf("var1 = %d\n",data.var1); //50
    printf("var2 = %d\n",data.var2); //50
    printf("var3 = %d\n",data.var3); //50
}
