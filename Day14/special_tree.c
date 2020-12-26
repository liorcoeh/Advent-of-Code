
#include "special_tree.h"

struct TREE_NODE
{
    int data;
    int level;
    int binary[10];
    struct TREE_NODE* left;
    struct TREE_NODE* right;
    struct TREE_NODE* parent;
};

static void PrintTreeRecursive(Node *root, int level);

Node* TreeCreate()
{
    int i = 0;
    Node* new_tree = (Node*)malloc(sizeof(Node));
    if (!new_tree)
    {
        return (NULL);
    }

    new_tree->data = -1;
    new_tree->level = 0;
    new_tree->left = NULL;
    new_tree->right = NULL;
    new_tree->parent = NULL;

    for (i = 0; i < 10; ++i)
    {
        new_tree->binary[i] = 0;
    }

    return (new_tree);
}

void TreeDestroy(Tree* tree)
{
    if (NULL == tree)
    {
        return;
    }

    TreeDestroy(tree->left);
    TreeDestroy(tree->right);

    free(tree);
    tree = NULL;
}

Node* CreateNewNode()
{
    int i = 0;
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return (NULL);
    }

    new_node->data = 0;
    new_node->level = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    for (i = 0; i < 10; ++i)
    {
        new_node->binary[i] = 0;
    }

    return (new_node);
}

int TreeInsert(Node* node)
{
    int i = 0;
    Node* left_node = NULL;
    Node* right_node = NULL;

    /* The node is a leaf */
    if (NULL == node->left)
    {
        left_node = CreateNewNode();
        if (!left_node)
        {
            return (1); /* Failure */
        }

        left_node->data = 0;
        left_node->level = node->level + 1;
        left_node->parent = node;
        for (i = 9; i > (9 - node->level); --i)
        {
            left_node->binary[i] = node->binary[i];
        }
        left_node->binary[i] = left_node->data;

        right_node = CreateNewNode();
        if (!right_node)
        {
            free(left_node);
            left_node = NULL;
            return (1); /* Failure */
        }

        right_node->data = 1;
        right_node->level = node->level + 1;
        right_node->parent = node;
        for (i = 9; i > (9 - node->level); --i)
        {
            right_node->binary[i] = node->binary[i];
        }
        right_node->binary[i] = right_node->data;

        node->left = left_node;
        node->right = right_node;

        return (0); /* Success */
    }

    if (1 == TreeInsert(node->left))
    {
        return (1); /* Failure */
    }

    if (1 == TreeInsert(node->right))
    {
        return (1); /* Failure */
    }

    return (0); /* Success */
}

void GetLevelBinary(Tree* tree, size_t binary_arrs[][10], int *index, int level)
{
    int i = 0;
    /* tree is a leaf */
    if (level == tree->level)
    {
        for (i = 0; i < 10; ++i)
        {
            binary_arrs[*index][i] = tree->binary[i];
        }
        ++(*index);
        return;
    }

    GetLevelBinary(tree->left, binary_arrs, index, level);
    GetLevelBinary(tree->right, binary_arrs, index, level);
}

void PrintTree(Tree *tree)
{ 
	PrintTreeRecursive(tree, 0);
	
	printf("\n\n");
} 

static void PrintTreeRecursive(Node *root, int level)
{ 
	int i = 0;
    int j = 0;
	
	if (!root)
	{ 
		return; 
	}

	level += 7; 
  
	PrintTreeRecursive(root->right, level); 
	printf("\n"); 
	
	for (i = 7; i < level; i++) 
	{
		printf(" ");
	} 
	
	printf("%d| ", root->level);
    for (j = 0; j < 10; ++j)
    {
        printf("%d", root->binary[j]);
    }
    printf("\n");
	
	PrintTreeRecursive(root->left, level); 
}