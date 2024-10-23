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