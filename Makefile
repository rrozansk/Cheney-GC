# compiler to use
CC = gcc
# flags to compiler
CFLAGS = -g -Wall -O3
# include
INCLUDES = -I/include/ -Iinclude/
# lib
#LFLAGS = -L/lib/
# link libs
#LIBS = -lm
# source files
SRCS = src/bits.c src/cheney.c src/trees.c src/test.c
# auto-generate the object files
OBJS = $(SRCS:.c=.o)
# define the executable file
MAIN = cheney_test

all:    $(MAIN)

$(MAIN): $(OBJS) 
	        $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	        $(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	        $(RM) *.o *~ $(MAIN) $(OBJS)
