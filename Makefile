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
# garbage collection main executable
MAIN_DEPS = include/cheney.h src/cheney.c src/main.c
# auto-generate the object files
MAIN_OBJS = $(MAIN_DEPS:.c=.o)
# define the executable file
MAIN = cheney
# garbage collection test executable
TEST_DEPS = include/cheney.h src/cheney.c test/testCHENEY.c
# auto-generate the object files
TEST_OBJS = $(TEST_DEPS:.c=.o)
# define the executable file
TEST = ctest

# targets not dependent on files so make doesnt get confused
.PHONY:  default build rebuild all install clean tar

default: $(MAIN)

build:   $(MAIN)

rebuild: clean build

all:     $(MAIN)

$(MAIN): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(MAIN_OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

install:  rebuild
	\cp $(MAIN) /usr/bin/

clean:
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(MAIN)

tar:
	\tar -cvf $(MAIN).tar $(TAR_FILES)

$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(TEST_OBJS) $(LFLAGS) $(LIBS)
	./$(TEST)
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(TEST)
