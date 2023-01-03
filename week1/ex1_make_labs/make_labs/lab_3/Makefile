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

# DO NOT DELETE
data.o: data.h
io.o: io.h
main.o: io.h data.h
