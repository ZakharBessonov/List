#include <stdio.h>
#include <stdlib.h>

#include "list_structs.h"
#include "list_help_funcs.h"

FILE* logfileList = NULL;

int main
{
    atexit(OpenListLogfile);

    List list = {};
    ListCtor(list, 12);





}
