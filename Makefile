# compiler to use gcc, clang, g++, etc.
CC = gcc
# compiler flags (add -g for debug)
CFLAGS = -Wall -O3
# includes (header file locations)
INCLUDES = -I/include/ -Iinclude/
# libraries (library file location)
LFLAGS = -L/lib/
# libraries to link
LIBS = -lm
# all the files to include in the generated .tar
TAR_FILES = include/*.h src/*.c test/*.c LICENSE.txt Makefile README.md
# name of generated tar
TAR_NAME = cheney
# garbage collection table driven tests executable
TEST_DEPS = include/cheney.h src/cheney.c test/testCHENEY.c
# auto-generate the object files
TEST_OBJS = $(TEST_DEPS:.c=.o)
# define the executable file
TEST = tests

# targets not dependent on files so make doesnt get confused
.PHONY:  default build rebuild all install clean tar

default: $(TEST)

build:   $(TEST)

rebuild: clean build

all:     $(TEST)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	\rm -f *.o *~ src/*.o src/*~ include/*.o include/*~ test/*.o test/*~ $(TEST)

tar:
	\tar -cvf $(TAR_NAME).tar $(TAR_FILES)

$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(TEST_OBJS) $(LFLAGS) $(LIBS)
	./$(TEST)
	\rm -f *.o *~ src/*.o src/*~ include/*.o include/*~ test/*.o test/*~ $(TEST)
