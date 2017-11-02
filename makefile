all:
	gcc -c *c
	gcc -o Problem_6 Problem_6.c -lpthread

clean:
	rm Problem_6 *o
