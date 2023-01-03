excer1: data.o main.o io.o
	cc -o excer1 data.o main.o io.o
	echo "Done"

data.o: data.c data.h
	cc -c data.c

main.o: main.c data.h io.h
	cc -c main.c

io.o: io.c io.h
	cc -c io.c

clean:
	rm -f *.o core