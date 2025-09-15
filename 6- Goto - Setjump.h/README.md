
# Bai 5 Goto - setjump.h
#### 1. Goto
#### - Định nghĩa:
- Khi khai báo từ khóa goto trong một hàm thì sẽ kiểm soát luồn thực thi của chương trình bằng cách nhảy đến một label đã được khai báo trước đó trong chương trình, khi dùng goto thì chỉ giới hạn trong nội bộ 1 hàm khai báo không thể nhảy đến hàm khác nếu hàm khác khai báo label.
#### - Cách dùng:
- Trường hợp 1: Goto dùng trong switchcase. Hàm switchcase dưới đây nếu không dùng goto thì sẽ dùng rất nhiều biến và sẽ tạo ra cơ chế rất phức tập để dòng chương trình có thể nhảy đến tag1, việc dùng goto sẽ tiện dụng hơn rất nhiều.
```javascripst 
#include <stdio.h>

int main()
{
    int option;
    tag1:
    do
    {
        printf("Menu1\n");
        printf("1: Tao ra menu thu hai \n");
        printf("2....\n");
        printf("3....\n");
        scanf_s("%d",&option);
    }while(option!=1);
    
    switch(option)
    {
        case 1:
        printf("Menu2\n");
        printf("0: Quay lai menu 1\n");
        printf("1: Ket thuc chuong trinh \n");
        printf("2....\n");
        scanf_s("%d",&option);
        switch (option)
        {
        case 0:
            goto tag1; //Dòng chương trình sẽ nhảy đến label tag1 để quay lại cái menu1
            break;
        case 1:
            goto thoat; //Dòng chương trình sẽ nhảy đến label thoat để thoát chương trình
            break;
        default:
            break;
        }
        break;
        case 2:
            break;
        case 3:
            break;

    }
    thoat:
    return 0;
}
```
- Trường hơp 2: Goto dùng trong hàm lặp. Trong chương trình dưới đây sử dùng tới 3 dòng lặp (1 dòng lặp while 1 và 2 dòng lặp for) thì để thoát được dòng lặp thì sẽ dùng một điều kiện tương ứng với break trong mỗi dòng lặp việc này sẽ làm chương trình dài hơn và phức tạp hơn, việc dùng goto sẽ tối giản code chương trình làm tổng quát chương trình sẽ dễ đọc hơn.
```javascripst 
#include <stdio.h>

int main()
{
    int i,j;
    while(1)
    {
        for (int i=0;i<5;i++)
        {
            for(j=0; j<5; j++){
                if (i == 2 && j ==3){
                    printf("thoat chuong trinh \n");
                    goto thoat; //Dòng chương trình sẽ nhảy đến label thoat để thoát chương trình
                }
            }
        }
    }
    thoat:
    return 0;
}
```
#### - Ứng dụng:
- Trong ứng dụng khi chạy tới đoạn chương trình này cần quay lại chức năng cũ.
- Trong chương trình có nhiều vòng lặp while,for.
- Trong lập trình nhúng sẽ ứng dụng trong hiển thị led ma trận dùng thuật toán quét LED. 
#### 2. Setjump.h
#### - Định nghĩa: 
- Giống với goto thì khi dùng thư viện setjump cũng có thể kiểm soát luồn thực thi chương trình ngoài việc có thể nhảy ở nội bộ hàm thì setjump có thể nhảy từ địa chỉ hàm này qua hàm khác qua hai hàm chính là setjmp và longjmp chính mà điều goto không làm được, có thể xem setjump là một bản nâng cấp đối với goto.
#### - Cách dùng:
- `Setjump` khi được dùng để lưu địa chỉ vị trí khi gọi hàm `Setjump` gán cho một biến có kiểu dữ liệu là `jump_buf`. Nếu được dùng lần đầu sẽ trả về 0, trả về một giá trị khác 0 khi quay lại từ `longjmp` là tham số thứ 2 được truyền vào `longjump`.
- `Longjmp`: Nhảy về vị trí hiện tại của `setjump` và tiếp tục thực thi từ đó. 
- Dùng setjump nội bộ trong hàm. Chương trình dưới đây nó sẽ thực thi là một vòng lặp vô tận bởi vì khi dòng chương trình thực thi đến dòng longjmp thì nó sẽ nhảy đến dòng có chứa hàm setjmp tiếp tục theo dòng chương trình thì lại đến dòng longjmp cứ như vậy mà nó sẽ lặp lại liên tục đến vô tận. 
```javascipt
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
/*Khởi tạo biến buf với kiểu dữ liệu là jmp_buf để lưu
 trạng thái hiện tại của môi trường đang thực thi
 không thể khai báo với biến buf  
*/
int main()
{
    int exception = setjmp(buf);
    /*Sau khi khởi tạo biến buf thì sẽ được dùng truyền vào hàm buf
    Hàm setjmp có nhiệm vụ là dùng lưu trạng thái hiện tại tức là đang đứng 
    ở đâu trong chương trình*/
    
    /*Sau khi khai báo setjump lần đầu tiên thì nó sẽ trả về là giá trị 0
    thì khi đó biến exception có giá trị là bằng 0*/

    if(exception == 0)
        printf("exception = %d\n",exception);
    else if(exception ==3)
        printf("exception = %d\n",exception);

    longjmp(buf,3);
    /*Khi chương trình thực thi đến dòng longjmp thì nó sẽ nhảy ngược trở lại
    đến hàm setjmp vị trí nó đang đứng và đồng thời gán giá trị cho biến exception
    là bằng 3 */

    return 0;
}
```
- Dùng setjunmp ngoài hàm 
```javascipt
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int exception;

double divide(int a, int b)
{
    if (a==0 && b==0)
        longjmp(buf,1); 
        /*Khi hàm vào divide là tham số (0,0) sẽ nhảy về dòng có chứa setjmp và gán
        exception = 1*/
    else if(a != 0 && b == 0)
        longjmp(buf,2);
         /*Khi hàm vào divide là tham số (a,0) sẽ nhảy về dòng có chứa setjmp và gán
        exception = 2*/

    return (double)a/b;
}

int main()
{
    if((exception = setjmp(buf))==0)
    {
        double result = divide(0,0);
        printf("ket qua = %f\n",result);
    }
    else if(exception == 1) 
        printf("khong ton tai");
    else if(exception == 2)
        printf("Chia cho 0\n");

    return 0;
}
```
#### - Ứng dụng:
- Dùng để xử lí lỗi nhưng mà không dừng chương trình lại đi, để debug chương trình, xử lý ngoại lệ mà không làm gián đoạn toàn bộ chương trình.
- Ứng dụng các từ khóa để xử lý ngoại lệ hỗ trợ hầu hết các ngôn ngữ lập trình hiện đại C++, Java, Python, C#, đối với C định nghĩa lại các từ khóa để dùng:
+ TRY: Kiểm tra 1 đoạn code có khả năng gây lỗi.
`define TRY: if((exception = setjump(buf) == 0))`
+ CATCH: Xác định loại lỗi.
`define CATCH(x) else if(exception == x)`
+ THROW: Ném ra ngoại lệ, in ra thông báo tương ứng với lỗi.
`define THROW(x) longjumpt(buf,x);`

