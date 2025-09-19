#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
   
    //malloc(5); //cấp phát 5 ô địa chỉ (5 byte): 0x01 0x02 0x03 0x04 0x05 nằm trên phân vùng heap
    int *ptr = NULL;
    int size = 20;
    ptr = (int *)malloc(size*sizeof(int)); //Cấp phát 20 phần tử tương đương 80 byte
    ptr[0] = 0;
    for (int i =  0; i<size; ++i)
        ptr[i] = 1+i;

    for (int i =0; i<size; ++i)
        printf("%p %d\n", ptr+i, ptr[i]);

    printf("\n\n");
    ptr = (int *)realloc(ptr, 40*sizeof(int)); //Cấp phát thêm (40 - 20) phần tử thêm 80 ô địa chỉ
  
    ptr[0] = 0;
    for (int i =  0; i<size*2; ++i)
        ptr[i] = 1+i;

    for (int i =0; i<size*2; ++i)
        printf("%p %d\n", ptr+i, ptr[i]);
    free(ptr);
    return 0;
}