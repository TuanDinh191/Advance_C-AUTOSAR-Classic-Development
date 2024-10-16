#include <stdio.h>

int main()
{
    int a = 10,b =20;

    int *const ptr = &a; //Khai báo hằng con trỏ
   
   /*Không thể thay đổi địa chỉ sang biến 
    khác khi dùng hằng con trỏ */
    ptr = &b; 

    /*Hằng con trỏ có thể thay đổi giá trị địa chỉ của biến đó 
    thông qua deference*/
    *ptr = 30;
    printf("%d\n",*ptr);
    return 0;
}