CC=cc
CFLAGS=-Wall -g
DEPS=dbg.h
OBJ=ex25.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex25: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex25 *.o
