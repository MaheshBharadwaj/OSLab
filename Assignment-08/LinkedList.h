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
    initialise(&(head->d));
    head->next = NULL;
    return head;
}

