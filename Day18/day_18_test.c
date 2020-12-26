
#include "day_18.h"

int main()
{
    char* file_name = "expressions.txt";
    char info[ARRAY_SIZE][LENGTH];

    GettingInfo(file_name, info);
    //PrintInfo(info);  

    printf("The answer for part One is: ");
    printf("%ld\n\n", PartOneFunction(info));

    printf("The answer for part Two is: ");
    printf("%ld\n\n", PartTwoFunction(info));

    return (0);
}