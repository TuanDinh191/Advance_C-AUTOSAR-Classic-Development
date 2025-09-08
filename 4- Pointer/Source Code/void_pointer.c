#include <stdio.h>
#include <string.h>
int main()
{
    void *ptr;

    int a = 10;
    ptr = &a;
    printf("dia chi: %p, gia tri: %d\n", ptr, *(int *)ptr);
    //Để đọc giá trị mà biến void ptr trỏ thì phải ép một kiểu dữ liệu cụ thể

    double b = 12.43;
    ptr = &b;
    printf("dia chi: %p, gia tri: %lf\n",ptr, *(double *)ptr);

    char c = 'C';
    
    char* str = "hello world";
    
    void *ptr1[] = {&a,&b,&c,str};
    printf("ptr[1] = %d\n",*(int *)ptr1[0]);
    printf("ptr[2] = %lf\n",*(double *)ptr1[1]);
    printf("ptr[3] = %c\n",*(char *)ptr1[2]);
    printf("ptr[4] = %s\n",(char *)ptr1[3]);
    printf("%d",sizeof(ptr1[3]));
    for(int i = 0; i<strlen(str); i++)
    {
        printf("str[%d] = %c\n",i,*((char *)ptr1[3] +i));
    }
}