#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
};

void fcfs(vector<Process>& processes) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);

    waitingTime[0] = 0;
    for (int i = 1; i < n; ++i) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; ++i) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
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

    fcfs(processes);

    return 0;
}
