#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int burstTime;
};

void roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<Process> readyQueue;
    vector<int> remainingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    for (int i = 0; i < n; ++i) {
        readyQueue.push(processes[i]);
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();
        int executeTime = min(quantum, remainingTime[currentProcess.id - 1]);
        currentTime += executeTime;
        remainingTime[currentProcess.id - 1] -= executeTime;

        if (remainingTime[currentProcess.id - 1] > 0) {
            readyQueue.push(currentProcess);
        } else {
            turnaroundTime[currentProcess.id - 1] = currentTime;
            waitingTime[currentProcess.id - 1] = currentTime - processes[currentProcess.id - 1].burstTime;
        }
    }

    cout << "Gantt Chart:\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << " ";
    }
    cout << endl;

    cout << "Turnaround Time:\n";
    double totalTurnaround = 0;
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << ": " << turnaroundTime[i] << endl;
        totalTurnaround += turnaroundTime[i];
    }
    cout << "Average Turnaround Time: " << totalTurnaround / n << endl;

    cout << "Waiting Time:\n";
    double totalWaiting = 0;
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << ": " << waitingTime[i] << endl;
        totalWaiting += waitingTime[i];
    }
    cout << "Average Waiting Time: " << totalWaiting / n << endl;
}

int main() {
    vector<Process> processes = {
        {1, 2},
        {2, 1},
        {3, 8},
        {4, 4},
        {5, 5}
    };

    int quantum;
    cout << "Enter quantum for Round-Robin: ";
    cin >> quantum;

    roundRobin(processes, quantum);

    return 0;
}
