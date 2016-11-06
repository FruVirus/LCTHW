CC=cc
CFLAGS=-Wall -g
DEPS=dbg.h
OBJ=ex27.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex27: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex27 *.o
