
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************** GENERAL FUNCTIONS ******************************/


/**************************** PART ONE FUNCTIONS ******************************/

/* The main function for part one - will give the answer */
int PartOneFunction(int time_stamp, int arr[], int array_size);


/**************************** PART TWO FUNCTIONS ******************************/

/* The main function for part two - will give the answer */
size_t PartTwoFunction(size_t arr[], size_t minutes[], int array_size);

size_t GetMulti(size_t arr[], int array_size);

size_t GetEachBus(size_t multi, size_t bus_id, size_t minutes);

size_t FindFirst(size_t multi, size_t total_sum);

void GettingInfo(char* file_name, size_t arr[], size_t minutes[], int array_size);
void PrintInfo(size_t arr[], size_t minutes[], int array_size);