all: p1fifo.c p2fifo.c
	gcc p1fifo.c -o p1fifo
	gcc p2fifo.c -o p2fifo