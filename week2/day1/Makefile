CC	= gcc
OPT	= -g 
CHIP	= 
ISA	= 
DEFS	= 
LIBS	= -lm
CFLAGS  = $(OPT) $(CHIP) $(ISA) $(DEFS) $(XOPT)

SOURCES = xtime.c
OBJECTS = $(SOURCES:.c=.o)

TARGET_PAR = pi_parallized.$(CC)
TARGET_UNPAR = pi_unparallized.$(CC)
TARGETS = $(TARGET_PAR) $(TARGET_UNPAR)

all: 
	$(MAKE) $(MAKEFLAGS) clean
	$(MAKE) $(MAKEFLAGS) $(TARGET_PAR)
	$(MAKE) $(MAKEFLAGS) clean
	$(MAKE) $(MAKEFLAGS) $(TARGET_UNPAR)

$(TARGET_PAR): clean $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) pi_parallized.o $(LIBS)

$(TARGET_UNPAR): clean $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) pi_unparallized.o $(LIBS)

clean:
	@/bin/rm -f $(OBJECTS) core

realclean: clean
	@/bin/rm -f $(TARGETS)


# DO NOT DELETE
pi_parallized.o: xtime.h
pi_unparallized.o: xtime.h
