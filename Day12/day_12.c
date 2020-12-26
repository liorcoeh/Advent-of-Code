
#include "day_12.h"

/*******************************************************************************
****************************** GENERAL FUNCTIONS *******************************
*******************************************************************************/

void GettingInfo(char* file_name,
                    char arr[][LENGTH], int nums[], int array_size)
{
    int index = 0;
    int i = 0;
    int j = 0;
    char c = 0;
    char buffer[LENGTH] = {0};
    char num[LENGTH] = {0};

    FILE *fptr;

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
            memcpy(arr[index], buffer, LENGTH);
            memset(buffer, 0, LENGTH);

            nums[index] = atoi(num);
            memset(num, 0, LENGTH);

            ++index;
            i = 0;
            j = 0;
        }
        else if ('A' <= c && 'Z' >= c)
        {
            *(buffer + i) = c;
            ++i;
        }
        else
        {
            *(num + j) = c;
            ++j;
        }
    }

    memcpy(arr[index], buffer, LENGTH);
    nums[index] = atoi(num);

    fclose(fptr);
}

void PrintInfo(char arr[][LENGTH], int nums[], int array_size)
{
    int i = 0;

    for (i = 0; i < array_size; ++i)
    {
        printf("%d. %s %d\n", i + 1, arr[i], nums[i]);
    }
}


/*******************************************************************************
***************************** PART ONE FUNCTIONS *******************************
*******************************************************************************/

int PartOneFunction(char arr[][LENGTH], int nums[], int array_size)
{
    int manhattan_distance = 0;
    int east_pos = 0;
    int north_pos = 0;
    Ship_Direction ship_direction = EAST;

    int index = 0;

    for (index = 0; index < array_size; ++index)
    {
        switch (*(arr[index]))
        {
            case ('E'):
            {
                east_pos += nums[index];
                break;
            }
            case ('S'):
            {
                north_pos -= nums[index];
                break;
            }
            case ('W'):
            {
                east_pos -= nums[index];
                break;
            }
            case ('N'):
            {
                north_pos += nums[index];
                break;
            }
            case ('R'):
            {
                UpdateDirection(arr[index], nums[index], &ship_direction);
                break;
            }
            case ('L'):
            {
                UpdateDirection(arr[index], nums[index], &ship_direction);
                break;
            }
            case ('F'):
            {
                MoveForword(nums[index], ship_direction, &east_pos, &north_pos);
                break;
            }
            default:
            {
                printf("DEFAULT!!!\n");
                break;
            }
        }
    }


    manhattan_distance = ManhattanDistance(east_pos, north_pos);

    return (manhattan_distance);
}

Ship_Direction UpdateDirection(char *turn_to, int degrees_amount,
                                            Ship_Direction *current_direction)
{
    int right_turn = degrees_amount;

    if ('L' == *turn_to)
    {
        right_turn = 360 - degrees_amount;
    }

    if (360 == right_turn || 0 == right_turn)
    {
        right_turn = 0;
    }
    else
    {
        right_turn /= 90;
    }

    *current_direction = ((*current_direction) + right_turn) % 4;

    return (*current_direction);
}

void MoveForword(int amount, Ship_Direction current_direction,
                                            int *east_pos, int *north_pos)
{
    switch (current_direction)
    {
        case (EAST):
        {
            (*east_pos) += amount;
            break;
        }
        case (SOUTH):
        {
            (*north_pos) -= amount;
            break;
        }
        case (WEST):
        {
            (*east_pos) -= amount;
            break;
        }
        case (NORTH):
        {
            (*north_pos) += amount;
            break;
        }
    }
}


int ManhattanDistance(int east_pos, int north_pos)
{
    if (0 > east_pos)
    {
        east_pos *= (-1);
    }

    if (0 > north_pos)
    {
        north_pos *= (-1);
    }

    return (east_pos + north_pos);
} 

/*******************************************************************************
***************************** PART TWO FUNCTIONS *******************************
*******************************************************************************/

int PartTwoFunction(char arr[][LENGTH], int nums[], int array_size)
{
    int manhattan_distance = 0;
    int east_pos = 0;
    int north_pos = 0;

    int wp_east_pos = 10;
    int wp_north_pos = 1;

    int index = 0;

    for (index = 0; index < array_size; ++index)
    {
        switch (*(arr[index]))
        {
            case ('E'):
            {
                wp_east_pos += nums[index];
                break;
            }
            case ('S'):
            {
                wp_north_pos -= nums[index];
                break;
            }
            case ('W'):
            {
                wp_east_pos -= nums[index];
                break;
            }
            case ('N'):
            {
                wp_north_pos += nums[index];
                break;
            }
            case ('R'):
            {
                UpdateWaypointAngle(arr[index], nums[index],
                                                &wp_east_pos, &wp_north_pos);
                break;
            }
            case ('L'):
            {
                UpdateWaypointAngle(arr[index], nums[index],
                                                &wp_east_pos, &wp_north_pos);
                break;
            }
            case ('F'):
            {
                //UpdateShipsPosition(nums[index], ship_direction, &east_pos, &north_pos);

                east_pos += (nums[index] * wp_east_pos);
                north_pos += (nums[index] * wp_north_pos);
                break;
            }
            default:
            {
                printf("DEFAULT!!!\n");
                break;
            }
        }
    }

    manhattan_distance = ManhattanDistance(east_pos, north_pos);

    return (manhattan_distance);
}

void UpdateWaypointAngle(char *direction, int degrees,
                                    int *wp_east_pos, int *wp_north_pos)
{
    int temp = 0;

    if (180 == degrees)
    {
        (*wp_east_pos) *= (-1);
        (*wp_north_pos) *= (-1);
        return;
    }

    if ('L' == *direction)
    {
        degrees = 360 - degrees;
    }

    if (90 == degrees)
    {
        temp = (*wp_east_pos) * (-1);

        *wp_east_pos = *wp_north_pos;
        *wp_north_pos = temp;
    }
    else if (270 == degrees)
    {
        temp = (*wp_north_pos) * (-1);

        *wp_north_pos = *wp_east_pos;
        *wp_east_pos = temp;
    }
}

void UpdateShipsPosition(int amount, int *ship_east_pos, int *ship_north_pos,
                                int wp_east_pos, int we_north_pos)
{
    *ship_east_pos += (amount * wp_east_pos);
    *ship_north_pos += (amount * we_north_pos);
}
