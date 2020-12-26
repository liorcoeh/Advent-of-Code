
#include "day_14.h"

int main()
{
    int masks[MASK_ARRAY_SIZE][MASK_LENGTH] = {0};

    Mem mem[MEM_ARRAY_SIZE] = {0};

    GettingInfo("initialization_program.txt", masks, mem);
    // PrintInfo(masks, mem);

    //printf("The answer to part One is: %ld\n", PartOneFunction(masks, mem));

    PartTwoFunction(masks, mem);

    return (0);
}

// min = 691897337
// max = 68273897275
// amount = 13303