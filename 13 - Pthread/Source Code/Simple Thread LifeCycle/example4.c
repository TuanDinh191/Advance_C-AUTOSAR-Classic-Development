#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void *task2(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task2] count %d\n", i);
        sleep(2);
    } 
    return NULL;
}

int main(){
    pthread_t t2;
    pthread_create(&t2,NULL,task2, NULL);

    pthread_detach(t2);
    for (int i=0; i<5; i++){
        printf("[main thread] count %d\n",i);
        sleep(2);
    }


    printf("chương trình đã kết thúc");
    return 0;
}

