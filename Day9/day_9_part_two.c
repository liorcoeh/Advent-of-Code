
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (610)
#define LENGTH (20)
#define INVALID_NUMBER (530627549)

void GettingInfo(int arr[ARRAY_SIZE]);
void PrintInfo(int arr[ARRAY_SIZE]);

int SumOfAllInRange(int arr[ARRAY_SIZE], int low, int high);
void ContiguousRange(int arr[ARRAY_SIZE], int *low, int *high);
void SmallestAndLargestInRange(int arr[ARRAY_SIZE], int low, int high, int *smallest, int *largest);

int main()
{
    int nums[ARRAY_SIZE] = {0};
    int low = 0;
    int high = 0;

    int smallest = 0;
    int largest = 0;

    GettingInfo(nums);
    //PrintInfo(nums);

    ContiguousRange(nums, &low, &high);

    printf("%d, %d\n", low, high);

    SmallestAndLargestInRange(nums, low, high, &smallest, &largest);

    printf("Smallest = %d, Largest = %d\n", smallest, largest);

    printf("%d\n", smallest + largest);

    return (0);
}

void SmallestAndLargestInRange(int arr[ARRAY_SIZE], int low, int high, int *smallest, int *largest)
{
    int min = arr[low];
    int max = arr[low];
    int i = 0;

    for (i = low; i <= high; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }

        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    *smallest = min;
    *largest = max;
}

void ContiguousRange(int arr[ARRAY_SIZE], int *low, int *high)
{
    int back = 0;
    int front = 0;
    int i = 0;

    int sum = 0;

    for (back = 0; back < ARRAY_SIZE - 1; ++back)
    {
        for (front = back + 1; front < ARRAY_SIZE; ++front)
        {
            sum = SumOfAllInRange(arr, back, front);

            if (INVALID_NUMBER == sum)
            {
                *low = back;
                *high = front;
            }
        }
    }
}

int SumOfAllInRange(int arr[ARRAY_SIZE], int low, int high)
{
    int i = 0;
    int result = 0;

    for (i = low; i <= high; ++i)
    {
        result += arr[i];
    }

    return (result);
}

void GettingInfo(int arr[ARRAY_SIZE])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char num[LENGTH] = {0};
    size_t length = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("numbers_part_two.txt", "r")))
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