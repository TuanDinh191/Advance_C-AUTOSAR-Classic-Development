#include <stdio.h>

#define CREATE_STRING(cmd)  #cmd
int main()
{
   printf("%s",CREATE_STRING(hello_world));
   return 0;
}