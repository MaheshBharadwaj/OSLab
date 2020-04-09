#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

void FIFO(char *, const int);

int main(){

    int n_free_frames = -1;
    int n_reqd_frames = -1;
    char sequence[20] = {0};
    int choice = -1;

    while(1){
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

        switch(choice){
            case 0:
                exit(0);
            case 1:
                printf(" Enter the number of free frames: ");
                scanf("%d", &n_free_frames);
                printf(" Enter the number of required frames: ");
                scanf("%d", &n_reqd_frames);
                getchar();
                printf(" Enter the Reference String: ");
                scanf("%[^\n]", sequence);
                break;
            case 2:
                FIFO(sequence, n_reqd_frames);
                break;
            case 3:
                //optimal();
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

void FIFO(char * refstr, const int n_frames){
    int size = 0;
    int faults = 0;

    List alloc = createEmptyList();


    Node* oldest;

    printf("\n");
    printf(" +-------+-----------------------+--------+\n");
    printf(" | Frame |       In Memory       | Faults |\n");
    printf(" +-------+-----------------------+--------+\n");

    int val = 0;
    int i = 0; 
    while (refstr[i])
    {
        if( isdigit(refstr[i])){
            val = refstr[i] - 48;
            for(int j = i+1; refstr[j] && isdigit(refstr[j]); j++){
                val = (val * 10) + (refstr[j] - 48);
                i = j;
            }

            printf(" |   %-2d  |", val);
            
            Node* isFound = search(alloc, val);
            
            if(!isFound){
                faults++;
                if (size < n_frames){
                    insertLast(alloc, val);
                    size++;

                    //Initialise first frame as oldest
                    if(size == 1)
                        oldest = alloc -> next;
                }
                else{

                    //Swap oldest frame with new frame
                    oldest -> d = val;

                    //Update oldest frame
                    if(oldest -> next)
                        oldest = oldest -> next;
                    else 
                        oldest = alloc -> next;
                }
            }
            display(alloc);
            for(int i = length(alloc) * 3; i <= 22; i++)
                printf(" ");
            printf("|   %-2d   |\n", faults);
        }

        i++;
    }
    printf(" +-------+-----------------------+--------+\n");
}