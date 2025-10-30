#include <stdio.h>
#include <stdlib.h>

#include "list_help_funcs.h"
#include "list_structs.h"
#include "list_setters_and_getters.h"
#include "list_macros.h"

extern FILE* logfileList;

int ListCheckNext(List* list)
{
    int tempElemCounter = 0;
    for (int i = ListGetHead(list); i != 0; i = ListGetNext(list, i))
    {
        tempElemCounter++;
    }

    if (tempElemCounter != ListGetElemCounter(list))
    {
        return 1;
    }

    return 0;
}

int ListCheckPrev(List* list)
{
    int tempElemCounter = 0;
    for (int i = ListGetTail(list); i != 0; i = ListGetPrev(list, i))
    {
        tempElemCounter++;
    }

    if (tempElemCounter != ListGetElemCounter(list))
    {
        return 1;
    }

    return 0;
}

int OpenLogfileList()
{
    logfileList = fopen(LOG_FILE_NAME_LIST, "w");
    if (logfileList == NULL)
    {
        printf("ERROR: An error occurred while opening logfileList.\n");
        return 1;
    }

    return 0;
}
