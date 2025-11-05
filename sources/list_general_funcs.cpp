#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_general_funcs.h"
#include "list_structs.h"
#include "list_help_funcs.h"
#include "list_macros.h"
#include "list_setters_and_getters.h"
#include "list_dump.h"
#include "list_consts.h"
#include "list_check_index.h"

extern FILE* logfileList;

int ListCtor(List* list, size_t numOfElems)
{
    if (numOfElems == 0)
    {
        PRINT_LOG_FILE_LIST("ERROR: Volume of list must be at least 1 !\n");
        return BAD_NUM_OF_ELEMS;
    }

    ListSetNumOfElements(list, numOfElems);
    ListSetElemCounter(list, 0);
    ListSetDataPt(list, (int*)calloc(numOfElems + 1, sizeof(int)));
    ListSetLinks(list, (Links*)calloc(numOfElems + 1, sizeof(Links)));

    if (ListGetLinks(list) == NULL || ListGetDataPt(list) == NULL)
    {
        PRINT_LOG_FILE_LIST("ERROR: An error was occurred while creating array of links or data!\n");

        if (ListGetLinks(list) == NULL && ListGetDataPt(list) == NULL)
        {
            return NULL_DATA_POINTER | NULL_LINKS_POINTER;
        }
        if (ListGetLinks(list) == NULL)
        {
            return NULL_LINKS_POINTER;
        }
        return NULL_DATA_POINTER;
    }

    ListSetFree(list, 1);
    ListSetNext(list, 0, 0);
    ListSetPrev(list, 0, 0);

    for (int i = 1; i < (int)numOfElems; i++)
    {
        ListSetNext(list, i, i + 1);
        ListSetPrev(list, i, -1);
    }

    ListSetNext(list, (int)numOfElems, 0);
    ListSetPrev(list, (int)numOfElems, -1);

    return LIST_OK;
}

RetAndErrors ListInsertBefore(List* list, int index, ListElem_t elem)
{
    return ListInsertAfter(list, ListGetPrev(list, index), elem);
}

RetAndErrors ListInsertAfter(List* list, int index, ListElem_t elem)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        CALL_DUMP(list, "Error!");
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

    if (ListGetPrev(list, index) == -1)
    {
        PRINT_LOG_FILE_LIST("ERROR: Trying to insert relative to non exist element. Action canceled.\n");
        return {-1, BAD_INDEX};
    }

    ListSetData(list, tempFree, elem);
    ListSetFree(list, ListGetNext(list, tempFree));

    ListSetNext(list, tempFree, gotNext);
    ListSetNext(list, index, tempFree);
    ListSetPrev(list, tempFree, ListGetPrev(list, gotNext));
    ListSetPrev(list, gotNext, tempFree);
    ListIncrementElemCounter(list);

#ifdef DEBUGMODE
    char message[MAX_SIZE_OF_MESSAGE] = "";
    snprintf(message, MAX_SIZE_OF_MESSAGE - 1, "After insert(%d, %d)", index, elem);
    CALL_DUMP(list, message);
#endif

    return {tempFree, LIST_OK};
}

int ListPrintElems(List* list)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        CALL_DUMP(list, "Error!");
        return -1;
    }

    size_t numOfElems = ListGetNumOfElems(list);

    printf("Index Data  Next  Prev\n");
    for (int i = 1; i <= (int)numOfElems; i++)
    {
        printf("%-5d %-5d %-5d %-5d\n", i, ListGetData(list, i).retValue, ListGetNext(list, i), ListGetPrev(list, i));
    }

    return 0;
}

int ListDeleteElem(List* list, int index)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        CALL_DUMP(list, "Error!");
        return -1;
    }

    if (ListCheckIndex(list, index))
    {
        return -1;
    }

    if (index == 0)
    {
        PRINT_LOG_FILE_LIST("ERROR: Trying to delete fiction element. Action canceled.\n");
        return -1;
    }

    int gotPrev = 0;
    if ((gotPrev = ListGetPrev(list, index)) == -1)
    {
        PRINT_LOG_FILE_LIST("ERROR: Trying to delete exist element. Action canceled.\n");
        return -1;
    }

    int gotNext = ListGetNext(list, index);

    ListSetNext(list, gotPrev, gotNext);
    ListSetPrev(list, gotNext, gotPrev);
    ListSetPrev(list, index, -1);
    ListSetNext(list, index, ListGetFree(list));
    ListSetFree(list, index);
    ListSetData(list, index, 0);
    ListDecrementElemCounter(list);

#ifdef DEBUGMODE
    char message[MAX_SIZE_OF_MESSAGE] = "";
    snprintf(message, MAX_SIZE_OF_MESSAGE - 1, "After delete(%d)", index);
    CALL_DUMP(list, message);
#endif

    return 0;
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

    if (ListGetNumOfElems(list) == 0)
    {
        errors |= BAD_NUM_OF_ELEMS;
    }

    if (ListGetNumOfElems(list) < ListGetElemCounter(list))
    {
        errors |= BAD_ELEM_COUNTER;
    }

    int tempFree = ListGetFree(list);
    if (tempFree < 0 || tempFree > (int)ListGetNumOfElems(list))
    {
        errors |= BAD_FREE;
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

int ListDtor(List* list)
{
    int errors = ListVerify(list);
    if (errors)
    {
        PRINT_LOG_FILE_LIST("ERROR: Damaged list was passed. Action canceled.\n");
        CALL_DUMP(list, "Error!");
        return -1;
    }

    ListSetFree(list, 0);
    ListSetNumOfElements(list, 0);
    ListSetElemCounter(list, 0);
    free(ListGetDataPt(list));
    ListSetDataPt(list, NULL);
    free(ListGetLinks(list));
    ListSetLinks(list, NULL);

    return 0;
}

