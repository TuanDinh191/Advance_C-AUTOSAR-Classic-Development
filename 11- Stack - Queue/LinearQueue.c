#include <stdio.h>
#include <stdlib.h>

// Structure to represent a queue
typedef struct{
    int *items;
    int front;
    int rear;
    int size;
} Queue;

// initialize the queue
Queue *initialize(int size){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
    return queue;
}

// check if the queue is full
int isFull(Queue queue){
    return queue.rear == queue.size - 1;
}

// check if the queue is empty
int isEmpty(Queue queue){
    return (queue.front == -1 || queue.front > queue.rear);
}

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
