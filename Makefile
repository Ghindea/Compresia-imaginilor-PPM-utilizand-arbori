CC = gcc
CFLAGS = -g -Wall -std=c11 -m64
build:
	$(CC) main.c task1.c task2.c task3.c functions.c $(CFLAGS) -o quadtree

run: build
	./quadtree
valgrind: 
	valgrind --leak-check=yes --track-origins=yes ./quadtree

clean:
	rm quadtree