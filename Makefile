CFLAGS=-Wall -Wconversion -pedantic
LIBS=-ledit

all:
	$(CC) $(CFLAGS) $(LIBS) main.c -o ./suss

clean:
	rm -rf ./suss
