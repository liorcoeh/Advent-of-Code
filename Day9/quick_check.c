
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (25)
#define LENGTH (20)

void GettingInfo(int arr[ARRAY_SIZE]);
void PrintInfo(int arr[ARRAY_SIZE]);

int IsASumOfTwo(int num, int arr[ARRAY_SIZE]);

int main()
{
    int nums[ARRAY_SIZE] = {0};
    int num = 530627549;

    GettingInfo(nums);

    IsASumOfTwo(num, nums);

    //PrintInfo(nums);

    return (0);
}

int IsASumOfTwo(int num, int arr[ARRAY_SIZE])
{
    int i = 0;
    int j = 0;

    for (i = 0; i < ARRAY_SIZE - 1; ++i)
    {
        for (j = i + 1; j < ARRAY_SIZE; ++j)
        {
            if (num == (arr[i] + arr[j]))
            {
                printf("EQAUL\n");
                return (1);
            }
        }
    }
    printf("NOT equal\n");
    return (0);
}

void GettingInfo(int arr[ARRAY_SIZE])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char num[LENGTH] = {0};
    size_t length = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("quick_check.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }
    
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

void PrintInfo(int arr[ARRAY_SIZE])
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d\n", arr[i]);
    }
}