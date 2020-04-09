typedef int Data;

typedef struct Node
{
    Data d;
    struct Node *next;
} Node;

typedef Node *List;

List createEmptyList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->d = 0;
    head->next = NULL;
    return head;
}

void insertLast(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->d = d;

    Node *tmp = head;

    while (tmp->next != NULL)
        tmp = tmp->next;

    new->next = NULL;
    tmp->next = new;
}

void insertFirst(List head, const Data d){
    Node *new = (Node*)malloc(sizeof(Node));
    new -> d = d;
    
    new -> next = head -> next;
    head -> next = new;
}

Data deleteFirst(List head)
{
    Data rVal = -1;
    if (head->next == NULL)
    {
        printf(" Empty List!\n");
        return rVal;
    }

    delete (head);
}

Data deleteLast(List head){
    Data rVal = -1;
    if (head->next == NULL)
    {
        printf(" Empty List!\n");
        return rVal;
    }

    Node *tmp = head;
    while(tmp -> next != NULL)
        tmp = tmp -> next;

    delete(tmp);
}

Data delete (List prev)
{
    Data rVal = -1;
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
}

int size(List head){
    Node * tmp = head -> next;
    if(tmp == NULL)
        return 0;
    
    int count = 0;
    while(tmp){
        tmp = tmp -> next;
        count++;
    }
    return count;
}