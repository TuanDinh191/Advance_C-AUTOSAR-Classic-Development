#include <stdio.h>
#include <stdarg.h>

#define ave_rain(...) Average_monthly_rainfall(__VA_ARGS__, 0)

float Average_monthly_rainfall(int rain_amount, ...)
{
 va_list args;

 va_start(args,rain_amount);

 int total = rain_amount, value = 0, month_count=1;
 float ave_rain_monthly = 0;

 while ((value = va_arg(args,int))!= 0)
 {
    total += value;
    month_count++;
 }
 
ave_rain_monthly = (float)total/month_count;

va_end(args);

return ave_rain_monthly; 
}

int main ()
{
 printf("The average monthly rainfall: %.2f mm",ave_rain(25, 23, 54, 47)); 
 return 0;
}