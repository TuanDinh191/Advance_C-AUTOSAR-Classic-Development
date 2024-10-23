#include <stdio.h>

extern int b;
void display();
extern int a;
void showfile();

int main()
{
    printf("%d",b);
    display();
    printf("%d",a);
    showfile();
    return 0;
}