#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_structs.h"
#include "list_consts.h"
#include "list_setters_and_getters.h"
#include "list_general_funcs.h"
#include "list_dump.h"
#include "list_check_index.h"
#include "list_help_funcs.h"

extern FILE* logfileList;

void ListDump(List* list, const char* fileName, const char* func, int line, const char* message)
{
    int errors = ListVerify(list);
    fprintf(logfileList, "<pre>\n"
                         "<h3> DUMP <red> from %s:</red> <blue>%s</blue> </h3>"
                         "List { %s:%d }", func, message, fileName, line);

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
        fprintf(logfileList, " %zu (BAD_NUM_OF_ELEMS)\n", ListGetNumOfElems(list));
    }
    else
    {
        fprintf(logfileList, " %zu\n", ListGetNumOfElems(list));
    }

    fprintf(logfileList, "Counter of elements: ");
    if (errors & BAD_NUM_OF_ELEMS)
    {
        fprintf(logfileList, " %zu (BAD_ELEM_COUNTER)\n", ListGetElemCounter(list));
    }
    else
    {
        fprintf(logfileList, " %zu\n", ListGetElemCounter(list));
    }

    fprintf(logfileList, "Free: ");
    if (errors & BAD_FREE)
    {
        fprintf(logfileList, " %d (BAD_ELEM_COUNTER)\n", ListGetFree(list));
    }
    else
    {
        fprintf(logfileList, " %d\n", ListGetFree(list));
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
        ListPrintNext(list);
        if (errors & BAD_NEXT)
        {
            fprintf(logfileList, " (BAD_NEXT)\n");
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
    }
    else
    {
        fprintf(logfileList, " (BAD_NUM_OF_ELEMS)\n");
    }

    fprintf(logfileList, "Image: \n");
    ListCreateGraph(list);
    fprintf(logfileList, "<img src=graphs_png/graph%d.png width=1400px>\n"
                         "\n\n\n\n\n\n</pre>\n", ListGetFileCounter(list));
}

void ListPrintData(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (int i = 0; i <= (int)numOfElems; i++)
    {
        fprintf(logfileList, "%-5d ", ListGetData(list, i).retValue);
    }

    fprintf(logfileList, "\n");
}

void ListPrintNext(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (int i = 0; i <= (int)numOfElems; i++)
    {
        fprintf(logfileList, "%-5d ", ListGetNext(list, i));
    }

    fprintf(logfileList, "\n");
}

void ListPrintPrev(List* list)
{
    size_t numOfElems = ListGetNumOfElems(list);

    for (int i = 0; i <= (int)numOfElems; i++)
    {
        fprintf(logfileList, "%-5d ", ListGetPrev(list, i));
    }

    fprintf(logfileList, "\n");
}

void ListCreateGraph(List* list)
{
    ListIncrementFileCounter(list);
    int fileCounter = ListGetFileCounter(list);

    char graphFileName[GRAPH_FILE_NAME_MAX_LEN] = "";
    snprintf(graphFileName, GRAPH_FILE_NAME_MAX_LEN - 1, "graphs_texts/graph%d.txt", fileCounter);

    FILE* graph = fopen(graphFileName, "w");
    if (graph == NULL)
    {
        fprintf(logfileList, "ERROR: An error was occurred while opening \"%s\".\n", graphFileName);
        return;
    }

    ListPrintTitleOfGraphFile(graph);

    ListWriteDescriptionOfNodes(list, graph);
    ListWriteDescriptionOfEdges(list, graph);

    fprintf(graph, "}\n");
    fclose(graph);

    char fmt[MAX_SIZE_OF_FORMAT_STRING] = "";
    snprintf(fmt, MAX_SIZE_OF_FORMAT_STRING -1, "dot graphs_texts/graph%d.txt -Tpng -o graphs_png/graph%d.png",
                                               fileCounter, fileCounter);
    system(fmt);
}

void ListWriteDescriptionOfNodes(List* list, FILE* graph)
{
    int cntOfElems = (int)ListGetNumOfElems(list);
    int isFree = 0;
    const char colors[2][8] = {"#a6c6ff", "#c0ffc0"};

    ListMakeNodeForElements(list, graph, "#f06dfc", 0);

    for (int i = 1; i <= cntOfElems; i++)
    {
        isFree = (ListGetPrev(list, i) == -1);
        ListMakeNodeForElements(list, graph, colors[isFree], i);
    }

    ListMakeNodeForHeadTailAndFree(graph);

    fprintf(graph, "{ rank = same; ");

    for (int i = 0; i < cntOfElems; i++)
    {
        fprintf(graph, "elem%d; ", i);
    }

    fprintf(graph, "elem%d}\n", cntOfElems);
}

void ListWriteDescriptionOfEdges(List* list, FILE* graph)
{
    fprintf(graph, "edge[dir=\"both\", weight=0];\n");

    int head = ListGetHead(list);
    int tail = ListGetTail(list);
    int tempFree = ListGetFree(list);
    size_t volumeOfList = ListGetNumOfElems(list);

    int errorCounter = 0;

    for (int i = 0; i <= (int)volumeOfList; i++)
    {
        if (ListCheckIndex(list, ListGetNext(list, i)))
        {
            ListMakeErrorWarningNode(graph, errorCounter, ListGetNext(list, i), i);
            errorCounter++;

            if (ListCheckIndex(list, ListGetPrev(list, i)))
            {
                ListMakeErrorWarningNode(graph, errorCounter, ListGetPrev(list, i), i);
                errorCounter++;
            }

            ListMakeEdgeFromElemToElem(graph, i, ListGetPrev(list, i), "");
            continue;
        }
        ListMakeEdgeFromElemToElem(graph, i, ListGetNext(list, i), "");
    }

    for (int i = 0; i < (int)volumeOfList; i++)
    {
        ListMakeEdgeFromElemToElem(graph, i, i + 1, "[weight=10, style=invis]");
    }

    ListMakeEdgesForHeadTailAndFree(graph, list, head, tail, tempFree);
}

void ListPrintTitleOfGraphFile(FILE* graph)
{
    fprintf(graph, "digraph {\n");
    fprintf(graph, "nodesep = 0.5;\n");
    fprintf(graph, "rankdir=HR;\n");
    fprintf(graph, "splines = ortho;\n");
}

void ListMakeNodeForElements(List* list, FILE* graph, const char* fillcolor, int index)
{
    fprintf(graph, "elem%d [shape=Mrecord, style=filled, fillcolor=\"%s\","
                       " label = \"{index = %d | data = %d | next = %d | prev = %d}\";]\n",
                       index, fillcolor, index, ListGetData(list, index).retValue, ListGetNext(list, index),
                       ListGetPrev(list, index));
}

void ListMakeNodeForHeadTailAndFree(FILE* graph)
{
    fprintf(graph, "HEAD [shape=rectangle, color=\"#ff6200\", style=filled, fillcolor=\"#ffd085\"];\n"
                   "TAIL [shape=rectangle, color=\"#ff6200\", style=filled, fillcolor=\"#ffd085\"];\n"
                   "FREE [shape=rectangle, color=\"#ff6200\", style=filled, fillcolor=\"#ffd085\"];\n"
                   "{ rank = same; HEAD; TAIL; FREE}\n");
}

void ListMakeEdgeFromElemToElem(FILE* graph, int start, int finish, const char* parameters)
{
    fprintf(graph, "elem%d->elem%d%s;\n", start, finish, parameters);
}

void ListMakeErrorWarningNode(FILE* graph, int errorCounter, int wrongNumber, int indexOfWrongElem)
{
    fprintf(graph, "error%d [shape=octagon, style=filled, fillcolor=\"#ff0000ff\", fontcolor=\"#ffffff\", label = \"%d\"]",
                    errorCounter, wrongNumber);
    fprintf(graph, "elem%d->error%d[color=\"#ff0000ff\", style=\"bold\", dir=\"forward\"];\n", indexOfWrongElem, errorCounter);
}

void ListMakeEdgesForHeadTailAndFree(FILE* graph, List* list, int head, int tail, int tempFree)
{
    int headTailFree[] = {head, tail, tempFree};
    char tempStrings[3][5] = {"HEAD", "TAIL", "FREE"};

    for (int i = 0; i < 3; i++)
    {
        if (!ListCheckIndex(list, headTailFree[i]))
        {
            fprintf(graph, "%s->elem%d[color=\"#ff6200\"];\n", tempStrings[i], headTailFree[i]);
        }
        else
        {
            fprintf(graph, "error%s [shape=octagon, style=filled, fillcolor=\"#ff0000ff\","
                           " fontcolor=\"#ffffff\", label = \"%d\"]", tempStrings[i], headTailFree[i]);
            fprintf(graph, "%s->errorHead[color=\"#ff0000ff\", style=\"bold\", dir=\"forward\"];\n", tempStrings[i]);
        }
    }
}
