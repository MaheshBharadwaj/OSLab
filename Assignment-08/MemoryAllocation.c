#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int start;
    unsigned int end;
    unsigned int size;
    int state;
} Partition;

char *const printState(const Partition P)
{
    static char str[5];
    if (P.state < -1)
        exit(1);
    else if (P.state == -1)
        strcpy(str, "Hole");
    else
    {
        str[0] = 'P';
        str[1] = (P.state/10) + 48;
        str[2] = (P.state%10) + 48;
        str[3] = '\0';
    }
    return str;
}

#define HOLE -1
#include "LinkedList.h"

typedef enum Mode
{
    FirstFit,
    BestFit,
    WorstFit
} Mode;

int main()
{

    int choice = -1;
    Mode m;

    while (1)
    {
        printf("\t\t\tMEMORY ALLOCATION TECHNIQUES\n");
        printf(" 1 - First Fit\n");
        printf(" 2 - Best Fit\n");
        printf(" 3 - Worst Fit\n");
        printf(" 0 - Exit\n");
        printf(" ------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &m);

        if (m < 0 || m > 3)
        {
            printf("Invalid Mode!\n");
            continue;
        }

        printf("\n\n");
        printf("\t\t\tOPTIONS\n");
        printf(" 1 - Entry / Allocate\n");
        printf(" 2 - Exit / De-Allocate\n");
        printf(" 3 - Display\n");
        printf(" 4 - Coalescing of Holes\n");
        printf(" 5 - Back\n");
        printf(" ------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5)
        {
            printf(" Invalid Input\n");
            continue;
        }

        if (choice == 5)
            continue;

        switch (choice)
        {
        case 1:
            switch (m)
            {
            case FirstFit:
                //FFAlloc();
                break;
            case BestFit:
                //BFAlloc();
                break;
            case WorstFit:
                //WFAlloc();
            default:
                break;
            }
            break;
        case 2:
            switch (m)
            {
            case FirstFit:
                //FFDealloc();
                break;
            case BestFit:
                //BFDealloc();
                break;
            case WorstFit:
                //WFDealloc();
            default:
                break;
            }
            break;
        case 3:
            //Display();
            break;
        case 4:
            //Coalesce();
        default:
            break;
        }
    }

    Partition tmp;
    tmp.state = -1;
    int n;
    List head = createEmptyList();
    printf(" Enter the number of blocks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf(" Enter the start and end: ");
        scanf("%d %d", &tmp.start, &tmp.end);
        tmp.size = tmp.end - tmp.start;
        insert(head, tmp);
    }

    printf(" Contents of the list:\n");
    display(head);
}