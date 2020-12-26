#ifndef DAY_18_H
#define DAY_18_H

#include <string.h>

#include "num_stack.h"
#include "char_stack.h"

#define ARRAY_SIZE (372)
#define LENGTH (185)

size_t PartOneFunction(char arr[ARRAY_SIZE][LENGTH]);
size_t PartTwoFunction(char arr[ARRAY_SIZE][LENGTH]);

void GettingInfo(char* file_name, char arr[ARRAY_SIZE][LENGTH]);
void PrintInfo(char arr[ARRAY_SIZE][LENGTH]);

size_t ExpressionValuePartOne(char *str);
size_t ExpressionValuePartTwo(char *str);

#endif /* DAY_18_H */