#include <stdio.h>
#include <stdlib.h>

#include "list_general_funcs.h"
#include "list_structs.h"
#include "list_help_funcs.h"
#include "list_macros.h"

extern FILE* logfileList;

int ListCtor(List* list, size_t numOfElems)
{
    if (numOfElems == 0)
    {
        PRINT_LOG_FILE_LIST("ERROR: Volume of list must be at least 1 !\n");
        return BAD_NUM_OF_ELEMS;
    }

    list->numOfElems = numOfElems;
    list->elemCounter = 0;
    list->data = (int*)calloc(numOfElems + 1, sizeof(int));
    list->links = (Links*)calloc(numOfElems + 1, sizeof(Links));

    if (list->links == NULL || list->data == NULL)
    {
        PRINT_LOG_FILE_LIST("ERROR: An error was occurred while creating array of links or data!\n");

        if (list->links == NULL && list->data == NULL)
        {
            return NULL_DATA_POINTER | NULL_LINKS_POINTER;
        }
        if (list->links == NULL)
        {
            return NULL_LINKS_POINTER;
        }
        return NULL_DATA_POINTER;
    }

    ListSetFree(list, 1);
    ListSetNext(list, 0, 0);
    ListSetPrev(list, 0, 0);

    for (size_t i = 1; i < numOfElems; i++)
    {
        ListSetNext(list, i, i + 1);
        ListSetPrev(list, i, -1);
    }

    ListSetNext(list, numOfElems, 0);
    ListSetPrev(list, numOfElems, -1);

    return LIST_OK;
}

RetAndErrors ListInsertBefore(List* list, int index, int elem)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        ListDump(list, __func__);
        return {-1, errors};
    }

    if (ListGetNumOfElems(list) == ListGetElemCounter(list))
    {
        PRINT_LOG_FILE_LIST("ERROR: List is full. Action canceled.\n");
        return {-1, FULL_LIST};
    }

    int gotPrev = ListGetPrev(list, index);
    if (gotPrev == -1)
    {
        return {-1, BAD_INDEX};
    }

    int tempFree = ListGetFree(list);

    ListSetFree(list, ListGetNext(list, tempFree));
    ListSetPrev(list, tempFree, gotPrev);
    ListSetPrev(list, index, tempFree);
    ListSetNext(list, tempFree, ListGetNext(list, gotPrev));
    ListSetNext(list, gotPrev, tempFree);
    ListIncrementElemCounter(list);

    return {tempFree, LIST_OK};
}

RetAndErrors ListInsertAfter(List* list, int index, int elem)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        ListDump(list, __func__);
        return {-1, errors};
    }

    if (ListGetNumOfElems(list) == ListGetElemCounter(list))
    {
        PRINT_LOG_FILE_LIST("ERROR: List is full. Action canceled.\n");
        return {-1, FULL_LIST};
    }

    int gotNext = ListGetNext(list, index);
    if (gotNext == -1)
    {
        return {-1, BAD_INDEX};
    }

    int tempFree = ListGetFree(list);

    ListSetFree(list, ListGetNext(list, tempFree));
    ListSetNext(list, tempFree, gotNext);
    ListSetNext(list, index, tempFree);
    ListSetPrev(list, tempFree, ListGetPrev(list, gotNext));
    ListSetPrev(list, gotNext, tempFree);
    ListIncrementElemCounter(list);

    return {tempFree, LIST_OK};
}

int ListVerify(List* list)
{
    int errors = LIST_OK;

    if (list == NULL)
    {
        return NULL_LIST_POINTER;
    }

    if (list->data == NULL)
    {
        errors |= NULL_DATA_POINTER;
    }

    if (list->links == NULL)
    {
        errors |= NULL_LINKS_POINTER;
    }

    if (list->numOfElems == 0)
    {
        errors |= BAD_NUM_OF_ELEMS;
    }

    if (list->numOfElems < list->elemCounter)
    {
        errors |= BAD_ELEM_COUNTER;
    }

    if (ListCheckNext(list))
    {
        errors |= BAD_NEXT;
    }

    if (ListCheckPrev(list))
    {
        errors |= BAD_PREV;
    }

    return errors;
}

