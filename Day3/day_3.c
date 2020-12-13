/*
 * Day 3:
 * 
 * First Part:
 * You start on the open square (.) in the top-left corner and need to reach
 * the bottom (below the bottom-most num_of_string on your map).
 * 
 * The toboggan can only follow a few specific slopes (you opted for a cheaper
 * model that prefers rational numbers); start by counting all the trees you
 * would encounter for the slope right 3, down 1:
 * 
 * From your starting position at the top-left, check the position that is
 * right 3 and down 1. Then, check the position that is right 3 and down 1 from
 * there, and so on until you go past the bottom of the map.
 * 
 * The locations you'd check in the above example are marked here with O where 
 * there was an open square and X where there was a tree:
 * 
 * ..##.........##.........##.........##.........##.........##.......  --->
 * #..O#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
 * .#....X..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
 * ..#.#...#O#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
 * .#...##..#..X...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
 * ..#.##.......#.X#.......#.##.......#.##.......#.##.......#.##.....  --->
 * .#.#.#....#.#.#.#.O..#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
 * .#........#.#........X.#........#.#........#.#........#.#........#
 * #.##...#...#.##...#...#.X#...#...#.##...#...#.##...#...#.##...#...
 * #...##....##...##....##...#X....##...##....##...##....##...##....#
 * .#..#...#.#.#..#...#.#.#..#...X.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
 * 
 * In this example, traversing the map using this slope would cause you to 
 * encounter 7 trees.
 * 
 * Starting at the top-left corner of your map and following a slope of right 3 
 * and down 1, how many trees would you encounter?
 * 
 * Second Part:
 * Time to check the rest of the slopes - you need to minimize the probability 
 * of a sudden arboreal stop, after all.
 * 
 * Determine the number of trees you would encounter if, for each of the 
 * following slopes, you start at the top-left corner and traverse the map all 
 * the way to the bottom:
 * 
 * Right 1, down 1.
 * Right 3, down 1. (This is the slope you already checked.)
 * Right 5, down 1.
 * Right 7, down 1.
 * Right 1, down 2.
 * In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s) 
 * respectively; multiplied together, these produce the answer 336.
 * 
 * What do you get if you multiply together the number of trees encountered on 
 * each of the listed slopes?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_STRINGS (323)
#define STRING_SIZE (32)

void GetInfoFromFile(char arr[NUM_OF_STRINGS][STRING_SIZE]);

int AmountOfTrees(char arr[NUM_OF_STRINGS][STRING_SIZE], int right, int down);

int MultiplyTrees(char arr[NUM_OF_STRINGS][STRING_SIZE]);

int main()
{
    char map[NUM_OF_STRINGS][STRING_SIZE];

    GetInfoFromFile(map);

    printf("The amount of trees in part one is: %d\n", AmountOfTrees(map, 3, 1));
    printf("The amount of multiplied trees is: %d\n", MultiplyTrees(map));

    return (0);
}

int MultiplyTrees(char arr[NUM_OF_STRINGS][STRING_SIZE])
{
    int first_slope = AmountOfTrees(arr, 1, 1);
    int second_slope = AmountOfTrees(arr, 3, 1);
    int third_slope = AmountOfTrees(arr, 5, 1);
    int forth_slope = AmountOfTrees(arr, 7, 1);
    int fifth_slope = AmountOfTrees(arr, 1, 2);
    int multi = (first_slope * second_slope * third_slope * forth_slope * fifth_slope);

    return (multi);
}

int AmountOfTrees(char arr[NUM_OF_STRINGS][STRING_SIZE], int right, int down)
{
    int i = 0; /* Going down */
    int j = 0; /* Going right */

    int amount_of_trees = 0;

    while (i < NUM_OF_STRINGS - 1)
    {
        j += right;
        i += down;

        if (i > NUM_OF_STRINGS)
        {
            break;
        }

        if ('#' == arr[i][j])
        {
            ++amount_of_trees;
        }

        if (30 < j + right)
        {
            j = ((j + right) % 30) - (right + 1);
        }
    }

    return (amount_of_trees);
}

void GetInfoFromFile(char arr[NUM_OF_STRINGS][STRING_SIZE])
{
    int num_of_string = 0;
    int i = 0;
    char c = 0;
    FILE* fptr;

    if (NULL == (fptr = fopen("trees.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    for (num_of_string = 0; num_of_string < NUM_OF_STRINGS; ++num_of_string)
    {
        i = 0;
        while ('\n' != (c = fgetc(fptr)))
        {
            arr[num_of_string][i] = c;
            ++i;
        }
    }
    
    fclose(fptr);
}

