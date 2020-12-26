
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Function(int starting_numbers[], int size, int number_requasted);

int main()
{
    int starting_numbers[7] = {5, 2, 8, 16, 18, 0, 1};
    int size = 7;
    int number_requasted_part_one = 2020;
    int number_requasted_part_two = 30000000;

    printf("The answer to part One is: ");
    printf("%d\n", Function(starting_numbers, size, number_requasted_part_one));

    printf("The answer to part Two is: ");
    printf("%d\n", Function(starting_numbers, size, number_requasted_part_two));

    return (0);
}

int Function(int starting_numbers[], int size, int number_requasted)
{
    int* counting_arr = (int*)calloc(number_requasted + 1, sizeof(int));
    int i = 0;
    int turn = 1;
    int previous_turn = 0;
    int next_num = 0;
    int status_of_next_num = 0;
    int num = 0;

    for (i = 0; i < size; ++i)
    {
        next_num = starting_numbers[i];
        status_of_next_num = counting_arr[next_num];
        num = next_num;
        counting_arr[num] = turn;
        ++turn;
    }

    for (i = size; i < number_requasted; ++i)
    {
        if (0 == status_of_next_num)
        {
            next_num = 0;
        }
        else
        {
            next_num = turn - previous_turn - 1;
        }

        status_of_next_num = counting_arr[next_num];
        num = next_num;
        previous_turn = counting_arr[num];
        counting_arr[num] = turn;
        ++turn;
    }    

    return (num);
}