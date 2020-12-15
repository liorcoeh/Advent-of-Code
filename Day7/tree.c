
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct TREE_NODE
{
    Key key;
    int data;
    int children_bags_amount;
    Node* left;
    Node* mid_left;
    Node* mid_right;
    Node* right;
};

Node* TreeCreate(Key key)
{
    Node* new_tree = (Node*)malloc(sizeof(Node));
    if (!new_tree)
    {
        return (NULL);
    }

    new_tree->key = key;
    new_tree->data = 1;
    new_tree->children_bags_amount = 0;

    new_tree->left = NULL;
    new_tree->mid_left = NULL;
    new_tree->mid_right = NULL;
    new_tree->right = NULL;

    return (new_tree);
}

void TreeDestroy(Node *root)
{
    if (NULL == root)
    {
        return;
    }

    TreeDestroy(root->left);
    TreeDestroy(root->mid_left);
    TreeDestroy(root->mid_right);
    TreeDestroy(root->right);
    
    free(root);
    root = NULL;
}

Node* CreateNewNode(Key key, int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return (NULL);
    }

    new_node->key = key;
    new_node->data = data;
    new_node->children_bags_amount = 0;

    new_node->left = NULL;
    new_node->mid_left = NULL;
    new_node->mid_right = NULL;
    new_node->right = NULL;

    return (new_node);
}

Node* TreeFind(Node* root, Key key)
{
    Node* node = NULL;

    if (NULL == root)
    {
        return (root);
    }

    node = TreeFind(root->left, key);
    if (NULL != node)
    {
        return (node);
    }
    if (key == root->key)
    {
        return (root);
    }

    node = TreeFind(root->mid_left, key);
    if (NULL != node)
    {
        return (node);
    }
    if (key == root->key)
    {
        return (root);
    }

    node = TreeFind(root->mid_right, key);
    if (NULL != node)
    {
        return (node);
    }
    if (key == root->key)
    {
        return (root);
    }

    node = TreeFind(root->right, key);
    if (NULL != node)
    {
        return (node);
    }
    if (key == root->key)
    {
        return (root);
    }

    return (node);
}

int GetLeftData(Node* node)
{
    if (NULL == node->left)
    {
        return (-1);
    }
    return (node->left->data);
}

int TreeInsert(Node* root, Key new_key, int new_data, Key where_key, int direction)
{
    Node* new_node = CreateNewNode(new_key, new_data);
    Node* node = TreeFind(root, where_key);

    if (NULL == node)
    {
        printf("Couldn't find %d in the tree\n", where_key);
        return (1); /* Failure */
    }

    if (0 == direction)
    {
        if (NULL == node->left)
        {
            node->left = new_node;
        }
        else if (node->left->key != new_key)
        {
            printf("%d\n", node->data);
            printf("There is a problem\n");
            return (1); /* Failure */
        }
    }
    else if (1 == direction)
    {
        if (NULL == node->mid_left)
        {
            node->mid_left = new_node;
        }
        else if (node->mid_left->key != new_key)
        {
            printf("There is a problem\n");
            return (1); /* Failure */
        }

    }
    else if (2 == direction)
    {
        if (NULL == node->mid_right)
        {
            node->mid_right = new_node;
        }
        else if (node->mid_right->key != new_key)
        {
            printf("There is a problem\n");
            return (1); /* Failure */
        }
    }
    else
    {
        if (NULL == node->right)
        {
            node->right = new_node;
        }
        else if (node->right->key != new_key)
        {
            printf("There is a problem\n");
            return (1); /* Failure */
        }
    }

    return (0); /* Success */
}

void PrintTree(Node* root)
{
    if (NULL == root)
    {
        printf("NULL\n");
        return;
    }

    printf("The key is: %d || The data is: %d || Children bags amount is: %d\n", root->key, root->data, root->children_bags_amount);
    PrintTree(root->left);
    PrintTree(root->mid_left);
    PrintTree(root->mid_right);
    PrintTree(root->right);
}

void UpdateBagsAmount(Node* root)
{
    root->children_bags_amount = 0;

    if (NULL == root)
    {
        return;
    }

    if (NULL != root->left)
    {
        UpdateBagsAmount(root->left);
        root->children_bags_amount += (root->left->children_bags_amount + root->left->data);
    }

    if (NULL != root->mid_left)
    {
        UpdateBagsAmount(root->mid_left);
        root->children_bags_amount += (root->mid_left->children_bags_amount + root->mid_left->data);
    }

    if (NULL != root->mid_right)
    {
        UpdateBagsAmount(root->mid_right);
        root->children_bags_amount += (root->mid_right->children_bags_amount + root->mid_right->data);
    }

    if (NULL != root->right)
    {
        UpdateBagsAmount(root->right);
        root->children_bags_amount += (root->right->children_bags_amount + root->right->data);
    }

    root->children_bags_amount *= root->data;
}

int GetKey(Node* node)
{
    return (node->key);
}

int GetData(Node* node)
{
    return (node->data);
}

int GetAmountOfBags(Node* node)
{
    return (node->children_bags_amount);
}