CC = gcc
CFLAGS = -g -Wall -std=c11
build:
	$(CC) *.c $(CFLAGS) -o quadtree

run: build
	./quadtree
valgrind: 
	valgrind --leak-check=yes --track-origins=yes ./quadtree

clean:
	rm quadtree