#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

int *const convert(const char *const, int *);

void FIFO(const int *const, const int, const int);
void optimal(const int *const, const int, const int);

int main()
{

    int n_free_frames = -1;
    int n_reqd_frames = -1;
    char buffer[20] = {0};
    int *sequence = NULL;
    int choice = -1;
    int len = 0;

    while (1)
    {
        printf("\t\t\t\tPAGE REPLACEMENT TECHNIQUES\n");
        printf(" 1 - Read Input\n");
        printf(" 2 - FIFO\n");
        printf(" 3 - Optimal\n");
        printf(" 4 - LRU\n");
        printf(" 5 - LFU\n");
        printf(" 0 - Exit\n");
        printf(" -------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            printf(" Enter the number of free frames: ");
            scanf("%d", &n_free_frames);
            printf(" Enter the number of required frames: ");
            scanf("%d", &n_reqd_frames);
            getchar();
            printf(" Enter the Reference String: ");
            scanf("%[^\n]", buffer);
            sequence = convert(buffer, &len);
            break;
        case 2:
            FIFO(sequence, len, n_reqd_frames);
            break;
        case 3:
            optimal(sequence, len, n_reqd_frames);
            break;
        case 4:
            //LRU();
            break;
        case 5:
            //LFU();
            break;
        default:
            printf(" Invalid Input!\n");
        }
        printf("\n");
    }
}

int *const convert(const char *const refstr, int *size)
{
    static int arr[30];
    int i = 0, val = 0;

    while (refstr[i])
    {
        if (isdigit(refstr[i]))
        {
            val = refstr[i] - 48;
            for (int j = i + 1; refstr[j] && isdigit(refstr[j]); j++)
            {
                val = (val * 10) + (refstr[j] - 48);
                i = j;
            }

            arr[*size] = val;
            (*size)++;
        }
        i++;
    }
    return arr;
}

void FIFO(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;

    List alloc = createEmptyList();

    Node *oldest;

    printf("\n");
    printf(" +-------+-----------------------+--------+\n");
    printf(" | Frame |       In Memory       | Faults |\n");
    printf(" +-------+-----------------------+--------+\n");

    for (int i = 0; i < len; i++)
    {
        printf(" |   %-2d  |", seq[i]);

        Node *isFound = search(alloc, seq[i]);

        if (!isFound)
        {
            faults++;
            if (size < n_frames)
            {
                insertLast(alloc, seq[i]);
                size++;

                //Initialise first frame as oldest
                if (size == 1)
                    oldest = alloc->next;
            }
            else
            {

                //Swap oldest frame with new frame
                oldest->d = seq[i];

                //Update oldest frame
                if (oldest->next)
                    oldest = oldest->next;
                else
                    oldest = alloc->next;
            }
        }
        display(alloc);
        for (int i = length(alloc) * 3; i <= 22; i++)
            printf(" ");
        printf("|   %-2d   |\n", faults);
    }
    printf(" +-------+-----------------------+--------+\n");
}

void optimal(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;
    int distance;

    List alloc = createEmptyList();

    Node *farthest = NULL, *tmp;

    printf("\n");
    printf(" +-------+-----------------------+--------+\n");
    printf(" | Frame |       In Memory       | Faults |\n");
    printf(" +-------+-----------------------+--------+\n");

    int val = 0;
    int i = 0;
    for (int i = 0; i < len; i++)
    {
        printf(" |   %-2d  |", seq[i]);

        Node *isFound = search(alloc, seq[i]);

        if (!isFound)
        {
            faults++;
            if (size < n_frames)
            {
                insertLast(alloc, seq[i]);
                size++;
            }
            else
            {
                tmp = alloc->next;
                distance = 0;

                //Find the frame which is used the farthest away and swap
                while (tmp)
                {
                    for (int j = i + 1; j < len; j++)
                    {
                        if (seq[j] == tmp->d)
                            if (j - i > distance)
                            {
                                distance = (j - i);
                                farthest = tmp;
                            }
                    }
                    tmp = tmp->next;
                }

                farthest->d = seq[i];
            }
        }
        display(alloc);
        for (int i = length(alloc) * 3; i <= 22; i++)
            printf(" ");
        printf("|   %-2d   |\n", faults);
    }
    printf(" +-------+-----------------------+--------+\n");
}

void LRU(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;
    int distance;

    List alloc = createEmptyList();

    Node *least_recent = NULL, *tmp;

    printf("\n");
    printf(" +-------+-----------------------+--------+\n");
    printf(" | Frame |       In Memory       | Faults |\n");
    printf(" +-------+-----------------------+--------+\n");

    int val = 0;
    int i = 0;
    for (int i = 0; i < len; i++)
    {
        printf(" |   %-2d  |", seq[i]);

        Node *isFound = search(alloc, seq[i]);

        if (!isFound)
        {
            faults++;
            if (size < n_frames)
            {
                insertLast(alloc, seq[i]);
                size++;
            }
            else
            {
                tmp = alloc->next;
                distance = 0;

                //Find the frame which is used the least recently and swap
                while (tmp)
                {
                    for (int j = i - 1; j >= 0; j--)
                    {
                        if (seq[j] == tmp->d)
                            if (i - j > distance)
                            {
                                distance = (i - j);
                                least_recent = tmp;
                            }
                    }
                    tmp = tmp->next;
                }
                least_recent->d = seq[i];
            }
            display(alloc);
            for (int i = length(alloc) * 3; i <= 22; i++)
                printf(" ");
            printf("|   %-2d   |\n", faults);
        }
        printf(" +-------+-----------------------+--------+\n");
    }
}