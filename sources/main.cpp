#include <stdio.h>
#include <stdlib.h>

#include "list_structs.h"
#include "list_help_funcs.h"
#include "list_general_funcs.h"
#include "list_dump.h"
#include "list_macros.h"
#include "list_setters_and_getters.h"

FILE* logfileList = NULL;

int main()
{
    atexit(CloseListLogfile);

    if (OpenLogfileList())
    {
        return 0;
    }

    List list = {};

    ListCtor(&list, 9);
    CALL_DUMP(&list, "Before changes");

    ListInsertAfter(&list, 0, 100);
    ListInsertAfter(&list, 1, 200);
    ListInsertAfter(&list, 2, 300);
    ListInsertAfter(&list, 3, 400);
    ListInsertAfter(&list, 4, 500);
    ListInsertAfter(&list, 5, 600);
    ListInsertAfter(&list, 6, 700);
    ListInsertAfter(&list, 7, 800);
    ListInsertAfter(&list, 8, 900);

    ListSetNext(&list, 6, 300);
    ListSetNext(&list, 4, 2);
    CALL_DUMP(&list, "Before changes");

    ListDtor(&list);

    return 0;
}
