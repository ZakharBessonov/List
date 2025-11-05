#ifndef LIST_SETTERS_AND_GETTERS_FUNCS_HEADER
#define LIST_SETTERS_AND_GETTERS_FUNCS_HEADER

#include "list_structs.h"

// Getters

RetAndErrors ListGetData(List* list, int index);

int ListGetNext(List* list, int index);

int ListGetPrev(List* list, int index);

int ListGetFree(List* list);

int ListGetHead(List* list);

int ListGetTail(List* list);

int ListGetFileCounter(List* list);

size_t ListGetNumOfElems(List* list);

size_t ListGetElemCounter(List* list);

int* ListGetDataPt(List* list);

Links* ListGetLinks(List* list);

// Setters

int ListSetData(List* list, int index, ListElem_t value);

int ListSetNext(List* list, int index, int value);

int ListSetPrev(List* list, int index, int value);

int ListSetFree(List* list, int value);

size_t ListIncrementElemCounter(List* list);

size_t ListDecrementElemCounter(List* list);

void ListSetFileCounter(List* list, int value);

void ListSetElemCounter(List* list, size_t value);

void ListSetNumOfElements(List* list, size_t value);

void ListSetDataPt(List* list, int* pt);

void ListSetLinks(List* list, Links* pt);

int ListIncrementFileCounter(List* list);

#endif
