#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int pid;
    float at, bt, st, et, wt, tat, rt, rem_t;
} Process;

#include "MinHeap.h"

int getIndex(Process *const arr, const int size, const Process p)
{
    for (int i = 0; i < size; i++)
        if (arr[i].pid == p.pid)
            return i;

    return -1;
}

Process *getProcesses(const int size)
{
    static Process p[100];

    for (int i = 0; i < size; i++)
    {
        printf("Enter the Arrival Time and Burst Time: ");
        scanf("%f %f", &p[i].at, &p[i].bt);
        getchar();
        p[i].pid = i + 1;
        p[i].rt = -1;
        p[i].rem_t = p[i].bt;
        p[i].st = p[i].et = -1;
        p[i].wt = p[i].tat = -1;
    }

    return p;
}

void FCFS(Process *const arr, const int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j].at < arr[i].at) //Arrived Earlier
            {
                Process tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
}

void SJF(Process *const arr, const int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j].bt < arr[i].bt) //Lower Burst Time
            {
                Process tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
}

void putTable(Process *const p, const int size)
{
    if (!size)
        return;

    float tot_wt = 0, tot_tat = 0;
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  | RT   |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");

    p[0].wt = 0;
    p[0].st = 0;
    p[0].et = p[0].bt;
    p[0].rt = p[0].st - p[0].at;
    p[0].tat = p[0].et - p[0].at;
    tot_tat = p[0].tat;
    tot_wt = p[0].bt;
    printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
           p[0].pid, p[0].at, p[0].bt, p[0].st, p[0].et, p[0].wt, p[0].tat, p[0].rt);

    for (int i = 1; i < size; i++)
    {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].st = p[i-1].et;
        p[i].et = p[i].st + p[i].bt;
        p[i].rt = p[i].st - p[i].at;
        tot_wt += p[i].wt;
        p[i].tat = p[i].et - p[i].at;
        tot_tat += p[i].tat;

        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].et, p[i].wt, p[i].tat, p[i].rt);
    }
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |      |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |      |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
}

void SRTF(Process *const p, const int size)
{
    int completed = 0;
    int last_process = 1;
    int index = 0;
    int prev_id = -1;
    float tot_tat = 0;
    float tot_wt = 0;

    Process tmp;
    PQueue processQueue = createPQueue(size);
    int time = 0;
    enqueue(processQueue, p[0]);

    printf("\n");

    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  | RT   |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
   // printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
     //      p[index].pid, p[index].at, p[index].bt, p[index].st, p[index].et, p[index].wt, p[index].tat, p[index].rt);

    while (completed < size)
    {
        //time++;
        if (p[last_process].at == time)
        {
            enqueue(processQueue, p[last_process]);
            last_process++;
        }

        tmp = dequeue(processQueue);

        index = getIndex(p, size, tmp);

        if (p[index].st == -1)
        { //Fresh Process
            p[index].st = time;
            p[index].rt = p[index].st - p[index].at;
        }

        tmp.rem_t--;
        p[index].rem_t--;

        if (tmp.rem_t == 0)
        {
            p[index].et = time + 1;
            p[index].tat = p[index].et - p[index].at;
            tot_tat += p[index].tat;
            p[index].wt = p[index].tat - p[index].bt;
            tot_wt += p[index].wt;
            completed++;
        }
        else
            enqueue(processQueue, tmp);
        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
               p[index].pid, p[index].at, p[index].bt, p[index].st, p[index].et, p[index].wt, p[index].tat, p[index].rt);
        time++;
    }

    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |      |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |      |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
}

int main(void)
{
    int size;
    int choice = 5;
    do
    {
        system("clear");
        printf("1 - FCFS\n");
        printf("2 - SJF\n");
        printf("3 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter the number of processes: ");
            scanf("%d", &size);

            Process *p = getProcesses(size);
            FCFS(p, size);
            putTable(p, size);
            printf("Press ENTER to continue...");
            getchar();
        }
        break;
        case 2:
        {
            printf("\n1 - Non Preemptive SJF\n");
            printf("2 - Preemptive SJF[SRTF]\n");
            printf("3 - back\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
            {
                printf("Enter the number of processes: ");
                scanf("%d", &size);

                Process *p = getProcesses(size);

                SJF(p, size);
                putTable(p, size);
                printf("Press ENTER to continue...");
                getchar();
            }
            break;
            case 2:
            {
                printf("Enter the number of processes: ");
                scanf("%d", &size);

                Process *p = getProcesses(size);

                SRTF(p, size);
                printf("Press ENTER to continue...");
                getchar();
            }
            case 3:
                break;
            default:
                printf("\nInvalid Input!\n");
            }
        }
        break;
        case 3:
            return 0;
        default:
            printf("Invalid Input\n");
        }
    } while (choice != 3);
}
