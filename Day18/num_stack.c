
#include "num_stack.h"

#define CAPACITY (50)

struct NUM_STACK
{
    int top;
    size_t* container;
};

NStack* NStackCreate()
{
    NStack* new_n_stack = (NStack*)malloc(sizeof(NStack));
    if (!new_n_stack)
    {
        return (NULL);
    }

    new_n_stack->top = 0;
    new_n_stack->container = (size_t*)malloc(sizeof(size_t) * CAPACITY);
    if (!new_n_stack->container)
    {
        free(new_n_stack);
        new_n_stack = NULL;

        return (NULL);
    }

    return (new_n_stack);
}

void NStackDestroy(NStack* stack)
{
    free(stack->container);
    stack->container = NULL;

    free(stack);
    stack = NULL;
}

int NStackPush(NStack* stack, size_t value)
{
    if (NStackIsFull(stack))
    {
        printf("NStack is FULL\n");
        return (1); /* Failure */
    }
    stack->container[stack->top] = value;
    ++stack->top;
    
    return (0); /* Success */
}

int NStackPop(NStack* stack)
{
    if (NStackIsEmpty(stack))
    {
        printf("NStack is EMPTY\n");
        return (1); /* Failure */
    }

    --stack->top;

    return (0); /* Success */
}

size_t NStackPeek(NStack* stack)
{
    if (NStackIsEmpty(stack))
    {
        printf("NStack is EMPTY\n");
        return (1); /* Failure */
    }

    return (stack->container[stack->top - 1]);
}

int NStackIsFull(NStack* stack)
{
    if (CAPACITY == stack->top)
    {
        return (1); /* True */
    }

    return (0); /* False */
}

int NStackIsEmpty(NStack* stack)
{
    if (0 == stack->top)
    {
        return (1); /* True */
    }

    return (0); /* False */
}

int NStackSize(NStack* stack)
{
    return (stack->top);
}