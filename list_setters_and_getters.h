#ifndef LIST_GENERAL_FUNCS_HEADER
#define LIST_GENERAL_FUNCS_HEADER

#include "list_structs.h"

// Getters

RetAndErrors GetData(List* list, int index);

int ListGetNext(List* list, int index);

int ListGetPrev(List* list, int index);

int ListGetFree(List* list);

int ListGetHead(List* list);

int ListGetTail(List* list);

int ListGetFileCounter(List* list)

size_t ListGetNumOfElems(List* list);

size_t ListGetElemCounter(List* list);

// Setters

int ListSetData(List* list, int index, int value);

int ListSetNext(List* list, int index, int value);

int ListSetPrev(List* list, int index, int value);

int ListSetFree(List* list, int value);

size_t ListIncrementElemCounter(List* list);

int ListIncrementFileCounter(List* list)

#endif
