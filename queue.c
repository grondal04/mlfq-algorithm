#include "queue.h"

bool isQueueEmpty(Queue *queue) {
    return (queue->front == NULL);
}

void initQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;

    queue->size = 0;
}

bool enqueue(Queue *queue, void *newElement) {

    //Create a new node, then point newnode value to value
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL)
        return false;
    newNode->element = newElement;
    newNode->next = NULL;

    //if there's rear, connect that rear to newNode
    if (queue->rear != NULL) {
        queue->rear->next = newNode;
    }
    queue->rear = newNode; //Check alternative below

        /***
    alternative:
    if (queue->rear != NULL) {
        queue->rear = queue->rear->next;
        //As long as we have already linked newNode to the next of the rear, it is safe to make the rear move to next;
    } else {
        queue->rear = newNode;
    }

    ***/


    //Check if queue is empty
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
    }
    queue->size++;
    return true;
}

void* dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        return QUEUE_EMPTY;
    }

    Node *temp = queue->front;
    void *element = temp->element;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    queue->size--;
    return element;
}
