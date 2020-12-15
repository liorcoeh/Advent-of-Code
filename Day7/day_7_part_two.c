
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_AMOUNT (22)
#define LENGTH (255)

typedef struct BAGS
{
    int amount;
    char bag_name[20];
} bags;

void GettingInfo(char arr[STRING_AMOUNT][LENGTH]);
void BagInfo(char *rule, bags *bag_info);

int main ()
{
    int i = 0;
    char info[STRING_AMOUNT][LENGTH];

    GettingInfo(info);

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        printf("%s\n", info[i]);
    }

    return (0);
}

void BagInfo(char *rule, bags *bag_info)
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
            bag_info->amount = atoi(rule + i);
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

void GettingInfo(char arr[STRING_AMOUNT][LENGTH])
{
    int index = 0;
    int i = 0;
    char c = 0;
    char buffer[LENGTH] = {0};
    int counter = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("relevant.txt", "r")))
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