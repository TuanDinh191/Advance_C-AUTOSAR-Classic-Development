# Bài 4: Memory layout
#### 1. Memory layout
#### - Định nghĩa:
- Các chương trình thực thi như main.exe trên windows hay main.hex trên vi điều khiển thường sẽ được lưu trên một phân vùng nhớ trước khi được copy vào RAM để thực thi hoặc khi chương trình đang chạy thì các biến sẽ lưu giá trị sẽ lưu vào phân vùng nhớ cụ thể .Trong máy tính sẽ có 5 phân vùng nhớ cụ thể: text, data, bss, heap, stack.

#### 2. Các phân vùng nhớ trong máy tính
#### - Phân vùng text (Text Segment) (Code Segment): 
- Chứa mã máy là nơi chứa các tập lệnh thực thi.
- Quyền truy cập: Chỉ có quyền đọc và thực thi, nhưng không có quyền ghi.
- Đối với hệ điều hành MacOS: Sử dụng compiler CLang đối với biến hằng số toàn cục hay chuỗi hằng (string literal) thì sẽ được lưu vào phân vùng text.
#### - Phân vùng Data  (Data Segment): 
- Quyền truy cập là đọc và ghi. Đối với biến hằng số toàn cục khác 0 nằm trên phân vùng data thì chỉ có quyền đọc (rdata).
- Chứa các biến toàn cục, biến dữ liệu tự định nghĩa (kể cả các thành phần) được khởi tạo giá trị khác 0.
- Chứa các biến static (global + local) được khởi tạo giá trị khác 0.
- Đối với hệ điều hành Windows: Sử dụng compiler MingW đối với biến hằng số toàn cục khác 0 hay chuỗi hằng thì sẽ được lưu vào phân vùng data.
- Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.
Ví dụ:
```
#include <stdio.h>

int a = 5;     // nằm trên phân vùng data

const b = 10;  // nằm trên phân vùng data

int *ptr = &a; // địa chỉ của con trỏ ptr nằm trên phân vùng data

static double c = 3.14;  // nằm trên phân vùng data

void test()
{
    static int d = 10;  // nằm trên phân vùng data
}
```
#### - Phân vùng bss (Bss Segment):
- Quyền truy cập là đọc và ghi. Đối với biến hằng số toàn cục bằng 0 hoặc không gán giá trị sẽ nằm trên phân vùng bss thì chỉ có quyền đọc (bss-readonly).
- Chứa các biến toàn cục, biến dữ liệu tự định nghĩa (kể cả các thành phần) khởi tạo giá trị bằng 0 hoặc không gán giá trị.
- Chứa các biến static (global + local) được khởi tạo giá trị bằng 0 hoặc không gán giá trị.
- Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.
Ví dụ:
```
#include <stdio.h>

int a; //nằm trên phân vùng bss

double b = 0; //nằm trên phân vùng bss

int *ptr = NULL ; //nằm trên phân vùng bss

static double c = 0; //nằm trên phân vùng bss

const int d = 0; //nắm trên phân vùng bss nhưng chỉ đọc (bss - read only)

void test()
{
    static int e; //nằm trên phân vùng bss

}
```
#### - Phân vùng Stack:
- Quyền truy cập: Đọc và ghi. Đối với biến hằng số cục bộ có thể thay đổi giá trị thông qua con trỏ.
- Chứa các biến cục bộ, tham số truyền vào.
- Sau khi ra khỏi hàm, sẽ thu hồi vùng nhớ.

```
#include <stdio.h>

void test()
{
    double a = 0; //nắm trên phân vùng stack
    const int c = 20; //nắm trên phân vùng stack có thể thay đổi giá trị thông qua con trỏ
    int *ptr = &c; //nắm trên phân vùng stack
    *ptr = 30;
    printf("%d",c);
}

int main()
{
    int a = 10; //nắm trên phân vùng stack
    int b = 20; //nắm trên phân vùng stack
    test();
}
```
#### - Phân vùng heap:
- Được cấp phát động.
- Cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu.
- Đối với cấp phát tĩnh thì sẽ có thể xảy ra tình trạng lãng phí bộ nhớ hoặc không đủ bộ nhớ, việc dùng cấp phát động sẽ linh động trong việc cấp phát bao nhiêu byte.
- Các hàm như malloc(), calloc(), realloc(), và free() được sử dụng để cấp phát và giải phóng bộ nhớ trên heap. Cả 3 hàm malloc, calloc và realloc đều trả về là con trỏ void nên khi dùng phải ép kiểu dữ liệu cụ thể để cho việc đọc và ghi đúng. Hàm free sẽ thu hồi vùng nhớ từ địa chỉ truyền vào.
Ví dụ:
```
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
   
    //malloc(5); //cấp phát 5 ô địa chỉ (5 byte): 0x01 0x02 0x03 0x04 0x05 nằm trên phân vùng heap
    int *ptr = NULL;
    int size = 20;
    ptr = (int *)malloc(size*sizeof(int)); //Cấp phát 20 phần tử tương đương 80 byte
    ptr[0] = 0;
    for (int i =  0; i<size; ++i)
        ptr[i] = 1+i;

    for (int i =0; i<size; ++i)
        printf("%p %d\n", ptr+i, ptr[i]);

    printf("\n\n");
    ptr = (int *)realloc(ptr, 40*sizeof(int)); //Cấp phát thêm (40 - 20) phần tử thêm 80 ô địa chỉ
  
    ptr[0] = 0;
    for (int i =  0; i<size*2; ++i)
        ptr[i] = 1+i;

    for (int i =0; i<size*2; ++i)
        printf("%p %d\n", ptr+i, ptr[i]);
    free(ptr); //Thu hồi vùng nhớ
    return 0;
}
```
#### - Sự khác biệt giữa malloc, calloc và realloc
- Malloc : Cấp phát vùng nhớ , dữ liệu không được khởi tạo, dữ liệu tại vị trí cấp phát ở mỗi vùng nhớ là rác.
- Calloc : Cấp phát vùng nhớ , dữ liệu được khởi tạo, dữ liệu tại vị trí cấp phát ở mỗi vùng nhớ là 0.
- Realloc: Thay đổi kích thước chỉ dùng được khi có 1 vùng nhớ đã cấp phát, có thể tăng kích thước bằng cách cấp phát thêm bộ nhớ, giảm kích thước thì vùng nhớ sẽ bị cắt giảm, dữ liệu được cấp phát thêm không được khởi tạo có giá trị là rác.
#### - Khi nào sử dụng Stack và khi nào sử dụng heap:
- Sử dụng Stack khi muốn hệ thống quản lý tự động, tốc độ nhanh biết được chính xác dữ liệu phân bố trước khi biên dịch sử dụng dữ liệu không quá lớn, không cần sử dụng dữ liệu khi kết thúc hàm.
- Sử dụng heap khi sử dụng đối tượng, cấu trúc dữ liệu lớn, không biết được chính xác dữ liệu phân bố trước khi biên dịch sử dụng dữ liệu lâu dài hơn khi ỏ ngoài phạm vi hàm. 
