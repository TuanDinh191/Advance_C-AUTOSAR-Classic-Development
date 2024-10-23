#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int exception;

#define TRY if((exception = setjmp(buf))==0)
#define CATCH(x) else if(exception == x)
#define THROW(x)  longjmp(buf,x);
double divide(int a, int b)
{
    if (a==0 && b==0)
        THROW(1) 
        /*Khi hàm vào divide là tham số (0,0) sẽ nhảy về dòng có chứa setjump và gán
        exception = 1*/
    else if(a != 0 && b == 0)
        THROW(2)
         /*Khi hàm vào divide là tham số (a,0) sẽ nhảy về dòng có chứa setjump và gán
        exception = 2*/

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
        printf("khong ton tai");
    CATCH(2)
        printf("Chia cho 0\n");

    return 0;
}