#ifndef LIST_STRUCTS_HEADER
#define LIST_STRUCTS_HEADER

enum Error
{
    LIST_OK = 0,
    NULL_LIST_POINTER = 1,
    NULL_DATA_POINTER = 2,
    NULL_LINKS_POINTER = 4,
    BAD_NUM_OF_ELEMS = 8,
    BAD_ELEM_COUNTER = 16,
    BAD_NEXT = 32,
    BAD_PREV = 64,
    BAD_INDEX = 128,
    FULL_LIST = 256
}

struct RetAndErrors
{
    int retValue;
    int error;
}

struct Links
{
    int next;
    int prev;
}

struct List
{
    size_t  numOfElems;
    size_t  elemCounter;
    int*    data;
    Links*  links;
    int     head;
    int     tail;
    int     free;
    int     fileCounter;
}

#endif
