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
    if (b == 0)
    {
        printf("Khong the chia cho 0\n");
        return 0;
    }
    else 
        return a/b;
}

//Con trỏ hàm làm tham số truyền vào của một hàm
int pheptoan(int (*ptrFunc)(int,int),int a,int b)
{
    return ptrFunc(a,b);
}

int main()
{
    int a = 36, b = 12;
    printf("Tong:   %d\n",pheptoan(tong,a,b));
    printf("Hieu:   %d\n",pheptoan(hieu,a,b));
    printf("Tich:   %d\n",pheptoan(tich,a,b));
    printf("Thuong: %d\n",pheptoan(thuong,a,b));
    return 0;
}