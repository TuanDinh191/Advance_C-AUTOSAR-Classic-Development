#include <stdio.h>

int tong(int a, int b)
{
    return a+b;
}

int hieu(int a, int b)
{
    return a-b;
}

int tich(int a, int b)
{
    return a*b;
}

int thuong (int a, int b)
{
    return a/b;
}



int main()
{
    int a = 36, b = 12;
    //Tạo mảng của con trỏ hàm
    int (*ptrFunc[])(int,int) = {&tong, &hieu, &tich, &thuong};
    printf("Tong:   %d\n",ptrFunc[0](a,b));
    printf("Hieu:   %d\n",ptrFunc[1](a,b));
    printf("Tich:   %d\n",ptrFunc[2](a,b));
    printf("Thuong: %d\n",ptrFunc[3](a,b));
    return 0;
}