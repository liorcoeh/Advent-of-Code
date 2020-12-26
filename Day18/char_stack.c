
#include "char_stack.h"

#define CAPACITY (50)

struct CHAR_STACK
{
    int top;
    char* container;
};

CStack* CStackCreate()
{
    CStack* new_n_stack = (CStack*)malloc(sizeof(CStack));
    if (!new_n_stack)
    {
        return (NULL);
    }

    new_n_stack->top = 0;
    new_n_stack->container = (char*)malloc(sizeof(char) * CAPACITY);
    if (!new_n_stack->container)
    {
        free(new_n_stack);
        new_n_stack = NULL;

        return (NULL);
    }

    return (new_n_stack);
}

void CStackDestroy(CStack* stack)
{
    free(stack->container);
    stack->container = NULL;

    free(stack);
    stack = NULL;
}

int CStackPush(CStack* stack, char c)
{
    if (CStackIsFull(stack))
    {
        printf("CStack is FULL\n");
        return (1); /* Failure */
    }
    stack->container[stack->top] = c;
    ++stack->top;
    
    return (0); /* Success */
}

int CStackPop(CStack* stack)
{
    if (CStackIsEmpty(stack))
    {
        printf("CStack is EMPTY\n");
        return (1); /* Failure */
    }

    --stack->top;

    return (0); /* Success */
}

char CStackPeek(CStack* stack)
{
    if (CStackIsEmpty(stack))
    {
        printf("CStack is EMPTY\n");
        return (-1); /* Failure */
    }

    return (stack->container[stack->top - 1]);
}

int CStackIsFull(CStack* stack)
{
    if (CAPACITY == stack->top)
    {
        return (1); /* True */
    }

    return (0); /* False */
}

int CStackIsEmpty(CStack* stack)
{
    if (0 == stack->top)
    {
        return (1); /* True */
    }

    return (0); /* False */
}

int CStackSize(CStack* stack)
{
    return (stack->top);
}