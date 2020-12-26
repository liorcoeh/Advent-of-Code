#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CHAR_STACK CStack;

CStack* CStackCreate();
void CStackDestroy(CStack* stack);

int CStackPush(CStack* stack, char c);
int CStackPop(CStack* stack);
char CStackPeek(CStack* stack);

int CStackIsFull(CStack* stack);
int CStackIsEmpty(CStack* stack);
int CStackSize(CStack* stack);

#endif /* CHAR_STACK_H */