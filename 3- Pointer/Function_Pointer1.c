#include <stdio.h>

void displayHello()
{
     printf("Hello_world\n");
}

int add(int a,int b)
{
    return a+b;
}
int main()
{
    /*Khai báo con trỏ hàm.Khi khai báo con trỏ hàm thì
    phải khai báo giống kiểu trả về của một hàm và kiểu dữ liệu 
    tham số hàm truyền vào của hàm mà con trỏ đó trỏ đến*/
    void (*ptrTofunc1)();

    //Gán địa chỉ của hàm displayHello
    ptrTofunc1 = displayHello;
    //ptrTofunc = &displayHello;
    
    //Gọi hàm displayHello thông qua con trỏ hàm
    ptrTofunc1();
    
    //Khai báo con trỏ hàm thứ 2 
    int (*ptrTofunc2)(int ,int);

    int a = 20, b = 30; 
    //Gán địa chỉ của hàm add  
    ptrTofunc2 = &add;

    //Cách gọi hàm thứ hai 
    printf("%d",(*ptrTofunc2)(a,b));

    return 0;
}