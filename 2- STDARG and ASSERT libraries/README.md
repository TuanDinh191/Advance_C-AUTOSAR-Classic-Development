
# Thư viện STDARG và ASSERT
#### 1.Thư viện STDARG
#### - Định nghĩa: 
- Giống với macro variadic thì thư viện stdarg dùng để thao tác với các tham số đầu vào của một hàm là không xác định.
#### - Cách dùng:
  - ` va_list `: Có kiểu dữ liệu là char*. Khi đã khai báo trong một hàm thì nó sẽ biến các tham số truyền vào hàm sẽ thành một chuỗi;
 -  `va_start(value, label)`: Có tham số truyền vào là value là biến mang kiểu `va_list`, và label có kiểu là string. `va_start` dùng để tách dữ liệu mình cần thao tác vào một mảng char(ký tự) riêng bằng cách so sánh chuỗi giữa value và label.
- `va_arg(value, kiểu dữ liệu)`: Có tham số truyền vào là value là biến mang kiểu `va_list`, tham số thứ 2 truyền vào để ép kiểu dữ liệu. Khi dùng `va_arg` thì sẽ lấy ra 1 phần tử đầu tiên trong mảng ký tự được tạo ra bởi `va_start` có kiểu dữ liệu mà mình đã ép, lần gọi tiếp theo sẽ lấy phần tử tiếp theo của mảng ký tự.
- `va_end(value)`: Sau khi đã dùng xong thao tác truyền vào của một hàm thì cần dùng `va_end` để thu hồi lại vùng nhớ đã thao tác của biến value có kiểu dữ liệu là `va_list`.
#### - Ứng dụng:
 ``` javascript
 #include <stdio.h>
 #include <stdarg.h>

int Average_monthly_rain(int month_count, ...)
{
  va_list args; 
  /*
  - Biến args là một con trỏ có dữ liệu là args
  - Va_list args => char *args = "int month_count,23,54,43"
  ...*/
  
  va_start(args, month_count);
  /*
  - Sau khi tách với chuỗi args thì có mảng kí tự là [23, 54, 43];
  */
  
  printf("%d\n",va_arg(args,int)); //In ra giá trị lấy ra từ mạng ký tự là 23
  printf("%d\n",va_arg(args,int)); //In ra giá trị lấy ra từ mạng ký tự là 54
  printf("%d\n",va_arg(args,int)); //In ra giá trị lấy ra từ mạng ký tự là 43

  va_end(args); //Thu hồi vùng nhớ biến args
  
  return 0;
}

int main ()
{
  Average_monthly_rain(3,23,54,43);
  return 0;
}

```
#### 2. Thư viện Assert
#### - Định nghĩa: 
- Dùng để kiểm tra điều kiện, khác với điều kiện `if/else` thì khi điều kiện đúng sai thì vẫn thực thi chương trình thì assert khi đúng thì vẫn thực thi chương trình nhưng khi điều kiện sai sẽ dừng hẳn chương trình kèm theo một thông điệp lỗi và báo thêm cụ thể là file nào dòng nào trong code chạy điều kiện sai.
#### - Cách dùng:
- assert(điều kiện && "thong diep loi")
#### - Ứng dụng:

``` javascript
#include <assert.h>

int main()
{
    int x = 7;
    assert(x==6 && "x phai bang 6");
    return 0;
}
```
In ra terminal:

Assertion failed: x==6 && "x phai bang 6", file C:\Users\Admin\Desktop\ok\main1.c, line 7