#include <stdio.h>

typedef struct {
    int PID,arrival,burst,completion,wait,turnaround,rburst;
} process;

int main() {
    int n, i, timeQuantum, count = 0, completed = 0;
    float totalW = 0, totalT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process pa[n];

    for (i = 0; i < n; i++) {
        printf("Enter Arrival time of Process %d: ", i + 1);
        scanf("%d", &pa[i].arrival);
        printf("Enter Burst time of Process %d: ", i + 1);
        scanf("%d", &pa[i].burst);
        pa[i].PID = i + 1;
        pa[i].rburst = pa[i].burst;
        pa[i].completion = pa[i].wait = pa[i].turnaround = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int queue[100], front = 0, rear = 0; 
    int gantt[100]; 
    int t = 0; 

    for (i = 0; i < n; i++) {
        if (pa[i].arrival == 0) {
            queue[rear++] = i;
        }
    }

    while (completed < n) {
        if (front == rear) {  
            gantt[count++] = -1;
            t++;
            for (i = 0; i < n; i++) {
                if (pa[i].arrival == t) {
                    queue[rear++] = i;
                }
            }
            continue;
        }

        int idx = queue[front++]; //currprocess
        gantt[count++] = pa[idx].PID; 

        if (pa[idx].rburst > timeQuantum) {
            t += timeQuantum;
            pa[idx].rburst -= timeQuantum;
        } else { 
            t += pa[idx].rburst;
            pa[idx].rburst = 0;
            pa[idx].completion = t;
            pa[idx].turnaround = pa[idx].completion - pa[idx].arrival;
            pa[idx].wait = pa[idx].turnaround - pa[idx].burst;
            totalT += pa[idx].turnaround;
            totalW += pa[idx].wait;
            completed++;
        }

        for (i = 0; i < n; i++) {
            if (pa[i].arrival <= t && pa[i].rburst > 0 && i != idx) {
                int exists = 0;
                for (int k = front; k < rear; k++) {  
                    if (queue[k] == i) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) queue[rear++] = i;
            }
        }
        if (pa[idx].rburst > 0) {
            queue[rear++] = idx;
        }
    }

    totalT /= n;
    totalW /= n;

    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWait\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", pa[i].PID, pa[i].arrival, pa[i].burst, pa[i].completion, pa[i].turnaround, pa[i].wait);
    }
    printf("Average Waiting Time: %.2f\n", totalW);
    printf("Average Turnaround Time: %.2f\n", totalT);

    printf("Gantt Chart: ");
    for (i = 0; i < count; i++) {
        if (gantt[i] == -1) {
            printf("Idle || ");
        } else {
            printf("P%d || ", gantt[i]);
        }
    }
    printf("\n");

    return 0;
}