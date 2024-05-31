#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_EMPTY INT_MIN

#include "mlfq_std.h"

typedef struct {
    void *element;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;

    int size;
} Queue;

void initQueue(Queue *queue);
bool enqueue(Queue *queue, void *value); //void *value is uncertain, must check usage: enqueue(queue, &process)
void* dequeue(Queue *queue); //Dequeue

bool isQueueEmpty(Queue *queue);

#endif // QUEUE_H
