CC=cc
CFLAGS=-Wall -g
DEPS=dbg.h
OBJ=ex23_temp.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex23_temp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f ex23 *.o
