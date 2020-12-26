#ifndef SPECIAL_TREE_H
#define SPECIAL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TREE_NODE Node;
typedef Node Tree;

Node* TreeCreate();
void TreeDestroy(Tree* tree);

Node* CreateNewNode();

int TreeInsert(Node* node);

void GetLevelBinary(Tree* tree, size_t binary_arrs[][10], int *index, int level);

void PrintTree(Tree *tree);


#endif /* SPECIAL_TREE_H */