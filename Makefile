CFLAGS=-Wall -Wconversion -pedantic
LIBS=-ledit
OBJS=./build/mpc.o

all: mpc
	$(CC) $(CFLAGS) $(LIBS) main.c $(OBJS) -o ./suss

mpc: mpc.c
	$(CC) $(CFLAGS) -lm mpc.c -c -o ./build/mpc.o

clean:
	rm -rf ./suss ./build/*
