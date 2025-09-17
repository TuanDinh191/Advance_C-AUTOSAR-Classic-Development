# Bài 7: Struct - Union
#### 1. Struct
#### - Định nghĩa:
- Là một kiểu cấu trúc dữ liệu do người dùng tự định nghĩa, bằng cách nhóm các kiểu dữ liệu khác nhau lại. Kích thước của struct là tổng của các thành phần cộng với padding (nếu có). Các thành phần sử dụng vùng nhớ khác nhau.
#### - Cách dùng:
- Cách khai báo thứ nhất:
```javascripst 
struct Data{
    int a;
    double b;
    char c;
};

struct Data data1,data2;
```
- Cách khai báo thứ 2:
```
typedef struct
{
    int a;
    double b;
    char c;
} Data;

Data data1,data2;
```
- Cách gán dữ liệu:
```
struct Data{
    int a;
    double b;
    char c;
};

struct Data data1,*data2;
data2 = &data1;
int main()
{
    data1.a = 10;
    data1.b = 20;
    data2->a =30;
    return 0;
}
```
#### - Cách tính kích thước của một struct:
- Data alignment: Tùy thuộc vào kiểu dữ liệu của thành phần trong struct thì các thành viên  trong struct được cấp phát tại địa chỉ có giá trị là bội số của kiểu dữ liệu mà nó khai báo. Giá trị địa chỉ của một struct khi được cấp phát sẽ bắt đầu là số chẵn, nếu sử dụng bộ nhớ quá nhiều ví dụ RAM hết vùng địa chỉ là số chẵn để cấp phát thì sẽ cấp phát tại vùng địa chỉ là số lẻ.
``` 
double (8 bytes): 0x00, 0x08, 0x10, 0x18,....
int, int32_t , uint32_t (4 bytes): 0x00, 0x04, 0x08, 0x0C,...
float, int16_t, uint16_t (2 bytes): 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A,...
char, int8_t, uint8_t (1 byte): 0x00, 0x01, 0x02
```
- Padding: Trong struct và union có các thành phần việc thêm những byte trống vào giữa các thành phần để cho phù hợp căn chỉnh của CPU, byte đệm được thêm vào để đảm bảo data alignment.
- Cách tính kích thước:
```
typedef struct {
    uint8_t var1;    // 1 byte + 7 padding 
    uint64_t var2;   // 8 byte
    uint32_t var3;   // 4 byte 
    uint16_t var4;   // 2 byte + 2 padding
}frame;
```
- Giả sử ta có một cái struct như trên, để tính được kích thước thì ta phải xác định trong struct đó thì có thành phần nào có kích thước dữ liệu lớn nhất dùng để cấp phát địa chỉ ô nhớ. Đầu tiên ta sẽ cấp phát 8 ô địa chỉ (var2 có kích thước dữ liệu lớn nhất trong các thành phần) giá trị biến var1 chiếm 1 byte sẽ lưu vào địa chỉ ô nhớ đầu tiên là sẽ còn 7 ô địa chỉ còn lại, var 2 thì chiếm đến 8 byte 7 ô địa chỉ còn lại này không đủ cấp phát cho biến var 2 nên sẽ được padding, tiếp trục cấp phát thêm 8 ô địa chỉ để lưu biến var2, tiếp tục đến biến var3 cấp phát thêm 8 địa chỉ ô nhớ vì 8 ô địa chỉ cấp phát cho biến var2 đã dùng hết, 4 byte đầu tiên của ô nhớ đã được dùng và còn lại 4 byte, 2 byte của biến var4 dùng tiếp 2 ô nhớ và 2 ô nhớ còn lại thì sẽ được padding tổng cộng kích thước struct này là 24 bytes.
#### Bit-Field: 
- Là một thành phần đặc biệt trong struct có thể chỉ định số lượng bit cụ thể cho 1 thành phần mà có kiểu dữ liệu là một số nguyên. Thay vì sử dụng toàn bộ kích thước của 1 kiểu dữ liệu có thể cắt nhỏ theo số bit, giúp tiết kiệm không gian bộ nhớ và mô tả chính xác hơn ý nghĩa của dữ liệu ví dụ chỉ cần lưu trạng thái bật/tắt chỉ cần 1 bit.
- Chỉ áp dụng cho member khai báo trên struct.
- Các thành phần khi dùng kỹ thuật bit-field sẽ không có giá trị địa chỉ cụ thể.
- Các thành phần có cùng kiểu dữ liệu sẽ chia sẽ chung 1 vùng nhớ.
```
typedef struct{
    //Cap phat 2 byte
    uint8_t a:2;
    uint8_t b:3;
    //Cap phat 2 byte
    uint16_t c:10;
}data;
```
#### 2. Union
#### - Định nghĩa: 
- Tương tự với struct thì union cũng là một kiểu dữ liệu do người dùng tự định nghĩa. Nhưng có kích thước khác với struct là kích thước của thành phần lớn nhất cộng với padding (nếu có). Các thành phần đều sử dụng chung một vùng nhớ khi có 1 thành phần nào thay đổi thì các thành phần khác cũng thay đổi theo.
- Cơ chế padding giống với struct.

#### - Cách dùng:
- Cách khai báo thứ nhất:
```javascripst 
union Data{
    int a;
    double b;
    char c;
};

Data data1,data2;
```
- Cách khai báo thứ 2:
```
typedef union{
    int a;
    double b;
    char c;
}Data;

Data data1,data2;
```
- Cách gán dữ liệu:
```
union Data
{
    uint8_t var1;  //1 byte + 3 padding 
    uint32_t var2; //4 byte
    uint16_t var3; //2 byte + 2 padding
};

union Data data;


int main()
{
    printf("Size of frame: %d\n",sizeof(data));
    data.var1 = 5;
    data.var2 = 6;
    data.var3 = 50;
    printf("var1 = %d\n",data.var1); //50
    printf("var2 = %d\n",data.var2); //50
    printf("var3 = %d\n",data.var3); //50
}
```
+ Trường hợp 1: Kích thước của Union phụ thuộc vào thành viên có kiểu dữ liệu là lớn nhất.
```
#include <stdio.h>
#include <stdint.h>
union Data
{
    uint8_t var1;  //1 byte + 3 padding 
    uint32_t var2; //4 byte
    uint16_t var3; //2 byte + 2 padding
};

union Data data;


int main()
{
    printf("Size of frame: %zd\n",sizeof(data));
                            //0x03      0x02    0x01     0x00                            
    data.var2 = 4294967200; //11111111 11111111 11111111 10100000

    printf("var1 = %d\n",data.var1); //160 - 0b10100000
    printf("var2 = %u\n",data.var2); //4294967200 - 0b11111111111111111111111110100000
    printf("var3 = %d\n",data.var3); //65440 - 0b11111111 10100000
    
    data.var3 = 600; //0b 00000010 01011000
    printf("var1 = %d\n",data.var1); //88 - 0b01011000
    printf("var2 = %u\n",data.var2); //4294902360 - 0b11111111 11111111 00000010 01011000
    printf("var3 = %d\n",data.var3); //600 - 0b00000010 01011000
    
    
}
```
+ Trường hợp 2: Kích thước của Union phụ thuộc vào thành viên có số byte chiếm nhiều nhất.
```
//Đầu tiên ta sẽ cấp phát 8 byte để lưu trữ cho union dưới đây nhưng do là ở thành viên thứ 2 có phần tử thứ 5 là b[4] 8 byte không đủ lưu trữ b[4] nên ta sẽ cấp phát lại lần thứ 2 cộng thêm 8 byte sẽ là 16 byte 
typedef union data
{
    //Cấp phát 16 byte 
    uint8_t a; //a(0x00) + 15padding 
    uint16_t b[5]; 
    //b[0](0x00 - 0x01) 
    //b[1](0x02 - 0x03)
    //b[2](0x04 - 0x05) 
    //b[3](0x06 - 0x07) 
    //b[4](0x08 - 0x09) + 6 padding
    uint32_t c; //c(0x00 - 0x03) + 12 padding
    double d; //d (0x00 - 0x07) + 8 padding
}Data;

//Trường hợp máy tính hoặc hệ thống sử dụng quá nhiều bộ nhớ lúc đó ví dụ RAM hết vùng địa chỉ là số chẵn để cấp phát thì sẽ cấp phát tại vùng địa chỉ bắt đầu là số lẻ.
{
    //Cấp phát 16 byte 
    uint8_t a; //a(0x01) + 15padding 
    uint16_t b[5]; 
    //b[0](0x02 - 0x03) 
    //b[1](0x04 - 0x05)
    //b[2](0x06 - 0x07) 
    //b[3](0x08 - 0x09) 
    //b[4](0x0a - 0x0b) + 6 padding (0x01, 0x0c - 0x10)
    uint32_t c; //c(0x04 - 0x07) + 12 padding (0x01 - 0x03, 0x08 - 0x010)
    double d; //d (0x08 - 0x0f) + 8 padding(0x01 - 0x07, 0x10)
}Data;
```
- Có thể lồng `struct` vào trong 1 cái `Union` là 1 thành viên của Union dùng để ứng dụng tổ chức các dữ liệu thành 1 frame dữ liệu để truyền đi hoặc có thể ứng dụng quản lý toàn bộ chân GPIO, ... .
```
typedef union
{
    struct
    {
        uint8_t id[2];          //uint16_t id
        uint8_t data[4];        //uint32_t data
        uint8_t check_sum[2];   //uint8_t check_sum
    } data;
    uint8_t frame[8];
} Data_Frame;
```

