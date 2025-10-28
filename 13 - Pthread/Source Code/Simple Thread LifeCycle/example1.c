#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *task1(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task1] count %d\n", i);
        sleep(5);
    }
    return NULL;
}
void *task2(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task2] count %d\n", i);
        sleep(5);
    }
    return NULL;
}

int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,task1,NULL);
    pthread_create(&t1,NULL,task2, NULL);
    while(1);
}