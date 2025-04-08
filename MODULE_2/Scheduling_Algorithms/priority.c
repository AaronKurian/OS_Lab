// #include <stdio.h>

// struct Process {
//     int processNo;
//     int arrivalTime;
//     int burstTime;
//     int priority;
// };

// // Sort processes based on arrival time and priority
// void sortProcesses(struct Process proc[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = i + 1; j < n; j++) {
//             if (proc[j].arrivalTime < proc[i].arrivalTime ||
//                 (proc[j].arrivalTime == proc[i].arrivalTime && proc[j].priority < proc[i].priority)) {
//                 // Swap processes
//                 struct Process temp = proc[i];
//                 proc[i] = proc[j];
//                 proc[j] = temp;
//             }
//         }
//     }
// }

// // Calculate waiting time
// void calculateWaitingTime(struct Process proc[], int wt[], int n) {
//     wt[0] = 0; // Waiting time for the first process is zero
//     int pstart[n];
//     pstart[0] = 0;
//     for (int i = 1; i < n; i++) {
//         pstart[i] = pstart[i - 1] + proc[i - 1].burstTime;
//         wt[i] = pstart[i] - proc[i].arrivalTime;
//     }
// }

// // Calculate turnaround time
// void calculateTurnaroundTime(struct Process proc[], int wt[], int tat[], int n) {
//     for (int i = 0; i < n; i++) {
//         tat[i] = proc[i].burstTime + wt[i];
//     }
// }

// // Function to print Gantt chart
// void printGanttChart(struct Process proc[], int n, int wt[], int tat[]) {
//     int total_time = 0;
//     printf("\nGantt Chart:\n");
//     printf("|");
//     for (int i = 0; i < n; i++) {
//         printf("P%d\t|", proc[i].processNo);
//     }
//     printf("\n");

//     printf("0");
//     for (int i = 0; i < n; i++) {
//         total_time += proc[i].burstTime;
//         printf("\t%d", total_time);
//     }
//     printf("\n");
// }

// int main() {
//     int n;
//     printf("Enter the number of processes: ");
//     scanf("%d", &n);

//     struct Process proc[n];
//     int wt[n], tat[n];

//     printf("Enter process details (arrival time, burst time, priority):\n");
//     for (int i = 0; i < n; i++) {
//         proc[i].processNo = i + 1;
//         printf("P%d: ", i + 1);
//         scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
//     }

//     // Sort processes based on arrival time and priority
//     sortProcesses(proc, n);

//     // Calculate waiting time and turnaround time
//     calculateWaitingTime(proc, wt, n);
//     calculateTurnaroundTime(proc, wt, tat, n);

//     // Display results
//     float awt = 0, atat = 0;
//     printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
//     for (int i = 0; i < n; i++) {
//         printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processNo, proc[i].arrivalTime,
//                proc[i].burstTime, proc[i].priority, wt[i], tat[i]);
//         awt += wt[i];
//         atat += tat[i];
//     }
    
//     printf("AWT=%.2f\t ATAT=%.2f\n", awt / n, atat / n);

//     // Print the Gantt chart
//     printGanttChart(proc, n, wt, tat);

//     return 0;
// }



#include <stdio.h>

struct Process {
    int processNo;
    int arrivalTime;
    int burstTime;
    int priority;
};

// Sort by arrival time, then priority
void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[j].arrivalTime < p[i].arrivalTime || 
               (p[j].arrivalTime == p[i].arrivalTime && p[j].priority < p[i].priority)) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

// Calculate waiting times
void calculateWaitingTime(struct Process p[], int n, int wt[]) {
    int start_time[n];
    start_time[0] = p[0].arrivalTime;
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        start_time[i] = start_time[i - 1] + p[i - 1].burstTime;
        wt[i] = start_time[i] - p[i].arrivalTime;
        if (wt[i] < 0) wt[i] = 0;  // Ensure non-negative
    }
}

// Turnaround = Waiting + Burst
void calculateTAT(struct Process p[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + p[i].burstTime;
}

// Print Gantt Chart
void printGanttChart(struct Process p[], int n) {
    int time = p[0].arrivalTime;

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d\t|", p[i].processNo);
    }
    printf("\n%d", time);

    for (int i = 0; i < n; i++) {
        time = (time < p[i].arrivalTime) ? p[i].arrivalTime : time;
        time += p[i].burstTime;
        printf("\t%d", time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int wt[n], tat[n];

    printf("Enter Arrival Time, Burst Time, Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].processNo = i + 1;
        printf("P%d: ", p[i].processNo);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
    }

    sortProcesses(p, n);
    calculateWaitingTime(p, n, wt);
    calculateTAT(p, n, wt, tat);

    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].processNo, p[i].arrivalTime,
               p[i].burstTime, p[i].priority, wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);

    printGanttChart(p, n);

    return 0;
}
