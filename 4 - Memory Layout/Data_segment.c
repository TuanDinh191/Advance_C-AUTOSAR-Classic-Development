#include <stdio.h>

int a = 5;     // nằm trên phân vùng data

const b = 10;  // nằm trên phân vùng data

int *ptr = &a; // địa chỉ của con trỏ ptr nằm trên phân vùng data

static double c = 3.14;  // nằm trên phân vùng data

void test()
{
    static int d = 10;  // nằm trên phân vùng data
}