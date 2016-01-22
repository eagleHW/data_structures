CC=gcc
CFLAGS=-I.
DEPS=treap.h
OBJ=main.o treap/treap.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: $(OBJ)
	rm $(OBJ) ./main
