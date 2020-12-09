/*
 * Day 1:
 * 
 * First Part:
 * Find two numbers in the list of given numbers that add up to '2020'.
 * The function should return the multication of these two numbers.
 * Example:
 * 
 * The list of given numbers is -
 * 1721
 * 979
 * 366
 * 299
 * 675
 * 1456
 * In this list, the two entries that sum to 2020 are 1721 and 299.
 * Multiplying them together produces 1721 * 299 = 514579, so the
 * correct answer is 514579.
 * 
 * Second Part:
 * Find three numbers that do the same thing, so if the list is the same
 * one as above the numbers will be: 979, 366, and 675.
 * Multiplying them together produces the answer: 241861950.
 */


/*
 * My idea to solve it is to first get all the numbers into an array by
 * reading them from a file.
 * Than I will sort the numbers O(nlog(n)).
 * For the first part I will go from the beggining of the array and the
 * end of the array looking for the two numbers.
 * Fot the second part I will go from the beggining of the array and will
 * use the function of the first part to find other two numbers that
 * equal the total sum minus the number I am currently on.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE (1000)
#define BUFFER_LENGTH (10)

/* StringIntoArr: Will take the numbers given as a list in a file and
 * will put them into an array of ints.
 */
void StringIntoArr(int arr[], int *size);

/*
 * CompareFunction: Used in the qsort function.
 */
int CompareFunction(const void* a, const void* b);

/*
 * TwoNums: Finds the two numbers that are equal to the requasted
 * sum, and returns the multication of the two.
 */
int TwoNums(int arr[], int size, int sum);

/*
 * ThreeNums: Finds three numbers that are equa to the requasted sum
 * and returns the multication of the three.
 */
int ThreeNums(int arr[], int size, int sum);

/*
 * PrintArr: Prints the array of ints.
 */
void PrintArr(int arr[], int size);

int main()
{
    int arr[SIZE] = {0};
    int size = 0;

    int sum = 2020;
    int result = 0;

    StringIntoArr(arr, &size);

    qsort(arr, size, sizeof(int), CompareFunction);

    /* Part One */
    result = TwoNums(arr, size, sum);

    printf("The result is: %d\n\n", result);

    /* Part Two */
    result = ThreeNums(arr, size, sum);

    printf("The result is: %d\n\n", result);

    return (0);
}

int TwoNums(int arr[], int size, int sum)
{
    int i = 0;
    int j = size - 1;

    while (i < j)
    {
        if (sum == (arr[i] + arr[j]))
        {
            printf("%d + %d = %d\n", arr[i], arr[j], arr[i] + arr[j]);
            return (arr[i] * arr[j]);
        }
        else if (sum > (arr[i] + arr[j]))
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
    printf("Couldn't find two nums equal to %d\n", sum);
    return (-1); /* Failure */
}

int ThreeNums(int arr[], int size, int sum)
{
    int result = 0;
    int i = 0;

    for (i = 0; i < size - 2; ++i)
    {
        result = TwoNums((arr + i), size - i, sum - arr[i]);
        if (-1 != result)
        {
            printf("%d\n", arr[i]);
            return (arr[i] * result);
        }
    }
}

void StringIntoArr(int arr[], int *size)
{
    char buffer[BUFFER_LENGTH];
    int index = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("nums.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    /* Gets the numbers line by line and puts them into an array */
    while (fgets(buffer, BUFFER_LENGTH, fptr))
    {
        arr[index] = atoi(buffer);
        ++index;
    }

    *size = index;

    fclose(fptr);
}

int CompareFunction(const void* a, const void* b)
{
   return (*(int*)a - *(int*)b);
}

void PrintArr(int arr[], int size)
{
    int i = 0;
    
    for (i = 0; i < size; ++i)
    {
        printf("%d, ", arr[i]);
    }
}