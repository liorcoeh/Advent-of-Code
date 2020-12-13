/*
 * Day 2:
 * 
 * First Part:
 * Find how many passwords are correct in the list of password given in
 * the file.
 * Each line gives the password policy and then the password. The
 * password policy indicates the lowest and highest number of times a
 * given letter must appear for the password to be valid. For example, 
 * 1-3 a means that the password must contain a at least 1 time and at
 * most 3 times.
 * 
 * Example:
 * 
 * The list of given passwords is -
 * 1-3 a: abcde
 * 1-3 b: cdefg
 * 2-9 c: ccccccccc
 * 
 * In the above example, 2 passwords are valid. The middle password, cdefg,
 * is not; it contains no instances of b, but needs at least 1.
 * The first and third passwords are valid: they contain one a or nine c,
 * both within the limits of their respective policies.
 * 
 * 
 * Second Part:
 * Each policy actually describes two positions in the password, where 1 means
 * the first character, 2 means the second character, and so on. (Be careful;
 * Toboggan Corporate Policies have no concept of "index zero"!) Exactly one of
 * these positions must contain the given letter. Other occurrences of the
 * letter are irrelevant for the purposes of policy enforcement.
 * Given the same example list from above:
 * 
 * 1-3 a: abcde is valid: position 1 contains a and position 3 does not.
 * 1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
 * 2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
 * How many passwords are valid according to the new interpretation of the
 * policies?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GettingALine(FILE* fptr, int *min, int *max, char* letter, char *password);
int CountingAmountPartOne();
int CountingAmountPartTwo();

int main()
{
    //printf("The amount of right passwords is: %d\n", CountingAmountPartOne());
    printf("The amount of right passwords is: %d\n", CountingAmountPartTwo());

    return (0);
}

int CountingAmountPartTwo()
{
    int total_amount = 0;
    int i = 0; int j = 0;
    int counter = 0;
    int min = 0;
    int max = 0;
    int check = 0;

    char letter[1] = {0};
    char password[50] = {0};

    FILE *fptr;

    if (NULL == (fptr = fopen("passwords.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (j < 1000)
    {
        counter = 0;
        min = 0;
        max = 0;
        memset(password, 0, 20);

        GettingALine(fptr, &min, &max, letter, password);

        min -= 1;
        max -= 1;

        if (((*letter == *(password + min)) && (*letter != *(password + max))) ||
            ((*letter != *(password + min)) && (*letter == *(password + max))))
        {
            ++total_amount;
        }

        ++j;
    }

    fclose(fptr);

    return (total_amount);
}

int CountingAmountPartOne()
{
    int total_amount = 0;
    int i = 0; int j = 0;
    int counter = 0;
    int min = 0;
    int max = 0;
    int check = 0;

    char letter[1] = {0};
    char password[50] = {0};

    FILE *fptr;

    if (NULL == (fptr = fopen("passwords.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (j < 1000)
    {
        counter = 0;
        min = 0;
        max = 0;
        memset(password, 0, 20);

        GettingALine(fptr, &min, &max, letter, password);

        i = 0;
        while (*(password + i))
        {
            if (*letter == *(password + i))
            {
                ++counter;
            }
            ++i;
        }

        if (counter >= min && counter <= max)
        {
            ++total_amount;
        }

        ++j;
    }

    fclose(fptr);

    return (total_amount);
}

void GettingALine(FILE* fptr, int *min, int *max, char* letter, char *password)
{
    char first_num[2] = {0};
    char second_num[2] = {0};
    int i = 0;
    char c = 0;

    while ('-' != (c = fgetc(fptr)))
    {
        first_num[i] = c;
        ++i;
    }

    *min = atoi(first_num);
    
    i = 0;
    while (' ' != (c = fgetc(fptr)))
    {
        second_num[i] = c;
        ++i;
    }

    *max = atoi(second_num);

    while (':' != (c = fgetc(fptr)))
    {
        *letter = c;
    }

    while (' ' != (c = fgetc(fptr)))
    {
        ;
    }

    i = 0;
    while ('\n' != (c = fgetc(fptr)))
    {
        *(password + i) = c;
        ++i;
    } 
}