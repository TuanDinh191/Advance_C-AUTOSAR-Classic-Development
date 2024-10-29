#include <stdio.h>
#include <stdint.h>

// typedef struct {
//     uint8_t var1[9];    //8 byte + 1 byte + 7 padding 
//     uint64_t var2[3];   //24 byte
//     uint32_t var3[2];   //8 byte
//     uint16_t var4[10];  //16 byte + 4 byte + 4 padding
// }frame;

typedef struct {
    uint8_t var1;    // 1 byte + 7 padding 
    uint64_t var2;   // 8 byte
    uint32_t var3;   // 4 byte 
    uint16_t var4;   // 2 byte + 2 padding
}frame;


int main()
{
    printf("Size of frame: %d\n",sizeof(frame));
}