#include <stdio.h>
#include <stdarg.h>

typedef struct 
{
    int hour;
    int minute;
    int second;
}time;

void display_time(int count,...)
{
    va_list args;
    va_start(args,count);
    time data;
    for (int i =0;i<count;++i)
    {
        data = va_arg(args,time);
        printf("The time is: %dh-%dm-%ds\n",data.hour,data.minute,data.second);
    }
}

int main()
{
    display_time(3,(time){12,30,51},(time){7,23,12},(time){18,33,59});
    return 0;
}