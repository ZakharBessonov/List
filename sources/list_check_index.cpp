#include <stdio.h>

#include "list_structs.h"
#include "list_check_index.h"

int ListCheckIndex(List* list, int index)
{
    return (index < 0 || index > (int)list->numOfElems);
}

