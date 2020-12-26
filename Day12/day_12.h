
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define  (774)
#define LENGTH (10)

//#define  (5)

typedef enum SHIP_DIRECTION
{
    EAST = 0,
    SOUTH,
    WEST,
    NORTH
} Ship_Direction;

/***************************** GENERAL FUNCTIONS ******************************/

void GettingInfo(char* file_name,
                    char arr[][LENGTH], int nums[], int array_size);
void PrintInfo(char arr[][LENGTH], int nums[], int array_size);

/* Gives the sum of the 'absolute' values of the east and north positions */
int ManhattanDistance(int east_pos, int north_pos);


/**************************** PART ONE FUNCTIONS ******************************/

/* The main function for part one - will give the answer */
int PartOneFunction(char arr[][LENGTH], int nums[], int array_size);

/* Updates the ship direction */
Ship_Direction UpdateDirection(char *turn_to, int degrees_amount,
                                            Ship_Direction *current_direction);

/* Moves the ship in the direction it is heading */
void MoveForword(int amount, Ship_Direction current_direction,
                                            int *east_pos, int *north_pos);


/**************************** PART TWO FUNCTIONS ******************************/

/* The main function for part two - will give the answer */
int PartTwoFunction(char arr[][LENGTH], int nums[], int array_size);

/* Updates the waypoint postion when the degrees change */
void UpdateWaypointAngle(char *direction, int degrees,
                                    int *wp_east_pos, int *wp_north_pos);

/* Updates the ships position */
void UpdateShipsPosition(int amount, int *ship_east_pos, int *ship_north_pos,
                                int wp_east_pos, int we_north_pos);