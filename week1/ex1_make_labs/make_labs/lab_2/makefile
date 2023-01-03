CC = gcc
OPT = -g -O3
WARN = -Wall
CFLAGS = $(OPT) $(WARN)
OBJECTS = data.o main.o io.o

excer1: $(OBJECTS)
	$(CC) $(CFLAGS) -o excer1 $(OBJECTS)

clean:
	rm -f *.o core

realclean: clean
	rm -f excer1

#file dependencies
data.o: data.c data.h
main.o: main.c data.h io.h
io.o: io.c io.h