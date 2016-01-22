CC=gcc
CFLAGS=-I.
DEPS=stack.h
OBJ=main.o stack/stack.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: $(OBJ)
	rm $(OBJ) ./main
