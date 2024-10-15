#include <stdio.h>
#include <stdarg.h>

float Average_monthly_rainfall(int month_count, ...)
{
 va_list args;
 va_start(args,month_count);
 int total = 0;
 float ave_rain_monthly = 0; 
 for(int i=0; i<month_count;++i)
    total += va_arg(args,int);
 
ave_rain_monthly = (float)total/month_count;

va_end(args);

return ave_rain_monthly; 
}

int main ()
{
 printf("The average monthly rainfall: %.2f mm",Average_monthly_rainfall(3,23,54,47)); 
 return 0;
}