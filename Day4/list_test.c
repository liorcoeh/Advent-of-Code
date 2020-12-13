

#include "list.h"

int main()
{
    List* list = ListCreate();

    char *buffer = "cid";

    ListPushAfter(list, buffer);

    buffer = "eyr";

    ListPushBefore(list, buffer);
    ListPushBefore(list, buffer);

    PrintList(list);

    printf("%s\n", ListGetFirst(list));

    ListDestroy(list);

    return (0);
}