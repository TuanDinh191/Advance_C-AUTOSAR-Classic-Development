#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int exception;

double divide(int a, int b)
{
    if (a==0 && b==0)
        longjmp(buf,1); 
        /*Khi hàm vào divide là tham số (0,0) sẽ nhảy về dòng có chứa setjump và gán
        exception = 1*/
    else if(a != 0 && b == 0)
        longjmp(buf,2);
         /*Khi hàm vào divide là tham số (a,0) sẽ nhảy về dòng có chứa setjump và gán
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