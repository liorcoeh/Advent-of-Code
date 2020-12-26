
#include "day_12.h"

#define ARRAY_SIZE (774)
//#define ARRAY_SIZE (5) /* For testing */

int main()
{
    char directions[ARRAY_SIZE][LENGTH];
    int amount[ARRAY_SIZE] = {0};

    GettingInfo("navigation.txt", directions, amount, ARRAY_SIZE);
    //GettingInfo("test.txt", directions, amount, ARRAY_SIZE);
    //PrintInfo(directions, amount, ARRAY_SIZE);

    printf("The answer for part One is: %d\n", PartOneFunction(directions, amount, ARRAY_SIZE));

    printf("The answer for part Two is: %d\n", PartTwoFunction(directions, amount, ARRAY_SIZE));

    return (0);
}