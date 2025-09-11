#include <stdio.h>

#define sum(...)                                     \
int arr[]= {__VA_ARGS__};                            \
int result = 0;                                      \
for (int i = 0; i<(sizeof(arr)/sizeof(arr[0]));++i)  \
{                                                    \
    result+= arr[i];                                 \
}                                                    \
printf("%d",result);                                
int main()
{
   sum(1,2,3,4,5);
}