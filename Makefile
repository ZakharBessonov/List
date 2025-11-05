flags=-I/Users/zaharbessonov/Desktop/Учёба\ в\ институте\ /Информатика/List/headers -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual\
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-security -Wformat-nonliteral -Wformat=2 -Winline\
-Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wshadow -Wsign-conversion -Wsign-promo\
-Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wundef -Wunreachable-code -Wunused -Wvariadic-macros\
-Wno-missing-field-initializers -Wno-narrowing -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation\
-fstack-protector -fstrict-overflow -Wlarger-than=8192 -fPIE -Werror=vla -Wchar-subscripts -Wformat-signedness\
-Wredundant-decls -Wswitch-enum -Wno-old-style-cast -fno-omit-frame-pointer -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,\shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CC=g++

sources=sources/main.cpp   sources/list_check_index.cpp   sources/list_dump.cpp   sources/list_general_funcs.cpp   sources/list_help_funcs.cpp   sources/list_setters_and_getters.cpp

all:
	$(CC) $(sources) -o list $(flags)
debug:
	$(CC) $(sources) -o list -DDEBUGMODE $(flags)
