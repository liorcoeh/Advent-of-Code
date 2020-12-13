
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (846)
#define BUFFER_LENGTH (11)

#define LEFT_ROW (0)
#define RIGHT_ROW (127)
#define LEFT_COLUMN (0)
#define RIGHT_COLUMN (7) 

void GettingInfo(char arr[ARRAY_SIZE][BUFFER_LENGTH]);
int GetSeatID(char *str);
int HighestSeatID(char arr[ARRAY_SIZE][BUFFER_LENGTH], int seat_ids[]);
void SortSeatIDS(int arr[], int size);

int FindMissingSeat(int arr[], int size);

void PrintStrings(char arr[ARRAY_SIZE][BUFFER_LENGTH]);
void PrintSeatIDS(int arr[], int size);
int CompareFunc(const void *a, const void *b);

int main()
{
    char main_arr[ARRAY_SIZE][BUFFER_LENGTH];
    int seat_ids[ARRAY_SIZE];

    GettingInfo(main_arr);

    // PrintStrings(main_arr);

    printf("Max Seat ID is: %d\n", HighestSeatID(main_arr, seat_ids));

    SortSeatIDS(seat_ids, ARRAY_SIZE);

    printf("The missing seat is: %d\n", FindMissingSeat(seat_ids, ARRAY_SIZE));

    //PrintSeatIDS(seat_ids, ARRAY_SIZE);

    return (0);
}

int GetSeatID(char *str)
{
    int seat_id = 0;
    int row = 0;
    int column = 0;

    int right = RIGHT_ROW;
    int left = LEFT_ROW;
    int half = 0;

    int i = 0;

    for (i = 0; i < 6; ++i)
    {
        half = (right - left) / 2;
        if (0 != half % 2)
        {
            ++half;
        }

        if ('F' == *(str + i))
        {
            right -= half; 
        }
        else if ('B' == *(str + i))
        {
            left += half;
        }
    }

    if ('F' == *(str + 6))
    {
        row = left;
    }
    else if ('B' == *(str + 6))
    {
        row = right;
    }

    right = RIGHT_COLUMN;
    left = LEFT_COLUMN;
    half = 0;

    for (i = 7; i < 9; ++i)
    {
        half = (right - left) / 2;
        if (0 != half % 2)
        {
            ++half;
        }

        if ('L' == *(str + i))
        {
            right -= half; 
        }
        else if ('R' == *(str + i))
        {
            left += half;
        }
    }

    if ('L' == *(str + 9))
    {
        column = left;
    }
    else if ('R' == *(str + 9))
    {
        column = right;
    }

    seat_id = (row * 8) + column;
    
    return (seat_id);
}

int HighestSeatID(char arr[ARRAY_SIZE][BUFFER_LENGTH], int seat_ids[])
{
    int max_seat_id = 0;
    int seat_id = 0;
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        seat_id = GetSeatID(arr[i]);
        seat_ids[i] = seat_id;

        if (max_seat_id < seat_id)
        {
            max_seat_id = seat_id;
        }
    }

    return (max_seat_id);
}

void SortSeatIDS(int arr[], int size)
{
    qsort(arr, size, sizeof(int), CompareFunc);
}

int FindMissingSeat(int arr[], int size)
{
    int missing_seat = 80;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        if (missing_seat != arr[i])
        {
            break;
        }
        else
        {
            ++missing_seat;
        }
    }

    return (missing_seat);
}

void GettingInfo(char arr[ARRAY_SIZE][BUFFER_LENGTH])
{
    char buffer[BUFFER_LENGTH];
    char c = 0;
    int i = 0;
    int j = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("boarding_seats.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        j = 0;
        while ('\n' != (c = fgetc(fptr)))
        {
            *(buffer + j) = c;
            ++j;
        }

        memcpy(arr[i], buffer, BUFFER_LENGTH);
    }

    fclose(fptr);
}

void PrintStrings(char arr[ARRAY_SIZE][BUFFER_LENGTH])
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d. %s\n", i + 1, arr[i]);
    }
    printf("\n");
}

void PrintSeatIDS(int arr[], int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("%d. %d\n", i + 1, arr[i]);
    }
}

int CompareFunc(const void *a, const void *b)
{
   return (*(int*)a -*(int*)b);
}