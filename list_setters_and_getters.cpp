#include <stdio.h>
#include <stdlib.h>

#include "list_structs.h"
#include "list_setters_and_getters.h"
#include "list_macros.h"

extern FILE* logfileList;

static int ListCheckIndex(List* list, int index)
{
    return (index < 0 || index > list->numOfElems);
}

// Getters

RetAndErrors GetData(List* list, int index)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Data index out of range!\n");
        return {-1, BAD_INDEX};
    }

    return {list->data[index], LIST_OK};
}

int ListGetNext(List* list, int index)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Next index out of range!\n");
        return -1;
    }

    return list->links[index]->next;
}

int ListGetPrev(List* list, int index)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Prev index out of range!\n");
        return -1;
    }

    return list->links[index]->prev;
}

int ListGetFree(List* list)
{
    return list->free;
}

int ListGetHead(List* list)
{
    return list->links[0]->next;
}

int ListGetTail(List* list)
{
    return list->links[0]->prev;
}

int ListGetFileCounter(List* list)
{
    return list->fileCounter;
}

size_t ListGetNumOfElems(List* list)
{
    return list->numOfElems;
}

size_t ListGetElemCounter(List* list)
{
    return list->elemCounter;
}

// Setters

int ListSetData(List* list, int index, int value)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Data index out of range!\n");
        return 1;
    }

    list->data[index] = value;
    return 0;
}

int ListSetNext(List* list, int index, int value)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Next index out of range!\n");
        return 1;
    }

    list->links[index]->next = value;
    return 0;
}

int ListSetPrev(List* list, int index, int value)
{
    if (ListCheckIndex(list, index))
    {
        PRINT_LOG_FILE_LIST("ERROR: Prev index out of range!\n");
        return 1;
    }

    list->links[index]->prev = value;
    return 0;
}

int ListSetFree(List* list, int value)
{
    if (ListCheckIndex(list, value))
    {
        PRINT_LOG_FILE_LIST("ERROR: Free index out of range!\n");
        return 1;
    }

    list->free = value;
    return 0;
}

size_t ListIncrementElemCounter(List* list)
{
    return list->elemCounter++;
}

int ListIncrementFileCounter(List* list)
{
    return list->fileCounter++;
}
