#include <stdio.h>

#define CREATE_VAR(name)    \
int     int_##name;         \
char    char_##name;        \
double  double_##name     

#define CONCAT(a, b) a##b
int main()
{
    CREATE_VAR(test);
    int ab = 50;
   printf("%d",CONCAT(a, b));
   return 0;
}