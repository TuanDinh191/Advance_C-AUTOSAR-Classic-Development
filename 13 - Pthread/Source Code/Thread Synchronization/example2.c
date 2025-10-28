#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>


//_Atomic int counter = 0; //từ khóa có sẵn trong chuẩn C11
atomic_int counter = 0; //typedef được định nghĩa trong <stdatomic.h>

void *increment(void *arg){
    for (int i = 0; i < 1000000; ++i)
        atomic_fetch_add(&counter,1);

    return NULL;
}

int main() {
   pthread_t t1, t2;
   pthread_create(&t1, NULL, increment, NULL);
   pthread_create(&t2, NULL, increment, NULL);
   pthread_join(t1, NULL);
   pthread_join(t2,NULL);

   printf("Expected = 2000000, Actual = %d\n", atomic_load(&counter));
}
