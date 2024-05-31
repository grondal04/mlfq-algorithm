
#include "process.h"

void initProcessQueue(ProcessQueue *p_queue, int timeQuantum) {
    initQueue(&p_queue->queue);
    p_queue->timeQuantum = timeQuantum;
}

bool isFinished(Process *process) {
    return process->isFinished;
}

void updateTurnaround(Process *process) {
    process->turnaroundTime = process->duration + process->waitingTime;
}

void calculateAverage(ProcessQueue *finishQueue, float *averageWait, float *averageTurnaround) {

    Node *runningNode = finishQueue->queue.front;
    Process *runningProcess = (Process*)runningNode->element;

    //printf("Assign calculate success!");

    if (runningNode == NULL) {
        printf("Calculate average error: Cannot calculate NULL.");
        return;
    }

    while (1) {
        *averageWait += runningProcess->waitingTime;
        *averageTurnaround += runningProcess->turnaroundTime;

        if (runningNode->next != NULL) {
            runningNode = runningNode->next;
            runningProcess = (Process*)runningNode->element;
        } else {
            break;
        }
    }

    *averageWait /= (float) finishQueue->queue.size;
    *averageTurnaround /= (float) finishQueue->queue.size;\

    //printf("Calculated perfectly!!\n");
}

void displayResults(ProcessQueue *finishQueue, float *averageWait, float *averageTurnaround) {

    Node *runningNode = finishQueue->queue.front;
    Process *runningProcess = (Process*)runningNode->element;

    if (runningNode == NULL) {
        printf("Display error: Cannot display NULL.");
        return;
    }
    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    while (1) {
        printf("%d\t%d\t\t%d\t\t%d\n",
        runningProcess->pid, runningProcess->duration, runningProcess->waitingTime, runningProcess->turnaroundTime);

        if (runningNode->next != NULL) {
            runningNode = runningNode->next;
            runningProcess = (Process*)runningNode->element;
        } else {
            break;
        }
    }

    printf("Average Waiting Time: %.2f\n", *averageWait);
    printf("Average Turnaround Time: %.2f\n", *averageTurnaround);
}
