CC = gcc
OPT = -g -O3
WARN = -Wall
CFLAGS = $(OPT) $(WARN)
LDLIBS = -lm

matrix_addition: matrix_addition.o
	$(CC) $(CFLAGS) matrix_addition.o -o $@ $(LDLIBS)

matrix_vector_multi: matrix_vector_multi.o
	$(CC) $(CFLAGS) matrix_vector_multi.o -o $@ $(LDLIBS)

matrix_multi: matrix_multi.o
	$(CC) $(CFLAGS) matrix_multi.o -o $@ $(LDLIBS)

matrix_multi_dynamic: matrix_multi_dynamic.o
	$(CC) $(CFLAGS) matrix_multi_dynamic.o -o $@ $(LDLIBS)


clean:
	rm -f *.o core

realclean: clean
	rm -f matrix_addition matrix_vector_multi matrix_multi

#file dependencies
