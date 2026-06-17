#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;

    int waitingTime;
    int turnaroundTime;
    int remainingTime;

    Process()
    {
        pid = 0;
        arrivalTime = 0;
        burstTime = 0;
        priority = 0;
        waitingTime = 0;
        turnaroundTime = 0;
        remainingTime = 0;
    }

    Process(int p, int arrival, int burst, int prio)
    {
        pid = p;
        arrivalTime = arrival;
        burstTime = burst;
        priority = prio;

        waitingTime = 0;
        turnaroundTime = 0;
        remainingTime = burst;
    }
};

#endif
