#include <stdio.h>

int main()
{
    int a = 10,b = 5;

    //Con trỏ hằng ptr trỏ đến địa chỉ của biến a
    const int *ptr = &a;
  //int const *ptr = &a;

    /*Không thể thay đổi giá trị của một biến thông qua con trỏ 
    dùng constant*/
    *ptr = 10;
    

    a = 5; //Muốn thay giá trị chỉ có thông qua biến 

    printf("%d\n",*ptr);
    
    ptr = &b; //Con trỏ hằng có thể trỏ đến địa chỉ của biến khác


    /*Không thể thay đổi giá trị của một biến thông qua con trỏ
    này trỏ đến biến khác*/
    *ptr = 20;

    return 0;
}