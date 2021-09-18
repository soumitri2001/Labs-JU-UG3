#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

typedef struct Node Node;

int isEmpty(Node *head)
{
    return head == NULL;
}

int getLength(Node *head)
{
    if (isEmpty(head))
        return 0;
    Node *temp = head;
    int len = 0;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

Node *insert(Node *head, int value)
{
    Node *newnode = (Node *)malloc(sizeof(struct Node));
    newnode->value = value;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
        return head;
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    return head;
}

Node *deleteAt(Node *head, int index)
{
    int len = getLength(head);
    if (index >= len) // 0-based indexing
        return head;

    Node *temp = head;

    if (index == 0)
    {
        head = head->next;
        return head;
    }
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    Node *temp1 = temp->next;
    temp->next = temp1->next;
    free(temp1);
    return head;
}

int lookupValue(Node *head, int search)
{
    if (head == NULL)
        return -1;
    int index = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->value == search)
            return index;
        index++;
        temp = temp->next;
    }
    return -1;
}

void printList(Node *head)
{
    Node *itr = head;
    while (itr != NULL)
    {
        printf("%d ", itr->value);
        itr = itr->next;
    }
    printf("\n");
}

int main()
{
    int num;
    printf("enter number of nodes: ");
    scanf("%d\n", &num);
    Node *head = NULL;
    head = insert(head, 20);
    printList(head);
    head = insert(head, 12);
    printList(head);
    head = insert(head, 31);
    printList(head);
    head = insert(head, 4);
    printList(head);
    head = insert(head, 7);
    printList(head);
    printf("%d\n", getLength(head));
    head = deleteAt(head, 2);
    printf("%d\n", getLength(head));
    printList(head);
    head = insert(head, 43);
    head = insert(head, 11);
    printList(head);
    printf("%d\n", getLength(head));
    printf("%d\n", lookupValue(head, 12));
    printf("%d\n", lookupValue(head, 69));

    return 0;
}