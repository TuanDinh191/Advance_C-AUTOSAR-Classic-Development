# Bài 13: Pthread (Luồng)
#### 1. Đặt vấn đề 
- Trước đây khi lập trình chương trình khi được thực thi sẽ được CPU thực thi theo tuần tự có nghĩa là nếu có hàm nào khai báo trước sẽ được thực thi trước, những chương trình này khi đó có yêu cầu chỉ cần xử lí tuần tự là đủ nhưng giờ yêu cầu của chương trình muốn thực thi cả 2 hàm cùng một lúc theo thời gian thực cần lấy dữ liệu đúng thời điểm để xử lí thì lúc này lập trình tuần tự không còn đáp ứng được nữa ta sẽ dùng lập trình song song.
#### 2. Lập trình song song 
#### - Định nghĩa: 
- Lập trình song song bản chất vẫn là lập trình tuần tự nhưng CPU thay vì dành thời gian xử lí cho xong 1 hàm 1 tác vụ thì sẽ chia thời gian xử lí 1 phần lệnh của 1 hàm 1 tác vụ A sau đó qua hàm, tác vụ B khác xử lí 1 phần lệnh rồi CPU sẽ quay lại để tiếp tục xử lí 1 phần lệnh của 1 hàm 1 tác vụ A nghĩa là các tác vụ các câu lệnh của nhiều hàm sẽ được gọi xử lí xen kẽ với nhau, lúc này chương trình cần tạo ra nhiều luồng cho nhiều tác vụ để có thể chạy song song.
#### 3. Thread (Luồng)
#### - Định nghĩa:
- Tiến trình (process) là các chương trình được cài đặt và chạy trên máy tính và mỗi tiến trình sẽ chứa nhiều thread (luồng) chạy song song , luồng là đơn vị thực thi nhỏ nhất của 1 tiến trình.
- Các luồng (thread) cùng tiến trình chia sẽ tài nguyên với nhau nhưng sẽ có stack và bộ đếm chương trình riêng biệt.
- Để lập trình song song trong C/C++ thì sẽ dùng thư viện Pthread (POSIX Threads) là thư viện tiêu chuẩn cho lập trình đa luồng. Thư viện này sẽ đặc biệt hữu ích trên các hệ thống có nhiều bộ xử lý hoặc bộ xử lý nhiều nhân, vì mỗi luồng có thể được phân bố cho các nhân khác nhau để chạy. 
- Thư viện này sẽ cung cấp các hàm như sau: 
#### - Hàm khởi tạo 1 luồng 
```
 int pthread_create(pthread_t *th, const pthread_attr_t *attr, void *(* func)(void *), void *arg);
```
__+__ Tham số 1 : con trỏ đến ID của thread mới được tạo ra

__+__ Tham số 2 : thuộc tính của thread (mặc định NULL)

__+__ Tham số 3 : Hàm được gọi và chạy trong thread 

__+__ Tham số 4 : danh sách các tham số truyền vào hàm 

__+__ Trả về 0 nếu thành công. 

Ví dụ triển khai trong chương trình :

- Dưới đây là chương trình thực thi cả 2 hàm task 1 và task 2 cùng một lúc bằng cách tạo ra 2 luồng cho 2 hàm này điểm chú ý là chương trình sẽ có 3 luồng là luồng chính của hàm main và 2 luồng con của 2 hàm task 1 và task 2, thì khi thực thì nếu mà luồng chính kết thúc thì sẽ kéo theo cả 2 luồng con kết thúc theo vì thế để tránh việc này xảy ra thì  ở trong chương trình chính ta phải để vòng lặp while(1) để cho luồng chính không bao giờ kết thúc để thực thi được 2 hàm task 1, task 2.
```
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

```
#### - Hàm đợi 1 luồng 
- Như đã nói ở trên thì để luồng con được thực thì phải duy trì được luồng chính, thay vì để dùng lặp while(1) trong hàm main thì ta sẽ dùng 1 hàm sẽ báo cho luồng chính đợi các luồng con thực thi xong rồi mới kết thúc.
```
 int   pthread_join(pthread_t t, void **res);
```
__+__ Tham số 1: ID của thread mà bạn muốn chờ đợi.

__+__ Tham số thứ 2: trả về kết quả nếu gọi pthread_exit bên trong hàm cho phép chạy trên luồng gọi join cho con trỏ cấp 2 để lưu trữ.

- Cách 1: Dùng `pthread_join` để 2 luồng con thực thi trước rồi mới tới thực thi luồng chính:
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *task1(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task1] count %d\n", i);
        sleep(1);
    }
    return NULL;
}
void *task2(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task2] count %d\n", i);
        sleep(2);
    } 
    return NULL;
}

int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,task1,NULL);
    pthread_create(&t2,NULL,task2, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    for (int i=0; i<5; i++){
        printf("[main thread] count %d\n",i);
        sleep(2);
    }
    printf("chương trình đã kết thúc");
    return 0;
}
```
- Cách 2: Có thể dùng hàm `pthread_join` để luồng chính và luồng phụ đều chạy song song, chương trình dưới đây mặc dù chương trình của luồng chính thực thi xong trước rồi nhưng vẫn đợi luồng con thực hiện xong rồi mới kết thúc chương trình.
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *task1(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task1] count %d\n", i);
        sleep(1);
    }
    return NULL;
}
void *task2(void *arg)
{
    for (int i = 0; i < 10; i++){
        printf("[task2] count %d\n", i);
        sleep(2);
    } 
    return NULL;
}

int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,task1,NULL);
    pthread_create(&t2,NULL,task2, NULL);

    for (int i=0; i<5; i++){
        printf("[main thread] count %d\n",i);
        sleep(2);
    }

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    printf("chương trình đã kết thúc");
    return 0;
}
```
#### - Hàm tách thread với luồng chính 
- Luồng được thực thi hàm `pthread_detach` sẽ tách với luồng chính và chạy độc lập.

```
 int pthread_detach(pthread_t thread);
```
- Khi dùng hàm `pthread_detach` sẽ tự giải phóng tài nguyên khi chạy xong, luồng đã gọi detach thì không được gọi join sau đó nữa sau khi kết thúc, không lấy được kết quả.
- Dù chạy độc lập so với luồng chính khi dùng `pthread_detach` luồng chính sẽ không đợi với luồng chạy dùng `pthread_detach` nghĩa là luồng chính thực thi rồi sẽ kết thúc chương trình sẽ kết thúc luôn luồng chạy `pthread_detach` mặc dù chương trình thực thi chưa xong. 
- Ví dụ triển khai trong chương trình:
```
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
```
#### - Hàm nhận kết quả trả về 
- Hàm `pthread_exit` nhận kết quả trả về từ luồng gọi hàm bằng `join`.
```
void pthread_exit(void *retval);
```
- Tham số con trỏ retval trả về kết quả cho thread gọi join (nếu cần)
- Nếu thread chỉ làm việc xong rồi thoát, không cần trả kết quả có thể dùng return NULL hoặc pthread_exit(NULL)
- Nếu muốn main thread kết thúc mà không dừng toàn bộ chương trình, cần gọi pthread_exit() thay vì return NULL → tránh việc thread con bị kill (nếu còn chạy).
- Ví dụ triển khai trong chương trình:
```
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void* SensorTask(void* arg) {
    float* sensor_value = (float*)malloc(sizeof(float));
    // Giả lập đọc cảm biến ngẫu nhiên
    *sensor_value = 20.0f + (rand() % 1000) / 100.0f; // 20.00–30.00
    pthread_exit(sensor_value); // Trả về giá trị đo được
}


int main() {
    pthread_t tid;
    srand(time(NULL));


    for (int i = 0; i < 100; i++) {  // mô phỏng 100 chu kỳ (≈1s)
        void* ret_val;
        pthread_create(&tid, NULL, SensorTask, NULL);
 

        //note : dùng detach ko lấy kết quả trẻ về được
        pthread_join(tid, &ret_val); // đợi thread con kết thúc


        float value = *(float*)ret_val;
        free(ret_val);
        // In liên tục trên cùng 1 dòng (không xuống dòng)
        printf("\r[ECU] Sensor value: %.2f °C", value);
        fflush(stdout); // buộc in ra ngay


        usleep(10 * 1000); // 10 ms
    }

    printf("\nDone.\n");
    return 0;
}
```
#### 4. Đồng bộ hóa cho nhiều luồng bằng atomic
- Khi có nhiều luồng cùng truy cập 1 biến (tài nguyên chung) ví dụ để thực hiện thao tác tăng hoặc giảm giá trị thì lúc này khi giá trị đã tăng hoặc giảm của luồng thứ 1 chưa kịp lưu giá trị thì đã bị luồng thứ 2 can thiệp vào biến đó để thực hiện tăng hoặc giảm giá trị thì giá trị của biến đã tăng của luồng thứ 1 đã mất đi do bị can thiệp bởi luồng thứ 2 thì hiện tượng này gọi là race condition. Để tránh hiện tượng này ta sẽ dùng `atomic` một cơ chế đảm bảo CPU thực hiện thao tác với tài nguyên chung một cách trọn vẹn không bị chen ngang bởi thread khác nghĩa là cơ chế này đảm bảo tại 1 thòi điểm chỉ có 1 luồng truy cập 1 vùng tài nguyên chung sẽ không bị tác động hay ngắt giữa chừng bởi các luồng khác.
- Chương trình khi dùng `atomic` sẽ phù hợp khi triển khai các thao tác (++,--,bật/tắt flag) trên 1 vùng dữ liệu toàn cục chia sẽ giữa nhiều luồng. 
#### - Khởi tạo cho 1 biến dùng atomic
- Cách 1: Dùng từ khóa có sẵn trong chuẩn C11 nằm trong thư viện `stdio.h`
```
_Atomic int counter = 0 ;
```
- Cách 2: Dùng tên bí danh typedef được định nghĩa trong thư viện `stdatomic.h`
```
atomic_int count = 0;
```
- Đối với một số trường hợp như là các thành phần nằm trong một struct sử dụng `atomic`, khi sử dụng cấp phát động hoặc khi không thể khởi tạo bằng phép gán `=` thì ta sẽ sử dụng hàm `atomic_init` để khởi tạo.
```
void atomic_init(volatile A *obj, C value);
```
__+__ Tham số 1: Con trỏ đến biến atomic có kiểu tương ứng, từ khóa volatile đảm bảo trình biên dịch không tối ưu hóa biến này.

__+__ Tham số 2: Giá trị được gán cho biến atomic.
#### - Tăng giá trị cho một biến dùng atomic
- Để tăng giá trị cho một biến dùng `atomic` ta sẽ dùng hàm như sau:
```
    atomic_fetch_add(atomic_init *obj, int operand);
```
__+__ Tham số 1: Con trỏ đến địa chỉ của biến atomic cần tăng giá trị.

__+__ Tham số 2: giá trị cần tăng thêm.

__+__ Trả về giá trị cũ trước khi tăng

#### - Đọc giá trị cho một biến dùng atomic
- Để đọc một biến dùng `atomic` ta sẽ dùng hàm như sau:      
```
    atomic_load(const atomic_init *obj);
```
Ví dụ triển khai trong chương trình:
```
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>


typedef struct {
    _Atomic int id;
    _Atomic int counter;
} Device;


int main() {
    Device *d = malloc(sizeof(Device));


    atomic_init(&d->id, 101);
    atomic_init(&d->counter, 0);


    atomic_fetch_add(&d->counter, 5);


    printf("Device %d - counter = %d\n",
           atomic_load(&d->id),
           atomic_load(&d->counter));


    free(d);
    return 0;
}
```
#### - Thay đổi giá trị cho biến dùng atomic
- Để thay đổi giá trị cho một biến dùng `atomic` ta sẽ dùng hàm như sau:
```
atomic_store(atomic_int *obj, int desired);
```
__+__ Tham số 1: Con trỏ đến địa chỉ của biến atomic cần ghi dữ liệu.

__+__ Tham số 2: Dữ liệu cần ghi vào biến atomic.

__+__ Không trả về giá trị.

#### 5. Đồng bộ hóa nhiều luồng bằng Mutex
- Khi ta dùng atomic chỉ bảo vệ cho 1 biến tức là 1 lệnh 1 thao tác cho cùng 1 vùng tài nguyên của 1 luồng khi được thực thi sẽ được thực hiện trọn vẹn mà không bị ngắt quãng khi ta muốn bảo vệ cho nhiều thao tác phức tạp cho một vùng tài nguyên, cập nhật nhiều biến hoặc tài nguyên cùng 1 lúc thì dùng atomic sẽ không đáp ứng đủ vì thế ta sẽ dùng `mutex`. Nói cách khác khi dùng `mutex` ta sẽ dùng để bảo vệ vùng code (critical section) nơi mà chỉ có 1 thread được vào.

#### - Khởi tạo và hủy mutex 
- Để dùng mutex sẽ có 2 cách khởi tạo:
- Cách 1: Khởi tạo 1 mutex cục bộ thì ta sẽ dùng hàm:
```
    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```
__+__ Tham số 1: Con trỏ đến biến mutex cần khởi tạo.

__+__ Tham số 2: Cấu hình thuộc tính mutex (mặc định là NULL)

__+__ Trả về 0 nếu khởi tạo thành công

- Khi khởi tạo một biến mutex cục bộ thì sau khi dùng xong sẽ dùng hàm sau để hủy, giải phóng tài nguyên hệ thống cấp phát cho mutex, trước khi hủy,giải phóng cần phải được unclock nếu không sẽ gây lỗi:
```
    int pthread_mutex_destroy(pthread_mutex_t *mutex);
``` 
- Cách 2: Khởi tạo tĩnh 1 mutex toàn cục, khi dùng cách này thì hệ thống tự động giải phóng tài nguyên, không cần gọi hàm `pthread_mutex_destroy`
```
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
```
#### - Quản lý Mutex
- Khi một luồng bắt đầu truy cập vào tài nguyên chung để thao tác thì sẽ dùng hàm `pthread_mutex_lock` để khóa mutex để không cho các luồng khác truy cập sau khi xử lí các thao tác xong rồi mới mở khóa dùng hàm `pthread_mutex_unlock` để cho các luồng khác được phép truy cập. 
- Ví dụ triển khai trong chương trình: Hàm print_log và chương trình chính đều dùng lệnh `printf` đều chia sẽ chung màn hình để in ra giá trị khi in ra màn hình console nếu hàm và chương trình  đều không dùng khóa mutex thì sẽ đều tranh dành tài nguyên để in ra màn hình thì lúc này sẽ in ra chồng chập lẫn nhau. 
```
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
```
#### 6. So sánh Atomic & Mutex





#### 7. Biến điều kiện (Condition variable) 
- Ở ví dụ dưới đây sẽ sử dụng `atomic` thì hàm receiver sẽ luôn đợi dữ liệu từ hàm `sender` ở trong dòng lặp while thì điều này vô tình sẽ gây ra cho CPU liên tục xử lý 1 cách vô ích gây giảm hiệu suất và chậm trễ khi cần xử lý những tác vụ khác đồng thời, lúc này dùng biến điều kiện để tối ưu hơn cho việc đồng bộ hóa giữa nhiều luồng với nhau.
```
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


atomic_int data_ready = 0;
int shared_data = 0;
/*
    - MÔ phỏng cơ chế quản lý cờ trạng thái
    - sử dụng store/load để ghi/đọc trạng thái của cờ -> quyết định khi nào kiểm tra dữ liệu
*/
void* Sender(void* arg) {
    for(int i = 0 ; i < 10 ; i++){
        shared_data = rand() % 50;  //mô phỏng data ngẫu nhiên
        //đánh dấu trạng thái có data
        atomic_store(&data_ready, 1);  // Ghi flag atomically
        printf("Producer: data sẵn sàng!\n");
        sleep(1);
    }
    return NULL;
}


void* Receiver(void* arg) {
    while(1){
        printf("Consumer: đợi dữ liệu...\n");
        while (atomic_load(&data_ready) == 0) { // Đọc flag atomically
            printf("checking dataReady\n");
            usleep(10*1000);
        }
        printf("Consumer: nhận được data = %d\n", shared_data);


        //reset flag để đợi tín hiệu mới
        atomic_store(&data_ready, 0);  // Ghi flag atomically
    }
    return NULL;
}


int main() {
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, Sender, NULL);
    pthread_create(&t2, NULL, Receiver, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
```
- Condition variable (cv) là biến được dùng để đồng bộ hóa giữa các luồng, nó đảm bảo một hoặc nhiều luồng sẽ chờ\ngủ cho đến khi được đánh thức để chạy khi 1 điều kiện/sự kiện được báo hiệu.
- Cơ chế này luôn được sử dụng kèm với mutex để đãm bảo:
__+__ Khi 1 luồng kiểm tra/cập nhật điều kiện, sẽ không bị luồng khác can thiệp

__+__ Tránh lỗi race condition.

#### - Khởi tạo và hủy 1 biến điều kiện
- Để dùng biến điều kiện sẽ có 2 cách khởi tạo:
- Cách 1: Khởi tạo động cho biến điều kiện cục bộ thì ta sẽ dùng hàm:
```
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL); // dùng thiết lập mặc định
```
- Khi khởi tạo một biến điều kiện cục bộ thì sau khi dùng xong sẽ dùng hàm sau để hủy, giải phóng tài nguyên của biến điều kiện khởi tạo động.

```
    pthread_cond_destroy(&cond)
```
-Cách 2: Khởi tạo tĩnh cho biến điều kiện toàn cục, khi dùng cách này thì hệ thống tự động giải phóng tài nguyên, không cần gọi hàm `pthread_cond_destroy`.
```
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```
#### - Thao tác với biến điều kiện 
- Đối với hàm chờ tìn hiệu sẽ dùng cơ chế Wait đặt luồng hiện tại vào trạng thái chờ/ngủ cho đến khi có tín hiệu signal hoặc broadcast thì trong hàm này sẽ dùng hàm sau đây để đợi/ngủ: 
```
    pthread_cond_wait(&cond, &mtx)
```

__+__ Tham số 1: Địa chỉ của biến điều kiện.

__+__ Tham số 2: Địa chỉ của biến mutex được dùng để khóa trong hàm đợi tín hiệu.
- Đối với hàm thông báo sẽ có 2 cơ chế là Signal hoặc là Broadcast sẽ thông báo ví dụ khi có dữ liệu mới đánh thức hàm chờ tín hiệu để đọc dữ liệu
- Đối với hàm thông báo cơ chế Signal sẽ dùng thông báo cho 1 luồng đợi tín hiệu:
```
    pthread_cond_signal(&cond)
```
__+__ Tham số truyền vào là địa chỉ của biến điều kiện.


Ví dụ triển khai trong chương trình cơ chế Wait/Signal:

```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0; //Cờ báo có dữ liệu
int data = 0;


void* task_calculation(void* arg) {
    char* nameTask = (char*)arg;
    while(1){
        pthread_mutex_lock(&mtx);
        while (!ready){
            printf("[%s] : is sleeping\n",nameTask);
            pthread_cond_wait(&cond, &mtx);
        }
        printf("[%s] : reading data %d\n",nameTask,data);
        ready = 0;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* task_sensor(void* arg) {
    char* nameTask = (char*)arg;
   
    while(1){
        pthread_mutex_lock(&mtx);
        data = rand() % 50;


        if(data > 20){
            printf("[%s] : notify task_calculation\n",nameTask);
            ready = 1;
            pthread_cond_signal(&cond);
        }
        else{
            printf("[%s] : processing\n",nameTask);
        }
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t t1,t2;
    srand(time(NULL));

     pthread_create(&t1,NULL,task_calculation,"task_calculation");
     pthread_create(&t2,NULL,task_sensor,"task_sensor");

     pthread_join(t1,NULL);
    // pthread_join(t2,NULL);


    return 0;
}
```
- Đối với hàm thông báo cơ chế Broadcast sẽ dùng để thông báo cho nhiều luồng đợi tín hiệu:
```
    pthread_cond_broadcast(*cond)
```
__+__ Tham số truyền vào là địa chỉ của biến điều kiện.

Ví dụ triển khai trong chương trình cơ chế Wait/Broadcast:
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
/*
    - Giữ cờ đếm broadcast_count – đại diện cho “phiên dữ liệu hiện tại”.


    - Mỗi worker lưu last_handled riêng của nó.


    - Nếu broadcast_count > last_handled → có dữ liệu mới → worker đọc.


*/
#define MAX_WORKER 3

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int data = 0;
int broadcast_count = 0;  // số lần signaler broadcast


typedef struct {
    int id;               // id đại diện cho mỗi thread worker
    int last_handled;     // worker nhớ mình đã xử lý đến broadcast nào
} worker_info_t;

void* worker(void* arg) {
    worker_info_t* info = (worker_info_t*)arg;
    while (1) {
        pthread_mutex_lock(&mtx);

        //lặp liên tục nếu signaler chưa có thông báo mới -> broadcast_count chưa được update
        while (info->last_handled == broadcast_count) {
            printf("[worker %d] : waiting for new data\n", info->id);
            pthread_cond_wait(&cond, &mtx);
        }


        // Cập nhật trạng thái và xử lý dữ liệu mới
        info->last_handled = broadcast_count;  
        printf("[worker %d] : reading data %d (broadcast %d)\n",
               info->id, data, broadcast_count);
        pthread_mutex_unlock(&mtx);


        usleep(500000); // giả lập thời gian xử lý 0.5s
    }
    return NULL;
}

void* signaler(void* arg) {
    char* nameTask = (char*)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        data = rand() % 100;
        if (data > 50) {
            broadcast_count++;
            printf("[%s] : broadcast new data = %d (broadcast %d)\n",
                   nameTask, data, broadcast_count);
            pthread_cond_broadcast(&cond);
        } else {
            printf("[%s] : skip broadcast (data=%d)\n", nameTask, data);
        }
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}


int main() {
    srand(time(NULL));
    pthread_t signal_thread;
    pthread_t workers[MAX_WORKER];
    worker_info_t infos[MAX_WORKER];


    pthread_create(&signal_thread, NULL, signaler, "signaler");


    for (int i = 0; i < MAX_WORKER; i++) {
        infos[i].id = i + 1;
        infos[i].last_handled = 0;
        pthread_create(&workers[i], NULL, worker, &infos[i]);
    }


    pthread_join(signal_thread, NULL);
    return 0;
}

```

#### 8 - Dọn dẹp tài nguyên
- Trong thư viện POSIX thread sẽ cung cấp hàm sẽ thực thi dọn dẹp tài nguyên khi chương trình kết thúc để dọn dẹp một cách tự động hoặc người dùng có thể chủ động trong việc dọn dẹp tài nnguyên. 

#### - Đăng ký hàm để dọn dẹp 
- Trước khi thực thi được hàm cleanup handler là hàm dọn dẹp tài nguyên ta phải đăng ký hàm đó để được dọn dẹp.

```
    void pthread_cleanup_push(void (*routine)(void *), void *arg);
```
__+__ Tham số 1: Con trỏ đến hàm cleanup (hàm được gọi để thu dọn nguyên).

__+__ Tham số 2: Địa chỉ của đối tượng mà bạn muốn giải phóng.
#### - Hàm thực thi hàm dọn dẹp 
- Dùng để thực thi hàm cleanup handler (hàm dọn dẹp) đã đăng ký gần nhất bới hàm `pthread_cleanup_push` hoạt dộng theo cơ chế LIFO (lấy phần tử mới nhất ra - tương ứng với hàm đã push trước đó) hàm dưới đây sẽ dọn dẹp một cách tự động bởi hệ thống khi chương trình kết thúc hoặc bởi người dùng.
```
    void pthread_cleanup_pop(int execute)
``` 
__+__ execute = 0: Chỉ gỡ handler ra khỏi stack, không gọi hàm cleanup.

__+__ execute != 0: Gỡ và gọi luôn hàm cleanup handler ngay lập tức.
#### 9 - Luồng báo thức (Alarm thread)
- Ở ví dụ chương trình biến điều kiện thì luồng có cơ chế Wait sẽ được đánh thức đợi tín hiệu từ luồng thông báo ngoài đó ra sẽ đợi một event sự kiện khi có phiên dữ liệu mới, nhưng giờ có một tác vụ chạy theo định kỳ và chu kỳ muốn một luồng sẽ được kích hoạt theo một thời điểm nhất định ví dụ luồng đó dùng để đọc dữ liệu cảm biến sau một chu kỳ thiết lập thì chương trình dưới đây ví dụ cho việc tạo một luồng báo thức để đánh thức luồng đọc dữ liệu cảm biến và cơ chế dọn dọn dẹp tài nguyên dùng hàm `cleanup`.

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#define ALARM_ms     100     //thời gian báo thức (ms)
#define DELAY_ms     1000  
#define ALARM_COUNTER   30  //số lần ALARM lặp lại


//biến toàn cục để mô phỏng việc đọc/ghi dữ liệu giữa nhiều luồng
atomic_int updated_sensor = 0;
atomic_int running = 1;


//cấu trúc chứa thông tin cấu hình của task Os
typedef struct OsTaskCtrl{
    pthread_mutex_t mx;
    pthread_t   tid;
    char* name;
}OsTaskCtrl;


//bảng cấu hình thông số cho task duy nhất
OsTaskCtrl Os_ConfigTable = {
    .name = "task_sensor",
    .tid = (pthread_t)0
};


//giải phóng worker tự động
void cleanup_worker(void* arg){
    OsTaskCtrl* const s = (OsTaskCtrl*)arg;
    printf("%s done reclaim resources\n",s->name);
    pthread_mutex_destroy(&s->mx);
}


// Thread worker: làm 1 việc rồi dừng
void* Task_sensor(void* arg) {
    OsTaskCtrl* const s = (OsTaskCtrl*)arg;
    srand(time(0));
    //đăng ký hàm cleanup sẽ được gọi khi luồng thực hiện xong
    pthread_cleanup_push(cleanup_worker,s);


    //truy cập data và xử lý dữ liệu
    pthread_mutex_lock(&s->mx);


    printf("[%s]đang đọc...\n", s->name);
    int temp = rand() % 100;    //mô phỏng đọc data ngẫu nhiên
    atomic_store(&updated_sensor,temp);    //ghi dự liệu vào biến toàn cục an toàn
    printf("[%s]Hoàn thành, thoát!\n",s->name);
   
    //bỏ truy cập data, cho phép các luồng khác sử dụng
    pthread_mutex_unlock(&s->mx);


    pthread_cleanup_pop(1); //gọi hàm cleanup để thu hồi tài nguyên


    return NULL;
}
// Thread scheduler: tạo worker theo lịch
void* scheduler_thread(void* arg) {
    static int currentCycle = 0;
    while (currentCycle < ALARM_COUNTER) {    //chu kỳ lặp bào thức
        static int AlarmTick = 0;
        if(AlarmTick < ALARM_ms){
            AlarmTick++; //mô phỏng biến đếm tràn trong timer
        }
        else{
            pthread_mutex_init(&Os_ConfigTable.mx,NULL);
            //khởi tạo
            if (pthread_create(&Os_ConfigTable.tid, NULL, Task_sensor,&Os_ConfigTable) != 0) {
                perror("pthread_create worker failed");
                continue;
            }


            pthread_detach(Os_ConfigTable.tid);  


            printf("[Scheduler] Đã tạo %s\n",Os_ConfigTable.name);
            AlarmTick = 0;   //reset biến đếm tràn timer
            currentCycle++; //cập nhật số lần lặp Alarm
        }
        usleep(DELAY_ms);
    }
    printf("[Os Scheduler] : Terminater\n");
    atomic_store(&running,0);
    return NULL;
}


int main() {
    pthread_t sched;
    pthread_mutex_t main_mx;
    pthread_mutex_init(&main_mx,NULL);
    if (pthread_create(&sched, NULL, scheduler_thread, NULL) != 0) {
        perror("pthread_create scheduler failed");
        return 1;
    }


    pthread_detach(sched);


    //mô phỏng luồng chính cập nhật dữ liệu từ task_sensor
    while(running){
        printf("[main thread] dữ liệu cập nhật từ %s : %d\n",Os_ConfigTable.name,atomic_load(&updated_sensor));
        pthread_mutex_unlock(&main_mx);
        sleep(1);
    }


    printf("[Main Os] : Terminated\n");


    return 0;
}

```
