
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (1000)
#define LENGTH (20)
#define PREAMBLE_SIZE (25)

void GettingInfo(int arr[ARRAY_SIZE][LENGTH]);
void PrintInfo(int arr[ARRAY_SIZE][LENGTH]);

void AddingTwoArrs(int num_one[LENGTH], int num_two[LENGTH], int result[LENGTH]);
int AreTwoArrsEqual(int num_one[LENGTH], int num_two[LENGTH]);

void NumNotEqualToSumOfTwo(int arr[ARRAY_SIZE][LENGTH], int num[LENGTH]);

void PrintArrNum(int num[LENGTH]);

int main()
{
    int nums[ARRAY_SIZE][LENGTH] = {0};
    int invalid_number[LENGTH] = {0};

    GettingInfo(nums);
    //PrintInfo(nums);

    NumNotEqualToSumOfTwo(nums, invalid_number);
    PrintArrNum(invalid_number);

    /* Invalid number is being used in the second part */


    return (0);
}

void NumNotEqualToSumOfTwo(int arr[ARRAY_SIZE][LENGTH], int num[LENGTH])
{
    int low = 0;
    int high = PREAMBLE_SIZE - 1;
    int index = PREAMBLE_SIZE;
    int i = 0;
    int j = 0;
    int check = 0;

    int sum_of_two[LENGTH] = {0};

    while (high < ARRAY_SIZE)
    {
        for (i = low; i < high; ++i)
        {
            for (j = i + 1; j <= high; ++j)
            {
                AddingTwoArrs(arr[i], arr[j], sum_of_two);
                {
                    if (1 == AreTwoArrsEqual(arr[index], sum_of_two))
                    {
                        ++index;
                        i = high;
                        j = high + 1;
                        check = 1; /* OK */
                    }
                    else
                    {
                        check = 0;
                    }
                    
                }
            }
        }

        if (0 == check)
        {
            for (i = 0; i < LENGTH; ++i)
            {
                num[i] = arr[index][i];
            }
            high = ARRAY_SIZE;
        }
        else
        {
            ++low;
            ++high;
        }
    }
}

void AddingTwoArrs(int num_one[LENGTH], int num_two[LENGTH], int result[LENGTH])
{
    int counter = 0;
    int length_one = num_one[LENGTH - 1];
    int length_two = num_two[LENGTH - 1];
    int i = length_one - 1;
    int j = length_two - 1;

    int local_result[LENGTH] = {0};
    int index = LENGTH - 1;
    int result_length = 0;
    int temp = 0;
    int leftover = 0;

    int max_length = 0;

    if (length_one >= length_two)
    {
        max_length = length_one;
    }
    else
    {
        max_length = length_two;
    }
    
    result_length = max_length;

    for (counter = 0; counter < max_length; ++counter)
    {
        if (0 <= i && 0 <= j)
        {
            temp = num_one[i] + num_two[j];
        }
        else if (0 <= i)
        {
            temp = num_one[i];
        }
        else if (0 <= j)
        {
            temp = num_two[j];
        }

        --i;
        --j;

        if (1 == leftover)
        {
            ++temp;
        }

        leftover = 0;

        if (9 < temp)
        {
            leftover = 1;
            temp -= 10;
        }

        local_result[index] = temp;
        --index;
    }
    
    if (1 == leftover)
    {
        local_result[index] = leftover;
        ++result_length;
    }

    result[LENGTH - 1] = result_length;

    for (i = 0; i < result_length; ++i)
    {
        result[i] = local_result[LENGTH - result_length + i];
    }
}

int AreTwoArrsEqual(int num_one[LENGTH], int num_two[LENGTH])
{
    int i = 0;
    int length = num_one[LENGTH - 1];

    /* If the length of the two numbers isn't the same, they aren't the same */
    if (num_one[LENGTH - 1] != num_two[LENGTH - 1])
    {
        return (0); /* False */
    }

    for (i = 0; i < length; ++i)
    {
        if (num_one[i] != num_two[i])
        {
            return (0); /* False */
        }
    }

    return (1); /* True */
}

void GettingInfo(int arr[ARRAY_SIZE][LENGTH])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char num[LENGTH] = {0};
    size_t length = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("numbers.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }
    
    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            length = strlen(num);
            i = 0;
            
            arr[index][LENGTH - 1] = length;

            while (length)
            {
                arr[index][i] = (*(num + i)) - '0';
                ++i;
                --length;
            }

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

    length = strlen(num);
    i = 0;
    
    arr[index][LENGTH - 1] = length;

    while (length)
    {
        arr[index][i] = (*(num + i)) - '0';
        ++i;
        --length;
    }

    fclose(fptr);
}

void PrintInfo(int arr[ARRAY_SIZE][LENGTH])
{
    int i = 0;
    int j = 0;
    int length = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        length = arr[i][LENGTH - 1];

        printf("%d. ", i + 1);
        for (j = 0; j < length; ++j)
        {
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

void PrintArrNum(int num[LENGTH])
{
    int i = 0;

    for (i = 0; i < LENGTH; ++i)
    {
        printf("%d", num[i]);
    }
    printf("\n");
}