#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int pid;
    float at, st, bt, wt, tat,ft,rt;
} Process;

Process *getProcesses(const int size)
{
    static Process p[100];

    for (int i = 0; i < size; i++)
    {
        printf("Enter the Arrival Time and Burst Time: ");
        scanf("%f %f", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
    }

    return p;
}

void FCFS(Process * const arr, const int size)
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

void SJF(Process * const arr,const int size)
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

void putTable(Process * const p,const int size)
{
    if(!size)
        return;

    float tot_wt = 0,tot_tat = 0;
    printf("+-----+--------------+------------+-----------+------------------+\n");
    printf("| PID | Arrival Time | Burst Time | Wait Time | Turn Around Time |\n");
    printf("+-----+--------------+------------+-----------+------------------+\n");
    p[0].wt = 0;
    p[0].st = 0;
    p[0].et = p[0].bt;
    p[0].rt = p[0].st - p[0].bt;
    p[0].tat = p[0].bt + p[0].wt;
    tot_tat = p[0].tat;
    
    printf("| %3d | %-12f | %-10f | %9f | %-16f |\n",p[0].pid,p[0].at,p[0].bt,p[0].wt,p[0].tat);

    for(int i = 1 ; i < size ; i++){
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        tot_wt += p[i].wt;
        p[i].tat = p[i].wt + p[i].bt;
        tot_tat += p[i].tat;

        printf("| %3d | %-12f | %-10f | %-9f | %-16f |\n",p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].tat);
    }
    printf("+-----+--------------+------------+-----------+------------------+\n");
    printf("|                    | Total      | %-9f | %-16f |\n",tot_wt,tot_tat);
    printf("|                    | Average    | %-9f | %-16f |\n",tot_wt/size,tot_tat/size);
    printf("+--------------------+------------+-----------+------------------+\n\n");   

}


int main(void)
{
    int size;

    printf("Enter the number of processes: ");
    scanf("%d", &size);

    Process *p = getProcesses(size);
    FCFS(p,size);
    putTable(p,size);
    SJF(p,size);
    putTable(p,size);

}