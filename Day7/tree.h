#ifndef TREE_H
#define TREE_H

typedef struct TREE_NODE Node;

typedef enum KEY
{
    shiny_gold,
    mirrored_crimson,
    mirrored_tan,
    drab_green,
    shiny_silver,
    dark_black,
    clear_green,
    bright_cyan,
    faded_bronze,
    vibrant_gray,
    faded_gold,
    clear_lavender,
    striped_tan,
    dim_teal,
    mirrored_gray,
    dotted_cyan,
    mirrored_red,
    dull_silver,
    dull_brown,
    vibrant_turquoise,
    dim_gold,
    posh_lavender
} Key;

Node* TreeCreate(Key key);
void TreeDestroy(Node *root);

Node* CreateNewNode(Key key, int data);

Node* TreeFind(Node* root, Key key);

int TreeInsert(Node* root, Key new_key, int new_data, Key where_key, int direction);

void PrintTree(Node* root);

void UpdateBagsAmount(Node* root);

int GetKey(Node* node);
int GetData(Node* node);
int GetAmountOfBags(Node* node);

int GetLeftData(Node* node);

#endif /* TREE_H */