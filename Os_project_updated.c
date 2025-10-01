#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, arrival, burst, priority;
    int waiting, turnaround, finish, remaining;
};

void ganttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
            printf(" P%d |", p[i].pid);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
            printf("   %d", p[i].finish);
    }
    printf("\n");
}

void calculateAvg(struct Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
}
void fcfs(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].finish = time;
    }
    ganttChart(p, n);
    calculateAvg(p, n);
}

void sjf(struct Process p[], int n) {
    int time = 0, completed = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed != n) {
        int idx = -1, min = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && isCompleted[i] == 0 && p[i].burst < min) {
                min = p[i].burst;
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].waiting = time - p[idx].arrival;
            time += p[idx].burst;
            p[idx].finish = time;
            isCompleted[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }
    ganttChart(p, n);
    calculateAvg(p, n);
}

void roundRobin(struct Process p[], int n, int quantum) {
    int time = 0, remain = n;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (remain != 0) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].arrival <= time) {
                if (p[i].remaining <= quantum) {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].finish = time;
                    p[i].turnaround = p[i].finish - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    remain--;
                } else {
                    time += quantum;
                    p[i].remaining -= quantum;
                }
            }
        }
    }
    ganttChart(p, n);
    calculateAvg(p, n);
}

void priorityScheduling(struct Process p[], int n) {
    int time = 0, completed = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed != n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && isCompleted[i] == 0 && p[i].priority < highest) {
                highest = p[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].waiting = time - p[idx].arrival;
            time += p[idx].burst;
            p[idx].finish = time;
            isCompleted[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }
    ganttChart(p, n);
    calculateAvg(p, n);
}

int main() {
    int n, choice, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter arrival time, burst time of P%d:\n", i+1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    do {
        printf("\n1. FCFS\n2. SJF\n3. Round Robin\n4. Priority Scheduling\n5. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
                break;
            case 3:
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                roundRobin(p, n, quantum);
                break;
            case 4:
                for (int i = 0; i < n; i++) {
                     p[i].pid = i + 1;
                     printf("Enter Priority P%d :\n", i + 1);
                     scanf("%d", &p[i].priority );
               }
                priorityScheduling(p, n);
                break;
        }

    } while (choice != 5);

    return 0;
}
