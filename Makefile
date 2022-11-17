CFLAGS=-Wall -Wconversion -pedantic
LIBS=-ledit -lm
OBJS=./build/mpc.o

all: mpc
	$(CC) $(CFLAGS) $(LIBS) main.c -o ./suss

mpc: mpc.c
	$(CC) $(CFLAGS) $(LIBS) mpc.c -c -o ./build/mpc.o

clean:
	rm -rf ./suss ./build/*
