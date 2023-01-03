F90C	= gfortran
F90FLAGS= -g -Wall -O3
OBJECTS	= f90main.o
LDFLAGS = $(F90FLAGS)

f90project: $(OBJECTS)
	$(F90C) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

clean:
	rm -f *.o core

realclean: clean
	rm -f f90project

%.o: %.f90
	$(F90C) $(F90FLAGS) -c $< -o $@

