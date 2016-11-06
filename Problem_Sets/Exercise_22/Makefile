CC=cc
CFLAGS=-Wall -g
DEPS=ex22.h dbg.h
OBJ=ex22_main.o ex22.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex22_main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex22_main *.o
