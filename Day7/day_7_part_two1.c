
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_AMOUNT (594)
#define LENGTH (255)

#define SIZE (22)

void GettingInfo(char arr[STRING_AMOUNT][LENGTH]);
int TheRule(char arr[STRING_AMOUNT][LENGTH], char *bag_name, char *rule);
void TheBagName(char *rule, char names[4][20], int *num_of_begs);

int Total(char arr[STRING_AMOUNT][LENGTH], char *bag_name);
void RecuTotal(char arr[STRING_AMOUNT][LENGTH], char *bag_name, char *rule, char names[4][20], int *num_of_bags);

int main()
{
    char part_two_arr[STRING_AMOUNT][LENGTH];
    char *bag_name = "shiny gold";

    char names[4][20];
    int num_of_begs = 0;

    char rule[LENGTH];

    GettingInfo(part_two_arr);

    //printf("%d\n", Total(part_two_arr, bag_name));

    return (0);
}

int Total(char arr[STRING_AMOUNT][LENGTH], char *bag_name)
{
    int num_of_bags = 0;
    char names[4][20];
    char rule[LENGTH];

    RecuTotal(arr, bag_name, rule, names, &num_of_bags);

    return (num_of_bags);
}

void RecuTotal(char arr[STRING_AMOUNT][LENGTH], char *bag_name, char *rule, char names[4][20], int *num_of_bags)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        if (1 == TheRule(arr, bag_name, rule))
        {
            TheBagName(rule, names, num_of_bags);
            for (j = 0; j < 4; ++j)
            {
                RecuTotal(arr, names[j], rule, names, num_of_bags);
            }
            i = STRING_AMOUNT;
        }
    }
}

void TheBagName(char *rule, char names[4][20], int *num_of_bags)
{
    int index = 0;
    int i = 0;
    int j = 0;
    char buffer[20] = {0};
    int count = 0;

    while (*(rule + i))
    {
        if (('1' <= *(rule + i)) && ('9' >= *(rule + i)))
        {
            *(num_of_bags) += atoi(rule + i);
            i += 2;
            memset(buffer, 0, 20);
            j = 0;

            while (2 > count)
            {
                if (' ' == *(rule + i))
                {
                    ++count;
                    if (2 == count)
                    {
                        break;
                    }
                }
                *(buffer + j) = *(rule + i);
                ++i;
                ++j;
            }

            memcpy(names[index], buffer, strlen(buffer));
            ++index;
            count = 0;
        }
        ++i;
    }
}

int TheRule(char arr[STRING_AMOUNT][LENGTH], char *bag_name, char *rule)
{
    int index = 0;
    int i = 0;
    char *temp = NULL;
    char buffer[20] = {0};
    int count = 0;

    for (index = 0; index < STRING_AMOUNT; ++index)
    {
        if (NULL != strstr(arr[index], bag_name))
        {
            memset(buffer, 0, 20);
            temp = arr[index];
            i = 0;

            while (2 > count)
            {
                if (' ' == *(temp + i))
                {
                    ++count;
                    if (2 == count)
                    {
                        break;
                    }
                }

                *(buffer + i) = *(temp + i);
                ++i;
            }

            count = 0;

            if (0 == strcmp(buffer, bag_name))
            {
                memcpy(rule, temp, strlen(temp));
                return (1); /* True */
            }
        }
    }
    return (0);
}

void GettingInfo(char arr[STRING_AMOUNT][LENGTH])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char buffer[LENGTH] = {0};
    int counter = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("rules_for_bags.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' != c)
        {
            *(buffer + i) = c;
            ++i;
            ++counter;
        }
        else
        {
            memcpy(arr[index], buffer, counter + 1);
            memset(buffer, 0, counter + i);
            ++index;
            i = 0;
            counter = 0;
        }

    }

    memcpy(arr[index], buffer, counter + 1);

    fclose(fptr);
}