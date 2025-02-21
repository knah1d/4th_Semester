#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int arrival_time;
    int remaining_time;
};
int count = 0;
void SJF(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    int turnaround_time[n];
    int waiting_time[n];
    int executed_processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed_processes < n) {
        int min_burst = 1000;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_burst && processes[i].remaining_time > 0) {
                min_burst = processes[i].remaining_time;
                selected_process = i;
            }
        }
        count++;
        if (selected_process == -1) {
            current_time++;
            continue;
        }
        
        

        executed_processes[selected_process] = processes[selected_process].pid;
        processes[selected_process].remaining_time--;
        current_time++;

        if (processes[selected_process].remaining_time == 0) {
            completed_processes++;
            int finish_time = current_time;
            turnaround_time[selected_process] = finish_time - processes[selected_process].arrival_time;
            waiting_time[selected_process] = turnaround_time[selected_process] - processes[selected_process].burst_time;
        }
    }

    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;
    int i;
    
    printf("Gantt Chart:\n");
    for (i = 0; i < n-1; i++) {
        printf("p%d -> ", executed_processes[i]);
    }
    printf("p%d", executed_processes[i]);
    
    printf("\nTurnaround Time:");
    for (int i = 0; i < n; i++) {
        printf(" %d", turnaround_time[i]);
        avg_turnaround_time += turnaround_time[i];
    }
    avg_turnaround_time /= n;
    
    printf("\nWaiting Time:");
    for (int i = 0; i < n; i++) {
        printf(" %d", waiting_time[i]);
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("%d\n",count);
}

int main() {
    struct Process processes[] = {
        {1, 20, 40, 0, 0},
        {2, 25, 30, 25, 0},
        {3, 25, 30, 30, 0},
        {4, 15, 35, 60, 0},
        {5, 10, 5, 100, 0},
        {6, 10, 10, 105, 0}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    SJF(processes, n);
    return 0;
}
