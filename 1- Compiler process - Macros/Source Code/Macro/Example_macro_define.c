    #include <stdio.h>

    //Định nghĩa tên thay thế cho 1 giá trị
    #define SIZE 5

    //#Định nghĩa tên thay thế cho 1 hàm 
    #define CREATE_FUNC(name, cmd) \
    void name()                    \
    {                              \
        printf(cmd);               \
    }                                               

    //Tạo hàm 
    CREATE_FUNC(func1,"This is function 1\n");
    CREATE_FUNC(func2,"This is function 2\n");
    CREATE_FUNC(func3,"This is function 3\n");

    int main()
    {
    int arr[SIZE] = {12,65,54,64,22};
    
    for (int i = 0; i<SIZE; ++i)
        printf("arr[%d]: %d\n",i,arr[i]);
    
    //Gọi hàm
    func1();
    func2();
    func3();
    return 0;
    }