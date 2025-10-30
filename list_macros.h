#ifndef LIST_MACROS_HEADER
#define LIST_MACROS_HEADER

#define BEGIN do
#define END while(false)

#define PRINT_LOG_FILE_LIST(X, ...) BEGIN { fprintf(logfileList, "%s:%d %s: " X,__FILE__, __LINE__, __func__, ##__VA_ARGS__);\
                                   fflush(logfileList); } END

#define CALL_DUMP(X, Y) BEGIN { ListDump(X, __FILE__, __func__, __LINE__, Y); } END

#endif
