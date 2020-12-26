
#include "day_13.h"

#define ARRAY_SIZE (9)
//#define ARRAY_SIZE (4) /* For testing */

/* #define PART_ONE */
#define PART_TWO

int main()
{
    #ifdef PART_ONE
    int time_stamp = 1002392;
    int buses[] = {13, 17, 19, 23, 29, 37, 41, 421, 487};

    // int time_stamp = 939;
    // int buses[] = {7, 13, 59, 31, 19};

    printf("The answer to part One is: %d\n", PartOneFunction(time_stamp, buses, ARRAY_SIZE));

    #endif /* PART_ONE */


    #ifdef PART_TWO
    size_t buses_part_two[ARRAY_SIZE] = {0};
    size_t minutes[ARRAY_SIZE] = {0};

    GettingInfo("notes_part_two.txt", buses_part_two, minutes, ARRAY_SIZE);
    // PrintInfo(buses_part_two, minutes, ARRAY_SIZE);

    printf("The answer to part Two is: %ld\n", PartTwoFunction(buses_part_two, minutes, ARRAY_SIZE));

    #endif /* PART_TWO */

    return (0);
}
