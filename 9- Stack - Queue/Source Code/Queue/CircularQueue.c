#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    int* items;
    int size;
    int front, rear;
} Queue;

void initialize(Queue *queue, int size) 
{
    queue->items = (int*) malloc(sizeof(int)* size);
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}

int is_empty(Queue queue) {
    return queue.front == -1;
}

int is_full(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;
}

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

int dequeue(Queue *queue) {
    if (!is_empty(*queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front =  (queue->front + 1) % queue->size;
        }
        return dequeued_value;
    } else {
        printf("Queue underflow\n");
        return -1;
    }
}

int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

int rear(Queue queue)
{
    if(!is_empty(queue))
        return queue.items[queue.rear];
    else {
        printf("Queue is empty\n");
        return -1;
    }
}

void display(Queue queue){
    if (is_empty(queue)){
        printf("Queue is empty!\n");
    } 
    else{
        printf("Queue elements: ");
        for (int i = 0; i < queue.size; i++){
            printf("%d ", queue.items[i]);
        }
        printf("\n");
    }
}


int main() {
    Queue queue;
    initialize(&queue, 3);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    display(queue);
    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n\n", rear(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Dequeue element: %d\n", dequeue(&queue));
    enqueue(&queue, 50);
    enqueue(&queue, 60);
    display(queue);
    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n\n", rear(queue));
    
    enqueue(&queue, 70);
    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n\n", rear(queue));
    return 0;
}


