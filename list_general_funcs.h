#ifndef LIST_GENERAL_FUNCS_HEADER
#define LIST_GENERAL_FUNCS_HEADER

#include "list_structs.h"

int ListCtor(List* list, size_t numOfElems);

int ListDtor(List* list);

RetAndErrors ListInsertBefore(List* list, int index, int elem);

RetAndErrors ListInsertAfter(List* list, int index, int elem);

int ListDeleteElem(List* list, int index);

int ListDtor(List* list, int index);

int ListVerify(List* list);

#endif
