#include <stdio.h>
#include <string.h>
#include <setjmp.h>

jmp_buf buf;

int exception;
char error_message[100];
int check = 0;     
  
enum ErrorCodes {NO_ERROR, FILE_ERROR, NETWORK_ERROR,CALCULATION_ERROR};
#define TRY if((exception = setjmp(buf))==0 && check == 0)
#define CATCH(x)  else if((exception == x)) 
#define THROW(x,code)   \
strcpy(error_message,code); \
if(x == NO_ERROR)        \
    check++;    \
else if(x == FILE_ERROR || x == NETWORK_ERROR || x == CALCULATION_ERROR)\
    longjmp(buf,x);\
if (check == 3)   \
    longjmp(buf,x);

void readFile()
{
    printf("Đọc file ...\n");
    //THROW(FILE_ERROR,"Lỗi đọc file: file không tồn tại");
    THROW(NO_ERROR,"Hệ thống thực thi an toàn không có lỗi nào phát hiện");
}

void networkOperation()
{
    printf("Đang xử lý mạng ...\n");
    THROW(NETWORK_ERROR,"Lỗi xử lý mạng: Mất kết nối với thiết bị");
    //THROW(NO_ERROR,"Hệ thống thực thi an toàn không có lỗi nào phát hiện");
}

void calculateData()
{
    printf("Đang tính toán dữ liệu ...\n");
    //THROW(CALCULATION_ERROR,"Lỗi khi tính toán dữ liệu: Không thể vào vùng nhớ để tính toán");
    THROW(NO_ERROR,"Hệ thống thực thi an toàn không có lỗi nào phát hiện");
}
int main()
{
    TRY
    {
        readFile();
        networkOperation();
        calculateData();
    }
    CATCH(FILE_ERROR)
        printf("%s\n",error_message);
    CATCH(NETWORK_ERROR)
        printf("%s\n",error_message);
    CATCH(CALCULATION_ERROR)
        printf("%s\n",error_message);
    CATCH(NO_ERROR)
        printf("%s\n",error_message);

    return 0;
}