#include <stdio.h>

int main()
{
   int a = 5; 
    //Địa chỉ của biến a: 0x12 có giá trị là 5:

    int *ptr1 = &a; 
    //Địa chỉ của biến con trỏ ptr1: 0xd2 nhưng có giá trị là 0x12 là địa chỉ của biến a

    int **ptr2 = &ptr1;
    // ptr2 là con trỏ cấp 2 
    //Địa chỉ của biến con trỏ ptr2: 0xf4 nhưng có giá trị là 0xd2 là địa chỉ của con trỏ ptr1  

    printf("Dia chi cua bien a: %p\n",&a);  
    printf("Gia tri cua ptr1:%p\n", ptr1);

    printf("Dia chi cua ptr1: %p\n", &ptr1);    
    printf("Gia tri cua ptr2: %p\n", ptr2);

    printf("Giai tham chieu ptr2 lan 1: %p\n ",*ptr2); //In ra giá trị của ptr1
    printf("Giai tham chieu ptr2 lan 2: %d\n",**ptr2); //In ra giá trị của a thông qua ptr2
    return 0;
}