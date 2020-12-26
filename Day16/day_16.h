#ifndef DAY_16_H
#define DAY_16_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VALID_NUMBERS
{
    int class_num;
    int low_low;
    int low_high;
    int high_low;
    int high_high;
} Valid_Nums;

/***************************** GENERAL FUNCTIONS ******************************/


/**************************** PART ONE FUNCTIONS ******************************/

/* The main function for part one - will give the answer */
int PartOneFunction(Valid_Nums valid_nums[], int tickets_info[][20], int indexs[]);


void GettingInfo(char* file_name, Valid_Nums valid_nums[], int tickets_info[][20]);

void ArrangeValidNums(Valid_Nums valid_nums[], int temp_valid_nums[]);

void FullRange(Valid_Nums valid_nums[], int* low, int* high);

void PrintInfo(Valid_Nums valid_nums[], int tickets_info[][20]);

/**************************** PART TWO FUNCTIONS ******************************/

void CheckFields(int valid_tickets[][20], Valid_Nums valid_nums[]);

void GetValidTickets(int tickets_info[][20], int indexs[], int valid_tickets[][20]);

#endif /* DAY_16_H */