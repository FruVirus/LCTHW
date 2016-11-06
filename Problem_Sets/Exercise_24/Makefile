CC=cc
CFLAGS=-Wall -g
DEPS=dbg.h
OBJ=ex24.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex24: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex24 *.o
