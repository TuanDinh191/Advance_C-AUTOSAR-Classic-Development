#include <stdio.h>

#define SIZE 10

#ifdef SIZE

int arr[SIZE];

#endif

#ifndef SIZE
#define SIZE 5

int arr[SIZE] = {1,2,3,4,5};

#endif
int main()
{
    for(int i = 0;i<SIZE; i++){
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}