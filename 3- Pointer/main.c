// #include <stdio.h>

// int main()
// {
// // int a[5] = { 5,8,2,6,7 };
// // 	int* p = &a[1];
// // 	p += 1;
// // 	printf("%d", p[1]);
//     unsigned char a = 'γ';
//     printf("%d",a);
// }

#include <stdio.h>

int main()
{
    char *str = "Tuan";
    char *str1 = "Tuan";
    while (*str == *str1)
    {
        str++;
        str1++;
    }
    printf("Hello World");

    return 0;
}