#ifndef LIST_DUMP_HEADER
#define LIST_DUMP_HEADER

void ListDump(List* list, const char* fileName, const char* func, int line, const char* message);

void ListPrintData(List* list);

void ListPrintNext(List* list);

void ListPrintPrev(List* list);

void ListCreateGraph(List* list);

void ListWriteDescriptionOfNodes(List* list, FILE* graph);

void ListWriteDescriptionOfEdges(List* list, FILE* graph);

void ListPrintTitleOfGraphFile(FILE* graph);

void ListMakeNodeForElements(List* list, FILE* graph, const char* fillcolor, int index);

void ListMakeNodeForHeadTailAndFree(FILE* graph);

void ListMakeEdgeFromElemToElem(FILE* graph, int start, int finish, const char* parameters);

void ListMakeErrorWarningNode(FILE* graph, int errorCounter, int wrongNumber, int indexOfWrongElem);

void ListMakeEdgesForHeadTailAndFree(FILE* graph, List* list, int head, int tail, int tempFree);

#endif
