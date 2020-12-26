
#include "day_11.h"

/*******************************************************************************
****************************** GENERAL FUNCTIONS *******************************
*******************************************************************************/

int OccupiedSeatsAmount(char arr[ARRAY_SIZE][LENGTH])
{
    int amount = 0;
    int y_pos = 0;
    int x_pos = 0;

    for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
    {
        for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
        {
            if ('#' == arr[y_pos][x_pos])
            {
                ++amount;
            }
        }
    }

    return (amount);
}

int TwoArrsEqual(char arr_one[ARRAY_SIZE][LENGTH], char arr_two[ARRAY_SIZE][LENGTH])
{
    int y_pos = 0;
    int x_pos = 0;

    for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
    {
        for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
        {
            if (arr_one[y_pos][x_pos] != arr_two[y_pos][x_pos])
            {
                return (0); /* False */
            }
        }
    }

    return (1); /* True */
}

void GettingInfo(char arr[ARRAY_SIZE][LENGTH])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char buffer[LENGTH] = {0};

    FILE *fptr;

    if (NULL == (fptr = fopen("seats.txt", "r")))
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

            ++index;
            i = 0;
        }
        else
        {
            *(buffer + i) = c;
            ++i;
        }
    }

    fclose(fptr);
}

void PrintInfo(char arr[ARRAY_SIZE][LENGTH])
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d. %s\n", i + 1, arr[i]);
    }
}



/*******************************************************************************
***************************** PART ONE FUNCTIONS *******************************
*******************************************************************************/

int PartOneFunction(char arr[ARRAY_SIZE][LENGTH])
{
    int y_pos = 0;
    int x_pos = 0;
    int occupied_seats = 0;
    char temp_one[ARRAY_SIZE][LENGTH];
    char temp_two[ARRAY_SIZE][LENGTH];

    int toggle = 0;
    int check = 0;

    GettingInfo(temp_one);
    GettingInfo(temp_two);

    for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
    {
        for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
        {
            occupied_seats = AmountOfOccupiedAdjacentSeats(arr, y_pos, x_pos);

            if (('L' == arr[y_pos][x_pos]) && (0 == occupied_seats))
            {
                temp_one[y_pos][x_pos] = '#';
            }
            else if (('#' == arr[y_pos][x_pos]) && (4 <= occupied_seats))
            {
                temp_one[y_pos][x_pos] = 'L';
            }
        }
    }

    while (0 == check)
    {
        if (0 == toggle) /* Change temp_two */
        {
            for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
            {
                for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
                {
                    occupied_seats = AmountOfOccupiedAdjacentSeats(temp_one, y_pos, x_pos);

                    if (('L' == temp_one[y_pos][x_pos]) && (0 == occupied_seats))
                    {
                        temp_two[y_pos][x_pos] = '#';
                    }
                    else if (('#' == temp_one[y_pos][x_pos]) && (4 <= occupied_seats))
                    {
                        temp_two[y_pos][x_pos] = 'L';
                    }
                    else
                    {
                        temp_two[y_pos][x_pos] = temp_one[y_pos][x_pos];
                    }
                    
                }
            }
            toggle = 1;
        }
        else /* Change temp_one */
        {
            for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
            {
                for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
                {
                    occupied_seats = AmountOfOccupiedAdjacentSeats(temp_two, y_pos, x_pos);

                    if (('L' == temp_two[y_pos][x_pos]) && (0 == occupied_seats))
                    {
                        temp_one[y_pos][x_pos] = '#';
                    }
                    else if (('#' == temp_two[y_pos][x_pos]) && (4 <= occupied_seats))
                    {
                        temp_one[y_pos][x_pos] = 'L';
                    }
                    else
                    {
                        temp_one[y_pos][x_pos] = temp_two[y_pos][x_pos];
                    }
                }
            }
            toggle = 0;
        }
        
        check = TwoArrsEqual(temp_one, temp_two);
    }

    occupied_seats = OccupiedSeatsAmount(temp_one);

    return (occupied_seats);
}

int AmountOfOccupiedAdjacentSeats(char arr[ARRAY_SIZE][LENGTH],
                                                    int y_pos, int x_pos)
{
    int amount = 0;

    if ((x_pos == 0) || (x_pos == LENGTH - 2) || (y_pos == 0) || (y_pos == ARRAY_SIZE - 1))
    {
        amount = AmountEdges(arr, y_pos, x_pos);
        return (amount);
    }

    /* Top Left */
    if ('#' == arr[y_pos - 1][x_pos - 1])
    {
        ++amount;
    }
    /* Top Middle */
    if ('#' == arr[y_pos - 1][x_pos])
    {
        ++amount;
    }
    /* Top Right */
    if ('#' == arr[y_pos - 1][x_pos + 1])
    {
        ++amount;
    }
    /* Middle Right */
    if ('#' == arr[y_pos][x_pos + 1])
    {
        ++amount;
    }
    /* Buttom Right */
    if ('#' == arr[y_pos + 1][x_pos + 1])
    {
        ++amount;
    }
    /* Buttom Middle */
    if ('#' == arr[y_pos + 1][x_pos])
    {
        ++amount;
    }
    /* Buttom Left */
    if ('#' == arr[y_pos + 1][x_pos - 1])
    {
        ++amount;
    }
    /* Middle Left */
    if ('#' == arr[y_pos][x_pos - 1])
    {
        ++amount;
    }

    return (amount);
}

int AmountEdges(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int amount = 0;
    /* Top Left Corner */
    if ((0 == x_pos) && (0 == y_pos))
    {
        if ('#' == arr[y_pos][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos])
        {
            ++amount;
        }
    }

    /* Top Right Corner */
    else if ((LENGTH - 2 == x_pos) && (0 == y_pos))
    {
        if ('#' == arr[y_pos][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos])
        {
            ++amount;
        }
    }

    /* Buttom Left Corner */
    else if ((0 == x_pos) && (ARRAY_SIZE - 1 == y_pos))
    {
        if ('#' == arr[y_pos - 1][x_pos])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos][x_pos + 1])
        {
            ++amount;
        }
    }

    /* Buttom Right Corner */
    else if ((LENGTH - 2 == x_pos) && (ARRAY_SIZE - 1 == y_pos))
    {
        if ('#' == arr[y_pos][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos])
        {
            ++amount;
        }
    }

    /* Top Edge */
    else if (0 == y_pos)
    {
        if ('#' == arr[y_pos][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos][x_pos + 1])
        {
            ++amount;
        }
    }

    /* Buttom Edge */
    else if (ARRAY_SIZE - 1 == y_pos)
    {
        if ('#' == arr[y_pos][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos][x_pos + 1])
        {
            ++amount;
        }
    }

    /* Left Edge */
    else if (0 == x_pos)
    {
        if ('#' == arr[y_pos - 1][x_pos])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos + 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos])
        {
            ++amount;
        }
    }

    /* Right Edge */
    else if (LENGTH - 2 == x_pos)
    {
        if ('#' == arr[y_pos - 1][x_pos])
        {
            ++amount;
        }
        if ('#' == arr[y_pos - 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos - 1])
        {
            ++amount;
        }
        if ('#' == arr[y_pos + 1][x_pos])
        {
            ++amount;
        }
    }


    return (amount);
}



/*******************************************************************************
***************************** PART TWO FUNCTIONS *******************************
*******************************************************************************/

int PartTwoFunction(char arr[ARRAY_SIZE][LENGTH])
{
    int y_pos = 0;
    int x_pos = 0;
    int occupied_seats = 0;
    char temp_one[ARRAY_SIZE][LENGTH];
    char temp_two[ARRAY_SIZE][LENGTH];

    int toggle = 0;
    int check = 0;

    int counter = 0;

    GettingInfo(temp_one);
    GettingInfo(temp_two);

    for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
    {
        for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
        {
            occupied_seats = AmountOfOccupiedLineOfSightSeats(arr, y_pos, x_pos);

            if (('L' == arr[y_pos][x_pos]) && (0 == occupied_seats))
            {
                temp_one[y_pos][x_pos] = '#';
            }
            else if (('#' == arr[y_pos][x_pos]) && (5 <= occupied_seats))
            {
                temp_one[y_pos][x_pos] = 'L';
            }
        }
    }

    while (0 == check)
    {
        if (0 == toggle) /* Change temp_two */
        {
            for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
            {
                for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
                {
                    occupied_seats = AmountOfOccupiedLineOfSightSeats(temp_one, y_pos, x_pos);

                    if (('L' == temp_one[y_pos][x_pos]) && (0 == occupied_seats))
                    {
                        temp_two[y_pos][x_pos] = '#';
                    }
                    else if (('#' == temp_one[y_pos][x_pos]) && (5 <= occupied_seats))
                    {
                        temp_two[y_pos][x_pos] = 'L';
                    }
                    else
                    {
                        temp_two[y_pos][x_pos] = temp_one[y_pos][x_pos];
                    }
                    
                }
            }
            toggle = 1;
        }
        else /* Change temp_one */
        {
            for (y_pos = 0; y_pos < ARRAY_SIZE; ++y_pos)
            {
                for (x_pos = 0; x_pos < LENGTH - 1; ++x_pos)
                {
                    occupied_seats = AmountOfOccupiedLineOfSightSeats(temp_two, y_pos, x_pos);

                    if (('L' == temp_two[y_pos][x_pos]) && (0 == occupied_seats))
                    {
                        temp_one[y_pos][x_pos] = '#';
                    }
                    else if (('#' == temp_two[y_pos][x_pos]) && (5 <= occupied_seats))
                    {
                        temp_one[y_pos][x_pos] = 'L';
                    }
                    else
                    {
                        temp_one[y_pos][x_pos] = temp_two[y_pos][x_pos];
                    }
                }
            }
            toggle = 0;
        }
        check = TwoArrsEqual(temp_one, temp_two);
    }

    occupied_seats = OccupiedSeatsAmount(temp_one);

    return (occupied_seats);
}

int AmountOfOccupiedLineOfSightSeats(char arr[ARRAY_SIZE][LENGTH],
                                                int y_pos, int x_pos)
{
    int amount = 0;

    if ((x_pos == 0) || (x_pos == LENGTH - 2) || (y_pos == 0) || (y_pos == ARRAY_SIZE - 1))
    {
        amount = AmountNearEdges(arr, y_pos, x_pos);
        return (amount);
    }

    amount += CheckRight(arr, y_pos, x_pos);
    amount += CheckDownRight(arr, y_pos, x_pos);
    amount += CheckDown(arr, y_pos, x_pos);
    amount += CheckDownLeft(arr, y_pos, x_pos);
    amount += CheckLeft(arr, y_pos, x_pos);
    amount += CheckUpLeft(arr, y_pos, x_pos);
    amount += CheckUp(arr, y_pos, x_pos);
    amount += CheckUpRight(arr, y_pos, x_pos);

    return (amount);
}

int AmountNearEdges(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int amount = 0;

    /* Top Left Corner */
    if ((0 == x_pos) && (0 == y_pos))
    {
        amount += CheckRight(arr, y_pos, x_pos);
        amount += CheckDownRight(arr, y_pos, x_pos);
        amount += CheckDown(arr, y_pos, x_pos);
    }

    /* Top Right Corner */
    else if ((LENGTH - 2 == x_pos) && (0 == y_pos))
    {
        amount += CheckLeft(arr, y_pos, x_pos);
        amount += CheckDownLeft(arr, y_pos, x_pos);
        amount += CheckDown(arr, y_pos, x_pos);
    }

    /* Buttom Left Corner */
    else if ((0 == x_pos) && (ARRAY_SIZE - 1 == y_pos))
    {
        amount += CheckRight(arr, y_pos, x_pos);
        amount += CheckUpRight(arr, y_pos, x_pos);
        amount += CheckUp(arr, y_pos, x_pos);
    }

    /* Buttom Right Corner */
    else if ((LENGTH - 2 == x_pos) && (ARRAY_SIZE - 1 == y_pos))
    {
        amount += CheckLeft(arr, y_pos, x_pos);
        amount += CheckUpLeft(arr, y_pos, x_pos);
        amount += CheckUp(arr, y_pos, x_pos);
    }

    /* Top Edge */
    else if (0 == y_pos)
    {
        amount += CheckRight(arr, y_pos, x_pos);
        amount += CheckDownRight(arr, y_pos, x_pos);
        amount += CheckDown(arr, y_pos, x_pos);
        amount += CheckDownLeft(arr, y_pos, x_pos);
        amount += CheckLeft(arr, y_pos, x_pos);
    }

    /* Buttom Edge */
    else if (ARRAY_SIZE - 1 == y_pos)
    {
        amount += CheckRight(arr, y_pos, x_pos);
        amount += CheckUpRight(arr, y_pos, x_pos);
        amount += CheckUp(arr, y_pos, x_pos);
        amount += CheckUpLeft(arr, y_pos, x_pos);
        amount += CheckLeft(arr, y_pos, x_pos);
    }

    /* Left Edge */
    else if (0 == x_pos)
    {
        amount += CheckUp(arr, y_pos, x_pos);
        amount += CheckUpRight(arr, y_pos, x_pos);
        amount += CheckRight(arr, y_pos, x_pos);
        amount += CheckDownRight(arr, y_pos, x_pos);
        amount += CheckDown(arr, y_pos, x_pos);
    }

    /* Right Edge */
    else if (LENGTH - 2 == x_pos)
    {
        amount += CheckUp(arr, y_pos, x_pos);
        amount += CheckUpLeft(arr, y_pos, x_pos);
        amount += CheckLeft(arr, y_pos, x_pos);
        amount += CheckDownLeft(arr, y_pos, x_pos);
        amount += CheckDown(arr, y_pos, x_pos);
    }

    return (amount);
}

int CheckRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int right = 0;

    if (LENGTH - 2 == x_pos)
    {
        return (0);
    }

    for (right = x_pos + 1; right < LENGTH - 1; ++right)
    {
        if ('#' == arr[y_pos][right])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[y_pos][right])
        {
            return (0); /* Empty seat */
        }
    }

    return (0);
}

int CheckDownRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int down = y_pos + 1;
    int right = x_pos + 1;

    if ((LENGTH - 2 == x_pos) || (ARRAY_SIZE - 1 == y_pos))
    {
        return (0);
    }

    while (down < ARRAY_SIZE && right < LENGTH - 1)
    {
        if ('#' == arr[down][right])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[down][right])
        {
            return (0); /* Empty seat */
        }

        ++down;
        ++right;
    }

    return (0);
}

int CheckDown(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int down = 0;

    if (ARRAY_SIZE - 1 == y_pos)
    {
        return (0);
    }

    for (down = y_pos + 1; down < ARRAY_SIZE; ++down)
    {
        if ('#' == arr[down][x_pos])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[down][x_pos])
        {
            return (0); /* Empty seat */
        }
    }

    return (0);
}

int CheckDownLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int down = y_pos + 1;
    int left = x_pos - 1;

    if ((0 == x_pos) || (ARRAY_SIZE - 1 == y_pos))
    {
        return (0);
    }

    while (down < ARRAY_SIZE && left >= 0)
    {
        if ('#' == arr[down][left])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[down][left])
        {
            return (0); /* Empty seat */
        }

        ++down;
        --left;
    }

    return (0);
}

int CheckLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int left = 0;

    if (0 == x_pos)
    {
        return (0);
    }

    for (left = x_pos - 1; left >= 0; --left)
    {
        if ('#' == arr[y_pos][left])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[y_pos][left])
        {
            return (0); /* Empty seat */
        }
    }

    return (0);
}

int CheckUpLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int up = y_pos - 1;
    int left = x_pos - 1;

    if ((0 == x_pos) || 0 == y_pos)
    {
        return (0);
    }

    while (up >= 0 && left >= 0)
    {
        if ('#' == arr[up][left])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[up][left])
        {
            return (0); /* Empty seat */
        }

        --up;
        --left;
    }

    return (0);
}

int CheckUp(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int up = 0;

    if (0 == y_pos)
    {
        return (0);
    }

    for (up = y_pos - 1; up >= 0; --up)
    {
        if ('#' == arr[up][x_pos])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[up][x_pos])
        {
            return (0); /* Empty seat */
        }
    }

    return (0);
}

int CheckUpRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos)
{
    int up = y_pos - 1;
    int right = x_pos + 1;

    if ((LENGTH - 1 == x_pos) || (0 == y_pos))
    {
        return (0);
    }

    while (up >= 0 && right < LENGTH - 1)
    {
        if ('#' == arr[up][right])
        {
            return (1); /* Occupied seat */
        }
        else if ('L' == arr[up][right])
        {
            return (0); /* Empty seat */
        }
        --up;
        ++right;
    }

    return (0);
}

