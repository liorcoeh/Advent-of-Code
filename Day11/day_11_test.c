
#include "day_11.h"

int main()
{
    char seats[ARRAY_SIZE][LENGTH];

    GettingInfo(seats);
    //PrintInfo(seats);

    //printf("The answer to part ONE is: %d\n", PartOneFunction(seats));
    printf("The answer to part Two is: %d\n", PartTwoFunction(seats));

    return (0);
}

