#include <stdio.h>

int *ptr;
void count(){
    static int a = 0;
    ptr = &a;
    printf("%d\n",++a);
}
int main()
{
    count();
    count();
    *ptr = 10;
    count();
    return 0;
}