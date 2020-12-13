
#include <string.h>
#include <stdlib.h>

#include "list.h"

struct LinkedListNode
{
    char buff[4];
    char content[10];
    struct LinkedListNode* next;
};

struct LinkedList
{
    int size;
    Node* next;
};

static void ListRecuDestroy(Node* node);
static void PrintRecuList(Node* node);

static Node* ListRecuFindBuffer(Node* node, char buffer[]);

List* ListCreate()
{
    List* new_list = (List*)malloc(sizeof(List));

    if (!new_list)
    {
        return (NULL);
    }

    new_list->size = 0;
    new_list->next = NULL;

    return (new_list);
}

void ListDestroy(List* list)
{
    ListRecuDestroy(list->next);

    free(list);
    list = NULL;
}

static void ListRecuDestroy(Node* node)
{
    if (NULL == node)
    {
        return;
    }

    ListRecuDestroy(node->next);

    free(node);
    node = NULL;
}

Node* CreateNewNode(char buffer[], char content[])
{
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (!new_node)
    {
        return (NULL);
    }

    strcpy(new_node->buff, buffer);
    strcpy(new_node->content, content);
    new_node->next = NULL;
}

char* ListGetFirst(List* list)
{
    if (ListIsEmpty(list))
    {
        return (NULL);
    }

    return (list->next->buff);
}

int ListPushBefore(List* list, char buffer[], char content[])
{
    Node* new_node = CreateNewNode(buffer, content);
    if (!new_node)
    {
        return (1); /* Failure */
    }

    new_node->next = list->next;
    list->next = new_node;
    ++(list->size);
    
    return (0); /* Success */
}

int ListPushAfter(List* list, char buffer[], char content[])
{
    Node* new_node = CreateNewNode(buffer, content);
    if (!new_node)
    {
        return (1); /* Failure */
    }

    if (ListIsEmpty(list))
    {
        ListPushBefore(list, buffer, content);
    }
    else
    {
        new_node->next = list->next->next;
        list->next->next = new_node;
    }
    
    ++(list->size);

    return (0); /* Success */
}

int ListSize(List* list)
{
    return (list->size);
}

int ListIsEmpty(List* list)
{
    if (NULL == list->next)
    {
        return (1); /* True */
    }

    return (0); /* False */
}

Node* ListGetNext(List* list)
{
    return (list->next);
}

Node* GetNext(Node* node)
{
    return (node->next);
}

char* GetKey(Node* node)
{
    return (node->buff);
}

char* GetData(Node* node)
{
    return (node->content);
}

void PrintList(List* list)
{
    PrintRecuList(list->next);
}

static void PrintRecuList(Node* node)
{
    if (NULL == node)
    {
        printf("NULL\n");
        return;
    }

    printf("%s:%s -> ", node->buff, node->content);

    PrintRecuList(node->next);
}