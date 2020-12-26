#include "day_13.h"

/*******************************************************************************
****************************** GENERAL FUNCTIONS *******************************
*******************************************************************************/



/*******************************************************************************
***************************** PART ONE FUNCTIONS *******************************
*******************************************************************************/

int PartOneFunction(int time_stamp, int arr[], int array_size)
{
    int bus_id = 0;
    int reminder = 0;
    int temp_minutes_to_wait = 0;
    int min_minutes_to_wait = time_stamp;

    int i = 0;

    for (i = 0; i < array_size; ++i)
    {
        reminder = time_stamp % arr[i];

        if (0 == reminder)
        {
            min_minutes_to_wait = 0;
        }
        else
        {
            temp_minutes_to_wait = arr[i] - reminder;
        }

        if (temp_minutes_to_wait < min_minutes_to_wait)
        {
            min_minutes_to_wait = temp_minutes_to_wait;
            bus_id = arr[i];
        } 
    }

    return (min_minutes_to_wait * bus_id);
}


/*******************************************************************************
***************************** PART TWO FUNCTIONS *******************************
*******************************************************************************/

/*
 * The algorithm for this part is based on the: Chinese Remainder Theorem.
 */

size_t PartTwoFunction(size_t arr[], size_t minutes[], int array_size)
{
    size_t total_sum = 0;
    size_t multi = 0;

    int i = 0;

    multi = GetMulti(arr, array_size);

    for (i = 0; i < array_size; ++i)
    {   
        total_sum += GetEachBus(multi, arr[i], minutes[i]);
    }

    return (FindFirst(multi, total_sum));
}

size_t GetMulti(size_t arr[], int array_size)
{
    size_t multi = 1;
    int i = 0;

    for (i = 0; i < array_size; ++i)
    {
        multi *= arr[i];
    }

    return (multi);
}

size_t GetEachBus(size_t multi, size_t bus_id, size_t minutes)
{
    size_t data = multi / bus_id;
    size_t remainder = data % bus_id;
    size_t multiplier = 0;
    size_t i = 0;

    if (minutes > bus_id)
    {
        minutes = minutes % bus_id;
    }

    if (0 == minutes || bus_id == minutes)
    {
        multiplier = bus_id;
    }
    else
    {
        while (multiplier != (bus_id - minutes))
        {
            ++i;
            multiplier = (remainder * i) % bus_id;
        }

        multiplier = i;
    }

    return (data * multiplier);
}

size_t FindFirst(size_t multi, size_t total_sum)
{
    return (total_sum % multi);
}

void GettingInfo(char* file_name, size_t arr[], size_t minutes[], int array_size)
{
    int index = 0;
    int i = 0;
    char c = 0;
    char num[10] = {0};
    int counter = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen(file_name, "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }
    
    while (EOF != (c = fgetc(fptr)))
    {
        if (',' == c && i != 0)
        {
            arr[index] = atoi(num);
            memset(num, 0, 10);

            minutes[index] = counter;

            ++index;
            ++counter;
            i = 0;
        }
        else if ('x' == c)
        {
            ++counter;
        }
        else if (',' != c)
        {
            *(num + i) = c;
            ++i;
        }
    }

    arr[index] = atoi(num);
    minutes[index] = counter;

    fclose(fptr);
}

void PrintInfo(size_t arr[], size_t minutes[], int array_size)
{
    int i = 0;

    for (i = 0; i < array_size; ++i)
    {
        printf("%ld->%ld\n", arr[i], minutes[i]);
    }
}