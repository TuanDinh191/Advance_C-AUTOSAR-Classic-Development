#include "Os.h"
#include "Os_event.h"
#include <stdio.h>
#include <stdlib.h>

void task_sensor() {

    printf("[task_sensor] : reading sensor...\n");
    /*đặt Event cho task_enginecontrol*/
    SetEvent(TASK_ID_EngineControl,EV_DataReady);

}

void task_CAN()
{
    printf("[task_CAN] :Reading CAN Frame data...\n");
    srand(time(0));         //khởi tạo seed sinh số ngẫu nhiên
    int data = rand()%30; 
    if (data < 10)
    {
        printf("[task_CAN] Error detected! Signaling Diagnostic\n");
        SetEvent(TASK_ID_Diagnostic,EV_TriggerError);
    }
    else 
    {
        printf("[task_CAN] No action needed\n");
    }
}

void task_enginecontrol() {
    EventMaskType ev = 0u;  //biến cục bộ đọc về event mong muốn 
    uint8_t errorflag = 0;  //cờ cục bộ mô phỏng tín hiệu lỗi
    srand(time(0));         //khởi tạo seed sinh số ngẫu nhiên

    for(;;){
        /*đợi event từ task mong muốn*/
       WaitEvent(TASK_ID_EngineControl,EV_DataReady);
        /*Đọc ra event đã đợi vào biến ev*/
        GetEvent(TASK_ID_EngineControl,&ev);
        if (ev & EV_DataReady) {

            /*Giả lập phát hiện lỗi ngẫu nhiên -> sử dụng hàm rand()*/
            //...
            errorflag = rand()%3;
            if(errorflag == 2){
                printf("[task Control] Error detected! Signaling Diagnostic\n");
                
                /*đặt event cho task mong muốn */
                SetEvent(TASK_ID_Diagnostic,EV_TriggerError);
            }
            else{
                printf("[task Control] Control command ready. Signaling Actuator\n");
                /*đặt event cho task mong muốn */
                SetEvent(TASK_ID_Actuator,EV_ControlCmdReady);
            }
            /* reset event cho task hiện tại */
            ClearEvent(TASK_ID_EngineControl, ev);
        }
        //printf("[Task_enginecontrol] is running\n");
    }
}

void task_actuator() {
    EventMaskType ev = 0u;
    
    for(;;){
        /*đợi event từ task mong muốn*/
        //...
        WaitEvent(TASK_ID_Actuator,EV_ControlCmdReady);
        /*Đọc ra event đã đợi vào biến ev*/
        //...
        GetEvent(TASK_ID_Actuator,&ev);
        if (ev & EV_ControlCmdReady){
           
            printf("[task Actuator] Executing control signal...\n");
            /*đặt event cho task mong muốn */
            //...
            
            /* reset event cho task hiện tại */
            ClearEvent(TASK_ID_Actuator,ev);
        }
    }
}

void task_diagnostic() {
    EventMaskType ev = 0u;
   
    for(;;){
        /*đợi event từ task mong muốn*/
        //...
        WaitEvent(TASK_ID_Diagnostic,EV_TriggerError);
        /*Đọc ra event đã đợi vào biến ev*/
        //...
        GetEvent(TASK_ID_Diagnostic,&ev);
        if (ev & EV_TriggerError){
            
            printf("[Diagnostic] Handling error...\n");
            /*đặt event cho task mong muốn */
            //...
            
            /* reset event cho task hiện tại */
            ClearEvent(TASK_ID_Diagnostic,ev);
        }
        //printf("[Task_diagnostic] is running\n");
    }
}
