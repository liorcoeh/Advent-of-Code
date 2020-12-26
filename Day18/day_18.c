
#include "day_18.h"

size_t PartOneFunction(char arr[ARRAY_SIZE][LENGTH])
{
    size_t total_sum = 0;
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        total_sum += ExpressionValuePartOne(arr[i]);
    }

    return (total_sum);
}

size_t PartTwoFunction(char arr[ARRAY_SIZE][LENGTH])
{
    size_t total_sum = 0;
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        total_sum += ExpressionValuePartTwo(arr[i]);
    }

    return (total_sum);
}

void GettingInfo(char* file_name, char arr[ARRAY_SIZE][LENGTH])
{
    int i = 0;
    char c = 0;
    size_t length = 0;

    FILE* fptr;

    if (NULL == (fptr = fopen(file_name, "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (NULL != fgets(arr[i], LENGTH, fptr))
    {
        ++i;
    }

    length = strlen(arr[i - 1]);
    arr[i - 1][length] = '\n';

    fclose(fptr);
}

void PrintInfo(char arr[ARRAY_SIZE][LENGTH])
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d) %s", i + 1, arr[i]);
    }
    printf("\n");
}

size_t ExpressionValuePartOne(char *str)
{
    NStack* n_stack = NStackCreate();
    CStack* c_stack = CStackCreate();

    size_t value = 0;
    int i = 0;

    size_t current = 0;
    size_t temp = 0;
    char c = 0;

    //printf("%s\n", str);

    while (*(str + i))
    {
        if (('0' <= *(str + i)) && ('9' >= *(str + i)))
        {
            current = *(str + i) - '0';
            if (NStackIsEmpty(n_stack) || ('(' == CStackPeek(c_stack)))
            {
                NStackPush(n_stack, current);
            }
            else
            {
                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                if ('+' == CStackPeek(c_stack))
                {
                    temp += current;
                }
                else if ('*' == CStackPeek(c_stack))
                {
                    temp *= current;
                }
                NStackPush(n_stack, temp);
                CStackPop(c_stack);
            }
        }
        else if (('+' == *(str + i)) || ('*' == *(str + i)) || (('(' == *(str + i))))
        {
            c = *(str + i);
            CStackPush(c_stack, c);
        }
        else if (')' == *(str + i))
        {
            CStackPop(c_stack);

            if (!CStackIsEmpty(c_stack) && ('(' != CStackPeek(c_stack)))
            {
                current = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                if ('+' == CStackPeek(c_stack))
                {
                    temp += current;
                    NStackPush(n_stack, temp);
                }
                else if ('*' == CStackPeek(c_stack))
                {
                    temp *= current;
                    NStackPush(n_stack, temp);
                }
                CStackPop(c_stack);
            }
        }
        ++i;
    }
    value = NStackPeek(n_stack);

    NStackDestroy(n_stack);
    CStackDestroy(c_stack);

    return (value);
}

size_t ExpressionValuePartTwo(char *str)
{
    NStack* n_stack = NStackCreate();
    CStack* c_stack = CStackCreate();

    size_t value = 0;
    int i = 0;

    size_t current = 0;
    size_t temp = 0;
    char c = 0;

    // printf("%s", str);

    while (*(str + i))
    {
        if (('0' <= *(str + i)) && ('9' >= *(str + i)))
        {
            current = *(str + i) - '0';
            if (NStackIsEmpty(n_stack) || ('(' == CStackPeek(c_stack)) || '*' == CStackPeek(c_stack))
            {
                NStackPush(n_stack, current);
            }
            else
            {
                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                if ('+' == CStackPeek(c_stack))
                {
                    temp += current;
                }

                NStackPush(n_stack, temp);
                CStackPop(c_stack);
            }
        }
        else if ('*' == *(str + i))
        {
            c = *(str + i);
            if (!CStackIsEmpty(c_stack) && '*' == CStackPeek(c_stack))
            {
                current = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp *= current;
                NStackPush(n_stack, temp);
                // pop c_stack (pop *);
                // push c_stack (push *);
            }
            else
            {
                CStackPush(c_stack, c);
            }
        }
        else if (('+' == *(str + i)) || (('(' == *(str + i))))
        {
            c = *(str + i);
            CStackPush(c_stack, c);
        }
        else if (')' == *(str + i))
        {
            if (!CStackIsEmpty(c_stack) && ('*' == CStackPeek(c_stack)))
            {
                current = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp *= current;
                NStackPush(n_stack, temp);

                CStackPop(c_stack);
            }

            CStackPop(c_stack); /* Pops the '(' relevant to the ')' */

            if (!CStackIsEmpty(c_stack) && ('+' == CStackPeek(c_stack)))
            {
                current = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp += current;
                NStackPush(n_stack, temp);

                CStackPop(c_stack);
            }
        }
        
        /* Getting to the end of the expresion */
        if ('\n' == *(str + i + 1))
        {
            if (!CStackIsEmpty(c_stack) && '*' == CStackPeek(c_stack))
            {
                current = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp = NStackPeek(n_stack);
                NStackPop(n_stack);

                temp *= current;
                NStackPush(n_stack, temp);

                CStackPop(c_stack);
            }
        }

        ++i;
    }

    value = NStackPeek(n_stack);

    NStackDestroy(n_stack);
    CStackDestroy(c_stack);

    // printf("%ld\n\n", value);
    return (value);
}
