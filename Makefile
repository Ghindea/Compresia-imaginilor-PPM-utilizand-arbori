CC = gcc
CFLAGS = -g -Wall
build:
	$(CC) *.c $(CFLAGS) -o quadtree

run: build
	./quadtree -d cb.out test.ppm 

valgrind: 
	valgrind --leak-check=yes --track-origins=yes ./quadtree

clean:
	rm quadtree