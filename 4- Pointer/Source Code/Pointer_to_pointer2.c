#include <stdio.h>

void single_ptr(char *ptr)
{
   ptr+=6;
}

void double_ptr(char **ptr)
{
    *ptr+=6;
}
int main()
{
    //Thong thuong ta se dung 
    char *str = "Hello world";


    single_ptr(str);
    printf("outside: %s\n",str);

    double_ptr(&str);
    printf("outside: %s\n",str);
}