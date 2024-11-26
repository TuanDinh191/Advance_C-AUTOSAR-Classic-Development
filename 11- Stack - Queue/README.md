# Bài 11: Stack - Queue 
#### 1. Stack 
#### - Định nghĩa:
 - Stack như được biết là một nơi để chứa dữ liệu cho các tham số truyền vào hàm và các biến cục bộ thì Stack sẽ có một tên gọi khác là ngăn xếp là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO) cụ thể hơn là phần tử cuối cùng được thêm vào stack khi muốn lấy ra thì nó cũng là phần tử đầu tiên được lấy ra, ngoại trừ phần tử cuối cùng thì muốn lấy phần tử trong Stack thì phải lấy ra các phần từ nằm đỉnh trên phần tử đó.
 - Các thao tác cơ bản trên Stack bao gồm : 
  `push` để thêm một phần tử vào đỉnh của Stack khi Stack đầy thì không thể thao tác push trên đỉnh Stack được.

  `pop` để xóa một phần tử ở đỉnh Stack, không thể xóa phần tử của một Stack nếu Stack đó rỗng.
  
  `top` để lấy giá trị phần tử ở đỉnh stack, nếu trong stack chỉ có một phần tử thì top sẽ bắt đầu = 0 khi giá trị top(max) tức là lấy giá trị đỉnh cao nhất của Stack đó thì lúc đó top(max) = size - 1 tức là sẽ bằng kích thước của Stack đó trừ 1 lúc này là Stack đang đầy tức là top lúc này đang lấy giá trị phần tử cuối cùng được thêm vào stack đó. Còn top = -1 tức là Stack đang rỗng. 

- Để mô phỏng hoạt động của một cấu trúc Stack trong C thì ta sẽ code theo dạng dưới đây:

Để mô phỏng một cấu trúc như Stack thì ta sẽ dùng struct, trong struct này sẽ chứa thành phần thứ nhất là một con trỏ kiểu int trỏ lưu địa chỉ của vùng nhớ cấp phát động để lưu các phần tử trong mảng có thể mô phỏng như Stack này chứa các giá trị của các phần tử, thành phần thứ 2 là kích thước của cái Stack này là có thể chứa bao nhiêu phần tử, giá trị top để xem giá trị tại đỉnh của Stack và nhờ giá trị top này có thể biết Stack này đang trống bao nhiêu phần tử đang rỗng hay đang full.    
```
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int* items;
    int size;
    int top;
} Stack;
```
Hàm initialize dưới đây là sẽ khởi tạo cho một Stack là cấp phát vùng nhớ để lưu giá trị phần tử, chọn kích cỡ cho một stack, đặt giá trị top ban đầu khi Stack này chưa chứa phần tử nào sẽ là top = -1.  

```
void initialize( Stack *stack, int size) {
    stack->items = (int*) malloc(sizeof(int) * size);
    stack->size = size;
    stack->top = -1;
}
```
Hàm is_empty dưới đây sẽ kiểm tra Stack có rỗng hay không bằng cách so sánh giá trị top có bằng 1 hay không 

```
int is_empty( Stack stack) {
    return stack.top == -1;
}
```

Hàm is_full dưới đây sẽ kiểm tra Stack này đã đầy hay chưa bằng cách so sánh giá trị top này có bằng kích thước stack trừ 1 hay không.    

```
int is_full( Stack stack) {
    return stack.top == stack.size - 1;
}
```
Hàm push dưới đây sẽ mô phỏng cho việc thêm một phần tử vào đỉnh Stack để thêm một phần tử vào đỉnh stack sẽ kiểm tra Stack này đã đầy chưa nếu Stack đầy thì sẽ không thể thao tác push được. 

```
void push( Stack *stack, int value) {
    if (!is_full(*stack)) {
        stack->items[++stack->top] = value;
    } else {
        printf("Stack overflow\n");
    }
}
```

Hàm pop dưới đây sẽ mô phỏng cho việc xóa một phần tử ở đỉnh Stack để xóa một phần tử ở đỉnh Stack sẽ kiểm tra Stack này có trống không nếu Stack rỗng thì sẽ không thể thao tác pop được.

```
int pop( Stack *stack) {
    if (!is_empty(*stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}
```

Hàm top dưới đây sẽ mô phỏng cho việc thao tác top lấy giá trị tại phần tử từ đỉnh của stack, nếu stack rỗng thì không thể lấy thao tác top.

```
int top( Stack stack) {
    if (!is_empty(stack)) {
        return stack.items[stack.top];
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}
```

Hàm main dưới đây mô phỏng cho việc khởi tạo một stack có chứa 5 phần tử, mô phỏng thao tác push cho nhiều phần tử, sau khi thực hiện tác thao tác push và pop sẽ thao tác top để lấy giá trị tại đỉnh Stack xem giá trị sau khi thực hiện thao push và pop thay đổi như thế nào.

```
int main() {
    Stack stack1;
    initialize(&stack1, 5);


    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);
    push(&stack1, 50);
    push(&stack1, 60);

    printf("Top element: %d\n", top(stack1));

    printf("Pop element: %d\n", pop(&stack1));
    printf("Pop element: %d\n", pop(&stack1));

    printf("Top element: %d\n", top(stack1));

    return 0;
}
```
#### 2. Queue
 #### - Định nghĩa: 
- Queue (hàng đợi) là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO) cụ thể hơn là phần tử đầu tiên được thêm vào Queue khi muốn lấy ra thì nó cũng là phần tử đầu tiên được lấy ra, vì thế sẽ chia ra nhiều kiểu của Queue 2 kiểu Queue thông dụng dùng nhiều nhất là Linear Queue và Circular Queue.

- Các thao tác cơ bản trên Queue bao gồm:

`enqueue` để thêm vào cuối hàng đợi. 

`dequeue` lấy phần tử từ đầu hàng đợi.

`front` để lấy giá trị của phần tử đứng đầu hàng đợi. 

`rear` để lấy giá trị của phần tử đứng cuối hàng đợi.

- Linear Queue là một Queue theo nguyên tác FIFO nhưng khi Queue đã đầy (rear = size -1 ) và có khoảng trống do các phần tử đã bị dequeue thì không thể thao tác enqueue để thêm phần tử mới, chỉ thao tác enqueue khi đã dequeue hết phần tử trong Queue đó tức là Queue đã rỗng và front, rear được reset về giá trị ban đầu bằng -1. 

Để mô phỏng hoạt động của một cấu trúc LinearQueue trong C thì ta sẽ code theo dạng dưới đây:

Để mô phỏng một cấu trúc như LinearQueue thì ta sẽ dùng struct, trong struct này sẽ chứa thành phần thứ nhất là một con trỏ kiểu int trỏ lưu địa chỉ của vùng nhớ cấp phát động để lưu các phần tử trong mảng có thể mô phỏng như Queue này chứa các giá trị của các phần tử, thành phần thứ 2 là kích thước của cái Queue này là có thể chứa bao nhiêu phần tử, giá trị front và rear sẽ tương ứng lấy giá trị phần tử đứng đầu và đứng cuối hàng đợi, nhờ vào giá trị rear và front thì có thể biết Queue đang trống bao nhiêu phần tử hay đang rỗng và nhờ vào giá trị rear có thể biết Queue này đã full chưa.  

```
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a queue
typedef struct{
    int *items;
    int rear;
    int front;
    int size;
} Queue;
```
Hàm initialize dưới đây là sẽ khởi tạo cho một LinearQueue là cấp phát vùng nhớ để lưu giá trị phần tử, chọn kích cỡ cho một Queue, đặt giá trị front, rear ban đầu khi Queue này chưa chứa phần tử nào sẽ là front = rear = -1.  

```
// initialize the queue
Queue *initialize(int size){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
    return queue;
}
```
Hàm isFull dưới đây sẽ kiểm tra Queue dưới đã đầy hay chưa bằng cách so sánh giá trị rear này có bằng kích thước của Queue trừ 1 hay không.

```
// check if the queue is full
int isFull(Queue queue){
    return queue.rear == queue.size - 1;
}
```
Hàm isEmpty dưới đây sẽ kiểm tra Queue có rỗng hay không bằng cách so sánh giá trị front này có bằng -1 hay không ( có thể dùng giá trị rear để so sánh) hoặc để chắc ăn hơn thì so sánh giá trị front lớn hơn giá trị rear. 

```
// check if the queue is empty
int isEmpty(Queue queue){
    return (queue.front == -1 || queue.front > queue.rear);
}
```
Hàm enqueue dưới đây sẽ mô phỏng cho việc thêm một phần tử vào cuối hàng đợi, để thêm một phần tử vào cuối hàng đợi sẽ kiểm tra Queue này đã đã đầy chưa nếu Queue đầy thì sẽ không thể thao tác enqueue được.

```
// add an element to the queue (enqueue)
void enqueue(Queue *queue, int data){
    if (isFull(*queue)){
        printf("Queue is full! Cannot add more elements.\n");
    } 
    else{
        if (isEmpty(*queue)){
            queue->front = queue->rear = 0;
        }
        else{
            queue->rear++;
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}
```
Hàm dequeue dưới đây sẽ mô phỏng cho việc lấy phần tử từ đầu hàng đợi, để lấy được phần tử từ đầu hàng đợi sẽ kiểm tra Queue này có rỗng hay không nếu Queue này trống thì sẽ không thể thao tác dequeue. 

```
// remove an element from the queue (dequeue)
int dequeue(Queue *queue){
    if (isEmpty(*queue)){
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    } 
    else{
        int value = queue->items[queue->front];
        if (queue->front == queue->rear){
            queue->front = queue->rear = -1;
        }
        else{
            queue->front++;
        }
        return value;
    }
}
```
Hàm display dưới đây sẽ hiển thị các phần tử có trong Queue, để hiện thị display sẽ kiểm tra Queue này có rỗng hay không nếu Queue này trống thì sẽ không thể hiển thị các phần tử trong Queue được. 

```
// Function to display the elements of the queue
void display(Queue queue){
    if (isEmpty(queue)){
        printf("Queue is empty!\n");
    } 
    else{
        printf("Queue elements: ");
        for (int i = queue.front; i <= queue.rear; i++){
            printf("%d ", queue.items[i]);
        }
        printf("\n");
    }
}
```

Hàm main dưới đây mô phỏng cho việc khởi tạo một LinearQueue có chứa 5 phần tử, mô phỏng thao tác enqueue cho nhiều phần tử, sau khi thực hiện tác thao tác enqueue sẽ gọi hàm display để hiển thị giá trị của các phần tử trong Queue, sau đó sẽ thực hiện các thao tác dequeue tiếp tục gọi hàm display để xem các phần tử trong Queue, tương tự các code còn lại.
```
int main()
{
    Queue *queue = initialize(5);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    enqueue(queue, 60);

    display(*queue);

    printf("Dequeued %d\n", dequeue(queue));
    printf("Dequeued %d\n", dequeue(queue));
    printf("Dequeued %d\n", dequeue(queue));
    printf("Dequeued %d\n", dequeue(queue));
    printf("Dequeued %d\n", dequeue(queue));
    display(*queue);

    enqueue(queue, 15);

    display(*queue);

    // enqueue(queue, 60); // This should show "Queue is full!"
    
    return 0;
}

```
- Circular Queue là một Queue theo nguyên tác FIFO nhưng khi Queue đạt trạng thái (rear = size -1) và có khoảng trống do các phần tử đã bị dequeue thì giá trị rear có thể "quay vòng" về vị trị 0 có thể thao tác enqueue để thêm phần tử mới vào các khoảng trống, chỉ khi Queue không trống các phần tử nào tức là full thì không thể thực hiện enqueue, đối với dequeue có thể dequeue vị trí các phần tử đã được enqueue lần thứ 2 thì giá trị front có thể "quay vòng" về vị trí 0 để thao tác dequeued để xóa các phần tử chỉ khi Queue trống hoàn toàn thì không thể thực hiện dequeue.   

Để mô phỏng hoạt động của một cấu trúc CircularQueue trong C thì ta sẽ code theo dạng dưới đây:

Để mô phỏng một cấu trúc như CircularQueue thì ta sẽ dùng struct, trong struct này sẽ chứa thành phần thứ nhất là một con trỏ kiểu int trỏ lưu địa chỉ của vùng nhớ cấp phát động để lưu các phần tử trong mảng có thể mô phỏng như Queue này chứa các giá trị của các phần tử, thành phần thứ 2 là kích thước của cái Queue này là có thể chứa bao nhiêu phần tử, thành phần thứ 3 giá trị front và rear sẽ tương ứng lấy giá trị phần tử đứng đầu và đứng cuối hàng đợi, nhờ vào giá trị rear và front thì có thể biết Queue đang trống bao nhiêu phần tử hay đang rỗng và nhờ vào giá trị rear có thể biết Queue này đã full chưa.  

```
#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    int* items;
    int size;
    int front, rear;
} Queue;
```

Hàm initialize dưới đây là sẽ khởi tạo cho một CircularQueue là cấp phát vùng nhớ để lưu giá trị phần tử, chọn kích cỡ cho một Queue, đặt giá trị front, rear ban đầu khi Queue này chưa chứa phần tử nào sẽ là front = rear = -1.  

```
void initialize(Queue *queue, int size) 
{
    queue->items = (int*) malloc(sizeof(int)* size);
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}
```

Hàm isEmpty dưới đây sẽ kiểm tra Queue có rỗng hay không bằng cách so sánh giá trị front này có bằng -1 hay không ( có thể dùng giá trị rear để so sánh).

```
int is_empty(Queue queue) {
    return queue.front == -1;
}
```

Hàm isFull dưới đây sẽ kiểm tra Queue dưới đã đầy hay chưa bằng cách lấy giá trị rear tăng lên 1 sau đó chia lấy phần dư để giá trị rear này có thể quay lại vị trí 0 có bằng giá trị của front hay không.  

```
int is_full(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;
}
```

Hàm enqueue dưới đây sẽ mô phỏng cho việc thêm một phần tử vào cuối hàng đợi và có thể thêm vào phần tử nào mà đã bị dequeue, để thêm một phần tử vào cuối hàng đợi sẽ kiểm tra Queue này đầy chưa nếu Queue đầy thì sẽ không thể thao tác enqueue được.

```
void enqueue(Queue *queue, int value) {
    if (!is_full(*queue)) {
        if (is_empty(*queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % queue->size;
        }
        queue->items[queue->rear] = value;
    } else {
        printf("Queue overflow\n");
    }
}
```
Hàm dequeue dưới đây sẽ mô phỏng cho việc lấy một phần tử từ đầu hàng đợi và có thể lấy một phần tử có vị trí đã được enqueue lần thứ 2 trở đi để lấy một phần tử từ đầu hàng đợi sẽ kiểm tra Queue này có trống hay không nếu Queue trống thì sẽ không thể thao tác enqueue được.
```
int dequeue(Queue *queue) {
    if (!is_empty(*queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeued_value;
    } else {
        printf("Queue underflow\n");
        return -1;
    }
}
```
Hàm front có chức năng mô phỏng lấy giá trị của phần tử đứng đầu hàng đợi.

```
int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}
```
Hàm rear có chức năng mô phỏng lấy giá trị của phần tử đứng cuối hàng đợi.

```
int rear(Queue queue)
{
    if(!is_empty(queue))
        return queue.items[queue.rear];
    else {
        printf("Queue is empty\n");
        return -1;
    }
}
```

Hàm main dưới đây mô phỏng cho việc khởi tạo một CircularQueue có chứa 3 phần tử, mô phỏng thao tác enqueue cho nhiều phần tử, sau khi thực hiện tác thao tác enqueue sẽ gọi hàm front để hiển thị giá trị phần tử đứng đầu hàng đợi trong Queue, sau đó sẽ thực hiện các thao tác dequeue tiếp tục gọi hàm front để xem các phần tử đứng đầu trong Queue, tương tự cho code còn lại.

```
int main() {
    Queue queue;
    initialize(&queue, 3);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Front element: %d\n", front(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Dequeue element: %d\n", dequeue(&queue));

    printf("Front element: %d\n", front(queue));

    enqueue(&queue, 40);
    enqueue(&queue, 50);
    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Front element: %d\n", front(queue));

    return 0;
}
```