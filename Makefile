CFLAGS=-Wall -Wconversion -pedantic
LIBS=-ledit

all: main.c
	$(CC) $(CFLAGS) $(LIBS) main.c -o ./suss

clean:
	rm -rf ./suss
