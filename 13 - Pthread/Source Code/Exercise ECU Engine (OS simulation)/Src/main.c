#include "Os.h"
#include "Os_alarm.h"
#include <unistd.h>
int main(){
    /* 
        - gọi StartOs() -> reset cấu hình task/alarm -> kích hoạt các driven-event task tương ứng
        - gọi SetRelAlarm() -> lên lịch chạy cho periodic-event task  
        - gọi shutdownOs() -> dừng mô phỏng (nếu cần)
            -> ví dụ gọi sleep() ở main sau 1 khoảng tgian nào đó -> hệ thống tự động dừng
    */
    if(StartOS() == E_OS_STATE)
    {
        ShutdownOS(E_OS_STATE);
    }
    
    if(SetRelAlarm(Alarm_500ms,0,100) == E_OS_STATE)
    {
        ShutdownOS(E_OS_STATE);
    }

    if(SetRelAlarm(Alarm_1000ms,0,100) == E_OS_STATE)
    {
        ShutdownOS(E_OS_STATE);
    }
    sleep(7);
    ShutdownOS(E_OK);
}