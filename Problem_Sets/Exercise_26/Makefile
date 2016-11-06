CC=cc
CFLAGS=-Wall -g
DEPS=dbg.h
OBJ=ex26.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex26: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex26 *.o
