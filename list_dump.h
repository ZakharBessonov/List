#ifndef LIST_DUMP_HEADER
#define LIST_DUMP_HEADER

void ListDump(List* list, char* fileName, char* func, int line, char* message);

void ListPrintData(List* list);

void ListPrintNext(List* list);

void ListPrintPrev(List* list);

void CreateGraph(List* list);

#endif
