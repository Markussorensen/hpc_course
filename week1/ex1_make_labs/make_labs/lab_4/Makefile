CC	= gcc
DEBUG	= -g -Wall
OPT	= -O3
CFLAGS	= $(DEBUG) $(OPT)
OBJECTS = data.o main.o io.o
LDFLAGS = $(CFLAGS)

project1: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS) -lm

clean:
	/bin/rm -f *.o core 

realclean: clean
	/bin/rm -f project1

data.o: data.c data.h
main.o: data.h io.h main.c
io.o  : io.h io.c
