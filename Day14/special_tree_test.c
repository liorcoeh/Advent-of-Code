
#include "special_tree.h"

int main()
{
    int i = 0;
    int j = 0;
    Tree* tree = TreeCreate();

    int binary_arrs[16][10] = {0};
    int index = 0;

    printf("here");
    for (i = 0; i < 4; ++i)
    {
        TreeInsert(tree);
    }

    GetLevelBinary(tree, binary_arrs, &index, 4);

    PrintTree(tree);

    for (i = 0; i < 16; ++i)
    {
        for (j = 0; j < 10; ++j)
        {
            printf("%d", binary_arrs[i][j]);
        }
        printf("\n\n");
    }

    TreeDestroy(tree);

    return (0);
}