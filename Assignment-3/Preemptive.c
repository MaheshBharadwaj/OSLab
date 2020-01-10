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
        p[i].pid = i + 1;
        p[i].rt = -1;
        p[i].rem_t = p[i].bt;
        p[i].st = p[i].et = -1;
        p[i].wt = p[i].tat = -1;
    }

    return p;
}

int main(void)
{
    int size;
    int completed = 0;
    int last_process = 1;
    int index = 0;

    float tot_tat = 0;
    float tot_wt = 0;

    Process tmp;

    printf("Enter the number of processes: ");
    scanf("%d", &size);

    Process *p = getProcesses(size);

    PQueue processQueue = createPQueue(size);
    int time = 0;
    enqueue(processQueue, p[0]);

    printf("\n");

    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  | RT   |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
           p[index].pid, p[index].at, p[index].bt, p[index].st, p[index].et, p[index].wt, p[index].tat, p[index].rt);

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
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");;
}
