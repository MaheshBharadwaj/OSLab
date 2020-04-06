typedef Partition *Data;

typedef struct Node
{
    Data d;
    struct Node *next;
} Node;

typedef Node *List;

List createEmptyList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->d = NULL;
    head->next = NULL;
    return head;
}

void insert(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->d = d;

    Node *tmp = head;

    while (tmp->next != NULL)
    {
        if (tmp->next->d->start > d->start)
            break;
        tmp = tmp->next;
    }
    new->next = tmp->next;
    tmp->next = new;
}

Data delete (List prev)
{
    Data rVal=NULL;
    if (!prev)
        return rVal;
    if (!prev->next)
        return rVal;

    Node *tmp = prev->next;
    rVal = tmp->d;
    prev->next = prev->next->next;
    free(tmp);

    return rVal;
}

void display(List head)
{
    Node *tmp = head->next;

    if (tmp == NULL)
    {
        printf(" Empty!\n");
        return;
    }

    while (tmp != NULL)
    {
        printf(" Start: %-3d  End: %-3d  Size: %-3d  State: %s\n", tmp->d->start, tmp->d->end,
                tmp->d->size,printState(*(tmp->d)));
        tmp = tmp->next;
    }
}