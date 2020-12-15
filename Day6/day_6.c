
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_AMOUNT (454)
#define STRING_SIZE (150)

void GettingInfoPartOne(char arr[STRING_AMOUNT][STRING_SIZE]);
int NumOfYes(char *str);
int TotalYes(char arr[STRING_AMOUNT][STRING_SIZE]);

void PrintStrings(char arr[STRING_AMOUNT][STRING_SIZE]);

void GettingInfoPartTwo(char arr[STRING_AMOUNT][STRING_SIZE]);
int NumOfQuestions(char *str);
int TotalQuestions(char arr[STRING_AMOUNT][STRING_SIZE]);

void SortString(char *str);

int main()
{
    //char part_one_arr[STRING_AMOUNT][STRING_SIZE];
    char part_two_arr[STRING_AMOUNT][STRING_SIZE];

    //GettingInfoPartOne(part_one_arr);
    GettingInfoPartTwo(part_two_arr);

    // printf("The total number of yes is: %d\n", TotalYes(part_one_arr));
    printf("The total number of questions is: %d\n", TotalQuestions(part_two_arr));

    // PrintStrings(part_one_arr);
    // PrintStrings(part_two_arr);

    return (0);
}

int TotalQuestions(char arr[STRING_AMOUNT][STRING_SIZE])
{
    int i = 0;
    int total = 0;

    for (i = 0; i < STRING_AMOUNT - 1; ++i)
    {
        total += NumOfQuestions(arr[i]);
    }

    return (total);
}

int NumOfQuestions(char *str)
{
    int people_num = 0;
    int arr[256] = {0};
    int i = 0;
    int total = 0;

    while (*(str + i))
    {
        if (' ' == *(str + i))
        {
            ++people_num;
        }
        else
        {
            ++arr[*(str + i)];
        }
        
        ++i;
    }

    for (i = 0; i < 256; ++i)
    {
        if (people_num == arr[i])
        {
            ++total;
        }
    }

    return (total);
}

void GettingInfoPartTwo(char arr[STRING_AMOUNT][STRING_SIZE])
{
    char c = 0;
    char temp = 0;
    char buffer[STRING_SIZE] = {0};
    int index = 0;
    int i = 0;
    int counter = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("yes_answers.txt", "r")))
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
        else if ('\n' == c && ('\n' == temp))
        {
            memcpy(arr[index], buffer, counter + 1);
            memset(buffer, 0, counter + 1);
            ++index;
            i = 0;
            counter = 0;
        }
        else
        {
            *(buffer + i) = ' ';
            ++i;
            ++counter;
        }
        
        temp = c;
    }

    memcpy(arr[index], "yf qtp cfzgy lny", 16);

    fclose(fptr);
}

int TotalYes(char arr[STRING_AMOUNT][STRING_SIZE])
{
    int total = 0;
    int i = 0;

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        total += NumOfYes(arr[i]);
    }

    return (total);
}

int NumOfYes(char *str)
{
    int arr[256] = {0};
    int i = 0;

    int num = 0;

    while (*(str + i))
    {
        if (0 == arr[*(str + i)])
        {
            ++arr[*(str + i)];
        }

        ++i;
    }

    for (i = 0; i < 256; ++i)
    {
        num += arr[i];
    }

    return (num);
}

void GettingInfoPartOne(char arr[STRING_AMOUNT][STRING_SIZE])
{
    char c = 0;
    char buffer[STRING_SIZE] = {0};
    int index = 0;
    int i = 0;
    int counter = 0;
    int num_c = 0;

    int size = 0;

    FILE *fptr;

    if (NULL == (fptr = fopen("yes_answers.txt", "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    //while (EOF != (c = fgetc(fptr)))
    while (size < 453)
    {
        c = fgetc(fptr);

        if ('\n' != c)
        {
            *(buffer + i) = c;
            ++i;
            ++counter;
            num_c = 0;
        }
        else if ('\n' == c)
        {
            ++num_c;
        }

        if (2 == num_c)
        {
            memcpy(arr[index], buffer, counter + 1);
            memset(buffer, 0, counter + 1);
            ++index;
            i = 0;
            counter = 0;
            num_c = 0;
            
            ++size;
        }
    }

    memcpy(arr[index], "yfqtpcfzgylny", 13);

    fclose(fptr);
}

void PrintStrings(char arr[STRING_AMOUNT][STRING_SIZE])
{
    int i = 0;

    for (i = 0; i < STRING_AMOUNT; ++i)
    {
        printf("%s\n", arr[i]);
    }
}

void SortString(char *str)
{
    char temp;
    int i = 0;
    int j = 0;

    int n = strlen(str);

    for (i = 0; i < n - 1; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}