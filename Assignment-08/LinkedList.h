typedef Partition Data;

typedef struct Node
{
    Data d;
    struct Node *next;
} Node;

typedef Node *List;

List createEmptyList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->d.start = head->d.end = head->d.size = 0;
    head->d.state = HOLE;
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
        if (tmp->next->d.start > d.end)
            break;
        tmp = tmp->next;
    }
    new->next = tmp->next;
    tmp->next = new;
}

void display(List head)
{
    Node *tmp = head->next;
    while (tmp != NULL)
    {
        printf(" Start: %-3d  End: %-3d  State: %s\n", tmp->d.start, tmp->d.end, printState(tmp->d));
        tmp = tmp->next;
    }
}