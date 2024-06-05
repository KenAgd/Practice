#@ symbol used in front of echo so that the echo command itself isn't printed and only whats in the "" is printed

#-g allows for gdb to be used on the program if I want/need to use it

#-Wall turns on warnings such as unused variables, uninitialized variables, implicit function declarations, and control reaches end of non-void function

#-o renames the executable to whatever is after it instead of the default "a.out"

#-c compiles without linking any files

#the way "all" command works is that it compiler looks at "all" call which is linked to "final" call. "final" call is linked to "main.o" call, which is the bottom of the call chain. It runs "main.o" first and then "final.


CC := gcc
GCC_FLAGS = -g -Wall
CLANG_FLAG = -g -Wall

ifeq ($(CC), gcc)
	CFLAGS := $(GCC_FLAGS)
else ifeq ($(CC),  clang)
	CFLAGS := $(CLANG_FLAGS)
endif

SOURCES := main.c avl.c merge.c
EXECUTABLE := bank

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)

valgrind: $(EXECUTABLE)
	valgrind --leak-check=yes --track-origins=yes --verbose --error-exitcode=1 ./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
