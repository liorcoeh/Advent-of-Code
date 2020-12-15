
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_AMOUNT (594)
#define STRING_LENGTH (255)

char new_arr[624][STRING_LENGTH];
int m_index = 0;


void GettingInfo(char arr[STRING_AMOUNT][STRING_LENGTH]);
void PrintStrings(char arr[STRING_AMOUNT][STRING_LENGTH]);
void GetShinyGoldBags(char arr[STRING_AMOUNT][STRING_LENGTH], char shiny_gold_bag_arr[10][STRING_LENGTH]);

int AmountOfBag(char *bag_name, char arr[STRING_AMOUNT][STRING_LENGTH]);

void ContainerBag(char *rule, char *holding_bag);
int IsRule(char *rule, char *bag_name);

int Total(char arr[STRING_AMOUNT][STRING_LENGTH], char *bag_name);
int RecuTotal(char arr[STRING_AMOUNT][STRING_LENGTH], char *bag_name, int *total);

int RemoveDuplicates(char arr[][STRING_LENGTH]);

int main()
{
    int total = 0;
    int duplicates = 0;
    int i = 0;

    char part_one_arr[STRING_AMOUNT][STRING_LENGTH];
    char *bag_name = "shiny gold";

    GettingInfo(part_one_arr);
    //PrintStrings(part_one_arr);

    total = Total(part_one_arr, bag_name);
    duplicates = RemoveDuplicates(new_arr);
    
    printf("The answer is: %d\n", total - duplicates);

    return (0);
}

int RemoveDuplicates(char arr[][STRING_LENGTH])
{
    int i = 0;
    int j = 0;
    int amount = 0;

    for (i = 0; i < 623; ++i)
    {
        for (j = i + 1; j < 624; ++j)
        {
            if ((0 != arr[i]) && (0 == strcmp(arr[i], arr[j])))
            {
                memset(arr[j], 0, strlen(arr[i]));
            }
        }
    }

    for (i = 0; i < 624; ++i)
    {
        if (0 == strlen(new_arr[i]))
        {
            ++amount;
        }       
    }

    return (amount);
}

int Total(char arr[STRING_AMOUNT][STRING_LENGTH], char *bag_name)
{
    int total = 0;

    RecuTotal(arr, bag_name, &total);

    return (total);
}

int RecuTotal(char arr[STRING_AMOUNT][STRING_LENGTH], char *bag_name, int *total)
{
    int i = 0;
    char name[20] = {0};

    //printf("%s\n", bag_name);
    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        if (1 == IsRule(arr[i], bag_name))
        {
            memcpy(new_arr[m_index], arr[i], strlen(arr[i]));
            ++m_index;
            ++(*total);
            memset(name, 0, 20);
            ContainerBag(arr[i], name);
            //printf("%s=> %s, %s\n", arr[i], bag_name, name);
            //printf("%d ==> %s, %s\n", i, bag_name, name);
            RecuTotal(arr, name, total);
        }
    };
}

int IsRule(char *rule, char *bag_name)
{
    int i = 0;
    char buffer[20] = {0};
    int count = 0;
    
    if (NULL != strstr(rule, bag_name))
    {
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

            *(buffer + i) = *(rule + i);
            ++i;
        }

        /* Only if the bag name is not at the beggining of the rule */
        /* If it is not  the container itself */
        if (0 != strcmp(buffer, bag_name))
        {
            return (1); /* True */
        }
    }

    return (0);
}

int AmountOfBag(char *bag_name, char arr[STRING_AMOUNT][STRING_LENGTH])
{
    int i = 0;
    int index = 0;
    int amount = 0;

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        if (NULL != strstr(arr[i], bag_name))
        {
            ++amount;
            ++index;
        }
    }

    return (amount);
}

void ContainerBag(char *rule, char *holding_bag)
{
    int count = 0;
    int i = 0;
    
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

        *(holding_bag + i) = *(rule + i);
        ++i;
    }

    //printf("%s", holding_bag);
}

void GetShinyGoldBags(char arr[STRING_AMOUNT][STRING_LENGTH], char shiny_gold_bag_arr[10][STRING_LENGTH])
{
    int i = 0;
    int length = 0;
    int index = 0;
    char buffer = STRING_LENGTH;
    char *str = "shiny gold bag";

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        if (NULL != strstr(arr[i], str))
        {
            length = strlen(arr[i]);
            memcpy(shiny_gold_bag_arr[index], arr[i], length);
            ++index;
        }
    }

    for (i = 0; i < 10; ++i)
    {
        printf("%s\n", shiny_gold_bag_arr[i]);
    }
}

void GettingInfo(char arr[STRING_AMOUNT][STRING_LENGTH])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char buffer[STRING_LENGTH] = {0};
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

void PrintStrings(char arr[STRING_AMOUNT][STRING_LENGTH])
{
    int i = 0;

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        printf("%s\n", arr[i]);
    }
}