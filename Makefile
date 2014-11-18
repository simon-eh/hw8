CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic

all: encode
encode: encode.c
	$(CC) $(CFLAGS) encode.c -o encode
run: encode.exe
	./encode.exe encode.test
clean:
	rm -f encode.exe