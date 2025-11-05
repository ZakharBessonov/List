#include <stdio.h>
#include <stdlib.h>

#include "list_help_funcs.h"
#include "list_structs.h"
#include "list_setters_and_getters.h"
#include "list_macros.h"
#include "list_consts.h"

extern FILE* logfileList;

int ListCheckNext(List* list)
{
    int tempElemCounter = 0;
    for (int i = ListGetHead(list); i != 0 && tempElemCounter != ABS_LIMIT_OF_LEN; i = ListGetNext(list, i))
    {
        if (i < 0)
        {
            return 1;
        }
        tempElemCounter++;
    }

    if (tempElemCounter != (int)ListGetElemCounter(list))
    {
        return 1;
    }

    return 0;
}

int ListCheckPrev(List* list)
{
    int tempElemCounter = 0;
    for (int i = ListGetTail(list); i != 0 && tempElemCounter != ABS_LIMIT_OF_LEN; i = ListGetPrev(list, i))
    {
        if (i < 0)
        {
            return 1;
        }
        tempElemCounter++;
    }

    if (tempElemCounter != (int)ListGetElemCounter(list))
    {
        return 1;
    }

    return 0;
}

int OpenLogfileList()
{
    logfileList = fopen(LOG_FILE_NAME_LIST, "w");
    fprintf(logfileList, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
    fflush(logfileList);
    if (logfileList == NULL)
    {
        printf("ERROR: An error occurred while opening logfileList.\n");
        return 1;
    }

    return 0;
}

void CloseListLogfile()
{
    fclose(logfileList);
}
