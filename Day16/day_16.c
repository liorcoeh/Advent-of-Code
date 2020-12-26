
#include "day_16.h"

/*******************************************************************************
***************************** PART ONE FUNCTIONS *******************************
*******************************************************************************/

int PartOneFunction(Valid_Nums valid_nums[], int tickets_info[][20], int indexs[])
{
    int total_sum = 0;
    int i = 0;
    int j = 0;
    int index = 0;
    int low = 0;
    int high = 0;
    int check = 0;

    FullRange(valid_nums, &low, &high);

    for (i = 0; i < 238; ++i)
    {
        for (j = 0; j < 20; ++j)
        {
            if (low > tickets_info[i][j] || high < tickets_info[i][j])
            {
                total_sum += tickets_info[i][j];
                indexs[index] = i;
                ++index;
            }
        }
    }

    return (total_sum);
}

void GettingInfo(char* file_name, Valid_Nums valid_nums[], int tickets_info[][20])
{
    int temp_valid_nums[80] = {0};
    int counter = 0;
    char c = 0;
    char temp = 0;
    char num[10] = {0};
    int i = 0;
    int j = 0;
    int index = 0;

    FILE* fptr;

    if (NULL == (fptr = fopen(file_name, "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            if (19 >= counter)
            {
                temp_valid_nums[index] = atoi(num);
                memset(num, 0, 10);
                ++index;
                i = 0;
            }

            if (24 < counter)
            {
                tickets_info[index][j] = atoi(num);
                memset(num, 0, 10);
                j = 0;
                ++index;
                i = 0;
            }
            ++counter;
        }

        if (20 >= counter)
        {
            if ('0' <= c && '9' >= c)
            {
                *(num + i) = c;
                ++i;
            }

            else if (('-' == c || ' ' == c) && ('0' <= temp && '9' >= temp))
            {
                temp_valid_nums[index] = atoi(num);
                memset(num, 0, 10);
                ++index;
                i = 0;
            }
        }

        else if (24 == counter)
        {
            index = 0;
        }

        else if (24 < counter)
        {
            if (',' == c)
            {
                tickets_info[index][j] = atoi(num);
                memset(num, 0, 10);
                ++j;
                i = 0;
            }
            else if ('0' <= c && '9' >= c)
            {
                *(num + i) = c;
                ++i;
            }
        }
        temp = c;
    }
    tickets_info[index][j] = atoi(num);

    ArrangeValidNums(valid_nums, temp_valid_nums);

    fclose(fptr);
}

void ArrangeValidNums(Valid_Nums valid_nums[], int temp_valid_nums[])
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 20; ++i)
    {
        valid_nums[i].class_num = i + 1;
        valid_nums[i].low_low = temp_valid_nums[j];
        ++j;
        valid_nums[i].low_high = temp_valid_nums[j];
        ++j;
        valid_nums[i].high_low = temp_valid_nums[j];
        ++j;
        valid_nums[i].high_high = temp_valid_nums[j];
        ++j;
    }
}

void FullRange(Valid_Nums valid_nums[], int* low, int* high)
{
    int arr[1000] = {0};
    int index = 0;
    int i = 0;

    for (index = 0; index < 20; ++index)
    {
        for (i = valid_nums[index].low_low; i < valid_nums[index].low_high; ++i)
        {
            if (arr[i] == 0)
            {
                ++arr[i];
            }
        }

        for (i = valid_nums[index].high_low; i < valid_nums[index].high_high; ++i)
        {
            if (arr[i] == 0)
            {
                ++arr[i];
            }
        }
    }

    for (i = 0; i < 1000; ++i)
    {
        if (arr[i] != 0)
        {
            *low = i;
            break;
        }
    }

    for (i = 999; i >= *low; --i)
    {
        if (arr[i] != 0)
        {
            *high = i + 1;
            break;
        }
    }
}


void PrintInfo(Valid_Nums valid_nums[], int tickets_info[][20])
{
    int i = 0;
    int j = 0;

    printf("The VALID NUMBERS:\n");
    for (i = 0; i < 20; ++i)
    {
        printf("%d) %d-%d %d-%d\n", valid_nums[i].class_num, valid_nums[i].low_low, valid_nums[i].low_high, valid_nums[i].high_low, valid_nums[i].high_high);
    }
    printf("\n\n");

    printf("The Real Numbers:\n");
    for (i = 0; i < 238; ++i)
    {
        printf("%d) ", i);
        for (j = 0; j < 19; ++j)
        {
            printf("%d, ", tickets_info[i][j]);
        }
        printf("%d\n", tickets_info[i][j]);
    }
    printf("\n\n");
}

/*******************************************************************************
***************************** PART TWO FUNCTIONS *******************************
*******************************************************************************/

void CheckFields(int valid_tickets[][20], Valid_Nums valid_nums[])
{
    int fields[20][20] = {0};
    int fields_row = 0;
    int fields_column = 0;

    int tickets_row = 0;
    int tickets_column = 0;

    int nums_row = 0;

    while (20 > tickets_column)
    {
        printf("\nTickets Column = %d\n", tickets_column + 1);
        for (tickets_row = 0; tickets_row < 190; ++tickets_row)
        {
            for (nums_row = 0; nums_row < 20; ++nums_row)
            {
                if (valid_nums[nums_row].low_high < valid_tickets[tickets_row][tickets_column] && valid_nums[nums_row].high_low > valid_tickets[tickets_row][tickets_column])
                {
                    printf("tickets row = %d, %d, field row = %d\n", tickets_row, valid_tickets[tickets_row][tickets_column], nums_row + 1);

                    fields_row = nums_row;
                    fields_column = tickets_column;

                    ++fields[fields_row][fields_column];
                }
            }
        }
        ++tickets_column;
    }

    printf("\n\n  ");
    int i = 0;
    for (i = 1; i < 21; ++i)
    {
        printf("%d | ", i);
    }
    printf("\n");
    
    for (fields_row = 0; fields_row < 20; ++fields_row)
    {
        printf("%d) ", fields_row + 1);
        for (fields_column = 0; fields_column < 20; ++fields_column)
        {
            printf("%d | ", fields[fields_row][fields_column]);
        }
        printf("\n\n");
    }
    printf("  ");
    for (i = 1; i < 21; ++i)
    {
        printf("%d | ", i);
    }
    printf("\n");
}

void GetValidTickets(int tickets_info[][20], int indexs[], int valid_tickets[][20])
{
    int info_index = 0;
    int valid_index = 0;
    int i = 0;
    int index = 0;

    for (info_index = 0; info_index < 238; ++info_index)
    {
        if (info_index != indexs[index])
        {
            for (i = 0; i < 20; ++i)
            {
                valid_tickets[valid_index][i] = tickets_info[info_index][i];
            }
            ++valid_index;
        }
        else
        {
            ++index;
        }
        
    }
}