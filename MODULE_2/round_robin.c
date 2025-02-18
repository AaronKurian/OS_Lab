#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;        // Process ID
    int burst_time; // Burst time
};

// Function to simulate Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n];
    int wt[n], tat[n];
    for (int i = 0; i < n; ++i)
        remaining_time[i] = processes[i].burst_time;

    int current_time = 0;
    int completed = 0;
    
    // Array to track the Gantt chart process sequence
    int gantt_chart[100], gantt_time[100];  
    int chart_index = 0;

    // Simulate the Round Robin process execution
    while (completed < n) {
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                flag = 1;
                gantt_chart[chart_index] = processes[i].id;   // Record the process in Gantt chart
                gantt_time[chart_index] = current_time;      // Record the time at which the process starts
                chart_index++;

                if (remaining_time[i] <= time_quantum) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    printf("Process P%d completed at time %d\n", processes[i].id, current_time);
                    tat[i] = current_time;
                    wt[i] = tat[i] - processes[i].burst_time;
                    printf("Process P%d WT=%d TAT=%d\n", processes[i].id, wt[i], tat[i]);
                    completed++;
                } else {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
        if (!flag)
            break;
    }

    // Calculate and display average waiting time and turnaround time
    float awt = 0, atat = 0;
    for (int i = 0; i < n; i++) {
        awt = awt + wt[i];
        atat = atat + tat[i];
    }
    printf("Average WT = %.2f Average TAT = %.2f\n", awt / n, atat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < chart_index; i++) {
        printf("|P%d\t", gantt_chart[i]);
    }
    printf("|\n");

    // Print the time line for the Gantt chart
    printf("0 ");
    for (int i = 0; i < chart_index; i++) {
        printf("\t%d", gantt_time[i] + (processes[gantt_chart[i] - 1].burst_time > time_quantum ? time_quantum : processes[gantt_chart[i] - 1].burst_time));
    }
    printf("\n");
}

int main() {
    int n = 3; // Number of processes
    struct Process processes[] = {{1, 4}, {2, 3}, {3, 5}};
    int time_quantum = 2;

    printf("Round Robin Scheduling:\n");
    roundRobin(processes, n, time_quantum);

    return 0;
}

