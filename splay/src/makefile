CC=gcc
CFLAGS= -std=c99 -I.       ##-W -std=c99 -I.
OBJ=main.o splay/splay.o
DEPS=splay/splay.h 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: $(OBJ) 
	rm $(OBJ) ./*~ ./splay/*~ ./main
