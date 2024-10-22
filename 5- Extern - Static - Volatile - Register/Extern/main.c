#include <stdio.h>

extern int a;
extern int b;
int add(int a, int b);
int minus(int a, int b);
int main()
{
    printf("%d\n",add(a,b));
    printf("%d\n",minus(a,b));
    return 0;
}