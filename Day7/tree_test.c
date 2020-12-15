
#include <stdio.h>

#include "tree.h"

int main()
{
    Node* tree = TreeCreate(shiny_gold);

    TreeInsert(tree, mirrored_crimson, 5, shiny_gold, 0);
    TreeInsert(tree, mirrored_tan, 5, shiny_gold, 1);
    TreeInsert(tree, drab_green, 5, shiny_gold, 2);
    TreeInsert(tree, shiny_silver, 5, shiny_gold, 3);

    TreeInsert(tree, dark_black, 2, mirrored_tan, 0);
    TreeInsert(tree, clear_green, 4, mirrored_tan, 1);
    TreeInsert(tree, bright_cyan, 2, mirrored_tan, 2);
    TreeInsert(tree, faded_bronze, 4, mirrored_tan, 3);

    TreeInsert(tree, vibrant_gray, 3, dark_black, 0);
    TreeInsert(tree, faded_bronze, 1, dark_black, 1);
    TreeInsert(tree, faded_gold, 2, dark_black, 2);

    TreeInsert(tree, clear_lavender, 4, bright_cyan, 0);
    TreeInsert(tree, drab_green, 4, bright_cyan, 1);
    TreeInsert(tree, striped_tan, 1, bright_cyan, 2);

    PrintTree(tree);

    UpdateBagsAmount(tree);
    printf("Total amount is: %d\n\n", GetAmountOfBags(tree));

    printf("The answer is 82,930\n");

    TreeDestroy(tree);

    return (0);
}