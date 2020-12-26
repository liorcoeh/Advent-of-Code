#ifndef NUM_STACK_H
#define NUM_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NUM_STACK NStack;

NStack* NStackCreate();
void NStackDestroy(NStack* stack);

int NStackPush(NStack* stack, size_t value);
int NStackPop(NStack* stack);
size_t NStackPeek(NStack* stack);

int NStackIsFull(NStack* stack);
int NStackIsEmpty(NStack* stack);
int NStackSize(NStack* stack);

#endif /* NUM_STACK_H */