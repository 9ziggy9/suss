CFLAGS=-Wall -Wconversion -pedantic -Wextra
LIBS=-ledit

all: main.c
	$(CC) $(CFLAGS) main.c -o ./test

prc: main.c
	$(CC) $(CFLAGS) -E -dD main.c -o ./test.prc

interpreter: suss.c
	$(CC) $(CFLAGS) $(LIBS) suss.c -o ./suss

clean:
	rm -rf ./suss ./test
