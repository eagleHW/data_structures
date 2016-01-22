CC=gcc
CFLAGS= -std=c99 -I.       ##-W -std=c99 -I.
OBJ=main.o interval_tree/interval.o
DEPS=interval_tree/interval.h 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: $(OBJ) 
	rm $(OBJ) ./*~ ./interval_tree/*~ ./main ./*#
