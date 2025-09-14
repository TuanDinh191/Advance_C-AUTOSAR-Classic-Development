# Bai 5 Storage Classes
#### 1. Extern
#### - Định nghĩa:
- Để dùng một biến hoặc một mảng hoặc một hàm của file khác khi đang dùng file chính ngoài việc khai báo include cái file khác thì việc dùng extern sẽ tiết kiệm bộ nhớ và thời gian trong giai đoạn compile file. Khi dùng từ khóa extern đối với một biến hoặc một hàm hoặc một mảng thì sẽ dùng lại một biến hoặc một hàm hoặc một mảng những gì file khác đã khai báo mà không dùng hết tất cả những gì mà file khác đã khai báo, tức là khi dùng extern thì file khác đều chia sẽ tài nguyên cho file có dùng extern.
- Chỉ sử dụng cho các biến/hàm là global.
- Chỉ được phép khai báo, không cho phép định nghĩa.
#### - Cách dùng:
- File 1: Second_file.c
```javascripst 
#include <stdio.h>

int a = 12;

int minus(int a, int b)
{
    return (b-a);
}

```
- File 2: Third_file.c
```javascripst 
#include <stdio.h>

int b = 23;

int add(int a, int b)
{
    return (a+b);
```
- File chính: main.c
```javascript
#include <stdio.h>

extern int a;
extern int b;
int add(int a, int b);
int minus(int a, int b);
int main()
{
    printf("%d\n",add(a,b));
    printf("%d\n",minus(a,b));
    return 0;
}
```
- Để chạy file main.c bắt buộc phải dùng lệnh `gcc main.c second_file.c third_file.c -o main` dể liên kết tất cả các file để tạo ra file thực thi duy nhất.
- Sau khi đã tạo được file thực thi `main.exe` thì dùng lệnh `\main` để thực thi
#### 2. Static
#### - Định nghĩa:
- Static cục bộ: Khi một biến static được khai báo trong một hàm thì khi sử dùng hàm đó lần thứ 1 thì biến static nó sẽ vẫn giữ giá trị sau khi hàm kết thúc, những lần dùng hàm này cho mấy lần sau thì nó dựa vào giá trị đã lưu biến static của hàm trước và sau khi kết thúc hàm thì giá trị được lưu lại xuyên suối chương trình để dùng cho hàm phía sau nếu tiếp tục gọi.  
#### - Cách dùng:
- Static cục bộ: Trong hàm count() nếu biến a khai báo không kèm với từ khóa `static` thì sau khi kết thúc hàm thì biến a bị thu hồi vùng nhớ sau những lần gọi hàm tiếp theo khi đó biến a khởi tạo lại đến vùng nhớ khác nếu hàm gọi lại, đối với hàm có biến khi dùng từ khóa `static` thì giá trị a tiếp tục lưu tại địa chỉ đó khi hàm kết thúc để dùng cho lần gọi hàm tiếp theo. 
```bash
#include <stdio.h>

void count(){
    static int a = 0;
    printf("%d\n",++a);
}
int main()
{
    count(); //In ra 1
    count(); //In ra 2
    count(); //In ra 3
    return 0;
}
```
- Có thể dùng con trỏ thay đổi biến dùng static
```bash
#include <stdio.h>

int *ptr;
void count(){
    static int a = 0;
    ptr = &a;
    printf("%d\n",++a);
}
int main()
{
    count(); //In ra 1
    count(); //In ra 2
    *ptr = 10;
    count(); //In ra 11
    return 0;
}
```
- Static toàn cục: Khi đối tượng toàn cục được khai báo với từ khóa `static` thì phạm vi sử dụng của đối tượng đó chỉ giới hạn trong file đó. Các file khác khi khai báo `extern` đối với đối tượng đó thì khi compile sẽ báo lỗi. Ứng dụng dùng để thiết kế thư viện

- File 1: second_file.c
```javasript
#include <stdio.h>
#include "second_file.h"

static int a = 20;

int b = 30;

static void showfile(){
    printf("This is second file.c \n");
}

void display()
{
    printf("Hello world\n");
}
```
- File 2: Second_file.h
```bash
#ifndef _FILE1_H
#define _FILE1_H

static int a;
int b;

static void showfile();
void display();
#endif
```
- File 3: static_toan_cuc.c
```bash
#include <stdio.h>

extern int b;
void display();
extern int a;
void showfile();

int main()
{
    printf("%d",b);
    display();
    printf("%d",a);
    showfile();
    return 0;
}
```
- Khi dùng từ khóa extern với static toàn cục với biến a và vs hàm showfile() trong file `static_toan_cuc.c` thì lúc compile máy tính sẽ báo lỗi.
#### Ứng dụng:
- Vào các thư viện không cho các file khác sử dụng từ khóa `extern` để sử dụng hàm từ thư viện.
#### 3. Register
#### - Định nghĩa:
- Khi thực hiện phép toán số học đối với một biến thì đầu tiên nó sẽ lưu vào RAM sau đố lưu vào register tiếp đến sẽ chuyển vào bộ ALU để thực hiện phép toán số học sau đó sẽ trả về kết quả cho register và trả lại giá trị về RAM.
- Khi khai báo `register` đối với một biến thì khi thực hiện phép toán số học thì biến sẽ không lưu vào RAM nữa mà nó sẽ lưu vào register sau đó chuyển giá trị đến ALU để thực hiện phép toán số học và trả về lại giá trị cho register.
- Một biến được khao báo với `register` sẽ giúp việc tính toán nhanh hơn tăng hiệu suất của chương trình để làm cho chương trình thực thi nhanh hơn.
- Chỉ áp dụng cho các biến khai báo cục bộ không thể khai báo toàn cục.
- Các biến nếu được khai báo `register` thì chỉ là đề xuất cho trình biên dịch và không đảm bảo biến sẽ được lưu trong thanh ghi. Trình biên dịch sẽ xem xét số lượng thanh ghi trên máy tính có đủ để lưu trữ cho biến khai báo `register` hay không nếu không sẽ được lưu vào RAM. Các biến `register` sau khi dùng sẽ được thu hồi thanh ghi đi để cho các biến khác sử dụng.
#### - Cách dùng:
- Ví dụ dưới đây cho thấy nếu biến i khi dùng register sẽ in ra thời gian chạy chương trình nhanh hơn so với không dùng register.
```bash
- #include <stdio.h>
#include <time.h>

int main() {
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    register int  i;

    // Đoạn mã của chương trình
    for (i = 0; i < 2000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);

    return 0;
}
```
#### Ứng dụng: 
- Vào các biến thực hiện phép toán số học.
#### 4. Volatile
#### - Định nghĩa:
 - Volatile sẽ được ứng dụng trong lập trình nhúng nhiều hơn, cụ thể khi viết chương trình một cảm biến để nhận dữ liệu thu thập được trong một dòng while. Nếu trong lúc thực thi chương trình sẽ kiểm tra cảm biến để thu thập dữ liệu cảm biến đó có cập nhật hay không nếu một khoảng thời gian mà không thấy cập nhật thì chương trình  sẽ tối ưu hóa và xóa biến đó đi khỏi chương trình khi đó nếu một khoảng thời gian sau cảm biến thu thập được dữ liệu mới thì không thể cập nhật biến đó được nữa để tránh tình trạng này ta dùng từ khóa volatile.
 - Volatile cũng có thể được ứng dụng nếu chương trình điều chỉnh mức độ tối ưu hóa của compiler (trình biên dịch).
 - Volatile cũng được ứng dụng trong các thanh ghi của vi điều khiển nếu có tác động bên ngoài bất ngờ hoặc ngoài sự kiểm soát của chương trình thay đổi giá trị thanh ghi.  
 ```
 #include "stm32f4xx.h"

uint8_t* reg = (uint8_t *)0x20000000;
volatile uint8_t* value = 0;

int main()
{
    while(1)
    {
        value = *reg;
        if (value != 0)break;
    }
    return 0;
}
 ```

