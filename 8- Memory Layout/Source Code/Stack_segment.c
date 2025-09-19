#include <stdio.h>

void test()
{
    double a = 0; //nắm trên phân vùng stack
    const int c = 20; //nắm trên phân vùng stack có thể thay đổi giá trị thông qua con trỏ
    int *ptr = &c; //nắm trên phân vùng stack
    *ptr = 30;
    printf("%d",c);
}

int main()
{
    int a = 10; //nắm trên phân vùng stack
    int b = 20; //nắm trên phân vùng stack
    test();
}