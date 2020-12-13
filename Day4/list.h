#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct LinkedList List;
typedef struct LinkedListNode Node;

List* ListCreate();

void ListDestroy(List* list);

Node* CreateNewNode(char buffer[], char content[]);

int ListPushBefore(List* list, char buffer[], char content[]);

int ListPushAfter(List* list, char buffer[], char content[]);

char* ListGetFirst(List* list);

int ListSize(List* list);

int ListIsEmpty(List* list);

Node* ListGetNext(List* list);

Node* GetNext(Node* node);

char* GetKey(Node* node);

char* GetData(Node* node);

void PrintList(List* list);

#endif /* LIST_H */