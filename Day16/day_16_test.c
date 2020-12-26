
#include "day_16.h"

int main()
{
    char* file_name = "tickets_info.txt";
    Valid_Nums valid_nums[20] = {0};
    int tickets_info[238][20] = {0};

    /* Will be used in part two */
    int indexs[48] = {0};
    int valid_tickets[190][20] = {0};

    GettingInfo(file_name, valid_nums, tickets_info);
    //PrintInfo(valid_nums, tickets_info);
    printf("The answer to part One is: ");
    printf("%d\n", PartOneFunction(valid_nums, tickets_info, indexs));

    GetValidTickets(tickets_info, indexs, valid_tickets);

    CheckFields(valid_tickets, valid_nums);

    // 2628667251989

    return (0);
}