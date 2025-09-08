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
    
    //Thông thường ta sẽ dùng con trỏ cấp 1 để lấy dữ liệu gửi về từ cảm biến   
    char *str = "Hello world";
 
    /*Ở đây nếu mà dùng hàm con trỏ có tham số truyền vào là con trỏ cấp 1 để 
    phân tích chuỗi "Hello" đầu tiên thì sau khi ra khỏi hàm thì giá trị địa 
    chỉ của con trỏ str phải tăng lên là 6 lần (theo kiểu char) sau khi thoát 
    khỏi hàm single_ptr dùng để giả sử để phân tích chuỗi thì khi in ra giá trị 
    str phải là World nhưng mà sau khi qua hàm single_ptr giá trị địa chỉ của 
    str vẫn không thay đổi vẫn sẽ in ra là "Hello World */
    single_ptr(str);
    printf("outside: %s\n",str);
    
    /*Qua hàm double_str có tham số truyền vào là con trỏ cấp 2 giả sử ta dùng
    nó để phân tách chuỗi "Hello" đầu tiên thì sau khi thoát khỏi hàm double_str 
    thì giá trị địa chỉ str sau khi in ra lúc này sẽ là world thôi tức là ta có thể 
    hiểu là sau khi dùng một hàm phân tách chuỗi rồi ta phải sang địa chỉ khác để 
    phân tách chuỗi khác nếu dùng hàm có địa chỉ là tham số là con trỏ cấp 1 thì sau
    khi phân tách thì giá trị địa chỉ của địa chỉ str vẫn không thay đổi khiến ta 
    không thể dùng hàm con trỏ có tham số là con trỏ cấp 1 để phân tách 
    chuỗi mới được*/
    double_ptr(&str);
    printf("outside: %s\n",str);
}