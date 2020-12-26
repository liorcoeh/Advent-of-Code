
#include "num_stack.h"
#include "char_stack.h"

int main()
{
    int i = 0;
    char c[5] = {'L', 'I', 'O', 'R', 'C'};
    NStack* n_stack = NStackCreate();
    CStack* c_stack = CStackCreate();

    for (i = 0; i < 5; ++i)
    {
        NStackPush(n_stack, (i + 1) * 3);
        printf("%d\n", NStackPeek(n_stack));
        printf("Size is: %d\n", NStackSize(n_stack));
    }

    for (i = 0; i < 7; ++i)
    {
        NStackPop(n_stack);
        printf("%d\n", NStackPeek(n_stack));
        printf("Size is: %d\n", NStackSize(n_stack));
    }

    for (i = 0; i < 5; ++i)
    {
        CStackPush(c_stack, c[i]);
        printf("%c\n", CStackPeek(c_stack));
        printf("Size is: %d\n", CStackSize(c_stack));
    }

    for (i = 0; i < 6; ++i)
    {
        CStackPop(c_stack);
        printf("%c\n", CStackPeek(c_stack));
        printf("Size is: %d\n", CStackSize(c_stack));
    }

    NStackDestroy(n_stack);
    CStackDestroy(c_stack);

    return (0);
}