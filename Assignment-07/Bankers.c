#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct Resource
{
    char name;
    unsigned short int qty;
} Resource;

typedef struct Process
{
    int pid;
    Resource max[MAX];
    Resource alloc[MAX];
    Resource need[MAX];
    //Resource temp[MAX];
} Process;

void ReadData(int *const n_process, Process *const arr, int *const n_resources, Resource *const avail);
void PrintData(const int n_process, const Process *const arr, const int n_resources, const Resource *const avail);

int main()
{

    int n_process = 0,
        n_resources = 0,
        choice = -1;
    ;

    Process p[MAX];
    Resource avail[MAX];

    while (1)
    {
        printf("\t\t\tBANKERS ALGORITHM\n");
        printf(" 1 - Read Data\n");
        printf(" 2 - Print Data\n");
        printf(" 3 - Safety Sequence\n");
        printf(" 4 - exit\n");
        printf(" ---------------------------\n");
        printf(" Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            ReadData(&n_process, p, &n_resources, avail);
            break;
        case 2:
            PrintData(n_process, p, n_resources, avail);
            break;
        // case 3:
        //     SafetySequence(n_process, p, n_resource, avail);
        //     break;
        case 4:
            exit(0);

        default:
            printf(" Invalid Option!\n");
            break;
        }
        printf("\n\n");
    }
}

void ReadData(int *const n_process, Process *const arr, int *const n_resources, Resource *const avail)
{
    printf(" Enter the Number of Processes: ");
    scanf("%d", n_process);
    printf(" Enter the Number of Resources: ");
    scanf("%d", n_resources);
    getchar();

    for (int i = 0; i < *n_resources; i++)
    {
        printf(" Enter the name of resource & available: ");
        scanf("%c %d", &avail[i].name, &avail[i].qty);
        getchar();
    }

    for (int i = 0; i < *n_process; i++)
    {
        printf("Enter Process ID, Max Required, Allocated");
        scanf("%d", &arr[i].pid);

        for (int j = 0; j < *n_resources; j++)
            scanf("%d", &arr[i].max[j].qty);

        for (int j = 0; j < *n_resources; j++)
        {
            scanf("%d", &arr[i].alloc[j].qty);
            arr[i].need[j].qty = arr[i].max[j].qty - arr[i].alloc[j].qty;
        }
    }
}

void PrintData(const int n_process, const Process *const arr, const int n_resources, const Resource *const avail)
{

    printf("\n");
    printf(" +-----+----------------+---------------+----------------+---------------+\n");
    printf(" | PID |   Allocated    |    Needed     |    Maximum     |   Available   |\n");
    printf(" |     |  ");

    for (int i = 0; i < n_resources; i++)
        printf("%c  ", avail[i].name);

    for (int i = n_resources * 3; i < strlen(" Allocated  "); i++)
        printf(" ");

    printf("  |  ");

    for (int i = 0; i < n_resources; i++)
        printf("%c  ", avail[i].name);

    for (int i = n_resources * 3; i < strlen("  Needed   "); i++)
        printf(" ");

    printf("  |  ");

    for (int i = 0; i < n_resources; i++)
        printf("%c  ", avail[i].name);

    for (int i = n_resources * 3; i < strlen("  Maximum   "); i++)
        printf(" ");

    printf("  |  ");

    for (int i = 0; i < n_resources; i++)
        printf("%c  ", avail[i].name);

    for (int i = n_resources * 3; i < strlen(" Available "); i++)
        printf(" ");

    printf("  |\n");
    printf(" +-----+----------------+---------------+----------------+---------------+\n");

    for (int k = 0; k < n_process; k++)
    {
        printf(" | P%2d |  ", arr[k].pid);
        for (int i = 0; i < n_resources; i++)
            printf("%2d ", arr[k].alloc[i].qty);

        for (int i = n_resources * 3; i < strlen(" Allocated  "); i++)
            printf(" ");

        printf("  |  ");

        for (int i = 0; i < n_resources; i++)
            printf("%2d ", arr[k].need[i].qty);

        for (int i = n_resources * 3; i < strlen("  Needed   "); i++)
            printf(" ");

        printf("  |  ");

        for (int i = 0; i < n_resources; i++)
            printf("%2d ", arr[k].max[i].qty);

        for (int i = n_resources * 3; i < strlen("  Maximum   "); i++)
            printf(" ");

        printf("  |  ");

        if (k == 0)
        {
            for (int i = 0; i < n_resources; i++)
                printf("%2d ", avail[i].qty);

            for (int i = n_resources * 3; i < strlen(" Available "); i++)
                printf(" ");
        }
        else
            printf("           ");

        printf("  |\n");
    }
}
