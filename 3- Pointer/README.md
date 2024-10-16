
# Bai 3 Pointer
#### 1. Pointer
#### - Định nghĩa:
- Con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng khác (biến, mảng, hàm).
- Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch đồi với máy tính. Còn trên vi điều khiển thì phụ thuộc vào vi xử lí.
- Mặc dù kích thước của các kiểu dữ liệu con trỏ đều bằng nhau. Nhưng khi thực hiên các đọc, viết hoặc thực hiện phép tính toán số học trên con trỏ đều cho kết quả khác nhau.
#### - Cách dùng:
- Con trỏ trỏ đến địa chỉ của biến
```javascript
int a = 5; 
//Địa chỉ của biến a: 0x12 có giá trị là 5:

int *ptr = &a; 
//Địa chỉ của biến con trỏ ptr: 0xd2 nhưng có giá trị là 0x12 là địa chỉ của biến a

printf("%d",*ptr);
//In ra giá trị mà biến ptr trỏ đến địa chỉ của biến a kết quả sẽ trả về là 5; 
```
- Con trỏ trỏ đến địa chỉ của mảng
```javascript
#include <stdio.h>

int main()
{
    int mang[] = [1,2,3,4];
    /*Các giá trị trong mảng có giá trị địa chỉ là 
    mang[0] = 1  địa chỉ: 0X01;
    mang[1] = 2  địa chỉ: 0x05;
    mang[2] = 3  địa chỉ: 0x09;
    mang[3] = 4  địa chỉ: 0x0D;
    */

    int *ptr = mang; //Khi lấy địa chỉ của biến mang thì việc ghi mang và &mang đều tương đương nhau
    
    printf("dia chi cua phan tu 1:%p", ptr); //Lấy địa chỉ của phần tử đầu tiên
    
    printf("dia chi cua phan tu 2:%p", ptr+1);
    /*Thực hiện phép tính toán số học với con trỏ là cộng thêm 1 
    khi cộng con trỏ lên 1 thì giá trị của con trỏ là địa chỉ được cộng lên 
    là 4 bởi vì con trỏ mang kiểu dữ liệu là int*.*/
    
    printf("dia chi cua phan tu 3:%p", ptr+2);
    //Tương tự con trỏ được cộng thêm 2 thì giá trị con trỏ được cộng lên 8;

    printf("gia tri dia chi cua phan tu 1:%d", *ptr);
    //In ra giá trị của con trỏ tại giá trị địa chỉ mà con trỏ trỏ được
    
    printf("gia tri dia chi cua phan tu 2:%p", *(ptr+1));
    printf("gia tri dia chi cua phan tu 3:%p", *(ptr+2));
    return 0;
}
```
- Con trỏ kiểu void (Void Pointer): Con trỏ void trỏ đến bất kỳ địa chỉ nào mà không quan tâm tới kiểu dữ liệu của giá trị tại địa chỉ đó.

```javascripts
#include <stdio.h>

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

    void *ptr1[] = {&a,&b,&c};
    printf("ptr[1] = %d\n",*(int *)ptr1[0]);
    printf("ptr[2] = %lf\n",*(double *)ptr1[1]);
    printf("ptr[3] = %c\n",*(char *)ptr1[2]);

}
```
- Con trỏ hàm (Pointer to function) là một biến con trỏ lưu địa chỉ của một hàm.
```javascript
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
```
- Con trỏ hằng (Pointer to Constant) là một con trỏ nhưng không thể thay đổi giá trị mà con trỏ này trỏ đến thông qua deference mà chỉ có thể đọc được giá trị mà con trỏ này trỏ đến địa chỉ đó.
```javascript
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
```
- Hằng con trỏ (Constant Pointer) là một con trỏ chỉ trỏ duy nhất 1 địa chỉ của một đối tượng khi được khai báo. Không thể thay đổi địa chỉ sang đối tượng khác khác khi dùng hằng con trỏ trỏ đến.
```javascript
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
```
- Null pointer (Con trỏ null) là một con trỏ không trỏ đến bất kỳ đối tượng hay vùng nhớ nào hết.
- Dùng con trỏ null để tránh con trỏ có thể trỏ đến vùng nhớ khác.
- Sau khi thực hiện xong thao tác với con trỏ thì gán về con trỏ null. 
```bash
int *ptr = NULL;
printf("%p",ptr); //Địa chỉ mặc định của con trỏ null là 0x00
```
- Pointer to pointer (Con trỏ trỏ đến con trỏ) là con trỏ cấp 2 hoặc cấp cao hơn để trỏ đến địa chỉ của một con trỏ.
```javascript
int a = 5; 
//Địa chỉ của biến a: 0x12 có giá trị là 5:

int *ptr1 = &a; 
//Địa chỉ của biến con trỏ ptr1: 0xd2 nhưng có giá trị là 0x12 là địa chỉ của biến a

int **ptr2 = &ptr1;
// ptr2 là con trỏ cấp 2 
//Địa chỉ của biến con trỏ ptr2: 0xf4 nhưng có giá trị là 0xd2 là địa chỉ của con trỏ ptr1  
```