CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -Wconversion

suss: main.c
	$(CC) $(CFLAGS) main.c -o suss

clean:
	rm -r suss
