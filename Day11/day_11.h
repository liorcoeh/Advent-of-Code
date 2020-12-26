#ifndef DAY_11_H
#define DAY_11_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (90)
#define LENGTH (100)

/***************************** GENERAL FUNCTIONS ******************************/

void GettingInfo(char arr[ARRAY_SIZE][LENGTH]);
void PrintInfo(char arr[ARRAY_SIZE][LENGTH]);

/* Checking if two arrays are equal */
int TwoArrsEqual(char arr_one[ARRAY_SIZE][LENGTH],
                                char arr_two[ARRAY_SIZE][LENGTH]);

/* Getting the amount of occupied seats (amount of '#' in the array) */
int OccupiedSeatsAmount(char arr[ARRAY_SIZE][LENGTH]);


/**************************** PART ONE FUNCTIONS ******************************/

/* The main function for part one - will give the answer */
int PartOneFunction(char arr[ARRAY_SIZE][LENGTH]);

/* Checks how many occupied seats are around a given seat */
int AmountOfOccupiedAdjacentSeats(char arr[ARRAY_SIZE][LENGTH],
                                                int y_pos, int x_pos);

/* Checks how many occupied seats are around a given seat nead the edges */
int AmountEdges(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);


/**************************** PART TWO FUNCTIONS ******************************/

/* The main function for part two - will give the answer */
int PartTwoFunction(char arr[ARRAY_SIZE][LENGTH]);

/* Checks how many occupied seats are within the lines of sight of a given */
/* seat */
int AmountOfOccupiedLineOfSightSeats(char arr[ARRAY_SIZE][LENGTH],
                                                int y_pos, int x_pos);

/* Checks how many occupied seats are within the lines of sight of a given */
/* seat nead the edges */
int AmountNearEdges(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);

/* Functions to check the status of the first seat in the line of sight */
int CheckRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckDownRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckDown(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckDownLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckUpLeft(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckUp(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);
int CheckUpRight(char arr[ARRAY_SIZE][LENGTH], int y_pos, int x_pos);

#endif /* DAY_11_H */