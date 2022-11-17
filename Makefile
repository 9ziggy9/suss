CFLAGS=-Wall -Wconversion -pedantic

all:
	$(CC) $(CFLAGS) main.c -o ./suss

clean:
	rm -rf ./suss
