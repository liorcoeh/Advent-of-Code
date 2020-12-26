
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (93)
/* #define ARRAY_SIZE (31) */ /* size of the test case */
#define LENGTH (5)

void GettingInfo(int arr[ARRAY_SIZE]);
void SortInfo(int arr[ARRAY_SIZE]);
int CompareFunc(const void *a, const void *b);
int PartOneFunction(int arr[ARRAY_SIZE]);
size_t PartTwoFunction(int arr[ARRAY_SIZE]);
void PrintInfo(int arr[ARRAY_SIZE]);

int main()
{
    int adapters[ARRAY_SIZE] = {0};

    GettingInfo(adapters);
    // PrintInfo(adapters);
    SortInfo(adapters);
    //PrintInfo(adapters);

    //printf("The answer for part ONE is: %d\n", PartOneFunction(adapters));
    printf("The answer for part TWO is: %ld\n", PartTwoFunction(adapters));

    return (0);
}

size_t PartTwoFunction(int arr[ARRAY_SIZE])
{
    size_t result = 1;
    int counter = 0;
    int temp = 0;
    int index = 0;
    int front = 0;
    int back = -1;

    for (index = 0; index < ARRAY_SIZE - 1; ++index)
    {
        front = index + 1;

        if (arr[index] + 3 == arr[front])
        {
            counter = index - back - 1;
            if (back == index)
            {
                counter = 0;
            }

            switch (counter)
            {
                case (0):
                {
                    temp = 1;
                    break;
                }
                case (1):
                {
                    temp = 2;
                    break;
                }
                case (2):
                {
                    temp = 4;
                    break;
                }
                case (3):
                {
                    temp = 7;
                    break;
                }
            }

            result *= temp;
            back = front;
        }
    }

    result *= 7;

    return (result);
}

int PartOneFunction(int arr[ARRAY_SIZE])
{
    int one_jolt = 0;
    int three_jolt = 1;
    int temp = 0;
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (temp + 1 == arr[i])
        {
            ++one_jolt;
        }
        else if (temp + 3 == arr[i])
        {
            ++three_jolt;
        }

        temp = arr[i];
    }

    return (one_jolt * three_jolt);
}

void GettingInfo(int arr[ARRAY_SIZE])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char num[LENGTH] = {0};
    size_t length = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("adapters.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    /* Used for the test case */
    /* if (NULL == (fptr = fopen("test.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }*/
    
    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            arr[index] = atoi(num);
            memset(num, 0, LENGTH);

            ++index;
            i = 0;
        }
        else
        {
            *(num + i) = c;
            ++i;
        }
    }

    arr[index] = atoi(num);

    fclose(fptr);
}

void SortInfo(int arr[ARRAY_SIZE])
{
    qsort(arr, ARRAY_SIZE, sizeof(int), CompareFunc);
}

void PrintInfo(int arr[ARRAY_SIZE])
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d. %d\n", i, arr[i]);
    }
}

int CompareFunc(const void *a, const void *b)
{
   return (*(int*)a - *(int*)b);
}