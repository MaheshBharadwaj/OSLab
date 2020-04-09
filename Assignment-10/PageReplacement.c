#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

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
        pritnf(" 0 - Exit\n");
        printf(" -------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 0:
                exit(0);
            case 1:
                printf(" Enter the Reference String: ");
                scanf("%[^\n]", sequence);
                break;
            case 2:
                //fifo();
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