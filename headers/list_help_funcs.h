#ifndef LIST_HELP_FUNCS_HEADER
#define LIST_HELP_FUNCS_HEADER

#include "list_structs.h"

int ListCheckNext(List* list);

int ListCheckPrev(List* list);

int OpenLogfileList();

void CloseListLogfile();

#endif
