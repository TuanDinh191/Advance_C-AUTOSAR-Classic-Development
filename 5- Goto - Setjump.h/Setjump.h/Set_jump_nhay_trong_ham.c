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
    /*Khi chương trình thực thi đến dòng longjump thì nó sẽ nhảy ngược trở lại
    đến hàm setjump vị trí nó đang đứng và đồng thời gán giá trị cho biến exception
    là bằng 3 */

    return 0;
}