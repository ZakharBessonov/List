#include <stdio.h>
#include <stdlib.h>

#include "list_structs.h"
#include "list_consts.h"
#include "list_setters_and_getters.h"
#include "list_general_funcs.h"
#include "list_dump.h"

extern FILE* logfileList;

void ListDump(List* list, char* fileName, char* func, int line, char* message);
{
    int errors = ListVerify(list);
    fprintf(logfileList, "<pre>\n"
                         "<h3> DUMP <red> from %s:</red> <blue>%s</blue> </h3>\n\n"
                         "List { %s:%d }", func, message, file, line);

    if (errors & NULL_LIST_POINTER)
    {
        fprintf(logfileList, " (NULL_LIST_POINTER)\n"
                             "</pre>\n\n");
        return;
    }
    else
    {
        fprintf(logfileList, "\n");
    }

    fprintf(logfileList, "Number of elements: ");
    if (errors & BAD_NUM_OF_ELEMS)
    {
        fprintf(logfileList, " %uz (BAD_NUM_OF_ELEMS)\n", ListGetNumOfElems(list));
    }
    else
    {
        fprintf(logfileList, " %uz\n", ListGetNumOfElems(list));
    }

    fprintf(logfileList, "Counter of elements: ");
    if (errors & BAD_NUM_OF_ELEMS)
    {
        fprintf(logfileList, " %uz (BAD_ELEM_COUNTER)\n", ListGetElemCounter(list));
    }
    else
    {
        fprintf(logfileList, " %uz\n", ListGetElemCounter(list));
    }

    fprintf(logfileList, "Data: ");
    if (errors & NULL_DATA_POINTER)
    {
        fprintf(logfileList, " (NULL_DATA_POINTER)\n");
    }
    else if (!(errors & BAD_NUM_OF_ELEMS))
    {
        ListPrintData(list);
    }
    else
    {
        fprintf(logfileList, " (BAD_NUM_OF_ELEMS)\n");
    }

    fprintf(logfileList, "Next: ");
    if (errors & NULL_LINKS_POINTER)
    {
        fprintf(logfileList, " (NULL_LINKS_POINTER)\n");
    }
    else if (!(errors & BAD_NUM_OF_ELEMS))
    {
        ListPrintNext(list, errors);
        if (errors & BAD_NEXT)
        {
            fprintf(logfileList, " (BAD_NEXT)\n");
        }
        else
        {
            fprintf(logfileList, "\n");
        }
    }
    else
    {
        fprintf(logfileList, " (BAD_NUM_OF_ELEMS)\n");
    }

    fprintf(logfileList, "Prev: ");
    if (errors & NULL_LINKS_POINTER)
    {
        fprintf(logfileList, " (NULL_LINKS_POINTER)\n");
    }
    else if (!(errors & BAD_NUM_OF_ELEMS))
    {
        ListPrintPrev(list);
        if (errors & BAD_PREV)
        {
            fprintf(logfileList, " (BAD_PREV)\n");
        }
        else
        {
            fprintf(logfileList, "\n");
        }
    }
    else
    {
        fprintf(logfileList, " (BAD_NUM_OF_ELEMS)\n");
    }

    fprintf(logfileList, "Image: \n");
    CreateGraph(list);
    fprintf(logfileList, "<img src=graph%d.png width=200px>\n"
                         "</pre>\n\n", ListGetFileCounter(list));
}

void ListPrintData(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (size_t i = 1; i <= numOfElems; i++)
    {
        fprintf(logfileList, "%d ", ListGetData(list, i));
    }

    fprintf(logfileList, "\n");
}

void ListPrintNext(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (size_t i = 1; i <= numOfElems; i++)
    {
        fprintf(logfileList, "%d ", ListGetNext(list, i));
    }

    fprintf(logfileList, "\n");
}

void ListPrintPrev(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (size_t i = 1; i <= numOfElems; i++)
    {
        fprintf(logfileList, "%d ", ListGetPrev(list, i));
    }

    fprintf(logfileList, "\n");
}

void CreateGraph(List* list)
{
    char graphFileName[GRAPH_FILE_NAME_MAX_LEN] = "graph";
    char numberOfFile[GRAPH_FILE_NUMBER_MAX_LEN] = itoa(ListGetFileCounter(list));
    strncat(graphFileName, numberOfFile, GRAPH_FILE_NUMBER_MAX_LEN);

    FILE* graph = fopen(graphFileName, "a");

    fprintf(graph, "digraph {\n");


}
