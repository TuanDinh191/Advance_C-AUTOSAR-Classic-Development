#include <stdio.h>

int a; //nằm trên phân vùng bss

double b = 0; //nằm trên phân vùng bss

int *ptr = NULL ; //nằm trên phân vùng bss

static double c = 0; //nằm trên phân vùng bss

const int d = 0; //nắm trên phân vùng bss nhưng chỉ đọc (bss - read only)

void test()
{
    static int e; //nằm trên phân vùng bss

}