#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
};

// Function to sort processes based on burst time (SJF)
void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap processes[j] and processes[j + 1]
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int wt[], int tat[]) {
    wt[0] = 0;  // First process has zero waiting time
    tat[0] = wt[0] + processes[0].burst_time; // Turnaround time for first process
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + processes[i - 1].burst_time;
        if (tat != NULL) {  // Check if tat is not NULL before updating it
            tat[i] = wt[i] + processes[i].burst_time;
        }
    }
}


// Function to calculate average waiting time and turnaround time
void calculateAvgTimes(struct Process processes[], int n) {
    int wt[n], tat[n];
    calculateTimes(processes, n, wt, tat);

    float avg_wt = 0, avg_tat = 0;
    printf("PID \tWT \tTAT\n");
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("%d\t %d\t %d\n", processes[i].pid, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", avg_wt / n);
    printf("Average turnaround time = %.2f\n", avg_tat / n);
}

// Function to print the Gantt chart
void printGanttChart(struct Process processes[], int n, int wt[]) {
    int time = 0;
    printf("\nGantt Chart: \n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", processes[i].pid);
        time += processes[i].burst_time;  // Add the burst time to the current time
    }
    printf("\n");

    // Print timeline
    time = 0;
    printf("0\t");
    for (int i = 0; i < n; i++) {
        time += processes[i].burst_time;
        printf("%d\t", time);
    }
    printf("\n");
}

int main() {
    int n = 5; // Number of processes
    struct Process processes[] = {
        {1, 0, 8},
        {2, 1, 1},
        {3, 2, 3},
        {4, 3, 2},
        {5, 4, 6}
    };

    // Sort processes based on burst time
    sortProcesses(processes, n);

    // Calculate average waiting time and turnaround time
    calculateAvgTimes(processes, n);

    // Print the Gantt Chart
    int wt[n];  // Waiting time array
    int tat[n];  // Turnaround time array
    calculateTimes(processes, n, wt, tat);  // Use a valid tat array

    printGanttChart(processes, n, wt);

    return 0;
}

