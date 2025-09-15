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