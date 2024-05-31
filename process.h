#ifndef PROCESS_H
#define PROCESS_H

#define HIGH_PRIORITY 2
#define MEDIUM_PRIORITY 4
#define LOW_PRIORITY 8

#include "queue.h"

typedef struct {
    int pid;
    int duration; //how long the process required to run finish

    int remainingTime;
    int waitingTime;
    int turnaroundTime;

    bool isFinished;
    int runTurn;
} Process;

typedef struct {
    int timeQuantum;
    Queue queue;
} ProcessQueue;

void initProcessQueue(ProcessQueue *p_queue, int timeQuantum);
bool isFinished(Process *process);
void updateTurnaround(Process *process);

void calculateAverage(ProcessQueue *finishQueue, float *averageWait, float *averageTurnaround);
void displayResults(ProcessQueue *finishQueue, float *averageWait, float *averageTurnaround);

#endif // PROCESS_H
