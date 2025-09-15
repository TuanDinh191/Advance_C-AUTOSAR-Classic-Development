#include <stdio.h>
#include <string.h>
#include <setjmp.h>

jmp_buf buf;

int exception;

char error_code[50];

#define TRY if((exception = setjmp(buf))==0)
#define CATCH(x) else if(exception == x)
#define THROW(x,code)   \
strcpy(error_code,code);  \
longjmp(buf,x);                            


double divide(int a, int b)
{
    if (a==0 && b==0)
    {
        THROW(1,"Khong ton tai\n");
    }
    else if(a=!0&& b==0)
    {
        THROW(2,"Lỗi: phép chia cho 0!\n");
    }
    return (double)a/b;
}

int main()
{
    TRY
    {
        double result = divide(2,0);
        printf("ket qua = %f\n",result);
    }
    CATCH(1)
        printf("%s\n",error_code);
    CATCH(2)
        printf("%s\n",error_code);

    return 0;
}