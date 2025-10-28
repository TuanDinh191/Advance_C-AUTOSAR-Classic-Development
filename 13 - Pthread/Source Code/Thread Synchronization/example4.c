#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


#define NUM_THREADS 5
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER; // Khởi tạo mutex

void *print_log(void *arg)
{
    int id = *(int *)arg;
    int stepCnt = 0;
    while (1)
    {
        pthread_mutex_lock(&log_mutex);                                  // khóa mutex để ngăn chặn các luồng khác sử dụng terminal
        printf("[Thread %d] processing step %d done.", id, stepCnt++);   // in log ra terminal an toàn
        printf("\n");
        pthread_mutex_unlock(&log_mutex);                                // mở khóa mutex
        usleep(1000);
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS]; // mảng lưu trữ số lượng luồng
    int ids[NUM_THREADS];           // mảng chứa id của từng luồng
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, print_log, &ids[i]);
    }

    while (1)
    {
        static int count = 0;
        pthread_mutex_lock(&log_mutex);   // khóa mutex để ngăn chặn các luồng khác sử dụng terminal
        printf("[Main thread] : processing counter %d", count++);
        printf("\n");
        pthread_mutex_unlock(&log_mutex); // mở khóa mutex
        usleep(1000);
    }
    return 0;
}
