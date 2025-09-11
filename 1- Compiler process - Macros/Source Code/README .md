
# Bai 1 Compiler Process - Macros 
- Khi tạo ra một chương trình để thực thi một tác vụ gì đó thì từ lúc ta dùng editor để viết code cho đến giai đoạn tạo ra file thực thi một tác vụ nào đó làm sao đó để từ ngôn ngữ bậc cao (C, C++, C#...) mà ta đang viết sang ngôn ngữ máy để máy tính hiểu được là những chuỗi nhị phân thì nó sẽ trải qua 4 giai đoạn: Preprocessor  (Tiền xử lí), Compiler (Quá trình biên dịch), Assembler (Hợp dịch), Linker (Liên kết).
#### 1. Preprocessor (Tiền xử lí)
- Chương trình từ ngôn ngữ bậc cao qua quá trình tiền xử xí sẽ cho ra file định dạng có đuôi là .i
- Để tạo ra file đuôi .i ta sẽ dùng trình biên dịch gcc đối với ngôn ngữ C hoặc g++ đối với ngôn ngữ C++ cú pháp đối với chương trình bằng ngôn ngữ C: `gcc -E main.c -o main`
- Bên trong file đuôi .i sẽ là bao gồm chương trình chính và kết quả xử lý các macro chẳng hạn như chỉ thị bao hàm tệp `#include` là sao chép toàn bộ thư viện, mã nguồn được thêm vào chương trình chính và các tên sẽ được định nghĩa lại bằng macro `#define` sẽ được thay thế bên trong file đuôi .i .... và xóa hết tất cả các comments có trong chương trình chính.
#### - Các macro và toán tử hay được dùng:
- `#define`: là chỉ thị định nghĩa tên dùng để thay thế cho một giá trị hoặc là chuỗi có thể dùng `#define` để thay thế cho một hàm.
``` 
    #include <stdio.h>

    //Định nghĩa tên thay thế cho 1 giá trị
    #define SIZE 5

    //#Định nghĩa tên thay thế cho 1 hàm 
    #define CREATE_FUNC(name, cmd) \
    void name()                    \
    {                              \
        printf(cmd);               \
    }                                               

    //Tạo hàm 
    CREATE_FUNC(func1,"This is function 1\n");
    CREATE_FUNC(func2,"This is function 2\n");
    CREATE_FUNC(func3,"This is function 3\n");

    int main()
    {
    int arr[SIZE] = {12,65,54,64,22};
    
    for (int i = 0; i<SIZE; ++i)
        printf("arr[%d]: %d\n",i,arr[i]);
    
    //Gọi hàm
    func1();
    func2();
    func3();
    return 0;
    }
```
- `#undef`: Hủy định nghĩa cho một tên được định nghĩa bằng `#define` sẽ `#define` lại một giá trị khác hoặc chuỗi khác.
```
#define SIZE 5
#undef  SIZE
#define SIZE 10

```
- `#if`,`#elif`,`#else`,`#endif`: là chỉ thị biên dịch có điều kiện dùng để kiểm tra điều kiện của một cái macro dùng cho macro chẳng hạn là `#define` sau khi dùng `#if`,`#elif`,`#else` thì ta phải dùng `#endif` để kết thúc điều kiện.
```
#define ESP32       1 
#define STM32       2 
#define ATmega324   3 

#define MCU STM32

#if MCU == STM32 
    void digitalWrite(Pin pin, Status state) {
        if (state == HIGH){
            GPIOA->ODR |= (1 << pin);
        }
        else {
            GPIOA->BSRR &= ~(1<<pin);
        } 
}

#elif MCU == ESP32
   void digitalWrite(Pin pin, Status state) {
       if (state == HIGH){
           GPIO.out_w1ts |= (1<< pin);
       }
       else {
           GPIO.out_w1tc =  (1<<pin);
       }
}

#else 
    void digitalWrite(Pin pin, Status state) {
        if (state == HIGH){
            PORTA |= (1<<pin);
        }
        else {
            PORTA &= ~(1<<pin);
        } 
}

#endif
```
- `#ifdef`, `#ifndef` : Dùng để kiểm tra xem một macro đã được định nghĩa (`#ifdef`) hay là chưa (`#ifndef`) sau khi dùng `#ifdef`, `#ifndef` thì ta phải dùng `#endif` để kết thúc điều kiện. `#ifdef` và `#ifndef` thường được sử dụng trong thiết kế thư viện khi `#include` thư viện 2 lần chở lên để tránh bị lỗi định nghĩa 2 lần cho 1 biến hoặc 1 hàm. 

```
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
```
- Toán tử `#`: Dùng để chuẩn hóa đoạn văn bản thành chuỗi chỉ dùng trong định nghĩa macro `#define` có tham số truyền vào.
```
#include <stdio.h>

#define CREATE_STRING(cmd)  #cmd
int main()
{
   printf("%s",CREATE_STRING(hello_world));
   return 0;
}
```
- Toán tử `##`: Dùng để nối 2 cái chuỗi lại với nhau chỉ dùng trong định nghĩa macro `#define` có tham số.
```
#include <stdio.h>

#define CREATE_VAR(name)    \
int     int_##name;         \
char    char_##name;        \
double  double_##name     

#define CONCAT(a, b) a##b
int main()
{
    CREATE_VAR(test);
    int ab = 50;
   printf("%d",CONCAT(a, b));
   return 0;
}
```
- Toán tử variadic:
    + ... : Dùng cho hàm được định nghĩa bằng macro `#define` không xác định được tham số truyền vào, biểu thị các đối số không xác định.
    + __VA_ARGS_ : Dùng cho hàm được định nghĩa bằng macro `#define` không xác định được tham số truyền vào, thay thế bằng danh sách các đối số.


```
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
```
#### 2. Compiler (Quá trình biên dịch)
- Sau quá trình tiền xử lý sẽ đến quá trình biên dịch qua quá trình này sẽ chuyển ngôn ngữ bậc cao sang ngôn ngữ bậc thấp gần với tập lệnh bộ vi xử lí sẽ cho ra file đuôi .s là file assembly code (file hợp ngữ) có thể thao tác trực tiếp trên CPU có thể điều khiển các thanh ghi, quá trình này chuyển từ ngôn ngữ ta có thể hiểu được bắt đầu chuẩn bị sang ngôn ngữ máy ngoài ra quá trình này sẽ kiểm tra cú pháp trong chương trình của ta đã được viết đúng hay chưa.
- Câu lệnh để thực thi: `gcc -S main.i -o main.s`
#### 3. Assembler (Hợp dịch)
- Bước kế tiếp của quá trình biên dịch sẽ là quá trình hợp dịch từ file đuôi .s assembly code sẽ cho ra file đuôi .o là file object chính là file mà máy tính có thể hiểu được là file nhị phân chỉ chứa giá trị là 0 và 1. 
- Câu lệnh thực thi: `gcc -c main.s -o main.o`
#### 4. Linker (Liên kết)
- Quá trình cuối cùng sẽ là quá trình liên kết tất cả các file .o. Nếu có nhiều chương trình (nhiều file đuôi .c) thì sau 3 bước trên nó sẽ cho ra nhiều file .o thì qua trình liên kết tất cả file đuôi .o này để cho ra file thực thi cuối cùng là file đuôi .exe . 
- Câu lệnh thực thi: `gcc main.o test.o -o main`
