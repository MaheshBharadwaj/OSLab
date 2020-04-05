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

void initialise(Partition *const p)
{
    p->start = p->end = p->size = p->state = -1;
}

#include "LinkedList.h"