
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