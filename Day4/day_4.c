
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

#define NUM_OF_LISTS (257)

void GettingTheInfo(List *arr[NUM_OF_LISTS]);
int AmountOfOKPartOne(List *arr[NUM_OF_LISTS]);
int ValidPassport(List *head);
int AmountOfOKPartTwo(List *arr[NUM_OF_LISTS]);

int main()
{
    int i = 0;
    List *main_arr[NUM_OF_LISTS];

    for (i = 0; i < NUM_OF_LISTS; ++i)
    {
        main_arr[i] = ListCreate();
    }

    GettingTheInfo(main_arr);

    printf("The amount of good passports is: %d\n\n", AmountOfOKPartOne(main_arr));

    printf("The amount of valid passports in part two is: %d\n", AmountOfOKPartTwo(main_arr));

    for (i = 0; i < NUM_OF_LISTS; ++i)
    {
        //PrintList(main_arr[i]);
        ListDestroy(main_arr[i]);
    }

    return (0);
}

int AmountOfOKPartTwo(List *arr[NUM_OF_LISTS])
{
    int amount = 0;
    int i = 0;

    for (i = 0; i < NUM_OF_LISTS - 1; ++i)
    {
        if (1 == ValidPassport(arr[i]))
        {
            ++amount;
        }
    }

    return (amount);
}

int ValidPassport(List *head)
{
    int counter = 0;
    Node* iter = ListGetNext(head);

    int check = 0;
    int i = 0;
    int temp = 0;
    int add = 0;
    char buffer[10] = {0};
    char num[4] = {0};
    char *arr[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    while (NULL != iter)
    {
        if (0 == strcmp("byr", GetKey(iter)))
        {
            temp = atoi(GetData(iter));
            

            if (1920 <= temp && 2020 >= temp)
            {
                ++counter;
            }
        }
        else if (0 == strcmp("iyr", GetKey(iter)))
        {
            temp = atoi(GetData(iter));

            if (2010 <= temp && 2020 >= temp)
            {
                ++counter;
            }
        }
        else if (0 == strcmp("eyr", GetKey(iter)))
        {
            temp = atoi(GetData(iter));

            if (2020 <= temp && 2030 >= temp)
            {
                ++counter;
            }
        }
        else if (0 == strcmp("hgt", GetKey(iter)))
        {
            strcpy(buffer, GetData(iter));

            if (5 == strlen(buffer))
            {
                memcpy(num, buffer, 3);
                add = 3;
            }
            else if (4 == strlen(buffer))
            {
                memcpy(num, buffer, 2);
                add = 2;
            }

            temp = atoi(num);
            
            for (i = 0; i < 3; ++i)
            {
                *(buffer + i) = *(buffer + i + add);
            }
            
            if (0 == strcmp("cm", buffer))
            {
                if (150 <= temp && 193 >= temp)
                {
                    ++counter;
                }
            }
            else if (0 == strcmp("in", buffer))
            {
                if (59 <= temp && 76 >= temp)
                {
                    ++counter;
                }
            }
        }
        else if (0 == strcmp("hcl", GetKey(iter)))
        {
            strcpy(buffer, GetData(iter));
            check = 1;

            if ('#' == *(buffer))
            {
                for (i = 1; i < 7; ++i)
                {
                    if ((('0' <= *(buffer + i)) && ('9' >= *(buffer + i))) || 
                    (('a' <= *(buffer + i)) && ('f' >= *(buffer + i))))
                    {
                        check = 0;
                    }
                    else
                    {
                        check = 1;
                    }
                    
                    if (1 == check)
                    {
                        break;
                    }
                }
            }

            if (0 == check)
            {
                ++counter;
            }
        }
        else if (0 == strcmp("ecl", GetKey(iter)))
        {
            strcpy(buffer, GetData(iter));

            for (i = 0; i < 7; ++i)
            {
                if (0 == strcmp(arr[i], buffer))
                {
                    ++counter;
                    break;
                }
            }
        }
        else if (0 == strcmp("pid", GetKey(iter)))
        {
            strcpy(buffer, GetData(iter));
            check = 1;

            if (9 == strlen(buffer))
            {
                for (i = 0; i < 9; ++i)
                {
                    if (('0' <= *(buffer + i)) && ('9' >= *(buffer + i)))
                    {
                        check = 0;
                    }
                    else
                    {
                        check = 1;
                    }

                    if (1 == check)
                    {
                        break;
                    }
                }
            }

            if (0 == check)
            {
                ++counter;
            }
        }

        iter = GetNext(iter);
    }

    if (7 == counter)
    {
        return (1); /* True */
    }
    else
    {
        return (0); /* False */
    }
    
}

// byr (Birth Year) - four digits; at least 1920 and at most 2002.
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
// hgt (Height) - a number followed by either cm or in:
// If cm, the number must be at least 150 and at most 193.
// If in, the number must be at least 59 and at most 76.
// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
// pid (Passport ID) - a nine-digit number, including leading zeroes.
// cid (Country ID) - ignored, missing or not.

int AmountOfOKPartOne(List *arr[NUM_OF_LISTS])
{
    int i = 0;
    int amount = 0;

    for (i = 0; i < NUM_OF_LISTS; ++i)
    {
        if (8 == ListSize(arr[i]))
        {
            ++amount;
        }
        else if (7 == ListSize(arr[i]) && (0 != strcmp("cid", ListGetFirst(arr[i]))))
        {
            ++amount;
        }
        else
        {
            ;
        }  
    }

    return (amount);
}

void GettingTheInfo(List *arr[NUM_OF_LISTS])
{
    FILE* fptr;
    char c = 'a';

    char buffer[4] = {0};
    char content[10] = {0};

    int i = 0;
    int arr_index = 0;

    if (NULL == (fptr = fopen("passports.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (EOF != (c = fgetc(fptr)))
    {
        memset(content, 0, 10);

        i = 0;
        *(buffer + i) = c;

        for (i = 1; i < 3; ++i)
        {
            if ('\n' == c)
            {
                --i;
                ++arr_index;
            }
            c = fgetc(fptr);
            *(buffer + i) = c;
        }

        i = 0;
        while (('\n' != (c = fgetc(fptr))) && (' ' != c))
        {
            if (':' != c)
            {
                *(content + i) = c;
                ++i;
            }
        }

        if (0 == strcmp("cid", buffer))
        {
            ListPushBefore(arr[arr_index], buffer, content);
        }
        else
        {
            ListPushAfter(arr[arr_index], buffer, content);
        }
    } 

    fclose(fptr);
}