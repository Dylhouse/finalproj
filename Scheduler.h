#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include "Process.h"

using namespace std;

class Scheduler
{
public:
    static void FCFS(vector<Process> processes);

    static void SJF(vector<Process> processes);

    static void PriorityScheduling(vector<Process> processes);

    static void RoundRobin(vector<Process> processes, int quantum);

    static void CompareAll(vector<Process> processes);
};

#endif
