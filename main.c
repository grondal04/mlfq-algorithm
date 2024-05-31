#include "queue.h"
#include "process.h"
#include "mlfq_std.h"

extern float averageWait = 0.0;
extern float averageTurnaround =0.0;

int run(Process *process, int time_slice);
void wait(Process *process, int actualyWaitTime);

int main(int argc, char* argv[]) {

    ProcessQueue highPriority, mediumPriority, lowPriority;
    ProcessQueue finishedProcess; //SAVE FINISHED QUEUE, and RESULT

    initProcessQueue(&highPriority, HIGH_PRIORITY);
    initProcessQueue(&mediumPriority, MEDIUM_PRIORITY);
    initProcessQueue(&lowPriority, LOW_PRIORITY);
    initProcessQueue(&finishedProcess, 0);

    int numProcesses = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        Process *newProcess = (Process*) malloc (sizeof(Process));

        //printf("Enter process ID for process %d: ", i + 1);
        //scanf("%d", &newProcess->pid);
        newProcess->pid = i + 1;
        printf("Enter duration for process %d: ", i + 1);
        scanf("%d", &newProcess->duration);

        newProcess->remainingTime = newProcess->duration;
        newProcess->waitingTime = 0;
        newProcess->turnaroundTime = 0;
        newProcess->isFinished = false;
        newProcess->runTurn = 0;

        enqueue(&highPriority.queue, newProcess);
        printf("Process %d enqueued in queue with time quantum %d\n", newProcess->pid, highPriority.timeQuantum);
    }

    runQueue(&highPriority, &mediumPriority, &finishedProcess);
    runQueue(&mediumPriority, &lowPriority, &finishedProcess);
    runQueue(&lowPriority, &lowPriority, &finishedProcess);

    calculateAverage(&finishedProcess, &averageWait, &averageTurnaround);
    displayResults(&finishedProcess, &averageWait, &averageTurnaround);

    return 0;
}

void runQueue(ProcessQueue *fromQueue, ProcessQueue *toQueue, ProcessQueue *finishedQueue) {

    while (!isQueueEmpty(&fromQueue->queue)) {
        Process *runningProcess = (Process*)dequeue(&fromQueue->queue);

        ///PROCESS RUN
        printf("\n\n\n");
        int runtime = run(runningProcess, fromQueue->timeQuantum);

        ///PROCESS WHICH IS NOT RUN, WILL WAIT
        waitQueue(fromQueue, runtime);
        if (!isQueueEmpty(toQueue) && (&fromQueue->queue != &toQueue->queue)) {
            waitQueue(toQueue, runtime);
        }

        ///IF PROCESS IS DONE, PUT IT IN finishedQueue, otherwise, the next Queue
        if (runningProcess->isFinished == true) {
            updateTurnaround(runningProcess);
            printf("Process %d finished execution\n", runningProcess->pid);
            enqueue(&finishedQueue->queue, runningProcess);
        } else if (runningProcess->isFinished == false){
            //Process enter the new queue also have to wait for another call
            enqueue(&toQueue->queue, runningProcess);
        }
        printf("\n\n\n");
    }

}

void waitQueue(ProcessQueue *waitQueue, int actualWaitTime) {
    if (!isQueueEmpty(&waitQueue->queue)) {
        Node *runningNode = waitQueue->queue.front;
        Process *pointer_process = (Process*)runningNode->element;

        while (runningNode != NULL) {
            //WAIT FOR 'runtime' AMOUNT OF TIME
            wait(pointer_process, actualWaitTime);

            //MOVE TO NEXT NODE
            if (runningNode->next != NULL) {
                runningNode = runningNode->next;
                pointer_process = (Process*)runningNode->element;
            } else {
                runningNode = NULL;
                pointer_process = NULL;
            }
        }
    }

}

void wait(Process *process, int actualyWaitTime) {
    process->waitingTime = process->waitingTime + actualyWaitTime;
    printf("wait time of process %d: %d\n", process->pid, process->waitingTime);
}

int run(Process *process, int time_slice) {
    int runTime = 0;

    char text[100];
    switch (time_slice) {
        case HIGH_PRIORITY:
            strcpy(text,"high priority");
            break;
        case MEDIUM_PRIORITY:
            strcpy(text,"medium priority");
            break;
        case LOW_PRIORITY:
            strcpy(text,"low priority");
            break;
    }
    printf("Process %d is running in %s queue\n", process->pid, text);

    int runningTime = time_slice;

    if (time_slice >= process->remainingTime) {
        runningTime = process->remainingTime; //If timeslice > remain time, we assigned runTime = remain time

        process->remainingTime = 0; //process is finish
        process->isFinished = true;
    } else {
        process->remainingTime -= runningTime; //otherwise, it's not finish, we minus remaining time by running time
    }

    return runningTime;
}
