
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_AMOUNT (622)
#define LENGTH (20)

void GettingInfo(char arr[ARRAY_AMOUNT][LENGTH], int nums[]);
void PrintInfo(char arr[ARRAY_AMOUNT][LENGTH], int nums[]);
void ResetArr(int arr[]);

int PartOneSolving(char arr[ARRAY_AMOUNT][LENGTH], int nums[]);
int PartTwoSolving(char arr[ARRAY_AMOUNT][LENGTH], int nums[]);

int main()
{
    int accumulator = 0;
    char arr[ARRAY_AMOUNT][LENGTH];
    int amount[ARRAY_AMOUNT] = {0};

    GettingInfo(arr, amount);
    // accumulator = PartOneSolving(arr, amount);

    // printf("The accumulator in part ONE is: %d\n", accumulator);

    accumulator = PartTwoSolving(arr, amount);

    printf("The accumulator in part TWO is: %d\n", accumulator);

    //PrintInfo(arr, amount);

    return (0);
}

int PartTwoSolving(char arr[ARRAY_AMOUNT][LENGTH], int nums[])
{
    int accumulator = 0;
    int index = 0;
    int check = 1;
    int i = 0;

    int counting_arr[ARRAY_AMOUNT] = {0};

    for (i = 0; i < ARRAY_AMOUNT; ++i)
    {
        accumulator = 0;
        index = 0;
        check = 1;
        ResetArr(counting_arr);

        if (0 == strcmp("jmp", arr[i]))
        {
            memcpy(arr[i], "nop", 4);
            check = 0;
        }
        else if (0 == strcmp("nop", arr[i]))
        {
            memcpy(arr[i], "jmp", 4);
            check = 0;
        }

        while (0 == check)
        {
            if (ARRAY_AMOUNT == index)
            {
                printf("The i is: %d\n", i);
                check = 2;
                break;
            }

            if (0 == strcmp("acc", arr[index]))
            {
                if (1 == counting_arr[index])
                {
                    check = 1;
                }
                else
                {
                    ++counting_arr[index];
                    accumulator += (nums[index]);
                    ++index;
                }
            }

            else if (0 == strcmp("jmp", arr[index]))
            {
                if (1 == counting_arr[index])
                {
                    check = 1;
                }
                else
                {
                    ++counting_arr[index];
                    index += (nums[index]);
                }
            }

            else /* (0 == strcmp("nop", arr[index])) */
            {
                if (1 == counting_arr[index])
                {
                    check = 1;
                }
                else
                {
                    ++counting_arr[index];
                    ++index;
                }
            }
        }

        if (1 == check)
        {
            if (0 == strcmp("jmp", arr[i]))
            {
                memcpy(arr[i], "nop", 4);
            }
            else if (0 == strcmp("nop", arr[i]))
            {
                memcpy(arr[i], "jmp", 4);
            }
        }
        else if (2 == check)
        {
            break;
        }
    }

    return (accumulator);
}

int PartOneSolving(char arr[ARRAY_AMOUNT][LENGTH], int nums[])
{
    int accumulator = 0;
    int index = 0;
    int check = 0;
    int steps = 0;

    int counting_arr[ARRAY_AMOUNT] = {0};

    while (0 == check)
    {
        if (0 == strcmp("acc", arr[index]))
        {
            if (1 == counting_arr[index])
            {
                check = 1;
            }
            else
            {
                ++counting_arr[index];
                accumulator += (nums[index]);
                ++index;
            }
        }

        else if (0 == strcmp("jmp", arr[index]))
        {
            if (1 == counting_arr[index])
            {
                check = 1;
            }
            else
            {
                ++counting_arr[index];
                index += (nums[index]);
            }
        }

        else /* (0 == strcmp("nop", arr[index])) */
        {
            if (1 == counting_arr[index])
            {
                check = 1;
            }
            else
            {
                ++counting_arr[index];
                ++index;
            }
        }
        ++steps;
    }

    return (accumulator);
}

void GettingInfo(char arr[ARRAY_AMOUNT][LENGTH], int nums[])
{
    int index = 0;
    int i = 0;
    int j = 0;
    char c = 0;
    char buffer[LENGTH] = {0};
    char num[LENGTH] = {0};
    int sign = 1;
    int counter = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("instructions.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }
    
    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            memcpy(arr[index], buffer, 4);
            memset(buffer, 0, 4);

            nums[index] = atoi(num);
            nums[index] *= sign;
            memset(num, 0, 5);

            ++index;
            i = 0;
            j = 0;
            sign = 1;
        }
        else if ('a' <= c && 'z' >= c)
        {
            *(buffer + i) = c;
            ++i;
        }
        else if ('-' == c)
        {
            sign = -1;
        }
        else if ('0' <= c && '9' >= c)
        {
            *(num + j) = c;
            ++j;
        }
    }

    memcpy(arr[index], buffer, 4);
    memset(buffer, 0, 4);

    nums[index] = atoi(num);
    nums[index] *= sign;

    fclose(fptr);
}

void PrintInfo(char arr[ARRAY_AMOUNT][LENGTH], int nums[])
{
    int i = 0;

    for (i = 0; i < ARRAY_AMOUNT; ++i)
    {
        printf("%d. %s || %d\n", i, arr[i], nums[i]);
    }
}

void ResetArr(int arr[])
{
    int i = 0;

    for (i = 0; i < ARRAY_AMOUNT; ++i)
    {
        arr[i] = 0;
    }
}