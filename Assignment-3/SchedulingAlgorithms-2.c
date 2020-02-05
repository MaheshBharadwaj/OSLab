#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int pid;
    float at, bt, st, et, wt, tat, rt, rem_t, pri;
} Process;

Process *getProcesses(const int size)
{
    static Process p[100];

    for (int i = 0; i < size; i++)
    {
        printf("Enter the Arrival Time, Burst Time & Priority: ");
        scanf("%f %f %f", &p[i].at, &p[i].bt, &p[i].pri);
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

void RR(Process *const p, const int size)
{
    FCFS(p, size);
    int time = 0;

    float tot_tat = 0;
    float tot_wt = 0;
    int total_time = 0;
    for (int i = 0; i < size; i++)
        total_time += p[i].bt;
    int q = 2;
    int i = 0;
    int completed = 0;

    printf("\nGANTT CHART[EACH CELL IS 1 Second]\n");
    for (int i = 0; i < total_time; i++)
        printf("+---");
    printf("+\n");

    while (completed != size)
    {
        if (p[i].rem_t)
        {
            if(p[i].rem_t == p[i].bt){
                p[i].st = time;
                p[i].rt = p[i].st - p[i].at;
            }
            if (p[i].rem_t > q)
            {
                time = time + q;
                p[i].rem_t -= q;
                for (int j = 0; j < q; j++)
                    printf("| %1d ", p[i].pid);
            }

            else
            {

                for (int j = 0; j < p[i].rem_t; j++)
                    printf("| %1d ", p[i].pid);
                completed++;
                time += p[i].rem_t;
                p[i].et = time;
                p[i].rem_t = 0;
                p[i].tat = p[i].et - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                tot_tat += p[i].tat;
                tot_wt += p[i].wt;
            }
        }

        i = (i + 1) % size;
    }
    printf("|\n");
    for (int i = 0; i < total_time; i++)
        printf("+---");
    printf("+\n\n");

    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  | RT   |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    for (int i = 0; i < size; i++)
        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f | %-4.1f |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].et, p[i].wt, p[i].tat, p[i].rt);
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |      |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |      |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+------+\n\n");
}

int main(void)
{
    int size;
    int choice = 5;
    do
    {
        system("clear");
        printf("1 - Round Robin\n");
        printf("2 - Priority\n");
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
            RR(p, size);
            printf("Press ENTER to continue...");
            getchar();
        }
        break;
        case 2:
        {
            /*
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
                choice = 2;
                break;
            default:
                printf("\nInvalid Input!\n");
            }
            */
        }
        break;
        case 3:
            return 0;
        default:
            printf("Invalid Input\n");
        }
    } while (choice != 3);
}
